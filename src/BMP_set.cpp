#include "BMP280.h"

/**
 * Set register BMP280_REG_ to value_
 */
void BMP280::setRegister(uint8_t BMP280_REG_, uint8_t value_)
{
    Wire.beginTransmission(deviceAddress);
    Wire.write(BMP280_REG_);
    Wire.write(value_);
    Wire.endTransmission();
}

/**
 * Set temperature oversampling to BMP280_OVERSAMP_
 */
void BMP280::setTempOversampling(uint8_t BMP280_OVERSAMP_)
{
    setRegister(BMP280_REG_CTRL_MEAS, (readRegister(BMP280_REG_CTRL_MEAS) & ~BMP280_BITS_OSRS_T) | (BMP280_OVERSAMP_ << 5));
}

/**
 * Set pressure oversampling to BMP280_OVERSAMP_
 */
void BMP280::setPressOversampling(uint8_t BMP280_OVERSAMP_)
{
    delay(100);
    setRegister(BMP280_REG_CTRL_MEAS, (readRegister(BMP280_REG_CTRL_MEAS) & ~BMP280_BITS_OSRS_P) | (BMP280_OVERSAMP_ << 2));
}

/**
 * Set power mode to BMP280_POWERMODE_
 */
void BMP280::setPowerMode(uint8_t BMP280_POWERMODE_)
{
    setRegister(BMP280_REG_CTRL_MEAS, (readRegister(BMP280_REG_CTRL_MEAS) & ~BMP280_BITS_MODE) | (BMP280_POWERMODE_));
}

/**
 * Set standby time for normal mode to BMP280_STANDBY_
 */
void BMP280::setStandbyTime(uint8_t BMP280_STANDBY_)
{
    setRegister(BMP280_REG_CONFIG, (readRegister(BMP280_REG_CONFIG) & ~BMP280_BITS_T_SB) | (BMP280_STANDBY_ << 5));
}

/**
 * Set filter coefficient to BMP280_FILTER_
 */
void BMP280::setFilterCoeff(uint8_t BMP280_FILTER_)
{
    setRegister(BMP280_REG_CONFIG, (readRegister(BMP280_REG_CONFIG) & ~BMP280_BITS_FILTER) | (BMP280_FILTER_ << 2));
}

/**
 * Enable or disable 3-wire SPI interface
 */
void BMP280::setSPI3Wire(uint8_t BMP280_SPI3_)
{
    setRegister(BMP280_REG_CONFIG, (readRegister(BMP280_REG_CONFIG) & ~BMP280_BITS_MODE) | (BMP280_SPI3_));
}