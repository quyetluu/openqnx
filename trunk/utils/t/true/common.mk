ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

INSTALLDIR_win32 = usr/bin
INSTALLDIR=$(firstword $(INSTALLDIR_$(OS)) bin)

define PINFO
PINFO DESCRIPTION=Return true value
endef

USEFILE=$(PROJECT_ROOT)/$(NAME).c

include $(MKFILES_ROOT)/qtargets.mk

WIN32_ENVIRON=mingw
