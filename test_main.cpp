#include "SpaceGraphics.h"

int main()
{
	SpaceGraphics sg(1000, 1000, DKGRAY);

	sg.Draw(RIGHTDOWNCUBE + Vec3{ 3, 4, 10}, RED);

	sg.print("output.ppm");
}