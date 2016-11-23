#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<ctime>

using namespace std;

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

//0 = sky blue
//1 = red
//2 = brown
//3 = skin
//4 = black
//5 = blue
//6 = dirt brown
//7 = brick brown
//8 = orange
//9 = yellow
COLORREF colors[] = { RGB(79, 172, 255), RGB(198, 0, 13), RGB(145, 70, 20),
					RGB(247, 204, 143), RGB(0, 0, 0), RGB(2, 18, 237),
					RGB(94, 73, 52), RGB(168, 109, 0), RGB(252, 166, 7),
					RGB(243, 255, 30)};

int marioStanding[16][16] = 
	{ {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 3, 3, 4, 3, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 3, 2, 3, 3, 3, 4, 3, 3, 3, 0, 0, 0 },
	{ 0, 0, 0, 2, 3, 2, 2, 3, 3, 3, 4, 3, 3, 3, 0, 0 },
	{ 0, 0, 0, 0, 2, 3, 3, 3, 3, 4, 4, 4, 4, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 5, 1, 1, 5, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 5, 1, 1, 5, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 5, 5, 5, 5, 1, 1, 1, 1, 0, 0 },
	{ 0, 0, 3, 3, 1, 5, 3, 5, 5, 3, 5, 1, 3, 3, 0, 0 },
	{ 0, 0, 3, 3, 3, 5, 5, 5, 5, 5, 5, 3, 3, 3, 0, 0 },
	{ 0, 0, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 0, 0 },
	{ 0, 0, 0, 0, 5, 5, 5, 0, 0, 5, 5, 5, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0 } 
};

int marioJumping[16][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3},
	{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 3, 3, 3},
	{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3},
	{0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 4, 3, 0, 1, 1, 1},
	{0, 0, 0, 0, 2, 3, 2, 3, 3, 3, 4, 3, 3, 1, 1, 1},
	{0, 0, 0, 0, 2, 3, 2, 2, 3, 3, 3, 4, 3, 3, 3, 1},
	{0, 0, 0, 0, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 1, 0},
	{0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 5, 1, 1, 1, 5, 1, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 5, 0, 0, 0},
	{3, 3, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 0, 0, 2},
	{3, 3, 3, 0, 5, 5, 1, 5, 5, 3, 5, 5, 3, 5, 2, 2},
	{0, 3, 0, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2},
	{0, 0, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2},
	{0, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0},
	{0, 2, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0} 
};

int groundBrick[16][16] = {
	{ 6, 3, 3, 3, 3, 3, 3, 3, 3, 4, 6, 3, 3, 3, 3, 6 },
	{ 3, 6, 6, 6, 6, 6, 6, 6, 6, 4, 3, 6, 6, 6, 6, 3 },
	{ 3, 6, 6, 6, 6, 6, 6, 6, 6, 4, 3, 6, 6, 6, 6, 3 },
	{ 3, 6, 6, 6, 6, 6, 6, 6, 6, 4, 3, 6, 6, 6, 6, 3 },
	{ 3, 6, 6, 6, 6, 6, 6, 6, 6, 4, 3, 4, 6, 6, 6, 3 },
	{ 3, 6, 6, 6, 6, 6, 6, 6, 6, 4, 6, 4, 4, 4, 4, 6 },
	{ 3, 6, 6, 6, 6, 6, 6, 6, 6, 4, 3, 3, 3, 3, 3, 4 },
	{ 3, 6, 6, 6, 6, 6, 6, 6, 6, 4, 3, 6, 6, 6, 6, 4 },
	{ 3, 6, 6, 6, 6, 6, 6, 6, 6, 4, 3, 6, 6, 6, 6, 4 },
	{ 3, 6, 6, 6, 6, 6, 6, 6, 6, 4, 3, 6, 6, 6, 6, 4 },
	{ 4, 4, 6, 6, 6, 6, 6, 6, 4, 3, 6, 6, 6, 6, 6, 4 },
	{ 3, 3, 4, 4, 6, 6, 6, 6, 4, 3, 6, 6, 6, 6, 6, 4 },
	{ 3, 6, 3, 3, 4, 4, 4, 4, 3, 6, 6, 6, 6, 6, 6, 4 },
	{ 3, 6, 6, 6, 3, 3, 3, 4, 3, 6, 6, 6, 6, 6, 6, 4 },
	{ 3, 6, 6, 6, 6, 6, 6, 4, 3, 6, 6, 6, 6, 6, 4, 4 },
	{ 6, 4, 4, 4, 4, 4, 4, 6, 4, 4, 4, 4, 4, 4, 4, 6 }
};

