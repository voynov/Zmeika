#include <windows.h>
#include <time.h>
#include <string.h>

#include <GL/glut.h>

#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "Fruct.h"

// prototypes of functions
void gameOver();
void initializeButtons();
void DrawSnake();
void Tick();
void DrawField();
void display();
void KeyboardEvent(int key, int a, int b);
void timer(int);
void OnMouseClick(int button, int state, int x, int y);
///////////////////////////////////////////////////////

/*
    Class Fruct represents game points which snake eats
*/
class Fruct m[numberOfApples];


class MenuButton
{
public:
	int x, y;
	int width, height;
	int stateOfButton;
	const char * nameOfButton;
	void (*onClickFunction)(int); // pointer on function

	void New()
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
		glRasterPos2f( x + spacing, y + spacing); //position of text
		for( int i = 0; nameOfButton[i] > 0; i++ ) //cycle while symbol!=0
		{
			glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, nameOfButton[i] );
		}
	}
} buttons[numberOfMenuButtons];

int main(int argc, char *argv[])
{
	srand(time(0));
	int i;
	// init fruct positions
	for (i = 0; i < 10; i++)
    {
		m[i].New();
    }

	glutInit(&argc, argv); //initializing of glut
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB ); // double buffering
	glutInitWindowSize (w, h);
	glutCreateWindow ("Zmeika");
	glClearColor(1.0, 1.0, 0.6, 1.0);  //background color
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	initializeButtons();
	time_t now;

	time(&now);  /* get current time; same as: now = time(NULL)  */

	startGame = localtime(&now);

    // When GLUT determines that the window needs to be redisplayed, 'display' callback function is called.
	glutDisplayFunc(display);

	//The special keyboard callback function is triggered when keyboard is pressed.
	glutSpecialFunc(KeyboardEvent);

	//glutTimerFunc registers the timer callback function which will be triggered in msecs milliseconds.
	glutTimerFunc(speedDelay, timer, 0);

	//When a user presses and releases mouse buttons in the window, each press and each release generates 'OnMouseClick'.
	glutMouseFunc(OnMouseClick);

    //glutMainLoop enters the GLUT event processing loop. This routine should be called at most once in a GLUT program.
	glutMainLoop();
}

void displayText( float x, float y, int r, int g, int b, const char *string )
{
	int j = strlen( string );

	glColor3f(r/255.0, g/255.0, b/255.0);
	glRasterPos2f( x, y );
	for( int i = 0; i < j; i++ )
	{
	    // glutBitmapCharacter renders one bitmap character using OpenGL
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
	}
}

void DrawSnake()
{
	glColor3f(colorRedOfHeadSnake, colorGreenOfHeadSnake, colorBlueOfHeadSnake);

	int headNumber = 1;
	for (int i = 0; i < headNumber; i++)
	{
	    // draw the rectangle using the function glRectf()
		glRectf(s[i].x * Scale, s[i].y * Scale, (s[i].x + sizeCoefficient) * Scale, (s[i].y + sizeCoefficient) * Scale);
	}

	glColor3f(colorRedOfSnake, colorGreenOfSnake, colorBlueOfSnake);

	for (int i = headNumber; i < num; i++)
	{
		glRectf(s[i].x * Scale, s[i].y * Scale, (s[i].x + sizeCoefficient) * Scale, (s[i].y + sizeCoefficient) * Scale);
	}
}

void collisionDetected()
{
	isGameOver = true;
	gameOver();
	//glutSetWindowTitle changes the window title
	glutSetWindowTitle(gameOverText);
}

void Tick()
{
	if (false == isGameOver)
	{
	    // copy all items of snake to new position
		for (int i=num;i>0;--i)
		{s[i].x=s[i-1].x;
		s[i].y=s[i-1].y;}

		if (dir==0) s[0].y+=1; // top
		if (dir==1) s[0].x-=1; // left
		if (dir==2) s[0].x+=1; // right
		if (dir==3) s[0].y-=1; // down

		for (int i=0; i<numberOfApples; i++)
		{
			if ((s[0].x == m[i].x) && (s[0].y == m[i].y))
			{
				num++;
				m[i].New(); // generate new position
				speedDelay -= 1; // delay time gets less
			}
		}

        // check field bounds and move head to opposite side of field
		if (s[0].x>N-1) s[0].x = 0;  if (s[0].x<0) s[0].x = N-1;
		if (s[0].y>M-1) s[0].y = 0;  if (s[0].y<0) s[0].y = M-1;

        // check snake has collision with itself
		for (int i=1; i<num; i++)
		{
			if (s[0].x == s[i].x && s[0].y == s[i].y)
			{
				collisionDetected();
			}
		}
		wasDrawn = true;
	}
}


