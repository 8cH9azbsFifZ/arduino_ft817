/*************************************************************************************************/
/* Configure the display screen  */
#include <LiquidCrystal.h> 

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define LCD_NUM_COL 16
#define LCD_NUM_ROW 2

// define some values used by the panel and buttons
int lcd_key;
int adc_key_in;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define CLICK_NONE         0
#define CLICK_LEFTHOLD     11
#define CLICK_RIGHTHOLD    12
#define CLICK_UPHOLD       10
#define CLICK_DOWNHOLD     9
#define CLICK_LEFTRIGHT    1
#define CLICK_RIGHTLEFT    2
#define CLICK_DOWNUP       3
#define CLICK_UPDOWN       4
#define CLICK_LEFTLEFT     5
#define CLICK_RIGHTRIGHT   6
#define CLICK_UPUP         7
#define CLICK_DOWNDOWN     8

#define N_BUTTONS 10
int buttons[N_BUTTONS];

int detect_multiclick ()
{
   // 3 button sequence for better detection 
  if (buttons[0] == btnRIGHT and buttons[1] == btnRIGHT and buttons[2] == btnRIGHT) { return CLICK_RIGHTHOLD; }
  if (buttons[0] == btnLEFT and buttons[1] == btnLEFT and buttons[2] == btnLEFT) { return CLICK_LEFTHOLD; }
  if (buttons[0] == btnDOWN and buttons[1] == btnDOWN and buttons[2] == btnDOWN) { return CLICK_DOWNHOLD; }
  if (buttons[0] == btnUP and buttons[1] == btnUP and buttons[2] == btnUP) { return CLICK_UPHOLD; }

  // 2 button pushes
  if (buttons[0] == btnRIGHT and buttons[1] == btnLEFT) { return CLICK_LEFTRIGHT; }
  if (buttons[0] == btnLEFT and buttons[1] == btnRIGHT) { return CLICK_RIGHTLEFT; }
  if (buttons[0] == btnDOWN and buttons[1] == btnUP) { return CLICK_UPDOWN; }
  if (buttons[0] == btnUP and buttons[1] == btnDOWN) { return CLICK_DOWNUP; }
  
  // double clicks
  if (buttons[0] == btnLEFT and buttons[1] == btnNONE and buttons[2] == btnLEFT) { return CLICK_LEFTLEFT; }
  if (buttons[0] == btnRIGHT and buttons[1] == btnNONE and buttons[2] == btnRIGHT) { return CLICK_RIGHTRIGHT; }  
  if (buttons[0] == btnDOWN and buttons[1] == btnNONE and buttons[2] == btnDOWN) { return CLICK_DOWNDOWN; }
  if (buttons[0] == btnUP and buttons[1] == btnNONE and buttons[2] == btnUP) { return CLICK_UPUP; }
  
  return CLICK_NONE;
}

/*************************************************************************************************/
/* Configure the FT 817 stuff */
#include <SoftwareSerial.h>
#include "FT817.h" 
#define TRUE 0
#define FALSE 1
typedef struct
{
  FT817 serial;
  int rxPin, txPin, speed; // serial connection parameters for the arduino
  // current status
  long freq;
  char mode[4];
  char smeter[4];
  byte smeterbyte;
} t_rig;
t_rig rig; 


/*************************************************************************************************/
// Bands configuration
#include "t_channels.h"
#include "t_bandplan.h"

int cur_ch;
#define CH_NAME_LEN 40
char cur_ch_name[CH_NAME_LEN];
#define NO_CHANNEL -1
#define CHANNEL_FOUND 0
#define NO_CHANNEL_FOUND -1

// NB: indices as in list above!! 
const int watchdog_frequencies[] = {43932500, 2706500, 14521250}; // FIXME: can be configured
const int num_watchdog_frequencies = 3;//FIXME

