#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.52)

m4_define([required_lttoolbox_version], [3.5.0])
m4_define([required_libxml_version], [2.6.17])
m4_define([required_libpcre_version], [6.4])

AC_INIT([apertium], [3.5.2], [sortiz@users.sourceforge.net])
AC_CONFIG_HEADER([apertium/apertium_config.h])

AC_CANONICAL_SYSTEM

GENERIC_LIBRARY_NAME=apertium

# Release versioning
GENERIC_MAJOR_VERSION=3
GENERIC_MINOR_VERSION=5
GENERIC_MICRO_VERSION=2

# API version (often = GENERIC_MAJOR_VERSION.GENERIC_MINOR_VERSION)
GENERIC_API_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION
AC_SUBST(GENERIC_API_VERSION)
AC_SUBST(GENERIC_MAJOR_VERSION)

# Shared library versioning
GENERIC_LIBRARY_VERSION=1:0:0
#                       | | |
#                +------+ | +---+
#                |        |     |
#             current:revision:age
#                |        |     |
#                |        |     +- increment if interfaces have been added
#                |        |        set to zero if interfaces have been removed
#                                  or changed
#                |        +- increment if source code has changed
#                |           set to zero if current is incremented
#                +- increment if interfaces have been added, removed or changed

AC_SUBST(GENERIC_LIBRARY_VERSION)
PACKAGE=$GENERIC_LIBRARY_NAME
AC_SUBST(GENERIC_LIBRARY_NAME)

GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
GENERIC_RELEASE=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION
AC_SUBST(GENERIC_RELEASE)
AC_SUBST(GENERIC_VERSION)

VERSION=$GENERIC_VERSION

AM_INIT_AUTOMAKE(no-define)
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX
AC_PROG_LIBTOOL
AC_LANG_CPLUSPLUS

CFLAGS="-Wall -Wextra $CFLAGS"
CXXFLAGS="-Wall -Wextra $CXXFLAGS"

AC_ARG_ENABLE(debug,
              [  --enable-debug    Enable "-g -Wall" compiler options],
              [CXXFLAGS="-g -Wall"; CFLAGS="-g -Wall"; AC_DEFINE([ENABLE_DEBUG], [1], [ENABLE_DEBUG])])

AC_ARG_ENABLE(profile,
              [  --enable-profile  Enable "-pg -g -Wall" compiler options],
              [CXXFLAGS="-pg -g -Wall"; CFLAGS="-pg -g -Wall"; LDFLAGS="-pg"])


