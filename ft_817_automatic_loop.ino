/*

    Apr 21th 2012
    
    FT-817 Automatic Loop
    by Alain De Carolis, WW3WW
    version 1.0
    
    This progam uses a modified version of the qrptracker library
    written by Bruce Gordon Robertson, VE9QRP
    
    released under the GPL V3 license
    
    for more info and full source code visit
    https://code.google.com/p/ft-817-automatic-loop/
    
*/

#include <SoftwareSerial.h>
#include "FT817.h"
#include <PWMServo.h> 
#include <EEPROM.h>

const int addr = 0;            // EEPROM address for saving the current capacitor position

int n = LOW;
int encoder0PinALast = LOW;

const int encoder0PinA = 3;    // Encoder PinA
const int encoder0PinB = 4;    // Encoder PinB
const int stepTime = 100;      // Mesures slow or fast encoder rotation
const int bigStep = 10;        // degrees during fast rotation
const int smallStep = 1;       // degrees during slow rotation
int step;

const int rxPin = 8;
const int txPin = 7;

const int buttonPin = 5;       // tuning button - push to tune
int buttonState = 0;           // tune button

const int ledPin = 12;         // tuning led - ON when tuning was successul
const int ledPinON = 11;       // tuned led - ON when tuned OK - blink for errors
const int servoPin = 9;        // this MUST be 9 when using the PWMServo lib
const int buzzerPin = 10;      // some acoustic effects
const int servoTimeout = 2000; // 2 seconds unused and the servo will detach

unsigned long servoTime;       // used to decide when we can detach the servo
unsigned long encoderTime;     // used to determine the econcoder rotation speed

int pos;                       // Servo Position helper variable
int swr;                       // SWR helper variable

const int minPos = 9;          // Minimum Position reachable by the Servo
const int maxPos = 180;        // Maximum Position reachable by the Servo

PWMServo myservo;
FT817 rig;

void setup() {

    pinMode (encoder0PinA,INPUT);
    pinMode (encoder0PinB,INPUT);
  
    Serial.begin(9600);
    SoftwareSerial mySerial(rxPin,txPin);
    rig.assignSerial(mySerial);
    
    pinMode(ledPin, OUTPUT);
    pinMode(ledPinON, OUTPUT);
    pinMode(buttonPin, INPUT);
    
    digitalWrite(ledPinON, HIGH);
    
    pos = EEPROM.read(addr);
    myservo.attach(servoPin);
    myservo.write(pos);
    Serial.print("Servo positioned to ");
    Serial.println(pos);
    servoTime = millis();
  
}

void loop() {
  
    // I can't understand why I need the following line
    // for now I'll live with it
    rig.begin(9600);
    
    if(( myservo.attached() ) && (millis() > (servoTime + servoTimeout))) {
      myservo.detach();
      Serial.println("Detaching the Servo");
      EEPROM.write(addr, pos);
      Serial.print("Servo position saved to ");
      // Saving the current position to the EEPROM
      // so I can safely turn power off the tuner
      // when unused
      Serial.println(EEPROM.read(addr));
    }
  
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);

    // if the pushbutton is pressed start tuning
    if (buttonState == HIGH) {
        tune();
    }
    
    // check the encoder    
    n = digitalRead(encoder0PinA);
    
    if ((encoder0PinALast == LOW) && (n == HIGH)) {
      
      if (! myservo.attached() ) {
        myservo.attach(servoPin);
        myservo.write(pos);
      }
      
      // Choose between fast or slow move      
      if (millis() - encoderTime > stepTime) {
        step = smallStep;
      } else {
        step = bigStep;
      }
      
      encoderTime = millis();
      
      if (digitalRead(encoder0PinB) == LOW) {
        
        if( pos >= maxPos ) { pos = maxPos; singleFlash(); }
        else {
          pos += step;
        }
        
      } else { // digitalRead(encoder0PinB) == HIGH
        
        if( pos <= minPos ) { pos = minPos; singleFlash(); }
        else {
          pos -= step;
        }
        
      }
     
     Serial.print("Position selected by the Encoder: ");
     Serial.println (pos);
     myservo.write(pos);
     servoTime = millis();
     
   }
   encoder0PinALast = n;
     
}

