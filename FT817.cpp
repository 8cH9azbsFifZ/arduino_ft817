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

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

#include "FT817.h"
#define DEBUG false
extern SoftwareSerial rigSoftSerial(16,17);

FT817::FT817()
{
    //pass in serial port here?
    pinMode(13, OUTPUT); 
}

void FT817::assignSerial(SoftwareSerial s) {
    rigSoftSerial = s;
}

void FT817::begin(int baud) {
    rigSoftSerial.begin(baud);
}

boolean FT817::setLockOn() {
    rigSoftSerial.flush();
    fourBytePreamble();
    sendCATCommandChar(FT817_LOCK_ON);
    byte b = readOneChar();
    
    if (b == 240) {
        if (DEBUG) { Serial.println("Lock was ON"); }
        was_locked = true;
    }
    
    else {
        if (DEBUG) { Serial.println("Lock was OFF"); }
        was_locked = false;
    }
    
    return was_locked;
}

boolean FT817::setLockOff() {
    rigSoftSerial.flush();
    fourBytePreamble();
    sendCATCommandChar(FT817_LOCK_OFF);
    byte b = readOneChar();
    
    if (b == 240) {
        if (DEBUG) { Serial.println("Lock was OFF"); }
        was_locked = false;
    }
    
    else {
        if (DEBUG) { Serial.println("Lock was ON"); }
        was_locked = true;
    }
    
    return was_locked;
}
void FT817::setCTCSSEncoderOn() {
    sendCATCommandChar(FT817_CTCSS_ENCODER_ON);
    threeBytePreamble();
    sendCATCommandChar(FT817_SET_CTCSS);
    readOneChar();
}

void FT817::setCTCSSOff() {
    sendCATCommandChar(FT817_CTCSS_OFF);
    threeBytePreamble();
    sendCATCommandChar(FT817_SET_CTCSS);
    readOneChar();
}

void FT817::setCTCSSFreq(unsigned int freq) {
    byte freq_bcd[2];
    to_bcd_be(freq_bcd, (long)  freq, 4);
    sendCATCommandChar(freq_bcd[0]);
    sendCATCommandChar(freq_bcd[1]);
    sendCATCommandChar(FT817_ANY_BYTE);
    sendCATCommandChar(FT817_ANY_BYTE);
    sendCATCommandChar(FT817_SET_CTCSS_FREQ);
    readOneChar();
}

void FT817::verifiedSetFreq(unsigned long freq) {
    if (setFreqTest(freq)) {
    return;
    }
    else if (setFreqTest(freq)) {
        return;
    }
    else {
        rigComError("Serious rig setting failure");
    }
}


void FT817::blink() {
    digitalWrite(13, HIGH);   // set the LED on
    delay(500);                  // wait for a second
    digitalWrite(13, LOW);    // set the LED off
    delay(500);
    digitalWrite(13, HIGH);   // set the LED on
    delay(500);                  // wait for a second
    digitalWrite(13, LOW);    // set the LED off
    delay(500);
}
void FT817::rigComError(char * string) {
    //blink();
    Serial.print("Rigcomm error: ");
 Serial.println(string);
 //instead loop the getFreqMode until we get good data
}

void FT817::setMode(byte mode) {
    if (mode <= 8) {
        sendCATCommandChar(mode);
        threeBytePreamble();
        sendCATCommandChar(FT817_MODE_SET);
        readOneChar();
    }
}

byte FT817::getMode() {
    unsigned long l = getFreqMode();
    return mode;
}

boolean FT817::setFreqTest(unsigned long freq) {
    setFreq(freq);
    //delay(100);
    unsigned long freqOut = getFreqMode();
    if (freqOut == freq) {
    /*
    Serial.print("pass: ");
    Serial.println(freqOut);
    */
    return true;
    }
    else { 
        if (DEBUG) {
            Serial.print("sent in: ");
            Serial.print(freq);
            Serial.print("got out: ");
            Serial.println(freqOut);
        }
    //rigComError("failed setfreqtest");
    return false;
    }
}

void FT817::setFreq(long freq) {
    unsigned char foo[4];
    // char bar[] = {0x11, 0x22};
    out = to_bcd_be(foo, freq, 8);
    sendCATCommandArray(out, 4);
    sendCATCommandChar(FT817_FREQ_SET);
    readOneChar();
}


unsigned long FT817::getFreqMode() {
    rigSoftSerial.flush();// not sure why I have to do this.
    //check for data after setFreq
    boolean readValid = true;
    fourBytePreamble();
    sendCATCommandChar(FT817_FREQMODE_READ);
    byte chars[4];
    long timeout = millis();
    long elapsed = 0;
    while (rigSoftSerial.available() < 5 && elapsed < 2000) {
        elapsed = millis() - timeout;
    }
    if (elapsed >= 2000) {
        if (DEBUG) {Serial.println("timeout on getfreqMode");}
        readValid = false;
    }
    else {
        if (DEBUG) {
            Serial.print("getfreQMode took: ");
            Serial.println(elapsed);
        }
        for (int i = 0; i < 4; i++) {
            chars[i] = rigSoftSerial.read(); 
            if (DEBUG) { Serial.println(chars[i]); }
        }
        mode = rigSoftSerial.read();
    } 

    if (readValid == false) {
        return FT817_BAD_READ;
    }  

    else {
        freq = from_bcd_be(chars, 4);
        if (DEBUG) {Serial.print("Final result from getfreqmode: ");}
        if (DEBUG) {Serial.println(freq);}
        return freq;
     }
}

