/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
//#include <windows.h>
#include <time.h>
#include <string.h>

//#include <GLUT/glut.h>
#include <GL/glut.h>

#include <ctime>
#include <stdlib.h>
#include <stdio.h>

//static int slices = 16;
//static int stacks = 16;

void gameOver();

/* GLUT callback Handlers */
int menuPaneHeight = 100.0;
int N = 30, M = 20;
int Scale=25;

int speedDelay = 50;
bool isGameOver = false;
bool wasDrawn = false;

int w = Scale*N;
int h = Scale*M+menuPaneHeight;

const int numberOfMenuButtons = 5;
int spacingBetweenButtons = 1;
int buttonStandartWidth = (w-spacingBetweenButtons)/numberOfMenuButtons - spacingBetweenButtons;
int buttonStandartHeight = 40;
char arrayOfStrings[numberOfMenuButtons][100] = {"New", "Pause", "Stats", "Exit", "About"};
char gameOverText[] = "GAME OVER";

int dir,num=4;
time_t timeOfPlay;
struct tm * startGame;
struct tm * pauseGame;

const int numberOfApples = 10;
const int maxLengthOfSnake = 100;
double sizeCoefficient = 0.9;
double sizeCoefficientOfApple = 0.97;

double colorRedOfApple = 0.8;
double colorGreenOfApple = 0.1;
double colorBlueOfApple = 0.1;

double colorRedOfSnake = 0.0;
double colorGreenOfSnake = 0.0;
double colorBlueOfSnake = 1.0;

double colorRedOfHeadSnake = 0.0;
double colorGreenOfHeadSnake = 1.0;
double colorBlueOfHeadSnake = 0.0;

double colorRedOfLines = 0.0;
double colorGreenOfLines = 0.7;
double colorBlueOfLines = 0.0;

double colorRedOfButton = 0.0;
double colorGreenOfButton = 0.7;
double colorBlueOfButton = 0.0;

double colorRedOfSelectedButton = 0.5;
double colorGreenOfSelectedButton = 0.9;
double colorBlueOfSelectedButton = 0.5;

double colorRedOfButtonText = 230;
double colorGreenOfButtonText = 310;
double colorBlueOfButtonText = 100;

struct coords
{
    int x;
    int y;
}  s[maxLengthOfSnake];

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

class Fructs
{
public:
    int x,y;

    void New()
    {
        x = rand() % N;
        y = rand() % M;

        for (int i = 0; i < num; i++)
        {
            coords aCoord  = s[i];

            if (x == aCoord.x && y == aCoord.y)
            {
                // incorrect position. Try the same function recursively
                New();
            }
        }
    }

    void DrawApple()
   {
       glColor3f(colorRedOfApple, colorGreenOfApple, colorBlueOfApple);
       glRectf(x*Scale, y*Scale,(x+sizeCoefficientOfApple)*Scale, (y+sizeCoefficientOfApple)*Scale);
    }

} m[numberOfApples];

 void DrawSnake()
 {
    glColor3f(colorRedOfHeadSnake, colorGreenOfHeadSnake, colorBlueOfHeadSnake);

    for (int i=0;i<num/2;i++)
    {
        glRectf(s[i].x * Scale, s[i].y * Scale, (s[i].x + sizeCoefficient)*Scale, (s[i].y + sizeCoefficient)*Scale);
    }

    glColor3f(colorRedOfSnake, colorGreenOfSnake, colorBlueOfSnake);

    for (int i=num/2;i<num;i++)
    {
        glRectf(s[i].x * Scale, s[i].y * Scale, (s[i].x + sizeCoefficient)*Scale, (s[i].y + sizeCoefficient)*Scale);
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

  //if (s[0].x>N-1) dir=1;  if (s[0].x<0) dir=2;
  //if (s[0].y>M-2) dir=3;  if (s[0].y<0) dir=0;

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

class MenuButton
{
public:
    int x, y;
    int width, height;
    int stateOfButton;
    char * nameOfButton;
    void (*onClickFunction)(int);

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
        displayText(x + spacing, y + spacing, colorRedOfButtonText, colorGreenOfButtonText, colorBlueOfButtonText, nameOfButton);
    }

} buttons[3];


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
    glRectf(0, 0, Scale * N, Scale * M);//GL_COLOR_BUFFER_BIT);
    displayText(N/2*Scale - 24*3, M/2*Scale, colorRedOfButtonText, colorGreenOfButtonText, colorBlueOfButtonText, gameOverText);
    glFlush();
    glutSwapBuffers();
}

void onNewGameButtonClick(int)
{
    glutSetWindowTitle("New game press");
    timeOfPlay = time(0);
    startGame = localtime( & timeOfPlay );
    char minutesStr[5];
    sprintf(minutesStr, "%i:%i", startGame->tm_min, startGame->tm_sec);
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
    glutSetWindowTitle("Stats press");
    time_t curTime = time(0);
    struct tm * now = localtime( & curTime );
    char minutesStr[5];
    sprintf(minutesStr, "%i:%i", now->tm_min /*- start->tm_min*/, now->tm_sec /*- start->tm_sec*/);
    glutSetWindowTitle(minutesStr);
    char differenceStr[5];
    //sprintf(differenceStr, "%i:%i", now->tm_min - startGame->tm_min, now->tm_sec - startGame->tm_sec);

    glutSetWindowTitle(differenceStr);
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

        buttons[i].onClickFunction = onClickFunctionArray[i];
    }
}

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
    glClearColor(1.0, 1.0, 0.6, 1.0);  //цвет фона
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    initializeButtons();
    glutDisplayFunc (display);
    glutSpecialFunc(KeyboardEvent);
    glutTimerFunc(speedDelay, timer, 0);
    glutMouseFunc(OnMouseClick);

    glutMainLoop();
}
