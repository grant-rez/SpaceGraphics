#ifndef PRIMITIVES_H
#define PRIMITIVES_H

struct Vec3
{
	double i, j, k;
};

struct Point2D
{
	double x, y;
};

struct Point3D
{
	double x, y, z;

	Point3D operator+(Vec3 trans) const
	{
		double i = x + trans.i;
		double j = y + trans.j;
		double k = z + trans.k;
		return Point3D{ i, j, k };
	}
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

	Cube operator+(Vec3 trans) const
	{
		return Cube{
		p0 + trans,
		p1 + trans,
		p2 + trans,
		p3 + trans,
		p4 + trans,
		p5 + trans,
		p6 + trans,
		p7 + trans
		};
	}
};

struct Color
{
	uint8_t r, g, b;
};

const Color RED = { 255, 0, 0 };
const Color GREEN = { 0, 255, 0 };
const Color BLUE = { 0, 0, 255 };
const Color DKGRAY = { 35, 35, 35 };

const Cube RIGHTDOWNCUBE = {
	Point3D{ -1.0,  1.0,  1.0 },
	Point3D{  1.0,  1.0,  1.0 },
	Point3D{  1.0,  1.0, -1.0 },
	Point3D{ -1.0,  1.0, -1.0 },
	Point3D{ -1.0, -1.0,  1.0 },
	Point3D{  1.0, -1.0,  1.0 },
	Point3D{  1.0, -1.0, -1.0 },
	Point3D{ -1.0, -1.0, -1.0 }
};

#endif // !PRIMITIVES_H
