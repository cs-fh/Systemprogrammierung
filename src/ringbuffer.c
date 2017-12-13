
#include "ringbuffer.h"
#include <stdlib.h>
#include <stddef.h>

ring_buffer *init_buffer(const size_t n, void (*f)(void *p)) {
	ring_buffer *rb;
	
	if(n < 1 || f == NULL) {
		return NULL;
	}
	rb = (ring_buffer*) malloc( sizeof(ring_buffer));
	rb->size = n;
	rb->count = 0;
	rb->head = 0;
	rb->elems = (void**) malloc(n*sizeof(void*) );
	rb->free_callback = f;
	return rb;
}

void *read_buffer(ring_buffer *cb) {
	if(cb == NULL) {
		return NULL;
	}
	if(cb->elems == NULL || cb->count == 0) {
		return NULL;
	}
	void *rv = cb->elems[cb->head];
	if(cb->head == cb->size - 1) {
		cb->head = 0;
	} else {
		cb->head++;
	}
	cb->count--;
	return rv;
}

void write_buffer(ring_buffer *cb, void *data) {
	if(cb == NULL || data == NULL) {
		return;
	}
	
	if(cb->count < cb->size) {
		cb->elems[(cb->head+cb->count)%cb->size] = data;
		cb->count++;
	} else {
		cb->free_callback (cb->elems[cb->head]);
		cb->elems[cb->head] = data;
		if(cb->head >= cb->size - 1) {
			cb->head = 0;
		} else {
			cb->head++;
		}
	}
}

int free_buffer(ring_buffer *cb) {
	int delElemsCount = 0;
	if(cb == NULL) {
		return -1;
	}
	while(cb->count > 0) {
		cb->free_callback (cb->elems[cb->head]);
		if(cb->head < cb->size-1) {
			cb->head++;
		} else {
			cb->head = 0;
		}
		cb->count--;
		delElemsCount++;
	}
	return delElemsCount;
}

int count_elements(const ring_buffer *cb) {
	if(cb == NULL) {
		return -1;
	}
	return cb->count;
}

int display_status(const ring_buffer *cb) {
	int nleds = 0, number = 0;
	float percent = 0.0;
	leds sht = LED01;
	
	init_led_bar();
	set_brightness(OFF);
	
	percent = ((float) cb->count / cb->size) * 100;
    	number = ceil(percent / 10);
	nleds = number; 
	
	for(int i = 0; i < nleds ; i++) {
		set_led(sht, FULL);
		sht = sht+(enum leds)1;
	}
	return nleds;
}