/*************************************************************************************************/
#define M_NONE 0
#define M_WATCHDOG 1
#define M_CHANNELS 2
#define M_FREQUENCY 3
#define M_SCANNING 4
byte modus;

/*************************************************************************************************/
// Initialize serial connection
void initialize_ft817 ()
{
  rig.rxPin = 12;// FIXME: can be configured
  rig.txPin = 13;// FIXME: can be configured
  rig.speed = 4800; // FIXME: can be configured
  Serial.begin(rig.speed);
  SoftwareSerial mySerial(rig.rxPin,rig.txPin);
  rig.serial.assignSerial(mySerial);
}

/*************************************************************************************************/
// Initialize the screen
void initialize_screen ()
{
  lcd.begin(LCD_NUM_COL, LCD_NUM_ROW);     // start the library
  lcd.clear();
  lcd.print("FT 817 (DG6FL)"); // print a simple message
}



/*************************************************************************************************/
void read_rig()
{
  rig.serial.begin(rig.speed);
  rig.freq = rig.serial.getFreqMode(rig.mode);
  rig.smeterbyte = rig.serial.getRxStatus(rig.smeter);
} 

/*************************************************************************************************/
void display_frequency_mode_smeter ()
{
  // All of the stuff below only creates a good frequency output - looks chaotic :(
  long freq = rig.freq * 10; //in Hz
  int mhz = freq / 1000000;
  int khz = (freq % 1000000)/1000;
  int hz = freq%1000;
  char ffreq[12];
  sprintf (ffreq, "%03d.%03d.%03d",mhz,khz,hz);

  get_cur_ch_name(rig.freq);
   
  lcd.clear();
  char upper[22];
  char lower[22];
  sprintf(upper, "%s %s",ffreq,rig.mode);
  sprintf(lower, "%s %s",rig.smeter,cur_ch_name);
  lcd.print(upper);
  lcd.setCursor(0,1);
  lcd.print(lower);
}


/*************************************************************************************************/
// return the channel number of the given frequency, -1 if no channel
int freq_to_channel (long freq)
{
  int i;
  for (i = 0; i < nchannels; i++)
  {
    if (freq == channels[i].freq) return i;
  }
  return NO_CHANNEL;
}

/*************************************************************************************************/
// set global variable cur_ch_name to band name or better if possible channel name
void get_cur_ch_name (long freq)
{
  int i;
  for (i = 0; i < nchannels; i++)
  {
    if (freq == channels[i].freq) 
    {
      sprintf (cur_ch_name, "%s", channels[i].name);
      return;
    }
  }
  /*
  for (i = 0; i < nbands; i++) 
  {
    if (bands[i].low <= freq && freq <= bands[i].high) 
    {
      cur_ch_name = bands[i].name;
      return;
    }
  }*/
  sprintf (cur_ch_name, "");
  return;
}




/*************************************************************************************************/
void channels_mode ()
{
  switch (lcd_key)             
  {
    case btnRIGHT: { set_channel (cur_ch+1); break; }
    case btnLEFT:  { set_channel (cur_ch-1); break; }
    case btnUP:    { modus = M_SCANNING; break; }
  }
}


/*************************************************************************************************/
void freq_plus_minus_mode ()
{
  float delta_freq = 10; // 10 == 100 Hz
  switch (lcd_key)             
  {
   case btnRIGHT: { rig.serial.setFreq(rig.freq + delta_freq); break; }
   case btnLEFT:  { rig.serial.setFreq(rig.freq - delta_freq); break; }
   case btnUP:    { rig.serial.setMode(FT817_MODE_USB); break; }
   case btnDOWN:  { rig.serial.setMode(FT817_MODE_CW); break;  }
   }
}

