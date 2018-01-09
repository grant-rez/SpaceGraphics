#ifndef PRIMITIVES_H
#define PRIMITIVES_H

struct Point2D
{
	double x, y;
};

struct Point3D
{
	double x, y, z;
};

struct Triangle2D
{
	Point2D p0, p1, p2;
};

struct Triangle3D
{
	Point3D p0, p1, p2;
};

struct Cube
{
	Point3D p0, p1, p2, p3, p4, p5, p6, p7;
};

struct Color
{
	uint8_t r, g, b;
};

struct Vec3
{
	double i, j, k;
};

const Color RED = { 255, 0, 0 };
const Color GREEN = { 0, 255, 0 };
const Color BLUE = { 0, 0, 255 };

const Cube RIGHTDOWNCUBE = {
	Point3D{ 0.25, -0.25, 2.0 },
	Point3D{ 0.75, -0.25, 2.0 },
	Point3D{ 0.75, -0.25, 1.5 },
	Point3D{ 0.25, -0.25, 1.5 },
	Point3D{ 0.25, -0.75, 2.0 },
	Point3D{ 0.75, -0.75, 2.0 },
	Point3D{ 0.75, -0.75, 1.5 },
	Point3D{ 0.25, -0.75, 1.5 }
};

#endif // !PRIMITIVES_H
