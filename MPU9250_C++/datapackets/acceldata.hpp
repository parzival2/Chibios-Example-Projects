/*
 * acceldata.hpp
 *
 *  Created on: Jun 1, 2019
 *      Author: kalyansreenivas
 */

#ifndef DATAPACKETS_ACCELDATA_HPP_
#define DATAPACKETS_ACCELDATA_HPP_

#include <stdint.h>

class AccelData {
 public:
  /*
   * Constructor
   */
  AccelData();
  /*
   * Destructor
   */
  ~AccelData();
  // Getters and setters
  void setAccelX(const float& accelX);
  void setAccelY(const float& accelY);
  void setAccelZ(const float& accelZ);
  void setTimeStamp(const uint64_t& timestamp);
  // Getters
  const float& getAccelX() const;
  const float& getAccelY() const;
  const float& getAccelZ() const;
  const uint64_t& getTimeStamp() const;

 private:
  /*
   * Acceleration in X direction
   */
  float mAccelX;
  /*
   * Acceleration in Y direction
   */
  float mAccelY;
  /*
   * Acceleration in Z direction
   */
  float mAccelZ;
  /*
   * Timestamp
   */
  uint64_t mTimeStamp;
};

#endif /* DATAPACKETS_ACCELDATA_HPP_ */
