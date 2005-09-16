dnl $Id$
dnl config.m4 for extension rpmreader

dnl If your extension references something external, use with:

PHP_ARG_WITH(rpmreader, for RPM file support,
dnl Make sure that the comment is aligned:
[  --with-rpmreader             Include RPM file support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(rpmreader, whether to enable rpmreader support,
dnl Make sure that the comment is aligned:
dnl [  --enable-rpmreader           Enable rpmreader support])

if test "$PHP_RPMREADER" != "no"; then
  dnl Write more examples of tests here...

  PHP_NEW_EXTENSION(rpmreader, rpmreader.c rpmreader_io.c, $ext_shared)

fi
