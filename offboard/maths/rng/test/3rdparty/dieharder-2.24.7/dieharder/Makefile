# Makefile.in generated by automake 1.9.6 from Makefile.am.
# dieharder/Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
# 2003, 2004, 2005  Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


srcdir = .
top_srcdir = ..

pkgdatadir = $(datadir)/dieharder
pkglibdir = $(libdir)/dieharder
pkgincludedir = $(includedir)/dieharder
top_builddir = ..
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
INSTALL = /usr/bin/install -c
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = i686-pc-linux-gnu
host_triplet = i686-pc-linux-gnu
subdir = dieharder
DIST_COMMON = README $(srcdir)/Makefile.am $(srcdir)/Makefile.in \
	COPYING
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
DIST_SOURCES =
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
ACLOCAL = ${SHELL} /home/phil/dev/c++/Simon/dieharder-2.24.7/missing --run aclocal-1.9
AMDEP_FALSE = #
AMDEP_TRUE = 
AMTAR = ${SHELL} /home/phil/dev/c++/Simon/dieharder-2.24.7/missing --run tar
AR = ar
AUTOCONF = ${SHELL} /home/phil/dev/c++/Simon/dieharder-2.24.7/missing --run autoconf
AUTOHEADER = ${SHELL} /home/phil/dev/c++/Simon/dieharder-2.24.7/missing --run autoheader
AUTOMAKE = ${SHELL} /home/phil/dev/c++/Simon/dieharder-2.24.7/missing --run automake-1.9
AWK = gawk

#========================================================================
# Define parameters and directives needed in compile/link steps.
#========================================================================
# C Compiler
CC = gcc
CCDEPMODE = depmode=none

# Compile flags (use fairly standard -O3 as default)
# PHIL - has added path of definitions.h - need to build our C_Interface.h
CFLAGS = -O3 -I ../include -I  ../../../../../../basic/compiler $(DEFINES) 
CPP = gcc -E
CPPFLAGS = 
CYGPATH_W = echo
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
DIEHARDER_CFLAGS = -I${prefix}/include
DIEHARDER_LIBS = -L${exec_prefix}/lib -ldieharder
DIEHARDER_LT_VERSION = 0:0:0
ECHO = echo
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = /bin/grep -E
EXEEXT = 
GREP = /bin/grep
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s

# Linker flags.
LDFLAGS = 
LIBOBJS = 

# Libraries
# ***************************** PHIL CHANGE *********************************
# THIS IS THE ONLY LINE PHIL CHANGED ( ADDING -L ../../../../../../../bin/[debug|release], -lRandom, lPrime, -lBasic and -lmt19937ar )
# YOU MAY NEED TO RE-AUTOGEN THIS AND THEN MAKE THE CHANGE TO
# THE GENERATED FILE SUITED TO YOUR ENVIRONMENT.
# Usuage 'make my_build=[debug|release]'
ifndef my_build
	my_build = debug
endif
LIBS = -L ../libdieharder -L ../../../../../../../../bin/linux_gcc_${my_build} -ldieharder -lgsl -lgslcblas -lm -lmt19937ar -lRandom -lPrime -lBasic

LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LTLIBOBJS = 
MAINT = #
MAINTAINER_MODE_FALSE = 
MAINTAINER_MODE_TRUE = #
MAKEINFO = ${SHELL} /home/phil/dev/c++/Simon/dieharder-2.24.7/missing --run makeinfo
OBJEXT = o
PACKAGE = dieharder
PACKAGE_BUGREPORT = 
PACKAGE_NAME = dieharder
PACKAGE_STRING = dieharder 2.24.7
PACKAGE_TARNAME = dieharder
PACKAGE_VERSION = 2.24.7
PATH_SEPARATOR = :
RANLIB = ranlib
RELEASE = 1
RELEASED = 
SET_MAKE = 
SHELL = /bin/bash
STRIP = strip

# This is automagically set in the toplevel build.  Do not edit by
# hand.
VERSION = 2.24.7
ac_ct_CC = gcc
am__fastdepCC_FALSE = 
am__fastdepCC_TRUE = #
am__include = include
am__leading_dot = .
am__quote = 
am__tar = ${AMTAR} chof - "$$tardir"
am__untar = ${AMTAR} xf -
bindir = ${exec_prefix}/bin
build = i686-pc-linux-gnu
build_alias = 
build_cpu = i686
build_os = linux-gnu
build_vendor = pc
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}
dvidir = ${docdir}
exec_prefix = ${prefix}
host = i686-pc-linux-gnu
host_alias = 
host_cpu = i686
host_os = linux-gnu
host_vendor = pc
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = /home/phil/dev/c++/Simon/dieharder-2.24.7/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mkdir_p = mkdir -p --
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /usr
program_transform_name = s,x,x,
psdir = ${docdir}
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
sysconfdir = ${prefix}/etc
target_alias = 

#========================================================================
# This is a Makefile for the dieharder tty application, part of the
# overall dieharder package.  It has a very abbreviated set of targets.
#
# make          alone should build the application.
#
# make clean    deletes the application and all object files
# make install  installs application and a man page
# make printout prints out all source and include files
#
# These two commands execute in the toplevel project directory only.
# make svn      does a svn commit and creates the timestamp $(SVN)
# make sync     does a svn commit and rsyncs to list of hosts
#========================================================================
PROJECT = dieharder
PROGRAM = dieharder
DIR = $(PROGRAM)
SVNTREE = $(HOME)/Src/svn-tree
SVNPATH = $(SVNTREE)/$(PROJECT)
SVNTIME = $(DIR:=.svn.time)

