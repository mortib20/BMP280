#include "BMP280.h"

/**
 * Start connection to sensor
 */
void BMP280::begin()
{
    Wire.begin();
    Wire.setClock(100000);
    setPowerMode(BMP280_POWERMODE_SLEEP);
    getCalibrationData();
}

/**
 * End connection to sensor
 */
void BMP280::end()
{
    Wire.end();
}

/**
 * Reset sensor to default
 */
void BMP280::reset()
{
    setRegister(BMP280_REG_RESET, BMP280_RESET);
}

/**
 * Write new register for reading
 */
void BMP280::writeRegister(uint8_t BMP280_REG_)
{
    Wire.beginTransmission(deviceAddress);
    Wire.write(BMP280_REG_);
    Wire.endTransmission();
}

/**
 * Read value from register
 */
uint8_t BMP280::readRegister(uint8_t BMP280_REG_)
{
    unsigned long start = millis();
    writeRegister(BMP280_REG_);

    Wire.requestFrom(deviceAddress, 0x1);

    while (!Wire.available())
    {
        unsigned long timeout = millis();
        if (timeout - start >= 100)
        {
            Serial.println("No connection to sensor");
            goto ERROR;
        }
    }

    return Wire.read();

    ERROR:
    return 0;
}

/**
 * Read values from register START_ to size_ into buffer_
 */
void BMP280::readRegisterBytes(uint8_t START_, uint8_t *buffer_, size_t size_)
{
    unsigned long start = millis();
    writeRegister(START_);

    Wire.requestFrom(deviceAddress, size_);

    for (size_t index = 0; index < size_; index++)
    {
        while (!Wire.available())
        {
            unsigned long timeout = millis();
            if (timeout - start >= 1000)
            {
                Serial.println("No connection to sensor");
                goto ERROR;
            }
        }

        buffer_[index] = Wire.read();
        continue;
        ERROR:
        buffer_[index] = 0;
    }
}