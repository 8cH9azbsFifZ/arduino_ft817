#include "WProgram.h"
#include "FT817.h"
#include <../NewSoftSerial/NewSoftSerial.h>
#define DEBUG false
extern NewSoftSerial rigSoftSerial(16,17);

FT817::FT817()
{
  //pass in serial port here?
  pinMode(13, OUTPUT); 

}

void FT817::assignSerial(NewSoftSerial s) {
  rigSoftSerial = s;
}

void FT817::begin(int baud) {
  rigSoftSerial.begin(baud);

}

void FT817::setLockOff() {
	  simpleCommand(0x80);
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
  	if (DEBUG) {
  		//Serial.print(0xFE,BYTE);
  		//Serial.print(mode, BYTE);
  	}
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

  /*Serial.print("pass: ");
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
  	   // rigComError("failed setfreqtest");
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
  //rigSoftSerial.flush();// not sure why I have to do this.
  //check for data after setFreq
  boolean readValid = true;
  fourBytePreamble();
  sendCATCommandChar(FT817_FREQMODE_READ);
  byte chars[4];
  if  (DEBUG) {Serial.print(0xBB, BYTE);}
     long timeout = millis();
     long elapsed = 0;
      while (rigSoftSerial.available() < 5 && elapsed < 2000) {
      	elapsed = millis() - timeout;
     	;}
  if (elapsed > 2000) {
  	if (DEBUG) {Serial.println("timeout on getfreqMode");}
  }
  else {
  	if (DEBUG) {
  	Serial.print("getfreQMode took: ");
  	Serial.println(elapsed);
  	}
  }
  for (int i = 0; i < 4; i++) {
     	chars[i] = rigSoftSerial.read();  
   
     if(chars[i] > 0x99) {
	//  readValid = false;  // if any character is bad then the whole string is bad
     }
  }
  mode = rigSoftSerial.read(); 
  if (DEBUG) {Serial.print(0xBB, BYTE);}
  /*
  if (readValid == false) {
    return FT817_BAD_READ;
  }
  
  else {
  */
  
//    if (true) {Serial.print("#");}
    freq = from_bcd_be(chars, 8);
  //  Serial.print("Final result from getfreqmode: ");
  //  Serial.println(freq);
    return freq;

//}
}

char FT817::readOneChar() {
	unsigned long startTime = millis();
	while (rigSoftSerial.available() < 1 && millis() < startTime + 2000) {
		;
	}
	if (millis() > startTime + 2000L) {
		if (DEBUG) {
			Serial.println("timeout");
			}
	//	return 0;
	}
	else {
	byte b = rigSoftSerial.read();
	if (DEBUG) {
	Serial.print("read char: " );
	Serial.print((int)b);
	Serial.print(" after ");
	Serial.println(millis()- startTime);
	}
	return b;
	}
	
}

void FT817::sendCATCommandChar(int command) {
	if (DEBUG) {
		Serial.print(command, BYTE);
	}
  rigSoftSerial.print(command, BYTE);
}

void FT817::sendCATCommandArray(  byte command[], int len) {
  for (int x = 0; x < len; x++) {
  	if (DEBUG) {
		Serial.print(command[x], BYTE);
	}
    rigSoftSerial.print(command[x], BYTE);
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

//Protected under gpl
unsigned long FT817::from_bcd_be(const  byte bcd_data[], unsigned bcd_len)
{
	int i;
	long f = 0;

	for (i=0; i < bcd_len/2; i++) {
		f *= 10;
		f += bcd_data[i]>>4;
		f *= 10;
		f += bcd_data[i] & 0x0f;
	}
	if (bcd_len&1) {
		f *= 10;
		f += bcd_data[bcd_len/2]>>4;
	}

	return f;
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
		bcd_data[bcd_len/2] |= (freq%10)<<4;	/* NB: low nibble is left uncleared */
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
