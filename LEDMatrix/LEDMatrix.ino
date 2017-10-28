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
	buffer[((LED_x * LED_y) / (LED_x * y)) +x] = true;
}

void writeLine(int x, int y, int x2, int y2) {

}