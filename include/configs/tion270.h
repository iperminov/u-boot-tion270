/*
 * ZEO Tion270 high-level configuration file (community version).
 * Based on Toradex Colibri PXA270 and ZEO Tion270 U-Boot 2010.03 configuration files.
 *
 * Copyright (C) 2010 Marek Vasut <marek.vasut@gmail.com>
 * Copyright (C) 2014 Igor A. Perminov <igor.a.perminov@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * Environment settings
 */
#define	CONFIG_BOOTDELAY		1	/* Autoboot delay */
#define CONFIG_BOOT_RETRY_TIME		60	/* Reboot after this timeout if no user input */
#define CONFIG_RESET_TO_RETRY			/* Reset board to reboot */

#define	CONFIG_ENV_OVERWRITE			/* Allow overwrite serial# and MAC in environment */

#define CONFIG_ETHADDR			80:81:82:83:84:85
#define CONFIG_IPADDR			192.168.0.100
#define CONFIG_NETMASK			255.255.255.0
#define CONFIG_SERVERIP			192.168.0.1
#define CONFIG_GATEWAYIP		192.168.0.1

#define	CONFIG_BOOTCOMMAND				\
	"setenv bootargs ${bootargs} ${mtdparts}; "	\
	"bootm 0x80000;"

#define	CONFIG_BOOTARGS				\
	"console=ttyS0,115200n8 "		\
	"root=/dev/mtdblock3 ro "		\
	"rootfstype=jffs2 "			\
	"quiet"

#define MTDIDS_DEFAULT				\
	"nor0=physmap-flash.0"

#define MTDPARTS_DEFAULT			\
	"mtdparts=physmap-flash.0:"		\
	"256k(u-boot)ro,256k(u-boot_env)ro,4m(ukernel)ro,-(root)"

#define CONFIG_EXTRA_ENV_SETTINGS		\
	"mtdids=" MTDIDS_DEFAULT	"\0"	\
	"mtdparts=" MTDPARTS_DEFAULT	"\0"	\
	"partition=nor0,3"		"\0"

/*
 * Bootloader Components Configuration
 */

#include <config_cmd_default.h>

/* CONFIG_CMD_NET is defined in config_cmd_default.h */
/* CONFIG_CMD_FLASH is defined in config_cmd_default.h */
#define	CONFIG_CMD_MMC			/* MMC support commands */
/* CONFIG_CMD_USB can be defined, but increases U-Boot size over 256k and requires extra testing/debugging */

/* Include support for FAT, Ext2, Ext4 And JFFS2 filesystems. */
#define CONFIG_CMD_FAT
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_JFFS2
/* JFFS2 filesystem can be mounted read-write and updated by file copying in the OS */
#define CONFIG_SYS_JFFS2_SORT_FRAGMENTS

/* Include "ping" and "dhcp" commands */
#ifdef CONFIG_CMD_NET
#  define CONFIG_CMD_PING
#  define CONFIG_CMD_DHCP
#endif

/* Include "mtdparts" command and related stuff */
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE		/* MTD device infrastructure support - needed for "mtdparts" command */
#define CONFIG_FLASH_CFI_MTD		/* Export CFI flash to MTD layer */

#define CONFIG_CMD_LED			/* Enable "led" command to control LEDs */
#define CONFIG_CMD_MEMTEST		/* Enable "memtest" command */

#define	CONFIG_TIMESTAMP		/* imls, bootm, etc print image timestamp */
#define	CONFIG_LZMA			/* LZMA compression support */
#define	CONFIG_OF_LIBFDT		/* Flattened device tree support including "fdt" command */
#define CONFIG_SERIAL_TAG		/* Give ethernet MAC address to kernel via tags interface */
#define	CONFIG_CMDLINE_TAG		/* Give command line to kernel via tags interface */
#define	CONFIG_SETUP_MEMORY_TAGS	/* Give RAM address/size to kernel via tags interface */

/*
 * HUSH Shell Configuration
 */
#define	CONFIG_SYS_HUSH_PARSER		/* Use HUSH shell */
#define	CONFIG_SYS_LONGHELP		/* Include detailed help for commands */

#include "tion270-common.h"

#endif	/* __CONFIG_H */
