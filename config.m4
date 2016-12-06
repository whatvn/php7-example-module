dnl $Id$
dnl config.m4 for extension example

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(example, for example support,
dnl Make sure that the comment is aligned:
[  --with-example            Include example support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(example, whether to enable example support,
dnl Make sure that the comment is aligned:
dnl [  --enable-example           Enable example support])

if test "$PHP_EXAMPLE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-example -> check with-path
  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  EXAMPLE_DIR=$PHP_EXAMPLE
  dnl
  if test -z "$EXAMPLE_DIR"; then
      EXAMPLE_CFLAGS= "$EXAMPLE_CFLAGS"
  fi


  dnl
  PHP_SUBST(EXAMPLE_CFLAGS)
  PHP_SUBST(EXAMPLE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(example, example.c, $ext_shared)
fi
