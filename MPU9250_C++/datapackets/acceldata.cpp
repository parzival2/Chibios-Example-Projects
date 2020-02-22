/*
 * acceldata.cpp
 *
 *  Created on: Jun 1, 2019
 *      Author: kalyansreenivas
 */
#include "acceldata.hpp"

/*
 * Constructor
 */
AccelData::AccelData() : mAccelX(0.), mAccelY(0.), mAccelZ(0.), mTimeStamp(0) {}

/*
 * Destructor
 */
AccelData::~AccelData() {
  mAccelX = 0.;
  mAccelY = 0.;
  mAccelZ = 0.;
}

/*
 * @brief Set acceleration in x axis
 *
 * @param[in] Acceleration in x axis
 */
void AccelData::setAccelX(const float& accelX) { mAccelX = accelX; }

/*
 * @brief Set acceleration in y axis
 *
 * @param[in] Acceleration in y axis
 */
void AccelData::setAccelY(const float& accelY) { mAccelY = accelY; }

/*
 * @brief Set acceleration in z axis
 *
 * @param[in] Acceleration in z axis
 */
void AccelData::setAccelZ(const float& accelZ) { mAccelZ = accelZ; }

/*
 * @brief Get Acceleration in x axis
 *
 * @ return Acceleration in x axis
 */
const float& AccelData::getAccelX() const { return mAccelX; }

/*
 * @brief Get Acceleration in y axis
 *
 * @ return Acceleration in y axis
 */
const float& AccelData::getAccelY() const { return mAccelY; }

/*
 * @brief Get Acceleration in z axis
 *
 * @ return Acceleration in z axis
 */
const float& AccelData::getAccelZ() const { return mAccelZ; }

/*
 * @brief Get Timestamp
 */
const uint64_t& AccelData::getTimeStamp() const
{
	return mTimeStamp;
}

/*
 * @brief Set Timestamp
 */
void AccelData::setTimeStamp(const uint64_t& timestamp)
{
	mTimeStamp = timestamp;
}


