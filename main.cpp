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
//#include "menubutton.h"
//static int slices = 16;
//static int stacks = 16;

void gameOver();
void initializeButtons();
void DrawSnake();
void Tick();
void DrawField();
void display();
void KeyboardEvent(int key, int a, int b);
void timer(int);
void OnMouseClick(int button, int state, int x, int y);

/* GLUT callback Handlers */

class Fruct m[numberOfApples];
class MenuButton
{
    public:
        int x, y;
        int width, height;
        int stateOfButton;
        const char * nameOfButton;
        void (*onClickFunction)(int);

        MenuButton(){};

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
        glRasterPos2f( x + spacing, y + spacing);
        for( int i = 0; nameOfButton[i] > 0; i++ )
        {
            glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, nameOfButton[i] );
        }
    }
} buttons[numberOfMenuButtons];;

int main(int argc, char *argv[])
{
    srand(time(0));
    int i;
    for (i=0;i<10;i++)
        m[i].New();

     s[i].x=10;
     s[i].y=10;

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize (w, h-menuPaneHeight);
    glutCreateWindow ("Test");
    glClearColor(1.0, 1.0, 0.6, 1.0);  //background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    initializeButtons();
    time_t now;

    time(&now);  /* get current time; same as: now = time(NULL)  */

    startGame = localtime(&now);

    glutDisplayFunc (display);
    glutSpecialFunc(KeyboardEvent);
    glutTimerFunc(speedDelay, timer, 0);
    glutMouseFunc(OnMouseClick);

    glutMainLoop();
}

void displayText( float x, float y, int r, int g, int b, const char *string )
{
    int j = strlen( string );

    glColor3f(r/255.0, g/255.0, b/255.0);
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
}

void DrawSnake()
{
    glColor3f(colorRedOfHeadSnake, colorGreenOfHeadSnake, colorBlueOfHeadSnake);

    int headNumber = 1;
    for (int i = 0; i < headNumber; i++)
    {
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
    glutSetWindowTitle(gameOverText);
}

 void Tick()
 {
    if (false == isGameOver)
    {
        for (int i=num;i>0;--i)
        {s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;}

        if (dir==0) s[0].y+=1;
        if (dir==1) s[0].x-=1;
        if (dir==2) s[0].x+=1;
        if (dir==3) s[0].y-=1;

        for (int i=0; i<numberOfApples; i++)
        {
            if ((s[0].x == m[i].x) && (s[0].y == m[i].y))
            {
                num++;
                m[i].New();
            }
        }

        if (s[0].x>N-1) s[0].x = 0;  if (s[0].x<0) s[0].x = N-1;
        if (s[0].y>M-1) s[0].y = 0;  if (s[0].y<0) s[0].y = M-1;

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

        for (int i=0; i < numberOfMenuButtons; i++)
        {
            buttons[i].x = spacingBetweenButtons + i * (buttonStandartWidth + spacingBetweenButtons);
            buttons[i].y = (M + 1) * Scale;
            buttons[i].width = buttonStandartWidth;
            buttons[i].height = buttonStandartHeight;
            buttons[i].New();
        }

        glFlush();
        glutSwapBuffers();
    }
}



void changeOppositeDirection()
{

    for (int i = 0; i < num/2; i++)
    {
        int temp = s[i].x;
        s[i].x = s[num-1-i].x;
        s[num-1-i].x = temp;
        temp = s[i].y;
        s[i].y = s[num-1-i].y;
        s[num-1-i].y = temp;
    }
}

void KeyboardEvent(int key, int a, int b)
{
    switch(key)
    {
        case 101 :
            {
                if (dir == 3)
                {
                    //changeOppositeDirection();
                } else
                {
                    if (true == wasDrawn)
                    {
                        dir=0;
                        wasDrawn = false;
                    }

                }

                break;
            }
        case 102 :
            {
                if (dir == 1)
                {
                    //changeOppositeDirection();
                } else
                {
                    if (true == wasDrawn)
                    {
                        dir=2;
                        wasDrawn = false;
                    }
                }

                break;
            }
        case 100 :
            {
                if (dir == 2)
                {
                    //changeOppositeDirection();
                } else
                {
                    if (true == wasDrawn)
                    {
                        dir=1;
                        wasDrawn = false;
                    }
                }

                break;
            }
        case 103 :
            {
                if (dir == 0)
                {
                    //changeOppositeDirection();
                } else
                {
                    if (true == wasDrawn)
                    {
                        dir=3;
                        wasDrawn = false;
                    }
                }

                break;
            }
    }
}

void timer(int = 0)
{
    display();

    Tick();

    //disableZbuffer();
    //drawCursor();

    glutTimerFunc(speedDelay,timer,0);
}

bool checkButtonClick(MenuButton * btn, int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON &&
        x > btn->x && x < btn->x+btn->width &&
         y > (h - (btn->y + btn->height)) && y < ((h - btn->y)))
    {
        if (state == 1)
        {
            //const char * str = "pppress up";
            btn->stateOfButton = 0;
            //glutSetWindowTitle(str);
            btn->onClickFunction(btn->x);
            return true;
        } else
        {
            const char * str = "down";
            btn->stateOfButton = 1;
            glutSetWindowTitle(str);
            return true;
        }
    } else
    {
        const char * str = "out";
        glutSetWindowTitle(str);
        btn->stateOfButton = 0;
        return false;
    }
}

