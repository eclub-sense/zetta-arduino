

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

String command = "";  
byte command_termination = 0;
byte previous=0;

void setup()   {
  command.reserve(200);
  Serial.begin(19200);
  display.begin();
  display.setContrast(60);
  display.clearDisplay();   // clears the screen and buffer
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.setRotation(2);
  display.setTextSize(2);
  display.println("Arduino  LCD");
  display.display();
  display.setTextSize(0);
  
}

void loop() {
  
}

void serialEvent() {
  if(readCommand(Serial.read())){
    display.clearDisplay();
    display.println(command);
    display.display();
    command="";  
  }  
}

boolean readCommand(byte incoming){  
  boolean finished = false;
  if(incoming==10){
    if(previous==13)finished=true;    
  } else if(incoming!=13){
    command+=(char)incoming;  
  }
  previous=incoming;
  return finished;
}
