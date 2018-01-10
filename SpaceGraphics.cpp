#include "SpaceGraphics.h"

void SpaceGraphics::print(std::string path)
{
	std::ostringstream oss;
	std::ofstream out(path, std::ofstream::binary);

	oss << "P3 " << canvas.width << " " << canvas.height << " 256\n";
	
	for (uint32_t y = 0; y < canvas.height; ++y)
	{
		for (uint32_t x = 0; x < canvas.width; ++x)
		{
			Point2D point = { static_cast<double>(x), static_cast<double>(y) };
			Color col = canvas.getPixel(point, true);
			uint32_t r = col.r; 
			uint32_t g = col.g;
			uint32_t b = col.b; 
			oss << r << " " << g << " " << b << " ";
		}
		oss << "\n";
	}
	out << oss.str();
}

// Triangle 3D is in World Space
// Triangle 2D is in Canvas Space
// CURRENTLY JUST DRAWS A 2D Triangle
void SpaceGraphics::Draw(Triangle3D triangle, Color color)
{
	Triangle2D tri2D = {
		viewport.MapToViewport(triangle.p0, canvas.width, canvas.height),
		viewport.MapToViewport(triangle.p1, canvas.width, canvas.height),
		viewport.MapToViewport(triangle.p2, canvas.width, canvas.height)
	};

	Vec3 zVals{ 1 / triangle.p0.z, 1 / triangle.p1.z, 1 / triangle.p2.z };

	Draw(tri2D, color, zVals);
	
}

// TODO: FIGURE OUT HOW TO MAKE TRIANGLES WITH HORIZONTAL RIGHT EDGES LOOK BETTER
void SpaceGraphics::Draw(Triangle2D triangle, Color color, Vec3 zVals)
{
	// rearrange points so y's are in ascending order
	if (triangle.p0.y > triangle.p1.y)
	{
		std::swap(triangle.p0, triangle.p1);
		std::swap(zVals.i, zVals.j);
	}
	if (triangle.p1.y > triangle.p2.y)
	{
		std::swap(triangle.p1, triangle.p2);
		std::swap(zVals.j, zVals.k);
	}
	if (triangle.p0.y > triangle.p1.y)
	{
		std::swap(triangle.p0, triangle.p1);
		std::swap(zVals.i, zVals.j);
	}

	std::vector<int32_t> xl01, xl12, xl02;
	interpolate(triangle.p0.y, triangle.p1.y, triangle.p0.x, triangle.p1.x, xl01);
	interpolate(triangle.p1.y, triangle.p2.y, triangle.p1.x, triangle.p2.x, xl12);
	interpolate(triangle.p0.y, triangle.p2.y, triangle.p0.x, triangle.p2.x, xl02);

	std::vector<double> zl01, zl12, zl02;
	interpolate(triangle.p0.y, triangle.p1.y, zVals.i, zVals.j, zl01);
	interpolate(triangle.p1.y, triangle.p2.y, zVals.j, zVals.k, zl12);
	interpolate(triangle.p0.y, triangle.p2.y, zVals.i, zVals.k, zl02);

	// set up the right and left
	std::vector<int32_t> x_left;
	std::vector<int32_t> x_right;
	std::vector<double> z_left;
	std::vector<double> z_right;

	// check midpoint of long side with p1 and see which is on what side of what
	int32_t longMidPoint = (triangle.p0.x + triangle.p2.x) / 2;
	if (longMidPoint > triangle.p1.x)
	{
		x_right = xl02;
		x_left = xl01;
		x_left.pop_back();
		x_left.insert(x_left.end(), xl12.begin(), xl12.end());

		z_right = zl02;
		z_left = zl01;
		z_left.pop_back();
		z_left.insert(z_left.end(), zl12.begin(), zl12.end());
	}
	else
	{
		x_left = xl02;
		x_right = xl01;
		x_right.pop_back();
		x_right.insert(x_right.end(), xl12.begin(), xl12.end());

		z_left = zl02;
		z_right = zl01;
		z_right.pop_back();
		z_right.insert(z_right.end(), zl12.begin(), zl12.end());
	}

	for (int32_t y = triangle.p0.y; y < triangle.p2.y; ++y)
	{
		int32_t idx = y - triangle.p0.y;

		std::vector<double> horizontalZ;
		interpolate(x_left[idx], x_right[idx], z_left[idx], z_right[idx], horizontalZ);
		for (int32_t x = x_left[idx]; x <= x_right[idx]; ++x)
		{
			Point2D p = { static_cast<double>(x), static_cast<double>(y) };
			if (horizontalZ[x - x_left[idx]] > canvas.getZBuf(p))
			{
				canvas.getZBuf(p) = horizontalZ[x - x_left[idx]];
				canvas.getPixel(p, false) = color;
			}
		}
	}
}

void SpaceGraphics::Draw(Cube cube, Color color)
{
	
	Draw(Triangle3D{ cube.p3, cube.p2, cube.p6 }, GREEN);
	Draw(Triangle3D{ cube.p3, cube.p6, cube.p7 }, GREEN);
	Draw(Triangle3D{ cube.p0, cube.p1, cube.p2 }, RED);
	Draw(Triangle3D{ cube.p0, cube.p2, cube.p3 }, RED);
	Draw(Triangle3D{ cube.p0, cube.p3, cube.p4 }, BLUE);
	Draw(Triangle3D{ cube.p3, cube.p4, cube.p7 }, BLUE);	
	Draw(Triangle3D{ cube.p1, cube.p2, cube.p5 }, BLUE);
	Draw(Triangle3D{ cube.p2, cube.p5, cube.p6 }, BLUE);
	Draw(Triangle3D{ cube.p4, cube.p5, cube.p6 }, RED);
	Draw(Triangle3D{ cube.p4, cube.p6, cube.p7 }, RED);
	Draw(Triangle3D{ cube.p1, cube.p0, cube.p5 }, GREEN);
	Draw(Triangle3D{ cube.p0, cube.p5, cube.p4 }, GREEN);
	
}

void interpolate(int32_t i0, int32_t i1, int32_t d0, int32_t d1, std::vector<int32_t> &out)
{
	// set up the vector to have exactly the right amount of memory
	out = std::vector<int32_t>();
	out.reserve(i1 - i0);

	// setup starting variables
	double slope = (i1 - i0 != 0) ? (static_cast<double>(d1 - d0) / static_cast<double>(i1 - i0)) : (0);
	double current = d0;
	
	// push back first value
	out.push_back(current);
	
	for (int i = 1; i <= i1 - i0; ++i)
	{
		current += slope;
		double temp = current;
		out.push_back(static_cast<int32_t>(std::round(temp)));
	}
}

void interpolate(int32_t i0, int32_t i1, double d0, double d1, std::vector<double> &out)
{
	// set up the vector to have exactly the right amount of memory
	out = std::vector<double>();
	out.reserve(i1 - i0);

	// setup starting variables
	double m = (i1 - i0 != 0) ? ((d1 - d0) / static_cast<double>(i1 - i0)) : (0);

	for (int i = 0; i <= i1 - i0; ++i)
	{
		out.push_back(d0 + (m * i));
	}
}