/*
 modules/counter.c

 Copyright (C) 2014   Cristian Klein <cristiklein@gmail.com>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * counter.c
 *
 *  Created on: Aug 1, 2014
 *      Author: Cristian Klein
 *
 *      Implements multiple user-incremented counters, to count
 *      people, glasses of water you drank, calories you ate, etc.
 *
 *      Use:
 *
 *      First line shows counter ID and the second line
 *      shows the counter value.
 *      ^ (up-arrow) select next counter
 *      v (dn-arrow) select previous counter
 *      # (num-longpressed) reset counter
 *      # (num-shortpressed) increment current counter
 *      * (star-Longpressed) -- noop
 *      - (both-arrows) increment current counter by 100
 */

#include <openchronos.h>
/* driver */
#include <drivers/display.h>

/* Defines */

#define MAX_COUNTERS	9

uint16_t counter_values[MAX_COUNTERS];
int8_t current_counter;

/* Function to write the screen */

void draw_counter_screen(void) {

	display_chars(0, LCD_SEG_L1_3_1, "CNT", SEG_SET);
	display_char(0, LCD_SEG_L1_0, '1' + current_counter, SEG_SET);
	_printf(0, LCD_SEG_L2_3_0, "%04u", counter_values[current_counter]);
}

/* Activation of the module */
static void counter_activated() {
	draw_counter_screen();
}

/* Deactivation of the module */
static void counter_deactivated() {
	/* clean up screen */
	display_clear(0, 1);
	display_clear(0, 2);
}

static void down_press() {
	current_counter --;
	if (current_counter < 0)
		current_counter += MAX_COUNTERS;
	draw_counter_screen();
}

static void up_press() {
	current_counter ++;
	if (current_counter >= MAX_COUNTERS)
		current_counter -= MAX_COUNTERS;
	draw_counter_screen();
}

static void num_press() {
	counter_values[current_counter] ++;
	draw_counter_screen();
}

static void num_long_press() {
	counter_values[current_counter] = 0;
	draw_counter_screen();
}

static void up_down_press() {
	counter_values[current_counter] += 100;
	draw_counter_screen();
}

void mod_counter_init(void) {
	menu_add_entry("COUNT", &up_press, &down_press, &num_press, NULL,
			&num_long_press, &up_down_press, &counter_activated,
			&counter_deactivated);
}