void DrawField()
{
	glColor3f(colorRedOfLines, colorGreenOfLines, colorBlueOfLines);
	// create figure between glBegin and glEnd.
	// Ten symbolic constants are accepted: GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP,
	// GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS, GL_QUAD_STRIP, and GL_POLYGON.
	glBegin(GL_LINES);
	for (int i=0; i<w; i+=Scale)
	{
		glVertex2f(i,0); glVertex2f(i,h-menuPaneHeight);
	}
	for (int j=0; j<h-menuPaneHeight+Scale/2; j+=Scale)
	{
		glVertex2f(0,j); glVertex2f(w,j);
	}
	glEnd();
}

void drawMenuButtons()
{
    for (int i=0; i < numberOfMenuButtons; i++)
	{
        buttons[i].x = spacingBetweenButtons + i * (buttonStandartWidth + spacingBetweenButtons);
        buttons[i].y = (M + 1) * Scale;
        buttons[i].width = buttonStandartWidth;
        buttons[i].height = buttonStandartHeight;
        buttons[i].New();
    }
}

void display()
{
	if (false == isGameOver)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		DrawField();

		DrawSnake();

		for (int i=0; i < numberOfApples; i++)
		{
			m[i].DrawApple();
		}

        // draw menu buttons at the top of field
        drawMenuButtons();

        // function glFlush() is not nesecarry for mode GLUT_DOUBLE but must be for mode GLUT_SINGLE
        // see initialize in main: glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB );
		//glFlush();

		// If the mode in use is not double buffered, glutSwapBuffers has no effect
		glutSwapBuffers();
	}
}

void KeyboardEvent(int key, int a, int b)
{
	switch(key)
	{
	case 101 : // arrow up on keyboard
		{
            if (dir != 3 && true == wasDrawn)
			{
				dir=0;
				wasDrawn = false;
			}
			break;
		}
	case 102 : // arrow right on keyboard
		{
            if (dir != 1 && true == wasDrawn)
            {
				dir=2;
				wasDrawn = false;
			}
			break;
		}
	case 100 : // arrow left on keyboard
		{
			if (dir != 2 && true == wasDrawn)
			{
				dir=1;
				wasDrawn = false;
			}
			break;
		}
	case 103 : // arrow down on keyboard
		{
			if (dir != 0 && true == wasDrawn)
			{
				dir=3;
				wasDrawn = false;
			}
			break;
		}
	}
}

void timer(int = 0)
{
	display();

	Tick();

	glutTimerFunc(speedDelay,timer,0);
}

bool checkButtonClick(MenuButton * btn, int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON &&
		x > btn->x && x < btn->x+btn->width &&
		y > (h - (btn->y + btn->height)) && y < ((h - btn->y)))
	{
		if (state == 1) // mouse button was released up
		{
			btn->stateOfButton = 0;
			btn->onClickFunction(btn->x);
			return true;
		} else // click of mouse button
		{
			btn->stateOfButton = 1;
			return true;
		}
	} else
	{
		btn->stateOfButton = 0;
		return false;
	}
}

void OnMouseClick(int button, int state, int x, int y)
{
	for (int i = 0; i < numberOfMenuButtons; i++)
	{
		bool result = checkButtonClick(&buttons[i], button, state, x, y);
		if (true == result)
		{
			break;
		}
	}
}

void about()
{
	glColor3f(colorRedOfStatsBackground, colorGreenOfStatsBackground, colorBlueOfStatsBackground);
	glRectf(0, 0, Scale * N, Scale * M);
	displayText(N/2*Scale - 2 * Scale, M/2*Scale + 4 * Scale,
             colorRedOfStatsText, colorGreenOfStatsText, colorBlueOfStatsText, "Author");
	displayText(N/2*Scale - 2 * Scale, M/2*Scale + 2 * Scale,
             colorRedOfStatsText, colorGreenOfStatsText, colorBlueOfStatsText, authorName);
	displayText(N/2*Scale - 2 * Scale, M/2*Scale,
             colorRedOfStatsText, colorGreenOfStatsText, colorBlueOfStatsText, year);
	glFlush();
	glutSwapBuffers();
}

