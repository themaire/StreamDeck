/*
  Base Project / @author 'Stream Cheap' Mini Macro Keyboard / David Madison
  @link partsnotincluded.com/electronics/diy-stream-deck-mini-macro-keyboard

  Added oled screen and support leds for retro illuminate by Nicolas ELIE / Twitter @nico_themaire

  F14 = scène d'intro
  F15 = live scène
  F16 = pause Scène
  F17 = scène d'outro
  F18 = start/stop diffusion
  F19 = start/stop record
  F20 = mute micro/show micro
*/

// ---------------------------------
// OLED Lib
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

// Default wiring : SDA > GPIO2  --- SCK > GPIO3
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//// Icons
#define Icon_width 32
#define Icon_height 32
static const unsigned char mute[128] PROGMEM=
{
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0xc0, 0x00, 
    0x00, 0x03, 0xc0, 0x00, 
    0x00, 0x07, 0xc0, 0x00, 
    0x00, 0x0f, 0xc0, 0x00, 
    0x00, 0x1f, 0xc0, 0x00, 
    0x00, 0x3f, 0xcc, 0x04, 
    0x3f, 0xff, 0xce, 0x0e, 
    0x7f, 0xff, 0xc6, 0x1c, 
    0x7f, 0xff, 0xc7, 0x38, 
    0x7f, 0xff, 0xc3, 0xf0, 
    0x7f, 0xff, 0xc1, 0xe0, 
    0x7f, 0xff, 0xc0, 0xe0, 
    0x7f, 0xff, 0xc1, 0xf0, 
    0x7f, 0xff, 0xc3, 0xb0, 
    0x7f, 0xff, 0xc7, 0x18, 
    0x3f, 0xff, 0xce, 0x1c, 
    0x00, 0x7f, 0xcc, 0x0e, 
    0x00, 0x3f, 0xc0, 0x00, 
    0x00, 0x1f, 0xc0, 0x00, 
    0x00, 0x07, 0xc0, 0x00, 
    0x00, 0x03, 0xc0, 0x00, 
    0x00, 0x01, 0xc0, 0x00, 
    0x00, 0x00, 0x80, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};

static const unsigned char no_mute[128] PROGMEM=
{
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0xc0, 0x00, 
    0x00, 0x03, 0xc0, 0x00, 
    0x00, 0x07, 0xc0, 0x00, 
    0x00, 0x0f, 0xc0, 0x00, 
    0x00, 0x1f, 0xc0, 0x00, 
    0x00, 0x3f, 0xc0, 0x00, 
    0x3f, 0xff, 0xc0, 0x00, 
    0x7f, 0xff, 0xc0, 0x00, 
    0x7f, 0xff, 0xc0, 0x00, 
    0x7f, 0xff, 0xc0, 0x00, 
    0x7f, 0xff, 0xc0, 0x00, 
    0x7f, 0xff, 0xc0, 0x00, 
    0x7f, 0xff, 0xc0, 0x00, 
    0x7f, 0xff, 0xc0, 0x00, 
    0x7f, 0xff, 0xc0, 0x00, 
    0x3f, 0xff, 0xc0, 0x00, 
    0x00, 0x7f, 0xc0, 0x00, 
    0x00, 0x3f, 0xc0, 0x00, 
    0x00, 0x1f, 0xc0, 0x00, 
    0x00, 0x07, 0xc0, 0x00, 
    0x00, 0x03, 0xc0, 0x00, 
    0x00, 0x01, 0xc0, 0x00, 
    0x00, 0x00, 0x80, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};

