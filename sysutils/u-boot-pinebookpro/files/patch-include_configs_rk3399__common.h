--- include/configs/rk3399_common.h.orig	2020-10-05 15:15:32 UTC
+++ include/configs/rk3399_common.h
@@ -56,12 +56,9 @@
 	"kernel_comp_addr_r=0x08000000\0" \
 	"kernel_comp_size=0x2000000\0"
 
-#ifndef ROCKCHIP_DEVICE_SETTINGS
-#define ROCKCHIP_DEVICE_SETTINGS
-#endif
-
 #include <config_distro_bootcmd.h>
 #include <environment/distro/sf.h>
+#define PREBOOT_CMD "led red:standby on;"
 #define CONFIG_EXTRA_ENV_SETTINGS \
 	ENV_MEM_LAYOUT_SETTINGS \
 	"fdtfile=" CONFIG_DEFAULT_FDT_FILE "\0" \
@@ -69,10 +66,11 @@
 	ROCKCHIP_DEVICE_SETTINGS \
 	BOOTENV \
 	BOOTENV_SF \
+	"loadaddr=0x40000000\0" \
+	"preboot=" PREBOOT_CMD "\0" \
 	"altbootcmd=" \
 		"setenv boot_syslinux_conf extlinux/extlinux-rollback.conf;" \
 		"run distro_bootcmd\0"
-
 #endif
 
 /* enable usb config for usb ether */
