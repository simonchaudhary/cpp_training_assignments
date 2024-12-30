

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <algorithm>

#include "../include/common/CommonHeader.hpp"

#include "../include/common/stb/stb_image.h"
#include "../include/common/stb/stb_image_write.h"

#include "../include/common/filter/Filter.cpp"

#include "../include/types/types.hpp"

#include "../include/struct/struct.hpp"

struct Pixel {
  int xPosition;
  int yPosition;

  Pixel(int x, int y) :xPosition(x), yPosition(y) {}
};


struct Point {
  int x;
  int y;

  Point(int xPosition, int yPosition) :x(xPosition), y(yPosition) {}
};


struct Box {
  Point topLeft;
  Point topRight;
  Point bottomRight;
  Point bottomLeft;

  Box() : topLeft(0, 0), topRight(0, 0), bottomRight(0, 0), bottomLeft(0, 0) {};


   //Constructor to require initialization
  Box(Point tl, Point tr, Point br, Point bl)
    : topLeft(tl), topRight(tr), bottomRight(br), bottomLeft(bl) {
  };



  // Helper method to print all corners
  void printCorners() const {
    cout << "Box Corners:\n";
    cout << "Top-left: (" << topLeft.x << ", " << topLeft.y << ")\n";
    cout << "Top-right: (" << topRight.x << ", " << topRight.y << ")\n";
    cout << "Bottom-left: (" << bottomLeft.x << ", " << bottomLeft.y << ")\n";
    cout << "Bottom-right: (" << bottomRight.x << ", " << bottomRight.y << ")\n";
  };

};

void printImage(const vector<vector<RGB>>& image) {
  for (const auto& row : image) {
    for (const auto& pixel : row) {
      cout << "(" << (int)pixel.r << ", " << (int)pixel.g << ", " << (int)pixel.b << ") ";
    }
    cout << '\n';
  }
};

