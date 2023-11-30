#include <U8glib.h>
#include <Wire.h>

const int soilMoisturePin = A0;
const int pumpPin = 2;
#define lightSensorPin A1

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NO_ACK);

static int lastSoilMoisture = -1;
static int lastLightSensorValue = -1;

void setup() {
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);
  Serial.begin(9600);
  Wire.begin();
  oled.setFont(u8g_font_helvB10);
}

void loop() {
  int soilMoisture = analogRead(soilMoisturePin);
  int lightSensorValue = analogRead(lightSensorPin);

  if (soilMoisture != lastSoilMoisture || lightSensorValue != lastLightSensorValue) {
    Serial.print("Soil Moisture: ");
    Serial.println(soilMoisture);
    Serial.print("Light Sensor Value: ");
    Serial.println(lightSensorValue);

    if (soilMoisture >= 600) {
      // Soil is dry, start pumping
      updateOled("Watering...");
      digitalWrite(pumpPin, HIGH);

      // Continue pumping until soil moisture is below or equal to 350
      while (soilMoisture > 500) {
        soilMoisture = analogRead(soilMoisturePin);// You can add a delay here if needed
        Serial.println(soilMoisture);
      }

      // Stop pumping
      digitalWrite(pumpPin, LOW);
      updateOled("Very good sun :)");
    } else {
      // Soil is within acceptable moisture levels
      if (lightSensorValue >= 100) {
        updateOled("Not enough sun!");
      } else {
        updateOled("Very good sun :)");
      }
      digitalWrite(pumpPin, LOW); // Ensure the pump is turned off
    }

    lastSoilMoisture = soilMoisture;
    lastLightSensorValue = lightSensorValue;
  }

  delay(1000);
}

void updateOled(String text) {
  oled.firstPage();
  do {
    oled.setFontPosTop();
    oled.drawStr(0, 0, text.c_str());
  } while ( oled.nextPage());
}