char FT817::readOneChar() {
    
    long timeout = millis();
    long elapsed = 0;
    while (rigSoftSerial.available() < 1 && elapsed < 200) {
         elapsed = millis() - timeout;
    }
    if (elapsed >= 200) {
        if (DEBUG) {
            Serial.println("readOneChar timeout");
        }
        return 0;
    }
    else {
        byte b = rigSoftSerial.read();
        if (DEBUG) {
            Serial.print("read char: ");
            Serial.println((int)b);
        }
    return b;
    }
}

void FT817::sendCATCommandChar(int command) {
    if (DEBUG) {
        Serial.print(byte(command));
    }
    rigSoftSerial.write(byte(command));
}

void FT817::sendCATCommandArray(  byte command[], int len) {
    for (int x = 0; x < len; x++) {
        if (DEBUG) {
        Serial.print(byte(command[x]));
    }
    rigSoftSerial.write(byte(command[x]));
    }
}

void FT817::fourBytePreamble() {
     sendCATCommandChar(FT817_ANY_BYTE);
     threeBytePreamble();
}

void FT817::threeBytePreamble() {
    sendCATCommandChar(FT817_ANY_BYTE);
    sendCATCommandChar(FT817_ANY_BYTE);
    sendCATCommandChar(FT817_ANY_BYTE);
}

void FT817::flush() {
    rigSoftSerial.flush();
}
void FT817::off() {
    simpleCommand(FT817_OFF);
}

void FT817::on() {
    fourBytePreamble();
    sendCATCommandChar(FT817_ANY_BYTE);
    simpleCommand(FT817_ON);
}

void FT817::setSplitModeOn() {
    simpleCommand(FT817_SPLITMODE_ON);
}


void FT817::setSplitModeOff() {
    simpleCommand(FT817_SPLITMODE_OFF);
}

void FT817::switchVFO() {
    simpleCommand(FT817_VFOMODE);
}

void FT817::setPTTOff() {
    //Serial.print("Ptt off: ");
    simpleCommand(FT817_PTT_OFF);    
}

void FT817::setPTTOn() {
    simpleCommand(FT817_PTT_ON);
}

boolean FT817::txMeters() {
    
    rigSoftSerial.flush();
    fourBytePreamble();
    sendCATCommandChar(FT817_READ_TX_METERS);
    byte b = readOneChar();
    
    if (b == false) {
        if (DEBUG) { Serial.println("Error"); }
        return false;
    }
    
    else if (b == 255) {
        if (DEBUG) { Serial.println("RX"); }
        return false;
    }
    
    else {
    
        byte c = readOneChar();

        pwr = b / 16;
        alc = b & 15;
        swr = c / 16;
        mod = c & 15;
        
        if (DEBUG) {
            Serial.println("TX");
            Serial.print("Power: ");
            Serial.println(pwr);
            Serial.print("SWR: ");
            Serial.println(swr);
            Serial.print("ALC: ");
            Serial.println(alc);
            Serial.print("Mod: ");
            Serial.println(mod);
        }
        
        return true;
        
    }
}

int FT817::getSWR() {

    tx = txMeters();
    return swr;

}

boolean FT817::getTXSuccess() {
    
    return tx;
    
}

boolean FT817::txState() {
    fourBytePreamble();
    sendCATCommandChar(FT817_READ_TX_STATE);
    byte b = readOneChar();
    
    if (b == 0) {
        return false;
    }
    else {
        return true;
    }
}

boolean FT817::txState2() {
    fourBytePreamble();
    sendCATCommandChar(FT817_READ_TX_STATE2);
    byte b = readOneChar();
    if (b == FT817_NOPTT) {
        return false;
    }
    else {
        return true;
    }
}

void FT817::simpleCommand(int command) {
    fourBytePreamble();
    sendCATCommandChar(command);
    readOneChar();
}

unsigned long FT817::from_bcd_be(unsigned char const* nybbles, size_t length)
{
    unsigned long result(0);
    while (length--) {
        result = result * 100 + (*nybbles >> 4) * 10 + (*nybbles & 15);
        ++nybbles;
    }
    return result;
}


//protected under gpl
 unsigned char * FT817::to_bcd_be( unsigned char bcd_data[], unsigned long  freq, unsigned bcd_len)
{
    int i;
     unsigned char a;

    /* '450'/4 -> 0,4;5,0 */
    /* '450'/3 -> 4,5;0,x */

    if (bcd_len&1) {
        bcd_data[bcd_len/2] &= 0x0f;
        bcd_data[bcd_len/2] |= (freq%10)<<4;    /* NB: low nibble is left uncleared */
        freq /= 10;
    }
    for (i=(bcd_len/2)-1; i >= 0; i--) {
        a = freq%10;
        freq /= 10;
        a |= (freq%10)<<4;
        freq /= 10;
        bcd_data[i] = a;
    }

    return bcd_data;
}
