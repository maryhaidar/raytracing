#ifndef BMPWRITER_H
#define BMPWRITER_H

#include <fstream>
#include "colour.h"

const int BYTES_PER_PIXEL = 3;
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;
unsigned char* create_bmp_file_header(int height, int stride);
unsigned char* create_bmp_info_header(int height, int width);

void write_bmp(int argc, char* argv[], int image_width, int image_height, colour** pixel_data) {
    // Default file name
    std::string filename = "image.bmp";

    if (argc > 1) {
        filename = argv[1];
    }

    int width_in_bytes = image_width * BYTES_PER_PIXEL;
    unsigned char padding[3] = {0, 0, 0};
    int padding_size = (4 - (width_in_bytes) % 4) % 4;
    int stride = (width_in_bytes) + padding_size;

    std::ofstream image_file(filename, std::ios::binary);
    
    unsigned char* file_header = create_bmp_file_header(image_height, stride);
    image_file.write(reinterpret_cast<char*>(file_header), FILE_HEADER_SIZE);

    unsigned char* info_header = create_bmp_info_header(image_height, image_width);
    image_file.write(reinterpret_cast<char*>(info_header), INFO_HEADER_SIZE);

    unsigned char* image = new unsigned char[image_height * stride];    // Allocate image buffer

    for (int j = image_height - 1; j >= 0; j--) {   // Iterate in reverse
        for (int i = 0; i < image_width; i++) {
            // Write pixel data to buffer
            int base_index = (j * stride) + (i * BYTES_PER_PIXEL);
            write_colour(image, base_index, pixel_data[j][i]);
        }
        // Write raw data and padding to file
        image_file.write(reinterpret_cast<char*>(image + j * stride), stride);
    }

    delete[] image; // Free allocated memory
    image_file.close();
}

unsigned char* create_bmp_file_header(int height, int stride) {
    int file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char file_header[] = {
        0, 0,           // signature
        0, 0, 0, 0,     // image file size in bytes
        0, 0, 0, 0,     // reserved
        0, 0, 0, 0,     // start of pixel array
    };

    file_header[0]  = static_cast<unsigned char>('B');
    file_header[1]  = static_cast<unsigned char>('M');
    file_header[2]  = static_cast<unsigned char>(file_size);
    file_header[3]  = static_cast<unsigned char>(file_size >> 8);
    file_header[4]  = static_cast<unsigned char>(file_size >> 16);
    file_header[5]  = static_cast<unsigned char>(file_size >> 24);
    file_header[10] = static_cast<unsigned char>(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return file_header;
}

unsigned char* create_bmp_info_header(int height, int width) {
    static unsigned char info_header[] = {
        0, 0, 0, 0,     // header size
        0, 0, 0, 0,     // image width
        0, 0, 0, 0,     // image height
        0, 0,           // number of colour planes
        0, 0,           // bits per pixel
        0, 0, 0, 0,     // compression
        0, 0, 0, 0,     // image size
        0, 0, 0, 0,     // horizontal resolution
        0, 0, 0, 0,     // vertical resolution
        0, 0, 0, 0,     // colours in colour table
        0, 0, 0, 0,     // important colour count
    };

    info_header[0]  = static_cast<unsigned char>(INFO_HEADER_SIZE);
    info_header[4]  = static_cast<unsigned char>(width);
    info_header[5]  = static_cast<unsigned char>(width >> 8);
    info_header[6]  = static_cast<unsigned char>(width >> 16);
    info_header[7]  = static_cast<unsigned char>(width >> 24);
    info_header[8]  = static_cast<unsigned char>(height);
    info_header[9]  = static_cast<unsigned char>(height >> 8);
    info_header[10] = static_cast<unsigned char>(height >> 16);
    info_header[11] = static_cast<unsigned char>(height >> 24);
    info_header[12] = static_cast<unsigned char>(1);
    info_header[14] = static_cast<unsigned char>(BYTES_PER_PIXEL * 8);

    return info_header;
}

#endif