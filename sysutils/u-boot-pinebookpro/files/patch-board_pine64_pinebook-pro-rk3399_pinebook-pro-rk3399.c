--- board/pine64/pinebook-pro-rk3399/pinebook-pro-rk3399.c.orig	2022-02-14 16:52:05 UTC
+++ board/pine64/pinebook-pro-rk3399/pinebook-pro-rk3399.c
@@ -7,13 +7,15 @@
 #include <common.h>
 #include <dm.h>
 #include <syscon.h>
+#include <linux/delay.h>
+#include <asm/gpio.h>
 #include <asm/io.h>
 #include <asm/arch-rockchip/clock.h>
 #include <asm/arch-rockchip/grf_rk3399.h>
+#include <asm/arch-rockchip/gpio.h>
 #include <asm/arch-rockchip/hardware.h>
 #include <asm/arch-rockchip/misc.h>
 #include <power/regulator.h>
-
 #define GRF_IO_VSEL_BT565_SHIFT 0
 #define PMUGRF_CON0_VSEL_SHIFT 8
 
@@ -59,6 +61,7 @@ int misc_init_r(void)
 	const u32 cpuid_length = 0x10;
 	u8 cpuid[cpuid_length];
 	int ret;
+	unsigned int gpio;
 
 	setup_iodomain();
 
@@ -69,6 +72,11 @@ int misc_init_r(void)
 	ret = rockchip_cpuid_set(cpuid, cpuid_length);
 	if (ret)
 		return ret;
+
+	gpio_lookup_name("B22", NULL, NULL, &gpio);
+	gpio_direction_output(gpio, 0);
+	udelay(500000);
+	gpio_direction_output(gpio, 1);
 
 	return ret;
 }
