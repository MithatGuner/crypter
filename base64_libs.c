//
// Created by mithat on 17.06.2023.
//
#include <stdlib.h>
#include <string.h>
#include "base64_libs.h"

void charToBinary(char character, char* binary) {
    for (int i = 7; i >= 0; i--) {
        binary[7 - i] = ((character >> i) & 1) + '0';
    }
}
char* stringToBinary(const char* string) {
    size_t length = strlen(string);
    size_t binaryLength = length * 8;
    char* binaryString = (char*)malloc((binaryLength + 1) * sizeof(char));
    binaryString[binaryLength] = '\0';

    for (size_t i = 0; i < length; i++) {
        charToBinary(string[i], binaryString + (i * 8));
    }

    return binaryString;
}
char* stringToBase64(const char* string) {
    const char base64Chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t stringLength = strlen(string);

    // Calculate the length of the resulting Base64 string
    size_t base64Length = ((stringLength + 2) / 3) * 4;
    char* base64 = (char*)malloc((base64Length + 1) * sizeof(char));
    base64[base64Length] = '\0';

    size_t base64Index = 0;
    size_t stringIndex = 0;

    while (stringIndex < stringLength) {
        unsigned char c1 = string[stringIndex++];
        unsigned char c2 = (stringIndex < stringLength) ? string[stringIndex++] : 0;
        unsigned char c3 = (stringIndex < stringLength) ? string[stringIndex++] : 0;

        // Encode the three characters to four Base64 characters
        unsigned char b1 = c1 >> 2;
        unsigned char b2 = ((c1 & 0x03) << 4) | (c2 >> 4);
        unsigned char b3 = ((c2 & 0x0F) << 2) | (c3 >> 6);
        unsigned char b4 = c3 & 0x3F;

        base64[base64Index++] = base64Chars[b1];
        base64[base64Index++] = base64Chars[b2];
        base64[base64Index++] = (c2 != 0) ? base64Chars[b3] : '=';
        base64[base64Index++] = (c3 != 0) ? base64Chars[b4] : '=';
    }

    return base64;
}
char* base64ToString(const char* base64) {
    const char base64Chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t base64Length = strlen(base64);

    // Calculate the length of the resulting string
    size_t stringLength = (base64Length / 4) * 3;
    if (base64[base64Length - 1] == '=') {
        stringLength--;
        if (base64[base64Length - 2] == '=')
            stringLength--;
    }

    char* string = (char*)malloc((stringLength + 1) * sizeof(char));
    string[stringLength] = '\0';

    size_t base64Index = 0;
    size_t stringIndex = 0;

    while (base64Index < base64Length) {
        unsigned char b1 = strchr(base64Chars, base64[base64Index++]) - base64Chars;
        unsigned char b2 = strchr(base64Chars, base64[base64Index++]) - base64Chars;
        unsigned char b3 = strchr(base64Chars, base64[base64Index++]) - base64Chars;
        unsigned char b4 = strchr(base64Chars, base64[base64Index++]) - base64Chars;

        // Decode the four Base64 characters to three characters
        unsigned char c1 = (b1 << 2) | (b2 >> 4);
        unsigned char c2 = ((b2 & 0x0F) << 4) | (b3 >> 2);
        unsigned char c3 = ((b3 & 0x03) << 6) | b4;

        string[stringIndex++] = c1;
        if (b3 != 64)
            string[stringIndex++] = c2;
        if (b4 != 64)
            string[stringIndex++] = c3;
    }

    return string;
}
// Function to convert binary string to text
char* binaryToText(const char* binary) {
    size_t binaryLength = strlen(binary);

    // Calculate the length of the resulting text string
    size_t textLength = (binaryLength + 7) / 8;
    char* text = (char*)malloc((textLength + 1) * sizeof(char));
    text[textLength] = '\0';

    size_t textIndex = 0;
    size_t binaryIndex = 0;

    while (binaryIndex < binaryLength) {
        unsigned char byte = 0;
        for (int i = 0; i < 8; i++) {
            byte <<= 1;
            if (binary[binaryIndex++] == '1') {
                byte |= 1;
            }
        }
        text[textIndex++] = byte;
    }

    return text;
}