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
 
 Author: Gerolf Ziegenhain, DG6FL
 
 */

#define LONG_MAX 1000000000
#define TRUE 0
#define FALSE 1
#define INIT_WAIT_TIME 1000
#include <SoftwareSerial.h>
#include <HardwareSerial.h>


/*************************************************************************************************/
/* Configure the display screen  */
#define LCD_NUM_COL 22//16
#define LCD_NUM_ROW 4//2

#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

uint8_t lcd_key;


/*************************************************************************************************/
/* Configure the FT 817 stuff */
#include <FT817.h> 
#define SMETER_LEN 4
#define FREQ_LEN 12 // length of frequency display
#define MODE_LEN 5
typedef struct
{
  // current status
  long freq;
  char mode[MODE_LEN];
  char smeter[SMETER_LEN];
  byte smeterbyte;
} 
t_status;
t_status rig; 

#define FT817_SPEED 38400
FT817 ft817(&Serial1);


void initialize_ft817 ()
{
  lcd.setCursor(0,1);
  lcd.print("Init FT817");
  ft817.begin(FT817_SPEED);
  delay(INIT_WAIT_TIME);
  read_rig();  
}

/*
  SD card read/write
 
 This example shows how to read and write data to and from an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10
 	 
 */
 
#include <SD.h>

File myFile;

void init_sd()
{
  lcd.setCursor(0,1);
  lcd.print("Init SD Card");

  pinMode(53, OUTPUT);
  
  if (!SD.begin(53)) {
    lcd.setCursor(0,1);
    lcd.print("initialization failed!");
    return;
  }
  lcd.setCursor(0,1);
  lcd.println("initialization done.");
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
}