int breakableBrick[16][16] = {
	{ 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4 },
	{ 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4 },
	{ 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7 },
	{ 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7 },
	{ 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4 },
	{ 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4 },
	{ 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7 },
	{ 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7 },
	{ 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
};

int bonusBrick[16][16] = {
	{ 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4 },
	{ 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4 },
	{ 8, 9, 4, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 9, 4 },
	{ 8, 9, 9, 9, 9, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 4 },
	{ 8, 9, 9, 9, 8, 8, 4, 4, 4, 8, 8, 9, 9, 9, 9, 4 },
	{ 8, 9, 9, 9, 8, 8, 4, 9, 9, 8, 8, 4, 9, 9, 9, 4 },
	{ 8, 9, 9, 9, 8, 8, 4, 9, 9, 8, 8, 4, 9, 9, 9, 4 },
	{ 8, 9, 9, 9, 9, 4, 4, 9, 8, 8, 8, 4, 9, 9, 9, 4 },
	{ 8, 9, 9, 9, 9, 9, 9, 8, 8, 4, 4, 4, 9, 9, 9, 4 },
	{ 8, 9, 9, 9, 9, 9, 9, 8, 8, 4, 9, 9, 9, 9, 9, 4 },
	{ 8, 9, 9, 9, 9, 9, 9, 9, 4, 4, 9, 9, 9, 9, 9, 4 },
	{ 8, 9, 9, 9, 9, 9, 9, 8, 8, 9, 9, 9, 9, 9, 9, 4 },
	{ 8, 9, 9, 9, 9, 9, 9, 8, 8, 4, 9, 9, 9, 9, 9, 4 },
	{ 8, 9, 4, 9, 9, 9, 9, 9, 4, 4, 9, 9, 9, 4, 9, 4 },
	{ 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
};

void drawBiggerPixel(HDC mydc, int x, int y, COLORREF color) {
	for (int i = x; i < x + 4; i++) {
		for (int j = y; j < y + 4; j++) {
			SetPixel(mydc, j, i, color);
		}
	}
}

void drawBackground(HDC mydc) {
	for (int b = 0; b < 465; b += 64) {
		for (int a = 0; a < 1200; a += 64) {
			for (int i = b, k = 0; i < b + 64; i += 4, k++) {
				for (int j = a, h = 0; j < a + 64; j += 4, h++) {
					drawBiggerPixel(mydc, i, j, colors[0]);
				}
			}
		}
	}
	for (int b = 0; b < 2; b++) {
		for (int a = 0; a < 1200; a += 64) {
			for (int i = 465 + b * 64, k = 0; i < 465 + ((b + 1) * 64); i += 4, k++) {
				for (int j = a, h = 0; j < a + 64; j += 4, h++) {
					drawBiggerPixel(mydc, i, j, colors[groundBrick[k][h]]);
				}
			}
		}
	}
	for(int a = 0; a < 5; a++){
		for (int i = 280, k = 0; i < 344; i += 4, k++) {
			for (int j = 400 + a * 64, h = 0; j < 464 + a * 64; j += 4, h++) {
				drawBiggerPixel(mydc, i, j, colors[breakableBrick[k][h]]);
			}
		}
	}
	for (int i = 280, k = 0; i < 344; i += 4, k++) {
		for (int j = 400 + 3 * 64, h = 0; j < 464 + 3 * 64; j += 4, h++) {
			drawBiggerPixel(mydc, i, j, colors[bonusBrick[k][h]]);
		}
	}
	for (int i = 0; i < 32; i += 4) {
		for (int j = 0; j < 64; j += 4) {
			drawBiggerPixel(mydc, i, j, colors[0]);
		}
	}
}

void drawMarioStanding(HDC mydc, int x, int y, int side) {
	if (side == 1) {
		for (int i = x, k = 0; i < x + 64; i += 4, k++) {
			for (int j = y, h = 0; j < y + 64; j += 4, h++) {
				drawBiggerPixel(mydc, i, j, colors[marioStanding[k][h]]);
			}
		}
	}
	else {
		for (int i = x, k = 0; i < x + 64; i += 4, k++) {
			for (int j = y, h = 15; j < y + 64; j += 4, h--) {
				drawBiggerPixel(mydc, i, j, colors[marioStanding[k][h]]);
			}
		}
	}
}

void drawMarioJumping(HDC mydc, int x, int y, int side) {
	if (side == 1) {
		for (int i = x, k = 0; i < x + 64; i += 4, k++) {
			for (int j = y, h = 0; j < y + 64; j += 4, h++) {
				drawBiggerPixel(mydc, i, j, colors[marioJumping[k][h]]);
			}
		}
	}
	else {
		for (int i = x, k = 0; i < x + 64; i += 4, k++) {
			for (int j = y, h = 15; j < y + 64; j += 4, h--) {
				drawBiggerPixel(mydc, i, j, colors[marioJumping[k][h]]);
			}
		}
	}
}

void clearMario(HDC mydc, int x, int y) {
	for (int i = x; i < x + 64; i += 4) {
		for (int j = y; j < y + 64; j += 4) {
			drawBiggerPixel(mydc, i, j, colors[0]);
		}
	}
}

bool equalColors(COLORREF color1, COLORREF color2) {
	return (GetRValue(color1) == GetRValue(color2) && GetGValue(color1) == GetGValue(color2) && GetBValue(color1) == GetBValue(color2));
}

void jump(HDC mydc, int& x, int& y, int& side) {
	clock_t startTime = clock(); //Start timer
	double timePassed;
	double timeToDelay = 45;
	int jumpChange = 44;
	int flag = 1;
	int c;
	COLORREF singlePixelColor = colors[0];
	while (flag) {

		timePassed = clock() - startTime;
		if (timePassed >= timeToDelay) {
			clearMario(mydc, x, y);
			jumpChange -= 4;
			x -= jumpChange;
			//jumpChange == -40
			//if (jumpChange <= 0 && !equalColors(singlePixelColor, colors[0])) {
			if (jumpChange == -40) {
				drawMarioStanding(mydc, x, y, side);
				flag = 0;
			}
			else {
				drawMarioJumping(mydc, x, y, side);
				singlePixelColor = GetPixel(mydc, x, y);
				startTime = clock();
			}
		}
		c = 0;
		if (_kbhit()) {
			switch ((c = _getch())) {
			case ARROW_LEFT:
				clearMario(mydc, x, y);
				y -= 10;
				side = 2;
				break;
			case ARROW_RIGHT:
				clearMario(mydc, x, y);
				y += 10;
				side = 1;
				break;
			default:
				break;
			}
		} 
	}
}

int main() {

	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	//COORD coords = {};
	//coords.X = 5000;
	//coords.Y = 5000;
	//SetConsoleScreenBufferSize(myconsole, coords);
	//COLORREF singlePixelColor;

	int side = 1;

	drawBackground(mydc);
	drawMarioStanding(mydc, 400, 100, side);
	int c;
	int x = 400;
	int y = 100;
	while (true) {
		c = 0;
		switch ((c = _getch())) {
		case ARROW_UP:
			clearMario(mydc, x, y);
			//x -= 10;
			//drawMarioJumping(mydc, x, y
			jump(mydc, x, y, side);
			break;
		case ARROW_DOWN:
			//clearMario(mydc, x, y);
			//x += 10;
			//drawMarioStanding(mydc, x, y);
			break;
		case ARROW_LEFT:
			clearMario(mydc, x, y);
			y -= 10;
			side = 2;
			drawMarioStanding(mydc, x, y, side);
			break;
		case ARROW_RIGHT:
			clearMario(mydc, x, y);
			y += 10;
			side = 1;
			drawMarioStanding(mydc, x, y, side);
			break;
		default:
			break;
		}

	}


	//ReleaseDC(myconsole, mydc);
	//cin.ignore();
	//main();
	return 0;
}