void gameOver()
{
	glColor3f(colorRedOfButton, colorGreenOfButton, colorBlueOfButton);
	glRectf(Scale * (N/2 - 4), Scale * (M/2 - 2),
         Scale * (N/2 - 4) + Scale * 8 ,  Scale * (M/2 - 2) + Scale * 4);//GL_COLOR_BUFFER_BIT);
	displayText(N/2*Scale - 24*3, M/2*Scale,
             colorRedOfButtonText, colorGreenOfButtonText, colorBlueOfButtonText, gameOverText);
	glFlush();
	glutSwapBuffers();
}

void onNewGameButtonClick(int)
{
	//glutSetWindowTitle("New game press");
	time_t now;
	time(&now);

	startGame = localtime(&now);

	isGameOver = false;
	num = 4;
}
void onPauseButtonClick(int)
{
	isGameOver = !isGameOver;
    if (isGameOver == true)
    {
        glutSetWindowTitle("Pause");
    } else
    {
        glutSetWindowTitle("Zmeika");
    }
}
void onStatsButtonClick(int)
{
	isGameOver = !isGameOver;
	if (isGameOver == true)
    {
        glutSetWindowTitle("Statistics");
    } else
    {
        glutSetWindowTitle("Zmeika");
    }
	time_t now = time(0);

	glColor3f(colorRedOfStatsBackground, colorGreenOfStatsBackground, colorBlueOfStatsBackground);
	glRectf(N/2*Scale - statPanelWidth/2, M * Scale - statPanelHeight,
         N/2*Scale - statPanelWidth/2 + statPanelWidth,
         M * Scale - statPanelHeight + statPanelHeight);

	double seconds;
	seconds = difftime(now, mktime(startGame));
	char minutesStr[20];
	int minutes = int(round(seconds))/60;
	int sec = int(round(seconds))%60;
	sprintf(minutesStr, "Time: %02i : %02i", minutes, sec);

	char stat1[20];
	sprintf(stat1, "Length: %i", num);

	char speedStr[20];
	sprintf(speedStr, "Speed: %i", speedDelay);

	//char sizeOfField[20];
	//sprintf(sizeOfField, "Size of field: %ix%i", N, M);

	displayText(N/2*Scale - 2 * Scale,  M * Scale - Scale,
             colorRedOfStatsText, colorGreenOfStatsText, colorBlueOfStatsText, stat1);
	displayText(N/2*Scale - 2 * Scale,  M * Scale - 3 * Scale,
             colorRedOfStatsText, colorGreenOfStatsText, colorBlueOfStatsText, minutesStr);
	displayText(N/2*Scale - 2 * Scale,  M * Scale - 5 * Scale,
             colorRedOfStatsText, colorGreenOfStatsText, colorBlueOfStatsText, speedStr);
    //displayText(N/2 * Scale - 2 * Scale,  M * Scale - 7 * Scale,
    //         colorRedOfStatsText, colorGreenOfStatsText, colorBlueOfStatsText, sizeOfField);
	glFlush();
	glutSwapBuffers();
}

void onExitButtonClick(int)
{
	glutSetWindowTitle("Exit");
	exit(0);
}

void onAboutButtonClick(int)
{
	isGameOver = !isGameOver;
	if (isGameOver == true)
    {
        glutSetWindowTitle("About");
    } else
    {
        glutSetWindowTitle("Zmeika");
    }
	about();
}

void initializeButtons()
{
	void (*onClickFunctionArray[])(int) = {&onNewGameButtonClick,
                                            &onPauseButtonClick,
                                            &onStatsButtonClick,
                                            &onExitButtonClick,
                                            &onAboutButtonClick};
	for (int i = 0; i < numberOfMenuButtons; i++)
	{
		buttons[i].stateOfButton = 0;
		buttons[i].nameOfButton = arrayOfStrings[i];

		buttons[i].onClickFunction = onClickFunctionArray[i];
	}
}
