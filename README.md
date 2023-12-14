# Växtvårdssystem

## Översikt
Detta Arduino-projekt implementerar ett intelligent bevattningssystem för växter med hjälp av jordfuktighetssensorer och ljussensorer. Det kontrollerar jordfuktighetsnivån och ljusförhållandena för att avgöra om växten behöver vattnas.

## Komponenter
- Arduino-kort
- Jordfuktighetssensor
- Ljussensor
- Peristaltisk pump
- OLED-display

## Beroenden
- U8glib-bibliotek för OLED-display
- Wire-bibliotek för I2C-kommunikation

## Installation
1. Anslut jordfuktighetssensorn till analog pin A0.
2. Anslut ljussensorn till analog pin A1.
3. Anslut den peristaltiska pumpen till digital pin 2.
4. Anslut OLED-displayen med I2C.

## Så fungerar det
1. Systemet läser av jordfuktighet och ljusnivåer.
2. Om jordfuktigheten är under en tröskel börjar det vattna tills fuktnivån är tillräcklig.
3. Om ljusnivåerna är för låga visas ett meddelande som indikerar otillräckligt solljus.
4. Om förhållandena är bra visas ett meddelande som indikerar optimalt solljus.

## Användning
- Ladda upp Arduino-koden till ditt kort.
- Följ den seriella utdatan för jordfuktighet och ljussensornivåer.
- OLED-displayen visar relevanta meddelanden om jordfuktighet och solljus.

## Bidrag
Du är välkommen att bidra till projektet genom att öppna ärenden eller skapa pull requests.

## Tack
- Detta projekt använder U8glib-biblioteket för OLED-displayen.
      