AC_PATH_PROG(XMLLINT, xmllint, no)
if test x$ac_cv_path_XMLLINT = x
then
  AC_MSG_ERROR([You don't have xmllint installed.])
fi
if test x$ac_cv_path_XMLLINT = xno
then
  AC_MSG_ERROR([You don't have xmllint installed.])
fi

  AC_PATH_PROG(XSLTPROC, xsltproc, no)
  if test x$ac_cv_path_XSLTPROC = x
  then
    AC_MSG_ERROR([You don't have xsltproc installed.])
  fi
  if test x$ac_cv_path_XSLTPROC = xno
  then
    AC_MSG_ERROR([You don't have xsltproc installed.])
  fi

AC_PATH_PROG(BASH, bash, no)
if test x$ac_cv_path_BASH = x
then
  AC_MSG_ERROR([You don't have bash installed.])
fi
if test x$ac_cv_path_BASH = xno
then
  AC_MSG_ERROR([You don't have bash installed.])
fi

AC_PATH_PROG(FLEX, flex, no)
if test x$ac_cv_path_FLEX = x
then
  AC_MSG_ERROR([You don't have flex installed.])
fi
if test x$ac_cv_path_FLEX = xno
then
  AC_MSG_ERROR([You don't have flex installed.])
fi

AC_CHECK_FUNCS(strcasecmp)

if test x$(uname) != xDarwin;
then
AC_CHECK_HEADER(pcreposix.h,
  AC_CHECK_LIB(pcre, pcre_fullinfo,[
    LIBS="$LIBS -lpcreposix -lpcre"
    no_comp_check=yes],
    AC_MSG_ERROR([*** unable to locate pcre library ***])),
  AC_MSG_ERROR([*** unable to locate pcreposix.h include file ***]))

AC_CHECK_HEADER(pcrecpp.h,
  AC_CHECK_LIB(pcrecpp,pcre_compile,[
  LIBS="$LIBS -lpcrecpp"
  no_comp_check=yes],
  AC_MSG_ERROR([*** unable to locate pcrecpp library ***])),
  AC_MSG_ERROR([*** unable to locate pcrecpp.h include file ***]))
fi


PKG_CHECK_MODULES(APERTIUM, [
  lttoolbox >= required_lttoolbox_version
  libxml-2.0 >= required_libxml_version
  libpcre >= required_libpcre_version], CPPFLAGS="$CPPFLAGS $APERTIUM_CFLAGS"; LIBS="$LIBS $APERTIUM_LIBS")

# Check for wide strings
AC_DEFUN([AC_CXX_WSTRING],[
  AC_CACHE_CHECK(whether the compiler supports wide strings,
  ac_cv_cxx_wstring,
  [AC_LANG_SAVE
   AC_LANG_CPLUSPLUS
   AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <string>]],[[
std::wstring test = L"test";
   ]])],
   [ac_cv_cxx_wstring=yes], [ac_cv_cxx_wstring=no])
   AC_LANG_RESTORE
  ])
])

AC_CXX_WSTRING
AC_C_BIGENDIAN

if test "$ac_cv_cxx_wstring" = no
then
  AC_MSG_ERROR([Missing wide string support])
fi


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h unistd.h stddef.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE

AC_CHECK_DECLS([fread_unlocked, fwrite_unlocked, fgetc_unlocked, fputc_unlocked, fputs_unlocked, getopt, getopt_long, fgetwc_unlocked, fputwc_unlocked, fgetws_unlocked, fputws_unlocked])
AC_CHECK_FUNCS([setlocale strdup getopt snprintf mbtowc])
AC_REPLACE_FUNCS(getopt_long)

AM_CONDITIONAL([WINDOWS], [test x$version_type = xwindows])
#AS_IF([test x$version_type = xwindows], [AC_DEFINE(HAVE_GETOPT_LONG,0)], [])

# Checks for highest supported C++ standard
AC_LANG(C++)
AX_CHECK_COMPILE_FLAG([-std=c++20], [CXXFLAGS="$CXXFLAGS -std=c++20"], [
 AX_CHECK_COMPILE_FLAG([-std=c++2a], [CXXFLAGS="$CXXFLAGS -std=c++2a"], [
  AX_CHECK_COMPILE_FLAG([-std=c++17], [CXXFLAGS="$CXXFLAGS -std=c++17"], [
   AX_CHECK_COMPILE_FLAG([-std=c++1z], [CXXFLAGS="$CXXFLAGS -std=c++1z"], [
    AX_CHECK_COMPILE_FLAG([-std=c++14], [CXXFLAGS="$CXXFLAGS -std=c++14"], [
     AX_CHECK_COMPILE_FLAG([-std=c++1y], [CXXFLAGS="$CXXFLAGS -std=c++1y"], [
      AX_CHECK_COMPILE_FLAG([-std=c++11], [CXXFLAGS="$CXXFLAGS -std=c++11"], [])
     ])
    ])
   ])
  ])
 ])
])

AC_CONFIG_FILES([python/setup.py])

AC_SUBST(APERTIUM_CFLAGS)
AC_SUBST(LIBS)

AM_PATH_PYTHON([3.4], [], [AC_MSG_WARN([Can't generate SWIG wrapper or run tests without Python])])

AC_ARG_ENABLE([python-bindings],
              AS_HELP_STRING([--enable-python-bindings],
                             [build python bindings (default=disabled)]),
              [enable_python_bindings=$enableval],
              [enable_python_bindings=no])
AM_CONDITIONAL([HAVE_PYTHON_BINDINGS], [test x$enable_python_bindings = xyes])

AC_OUTPUT([Makefile apertium.pc apertium/Makefile tests/Makefile tests/tagger/Makefile python/Makefile])
