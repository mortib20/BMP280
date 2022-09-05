#include <Arduino.h>
#include <Wire.h>

#include "BMP280_defs.h"

class BMP280
{
public:
    BMP280();
    BMP280(int8_t BMP280_ADDR_) : deviceAddress(BMP280_ADDR_) {};
    
    void begin();
    void end();
    void reset();
    
    void setTempOversampling(uint8_t BMP280_OVERSAMP_);
    void setPressOversampling(uint8_t BMP280_OVERSAMP_);
    void setPowerMode(uint8_t BMP280_POWERMODE_);
    void setStandbyTime(uint8_t BMP280_STANDBY_);
    void setFilterCoeff(uint8_t BMP280_FILTER_);
    void setSPI3Wire(uint8_t BMP280_SPI3_);

    uint8_t getTempOversampling();
    uint8_t getPressOversampling();
    uint8_t getPowerMode();
    uint8_t getStandbyTime();
    uint8_t getFilterCoeff();
    uint8_t getSPI3Wire();
    uint8_t getChipID();

    float getTemperature();
    float getTemperatureForced();
    float getPressure();
    float getPressureForced();
    void getSensorData(float *temperature, float *pressure);
    void getSensorDataForced(float *temperature, float *pressure);
private:
    const uint8_t chipID = BMP280_CHIP_ID;
    int8_t deviceAddress = BMP280_ADDR_0;
    bmp280_calibration_data_t calibrationData;
    int32_t tFine;

    void writeRegister(uint8_t BMP280_REG_);
    void setRegister(uint8_t BMP280_REG_, uint8_t value_);

    uint8_t readRegister(uint8_t BMP280_REG_);
    void readRegisterBytes(uint8_t START_, uint8_t *buffer, size_t size);

    void getCalibrationData();
    int32_t getUncalibTemp();
    int32_t getUncalibPress();
};