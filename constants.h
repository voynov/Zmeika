#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <ctime>
#define maxLengthOfSnake 100
#define numberOfMenuButtons 5
#define numberOfApples 1

extern int menuPaneHeight;
extern int N, M;
extern int Scale;
extern int statPanelWidth;
extern int statPanelHeight;

extern int speedDelay;
extern bool isGameOver;
extern bool wasDrawn;

extern int w;
extern int h;

extern int minutesStart;
extern int secondsStart;
extern int minutesFinish;
extern int secondsFinish;

extern int spacingBetweenButtons;
extern int buttonStandartWidth;
extern int buttonStandartHeight;
extern char arrayOfStrings[numberOfMenuButtons][100];
extern char gameOverText[10];

extern int dir, num;
extern time_t timeOfPlay;
extern struct tm * startGame;
extern struct tm * pauseGame;

extern struct coords {
    int x;
    int y;
}  s[maxLengthOfSnake];
//const extern int numberOfApples;
//const extern int maxLengthOfSnake;
extern double sizeCoefficient;
extern double sizeCoefficientOfApple;

extern double colorRedOfApple;
extern double colorGreenOfApple;
extern double colorBlueOfApple;

extern double colorRedOfSnake;
extern double colorGreenOfSnake;
extern double colorBlueOfSnake;

extern double colorRedOfHeadSnake;
extern double colorGreenOfHeadSnake;
extern double colorBlueOfHeadSnake;

extern double colorRedOfLines;
extern double colorGreenOfLines;
extern double colorBlueOfLines;

extern double colorRedOfButton;
extern double colorGreenOfButton;
extern double colorBlueOfButton;

extern double colorRedOfSelectedButton;
extern double colorGreenOfSelectedButton;
extern double colorBlueOfSelectedButton;

extern double colorRedOfButtonText;
extern double colorGreenOfButtonText;
extern double colorBlueOfButtonText;


#endif // CONSTANTS_H_INCLUDED
