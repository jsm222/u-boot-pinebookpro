--- drivers/video/rockchip/rk_edp.c.orig	2020-10-05 15:15:32 UTC
+++ drivers/video/rockchip/rk_edp.c
@@ -18,9 +18,15 @@
 #include <asm/io.h>
 #include <asm/arch-rockchip/clock.h>
 #include <asm/arch-rockchip/edp_rk3288.h>
+#if defined(CONFIG_ROCKCHIP_RK3288)
 #include <asm/arch-rockchip/grf_rk3288.h>
-#include <asm/arch-rockchip/hardware.h>
 #include <dt-bindings/clock/rk3288-cru.h>
+#endif
+#if defined(CONFIG_ROCKCHIP_RK3399)
+#include <asm/arch-rockchip/grf_rk3399.h>
+#include <dt-bindings/clock/rk3399-cru.h>
+#endif
+#include <asm/arch-rockchip/hardware.h>
 #include <linux/delay.h>
 
 #define MAX_CR_LOOP 5
@@ -39,7 +45,12 @@ static const char * const pre_emph_names[] = {
 
 struct rk_edp_priv {
 	struct rk3288_edp *regs;
+#if defined(CONFIG_ROCKCHIP_RK3288)
 	struct rk3288_grf *grf;
+#endif
+#if defined(CONFIG_ROCKCHIP_RK3399)
+	struct rk3399_grf_regs *grf;
+#endif
 	struct udevice *panel;
 	struct link_train link_train;
 	u8 train_set[4];
@@ -1037,6 +1048,7 @@ static int rk_edp_probe(struct udevice *dev)
 	int vop_id = uc_plat->source_id;
 	debug("%s, uc_plat=%p, vop_id=%u\n", __func__, uc_plat, vop_id);
 
+#if defined(CONFIG_ROCKCHIP_RK3288)
 	ret = clk_get_by_index(dev, 1, &clk);
 	if (ret >= 0) {
 		ret = clk_set_rate(&clk, 0);
@@ -1046,6 +1058,7 @@ static int rk_edp_probe(struct udevice *dev)
 		debug("%s: Failed to set EDP clock: ret=%d\n", __func__, ret);
 		return ret;
 	}
+#endif
 
 	ret = clk_get_by_index(uc_plat->src_dev, 0, &clk);
 	if (ret >= 0) {
@@ -1057,14 +1070,20 @@ static int rk_edp_probe(struct udevice *dev)
 		      __func__, uc_plat->src_dev->name, ret);
 		return ret;
 	}
-
+#if defined(CONFIG_ROCKCHIP_RK3288)
 	/* grf_edp_ref_clk_sel: from internal 24MHz or 27MHz clock */
 	rk_setreg(&priv->grf->soc_con12, 1 << 4);
 
 	/* select epd signal from vop0 or vop1 */
 	rk_clrsetreg(&priv->grf->soc_con6, (1 << 5),
 	    (vop_id == 1) ? (1 << 5) : (0 << 5));
+#endif
 
+#if defined(CONFIG_ROCKCHIP_RK3399)
+	/* select epd signal from vop0 or vop1 */
+	rk_clrsetreg(&priv->grf->soc_con20, (1 << 5),
+	    (vop_id == 1) ? (1 << 5) : (0 << 5));
+#endif
 	rockchip_edp_wait_hpd(priv);
 
 	rk_edp_init_refclk(regs);
@@ -1085,6 +1104,7 @@ static const struct dm_display_ops dp_rockchip_ops = {
 
 static const struct udevice_id rockchip_dp_ids[] = {
 	{ .compatible = "rockchip,rk3288-edp" },
+	{ .compatible = "rockchip,rk3399-edp" },
 	{ }
 };
 
