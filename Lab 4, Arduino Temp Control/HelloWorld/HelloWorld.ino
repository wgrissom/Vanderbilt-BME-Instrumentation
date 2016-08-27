/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

const int analogInPin = A1;  // Analog input pin that the potentiometer is attached to
const int buttonPin = A0; // Analog input that the buttons are attached to
const int analogOutPin = 3;

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int buttonValue = 0;
int buttonCounter = 0;
float sensorValueVolts = 0;
float buttonValueVolts = 0;
float sensorValueTemp = 0;
float sensorResistance = 0;


float R0 = 100000;
float T0 = 298;
float beta = 3950;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
   // read the analog in value:
  sensorValue = analogRead(analogInPin);   
  sensorValueVolts = float(sensorValue)/1023*5;
  sensorResistance = R0*(5 - sensorValueVolts)/sensorValueVolts;
  sensorValueTemp = beta/log(sensorResistance/(R0*exp(-beta/T0))) - 273.15;
  
  // just eyeballing it, temp res is about 0.09 deg C
  
  buttonValue = analogRead(buttonPin);
  buttonValueVolts = float(buttonValue)/1023*5;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(sensorValueVolts);
  lcd.setCursor(5,0);
  lcd.print("Volts");
  
//  lcd.setCursor(0,1);
//  if(buttonValue > 72 && buttonValue < 250) buttonCounter++;
//  if(buttonValue > 250 && buttonValue < 410) buttonCounter--;
//  //lcd.print(buttonValue);
//  lcd.print(buttonCounter);

  lcd.setCursor(0,1);
  lcd.print(sensorValueTemp);
  lcd.setCursor(6,1);
  lcd.print("deg C");
  
  outputValue = 200;
  analogWrite(analogOutPin, outputValue); 
  
  delay(1000);
  
  // Up: 144
  // Down: 329
  // Left: 504
  // Right: 0
  // Select: 738
  // Nothing: 1023
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis()/1000);
}

