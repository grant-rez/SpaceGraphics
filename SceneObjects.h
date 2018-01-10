#ifndef SCENE_OBJECTS_H
#define SCENE_OBJECTS_H

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
}; // Class Canvas



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
}; // Class Viewport



class Camera
{
public:
	Camera(Vec3 pos_, Vec3 dir_) : pos(pos_), dir(dir_) { }

private:
	Vec3 pos;
	Vec3 dir;
};
#endif // !SCENE_OBJECTS_H
