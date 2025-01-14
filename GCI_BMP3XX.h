/*!
 * @file Adafruit_BMP3XX.h
 *
 * Adafruit BMP3XX temperature & barometric pressure sensor driver
 *
 * This is the documentation for Adafruit's BMP3XX driver for the
 * Arduino platform.  It is designed specifically to work with the
 * Adafruit BMP388 breakout: https://www.adafruit.com/products/3966
 *
 * These sensors use I2C or SPI to communicate
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Ladyada for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#ifndef __BMP3XX_H__
#define __BMP3XX_H__

#include "bmp3.h"
#include <stdint.h>
#include <Adafruit_I2CDevice.h>

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
constexpr uint8_t BMP3XX_DEFAULT_ADDRESS {0x77}; ///< The default I2C address

/** Adafruit_BMP3XX Class for both I2C and SPI usage.
 *  Wraps the Bosch library for Arduino usage
 */
class GCI_BMP3XX {
public:
    GCI_BMP3XX();

    bool begin_I2C(
        uint8_t addr = BMP3XX_DEFAULT_ADDRESS,
        TwoWire *theWire = &Wire);

    uint8_t chipID(void);

    bool setTemperatureOversampling(uint8_t os);
    bool setPressureOversampling(uint8_t os);
    bool setIIRFilterCoeff(uint8_t fs);
    bool setOutputDataRate(uint8_t odr);

    /// Perform a reading in blocking mode
    bool performReading(void);

    /// Temperature (Celsius) assigned after calling performReading()
    double temperature;
    /// Pressure (Pascals) assigned after calling performReading()
    double pressure;

private:
    struct bmp3_dev the_sensor;
};

#endif
