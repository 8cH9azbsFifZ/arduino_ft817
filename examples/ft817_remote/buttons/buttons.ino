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


/*************************************************************************************************/
// Initialize the screen
void initialize_screen ()
{
  lcd.begin(LCD_NUM_COL, LCD_NUM_ROW);     // start the library
  lcd.clear();
  lcd.print("FT 817 (DG6FL)"); // print a simple message
}


/*************************************************************************************************/
// Global Setup Routing 
void setup (){
  initialize_screen();
  lcd_key = btnNONE;
  adc_key_in = 0;
}

#define N_BUTTONS 10
int buttons[N_BUTTONS];

void update_buttons(int number)
{
  int i;
  for (i = N_BUTTONS-1; i >= 1; i--)
 {
   buttons[i] = buttons[i-1];
 } 
 buttons[0] = number;
}
void debug_multiclick()
{
    char bb[N_BUTTONS+1];
  sprintf (bb, "%d%d%d%d%d%d%d%d", 
  buttons[0],
  buttons[1],
  buttons[2],
  buttons[3],
  buttons[4],
  buttons[5],
  buttons[6],
  buttons[7]
  );
  lcd.print(bb);
}

int detect_multiclick ()
{
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

void loop ()
{
  lcd.clear();
  lcd.print("test");
  lcd_key = read_LCD_buttons();  
  update_buttons(lcd_key);
  lcd.setCursor(0,0);
  debug_multiclick();
  int a = detect_multiclick();
  if (a!=CLICK_NONE)
  {
    lcd.setCursor(0,1);
    lcd.print(a);
    delay(2000);
  }
  
  
switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnRIGHT: { lcd.setCursor(0,1); lcd.print("right"); break; }
  }
  delay(50);
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


