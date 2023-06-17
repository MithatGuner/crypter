//
// Created by mithat on 17.06.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <zlib.h>
#include <jpeglib.h>
#include "jpg_libs.h"

void encodeStringToJPEG(const char* inputString, const char* outputImage) {
    // Calculate the dimensions of the image based on the input string
    int stringLength = strlen(inputString);
    //int width = stringLength;
    int width = stringLength;
    int height = 1;

    // Allocate memory for pixel data
    uint8_t* pixels = (uint8_t*) malloc(width * height * 3 * sizeof(uint8_t));
    if (pixels == NULL) {
        printf("Error allocating memory\n");
        return;
    }

    // Convert the string to binary and store it in the pixel data
    for (int i = 0; i < stringLength; i++) {
        if (inputString[i] == '1') {
            pixels[i * 3] = 0;   // Red component
            pixels[i * 3 + 1] = 0; // Green component
            pixels[i * 3 + 2] = 0; // Blue component
        } else {
            pixels[i * 3] = 255;   // Red component
            pixels[i * 3 + 1] = 255; // Green component
            pixels[i * 3 + 2] = 255; // Blue component
        }
    }

    // Create JPEG image
    FILE* imageFile = fopen(outputImage, "wb");
    if (imageFile == NULL) {
        printf("Error creating the image file\n");
        free(pixels);
        return;
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, imageFile);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 100, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer;
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer = &pixels[cinfo.next_scanline * width * 3];
        jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(imageFile);
    free(pixels);
}

void decodeJPEGToString(const char* inputImage, char** outputString, int* stringLength) {
    // Open the JPEG image file for reading
    FILE* imageFile = fopen(inputImage, "rb");
    if (imageFile == NULL) {
        printf("Error opening the image file\n");
        return;
    }

    struct jpeg_error_mgr jerr;
    struct jpeg_decompress_struct cinfo;
    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, imageFile);

    // Read JPEG header
    jpeg_read_header(&cinfo, TRUE);

    // Start the decompression
    jpeg_start_decompress(&cinfo);

    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int numComponents = cinfo.output_components;

    // Allocate memory for pixel data
    uint8_t* pixels = (uint8_t*) malloc(width * height * numComponents * sizeof(uint8_t));
    if (pixels == NULL) {
        printf("Error allocating memory\n");
        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        fclose(imageFile);
    }

    // Read scanlines to extract pixel data
    JSAMPROW row_pointer;
    int scanline = 0;
    while (scanline < height) {
        row_pointer = &pixels[scanline * width * numComponents];
        jpeg_read_scanlines(&cinfo, &row_pointer, 1);
        scanline++;
    }

    // Finish the decompression
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(imageFile);

    // Convert the pixel data to binary string
    *stringLength = width;
    *outputString = (char*) malloc((*stringLength + 1) * sizeof(char));
    if (*outputString == NULL) {
        printf("Error allocating memory\n");
        free(pixels);
        return;
    }

    for (int i = 0; i < *stringLength; i++) {
        // Assuming black pixel (0, 0, 0) is binary '1' and white pixel (255, 255, 255) is binary '0'
        int red = pixels[i * numComponents];
        int green = pixels[i * numComponents + 1];
        int blue = pixels[i * numComponents + 2];

        if (red == 0 && green == 0 && blue == 0) {
            (*outputString)[i] = '1';
        } else {
            (*outputString)[i] = '0';
        }
    }
    (*outputString)[*stringLength] = '\0';

    free(pixels);
}
