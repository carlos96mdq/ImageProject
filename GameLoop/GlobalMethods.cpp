#include "GlobalMethods.h"

namespace MATH
{
	// Normalize a vector
	void normalize(sf::Vector2f& vector)
	{
		float magnitud = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
		if (magnitud == 0)
		{
			return;
		}		
		vector.x = vector.x / magnitud;
		vector.y = vector.y / magnitud;
	}

	// Rotate a vector a number of radians
	void rotate(sf::Vector2f& vector, float degree)
	{
		float magnitud = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
		if (magnitud == 0)
		{
			return;
		}
		float angle = acosf(vector.x / magnitud);
		// As acos() return an angle between 0 and 180, a verification needs to be done to include 180 to 360
		if (vector.y < 0)
		{
			angle = -angle;
		}
		// Convert degree to radians
		float pi = 2 * acosf(0.0);
		// Because the y axis is rotated 180 degrees (is positive downstairs and not upstairs) this conversion is needed
		degree = -degree;
		angle += (degree * pi / 180);
		vector.x = magnitud * cosf(angle);
		vector.y = magnitud * sinf(angle);
	}
}