/*
 * ZEO Tion270 LED Support (community version).
 *
 * Copyright (C) 2014 Igor A. Perminov <igor.a.perminov@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <status_led.h>
#include <asm/arch/gpio.h>

/*
 * Note: coloured_LED_init() and red_led_on() are called by ARM initialization code.
 */

static inline void status_led_set_state(unsigned gpio, int inverted, int state) {
	gpio_set_value(gpio, !(inverted) != !(state));
}

#ifdef CONFIG_CMD_LED
static led_id_t saved_state[4] = {
		STATUS_LED_OFF, STATUS_LED_OFF, STATUS_LED_OFF, STATUS_LED_OFF
};
#endif /* CONFIG_CMD_LED */

void coloured_LED_init(void)
{
	debug("%s\n", __func__);

	// GAFRs are already set to AF0 (GPIO) by initialization code.

#if CONFIG_RED_LED_GPIO >= 0
	gpio_request(CONFIG_RED_LED_GPIO, "Red LED");
	gpio_direction_output(CONFIG_RED_LED_GPIO, CONFIG_RED_LED_INVERTED);
#endif /* CONFIG_RED_LED_GPIO >= 0 */

#if CONFIG_GREEN_LED_GPIO >= 0
	gpio_request(CONFIG_GREEN_LED_GPIO, "Green LED");
	gpio_direction_output(CONFIG_GREEN_LED_GPIO, CONFIG_GREEN_LED_INVERTED);
#endif /* CONFIG_GREEN_LED_GPIO >= 0 */
}

#if CONFIG_RED_LED_GPIO >= 0

void red_led_on(void)
{
	debug("%s\n", __func__);

	status_led_set_state(CONFIG_RED_LED_GPIO, CONFIG_RED_LED_INVERTED, 1);
#ifdef CONFIG_CMD_LED
	saved_state[STATUS_LED_BIT_RED] = STATUS_LED_ON;
#endif /* CONFIG_CMD_LED */
}

void red_led_off(void)
{
	debug("%s\n", __func__);

	status_led_set_state(CONFIG_RED_LED_GPIO, CONFIG_RED_LED_INVERTED, 0);
#ifdef CONFIG_CMD_LED
	saved_state[STATUS_LED_BIT_RED] = STATUS_LED_OFF;
#endif /* CONFIG_CMD_LED */
}

#else

void red_led_on(void) { }
void red_led_off(void) { }

#endif /* CONFIG_RED_LED_GPIO >= 0 */

#if CONFIG_GREEN_LED_GPIO >= 0

void green_led_on(void)
{
	debug("%s\n", __func__);

	status_led_set_state(CONFIG_GREEN_LED_GPIO, CONFIG_GREEN_LED_INVERTED, 1);
#ifdef CONFIG_CMD_LED
	saved_state[STATUS_LED_BIT_GREEN] = STATUS_LED_ON;
#endif /* CONFIG_CMD_LED */
}

void green_led_off(void)
{
	debug("%s\n", __func__);

	status_led_set_state(CONFIG_GREEN_LED_GPIO, CONFIG_GREEN_LED_INVERTED, 0);
#ifdef CONFIG_CMD_LED
	saved_state[STATUS_LED_BIT_GREEN] = STATUS_LED_OFF;
#endif /* CONFIG_CMD_LED */
}

#else

void green_led_on(void) { }
void green_led_off(void) { }

#endif /* CONFIG_GREEN_LED_GPIO >= 0 */

#ifdef CONFIG_CMD_LED

void __led_set(led_id_t mask, int state)
{
	debug("%s: mask=%ld, state=%d\n", __func__, mask, state);

	switch (mask) {
#if CONFIG_RED_LED_GPIO >= 0
	case STATUS_LED_BIT_RED:
		if (state == STATUS_LED_ON) {
			red_led_on();
		}
		else {
			red_led_off();
		}

		break;
#endif /* CONFIG_RED_LED_GPIO >= 0 */

#if CONFIG_GREEN_LED_GPIO >= 0
	case STATUS_LED_BIT_GREEN:
		if (state == STATUS_LED_ON) {
			green_led_on();
		}
		else {
			green_led_off();
		}

		break;
#endif /* CONFIG_GREEN_LED_GPIO >= 0 */

	default:
		break;
	}
}

void __led_toggle(led_id_t mask)
{
	debug("%s: mask=%ld\n", __func__, mask);

	switch (mask) {
#if CONFIG_RED_LED_GPIO >= 0
	case STATUS_LED_BIT_RED:
		if (saved_state[STATUS_LED_BIT_RED] != STATUS_LED_ON) {
			red_led_on();
		}
		else {
			red_led_off();
		}

		break;
#endif /* CONFIG_RED_LED_GPIO >= 0 */

#if CONFIG_GREEN_LED_GPIO >= 0
	case STATUS_LED_BIT_GREEN:
		if (saved_state[STATUS_LED_BIT_GREEN] != STATUS_LED_ON) {
			green_led_on();
		}
		else {
			green_led_off();
		}

		break;
#endif /* CONFIG_GREEN_LED_GPIO >= 0 */

	default:
		break;
	}
}

#endif /* CONFIG_CMD_LED */
