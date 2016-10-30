mod_yacco.la: mod_yacco.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_yacco.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_yacco.la

