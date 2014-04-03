/*
 * PXA GPIO functions.
 *
 * Copyright (C) 2014 Igor A. Perminov <igor.a.perminov@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef	__ASM_PXA_GPIO_H__
#define	__ASM_PXA_GPIO_H__

#include <asm/io.h>
#include <asm/types.h>
#include "pxa-regs.h"

static inline int gpio_set_value(unsigned gpio, int value);

static inline int gpio_request(unsigned gpio, const char *label)
{ return 0; }

static inline int gpio_free(unsigned gpio)
{ return 0; }

static inline int gpio_direction_input(unsigned gpio) {
	writel(readl(GPDR(gpio)) & ~GPIO_bit(gpio), GPDR(gpio));
	return 0;
}

static inline int gpio_direction_output(unsigned gpio, int value) {
	gpio_set_value(gpio, value);
	writel(readl(GPDR(gpio)) | GPIO_bit(gpio), GPDR(gpio));
	return 0;
}

static inline int gpio_get_value(unsigned gpio) {
	return !!(readl(GPLR(gpio)) & GPIO_bit(gpio));
}

static inline int gpio_set_value(unsigned gpio, int value) {
	if (value)
		writel(GPIO_bit(gpio), GPSR(gpio));
	else
		writel(GPIO_bit(gpio), GPCR(gpio));
	return 0;
}

static inline void _pxa2xx_mfp_config(unsigned pin, unsigned af, unsigned output, int drive_high) {
	unsigned gafr_shift = (pin & 0x0F) * 2;
	writel((readl(GAFR(pin)) & ~(0x03 << gafr_shift)) | ((af & 0x03) << gafr_shift), GAFR(pin));
	if (output)
		gpio_direction_output(pin, drive_high);
	else
		gpio_direction_input(pin);
}

static inline void pxa2xx_mfp_config(unsigned md) {
	_pxa2xx_mfp_config(md & GPIO_MD_MASK_NR, (md & GPIO_MD_MASK_FN) >> 8, md & GPIO_MD_MASK_DIR, 0);
}

#endif /* __ASM_PXA_GPIO_H__ */
