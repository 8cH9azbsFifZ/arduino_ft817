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

#ifndef FT817_h
#define FT817_h

#include <SoftwareSerial.h>

// Design note:
// In contrast to hamlib yaesu_cmd_set_t ncmd structure we use only the
// relevant bytes, here and do not list the whole sequence, here. 
// The sequence will contain five bytes, where (except for ptt off) all 
// middle three bytes are 0x00.
// In the definitions below two comments are added for each value:
// <c|i> <1|5>
// 	c 		complete sequence: no additional parameters needed
// 	i		incomplete sequence: additional parameters neccesary
// 	1		value is the 1st byte in sequence
// 	5		value is the 5th byte in sequence
#define FT817_FREQ_SET 0x01								// i5
#define FT817_FREQMODE_READ 0x03							// c5 - get freq & mode status
#define FT817_MODE_SET 0x07								// c5
																	// used in conjunction with
																	// any mode listed below
#define FT817_MODE_LSB 0x00								// c1
#define FT817_MODE_USB 0x01								// c1
#define FT817_MODE_CW 0x02									// c1
#define FT817_MODE_CWR 0x03								// c1
#define FT817_MODE_AM 0x04									// c1
#define FT817_MODE_FM 0x08									// c1
#define FT817_MODE_FMN 0x88								// c1
#define FT817_MODE_DIG 0x0A								// c1
#define FT817_MODE_PKT 0x0C								// c1
#define FT817_MODE_CW_NARROW 0x82						// FIXME: undocumented
#define FT817_MODE_CWR_NARROW 0x83						// FIXME: undocumented
#define FT817_MODE_DIG_NARROW 0x8A						// FIXME: undocumented
#define FT817_ANY_BYTE 0x00								// c2 c3 c4 
																	// empty bytes in middle of sequence
																	// wakeup sequence: 5x any byte
#define FT817_BAD_READ 0
#define FT817_SPLITMODE_OFF 0x82 						// c5
#define FT817_SPLITMODE_ON 0x02 							// c5
#define FT817_VFOMODE    0x81 							// c5 - toggle vfo a/b
#define FT817_OFF  0x8F										// c5
#define FT817_ON  0x0F										// c5
#define FT817_PTT_OFF  0x88								// c5
#define FT817_PTT_ON   0x08								// c5
#define FT817_READ_RX_STATE 0xE7							// c5
#define FT817_READ_TX_STATE 0x10							// FIXME: not official
#define FT817_READ_TX_STATE2 0xF7						// c5
#define FT817_READ_TX_METERS 0xBD 						// FIXME: not in hamlib
																	// 0xBD is undocumented
#define FT817_NOPTT 0xFF
#define FT817_SET_CTCSS 0x0A								// c5 - used in conjunction with below
#define FT817_CTCSS_ON 0x2A								// c1
#define FT817_CTCSS_ENCODER_ON 0x4A						// c1
#define FT817_CTCSS_OFF 0x8A								// c1
#define FT817_SET_DCS_ON 0x0A								// c1 - used with FT817_SET_CTCSS
#define FT817_SET_CTCSS_FREQ 0x0B						// i5
#define FT817_SET_DCS_CODE 0x0C							// i5
#define FT817_LOCK_OFF 0x80								// c5
#define FT817_LOCK_ON 0x00									// c5
#define FT817_CLAR_ON 0x05									// c5
#define FT817_CLAR_OFF 0x85								// c5
#define FT817_SET_CLAR_FREQ 0xF5							// i5
#define FT817_SET_RPT 0x09									// c5 
																	// used in conjunction with rpt shift
#define FT817_RPT_MINUS 0x09								// c1
#define FT817_RPT_PLUS 0x49								// c1
#define FT817_RPT_SIMPLEX 0x89							// c1
#define FT817_RPT_OFFSET_FREQ 0xF9						// i5
#define FT817_CONFIG_READ 0xA7							// FIXME: unofficial
#define FT817_CONFIG_RES 0xBE								// FIXME: DO NOT USE
#define FT817_CONFIG_EEPROM_READ 0xBB					// FIXME: unofficial
#define FT817_CONFIG_EEPROM_WRITE 0xBC					// FIXmE: unofficial

// FT 817 STR_CAL
#define FT817_S0 0x00
#define FT817_S1 0x01
#define FT817_S2 0x02
#define FT817_S3 0x03
#define FT817_S4 0x04
#define FT817_S5 0x05
#define FT817_S6 0x06
#define FT817_S7 0x07
#define FT817_S8 0x08
#define FT817_S9 0x09
#define FT817_S10 0x0A
#define FT817_S20 0x0B
#define FT817_S30 0x0C
#define FT817_S40 0x0D
#define FT817_S50 0x0E
#define FT817_S60 0x0F

#define FT817_SERIAL_TIMEOUT_MILLIS 8000
#define COMMAND_DELAY_FREQ_CHANGE 0
#define COMMAND_DELAY 0

// FIXME
#define FT817_TX_PIN 13
#define FT817_RX_PIN 12

class FT817
{
  public:
    FT817(SoftwareSerial *ser); // Constructor when using SoftwareSerial

    boolean txState();
    boolean txState2();
    boolean txMeters();
    boolean getTXSuccess();
    int getSWR();
    void setPTTOn();
    void setPTTOff();
    void flush();
    void setMode(byte mode);
    void verifiedSetFreq(unsigned long freq);
    byte getMode();
    byte getRxStatus(char *smeter); //FIXME: seems like not all functions are implemented yet
    boolean setFreqTest(unsigned long freq);
    void setFreq(long freq);
    unsigned long getFreqMode(char *modename);
    void setSplitModeOn();
    void setSplitModeOff();
    void setCTCSSEncoderOn();
    void setCTCSSOff();
    void setCTCSSFreq(unsigned int);
    void switchVFO();
    boolean setLockOn();
    boolean setLockOff();
    void off();
    void on();
    void begin(int baud);
	 int setRPTshift (long offset);


  private:
    void simpleCommand(int command);
    char readOneChar();
    void fourBytePreamble();
    void threeBytePreamble();
    void sendCATCommandChar(int command);
    void sendCATCommandArray( byte command[], int len);
    unsigned long from_bcd_be(unsigned char const* nybbles, size_t length);
    unsigned char * to_bcd_be( byte bcd_data[], unsigned long freq, unsigned bcd_len);
    byte mode; // FIXME: global variable
    byte status;
    boolean tx;
    int swr;
    int mod;
    int alc;
    int pwr;
    boolean was_locked;
    unsigned long freq;
    unsigned char foo[4];
    unsigned char * out;
    void rigComError(char * string);
    SoftwareSerial *rigSoftSerial;

};

#endif