void sd_write()
{
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
	// close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void sd_read()
{
  // re-open the file for reading:
  myFile = SD.open("ch.txt");
  if (myFile) {
    Serial.println("ch.txt:");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
  	// if the file didn't open, print an error:
    Serial.println("error opening ch.txt");
  }
}



/*************************************************************************************************/
// Bands configuration
#include "t_channels.h"
#include "t_repeaters.h"
#include "t_bandplan.h"

int cur_ch;
#define CH_NAME_LEN 20
#define NO_CHANNEL -1
#define CHANNEL_FOUND 0
#define NO_CHANNEL_FOUND -1

// NB: indices as in list above!! 
const long watchdog_frequencies[] = {
  43340000, 43932500, 2706500, 14521250}; // FIXME: can be configured
const int num_watchdog_frequencies = 4;//FIXME

/*************************************************************************************************/
#define M_NONE 0
#define M_WATCHDOG 1
#define M_CHANNELS 2
#define M_FREQUENCY 3
#define M_SCANNING 4
byte modus;

#include <math.h>
typedef struct
{
  float lat;
  float lon;
  char qth[7];
  int dist; // distance to repeater (km)
} t_position;
t_position curpos;
float mz_lat = 	50.03333, mz_lon = 8.28438;

/*************************************************************************************************/

void wgs_to_maidenhead (float lat, float lon, char *locator)
{
  char *m = locator;
  lon += 180.;
  lat += 90.;

  m[0] = 0x41+(int)(lon/20.);
  m[1] = 0x41+(int)(lat/10.);
  m[2] = 0x30+(int)((fmod(lon,20.))/2.);
  m[3] = 0x30+(int)((fmod(lat,10.))/1.);
  m[4] = 0x61+(int)((lon - ((int)(lon/2.)*2.)) / (5./60.));
  m[5] = 0x61+(int)((lat - ((int)(lat/1.)*1.)) / (2.5/60.));;
}

/*************************************************************************************************/

void maidenhead_to_wgs (float *lat, float *lon, char *locator)
{
  *lon -= 180.;
  *lat -= 90.;
  char *m = locator;

  *lon += (m[0]-0x41)*20.;
  *lat += (m[1]-0x41)*10.;
  *lon += (m[2]-0x30)*2.;
  *lat += (m[3]-0x30)*1.;
  *lat += (m[4]-0x61)*(5./60.);
  *lon += (m[5]-0x61)*(2.5/60.);
}

/*************************************************************************************************/

float calculate_distance_wgs84 (float lat1, float lon1, float lat2, float lon2)
{
  // NB: accuracy: (a) formula (b) 6letter locator: +-32km
  float r = 6378.; //km
  float fac = 3.1415/180.;
  float a1 = lat1*fac,
	b1 = lon1*fac,
	a2 = lat2*fac,
	b2 = lon2*fac;
  float dd = 
	  acos(cos(a1)*cos(b1)*cos(a2)*cos(b2) 
		+ cos(a1)*sin(b1)*cos(a2)*sin(b2) 
		+ sin(a1)*sin(a2)) * r;
  return dd;
}


/*************************************************************************************************/

#include <Adafruit_GPS.h>
#define GPS_SPEED 9600
Adafruit_GPS GPS(&Serial2);

uint32_t timer;

#define PMTK_SET_NMEA_UPDATE_01HZ  "$PMTK220,10000*2F" 

void initialize_gps ()
{

  lcd.setCursor(0,1);
  lcd.print("Init GPS");

  GPS.begin(GPS_SPEED);

  // initialize gps module
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  //GPS.sendCommand(PMTK_SET_NMEA_UPDATE_01HZ);
  //GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  delay(INIT_WAIT_TIME);
  Serial2.println(PMTK_Q_RELEASE);
  // 1st signal
  timer = millis();

  read_gps(); 

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
void read_rig ()
{
  do // rig frequency may initially be 0
  {
    rig.freq = ft817.getFreqMode(rig.mode);
    rig.smeterbyte = ft817.getRxStatus(rig.smeter);
  } 
  while (rig.freq == 0); 
} 


/*************************************************************************************************/

void display_frequency ()
{
  // Frequency
  // All of the stuff below only creates a good frequency output - looks chaotic :(
  long freq = rig.freq * 10; //in Hz
  int mhz = freq / 1000000;
  int khz = (freq % 1000000)/1000;
  int hz = freq % 1000;

  lcd.setCursor(0,0);
  if (mhz < 100) { lcd.print("0"); }
  if (mhz < 10) { lcd.print("0"); }
  lcd.print(mhz);
  lcd.print(".");  
  if (khz < 100) { lcd.print("0"); }
  if (khz < 10) { lcd.print("0"); }
  lcd.print(khz);
  lcd.print(".");    
  if (hz < 100) { lcd.print("0"); }
  if (hz < 10) { lcd.print("0"); }
  lcd.print(hz);
  lcd.print(" ");
  lcd.print(rig.mode);
}

void display_channel ()
{
  int i = get_cur_ch_name(rig.freq);
  int j = get_cur_band_name(rig.freq);
  lcd.setCursor(0,1); 
  if (i >= 0) { lcd.print(channels[i].name); }
  else
  { 
    if (j >= 0) { lcd.print(bands[j].name); }
    else { lcd.print("No bandplan        "); }
  }
}

void display_smeter ()
{
  lcd.setCursor(0,2); 
  lcd.print(rig.smeter);
}

void update_curpos ()
{
  if (GPS.fix) { curpos.lat = (float)(GPS.lat); curpos.lon = (float)(GPS.lon); }
  else { curpos.lat =mz_lat;curpos.lon= mz_lon; } //FIXME
  wgs_to_maidenhead(curpos.lat,curpos.lon,curpos.qth);
  char *qth2 = "JO21da";// FIXME: repeater position
  float lat2,lon2;
  maidenhead_to_wgs (&lat2,&lon2,qth2);
  curpos.dist = (int)calculate_distance_wgs84 (curpos.lat,curpos.lon,lat2,lon2);
}

void display_time()
{  
  // time
  lcd.setCursor(0,3); 
  if (GPS.hour < 10) { lcd.print("0"); }
  lcd.print(GPS.hour);
  lcd.print(":");
  if (GPS.minute < 10) { lcd.print("0"); }
  lcd.print(GPS.minute);
  lcd.print(" ");
  
  // qth
  lcd.print(curpos.qth);
  lcd.print(" ");
  
  // distance to repeater
  if (curpos.dist < 1000) {
    if (curpos.dist < 100) { lcd.print("0"); }
    if (curpos.dist < 10) { lcd.print("0"); }
    lcd.print(curpos.dist);
    lcd.print("km");
  }
}
void display_frequency_mode_smeter ()
{
  lcd.clear();
  display_frequency();
  display_channel();
  display_smeter();
  display_time();
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
int get_cur_ch_name (long freq)
{
  int i;
  for (i = 0; i < nchannels; i++)
  {
    if (freq == channels[i].freq) { return i; }
  }
  return -1;
}

int get_cur_band_name (long freq)
{
  int i;
  for (i = 0; i < nbands; i++)
  {
    if (bands[i].low <= freq && freq <= bands[i].high) { return i; }
  }
  return -1;
}

/*************************************************************************************************/
void channels_mode ()
{
  if (lcd_key & BUTTON_RIGHT)  { 
    set_channel (cur_ch+1); 
  }
  if (lcd_key & BUTTON_LEFT)   { 
    set_channel (cur_ch-1); 
  }
  if (lcd_key & BUTTON_UP)     { 
    modus = M_SCANNING; 
  }
}


/*************************************************************************************************/
void freq_plus_minus_mode ()
{
  float delta_freq = 10; // 10 == 100 Hz

  // TBD
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
    ch =  nchannels-1;
  }
  cur_ch = ch;

  // update the rig 
  long f = channels[cur_ch].freq;
  if (f < 0) { f = -f; }
  
  do // it may happen, that the frequency is not set correctly during the 1st attempt.
  {
    ft817.setFreq(f);
    read_rig();
  } 
  while (rig.freq != f);

  ft817.setMode(channels[cur_ch].mode);
  if (channels[cur_ch].freq < 0) // negative freq => repeater 
  {     
    // FIXME 
    if (rig.freq > 20000000) { ft817.setRPTshift(rpt70cm); }
    else { ft817.setRPTshift(rpt2m); }
  }
}

/*************************************************************************************************/
int find_nearest_channel ()
{

  int i;
  int nearest_channel = 0;
  long delta_freq_min = LONG_MAX;
  for (i = 0; i < nchannels; i++)
  {

    long delta_freq = channels[i].freq - rig.freq;

    delay(10);
    if (delta_freq < 0) { 
      delta_freq = -delta_freq; 
    }
    if (delta_freq < delta_freq_min)
    {
      nearest_channel = i;
      delta_freq_min = delta_freq;
    }
  }


  return nearest_channel;
}

/*************************************************************************************************/
byte signal_detected ()
{
  switch (rig.smeterbyte)
  {
  case FT817_S0:   
    { 
      return FALSE; 
      break; 
    }
  case FT817_S1:   
    { 
      return TRUE; 
      break; 
    }
  case FT817_S2:   
    { 
      return TRUE; 
      break; 
    }
  case FT817_S3:   
    { 
      return TRUE; 
      break; 
    }
  case FT817_S4:   
    { 
      return TRUE; 
      break; 
    }
  case FT817_S5:   
    { 
      return TRUE; 
      break; 
    }
  case FT817_S6:   
    { 
      return TRUE; 
      break; 
    }
  case FT817_S7:   
    { 
      return TRUE; 
      break; 
    }
  case FT817_S8:   
    { 
      return TRUE; 
      break; 
    }
  case FT817_S10:  
    { 
      return TRUE; 
      break; 
    }
  case FT817_S20:  
    { 
      return TRUE; 
      break; 
    }
  case FT817_S30:  
    { 
      return TRUE; 
      break; 
    }
  case FT817_S40:  
    { 
      return TRUE; 
      break; 
    }
  case FT817_S50:  
    { 
      return TRUE; 
      break; 
    }
  case FT817_S60:  
    { 
      return TRUE; 
      break; 
    }
  default:         
    { 
      return FALSE; 
      break; 
    }
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
  long oldfreq = rig.freq;
  lcd.setCursor(0,0);
  lcd.print ("Watchdog            ");
  lcd.setCursor(0,1);
  lcd.print ("                    ");
  lcd.setCursor(0,2);
  lcd.print ("                    ");
  for (i = 0; i < num_watchdog_frequencies; i++)
  {
    ft817.setFreq(watchdog_frequencies[i]);
    //set_channel (freq_to_channel(watchdog_frequencies[i]));
    delay(SCAN_DELAY);
    read_rig();

    // FIXME: other display for watchdog mode
    if (signal_detected() == TRUE)
    {
      lcd.setCursor(0,1);
      lcd.print ("Signal detected!");
      display_smeter();
      //modus = M_NONE;
      return CHANNEL_FOUND;
    }
  }
  ft817.setFreq(oldfreq);
  read_rig();
  display_frequency();
  display_channel();
  return 1;
}


/*************************************************************************************************/
#define TIMER 80000 //timer in ms
#define TIMER_GPS 2000
#define TIMER_SMETER 500
#define TIMER_FREQUENCY 4500
#define TIMER_WATCHDOG 40000

void read_gps ()
{
  char c = GPS.read();

  if (GPS.newNMEAreceived()) {
   
    if (!GPS.parse(GPS.lastNMEA())) 
      return; 
  }
  if (timer > millis()) timer = millis();
}

/*************************************************************************************************/
// Global Setup Routing 
void setup ()
{
  Serial.begin(9600);
  initialize_screen();

  initialize_gps();
  initialize_ft817();

Serial.print(channels[22].name);

  modus = M_CHANNELS;
  cur_ch = find_nearest_channel();
  //cur_ch = 0;
  display_frequency_mode_smeter ();
}



/*************************************************************************************************/
// Main loop
void loop ()
{    
  int update_display = 0;
  read_gps();
  read_rig();
  
  uint32_t curtimer = millis() - timer;
  if (curtimer > TIMER) {
    timer = millis(); // reset the timer
  }
  if (curtimer > TIMER_GPS)  {  update_curpos();  display_time();  } //show_gps();}
  if (curtimer > TIMER_SMETER)  {    display_smeter();  }
  if (curtimer > TIMER_FREQUENCY)  {    display_frequency(); display_channel(); }
  //if (curtimer > TIMER_WATCHDOG)  {  watchdog(); timer = millis(); }


  //lcd_key = lcd.readButtons();
  //Serial.print ("Read key: ");
  //Serial.print (lcd_key);
  //Serial.print ("\n");
  //modus = M_WATCHDOG;
  switch (modus)
  {
  case M_WATCHDOG: 
    { 
      //watchdog(); 
      break; 
    }
  case M_CHANNELS: 
    { 
      //channels_mode(); 
      break; 
    }
  case M_FREQUENCY: 
    { 
      //freq_plus_minus_mode (); 
      break; 
    }
  case M_SCANNING: 
    { 
      //scan_function(); 
      break; 
    }
  }
}


