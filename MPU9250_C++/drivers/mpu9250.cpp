/*
 * mpu9250.cpp
 *
 *  Created on: May 30, 2019
 *      Author: kalyansreenivas
 */
#include "mpu9250.hpp"

MPU9250::MPU9250(SPIDriver* spiDriver, SPIConfig* spiConfig)
    : mspiDriver(spiDriver),
      mspiConfig(spiConfig),
      mInternalState(States::INITIALIZING),
      mAccelDivider(0),
      mGyroDivider(0.) {
  // Initialize the driver
  initialize();
}

/*
 * @brief Initializes MPU9250 by setting initialization parameters.
 *
 * @ returns Returns the value contained in WHO_AM_I register. It will serve as
 * a
 *   check to verify that the MPU9250 is properly connected and ready to
 * communicate.
 */
void MPU9250::initialize() {
  // First check whether MPU9250 is properly connected.
  // It can be done by checking the WHO_AM_I register.
  const uint8_t returnVal = this->probeMPU9250();
  // Compare the result with the response that will be expected
  if (returnVal == (uint8_t)MPU_REG::WHO_AM_I_RESP) {
    mInternalState = States::INITIALIZED;
  }
  // Reset device
  // Device can be rest by writing to PWR_MGMT_1 register
  writeRegister((uint8_t)MPU_REG::PWR_MGMT_1, (uint8_t)MPU_CFG::H_RESET, 1);
  // Clock source to best available clock source
  writeRegister((uint8_t)MPU_REG::PWR_MGMT_1, (uint8_t)MPU_CFG::CLKSEL_BEST, 1);
  // Enable Accel and Gyro
  // This can be done by writing to PWR_MGMT_2 register
  writeRegister((uint8_t)MPU_REG::PWR_MGMT_2,
                (uint8_t)MPU_CFG::ENAGLE_GYRO_ACCEL, 1);
  // Set lowpass filter value for Gyro
  writeRegister((uint8_t)MPU_REG::CONFIG,
                (uint8_t)MPU_GYRO_CFG::DLPF_CFG_GYRO_184, 1);
  // Set Sensitivity scale of Gyro
  writeRegister((uint8_t)MPU_REG::CONFIG_GYRO,
                (uint8_t)MPU_GYRO_CFG::GYRO_FS_SEL_250DPS, 1);
  // Set sensitivity scale for Accelerometer
  writeRegister((uint8_t)MPU_REG::CONFIG_ACCEL,
                (uint8_t)MPU_ACCEL_CFG::ACCEL_FS_SEL_2G, 1);
  // Set Accelerometer low pass filter and ODR
  writeRegister((uint8_t)MPU_REG::CONFIG_ACCEL_2,
                (uint8_t)MPU_ACCEL_CFG::DLPF_ACCEL_184, 1);
  // Set Gyro and Accel dividers
  updateGyroAccelDividers();
}

/*
 * @brief Reads register or registers
 *
 * @param[in]
 */
void MPU9250::readRegisters(const uint8_t& registerToRead, void* receiveBuffer,
                            uint8_t nBytes) {
  uint8_t txBuffer = registerToRead | (uint8_t)MPU_REG::READ_FLAG;
  // Select SPI device
  this->selectSpiDevice();
  spiSend(mspiDriver, 1, &txBuffer);
  spiReceive(mspiDriver, nBytes, receiveBuffer);
  // Release the SPI device
  this->unSelectSpiDevice();
}

void MPU9250::writeRegister(const uint8_t& registerToWrite,
                            const uint8_t& dataToWrite, const uint8_t& nBytes) {
  // Transfer buffer
  uint8_t txBuffer[2];
  txBuffer[0] = registerToWrite;
  txBuffer[1] = dataToWrite;
  // Select SPI device
  this->selectSpiDevice();
  // Send data
  spiSend(mspiDriver, nBytes, &txBuffer);
  // Unselect and release the SPI device
  this->unSelectSpiDevice();
}

/*
 * @brief Selects the SPI device to start the transmission
 */
void MPU9250::selectSpiDevice() {
  // Acquire SPI bus
  spiAcquireBus(mspiDriver);

  // Start SPI transaction
  spiStart(mspiDriver, mspiConfig);

  // Select the SPI device
  spiSelect(mspiDriver);
}

/*
 * Un-selects and release the SPI device
 */
void MPU9250::unSelectSpiDevice() {
  // Unselect the slave
  spiUnselect(mspiDriver);

  // Release bus to be used by others
  spiReleaseBus(mspiDriver);
}

/*
 * @brief Set the dividers for Accelerometer and Gyroscope
 */
