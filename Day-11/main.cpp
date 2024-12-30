

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION


#include "../include/common/CommonHeader.hpp"

#include "../include/common/stb/stb_image.h"
#include "../include/common/stb/stb_image_write.h"

#include "../include/common/filter/Filter.cpp"

#include "../include/types/types.hpp"

#include "../include/struct/struct.hpp"


int main(){

	  Filter filter;

    int width = 11000;
    int height = 11000;

    // Create canvas of 1100 x 1100px
    auto mycanvas = filter.createCanvas(width, height);

   int imageWidth, imageHeight, imageChannels;

    unsigned char* imageData = stbi_load("C:/Users/Leapfrog/source/repos/simonchaudhary/cpp_training_assignments/Day-9/images/tile.jpg", &imageWidth, &imageHeight, &imageChannels, 3);

    if (imageData == nullptr) {
       cout << "Image loading failed\n";
    }

    auto image = filter.convertTo2D(imageData,imageWidth, imageHeight);

    int padding = 13;
    
    int repeatWidth = (width + padding)/ (imageWidth+padding);

    int repeatHeight = (height +padding)/ (imageHeight+padding);

    cout << "start repeating\n";

    for (int i = 0; i < repeatHeight;++i) {
      for (int j = 0; j < repeatWidth; ++j) {
        int xPos = j * (imageWidth + padding);
        int yPos = i * (imageHeight + padding);

        cout << xPos << " : " << yPos << '\n';

        filter.placeTileOnCanvas(mycanvas, image,xPos, yPos, imageWidth, imageHeight);
      }
    }

    cout << "complete repeating\n";

    filter.saveToPNG(mycanvas, width, height, "tiled_image_with_padding2.png");

    cout << "Save success\n";

    return 0;
}

