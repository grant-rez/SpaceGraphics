#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <stdint.h>

#include "Primitives.h"

class Viewport
{
public:
	Viewport(int32_t width_, int32_t height_, int32_t depth_) : width(width_), height(height_), depth(depth_) { }
	
	Point2D MapToViewport(Point3D p, uint32_t canvas_width, uint32_t canvas_height)
	{
		double x = depth * p.x / p.z;
		double y = depth * p.y / p.z;
		x = x * canvas_height / 2;
		y = y * canvas_height / 2;
		return Point2D{ x, y };
	}

private:
	int32_t width, height, depth;
};

#endif // !VIEWPORT_H
