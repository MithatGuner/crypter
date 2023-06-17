//
// Created by mithat on 17.06.2023.
//

#ifndef PHP_MITCRYPT_BASE64_LIBS_H
#define PHP_MITCRYPT_BASE64_LIBS_H
void charToBinary(char character, char* binary);
char* stringToBinary(const char* string);
char* stringToBase64(const char* string);
char* base64ToString(const char* base64);
char* binaryToText(const char* binary);
#endif //PHP_MITCRYPT_BASE64_LIBS_H
