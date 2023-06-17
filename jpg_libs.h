//
// Created by mithat on 17.06.2023.
//

#ifndef PHP_MITCRYPT_JPG_LIBS_H
#define PHP_MITCRYPT_JPG_LIBS_H
void encodeStringToJPEG(const char* inputString, const char* outputImage);
void decodeJPEGToString(const char* inputImage, char** outputString, int* stringLength);
#endif //PHP_MITCRYPT_JPG_LIBS_H
