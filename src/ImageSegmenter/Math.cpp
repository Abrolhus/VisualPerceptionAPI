#include "Math.h"
#include <cstdlib>
#include <cmath>

extern "C"
{
	float FixAngle(float rad)
	{
		rad = std::fmod(rad, 2 * PI);
		if (rad > PI)
			rad -= 2 * PI;
		return rad;
	}

	float FixAngled(float deg)
	{
		deg = std::fmod(deg, 360);
		if (deg > 180)
			deg -= 360;
		return deg;
	}
}