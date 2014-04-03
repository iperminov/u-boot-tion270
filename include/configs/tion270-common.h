/*
 * ZEO Tion270 common low-level configuration file (community version).
 * Based on Toradex Colibri PXA270 and ZEO Tion270 U-Boot 2010.03 configuration files.
 *
 * Copyright (C) 2010 Marek Vasut <marek.vasut@gmail.com>
 * Copyright (C) 2014 Igor A. Perminov <igor.a.perminov@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __TION270_COMMON_H
#define __TION270_COMMON_H

/*
 * High Level Board Configuration Options
 */
#define	CONFIG_CPU_PXA27X		1	/* Marvell PXA27x CPU */
#define	CONFIG_SYS_TEXT_BASE		0x0	/* U-Boot code is placed in flash at this address */

/*
 * Serial Console Configuration
 */
#define	CONFIG_PXA_SERIAL			/* Use PXA hardware serial port(s) */
#define	CONFIG_FFUART			1	/* Use FFUART */
#define	CONFIG_CONS_INDEX		3	/* Serial console is on FFUART */
#define	CONFIG_BAUDRATE			115200	/* Default speed */

/*
 * Networking Configuration: Voipac DM9000 chip on board
 */
#ifdef	CONFIG_CMD_NET
#  define CONFIG_DRIVER_DM9000		1			/* Use DM9000 driver */
#  define CONFIG_DM9000_BASE		0x08000000		/* Base IO/data address */
#  define DM9000_IO			(CONFIG_DM9000_BASE)
#  define DM9000_DATA			(CONFIG_DM9000_BASE + 4)
#  define CONFIG_DM9000_NO_SROM		1			/* No EEPROM with MAC */
#  define CONFIG_NET_RETRY_COUNT	10			/* Maximum retry count on failure */
#endif

/*
 * LED configuration
 */
#ifndef CONFIG_RED_LED_GPIO
#  define CONFIG_RED_LED_GPIO		54	/* Red LED on GPIO 54 */
#  define CONFIG_RED_LED_INVERTED	1	/* Clear GPIO output to turn LED on */
#endif
#ifndef CONFIG_GREEN_LED_GPIO
#  define CONFIG_GREEN_LED_GPIO		107	/* Green LED on GPIO 107 */
#  define CONFIG_GREEN_LED_INVERTED	1	/* Clear GPIO output to turn LED on */
#endif

/*
 * Below is stuff just to make "led" command work. Red LED has number 0, green LED is 1.
 * With no CONFIG_CMD_LED configured you'll have red LED turned on at startup time
 * and turned off just before Linux kernel is being run.
 * With CONFIG_CMD_LED it is possible in addition to control both LEDs
 * from command line / scripts.
 */
#ifdef CONFIG_CMD_LED
#  define CONFIG_STATUS_LED
#  define CONFIG_BOARD_SPECIFIC_LED	1
#  if defined(CONFIG_RED_LED_GPIO) && (CONFIG_RED_LED_GPIO >= 0)
#    define STATUS_LED_BIT_RED		0
#    define STATUS_LED_BIT		STATUS_LED_BIT_RED
#    define STATUS_LED_STATE		STATUS_LED_OFF
#    define STATUS_LED_PERIOD		(CONFIG_SYS_HZ / 2)
#  endif
#  if defined(CONFIG_GREEN_LED_GPIO) && (CONFIG_GREEN_LED_GPIO >= 0)
#    define STATUS_LED_BIT_GREEN	1
#    define STATUS_LED_BIT1		STATUS_LED_BIT_GREEN
#    define STATUS_LED_STATE1		STATUS_LED_OFF
#    define STATUS_LED_PERIOD1		(CONFIG_SYS_HZ / 2)
#  endif
#endif

/*
 * HUSH Shell Configuration
 */
#ifdef CONFIG_SYS_HUSH_PARSER
#  define CONFIG_SYS_PROMPT		"$ "			/* HUSH shell command line prompt */
#endif

#define	CONFIG_SYS_CBSIZE		256			/* Console I/O buffer size */
#define	CONFIG_SYS_PBSIZE		\
	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)	/* Print buffer size */
#define	CONFIG_SYS_MAXARGS		16			/* Maximum number of command args */
#define	CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot argument buffer size */
#define	CONFIG_CMDLINE_EDITING		1			/* Allow interactive command line editing */
#define	CONFIG_AUTO_COMPLETE		1			/* Allow command line auto-completion */

/*
 * Miscellaneous Configuration
 */
#define CONFIG_SYS_CONSOLE_IS_IN_ENV	1	/* stdin/out/err are set in environment */
#define CONFIG_SYS_CONSOLE_INFO_QUIET	1	/* Don't print "stdin/out/err: ..." */
#define	CONFIG_SYS_DEVICE_NULLDEV	1	/* Support "null" device */

#ifndef CONFIG_SYS_MALLOC_LEN
#  define CONFIG_SYS_MALLOC_LEN		(128 * 1024)	/* Memory pool size for dynamic allocation */
#endif

