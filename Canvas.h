#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <vector>

#include "Primitives.h"

class Canvas
{
public:
	Canvas(uint32_t width_, uint32_t height_, Color color) : width(width_), height(height_), pixels(width * height, color), zBuf(width * height, 0) { }

	Color & getPixel(Point2D point, bool absolute)
	{
		if (!absolute)
		{
			point.x = point.x + (width / 2);
			point.y = point.y + (height / 2);
		}
		
		return pixels[static_cast<int32_t>(point.x) + (static_cast<int32_t>(point.y) * width)];
	}

	double & getZBuf(Point2D point)
	{

		point.x = point.x + (width / 2);
		point.y = point.y + (height / 2);
		return zBuf[static_cast<int32_t>(point.x) + (static_cast<int32_t>(point.y) * width)];
	}

	uint32_t width, height;

private:
	std::vector<Color> pixels;
	std::vector<double> zBuf;
};

#endif // !CANVAS_H
