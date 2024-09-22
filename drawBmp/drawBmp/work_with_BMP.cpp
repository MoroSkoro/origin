#include "work_with_BMP.h"
#include <iostream>

Work_with_BMP::Work_with_BMP() {}

bool Work_with_BMP::openBMP(const std::string& fileName){
    fileBmp.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
    if (!fileBmp.is_open()){
        throw std::string{ "Не удалось открыть файл " + fileName };
        return false;
    }
    return true;
}
void Work_with_BMP::displayBMP(){
    fileBmp.read((char*)&bfh, sizeof(bfh));
    std::cout << "Format is: " << bfh.bfType << std::endl; //19778
    std::cout << "Ofset is: " << bfh.bfOffBits << std::endl;

    fileBmp.read((char*)&bih, sizeof(bih));
    std::cout << "Count bit for pix is: " << bih.biBitCount << std::endl;
    std::cout << "Width is: " << bih.biWidth << std::endl;
    std::cout << "Height is: " << bih.biHeight << std::endl;

    fileBmp.seekg(bfh.bfOffBits, std::ios_base::beg);
    if (bih.biBitCount==24) write_pix_as_char_24();
    else if (bih.biBitCount == 32) write_pix_as_char_32();
    else throw std::string{ "Формат файл не 24 и не 32 бита на пиксель."};
}

void Work_with_BMP::closeBMP() {
    fileBmp.close();
}

void Work_with_BMP::write_pix_as_char_24(){
    size_t padding = 0;
    if ((bih.biWidth * 3) % 4) padding = 4 - (bih.biWidth * 3) % 4;
    for (int i = 0; i < bih.biHeight; i++) {
        for (int j = 0; j < bih.biWidth; j++) {
            fileBmp.read((char*)&rgb, sizeof(rgb));
            if ((rgb.rgbtBlue < 128) && (rgb.rgbtGreen < 128) && (rgb.rgbtRed < 128)) std::cout << "x"; // белый цвет
            else std::cout << " "; // черный цвет 
        }
        std::cout << "\n";
        if (padding != 0) {
            fileBmp.read((char*)&rgb, padding);
        }

    }
}

void Work_with_BMP::write_pix_as_char_32() {
    for (int i = 0; i < bih.biHeight; i++) {
        for (int j = 0; j < bih.biWidth; j++) {
            fileBmp.read((char*)&rgba, sizeof(rgba));
            if ((rgba.rgbBlue < 128) && (rgba.rgbGreen < 128) && (rgba.rgbRed < 128)) std::cout << "x"; // черный цвет
            else std::cout << " "; // белый цвет 
        }
        std::cout << "\n";
    }
}

Work_with_BMP::~Work_with_BMP(){
    if (fileBmp.is_open()) fileBmp.close();
}

