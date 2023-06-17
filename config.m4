PHP_ARG_ENABLE(mitcrypt, whether to enable mitcrypt support,
[  --enable-mitcrypt          Enable mitcrypt support], no)

if test "$PHP_MITCRYPT" != "no"; then
  AC_DEFINE(HAVE_MITCRYPT, 1, [ Have mitcrypt support ])
  PHP_NEW_EXTENSION(mitcrypt, mitcrypt.c base64_libs.c jpg_libs.c, $ext_shared)
fi
