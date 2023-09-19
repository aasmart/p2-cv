#include <iostream>
#include "Image.hpp"
#include "processing.hpp"
#include <fstream>

void invalidArgument() {
    std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
                << "WIDTH and HEIGHT must be less than or equal to original" << std::endl;
}

int main(int argc, char *argv[]) {
    if(argc < 4 || argc > 5) {
        invalidArgument();
        return 1;
    }

    // Get all inputs
    std::string in = argv[1];
    std::string out = argv[2];
    int width = std::stoi(argv[3]);
    int height = -1;
    if(argc == 5)
        height = std::stoi(argv[4]);

    // Read in image
    std::ifstream fileStream;
    fileStream.open(in);

    if(!fileStream.is_open()) {
        std::cout << "Error opening file: " << in << std::endl;
        return 2;
    }

    Image* img = new Image();
    Image_init(img, fileStream);
    fileStream.close();

    // Error checking
    if(argc != 5)
        height = Image_height(img);

    if(width <= 0 || width > Image_width(img)
        || height <= 0 || height > Image_height(img)) 
    {
        invalidArgument();
        return 1;
    }

    // Carve the image
    seam_carve(img, width, height);

    // Output
    std::ofstream fileOutStream;
    fileOutStream.open(out.c_str());

    if(!fileOutStream.is_open()) {
        std::cout << "Error opening file: " << out << std::endl;
        return 2;
    }

    Image_print(img, fileOutStream);
    fileOutStream.close();

    delete img;
    return 0;
}