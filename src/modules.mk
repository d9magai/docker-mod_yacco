mod_yacko.la: mod_yacko.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_yacko.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_yacko.la

