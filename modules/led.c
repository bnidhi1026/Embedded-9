/* includes */

#include "vxWorks.h"
#include <unistd.h>
#include <tasklib.h>
#include "../gpioLib/gpioLib.h"

#define PIN 16
#define STACK_SIZE 1000
TASK_ID t;
TASK_ID bt;
int stat = 0;
int count = 0;
int count2 = 0;

void blink() {
	pinMode(0, OUT);
	pinMode(1, OUT);
	pinMode(2, OUT);
	pinMode(3, OUT);
	pinMode(4, OUT);
	pinMode(5, OUT);
	pinMode(6, OUT);
	pinMode(7, OUT);
	gpioWrite(0, LOW);
	gpioWrite(1, LOW);
	gpioWrite(2, LOW);
	gpioWrite(3, LOW);
	gpioWrite(4, LOW);
	gpioWrite(5, LOW);
	gpioWrite(6, LOW);
	gpioWrite(7, LOW);
	while (1) {
		if (stat == 0) {
			printf("am first\n");
			gpioWrite(count, HIGH);
			sleep(1);
			gpioWrite(count, LOW);
			count = (count + 1) % 8;
		}
		if (stat == 1) {
			gpioWrite(count, HIGH);
			gpioWrite((count + 1) % 8, HIGH);
			sleep(1);
			gpioWrite(count, LOW);
			gpioWrite((count + 1) % 8, LOW);
			count = (count + 1) % 8;
		}
		if (stat == 2) {
			gpioWrite(count, HIGH);
			gpioWrite(count2, HIGH);
			usleep(500000);
			gpioWrite(count2, LOW);
			count2 = (count2 + 1) % 8;
			gpioWrite(count2, HIGH);
			usleep(500000);
			gpioWrite(count, LOW);
			gpioWrite(count2, LOW);
			count = (count + 1) % 8;
			count2 = (count2 + 1) % 8;
		}
		if (stat == 3) {
			gpioWrite(0, HIGH);
			gpioWrite(1, HIGH);
			gpioWrite(2, HIGH);
			gpioWrite(3, HIGH);
			gpioWrite(4, HIGH);
			gpioWrite(5, HIGH);
			gpioWrite(6, HIGH);
			gpioWrite(7, HIGH);
			sleep(1);
			gpioWrite(0, LOW);
			gpioWrite(1, LOW);
			gpioWrite(2, LOW);
			gpioWrite(3, LOW);
			gpioWrite(4, LOW);
			gpioWrite(5, LOW);
			gpioWrite(6, LOW);
			gpioWrite(7, LOW);
			sleep(1);
		}

	}
}

void btn() {
	pinMode(8, IN);
	while (1) {
		if (gpioRead(8) == LOW) {
			printf("btn pressed\n");
			stat = (stat + 1) % 4;
			count = 0;
			count2 = 0;
			gpioWrite(0, LOW);
			gpioWrite(1, LOW);
			gpioWrite(2, LOW);
			gpioWrite(3, LOW);
			gpioWrite(4, LOW);
			gpioWrite(5, LOW);
			gpioWrite(6, LOW);
			gpioWrite(7, LOW);
			sleep(1);
		}
	}
}

void start() {
	t = taskSpawn("blink_t", 200, 0, STACK_SIZE, (FUNCPTR)blink, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	bt = taskSpawn("btn_t", 200, 0, STACK_SIZE, (FUNCPTR)btn, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	int loop = 0;
	while(1) {
		loop++;
		if (loop > 30) break;
		printf("working...\n");
		sleep(1);
	}
	taskDelete(t);
	taskDelete(bt);
}
