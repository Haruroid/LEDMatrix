#include <avr/pgmspace.h>
#include "Objects.h"

#define DEBUG

const int LED_x = 43;
const int LED_y = 58;

bool buffer[LED_x * LED_y];

void setup()
{
	/* add setup code here */
	for (int i = 0; i < (LED_x * LED_y); i++) {
		buffer[i] = false;
	}
#ifdef DEBUG
	Serial.begin(9600);
#endif
	writeObject(0, 0, test);
}

void loop()
{

	/* add main program code here */
}

/*
x:X
y:Y
on:点灯or消灯
*/
void writeDot(int x, int y, bool on) {
	if (x < 0 || y < 0 || x > LED_x || y > LED_y)
		return;
	buffer[(LED_x * y) + x] = on;
#ifdef DEBUG
	char str[255];
	sprintf(str, "(%d,%d)%d", x, y, on);
	Serial.println(str);
#endif // DEBUG

}

/*
x:開始地点X
y:開始地点Y
x2:終了地点X
y2:終了地点Y
on:点灯or消灯
*/
void writeRect(int x, int y, int x2, int y2, bool on) {
	if (x < 0 || y < 0 || x > LED_x || y > LED_y || x2 < 0 || y2 < 0
		|| x2 > LED_x || y2 > LED_y || x2 < x || y2 < y)
		return;

	for (int i = x; i <= x2; i++) {
		if (i > LED_x)
			break;
		writeDot(i, y, on);
		writeDot(i, y2, on);
	}
	for (int n = y; n <= y2; n++) {
		if (n > LED_y)
			break;
		writeDot(x, n, on);
		writeDot(x2, n, on);
	}
}

/*
x:開始地点X
y:開始地点Y
dat:データ配列uint16_t[]
*/
void writeObject(int x, int y, const uint16_t *dat) {
	if (x < 0 || x> LED_x || y < 0 || y>LED_y)
		return;
	int x_len = pgm_read_dword_near(&dat[0]) -1;
	int y_len = pgm_read_dword_near(&dat[1]) -1;
#ifdef DEBUG
	char str[255];
	sprintf(str, "x_len:%d,y_len:%d", x_len, y_len);
	Serial.println(str);
#endif // DEBUG

	if (x_len <= 0 || y_len <= 0)
		return;
	for (int n = y; n <= y_len + y; n++) {
		for (int i = x; i <= x_len + x; i++) {
#ifdef DEBUG
			char st[255];
			sprintf(st, "dat[%d]: %d", (x_len + 1) * (n - y) + (i - x) + 2, (int)pgm_read_dword_near(&dat[(x_len + 1) * (n - y) + (i - x) + 2]));
			Serial.println(st);
#endif // DEBUG
			bool t_dat = (int)pgm_read_dword_near(&dat[(x_len + 1) * (n - y) + (i - x) + 2]) == 1;
			writeDot(i, n, t_dat);
		}
	}
}