#define CONFIG_BOARD_LATE_INIT		1	/* Call board_late_init() defined in board code */
#define CONFIG_SHOW_BOOT_PROGRESS	1	/* Call show_boot_progress() defined in board code */

#define CONFIG_SYS_DIRECT_FLASH_NFS	1	/* Allow direct loading into flash by "nfs" command */
#define CONFIG_SYS_DIRECT_FLASH_TFTP	1	/* Allow direct loading into flash by "tftp" command */

/*
 * DRAM Map
 */
#define	CONFIG_NR_DRAM_BANKS		1		/* We have 1 bank of DRAM */
#define	PHYS_SDRAM_1			0xa0000000	/* SDRAM Bank #1 at CS0 */

#if defined(CONFIG_RAM_64M)
#  define	PHYS_SDRAM_1_SIZE	0x04000000	/* 64 MB */
#elif defined(CONFIG_RAM_128M)
#  define	PHYS_SDRAM_1_SIZE	0x08000000	/* 128 MB */
#else
#  error Either CONFIG_RAM_64M or CONFIG_RAM_128M should be defined
#endif /* defined(CONFIG_RAM_64M) */

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1	/* Physical start of SDRAM */

#define	CONFIG_SYS_INIT_SP_ADDR		0x5c010000	/* Initial stack pointer in PXA27x internal RAM */

/* memtest stuff */
#define CONFIG_SYS_ALT_MEMTEST		1		/* Perform alternative (extended) memory test */
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1	/* Default test start address */
#define CONFIG_SYS_MEMTEST_END		\
	(PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE - 0x180000 - 4)	/* Default test end address (minus reserved area and scratch) */
#define CONFIG_SYS_MEMTEST_SCRATCH	CONFIG_SYS_MEMTEST_END	/* Address of extra 4 bytes required for alternative memtest */

#define	CONFIG_SYS_LOAD_ADDR		PHYS_SDRAM_1	/* Default load address for commands */

/*
 * NOR FLASH
 */
#ifndef	CONFIG_SYS_NO_FLASH

#  define PHYS_FLASH_1			0x00000000	/* Flash Bank #1 physical address */
#  define CONFIG_SYS_FLASH_BASE		PHYS_FLASH_1	/* Physical start address of flash memory */

#  define CONFIG_SYS_FLASH_CFI				/* Flash driver uses extra elements to store flash geometry */
#  define CONFIG_FLASH_CFI_DRIVER	1		/* Use CFI flash driver */

#  define CONFIG_SYS_MAX_FLASH_SECT	(4 + 255)	/* Maximum number of flash sectors */
#  define CONFIG_SYS_MAX_FLASH_BANKS	1		/* Maximum number of flash banks */

/* Timeout values in ticks */
#  define CONFIG_SYS_FLASH_ERASE_TOUT	(25 * CONFIG_SYS_HZ)	/* Erase timeout */
#  define CONFIG_SYS_FLASH_WRITE_TOUT	(25 * CONFIG_SYS_HZ)	/* Write timeout */

#  define CONFIG_SYS_FLASH_USE_BUFFER_WRITE	1	/* Utilize buffered flash writing */
#  define CONFIG_SYS_FLASH_WRITE_UNALIGNED	1	/* Allow write data to flash from unaligned source (nfs, tftp) */
#  define CONFIG_SYS_FLASH_PROTECTION		1	/* Use hardware flash write protection */
#  define CONFIG_SYS_FLASH_EMPTY_INFO		1	/* Display erased sectors in flinfo */

#  define CONFIG_ENV_IS_IN_FLASH		1	/* Environment is stored in flash */

#else	/* No flash */
#  define CONFIG_SYS_ENV_IS_NOWHERE		1	/* Environment is not stored anywhere */
#endif

#define	CONFIG_SYS_MONITOR_BASE		0x0		/* U-Boot address in flash to calculate environment address */
#ifndef CONFIG_SYS_MONITOR_LEN
#  define CONFIG_SYS_MONITOR_LEN	0x40000		/* U-Boot size in flash to calculate environment address */
#endif

#define	CONFIG_ENV_ADDR			\
	(CONFIG_SYS_MONITOR_BASE + CONFIG_SYS_MONITOR_LEN)	/* Environment address in flash */
#define	CONFIG_ENV_SIZE			0x40000		/* Maximum environment size in flash */
#define	CONFIG_ENV_SECT_SIZE		0x40000		/* Flash sector size, where environment is stored */

/*
 * GPIO settings
 *
 * GPIO 0:   AF0 In         - MMC card detect
 * GPIO 10:  AF1 In         - FFUART DCD
 * GPIO 18:  AF1 In         - RDY
 * GPIO 27:  AF3 Out (low)  - FFUART RTS
 * GPIO 32:  AF2 Out (low)  - MMC CLK
 * GPIO 33:  AF2 In         - FFUART DSR
 * GPIO 34:  AF1 In         - FFUART RXD
 * GPIO 38:  AF1 In         - FFUART RI
 * GPIO 39:  AF2 Out (low)  - FFUART TXD
 * GPIO 40:  AF2 Out (low)  - FFUART DTR
 * GPIO 49:  AF2 Out (high) - nPWE
 * GPIO 78:  AF2 Out (high) - nCS2 (DM9000)
 * GPIO 92:  AF1 In         - MMC DAT0
 * GPIO 100: AF3 In         - FFUART CTS
 * GPIO 109: AF1 In         - MMC DAT1
 * GPIO 110: AF1 In         - MMC DAT2
 * GPIO 111: AF1 In         - MMC DAT3
 * GPIO 112: AF1 In         - MMC CMD
 */
