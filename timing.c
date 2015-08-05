/* Copyright (C) 2015 David Guerrero
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef TIMING
#include "timing.h"
#endif

#include <avr/io.h>

// #define LSB(n) (n & 255)
// #define MSB(n) ((n >> 8) & 255)
//
// void configure_clock(void)
// {
// 	// TCCR3A=_BV(WGM32);
// 	// TCCR3B=_BV(WGM33)|_BV(WGM32)|5;
// 	//Compare match with ICR3|divide frequency by 1024 (1 Khz aprox.=> 1 ms period)
//
// 	TCCR3B|=5;
// 	//divide frequency by 1024 (1 Khz aprox.=> 1 ms period)
// }

uint8_t initial_milisecond;
//void count(uint16_t miliseconds)
void count_miliseconds(void)
{
	// uint16_t top_value;
	// top_value=miliseconds-1;
	// cli();//disable interrupts
	// ICR3H=MSB(top_value);
	// ICR3L=LSB(top_value);
	// TCNT3=0;     // set timer3 counter initial value to 0
	// TIFR3|=1<<3;  // clear the compare match flag
  // sei();//enable interrupts
	//green_semaphore=0;
	// initial_milisecond=pullings_counter>>1;
	initial_milisecond=TCNT0;
	//green_semaphore=1;
	return;
}

uint8_t elapsed_miliseconds(void)
{
	// uint16_t new_value,old_value;
	// old_value=pullings_counter;
	// new_value=pullings_counter;
	// while(old_value==new_value) //wait for a change in the polling counter
	// {
	// 	old_value=new_value;
	// 	new_value=pullings_counter;
	// }
	// green_semaphore=0;
	// new_value=pullings_counter;
	// green_semaphore=1;
	return TCNT0-initial_milisecond;
}

void active_wait (uint32_t delay)
{
	volatile uint32_t counter;
	for(counter=0;counter<delay;counter++);
}

void wait_for_miliseconds(uint8_t miliseconds_delay)
{
	count_miliseconds();
	while(elapsed_miliseconds()<miliseconds_delay);
	return;
}