void tune() {

    boolean tuned = 0;
    unsigned int quadrant = 0;
    unsigned long sweepTime;
    unsigned int quadrantSize = 15;
    unsigned quadrantTime = 150;
  
    Serial.println("At Tune...");

    // Get current mode
    byte mode = rig.getMode();
    Serial.print("The Radio is in mode ");
    Serial.println(mode);

    // Set FM for Tuning
    rig.setMode(FT817_MODE_FM);
    
    // Set TX on
    rig.setPTTOn();
    delay(300);
    
    // read the first SWR measure   
    swr = rig.getSWR();
    
    Serial.print("Initial SWR ");
    Serial.println(swr);
    
    if (! rig.getTXSuccess()) {
      rig.setPTTOff();
      delay(300);
      rig.setMode(mode);
      Serial.println("Error: The Radio cannot transmit!");
      errorBeep();
      return;
    }
    
    if (swr <= 3) {
      rig.setPTTOff();
      delay(300);
      rig.setMode(mode);
      Serial.println("Already Tuned");
      successBeep();
      return;
    }
    
    Serial.println("Moving the Capacitor");
    if (! myservo.attached() ) {
      myservo.attach(servoPin);
      servoTime = millis();
    }

    // Move to one end
    // TODO: choose the right end depending on where the capacitor
    // already is
    
    myservo.write(minPos);
    servoTime = millis();
    
    // give some time to the servo to reach its position
    // a standard HS-322HD does 0.19 sec/60° at 4.8V
    
    delay(1500); 
    
    Serial.println("Starting the SWR Samples");
    // This is faster than sampling one degree at a time
    for( pos = minPos; pos <= maxPos; pos += quadrantSize ) {
      
      quadrant++;

      Serial.print("Entering quadrant ");
      Serial.print(quadrant);
      Serial.print(": ");
      Serial.print(quadrantSize * (quadrant -  1) + minPos);
      Serial.print("-");
      Serial.println(quadrantSize * quadrant + minPos);
      
      myservo.write(pos);
      
      servoTime = millis();

      for(sweepTime = servoTime; sweepTime <= servoTime + quadrantTime; sweepTime = millis()) {
        
        // Stop if a button is pressed
        if ( digitalRead(buttonPin) == HIGH ) {
          errorBeep();
          break;
        }
          
        swr = rig.getSWR();
        Serial.print(" SWR: ");
        Serial.println(swr);
  
        if (swr == 0) {
              
          Serial.println(" SWR 0 Found!");
          tuned = 1;
          break;
              
        }

      }
      
      if (tuned) {
        Serial.print("Tunable in quadrant ");
        Serial.println(quadrant);
        
        // Fine Tuning
        // Go back two quadrants to find the right position
        tuned = 0;
        for (pos = quadrantSize * quadrant + minPos; 
             pos >= quadrantSize * ( quadrant - 2) + minPos;
             pos--) {
          
          myservo.write(pos);
          Serial.print("Trying pos ");
          Serial.print(pos);
          delay(50);
          swr = rig.getSWR();
          Serial.print(" SWR: ");
          Serial.println(swr);
          
          if (swr == 0) {
             Serial.print("Tuned to pos ");
             Serial.println(pos);
             tuned = 1;
             break;
          } 
          
        }
        
        break;   

      } 
      
    }
        
    // The End
    // back to RX
    rig.setPTTOff();
    delay(300);
    // Switch back to original mode
    rig.setMode(mode);
    
    if (tuned) {
      successBeep();
    } else {
      errorBeep();
    }
    
}

void singleFlash() {
   
   digitalWrite(ledPinON, LOW);
   delay(300);
   digitalWrite(ledPinON, HIGH);   
   
}

void errorBeep() {
   
   digitalWrite(ledPinON, LOW);
   delay(300);
   digitalWrite(ledPinON, HIGH);
   delay(300);
   digitalWrite(ledPinON, LOW);
   delay(300);
   digitalWrite(ledPinON, HIGH);
   delay(300);   
   tone(buzzerPin, 800, 500);
   
}

void successBeep() {
  
   digitalWrite(ledPin, HIGH);

   tone(buzzerPin, 600, 500);
   digitalWrite(ledPin, HIGH);
   delay(100);
   digitalWrite(ledPin, LOW);
   
   tone(buzzerPin, 800, 500);
   digitalWrite(ledPin, HIGH);
   delay(100);
   digitalWrite(ledPin, LOW);

   tone(buzzerPin, 1000, 500);
   digitalWrite(ledPin, HIGH);
   delay(100);
   
   digitalWrite(ledPin, LOW);
   
}
