#include "constants.h"

int menuPaneHeight = 66;
int N = 20, M = 20;
int Scale=30;
int statPanelWidth = Scale * 10;
int statPanelHeight = Scale * 6;

int speedDelay = 50;
bool isGameOver = false;
bool wasDrawn = false;

int w = Scale*N;
int h = Scale*M+menuPaneHeight;

int minutesStart = 0;
int secondsStart = 0;
int minutesFinish = 0;
int secondsFinish = 0;

int spacingBetweenButtons = 1;
int buttonStandartWidth = w/numberOfMenuButtons - spacingBetweenButtons;
int buttonStandartHeight = 40;
const char * arrayOfStrings[] = {"New", "Pause", "Stats", "Exit", "About"};
char gameOverText[] = "GAME OVER";

const char * authorName = "Denis Fominyh";
const char * year = "2013";

int dir = 0; // one of the option from: up, right, left, down
int num = 4; // length of snake
time_t timeOfPlay;
struct tm * startGame;
struct tm * pauseGame;

struct coords s[maxLengthOfSnake];

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

double colorRedOfStatsText = 40;
double colorGreenOfStatsText = 100;
double colorBlueOfStatsText = 64;

double colorRedOfStatsBackground = 220;
double colorGreenOfStatsBackground = 220;
double colorBlueOfStatsBackground = 220;