static const unsigned char rec[128] PROGMEM=
{
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x07, 0xf0, 0x00, 
    0x00, 0x3f, 0xfc, 0x00, 
    0x00, 0x7f, 0xfe, 0x00, 
    0x01, 0xff, 0xff, 0x80, 
    0x03, 0xff, 0xff, 0xc0, 
    0x03, 0xff, 0xff, 0xc0, 
    0x07, 0xff, 0xff, 0xe0, 
    0x0f, 0xff, 0xff, 0xf0, 
    0x0f, 0xff, 0xff, 0xf0, 
    0x0f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x0f, 0xff, 0xff, 0xf0, 
    0x0f, 0xff, 0xff, 0xf0, 
    0x07, 0xff, 0xff, 0xe0, 
    0x03, 0xff, 0xff, 0xc0, 
    0x03, 0xff, 0xff, 0xc0, 
    0x01, 0xff, 0xff, 0x80, 
    0x00, 0x7f, 0xfe, 0x00, 
    0x00, 0x3f, 0xfc, 0x00, 
    0x00, 0x0f, 0xf0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};

static const unsigned char swico[128] PROGMEM=
{
    0xff, 0xff
};


// UVLED GPIO definition
const uint8_t UVLED_1 = 5;
const uint8_t UVLED_2 = 6;
const uint8_t UVLED_3 = 9;
const uint8_t UVLED_4 = 10;

class uvLed {
  public:
    uvLed(uint8_t pin){
      pinLed = pin;
      init();
    }

    void init() {
      pinMode(pinLed, OUTPUT);
      digitalWrite(pinLed, LOW);
    }

    void on() {
      digitalWrite(pinLed, HIGH);
    }

    void analOn(int duty) {
      analogWrite(pinLed, duty);
    }

    void off() {
      digitalWrite(pinLed, LOW);
    }

  private:
    uint8_t pinLed;
};

//UV leds objects array
uvLed uvLeds[] = {
  {UVLED_1},
  {UVLED_2},
  {UVLED_3},
  {UVLED_4}
};

const uint8_t NumUvLeds = sizeof(uvLeds) / sizeof(uvLed); 

#include "Keyboard.h"
// Key definitions
const uint8_t BUTTON_KEY1 = KEY_F14;
const uint8_t BUTTON_KEY2 = KEY_F15;
const uint8_t BUTTON_KEY3 = KEY_F16;
const uint8_t BUTTON_KEY4 = KEY_F17;
const uint8_t BUTTON_KEY5 = KEY_LEFT_ALT;
const uint8_t BUTTON_TAB = KEY_TAB;
const uint8_t BUTTON_KEY6 = KEY_F18;
const uint8_t BUTTON_KEY7 = KEY_F19;
const uint8_t BUTTON_KEY8 = KEY_F20;

// Btn GPIO definitions
const uint8_t BUTTON_PIN1 = 16;
const uint8_t BUTTON_PIN2 = 14;
const uint8_t BUTTON_PIN3 = 4;
const uint8_t BUTTON_PIN4 = A3;
const uint8_t BUTTON_PIN5 = A2;
const uint8_t BUTTON_PIN6 = 7;
const uint8_t BUTTON_PIN7 = 8;
const uint8_t BUTTON_PIN8 = A1;
const uint8_t BUTTON_LEDUV = 15;
uint8_t btnLedUVState = 0;
const uint8_t LED_BTN8 = A0;

const long debounceTime = 130;
unsigned long lastPressed;
uint8_t cptBtn = 0;

// Button helper class for handling press/release and debouncing
class button {
  public:
    const char key;
    const uint8_t pin;
    bool activated = false;
    uint8_t mode = 0;
    bool tabed = false;

    button(uint8_t k, uint8_t p) : key(k), pin(p) {}

    uint8_t setled(void) { // Prepare the led associated
      if (pin == BUTTON_PIN8) { // If pin is the mute btn
        // Create LED. Active low.
        const uint8_t pinled = LED_BTN8 ;
        pinMode(pinled, OUTPUT);
        digitalWrite(pinled, LOW);
        return pinled;
      } else {
        return 0;
      }
    }
    const uint8_t buttonled = setled();

    void clearBlank() {
      display.clearDisplay();
      display.display();
      }

    void printText(String myinputstring, int8_t x=0, int8_t y=0, int8_t siZe=2) {
      display.clearDisplay();
    
      display.setTextSize(siZe); // Draw X-scale text
      display.setTextColor(WHITE);
      display.setCursor(x, y);
      display.println(myinputstring);
      display.display(); // Show expected text
    }

