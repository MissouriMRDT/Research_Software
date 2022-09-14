
#include <SoftwareSerial.h>
#define rxPin 6
#define txPin 7

byte Splashset = 0;

// Set up a new SoftwareSerial object
SoftwareSerial LCD =  SoftwareSerial(rxPin, txPin);

void setup()  {
 // Define pin modes for TX and RX
 pinMode(rxPin, INPUT);
 pinMode(txPin, OUTPUT);

 //Start serial communication at 9600 for debug statements
 Serial.begin(9600); 
 
 // Set the baud rate for the SoftwareSerial object  
 LCD.begin(9600); 
}

void loop() {
  
     /*
     if (Splashset == 0){
        SetScreen(0);
        SetSplash(String("    ROVER BMS V1"), 0, 0);
        Splashset = 1; 
     }
     */
     
     SetBacklight(255, 255, 255);
     SetText(String("Testing Contrast"), 0, 0);
     Serial.println("Testing Contrast");
     SetContrast(100);
     delay(3000); 
     SetContrast(75);
     delay(3000); 
     SetContrast(50);
     delay(3000); 
     SetContrast(25);
     delay(3000); 
     SetContrast(0);
     delay(3000); 
     
     SetText(String("Testing Backlight"), 0, 0);
     Serial.println("Testing Backlight");
     for (int I = 0; I < 255; I++){
     SetBacklight(I, 0, 0);
     }
     for (int J = 0; J < 255; J++){
     SetBacklight(255, J, 0);
     }
     for (int K = 0; K < 255; K++){
     SetBacklight(255, 255, K);
     }
     
     Serial.println("Testing text");
     SetText(String("Testing Text"), 0, 0);
     delay(500);
     SetText(String("Testing Text"), 64, 0);
     delay(500);
     SetText(String("Testing Text"), 20, 0);
     delay(500);
     SetText(String("Testing Text"), 84, 0);
     delay(500);
     SetText(String("Testing Text"), 84, 1);
     delay(500);
     SetText(String("Testing Text"), 84, 2);   
     delay(500);
     SetText(String("Testing Text"), 84, 3);
     delay(500);
     SetText(String("Testing Text"), 84, 4);
     delay(500);
     SetText(String("Testing Text"), 84, 5);
     delay(500);
     SetText(String("Testing Text"), 84, 6);
     delay(500);
     SetText(String("Testing Text"), 84, 7);
     delay(500);
     SetText(String("Testing Text"), 84, 8);
     delay(500);

     SetText(String("Testing Cursor"), 0, 0);
     Serial.println("Testing Cursor");
     SetCursor(0);
     delay(3000);
     SetCursor(1);
     delay(3000);
     SetCursor(2);
     delay(3000);
     SetCursor(3);
     delay(3000);

     SetText(String("Testing Screen"), 0, 0);
     Serial.println("Testing Screen");
     SetScreen(1);
     delay(1000);
     SetScreen(0);
     delay(1000);

     
   
}

void SetContrast(int contrast) {
  /*
  Usable Contrast:
  255-Off
  0-Brightest
  */
 LCD.write(124); //Put LCD into setting mode
 LCD.write(24); //Send contrast command
 LCD.write(contrast);
}

void SetText(String text, int line, int cursorPosition) {
 /*
 Line 1 = 0
 Line 2 = 64
 Line 3 = 20
 Line 4 = 84
 The cursor position is a number from 0-19 
  */
  
 LCD.write(124); //Put LCD into setting mode
 LCD.write(45); //Send clear display character
 LCD.write(254); //Command Character
 LCD.write(128 + line + cursorPosition);
 LCD.print(text);
}

void SetBacklight(int red, int green, int blue) {
  /*
 Use RGB values:
 red, green, blue
 0-Off
 255-Brightest
  */
 LCD.write(124);
 LCD.write(43);
 LCD.write(red);
 LCD.write(green);
 LCD.write(blue);
}

void SetCursor(int cursorFlag){
/*
 Cursor flag:
 0- cursor off, blinking off 
 1- cursor on, blinking off
 2- cursor off, blinking on 
 3- cursor on, blinking on
  */
 if (cursorFlag == 0){
  LCD.write(254); //Send command character
  LCD.write( (1<<3) | (1<<2) ); //Cursor off, blinking box off
 }

 else if (cursorFlag == 1){
  LCD.write(254); //Send command character
  LCD.write( (1<<3) | (1<<2) | (1<<1) ); //Cursor on, blinking box off
 }
 else if (cursorFlag == 2){
  LCD.write(254); //Send command character
  LCD.write( (1<<3) | (1<<2) | (1<<0) ); //Cursor off, blinking box on
 }
  //Control the blink
 else if (cursorFlag == 3){
  LCD.write(254); //Send command character
  LCD.write( (1<<3) | (1<<2) | (1<<1) | (1<<0) ); //Cursor on, blinking box on
 }
}

void SetScreen(int screenFlag){
  /*
 Screen flag:
 0- Screen off
 1- Screen on
  */
 if (screenFlag == 0){
    LCD.write(254); //Send command character
    LCD.write( (1<<3) ); //Display off, cursor off, blink off
    SetBacklight(0, 0, 0);
}

 else if (screenFlag == 1){
    LCD.write(254); //Send command character
    LCD.write( (1<<3) | (1<<2) ); //Display on, cursor off, blink off
    SetBacklight(255, 255, 255);
 }
}


void SetSplash(String text, int line, int cursorPosition) {
 LCD.write(124); //Put LCD into setting mode
 LCD.write(45); //Send clear display character
 LCD.write(254); //Command Character
 LCD.write(128 + line + cursorPosition);
 LCD.print(text);
 delay(1000);
 LCD.write(124); //Put LCD into setting mode
 LCD.write(10);
}
