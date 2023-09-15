#include <iostream>
#include "Image.hpp"
#include "processing.hpp"
#include <fstream>

int main(int argc, char *argv[]) {
    if(argc < 4 || argc > 5) {
        std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
                << "WIDTH and HEIGHT must be less than or equal to original" << std::endl;
        return 1;
    }

    std::string in = argv[1];
    std::string out = argv[2];
    int width = std::stoi(argv[3]);
    int height = -1;
    if(argc == 5)
        height = std::stoi(argv[4]);

    std::ifstream fileStream;
    fileStream.open(in);

    if(!fileStream.is_open()) {
        std::cout << "Error opening file: " << in << std::endl;
        return 2;
    }

    Image* img = new Image();
    Image_init(img, fileStream);

    if(argc != 5)
        height = Image_height(img);

    seam_carve(img, width, height);

    fileStream.close();
    std::ofstream fileOutStream;
    fileOutStream.open(out.c_str());

    Image_print(img, fileOutStream);

    fileOutStream.close();

    delete img;

    return 0;
}