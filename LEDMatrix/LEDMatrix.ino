const int LED_x = 24;
const int LED_y = 40;

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

void writeDot(int x, int y) {
	if (x < 0 || y < 0 || x > LED_x || y > LED_y) {
		return;
	}

	buffer[(LED_x * y) + x] = true;
}

void writeRect(int x, int y, int x2, int y2) {
	int len_x = x2 - x;
	int len_y = y2 - y;

	if (x < 0 || y < 0 || x > LED_x || y > LED_y || x2 < 0 || y2 < 0
		|| x2 > LED_x || y2 > LED_y || x2 < x || y2 < y) {
		return;
	}

	for (int i = x; i <= x2; i++) {
		if (i > LED_x)
			break;

		writeDot(i, y);
		writeDot(i, y2);
	}
	for (int n = y; n <= y2; n++) {
		if (n > LED_y)
			break;
		writeDot(x, n);
		writeDot(x2, n);
	}

}
