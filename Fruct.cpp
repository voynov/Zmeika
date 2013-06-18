#include "Fruct.h"
#include <stdlib.h>
#include "constants.h"
#include <GL/glut.h>


Fruct::Fruct()
{

}

void Fruct::New()
{
	x = rand() % N;
	y = rand() % M;

	for (int i = 0; i < num; i++)
	{
		coords aCoord  = s[i];

		if (x == aCoord.x && y == aCoord.y)
		{
			// incorrect position. Call the same function
			// recursively if coords are not appropriate
			New();
		}
	}
}

void Fruct::DrawApple()
{
	glColor3f(colorRedOfApple, colorGreenOfApple, colorBlueOfApple);
	glRectf(x*Scale, y*Scale,(x+sizeCoefficientOfApple)*Scale, (y+sizeCoefficientOfApple)*Scale);
}

