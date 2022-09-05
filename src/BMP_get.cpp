#include "BMP280.h"

/**
 * Get current temperature oversampling value.
 */
uint8_t BMP280::getTempOversampling()
{
    return (readRegister(BMP280_REG_CTRL_MEAS) & BMP280_BITS_OSRS_T) >> 5;
}

/**
 * Get current pressure oversampling value.
 */
uint8_t BMP280::getPressOversampling()
{
    return (readRegister(BMP280_REG_CTRL_MEAS) & BMP280_BITS_OSRS_P) >> 2;
}

/**
 * Get current power mode value.
 */
uint8_t BMP280::getPowerMode()
{
    return (readRegister(BMP280_REG_CTRL_MEAS) & BMP280_BITS_MODE);
}

/**
 * Get current standby time value.
 */
uint8_t BMP280::getStandbyTime()
{
    return (readRegister(BMP280_REG_CONFIG) & BMP280_BITS_T_SB) >> 5;
}

/**
 * Get current filter coefficient value
 */
uint8_t BMP280::getFilterCoeff()
{
    return (readRegister(BMP280_REG_CONFIG) & BMP280_BITS_FILTER) >> 2;
}

/**
 * Get current SPI3Wire value
 */
uint8_t BMP280::getSPI3Wire()
{
    return (readRegister(BMP280_REG_CONFIG) & BMP280_BITS_SPI3W_EN);
}

/**
 * Get ChipID
 */
uint8_t BMP280::getChipID()
{
    return readRegister(BMP280_REG_ID);
}

/**
 * Read calibration data
 */
void BMP280::getCalibrationData()
{
    calibrationData.dig_t1 = TO_UINT16(readRegister(BMP280_REG_DIG_T1_MSB), readRegister(BMP280_REG_DIG_T1_LSB));
    calibrationData.dig_t2 = TO_INT16(readRegister(BMP280_REG_DIG_T2_MSB), readRegister(BMP280_REG_DIG_T2_LSB));
    calibrationData.dig_t3 = TO_INT16(readRegister(BMP280_REG_DIG_T3_MSB), readRegister(BMP280_REG_DIG_T3_LSB));

    calibrationData.dig_p1 = TO_INT16(readRegister(BMP280_REG_DIG_P1_MSB), readRegister(BMP280_REG_DIG_P1_LSB));
    calibrationData.dig_p2 = TO_INT16(readRegister(BMP280_REG_DIG_P2_MSB), readRegister(BMP280_REG_DIG_P2_LSB));
    calibrationData.dig_p3 = TO_INT16(readRegister(BMP280_REG_DIG_P3_MSB), readRegister(BMP280_REG_DIG_P3_LSB));
    calibrationData.dig_p4 = TO_INT16(readRegister(BMP280_REG_DIG_P4_MSB), readRegister(BMP280_REG_DIG_P4_LSB));
    calibrationData.dig_p5 = TO_INT16(readRegister(BMP280_REG_DIG_P5_MSB), readRegister(BMP280_REG_DIG_P5_LSB));
    calibrationData.dig_p6 = TO_INT16(readRegister(BMP280_REG_DIG_P6_MSB), readRegister(BMP280_REG_DIG_P6_LSB));
    calibrationData.dig_p7 = TO_INT16(readRegister(BMP280_REG_DIG_P7_MSB), readRegister(BMP280_REG_DIG_P7_LSB));
    calibrationData.dig_p8 = TO_INT16(readRegister(BMP280_REG_DIG_P8_MSB), readRegister(BMP280_REG_DIG_P8_LSB));
    calibrationData.dig_p9 = TO_INT16(readRegister(BMP280_REG_DIG_P9_MSB), readRegister(BMP280_REG_DIG_P9_LSB));
}

/**
 * Get uncalibrated temperature 
 */ 
int32_t BMP280::getUncalibTemp()
{
    uint8_t buffer[3];
    readRegisterBytes(BMP280_REG_TEMP_MSB, buffer, 3);
    return UNCALIB_TO_INT32(buffer[0], buffer[1], buffer[2]);
}

/**
 * Get uncalibrated pressure
 */
int32_t BMP280::getUncalibPress()
{
    uint8_t buffer[3];
    readRegisterBytes(BMP280_REG_PRESS_MSB, buffer, 3);
    return UNCALIB_TO_INT32(buffer[0], buffer[1], buffer[2]);
}

// Get calibrated temperature
float BMP280::getTemperature()
{
    int32_t uncalibTemp = getUncalibTemp();
    int32_t var1, var2, T;
    
    var1 = ((((uncalibTemp >> 3) - ((int32_t) calibrationData.dig_t1 << 1))) * ((int32_t) calibrationData.dig_t2)) >> 11;

    var2 = (((((uncalibTemp >> 4) - ((int32_t) calibrationData.dig_t1)) * ((uncalibTemp >> 4) - ((int32_t) calibrationData.dig_t1))) >> 12) * ((int32_t) calibrationData.dig_t3)) >> 14;
    
    tFine = var1 + var2;

    T = (tFine * 5 + 128) >> 8;

    return (float) T / 100.0f;
}

// Get calibrated pressure
float BMP280::getPressure()
{
    int32_t uncalibTemp = getUncalibPress();
    int64_t var1, var2, P;

    var1 = ((int64_t) tFine) - 128000;
    var2 = var1 * var1 * (int64_t) calibrationData.dig_p6;
    var2 = var2 + ((var1 * (int64_t) calibrationData.dig_p5) << 17);
    var2 = var2 + (((int64_t) calibrationData.dig_p4) << 35);
    var1 = ((var1 * var1 * (int64_t) calibrationData.dig_p3) >> 8) + ((var1 * (int64_t) calibrationData.dig_p2) << 12);
    var1 = (((((int64_t) 1) << 47) + var1)) * ((int64_t) calibrationData.dig_p1) >> 33;
    if(var1 == 0)
    {
        return 0;
    }
    P = 1048576 - uncalibTemp;
    P = (((P << 31) - var2) * 3125) / var1;
    var1 = (((int64_t) calibrationData.dig_p9) * (P >> 13) * (P >> 13)) >> 25;
    var2 = (((int64_t) calibrationData.dig_p8) * P) >> 19;
    P = ((P + var1 + var2) >> 8) + (((int64_t) calibrationData.dig_p7) << 4);

    return (float) (P / 25600.0f);
}

/**
 * Get temperature in forced mode
 */
float BMP280::getTemperatureForced()
{
    setPowerMode(BMP280_POWERMODE_FORCED);
    return getTemperature();
}

/**
 * Get pressure in forced mode
 */
float BMP280::getPressureForced()
{
    setPowerMode(BMP280_POWERMODE_FORCED);
    return getPressure();
}

/**
 * Get temperature and pressure
 */
void BMP280::getSensorData(float *temperature, float *pressure)
{
    (*temperature) = getTemperature();
    (*pressure) = getPressure();
}

/**
 * Get temperature and pressure in forced mode
 */
void BMP280::getSensorDataForced(float *temperature, float *pressure)
{
    setPowerMode(BMP280_POWERMODE_FORCED);
    (*temperature) = getTemperature();
    (*pressure) = getPressure();
}