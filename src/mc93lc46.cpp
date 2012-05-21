#include "WProgram.h"
#include "mc93lc46.h"

void mc93lc46_setup() {

	DDRB |= _BV(0) | _BV(1) | _BV(2);
	DDRD |= _BV(6);
	DDRB &= ~_BV(7);
}

void mc93lc46_delay(unsigned int count) {
	while (count > 0) {
		count--;
	}
}

void mc93lc46_pulse(void) {

	PORTB |= _BV(2);
	mc93lc46_delay(10000);
	PORTB &= ~_BV(2);
}

void mc93lc46_start_bit(void) {
	digitalWrite(MC93LC46_PIN_CS, HIGH);
	digitalWrite(MC93LC46_PIN_DI, HIGH);

	mc93lc46_pulse();
}

void mc93lc46_ewen(void) {
	unsigned char i, temp;
	mc93lc46_start_bit();

	temp = 0x80;

	for (i = 0; i < 8; i++) {
		if (0x30 & temp) {
			digitalWrite(MC93LC46_PIN_DI, HIGH);
		} else {
			digitalWrite(MC93LC46_PIN_DI, LOW);
		}
		mc93lc46_pulse();
		temp >>= 1;
	}

	digitalWrite(MC93LC46_PIN_CS, LOW);
}

void mc93lc46_ewds(void) {
	unsigned char i;

	mc93lc46_start_bit();

	digitalWrite(MC93LC46_PIN_DI, LOW);

	for (i = 0; i < 8; i++) {
		mc93lc46_pulse();
	}

	digitalWrite(MC93LC46_PIN_CS, LOW);
}

void mc93lc46_write(unsigned char address, unsigned char data) {
	unsigned char i;
	unsigned int temp;

	address &= 0x3F; // mask include 6 bits from  LSB
	address += 0x40; // add op code
	temp = 0x80;

	mc93lc46_ewen();
	mc93lc46_start_bit();

	for (i = 0; i < 8; i++) {
		if (address & temp) {
			digitalWrite(MC93LC46_PIN_DI, HIGH);
		} else {
			digitalWrite(MC93LC46_PIN_DI, LOW);
		}
		mc93lc46_pulse();
		temp >>= 1;
	}

	temp = 0x80;

	for (i = 0; i < 8; i++) {
		if (data & temp) {
			digitalWrite(MC93LC46_PIN_DI, HIGH);
		} else {
			digitalWrite(MC93LC46_PIN_DI, LOW);
		}
		mc93lc46_pulse();
		temp >>= 1;
	}

	digitalWrite(MC93LC46_PIN_CS, LOW);

	mc93lc46_ewds();
}

unsigned int mc93lc46_read(unsigned char address) {
	unsigned char i, temp;
	unsigned char data = 0;

	temp = 0x80;
	address &= 0x3F;
	address += 0x80;

	mc93lc46_start_bit();

	for (i = 0; i < 8; i++) {
		if (address & temp) {
			digitalWrite(MC93LC46_PIN_DI, HIGH);
		} else {
			digitalWrite(MC93LC46_PIN_DI, LOW);
		}
		mc93lc46_pulse();
		temp >>= 1;
	}

	for (i = 0; i < 8; i++) {
		mc93lc46_pulse();

		if (digitalRead(MC93LC46_PIN_DO) == HIGH) {
			data |= 0x1;
		}
		if (i < 7) {
			data <<= 1;
		}
	}

	digitalWrite(MC93LC46_PIN_CS, LOW);

	return data;
}

