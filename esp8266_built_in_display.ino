
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <U8g2_for_Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;

void setup() {
  Wire.begin(14,12);  
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  u8g2_for_adafruit_gfx.begin(display);                 // connect u8g2 procedures to Adafruit GFX
}

void loop() {  
  display.clearDisplay();                               // clear the graphcis buffer  
  u8g2_for_adafruit_gfx.setFont(u8g2_font_squirrel_tr);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2_for_adafruit_gfx.setFontMode(1);                 // use u8g2 transparent mode (this is default)
  u8g2_for_adafruit_gfx.setFontDirection(0);            // left to right (this is default)
  u8g2_for_adafruit_gfx.setForegroundColor(WHITE);      // apply Adafruit GFX color
  u8g2_for_adafruit_gfx.setCursor(0,15);                // start writing at this position
  u8g2_for_adafruit_gfx.print("Display is working!");
  u8g2_for_adafruit_gfx.setCursor(0,40);                // start writing at this position
  u8g2_for_adafruit_gfx.print("Have fun with it");            // UTF-8 string with german umlaut chars
  u8g2_for_adafruit_gfx.setCursor(0,60);                // start writing at this position
//  if (millis() / 1000 == 1)
//  {
//    count++
//  }
  uint8_t count = millis() / 1000;  
  char *s = "Uptime";
  u8g2_for_adafruit_gfx.print(count); 
  display.display();                                    // make everything visible
  delay(1000);
}
