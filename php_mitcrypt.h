/* mitcrypt extension for PHP */

#ifndef PHP_MITCRYPT_H
# define PHP_MITCRYPT_H

extern zend_module_entry mitcrypt_module_entry;
#define phpext_mitcrypt_ptr &mitcrypt_module_entry

#define PHP_MITCRYPT_AUTHOR "Mithat GUNER"
#define PHP_MITCRYPT_VERSION "1.0.0"
#define ENCRYPTION_KEY "9876666666666666666666"

# if defined(ZTS) && defined(COMPILE_DL_MITCRYPT)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_MITCRYPT_H */
