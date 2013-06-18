#include "menubutton.h"
#include <GL/glut.h>
#include "constants.h"
#include <string.h>

MenuButton::MenuButton()
{

}

void MenuButton::New()
{
    int spacing = 5;
    if (0 == stateOfButton)
    {
        glColor3f(colorRedOfButton, colorGreenOfButton, colorBlueOfButton);
    } else
    {
        glColor3f(colorRedOfSelectedButton, colorGreenOfSelectedButton, colorBlueOfSelectedButton);
    }

    glRectf(x, y, x + width, y + height);

    glColor3f(colorRedOfButtonText/255.0, colorGreenOfButtonText/255.0, colorBlueOfButtonText/255.0);
    glRasterPos2f( x + spacing, y + spacing);
    for( int i = 0; nameOfButton[i] > 0; i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, nameOfButton[i] );
    }
}


