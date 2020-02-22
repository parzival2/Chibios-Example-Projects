/*
 * mpuregisters.hpp
 *
 *  Created on: May 30, 2019
 *      Author: kalyansreenivas
 */

#ifndef DRIVERS_MPUREGISTERS_HPP_
#define DRIVERS_MPUREGISTERS_HPP_

// MPU9250 Registers
enum class MPU_REG : uint8_t {
  WHO_AM_I = 0x75,
  READ_FLAG = 0x80,
  READHEX = 0x00,
  WHO_AM_I_RESP = 0x71,
  // Accelerometer data registers
  // X Axis
  ACCEL_XOUT_H = 0x3B,
  ACCEL_XOUT_L = 0x3C,
  // Y Axis
  ACCEL_YOUT_H = 0x3D,
  ACCEL_YOUT_L = 0x3E,
  // Z Axis
  ACCEL_ZOUT_H = 0x3F,
  ACCEL_ZOUZ_L = 0x40,
  // Temperature sensor
  TEMP_OUT_H = 0x41,
  TEMP_OUT_L = 0x42,
  // Gyro data registers
  // X Axis
  GYRO_XOUT_H = 0x43,
  GYRO_XOUT_L = 0x44,
  // Y Axis
  GYRO_YOUT_H = 0x45,
  GYRO_YOUT_L = 0x46,
  // Z Axis
  GYRO_ZOUT_H = 0x47,
  GYRO_ZOUZ_L = 0x48,
  // Power management registers
  PWR_MGMT_1 = 0x6B,
  PWR_MGMT_2 = 0x6C,
  // Configuration registers(Gyro and temperature sensors are filtered according
  // to this value)
  CONFIG = 0x1A,
  CONFIG_GYRO = 0x1B,
  CONFIG_ACCEL = 0x1C,
  CONFIG_ACCEL_2 = 0x1D

};

/*
 * MPU9250 Configuration registers
 * https://cdn.sparkfun.com/assets/learn_tutorials/5/5/0/MPU-9250-Register-Map.pdf
 * Starting from Page 40.
 *
 * Calculated using
 * http://calc.50x.eu/
 */
enum class MPU_CFG : uint8_t {
  /*
   * PWR_MGMT_1
   */
  // Resets the internal registers and restores default settings
  H_RESET = 0x80,
  // When set, the chip is set to sleep mode
  SLEEP = 0x40,
  // When set, and SLEEP and STANDBY are not set, the chip will cycle
  // between sleep and taking a single sample at a rate determined by
  // LP_ACCEL_ODR register
  CYCLE = 0x20,
  // When set, the gyro drive and pll circuitry are enabled, but
  // sense paths are disabled.
  GYRO_STANDBY = 0x10,
  // Powerdown internal PTAT voltage generator and PTAT ADC
  PD_PTAT = 0x08,
  // Clock source internal
  CLKSEL_INTERNAL = 0x00,
  // Selects best available clock source
  CLKSEL_BEST = 0x01,
  // Stops clock
  CLKSEL_STOPCLOCK = 0x07,

  /*
   * PWR_MGMT_2
   */
  // Disable X Accelerometer
  DISABLE_X_A = 0x20,
  // Disable Y accelerometer
  DISABLE_Y_A = 0x10,
  // Disable Z accelerometer
  DISABLE_Z_A = 0x08,
  // Disable X gyro
  DISABLE_X_G = 0x04,
  // Disable Y gyro
  DISABLE_Y_G = 0x02,
  // Disable Z gyro
  DISABLE_Z_G = 0x01,
  // Enable Gyro and Accelerometer
  ENAGLE_GYRO_ACCEL = 0x00
};

enum class MPU_GYRO_CFG : uint8_t {
  /*
   * Digital Low-pass filter
   */
  // 250hz bandwidth for Gyroscope and 4000hz for temperature sensor
  DLPF_CFG_GYRO_250 = 0x00,
  // 184hz bandwidth
  DLPF_CFG_GYRO_184 = 0x01,
  // 92hz bandwidth
  DLPF_CFG_GYRO_92 = 0x02,
  // 41hz bandwidth
  DLPF_CFG_GYRO_41 = 0x03,
  // 20hz bandwidth
  DLPF_CFG_GYRO_20 = 0x04,
  // 10hz bandwidth
  DLPF_CFG_GYRO_10 = 0x05,
  // 5hz bandwidth
  DLPF_CFG_GYRO_5 = 0x06,
  /*
   * Gyro full scale select
   */
  // 250 degrees/sec
  GYRO_FS_SEL_250DPS = 0x00,
  // 500 degrees/sec
  GYRO_FS_SEL_500DPS = 0x08,
  // 1000 degrees/sec
  GYRO_FS_SEL_1000DPS = 0x10,
  // 2000 degrees/sec
  GYRO_FS_SEL_2000DPS = 0x18,
};

enum class MPU_ACCEL_CFG : uint8_t {
  /*
   * Digital Low-pass filter
   */
  // 460hz
  DLPF_ACCEL_460 = 0x00,
  // 184hz
  DLPF_ACCEL_184 = 0x01,
  // 92hz
  DLPF_ACCEL_92 = 0x02,
  // 41hz
  DLPF_ACCEL_41 = 0x03,
  // 20hz
  DLPF_ACCEL_20 = 0x04,
  // 10hz
  DLPF_ACCEL_10 = 0x05,
  // 5hz
  DLPF_ACCEL_5 = 0x06,
  /*
   * Accel full scale select
   */
  // 2g
  ACCEL_FS_SEL_2G = 0x00,
  // 4g
  ACCEL_FS_SEL_4G = 0x08,
  // 8g
  ACCEL_FS_SEL_8G = 0x10,
  // 10g
  ACCEL_FS_SEL_10G = 0x18,
};

#endif /* DRIVERS_MPUREGISTERS_HPP_ */
