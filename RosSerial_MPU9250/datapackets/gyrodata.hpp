/*
 * gyrodata.hpp
 *
 *  Created on: Jun 1, 2019
 *      Author: kalyansreenivas
 */

#ifndef DATAPACKETS_GYRODATA_HPP_
#define DATAPACKETS_GYRODATA_HPP_

class GyroData {
 public:
  /*
   * Constructor
   */
  GyroData();

  /*
   * Destructor
   */
  ~GyroData();
  // Getters and setters
  void setAngularVelX(const float& angVelX);
  void setAngularVelY(const float& angVelY);
  void setAngularVelZ(const float& angVelZ);
  // Getters
  const float& getAngularVelX() const;
  const float& getAngularVelY() const;
  const float& getAngularVelZ() const;

 private:
  /*
   * Angular velocity in X
   */
  float mAngularVelX;
  /*
   * Angular velocity in Y
   */
  float mAngularVelY;
  /*
   * Angular velocity in Z
   */
  float mAngularVelZ;
};

#endif /* DATAPACKETS_GYRODATA_HPP_ */