    void press(boolean state) {
      if (state == pressed || (millis() - lastPressed  <= debounceTime)) {
        return; // Nothing to see here, folks
      }
      lastPressed = millis();
      
      state ? Keyboard.press(key) : Keyboard.release(key);
      pressed = state;

      if (pin == BUTTON_PIN5 and pressed) {
        if (!tabed) {
          Keyboard.press(BUTTON_TAB);
          delay(50);
          Keyboard.release(BUTTON_TAB);
          tabed = true;
        }
        tabed = false;
        Serial.println("ALT");
      }

      cptBtn += 1;

      if (pressed == 0){

        if (pin == BUTTON_PIN1) {
          display.stopscroll();
          printText("  Intro",0,10);
          display.display();
        } else if (pin == BUTTON_PIN2) {
          display.stopscroll();
          printText("Live scene",0,10);
          display.display();
        } else if (pin == BUTTON_PIN3) {
          display.stopscroll();
          printText("  Pause",0,10);
          display.display();
        } else if (pin == BUTTON_PIN4) {
          display.stopscroll();
          printText("  Outro",0,10);
          display.display();
        } else if (pin == BUTTON_PIN5) {
          if (activated == false) {
            printText("  ALT-Tab ",0,10);
            display.display();
          } 
        } else if (pin == BUTTON_PIN6) {
          // DIFFUSION
          display.stopscroll();
          if (activated == false) {
            activated = true;
            printText("Diffusion",0,10);
            display.display();
          } else if (activated == true and cptBtn == 2){
            activated = false;
            display.stopscroll();
            printText("No diff.",0,10);
            display.display();
          }
        } else if (pin == BUTTON_PIN7) {
          // RECORDING
          if (activated == false) {
            activated = true;
            printText("Record",40,10);
            display.drawBitmap(0, 0, rec, Icon_width, Icon_height, 1);
            display.display();
          } else if (activated == true and cptBtn == 2){
            activated = false;
            display.stopscroll();
            printText("  Stop rec",0,10);
            display.fillRect(0,9,17,17,WHITE);
            display.display();
          }
        } else if (pin == BUTTON_PIN8) {
          // MUTING
          if (activated == false) {
            activated = true;
            digitalWrite(buttonled, HIGH);
            printText("Mute",52,10);
            display.drawBitmap(0, 0, mute, Icon_width, Icon_height, 1);
            display.startscrollright(0x00, 0x0F);
            display.display();
          } else if (activated == true and cptBtn == 2){
            activated = false;
            digitalWrite(buttonled, LOW);
            display.stopscroll();
            printText("On AIR",42,10);
            display.drawBitmap(0, 0, no_mute, Icon_width, Icon_height, 1);
            display.display();
          }
        } else {
          clearBlank();
          // Draw pin n° with the simple screen function
          String charpin;
          charpin = String(pin) + " - " + String(buttonled) + "\n" + String(activated) + "- cptBtn: " + String(cptBtn);
          printText(charpin);
        }
        
        cptBtn = 0;
      }

    }

    void update() {
      press(!digitalRead(pin));
    }

  private:
    const long debounceTime = 30;
    unsigned long lastPressed;
    boolean pressed = 0;
    uint8_t cptBtn = 0;
};

// Objects creations
// Button objects, organized in array
button buttons[] = {
  {BUTTON_KEY1, BUTTON_PIN1},
  {BUTTON_KEY2, BUTTON_PIN2},
  {BUTTON_KEY3, BUTTON_PIN3},
  {BUTTON_KEY4, BUTTON_PIN4},
  {BUTTON_KEY5, BUTTON_PIN5},
  {BUTTON_KEY6, BUTTON_PIN6},
  {BUTTON_KEY7, BUTTON_PIN7},
  {BUTTON_KEY8, BUTTON_PIN8},
};

