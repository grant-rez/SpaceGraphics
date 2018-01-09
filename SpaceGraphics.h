#ifndef SPACE_GRAPHICS_H
#define SPACE_GRAPHICS_H

#include <stdint.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

#include "Canvas.h"
#include "Primitives.h"
#include "Viewport.h"


class SpaceGraphics
{
public:
	SpaceGraphics(uint32_t width, uint32_t height, Color color) : canvas(width, height, color), viewport(2, 2, 1) { }

	void print(std::string path);

	void Draw(Cube cube, Color color);

	void Draw(Triangle3D triangle, Color color);

	void Draw(Triangle2D triangle, Color color, Vec3 zVals);
private:
	
	
	Canvas canvas;
	Viewport viewport;
};

void interpolate(int32_t i0, int32_t i1, int32_t d0, int32_t d1, std::vector<int32_t> &out);
void interpolate(int32_t i0, int32_t i1, double d0, double d1, std::vector<double> &out);

#endif // !SPACE_GRAPHICS_H