#========================================================================
# Define all sources.  Note that we choose to depend on ALL the includes
# in the include directory, which cannot be empty or this will barf.
# We also have dependencies that extend to the libdieharder source
# directory, as we need to force a build if any of them change.
#========================================================================
SRCSOURCES = $(shell ls *.c  2>&1 | sed -e "/\/bin\/ls:/d")
SRCINCLUDES = $(shell ls *.h  2>&1 | sed -e "/\/bin\/ls:/d")

# These are important dependencies, although it isn't easy to
# see how to force a consistent build when working on the UI
# and library at the same time.  Maybe with particular make targets...
LIBINCLUDES = $(shell ls ../include/dieharder/*.h  2>&1 | sed -e "/\/bin\/ls:/d")
PROGLIB_SONAME = ../libwulf/libdieharder.so.$(VERSION)
SOURCES = $(LIBSOURCES) $(SRCSOURCES)
INCLUDES = $(LIBINCLUDES) $(SRCINCLUDES)
OBJECTS = $(SRCSOURCES:.c=.o)
DEFINES = -DVERSION=$(VERSION)

#========================================================================
# printout makes an enscript -2r printout of SOURCES and
# and INCLUDES.  Use lpr if you don't have enscript
#========================================================================
LPR = enscript -2r
all: all-am

.SUFFIXES:
$(srcdir)/Makefile.in: # $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh \
		&& exit 0; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --gnu  dieharder/Makefile'; \
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  dieharder/Makefile
.PRECIOUS: Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh

$(top_srcdir)/configure: # $(am__configure_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(ACLOCAL_M4): # $(am__aclocal_m4_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
uninstall-info-am:
tags: TAGS
TAGS:

ctags: CTAGS
CTAGS:


distdir: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's|.|.|g'`; \
	list='$(DISTFILES)'; for file in $$list; do \
	  case $$file in \
	    $(srcdir)/*) file=`echo "$$file" | sed "s|^$$srcdirstrip/||"`;; \
	    $(top_srcdir)/*) file=`echo "$$file" | sed "s|^$$topsrcdirstrip/|$(top_builddir)/|"`;; \
	  esac; \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    dir="/$$dir"; \
	    $(mkdir_p) "$(distdir)$$dir"; \
	  else \
	    dir=''; \
	  fi; \
	  if test -d $$d/$$file; then \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -pR $(srcdir)/$$file $(distdir)$$dir || exit 1; \
	    fi; \
	    cp -pR $$d/$$file $(distdir)$$dir || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-am
all-am: Makefile
installdirs:
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean-am: clean-generic clean-libtool mostlyclean-am

distclean: distclean-am
	-rm -f Makefile
distclean-am: clean-am distclean-generic distclean-libtool

dvi: dvi-am

dvi-am:

html: html-am

info: info-am

info-am:

install-data-am:

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-generic mostlyclean-libtool

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am: uninstall-info-am

.PHONY: all all-am check check-am clean clean-generic clean-libtool \
	distclean distclean-generic distclean-libtool distdir dvi \
	dvi-am html html-am info info-am install install-am \
	install-data install-data-am install-exec install-exec-am \
	install-info install-info-am install-man install-strip \
	installcheck installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-generic \
	mostlyclean-libtool pdf pdf-am ps ps-am uninstall uninstall-am \
	uninstall-info-am


#========================================================================
# List of variants one can make.  all is the default.  We always
# presume the simplest of dependencies and remake if includes change
# for example.
#========================================================================
all: $(PROGRAM)

$(PROGRAM): $(OBJECTS) $(PROGLIB_SONAME)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS) 

#========================================================================
# This is cautiously permitted.  REALLY, though, we need a conditional
# that punts with a warning if we try this during an rpm build and
# the library is not found -- the right solution then is to install
# the library first!
#========================================================================
$(PROGLIB_SONAME):
	- (cd ../libdieharder ;\
	 $(MAKE))

#========================================================================
# The only safe place to do commits is in the toplevel directory
#========================================================================
svn:
	(cd ..;make svn)

sync:
	(cd ..;make sync)
# LPR = lpr
printout:
	$(LPR) $(SRCSOURCES) $(SRCINCLUDES)

#========================================================================
#  A standard cleanup target
#========================================================================
clean : 
	- rm -f core $(PROGRAM) *.o $(PROGRAM).1.gz

install : $(PROGRAM)
	(install -d $(prefix)/bin; \
	install -m 755 $(PROGRAM) $(prefix)/bin; \
	install -d $(prefix)/share/man/man1; \
	gzip -c -9 $(PROGRAM).1 > $(PROGRAM).1.gz; \
	install -m 644 $(PROGRAM).1.gz $(prefix)/share/man/man1)

#========================================================================
# We give all generic rules below.  Currently we only need a rule for 
# objects.
#========================================================================
%.o:%.c
	$(CC) -c $(CFLAGS) $<
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
