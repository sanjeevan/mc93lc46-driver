#include "WProgram.h"
#include "mc93lc46.h"

extern "C" void __cxa_pure_virtual() {
	cli();
	for (;;)
		;
}

void setup() {
	mc93lc46_setup();
	pinMode(9, OUTPUT);
}

void loop() {
	unsigned int x = 0;

	mc93lc46_write(98, 100);

	while (1){

		x = mc93lc46_read(98);

		if (x == 100){
			digitalWrite(8, HIGH);
			delay(15);
			digitalWrite(8, LOW);
			delay(15);
		}

		delay(10);
	}
}

int main(void) {
	init();
	setup();

	for (;;) {
		loop();
	}
}

