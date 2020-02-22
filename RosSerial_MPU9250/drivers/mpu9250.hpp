/*
 * mpu9250.hpp
 *
 *  Created on: May 30, 2019
 *      Author: kalyansreenivas
 */

#ifndef DRIVERS_MPU9250_HPP_
#define DRIVERS_MPU9250_HPP_

#include "ch.hpp"
#include "datapackets/acceldata.hpp"
#include "datapackets/gyrodata.hpp"
#include "hal.h"
#include "mpuregisters.hpp"

class MPU9250 {
 public:
  // States
  enum class States : uint8_t { INITIALIZING = 0, INITIALIZED = 1 };
  MPU9250(SPIDriver* spiDriver, SPIConfig* spiConfig);

  // Getter and setters
  const States& getState() const;

  void getGyroData(GyroData& gyroData);

  void getAccelData(AccelData& accelData);



 private:
  /*
   * Private functions
   */
  void initialize();

  void readRegisters(const uint8_t& registerToRead, void* receiveBuffer,
                     uint8_t nBytes);

  void writeRegister(const uint8_t& registerToWrite, const uint8_t& dataToWrite,
                     const uint8_t& nBytes);

  uint8_t probeMPU9250();

  void selectSpiDevice();

  void unSelectSpiDevice();

  void updateGyroAccelDividers();

  /*
   * Private variables
   */
  SPIDriver* mspiDriver;
  SPIConfig* mspiConfig;

  /*
   * Internal state of MPU9250
   */
  States mInternalState;
  /*
   * Accelerometer divider
   */
  uint16_t mAccelDivider;
  /*
   * Gyroscope divider
   */
  float mGyroDivider;
};
#endif /* DRIVERS_MPU9250_HPP_ */