void MPU9250::updateGyroAccelDividers() {
  // Set the Gyro and Accel dividers based on the data set in the device
  uint8_t gyroDivider;
  readRegisters((uint8_t)MPU_REG::CONFIG_GYRO, &gyroDivider, 1);
  switch (gyroDivider) {
    case (uint8_t)MPU_GYRO_CFG::GYRO_FS_SEL_250DPS:
      mGyroDivider = 131;
      break;
    case (uint8_t)MPU_GYRO_CFG::GYRO_FS_SEL_500DPS:
      mGyroDivider = 65.5;
      break;
    case (uint8_t)MPU_GYRO_CFG::GYRO_FS_SEL_1000DPS:
      mGyroDivider = 32.8;
      break;
    case (uint8_t)MPU_GYRO_CFG::GYRO_FS_SEL_2000DPS:
      mGyroDivider = 16.4;
      break;
  }
  // Set Accel divider
  uint8_t accelDivider;
  readRegisters((uint8_t)MPU_REG::CONFIG_ACCEL, &accelDivider, 1);
  switch (accelDivider) {
    case (uint8_t)MPU_ACCEL_CFG::ACCEL_FS_SEL_2G:
      mAccelDivider = 16384;
      break;
    case (uint8_t)MPU_ACCEL_CFG::ACCEL_FS_SEL_4G:
      mAccelDivider = 8192;
      break;
    case (uint8_t)MPU_ACCEL_CFG::ACCEL_FS_SEL_8G:
      mAccelDivider = 4096;
      break;
    case (uint8_t)MPU_ACCEL_CFG::ACCEL_FS_SEL_10G:
      mAccelDivider = 2048;
      break;
  }
}

/*
 * @brief Reads the WHO_AM_I register of MPU9250.
 *
 * @ return Returns the received value from MPU9250.
 */
uint8_t MPU9250::probeMPU9250() {
  uint8_t receiveBuffer[2];
  readRegisters((uint8_t)MPU_REG::WHO_AM_I, &receiveBuffer, 2);
  return receiveBuffer[1];
}

const MPU9250::States& MPU9250::getState() const { return mInternalState; }

/*
 * @brief Get Gyrodata from MPU9250
 *
 * @param[in/out] gyroData The Gyroscope data
 */
void MPU9250::getGyroData(GyroData& gyroData) {
  // The receive buffer should of length 6 because of two bytes for
  // each axis
  uint8_t gyroReceiveBuffer[6];
  readRegisters((uint8_t)MPU_REG::GYRO_XOUT_H, &gyroReceiveBuffer, 6);
  // Combine high byte and low byte
  // https://stackoverflow.com/questions/11193918/combine-merge-two-bytes-into-one/11193978
  int16_t tempGyroX =
      ((int16_t)gyroReceiveBuffer[0] << 8) | gyroReceiveBuffer[1];
  int16_t tempGyroY =
      ((int16_t)gyroReceiveBuffer[2] << 8) | gyroReceiveBuffer[3];
  int16_t tempGyroZ =
      ((int16_t)gyroReceiveBuffer[4] << 8) | gyroReceiveBuffer[5];
  // Assign the gyro data
  gyroData.setAngularVelX((float)tempGyroX / mGyroDivider);
  gyroData.setAngularVelY((float)tempGyroY / mGyroDivider);
  gyroData.setAngularVelZ((float)tempGyroZ / mGyroDivider);
  // Set the timestamp too
  systime_t timeStamp = chVTGetSystemTime();
  // Convert the system time to microseconds
  gyroData.setTimeStamp(chTimeI2MS(timeStamp));
}

/*
 * @brief Get Acceldata from MPU9250
 *
 * @param[in/out] accelData The Accelerometer data
 */
void MPU9250::getAccelData(AccelData& accelData) {
  // The receive buffer should be of length 6
  uint8_t accelReceiveBuffer[6];
  readRegisters((uint8_t)MPU_REG::ACCEL_XOUT_H,
                &accelReceiveBuffer, 6);
  // Combine high byte and low byte just like we did for Gyro
  int16_t tempAccelX =
      ((int16_t)accelReceiveBuffer[0] << 8) | accelReceiveBuffer[1];
  int16_t tempAccelY =
      ((int16_t)accelReceiveBuffer[2] << 8) | accelReceiveBuffer[3];
  int16_t tempAccelZ =
      ((int16_t)accelReceiveBuffer[4] << 8) | accelReceiveBuffer[5];
  // Update accel data
  accelData.setAccelX((float)tempAccelX / mAccelDivider);
  accelData.setAccelY((float)tempAccelY / mAccelDivider);
  accelData.setAccelZ((float)tempAccelZ / mAccelDivider);
  // Set the timestamp too
  systime_t timeStamp = chVTGetSystemTime();
  // Convert the system time to microseconds
  accelData.setTimeStamp(chTimeI2MS(timeStamp));
}
