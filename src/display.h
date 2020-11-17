#include <SPI.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// images
#include <faceHappy.h>
#include <faceFine.h>
#include <faceSad.h>
#include <faceThirst.h>

#define PAGE_BUTTON D3

/* Object named display, of the class Adafruit_SSD1306 */
Adafruit_SSD1306 display(128, 64, &Wire);

uint8_t s = 0, m = 0, h = 0;

char* lastMood = "happy";
bool page = 0;

struct displayData {
  int temperature;
  int humidity;
  int soil;
};
struct displayData lastDisplayData;

void setupDisplay()   {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); /* Initialize display with address 0x3C */
  display.clearDisplay();  /* Clear display */
  display.setTextSize(1);	/* Select font size of text. Increases with size of argument. */
  display.setTextColor(WHITE);	/* Color of text*/
}

void drawStr(uint8_t x, uint8_t y, char* str){
  display.setCursor(x, y);  /* Set x,y coordinates */
  display.println(str);
}

void showBitmap(char* mood) {
  lastMood = mood;

  if(page == 0) {
    display.clearDisplay();
    Serial.print(F("Mostrando bitmap: "));
    Serial.println(mood);

    if(mood == "happy") {
      display.drawBitmap(0, 0, happyBMP, 128, 64, WHITE);
    } else if (mood == "fine") {
      display.drawBitmap(0, 0, fineBMP, 128, 64, WHITE);
    } else if (mood == "sad") {
      display.drawBitmap(0, 0, sadBMP, 128, 64, WHITE);
    } else if (mood == "thirst") {
      display.drawBitmap(0, 0, thirstBMP, 128, 64, WHITE);
    }

    display.display();
  }
}

void writeOLED(int temperature, int humidity, int soil){
  lastDisplayData.temperature = temperature;
  lastDisplayData.humidity = humidity;
  lastDisplayData.soil = soil;

  // Serial.printf("Novos dados de dispalt: %d , %d , %d\n", temperature, humidity, soil);

  if(page == 1) {
    char strTemperature[50];
    char strHumidity[50];
    char strSoil[50];
    char percent[1];


    sprintf(strTemperature, "Temperatura: %d\xB0C", temperature);
    strcpy(percent, "%");
    sprintf(strHumidity, "Humidade: %d%s", humidity, percent);
    sprintf(strSoil, "Humidade Solo: %d%s", soil, percent);

    time_t now = getNow();

    display.clearDisplay();  /* Clear display */
    drawStr(10, 10, strTemperature);
    drawStr(10, 22, strHumidity);
    drawStr(10, 34, strSoil);
    drawStr(10, 46, ctime(&now));
    display.display();
  }
}

void nextPage() {
  page = page == 0 ? 1 : 0;

  if(page == 0) {
    showBitmap(lastMood);
  } else {
    writeOLED(lastDisplayData.temperature, lastDisplayData.humidity, lastDisplayData.soil);
  }
}

void loopDisplay() {
  int buttonState = 0;
  buttonState = digitalRead(PAGE_BUTTON);
  if (buttonState == 1) {
    Serial.println("Botão da página acionado.");
    nextPage();
    Serial.print("Página atual: ");
    Serial.println(page);
    delay(2000);
  }
}
