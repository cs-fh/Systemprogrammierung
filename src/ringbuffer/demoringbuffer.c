
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <math.h>
#include "ledbar/ledbar.h"
#include "ringbuffer/ringbuffer.h"

int main() {
	
	float (*fp) (int);

	void free_cb(void *fp) {
		free(fp);
	}

	ring_buffer *rb = init_buffer(10, fp);
	int g = 11;
	write_buffer(rb, &g);
	int *ptr = read_buffer(rb);
	printf("Zahl: %d", ptr);
	


}	