/*************************************************************************************************/
void set_channel (int ch)
{  
  // setup the internal current channel
  if (ch > nchannels - 1)
  {
    ch = 0;
  }
  if (ch < 0)
  {
    ch =  - 1;
  }
  cur_ch = ch;

  // update the rig
  rig.serial.setFreq(channels[cur_ch].freq);
  rig.serial.setFreq(channels[cur_ch].freq); // sometime not set at 1st time FIXME with while
  rig.serial.setMode(channels[cur_ch].mode);
  //if (channels[cur_ch].rpt != 0) { rig.serial.setRPTshift(channels[cur_ch].rpt); }
}

/*************************************************************************************************/
byte signal_detected ()
{
  switch (rig.smeterbyte)
  {
    case FT817_S0:   { return FALSE; break; }
    case FT817_S1:   { return TRUE; break; }
    case FT817_S2:   { return TRUE; break; }
    case FT817_S3:   { return TRUE; break; }
    case FT817_S4:   { return TRUE; break; }
    case FT817_S5:   { return TRUE; break; }
    case FT817_S6:   { return TRUE; break; }
    case FT817_S7:   { return TRUE; break; }
    case FT817_S8:   { return TRUE; break; }
    case FT817_S10:  { return TRUE; break; }
    case FT817_S20:  { return TRUE; break; }
    case FT817_S30:  { return TRUE; break; }
    case FT817_S40:  { return TRUE; break; }
    case FT817_S50:  { return TRUE; break; }
    case FT817_S60:  { return TRUE; break; }
    default:         { return FALSE; break; }
  }
}

/*************************************************************************************************/
#define SCAN_DELAY 30 //ms
// Scan function
int scan_function()
{
  int i;
  for (i = 0; i < nchannels; i++)
  {
    set_channel (i);
    delay(SCAN_DELAY);
    read_rig();
    display_frequency_mode_smeter();
    if (signal_detected() == TRUE)
    {
      modus = M_CHANNELS;
      return CHANNEL_FOUND;
    }
  }
  modus = M_CHANNELS;
  return NO_CHANNEL_FOUND;
}


/*************************************************************************************************/
#define SCAN_DELAY 30 //ms
int watchdog ()
{
  int i;
  for (i = 0; i < num_watchdog_frequencies; i++)
  {
    set_channel (freq_to_channel(watchdog_frequencies[i]));
    delay(SCAN_DELAY);
    read_rig();
    display_frequency_mode_smeter();
    // FIXME: other display for watchdog mode
    if (signal_detected() == TRUE)
    {
      modus = M_NONE;
      return CHANNEL_FOUND;
    }
  }
}

/*************************************************************************************************/
// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
 return btnNONE;  // when all others fail, return this...
}


/*************************************************************************************************/
float distance_between_points (float lat1, float lon1, float lat2, float lon2)
{
  return 0;
}



/*************************************************************************************************/
// Global Setup Routing 
void setup ()
{
  initialize_ft817();
  initialize_screen();
  modus = M_CHANNELS;
  lcd_key = btnNONE;
  adc_key_in = 0;
//ESW repeater  set_channel (99); // FIXME: detect current start channel 
  set_channel (0); // FIXME: detect current start channel 
}



/*************************************************************************************************/
// Main loop
void loop ()
{
  read_rig(); // update the rig structure
  display_frequency_mode_smeter (); // Update the display
  
  // handle the key input
  lcd_key = read_LCD_buttons(); // read into global variable; events can be processed by functions below
  int a = detect_multiclick();
  if (a != CLICK_NONE)
  {
    if (a == CLICK_UPUP) { modus = M_CHANNELS; }
    if (a == CLICK_DOWNDOWN) { modus = M_FREQUENCY; }
    if (a == CLICK_LEFTLEFT) { modus = M_WATCHDOG; }
    if (a == CLICK_LEFTHOLD) { modus = M_SCANNING; }
  }
  
  switch (modus)
  {
    case M_WATCHDOG: { watchdog(); break; }
    case M_CHANNELS: { channels_mode(); break; }
    case M_FREQUENCY: { freq_plus_minus_mode (); break; }
    case M_SCANNING: { scan_function(); break; }
  }
  
}

