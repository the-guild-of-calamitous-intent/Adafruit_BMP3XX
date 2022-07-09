/***************************************************************************
  This is a library for the BMP3XX temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP388 Breakout
  ----> http://www.adafruit.com/products/3966

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include "GCI_BMP3XX.h"

constexpr float SEALEVELPRESSURE_HPA {1013.25};

GCI_BMP3XX bmp;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Wire.setClock(100000); // 100 kHz
  // Wire.setClock(400000); // 400 kHz

  if (!bmp.begin_I2C()) {   // hardware I2C mode, can pass in address & alt Wire
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  // Datasheet, table 9, pg 17
  if (1) {
        // Drone
        // Mode: Normal
        // OS Pres: x8
        // OS Temp: x1
        // IIR: 2 -> 3
        // Sampling: 50Hz
        // RMS Noise [cm]: 11
        bmp.setTemperatureOversampling(BMP3_NO_OVERSAMPLING);
        bmp.setPressureOversampling(BMP3_OVERSAMPLING_8X);
        bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
        bmp.setOutputDataRate(BMP3_ODR_50_HZ);
    }
    else {
        // Indoor nav
        // Mode: Normal
        // OS Pres: x16
        // OS Temp: x2
        // IIR: 4 -> 15
        // Sampling: 25Hz
        // RMS Noise [cm]: 5
        bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_2X);
        bmp.setPressureOversampling(BMP3_OVERSAMPLING_16X);
        bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_15);
        bmp.setOutputDataRate(BMP3_ODR_25_HZ);
    }
}

void loop() {
  if (! bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  // Serial.println(bmp.temperature, 1);       // C
  Serial.println(bmp.pressure / 100.0, 3);  // hPa

  delay(10); // ~100Hz
}
