/* mitcrypt extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <string.h>
#include <stdlib.h>
#include "php.h"
#include "ext/standard/info.h"
#include "php_mitcrypt.h"
#include "base64_libs.h"
#include "jpg_libs.h"

PHP_FUNCTION(mitcrypt_encode)
{
    char *input_string;
    size_t input_string_len;

    char *filename_string;
    size_t filename_string_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &input_string, &input_string_len, &filename_string, &filename_string_len) == FAILURE) {
        RETURN_NULL();
    }

    char *base64 = stringToBase64(input_string);
    char *binary = stringToBinary(base64);
    char *string = binaryToText(binary);

    size_t binary_len = strlen(binary);
    char *key = ENCRYPTION_KEY;
    size_t key_len = strlen(key);

    char * encrypted = NULL;
    encrypted = (char *) malloc( sizeof *binary * binary_len );
    for (size_t i = 0; i < binary_len + 1; i++) {
        encrypted[i] = binary[i] ^ key[i % key_len];
    }

    encodeStringToJPEG(stringToBinary(encrypted), filename_string);
    RETURN_STRING(stringToBinary(encrypted));

}


PHP_FUNCTION(mitcrypt_decode)
{


    char *filename_string;
    size_t filename_string_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &filename_string, &filename_string_len) == FAILURE) {
        RETURN_NULL();
    }

    const char* inputImage = filename_string;
    char* decodedString;
    int stringLength;
    // Decode the JPEG image and extract the binary data
    decodeJPEGToString(inputImage, &decodedString, &stringLength);
    if(!decodedString)
        RETURN_BOOL(0);

    char * decrypted = NULL;
    size_t encrypted_len = strlen(decodedString);
    char *key = ENCRYPTION_KEY;
    size_t key_len = strlen(key);


    char *binaryToDecode = binaryToText(decodedString);
    size_t binaryToDecode_len = strlen(decodedString);

    decrypted = (char *) malloc( binaryToDecode_len * sizeof(char) );
    for (size_t i = 0; i < binaryToDecode_len; i++) {
        decrypted[i] = binaryToDecode[i] ^ key[i % key_len];
    }


    RETURN_STRING(base64ToString(binaryToText(decrypted)));

}

ZEND_BEGIN_ARG_INFO(arginfo_mitcrypt_encode, 0)
    ZEND_ARG_INFO(0,str)
    ZEND_ARG_INFO(0,filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mitcrypt_decode, 0)
    ZEND_ARG_INFO(0,filename)
ZEND_END_ARG_INFO()

const zend_function_entry mitcrypt_functions[] = {
    PHP_FE(mitcrypt_encode, arginfo_mitcrypt_encode)
    PHP_FE(mitcrypt_decode, arginfo_mitcrypt_decode)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(mitcrypt)
{
    /* Here the module is being initialized */
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(mitcrypt)
{
    /* Here the module is deinitialized */
    return SUCCESS;
}

PHP_RINIT_FUNCTION(mitcrypt)
{
#if defined(ZTS) && defined(COMPILE_DL_MITCRYPT)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif

    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(mitcrypt)
{
    /* Here the module is deinitialized for a given request */
    return SUCCESS;
}

PHP_MINFO_FUNCTION(mitcrypt)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "mitcrypt support", "enabled");
    php_info_print_table_row(2, "Version", PHP_MITCRYPT_VERSION);
    php_info_print_table_row(2, "Author", PHP_MITCRYPT_AUTHOR);
    php_info_print_table_end();
}

zend_module_entry mitcrypt_module_entry = {
    STANDARD_MODULE_HEADER,
    "mitcrypt", /* Extension name */
    mitcrypt_functions, /* zend_function_entry */
    PHP_MINIT(mitcrypt), /* PHP_MINIT - Module initialization */
    PHP_MSHUTDOWN(mitcrypt), /* PHP_MSHUTDOWN - Module shutdown */
    PHP_RINIT(mitcrypt), /* PHP_RINIT - Request initialization */
    PHP_RSHUTDOWN(mitcrypt), /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(mitcrypt), /* PHP_MINFO - Module info */
    PHP_MITCRYPT_VERSION, /* Version */
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MITCRYPT
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(mitcrypt)
#endif