#define	CONFIG_SYS_GPSR0_VAL	0x00000000
#define	CONFIG_SYS_GPSR1_VAL	0x00020000
#define	CONFIG_SYS_GPSR2_VAL	0x00004000
#define	CONFIG_SYS_GPSR3_VAL	0x00000000

#define	CONFIG_SYS_GPCR0_VAL	0x00000000
#define	CONFIG_SYS_GPCR1_VAL	0x00000000
#define	CONFIG_SYS_GPCR2_VAL	0x00000000
#define	CONFIG_SYS_GPCR3_VAL	0x00000000

#define	CONFIG_SYS_GPDR0_VAL	0x08000000
#define	CONFIG_SYS_GPDR1_VAL	0x00020181
#define	CONFIG_SYS_GPDR2_VAL	0x00004000
#define	CONFIG_SYS_GPDR3_VAL	0x00000000

#define	CONFIG_SYS_GAFR0_L_VAL	0x00100000
#define	CONFIG_SYS_GAFR0_U_VAL	0x00C00010
#define	CONFIG_SYS_GAFR1_L_VAL	0x0002901A
#define	CONFIG_SYS_GAFR1_U_VAL	0x00000008
#define	CONFIG_SYS_GAFR2_L_VAL	0x20000000
#define	CONFIG_SYS_GAFR2_U_VAL	0x01000000
#define	CONFIG_SYS_GAFR3_L_VAL	0x54000300
#define	CONFIG_SYS_GAFR3_U_VAL	0x00000001

/* Clear Peripheral Control Hold and Standby Mode Status bits */
#define	CONFIG_SYS_PSSR_VAL	0x30

/*
 * Clock settings
 *
 * One of the following values is expected to be defined in boards.cfg for SYS_CPUSPEED:
 * 0x290 for 520 MHz (Turbo-Mode-to-Run-Mode Ratio = 2.5, Run-Mode-to-Oscillator Ratio = 16)
 * or 0x210 for 416 MHz (Turbo-Mode-to-Run-Mode Ratio = 2, Run-Mode-to-Oscillator Ratio = 16).
 */
#if !defined(CONFIG_SYS_CPUSPEED)
#  error CONFIG_SYS_CPUSPEED must be defined
#endif /* !defined(CONFIG_SYS_CPUSPEED) */

/* Enable Memory Controller, OS Timer and FFUART clocks */
#define	CONFIG_SYS_CKEN		0x00500240
/* Memory controller clock frequency is the same as the system bus frequency; set frequency ratio (see above) */
#define	CONFIG_SYS_CCCR		(0x02000000 | CONFIG_SYS_CPUSPEED)

/*
 * Memory controller settings
 */
#define	CONFIG_SYS_MSC0_VAL	0x9ee1c5f2
#define	CONFIG_SYS_MSC1_VAL	0xf974f974
#define	CONFIG_SYS_MSC2_VAL	0x9ee19ee1

#if defined(CONFIG_RAM_64M)
#  define CONFIG_SYS_MDCNFG_VAL	0x090009c9	/* 64 M */
#elif defined(CONFIG_RAM_128M)
// TODO 128M RAM testing required
#  warning RAM_128M not tested yet
#  define CONFIG_SYS_MDCNFG_VAL	0x890009d1	/* 128 M */
#else
#  error Either CONFIG_RAM_64M or CONFIG_RAM_128M should be defined
#endif /* defined(CONFIG_RAM_64M) */

/* CONFIG_SYS_MDREFR_VAL = 0x00000031 from the original Tion270 patch doesn't work */
#define	CONFIG_SYS_MDREFR_VAL	0x2013e01e
#define	CONFIG_SYS_MDMRS_VAL	0x00000000
#define	CONFIG_SYS_FLYCNFG_VAL	0x00010001
#define	CONFIG_SYS_SXCNFG_VAL	0x40044004

/*
 * PCMCIA and CF Interfaces
 */
#define	CONFIG_SYS_MECR_VAL	0x00000001
#define	CONFIG_SYS_MCMEM0_VAL	0x00004204
#define	CONFIG_SYS_MCMEM1_VAL	0x00000000
#define	CONFIG_SYS_MCATT0_VAL	0x00010504
#define	CONFIG_SYS_MCATT1_VAL	0x00000000
#define	CONFIG_SYS_MCIO0_VAL	0x00008407
#define	CONFIG_SYS_MCIO1_VAL	0x00000000

#include "pxa-common.h"

#endif	/* __TION270_COMMON_H */
