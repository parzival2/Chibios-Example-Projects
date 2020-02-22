/*
 * acceldata.hpp
 *
 *  Created on: Jun 1, 2019
 *      Author: kalyansreenivas
 */

#ifndef DATAPACKETS_ACCELDATA_HPP_
#define DATAPACKETS_ACCELDATA_HPP_

/*
 * A Class that will hold the Accelerometer data.
 *
 * Note: Make sure that the sensor produces data in g's.
 */
class AccelData {
public:
	// Constants
	/*
	 * Earth gravity in m/sec2
	 */
	static constexpr float STANDARD_GRAVITY = 9.80665;
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
	// Getters
	const float& getAccelX() const;
	const float& getAccelY() const;
	const float& getAccelZ() const;

private:
	/*
	 * Acceleration in X direction - m/sec2
	 */
	float mAccelX;
	/*
	 * Acceleration in Y direction - m/sec2
	 */
	float mAccelY;
	/*
	 * Acceleration in Z direction - m/sec2
	 */
	float mAccelZ;
};

#endif /* DATAPACKETS_ACCELDATA_HPP_ */
