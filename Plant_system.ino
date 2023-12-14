#include <U8glib.h>
#include <Wire.h>

const int soilMoisturePin = A0;               // Analog pin för jordfuktighetssensorn
const int pumpPin = 2;                        // Pin för pumpen
#define lightSensorPin A1                      // Analog pin för ljussensorn

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NO_ACK); // Instans av U8glib för OLED-skärmen

static int lastSoilMoisture = -1;             // Variabel för att spara föregående värde av jordfuktighet
static int lastLightSensorValue = -1;          // Variabel för att spara föregående värde av ljussensorn

void setup() {
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);
  Serial.begin(9600);
  Wire.begin();
  oled.setFont(u8g_font_helvB10);             // Använd HelvB10-fonten på OLED-skärmen
}

void loop() {
  int soilMoisture = analogRead(soilMoisturePin);
  int lightSensorValue = analogRead(lightSensorPin);

  if (soilMoisture != lastSoilMoisture || lightSensorValue != lastLightSensorValue) {
    Serial.print("Jordfuktighet: ");
    Serial.println(soilMoisture);
    Serial.print("Ljussensorvärde: ");
    Serial.println(lightSensorValue);

    if (soilMoisture >= 600) {
      // Jord är torr, påbörja bevattning
      updateOled("Bevattning...");
      digitalWrite(pumpPin, HIGH);

      // Fortsätt bevattning tills jordfuktighet är under eller lika med 350
      while (soilMoisture > 500) {
        soilMoisture = analogRead(soilMoisturePin);// Du kan lägga till en fördröjning här om det behövs
        Serial.println(soilMoisture);
      }

      // Stoppa bevattning
      digitalWrite(pumpPin, LOW);
      updateOled("Mycket bra sol :)");
    } else {
      // Jordfuktighet är inom acceptabla nivåer
      if (lightSensorValue >= 100) {
        updateOled("Inte tillräckligt med sol!");
      } else {
        updateOled("Mycket bra sol :)");
      }
      digitalWrite(pumpPin, LOW); // Se till att pumpen är avstängd
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
