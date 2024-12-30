#ifndef FILTER_H
#define FILTER_H

//#include <algorithm>

#include "../../types/types.hpp"

class Filter {
public:
	ImageData convertTo2D(const unsigned char* imageData, int width, int height);

	void saveToPNG(const ImageData& imageData, int width, int height, const char* filename);

	void convertToGrayscale(ImageData& imageData, int width, int height);

	//void sobelEdgeDetection(ImageData& imageData, int width, int height, RGB edgeColor, int threshold);


	void sobelEdgeDetection(ImageData& imageData, int width, int height);

	ImageData createCanvas(int width, int height);

	void placeTileOnCanvas(ImageData& canvas, ImageData& image, int xPos, int yPos, int tileWidth, int tileHeight);

	//void applyMedianFilter(ImageData& imageData);

	void brightenImage(ImageData& image, float brightnessFactor);

	void sharpen(ImageData& image);

};

#endif // FILTER_H
