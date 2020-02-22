/*
 * gyrodata.cpp
 *
 *  Created on: Jun 1, 2019
 *      Author: kalyansreenivas
 */
#include "gyrodata.hpp"

/*
 * Constructor
 */
GyroData::GyroData() :
mAngularVelX(0.),
mAngularVelY(0.),
mAngularVelZ(0.),
mTimeStamp(0)
{
  // Nothing to do
}

/*
 * Destructor
 */
GyroData::~GyroData() {
  // Set the angular velocity values to their defaults
  mAngularVelX = 0.;
  mAngularVelY = 0.;
  mAngularVelZ = 0.;
}

/*
 * @brief Set angular velocity in X direction
 *
 * @param[in] angular velocity in X
 */
void GyroData::setAngularVelX(const float& angVelX) { mAngularVelX = angVelX; }

/*
 * @brief Set angular velocity in Y direction
 *
 * @param[in] angular velocity in Y
 */
void GyroData::setAngularVelY(const float& angVelY) { mAngularVelY = angVelY; }

/*
 * @brief Set angular velocity in Z direction
 *
 * @param[in] angular velocity in Z
 */
void GyroData::setAngularVelZ(const float& angVelZ) { mAngularVelZ = angVelZ; }

/*
 * @brief Set Timestamp
 *
 * @param[in] timestamp Timestamp
 */
void GyroData::setTimeStamp(const uint64_t& timestamp)
{
	mTimeStamp = timestamp;
}

/*
 * @brief Get angular velocity in X Direction
 *
 * @return Returns the angular velocity in X direction.
 */
const float& GyroData::getAngularVelX() const { return mAngularVelX; }

/*
 * @brief Get angular velocity in Y Direction
 *
 * @return Returns the angular velocity in Y direction.
 */
const float& GyroData::getAngularVelY() const { return mAngularVelY; }

/*
 * @brief Get angular velocity in Z Direction
 *
 * @return Returns the angular velocity in Z direction.
 */
const float& GyroData::getAngularVelZ() const { return mAngularVelZ; }

/*
 * @brief Get timestamp
 *
 * @return Returns the timestamp
 */
const uint64_t& GyroData::getTimeStamp() const
{
	return mTimeStamp;
}
