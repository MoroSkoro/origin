#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

class Work_with_BMP
{
public:
	Work_with_BMP();
	bool openBMP(const std::string& fileName);
	void displayBMP();
	void closeBMP();
	~Work_with_BMP();

private:
	std::string file_name;
	std::fstream fileBmp;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	RGBTRIPLE rgb;
	RGBQUAD rgba;
	void write_pix_as_char_24();
	void write_pix_as_char_32();
};