int main() {

  Filter filter;

  int imageWidth, imageHeight, imageChannels;

  unsigned char* imageData = stbi_load("C:/Users/Leapfrog/source/repos/simonchaudhary/cpp_training_assignments/Day-12/images/maze.jpg", &imageWidth, &imageHeight, &imageChannels, 3);

  if (imageData == nullptr) {
    cout << "Image loading failed\n";
  }

	cout << "Image loaded successfully\n";

  auto image = filter.convertTo2D(imageData, imageWidth, imageHeight);

  // Apply Bright to Image by 40%.
  //filter.brightenImage(image, 1.4f);

  //filter.sharpen(image);

  // Initial point.
  //Box aBox(Point(-1, -1), Point(-1, -1), Point(-1, -1), Point(-1, -1));

 
  
  int myMaxX = -1;  // Initialize to -1, assuming no valid pixel initially
  int myMaxY = -1;

  // Using Box
  //for (int i = 0; i < image.size(); i++) {
  //		//pixelrow row;
  //	for (int j = 0; j < image[i].size(); j++) {
  //    if (image[i][j].r >= 200 && image[i][j].g <= 90 && image[i][j].b <= 90) {
  //      //cout << "y: " << i << " x: " << j << "\n";
  //      if (j > myMaxX) {
  //        myMaxX = j;  // Update x position (column index)
  //      }

  //      if (i > myMaxY) {
  //        myMaxY = i;  // Update y position (row index)
  //      }

  //      if (aBox.topLeft.x == -1) {
  //        aBox.topLeft.x = j;
  //      }

  //      if (aBox.topLeft.y == -1) {
  //        aBox.topLeft.y = i;
  //      }

  //      if (j == myMaxX) {
  //        aBox.topRight.x = j;
  //      }

  //      if (aBox.topRight.y == -1) {
  //        aBox.topRight.y = i;
  //      }

  //      // Update bottom-left (smallest x and largest y)
  //      aBox.bottomLeft.x = aBox.topLeft.x;
  //      

  //      if (i == myMaxY) {
  //        aBox.bottomLeft.y = i;
  //      }

  //      // Update bottom-right (largest x and y)
  //      aBox.bottomRight.x = aBox.topRight.x;

  //      aBox.bottomRight.y = aBox.bottomLeft.y;

  //      // Change color to green
  //     /* image[i][j].r = 0;
  //		  image[i][j].g = 255;
  //		  image[i][j].b = 26;*/

  //    }

  //	}
  //}

  //aBox.printCorners();

  //image[aBox.topLeft.y][aBox.topLeft.x].r = 0;
  //image[aBox.topLeft.y][aBox.topLeft.x].g = 0;
  //image[aBox.topLeft.y][aBox.topLeft.x].b = 0;

  //image[aBox.topRight.y][aBox.topRight.x].r = 0;
  //image[aBox.topRight.y][aBox.topRight.x].g = 0;
  //image[aBox.topRight.y][aBox.topRight.x].b = 0;

  //image[aBox.bottomRight.y][aBox.bottomRight.x].r = 0;
  //image[aBox.bottomRight.y][aBox.bottomRight.x].g = 0;
  //image[aBox.bottomRight.y][aBox.bottomRight.x].b = 0;

  //image[aBox.bottomLeft.y][aBox.bottomLeft.x].r = 0;
  //image[aBox.bottomLeft.y][aBox.bottomLeft.x].g = 0;
  //image[aBox.bottomLeft.y][aBox.bottomLeft.x].b = 0;

  //filter.saveToPNG(image, 500, 500, "my_redbox.png");






  //  cout << "saved to box\n";



  //ImageData redbox;

  //RGB color;

  Pixel pixel(0, static_cast<int>(image.size()));


  

	for (int i = 0; i < image.size(); i++) {
			//PixelRow row;
		for (int j = 0; j < image[i].size(); j++) {


      if (image[i][j].r >= 200 && image[i][j].g <= 90 && image[i][j].b <= 90) {
			cout << "i: " << i << " j: " << j << "\n";
      
      pixel.yPosition = std::min(pixel.yPosition,i);

      pixel.xPosition = std::max(pixel.xPosition, j);

      image[i][j].r = 0;
			image[i][j].g = 255;
			image[i][j].b = 26;

      }
		}
	}

  int xBreak;
  int yBreak;

  cout << "x: " << pixel.xPosition << "y : " << pixel.yPosition << "\n";

    
  for (int j = pixel.xPosition; j < image.size(); j++) {
    if (image[pixel.yPosition][j].r >= 240 && image[pixel.yPosition][j].g >= 240 && image[pixel.yPosition][j].b >= 240) {

      cout << "Break at x: " << j << '\n';
      // Reduce pixel after hit the boundry
      xBreak = j-10;

      break;
    }

    image[pixel.yPosition][j].r = 127;
    image[pixel.yPosition][j].g = 17;
    image[pixel.yPosition][j].b = 224;
  }

  for (int j = pixel.yPosition; j < image.size(); j++) {
    if (image[j][xBreak].r >= 240 && image[j][xBreak].g >= 240 && image[j][xBreak].b >= 240) {

      cout << "Break at x: " << j << '\n';
      yBreak = j - 10;

      break;
    }

    image[j][xBreak].r = 127;
    image[j][xBreak].g = 17;
    image[j][xBreak].b = 224;
  }


  for (int j = xBreak; j < image.size(); j++) {
    if (image[yBreak][j].r >= 240 && image[yBreak][j].g >= 240 && image[yBreak][j].b >= 240) {

      cout << "Break at x: " << j << '\n';
      // Reduce pixel after hit the boundry
      xBreak = j - 10;

      break;
    }

    image[yBreak][j].r = 127;
    image[yBreak][j].g = 17;
    image[yBreak][j].b = 224;
  }

  for (int j = yBreak; j < image.size(); j++) {
    if (image[j][xBreak].r >= 240 && image[j][xBreak].g >= 240 && image[j][xBreak].b >= 240) {

      cout << "Break at x: " << j << '\n';
      yBreak = j - 10;

      break;
    }

    image[j][xBreak].r = 127;
    image[j][xBreak].g = 17;
    image[j][xBreak].b = 224;
  }

  for (int j = xBreak; j < image.size(); j++) {
    if (image[yBreak][j].r >= 240 && image[yBreak][j].g >= 240 && image[yBreak][j].b >= 240) {

      cout << "Break at x: " << j << '\n';
      // Reduce pixel after hit the boundry
      xBreak = j - 10;

      break;
    }

    image[yBreak][j].r = 127;
    image[yBreak][j].g = 17;
    image[yBreak][j].b = 224;
  }

  for (int j = yBreak; j < image.size(); j++) {
    if (image[j][xBreak].r >= 240 && image[j][xBreak].g >= 240 && image[j][xBreak].b >= 240) {

      cout << "Break at x: " << j << '\n';
      yBreak = j - 10;

      break;
    }

    image[j][xBreak].r = 127;
    image[j][xBreak].g = 17;
    image[j][xBreak].b = 224;
  }


  filter.saveToPNG(image, 500, 500, "my_redbox_old.png");

  return 0;
}


