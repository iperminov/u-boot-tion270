/*
 * PXA GPIO functions.
 *
 * Copyright (C) 2014 Igor A. Perminov <igor.a.perminov@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef	__ASM_PXA_GPIO_H__
#define	__ASM_PXA_GPIO_H__

#include <asm/types.h>
#include "pxa-regs.h"

static inline int gpio_set_value(unsigned gpio, int value);

static inline int gpio_request(unsigned gpio, const char *label)
{ return 0; }

static inline int gpio_free(unsigned gpio)
{ return 0; }

static inline int gpio_direction_input(unsigned gpio) {
	*((volatile u32 *) GPDR(gpio)) &= ~GPIO_bit(gpio);
	return 0;
}

static inline int gpio_direction_output(unsigned gpio, int value) {
	gpio_set_value(gpio, value);
	*((volatile u32 *) GPDR(gpio)) |= GPIO_bit(gpio);
	return 0;
}

static inline int gpio_get_value(unsigned gpio) {
	return !!(*((volatile u32 *) GPLR(gpio)) & GPIO_bit(gpio));
}

static inline int gpio_set_value(unsigned gpio, int value) {
	if (value) {
		*((volatile u32 *) GPSR(gpio)) |= GPIO_bit(gpio);
	}
	else {
		*((volatile u32 *) GPCR(gpio)) |= GPIO_bit(gpio);
	}
	return 0;
}

#endif /* __ASM_PXA_GPIO_H__ */
