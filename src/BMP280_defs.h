/**
 * Chip identification number
 */
#define BMP280_CHIP_ID 0x58

/**
 * Reset value
 */
#define BMP280_RESET 0xB6

/**
 * Bits
 */
enum BMP280_BITS
{
    BMP280_BITS_OSRS_T      = 0b11100000,
    BMP280_BITS_OSRS_P      = 0b00011100,
    BMP280_BITS_MODE        = 0b00000011,
    BMP280_BITS_T_SB        = 0b11100000,
    BMP280_BITS_FILTER      = 0b00011100,
    BMP280_BITS_SPI3W_EN    = 0b00000011
};

/**
 * I2C address definitions
 */
enum BMP280_ADDR
{
    BMP280_ADDR_0 = 0x76,
    BMP280_ADDR_1 = 0x77
};

/**
 * Power mode definitions
 */
enum BMP280_POWERMODE
{
    BMP280_POWERMODE_SLEEP  = 0b00,
    BMP280_POWERMODE_FORCED = 0b01,
    BMP280_POWERMODE_NORMAL = 0b11
};

/**
 * Oversampling settings definitions
 */
enum BMP280_OVERSAMP
{
    BMP280_OVERSAMP_OFF         = 0b000,
    BMP280_OVERSAMP_ULTRA_LOW   = 0b001,
    BMP280_OVERSAMP_LOW         = 0b010,
    BMP280_OVERSAMP_STANDARD    = 0b011,
    BMP280_OVERSAMP_HIGH        = 0b100,
    BMP280_OVERSAMP_ULTRA_HIGH  = 0b101
};

/**
 * Filter coefficient settings definitions
 */
enum BMP280_FILTER
{
    BMP280_FILTER_OFF       = 0b000,
    BMP280_FILTER_COEFF_2   = 0b001,
    BMP280_FILTER_COEFF_4   = 0b010,
    BMP280_FILTER_COEFF_8   = 0b011,
    BMP280_FILTER_COEFF_16  = 0b100
};

/**
 * Normal mode standby times definitions
 */
enum BMP280_STANDBY
{
    BMP280_STANDBY_0_5  = 0b000,
    BMP280_STANDBY_62_5 = 0b001,
    BMP280_STANDBY_125  = 0b010,
    BMP280_STANDBY_250  = 0b011,
    BMP280_STANDBY_500  = 0b100,
    BMP280_STANDBY_1000 = 0b101,
    BMP280_STANDBY_2000 = 0b110,
    BMP280_STANDBY_4000 = 0b111
};


/**
 * 3-wire interface enabled or disabled definitions
 */
enum BMP280_SPI3
{
    BMP280_SPI3_DISABLED    = 0b00,
    BMP280_SPI3_ENABLED     = 0b01
};

enum BMP280_REG
{
    BMP280_REG_TEMP_XLSB    = 0xFC,
    BMP280_REG_TEMP_LSB     = 0xFB,
    BMP280_REG_TEMP_MSB     = 0xFA,
    BMP280_REG_PRESS_XLSB   = 0xF9,
    BMP280_REG_PRESS_LSB    = 0xF8,
    BMP280_REG_PRESS_MSB    = 0xF7,
    BMP280_REG_CONFIG       = 0xF5,
    BMP280_REG_CTRL_MEAS    = 0xF4,
    BMP280_REG_STATUS       = 0xF3,
    BMP280_REG_RESET        = 0xE0,
    BMP280_REG_ID           = 0xD0,
    BMP280_REG_DIG_T1_LSB   = 0x88,
    BMP280_REG_DIG_T1_MSB   = 0x89,
    BMP280_REG_DIG_T2_LSB   = 0x8A,
    BMP280_REG_DIG_T2_MSB   = 0x8B,
    BMP280_REG_DIG_T3_LSB   = 0x8C,
    BMP280_REG_DIG_T3_MSB   = 0x8D,
    BMP280_REG_DIG_P1_LSB   = 0x8E,
    BMP280_REG_DIG_P1_MSB   = 0x8F,
    BMP280_REG_DIG_P2_LSB   = 0x90,
    BMP280_REG_DIG_P2_MSB   = 0x91,
    BMP280_REG_DIG_P3_LSB   = 0x92,
    BMP280_REG_DIG_P3_MSB   = 0x93,
    BMP280_REG_DIG_P4_LSB   = 0x94,
    BMP280_REG_DIG_P4_MSB   = 0x95,
    BMP280_REG_DIG_P5_LSB   = 0x96,
    BMP280_REG_DIG_P5_MSB   = 0x97,
    BMP280_REG_DIG_P6_LSB   = 0x98,
    BMP280_REG_DIG_P6_MSB   = 0x99,
    BMP280_REG_DIG_P7_LSB   = 0x9A,
    BMP280_REG_DIG_P7_MSB   = 0x9B,
    BMP280_REG_DIG_P8_LSB   = 0x9C,
    BMP280_REG_DIG_P8_MSB   = 0x9D,
    BMP280_REG_DIG_P9_LSB   = 0x9E,
    BMP280_REG_DIG_P9_MSB   = 0x9F
};

struct bmp280_calibration_data_t
{
    uint16_t    dig_t1;
    int16_t     dig_t2;
    int16_t     dig_t3;
    uint16_t    dig_p1;
    int16_t     dig_p2;
    int16_t     dig_p3;
    int16_t     dig_p4;
    int16_t     dig_p5;
    int16_t     dig_p6;
    int16_t     dig_p7;
    int16_t     dig_p8;
    int16_t     dig_p9;
};

/**
 * Conversion
 */
#define TO_UINT16(MSB, LSB) (uint16_t) (((uint16_t) MSB << 8) | ((uint16_t) LSB))
#define TO_INT16(MSB, LSB) (int16_t) (((int16_t) MSB << 8) | ((int16_t) LSB))
#define UNCALIB_TO_INT32(MSB, LSB, XLSB) (int32_t) ((int32_t) MSB << 12) | ((int32_t) LSB << 4) | ((int32_t) XLSB >> 4)