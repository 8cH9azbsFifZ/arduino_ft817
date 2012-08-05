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

#ifndef FT817_h
#define FT817_h

#include "../SoftwareSerial/SoftwareSerial.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

#define FT817_FREQ_SET 0x01
#define FT817_FREQMODE_READ 0x03
#define FT817_MODE_SET 0x07
#define FT817_MODE_LSB 0x00
#define FT817_MODE_USB 0x01
#define FT817_MODE_CW 0x02
#define FT817_MODE_CWR 0x03
#define FT817_MODE_AM 0x04
#define FT817_MODE_FM 0x08
#define FT817_MODE_DIG 0x0A
#define FT817_MODE_PKT 0x0C
#define FT817_ANY_BYTE 0x00
#define FT817_BAD_READ 0
#define FT817_SPLITMODE_OFF  0x82 // split off
#define FT817_SPLITMODE_ON  0x02 // split on
#define FT817_VFOMODE    0x81 // A or B
#define FT817_OFF  0x8F
#define FT817_ON  0x0F
#define FT817_PTT_OFF  0x88
#define FT817_PTT_ON   0x08
#define FT817_READ_RX_STATE 0xE7
#define FT817_READ_TX_STATE 0x10
#define FT817_READ_TX_STATE2 0xF7
#define FT817_READ_TX_METERS 0xBD // Undocumented
#define FT817_NOPTT 0xFF
#define FT817_SET_CTCSS 0x0A
#define FT817_CTCSS_ON 0x2A
#define FT817_CTCSS_ENCODER_ON 0x4A
#define FT817_CTCSS_OFF 0x8A
#define FT817_SET_CTCSS_FREQ 0x0B
#define FT817_LOCK_OFF 0x80
#define FT817_LOCK_ON 0x00
#define FT817_SERIAL_TIMEOUT_MILLIS 8000
#define COMMAND_DELAY_FREQ_CHANGE 0
#define COMMAND_DELAY 0
class FT817
{
  public:
    FT817();
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
    byte getRxStatus();
    boolean setFreqTest(unsigned long freq);
    void setFreq(long freq);
    unsigned long getFreqMode();
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
    void assignSerial(SoftwareSerial s);
    void begin(int baud);

  private:
    void simpleCommand(int command);
    char readOneChar();
    void fourBytePreamble();
    void threeBytePreamble();
    void sendCATCommandChar(int command);
    void sendCATCommandArray( byte command[], int len);
    unsigned long from_bcd_be(unsigned char const* nybbles, size_t length);
    unsigned char * to_bcd_be( byte bcd_data[], unsigned long freq, unsigned bcd_len);
    byte mode;
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
    void blink();
    void rigComError(char * string);

};

#endif