const uint8_t NumButtons = sizeof(buttons) / sizeof(button);

// --------------------------------- End keyboard definition

void failsafe() {
  for (;;) {} // Just going to hang out here for awhile :D
}

void ledsOn(uint8_t duty = 0) {
  for (int i = 0; i < NumUvLeds; i++) {
    uvLeds[i].analOn(duty);
  }
}

void ledsOff() {
  for (int i = 0; i < NumUvLeds; i++) {
    uvLeds[i].off();
  }
}

void setup() {
  //------ Startup SCREEN
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  // Clear the buffer
  display.clearDisplay();
  display.display();

  //------ Startup buttons
  // Safety check. Ground pin #1 (RX) to cancel keyboard inputs.
  pinMode(1, INPUT_PULLUP);
  if (!digitalRead(1)) {
    failsafe();
  }
  // Set pinmode for all button in the array
  for (int i = 0; i < NumButtons; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
}

uint8_t ledMode = 0;

bool light = false;

int cptLight = 0;
bool inverted = false;
uint8_t increment;

bool turn = false;
bool turnOne = false;
uint8_t cptTurn = 0;

void changeMode(void) {
  if (millis() - lastPressed  <= 600) {
    return; // Nothing to see here, folks
    Serial.println("crotte... merde!!!");
  }
  Serial.println("milis - lastPressed");
  Serial.println(millis() - lastPressed);
  lastPressed = millis();

  switch(ledMode) {
    case 0:
      light = false;
      turn = false;
      turnOne = false;
      ledsOff();
      ledMode++;
      Serial.println("Case 0");
      Serial.println("light false : " + String(light));
      Serial.println("turn false : " + String(turn));
      Serial.println("turnOne false : " + String(turnOne));
      break;
    case 1:
      ledsOn(70);
      ledMode++;
      break;
    case 2:
      ledsOn(170);
      ledMode++;
      break;
    case 3:
      ledsOn(254);
      ledMode++;
      break;
    case 4:
      light = true;
      increment = 15;
      ledMode++;
      break;
    case 5:
      turn = true;
      increment = 30;
      ledMode++;
      break;
    case 6:
      turnOne = true;
      ledMode = 0;
      break;
  }
  
  delay(20);
}

void loop() {
  for (int i = 0; i < NumButtons; i++) {
    buttons[i].update();
  }
  
  if (light) {
    if (turn == false) {
      if (inverted == false) {
        if (cptLight + increment > 255) {
          inverted = true;
          cptLight = 255;
          delay(20);
        } else {
          cptLight = cptLight + increment;
        }
      } else if (inverted == true){
        if (cptLight - increment < 0) {
          inverted = false;
          cptLight = 0;
          delay(200);
        } else {
          cptLight = cptLight - increment;
        }
      }
      for (int i = 0; i < NumUvLeds; i++) {
        uvLeds[i].analOn(cptLight);
      }

      //Serial.println('ca turn pas');
    } else { // Turn
      if (cptLight + increment > 260) {
        //inverted = true;
        Serial.println("raz cptlight car :");
        Serial.println(cptLight + increment);
        cptLight = 0;
      } else if (cptLight + increment > 255 and cptLight + increment < 260) {
        cptLight = 255;
        Serial.println("a fond");
      } else {
        cptLight = cptLight + increment;
      }
      if (turnOne) {
        if (cptTurn >= 1 and cptTurn <= 3) {
          uvLeds[cptTurn - 1].off();
        }
      }

      uvLeds[cptTurn].analOn(cptLight);

      if (cptTurn == 3) {
        cptTurn = 0;
      } else {
        cptTurn++;
      }
      Serial.println("ca turn ...");
      Serial.println(cptLight);
      Serial.println("...");
    }
  }

  //btnLedUVState = digitalRead(BUTTON_LEDUV);
  if (digitalRead(BUTTON_LEDUV)) {
    changeMode();
    Serial.println("ledMode");
    Serial.println(ledMode);
    Serial.println("...");
  }
  delay(100);
}
