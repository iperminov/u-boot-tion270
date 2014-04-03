/*
 * ZEO Tion270 board support (community version).
 * Based on Toradex Colibri PXA270 and ZEO Tion270 U-Boot 2010.03 board sources.
 *
 * Copyright (C) 2010 Marek Vasut <marek.vasut@gmail.com>
 * Copyright (C) 2014 Igor A. Perminov <igor.a.perminov@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <bootstage.h>
#include <asm/arch/hardware.h>
#include <asm/arch/regs-mmc.h>
#include <asm/arch/pxa.h>
#include <asm/arch/gpio.h>
#include <netdev.h>
#include <asm/io.h>
#include <serial.h>
#include <usb.h>
#include <status_led.h>

extern void red_led_off(void);

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	/* We have RAM, disable cache */
	dcache_disable();
	icache_disable();

	/* arch number of tion270 */
	gd->bd->bi_arch_number = MACH_TYPE_TION270;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

	return 0;
}

int dram_init(void)
{
	pxa2xx_dram_init();
	gd->ram_size = PHYS_SDRAM_1_SIZE;
	return 0;
}

void enable_caches(void)
{
	/*
	 * Don't actually enable caches, just define this routine
	 * to suppress ugly warning at boot time.
	 */
}

#ifdef CONFIG_DRIVER_DM9000
int board_eth_init(bd_t *bis)
{
	return dm9000_initialize(bis);
}
#endif

#ifdef CONFIG_CMD_MMC
int board_mmc_init(bd_t *bis)
{
	pxa_mmc_register(0);
	return 0;
}
#endif

#ifdef CONFIG_CMD_USB

#warning USB support testing/debugging required

int board_usb_init(int index, enum usb_init_type init)
{
	/*
	 * GPIO 88:  AF1 In         - USBH1 PWR
	 * GPIO 89:  AF2 Out (low)  - USBH1 PEN
	 */
	pxa2xx_mfp_config(88 | GPIO_ALT_FN_1_IN);
	pxa2xx_mfp_config(89 | GPIO_ALT_FN_2_OUT);

	writel((readl(UHCHR) | UHCHR_PCPL | UHCHR_PSPL) &
		~(UHCHR_SSEP0 | UHCHR_SSEP1 | UHCHR_SSEP2 | UHCHR_SSE),
		UHCHR);

	writel(readl(UHCHR) | UHCHR_FSBIR, UHCHR);

	while (UHCHR & UHCHR_FSBIR)
		;

	writel(readl(UHCHR) & ~UHCHR_SSE, UHCHR);
	writel((UHCHIE_UPRIE | UHCHIE_RWIE), UHCHIE);

	/* Clear any OTG Pin Hold */
	if (readl(PSSR) & PSSR_OTGPH)
		writel(readl(PSSR) | PSSR_OTGPH, PSSR);

	/*
	 * Ports are power switched. All ports are powered at the same time.
	 * No OC protection.
	 */
	writel((readl(UHCRHDA) | 0x1000) & ~(0x300), UHCRHDA);

	/* Set port power control mask bits, only 2 ports. */
	writel(readl(UHCRHDB) | (0x3 << 17), UHCRHDB);

	/* Enable port 2 */
	writel(readl(UP2OCR) | UP2OCR_HXOE | UP2OCR_HXS |
		UP2OCR_DMPDE | UP2OCR_DPPDE, UP2OCR);

	return 0;
}

int board_usb_cleanup(int index, enum usb_init_type init)
{
	return 0;
}

int usb_board_stop(void)
{
	writel(readl(UHCHR) | UHCHR_FHR, UHCHR);
	udelay(11);
	writel(readl(UHCHR) & ~UHCHR_FHR, UHCHR);

	writel(readl(UHCCOMS) | 1, UHCCOMS);
	udelay(10);

	writel(readl(CKEN) & ~CKEN10_USBHOST, CKEN);

	/* Cleanup USB MFP assignments. */
	pxa2xx_mfp_config(88 | GPIO_IN);
	pxa2xx_mfp_config(89 | GPIO_IN);

	return 0;
}
#endif

#ifdef CONFIG_BOARD_LATE_INIT
int board_late_init(void)
{
	debug("%s\n", __func__);
	return 0;
}
#endif

#ifdef CONFIG_SHOW_BOOT_PROGRESS
void show_boot_progress(int stage)
{
	debug("%s: stage=%d\n", __func__, stage);

	if (stage == BOOTSTAGE_ID_RUN_OS) {
		red_led_off();
	}
}
#endif /* CONFIG_SHOW_BOOT_PROGRESS */

#ifdef CONFIG_SERIAL_TAG
/* Board serial number is calculated from MAC and then converted back to MAC by the kernel. */
void get_board_serial(struct tag_serialnr* serialnr)
{
	int i;
	char *s, *e;

	serialnr->low = 0;
	serialnr->high = 0;

	s = getenv("ethaddr");

	if (!s) {
		return;
	}

	for (i = 0; i < 4; i++) {
		serialnr->low |= simple_strtoul(s, &e, 16) << (i * 8);
		s = e + 1;
	}

	for (i = 0; i < 2; i++) {
		serialnr->high |= simple_strtoul(s, &e, 16) << (i * 8);
		s = e + 1;
	}
}
#endif
