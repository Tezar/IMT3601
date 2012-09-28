#include "Vehicle.hpp"


Vehicle::Vehicle(void)
{
	force = force_forward;
	turning = turning_none;
	position.set(0,0,0);
}


Vehicle::~Vehicle(void)
{
}
