/*
	 This file is part of the FT817 Arduino Library.

    The FT817 Arduino Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The FT817 Arduino Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FT817 Arduino Library.  If not, see http://www.gnu.org/licenses/;.	  


	 Contributing Authors:
		Alain De Carolis, WW3WW
		Bruce Gordon Robertson, VE9QRP
		Gerolf Ziegenhain, DG6FL
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
	 char *modename;
    unsigned long l = getFreqMode(modename);
    return mode;
}

boolean FT817::setFreqTest(unsigned long freq) {
    setFreq(freq);
    //delay(100);
	 char *modename;
    unsigned long freqOut = getFreqMode(modename);
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


unsigned long FT817::getFreqMode(char *modename) {
    rigSoftSerial.flush();// not sure why I have to do this.
    //check for data after setFreq
    boolean readValid = true;
    fourBytePreamble();
    sendCATCommandChar(FT817_FREQMODE_READ);
    byte chars[4];
    long timeout = millis();
    long elapsed = 0;
	 sprintf (modename, "");

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
		  switch (mode)
		  {
			  case FT817_MODE_LSB: sprintf (modename, "LSB"); break;
			  case FT817_MODE_USB: sprintf (modename, "USB"); break;
			  case FT817_MODE_CW: sprintf (modename, "CW"); break;
			  case FT817_MODE_CWR: sprintf (modename, "CWR"); break;
			  case FT817_MODE_AM: sprintf (modename, "AM"); break;
			  case FT817_MODE_FM: sprintf (modename, "FM"); break;
			  case FT817_MODE_FMN: sprintf (modename, "FMN"); break;
			  case FT817_MODE_DIG: sprintf (modename, "DIG"); break;
			  case FT817_MODE_PKT: sprintf (modename, "PKT"); break;
			  case FT817_MODE_CW_NARROW: sprintf (modename, "CWN"); break;
			  case FT817_MODE_CWR_NARROW: sprintf (modename, "CWRN"); break;
			  case FT817_MODE_DIG_NARROW: sprintf (modename, "DIGN"); break;
		  }
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

byte FT817::getRxStatus(char *smeter) {
    fourBytePreamble();
    sendCATCommandChar(FT817_READ_RX_STATE);
    byte b = readOneChar();
	 sprintf (smeter, "");
	 switch (b)
	 {
		 case FT817_S0:  sprintf (smeter, "S0 "); break;
		 case FT817_S1:  sprintf (smeter, "S1 "); break;
		 case FT817_S2:  sprintf (smeter, "S2 "); break;
		 case FT817_S3:  sprintf (smeter, "S3 "); break;
		 case FT817_S4:  sprintf (smeter, "S4 "); break;
		 case FT817_S5:  sprintf (smeter, "S5 "); break;
		 case FT817_S6:  sprintf (smeter, "S6 "); break;
		 case FT817_S7:  sprintf (smeter, "S7 "); break;
		 case FT817_S8:  sprintf (smeter, "S8 "); break;
		 case FT817_S9:  sprintf (smeter, "S9 "); break;
		 case FT817_S10: sprintf (smeter, "+10"); break;
		 case FT817_S20: sprintf (smeter, "+20"); break;
		 case FT817_S30: sprintf (smeter, "+30"); break;
		 case FT817_S40: sprintf (smeter, "+40"); break;
		 case FT817_S50: sprintf (smeter, "+50"); break;
		 case FT817_S60: sprintf (smeter, "+60"); break;
		 default: 		  sprintf (smeter, "S0 "); break;
	 }
	 return b;
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


// Set repeater shift
int FT817::ft817_set_rptr_shift (byte shift)
{
	/* Note: this doesn't have effect unless FT817 is in FM mode
	   although the command is accepted in any mode.
	*/
	switch (shift) {
		case RIG_RPT_SHIFT_NONE: { sendCATCommandChar(FT817_NATIVE_CAT_SET_RPT_SHIFT_SIMPLEX); break; }
		case RIG_RPT_SHIFT_MINUS: { sendCATCommandChar(FT817_NATIVE_CAT_SET_RPT_SHIFT_MINUS); break; }
		case RIG_RPT_SHIFT_PLUS: { sendCATCommandChar(FT817_NATIVE_CAT_SET_RPT_SHIFT_PLUS); break; }
	}
	return 0;
}
