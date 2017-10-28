const int LED_x = 43;
const int LED_y = 58;

bool buffer[LED_x * LED_y];

void setup()
{
	/* add setup code here */
	for (int i = 0; i < (LED_x * LED_y); i++) {
		buffer[i] = false;
	}
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
dat_x:xの長さ
dat_y:yの長さ
dat:データ配列bool[]
*/
void writeObject(int x, int y, int dat_x, int dat_y, bool *dat) {
	if (x < 0 || x> LED_x || y < 0 || y>LED_y || dat_x < 0 || dat_y < 0)
		return;
	for (int n = y; n <= dat_y; n++) {
		for (int i = x; i <= dat_x; i++) {
			writeDot(x, n, dat[(dat_x * (n - y)) + (i - x)]);
		}
	}
}