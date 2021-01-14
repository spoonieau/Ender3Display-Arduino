/*
 * Ender 3 pro display (12864ZW-10) Arduino demo
 * 
 * Dependencies 
 * U8g2lib https://github.com/olikraus/u8g2
 * 
 *    hook up pinout
 *        EXP3
 *    ╔═══     ═══╗
 *    ║ 1 2 3 4 5 ║
 *    ║ 6 7 8 9 10║
 *    ╚═══════════╝
 *
 *
 * EXP3 Pins       Arduino Uno Pins
 *     1              Ground
 *     2              D10 (CS)
 *     3              D3  (Enc B)
 *     4              D2  (Enc A)
 *     5              D9  (Buzzer)
 *     6              5+
 *     7              D11 (Data)
 *     8              D13 (Clk)
 *     9              D8  (Reset)
 *     10             D4  (PushBtn)
 * 
 */


#include <U8g2lib.h>
#include <SPI.h>

//U8g2lib Display pin assigment and setup
const short PIN_Clk = 13;
const short PIN_Data = 11;
const short PIN_CS = 10;
const short PIN_Reset = 8;

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, PIN_Clk, PIN_Data, PIN_CS, PIN_Reset);

//Buzzer pin assigment and setup
const short PIN_Buzzer = 9;

//Rotary Encoder pin assigment and setup
int PIN_A = 2;
int PIN_B =3;
int PIN_PushBTN = 4;
int ENC_Pos = 0;
int VAL_Rotary;
int VAL_LastRotary;

void setup() 
{
  // put your setup code here, to run once:
pinMode (PIN_A, INPUT_PULLUP);
pinMode (PIN_B, INPUT_PULLUP);
pinMode (PIN_PushBTN, INPUT_PULLUP); 
pinMode (PIN_Buzzer, OUTPUT); 
attachInterrupt(0, Do_Rotary, CHANGE);
u8g2.begin();
}

void loop() 
{

 // If Rotary Encoder push button is pressed
 int btn = digitalRead(PIN_PushBTN);
 if (btn == LOW)
 {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0,10,"Push Button, BUZZ");
  u8g2.sendBuffer();
  Do_Buzz();
 }

 //Rotary Encoder turned to the right (ClockWise)
 if (VAL_Rotary>VAL_LastRotary)
 {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0,10,"ClockWise");
  u8g2.sendBuffer();
 }

 //Rotary Encoder turned to the left (CounterClockWise)
 if (VAL_Rotary<VAL_LastRotary)
 {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0,10,"CounterClockWise");
  u8g2.sendBuffer();
 }

 // Update last position 
 VAL_LastRotary = VAL_Rotary;
 delay(250);
}

// Functions 

// Buzzer function, make noise.
void Do_Buzz()
{
  tone(PIN_Buzzer, 1000);
  delay(1000);
  noTone(PIN_Buzzer);
  u8g2.clearBuffer();
}

// Rotary Encoder, Keep track of encoder position.
void Do_Rotary()
{
  if (digitalRead(PIN_A) == digitalRead(PIN_B))
  {
    ENC_Pos++;
  }
  else
  {
    ENC_Pos--;
  }
  VAL_Rotary = ENC_Pos/2.5; 
  
}