void OnMouseClick(int button, int state, int x, int y)
{
 // for all active buttons
 //   if point(x,y) is inside button
 //     DoSomeButtonAction()
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
    glColor3f(255, 255, 255*10/6);
    glRectf(0, 0, Scale * N, Scale * M);//GL_COLOR_BUFFER_BIT);
    displayText(N/2*Scale, M/2*Scale, 105, 255, 255*10/6, "About");
    glFlush();
    glutSwapBuffers();
}

void gameOver()
{
    glColor3f(colorRedOfButton, colorGreenOfButton, colorBlueOfButton);
    glRectf(Scale * (N/2 - 4), Scale * (M/2 - 2), Scale * (N/2 - 4) + Scale * 8 ,  Scale * (M/2 - 2) + Scale * 4);//GL_COLOR_BUFFER_BIT);
    displayText(N/2*Scale - 24*3, M/2*Scale, colorRedOfButtonText, colorGreenOfButtonText, colorBlueOfButtonText, gameOverText);
    glFlush();
    glutSwapBuffers();
}

void onNewGameButtonClick(int)
{
    glutSetWindowTitle("New game press");
    time_t now;

    double seconds;

    time(&now);  /* get current time; same as: now = time(NULL)  */

    startGame = localtime(&now);

    seconds = difftime(now,mktime(startGame));

    //int secondsStart = now->tm_sec;
    char minutesStr[5];
    sprintf(minutesStr, "%f",  seconds);
    glutSetWindowTitle(minutesStr);

    isGameOver = false;
    num = 4;
}
void onPauseButtonClick(int)
{
    glutSetWindowTitle("Pause press");
    isGameOver = !isGameOver;
}
void onStatsButtonClick(int)
{
    isGameOver = !isGameOver;
    glutSetWindowTitle("Stats press");

    time_t now = time(0);

    char differenceStr[5];

    glutSetWindowTitle(differenceStr);

    glColor3f(255, 20, 255*10/6);
    glRectf(N/2*Scale - statPanelWidth/2, M * Scale - statPanelHeight, N/2*Scale - statPanelWidth/2 + statPanelWidth, M * Scale - statPanelHeight + statPanelHeight);//GL_COLOR_BUFFER_BIT);

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

    displayText(N/2*Scale - 2*Scale,  M * Scale - Scale, 40, 100, 255*10/6, stat1);
    displayText(N/2*Scale - 2*Scale,  M * Scale - 3*Scale, 40, 100, 255*10/6, minutesStr);
    displayText(N/2*Scale - 2*Scale,  M * Scale - 5*Scale, 40, 100, 255*10/6, speedStr);
    glFlush();
    glutSwapBuffers();
}
void onExitButtonClick(int)
{
    glutSetWindowTitle("Exit press");
    exit(0);
}
void onAboutButtonClick(int)
{
    glutSetWindowTitle("About press");
    isGameOver = !isGameOver;
    about();
}

void initializeButtons()
{
    void (*onClickFunctionArray[])(int) = {&onNewGameButtonClick, &onPauseButtonClick, &onStatsButtonClick, &onExitButtonClick, &onAboutButtonClick};
    for (int i = 0; i < numberOfMenuButtons; i++)
    {
        buttons[i].stateOfButton = 0;
        buttons[i].nameOfButton = arrayOfStrings[i];
        glutSetWindowTitle(buttons[i].nameOfButton);

        buttons[i].onClickFunction = onClickFunctionArray[i];
    }
}


