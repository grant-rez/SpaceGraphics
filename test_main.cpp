#include "SpaceGraphics.h"

int main()
{
	SpaceGraphics sg(1000, 1000, Color{ 250,250,250 });

	sg.Draw(RIGHTDOWNCUBE, RED);

	sg.print("output.ppm");
}