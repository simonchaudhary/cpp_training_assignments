#ifndef FILTER_H
#define FILTER_H

#include "../../types/types.hpp"

class Filter {
public:
	ImageData convertTo2D(const unsigned char* imageData, int width, int height);

	void saveToPNG(const ImageData& imageData, int width, int height, const char* filename);

	void convertToGrayscale(std::vector<std::vector<RGB>>& imageData, int width, int height);

	void sobelEdgeDetection(std::vector<std::vector<RGB>>& imageData, int width, int height, RGB edgeColor, int threshold);

	ImageData createCanvas(int width, int height);

	void placeTileOnCanvas(ImageData& canvas, ImageData& image, int xPos, int yPos, int tileWidth, int tileHeight);


};

#endif // FILTER_H
