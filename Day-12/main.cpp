//
//
//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//
//#include <algorithm>
//
//#include "../include/common/CommonHeader.hpp"
//
//#include "../include/common/stb/stb_image.h"
//#include "../include/common/stb/stb_image_write.h"
//
//#include "../include/common/filter/Filter.cpp"
//
//#include "../include/types/types.hpp"
//
//#include "../include/struct/struct.hpp"
//
//struct Pixel {
//  int xPosition;
//  int yPosition;
//
//  Pixel(int x, int y) :xPosition(x), yPosition(y) {}
//};
//
//
//void printImage(const vector<vector<RGB>>& image) {
//  for (const auto& row : image) {
//    for (const auto& pixel : row) {
//      cout << "(" << (int)pixel.r << ", " << (int)pixel.g << ", " << (int)pixel.b << ") ";
//    }
//    cout << '\n';
//  }
//};
//
//int main() {
//
//  Filter filter;
//
//  int imageWidth, imageHeight, imageChannels;
//
//  unsigned char* imageData = stbi_load("C:/Users/Leapfrog/source/repos/simonchaudhary/cpp_training_assignments/Day-12/images/maze.jpg", &imageWidth, &imageHeight, &imageChannels, 3);
//
//  if (imageData == nullptr) {
//    cout << "Image loading failed\n";
//  }
//
//	cout << "Image loaded successfully\n";
//
//  auto image = filter.convertTo2D(imageData, imageWidth, imageHeight);
//
//
//  Pixel pixel(0, static_cast<int>(image.size()));
//
//
//  
//
//	for (int i = 0; i < image.size(); i++) {
//			//PixelRow row;
//		for (int j = 0; j < image[i].size(); j++) {
//
//
//      if (image[i][j].r >= 200 && image[i][j].g <= 90 && image[i][j].b <= 90) {
//			cout << "i: " << i << " j: " << j << "\n";
//      
//      pixel.yPosition = std::min(pixel.yPosition,i);
//
//      pixel.xPosition = std::max(pixel.xPosition, j);
//
//      image[i][j].r = 0;
//			image[i][j].g = 255;
//			image[i][j].b = 26;
//
//      }
//		}
//	}
//
//  int xBreak;
//  int yBreak;
//
//  cout << "x: " << pixel.xPosition << "y : " << pixel.yPosition << "\n";
//
//    
//  for (int j = pixel.xPosition; j < image.size(); j++) {
//    if (image[pixel.yPosition][j].r >= 240 && image[pixel.yPosition][j].g >= 240 && image[pixel.yPosition][j].b >= 240) {
//
//      cout << "Break at x: " << j << '\n';
//      // Reduce pixel after hit the boundry
//      xBreak = j-10;
//
//      break;
//    }
//
//    image[pixel.yPosition][j].r = 127;
//    image[pixel.yPosition][j].g = 17;
//    image[pixel.yPosition][j].b = 224;
//  }
//
//  for (int j = pixel.yPosition; j < image.size(); j++) {
//    if (image[j][xBreak].r >= 240 && image[j][xBreak].g >= 240 && image[j][xBreak].b >= 240) {
//
//      cout << "Break at x: " << j << '\n';
//      yBreak = j - 10;
//
//      break;
//    }
//
//    image[j][xBreak].r = 127;
//    image[j][xBreak].g = 17;
//    image[j][xBreak].b = 224;
//  }
//
//
//  for (int j = xBreak; j < image.size(); j++) {
//    if (image[yBreak][j].r >= 240 && image[yBreak][j].g >= 240 && image[yBreak][j].b >= 240) {
//
//      cout << "Break at x: " << j << '\n';
//      // Reduce pixel after hit the boundry
//      xBreak = j - 10;
//
//      break;
//    }
//
//    image[yBreak][j].r = 127;
//    image[yBreak][j].g = 17;
//    image[yBreak][j].b = 224;
//  }
//
//  for (int j = yBreak; j < image.size(); j++) {
//    if (image[j][xBreak].r >= 240 && image[j][xBreak].g >= 240 && image[j][xBreak].b >= 240) {
//
//      cout << "Break at x: " << j << '\n';
//      yBreak = j - 10;
//
//      break;
//    }
//
//    image[j][xBreak].r = 127;
//    image[j][xBreak].g = 17;
//    image[j][xBreak].b = 224;
//  }
//
//  for (int j = xBreak; j < image.size(); j++) {
//    if (image[yBreak][j].r >= 240 && image[yBreak][j].g >= 240 && image[yBreak][j].b >= 240) {
//
//      cout << "Break at x: " << j << '\n';
//      // Reduce pixel after hit the boundry
//      xBreak = j - 10;
//
//      break;
//    }
//
//    image[yBreak][j].r = 127;
//    image[yBreak][j].g = 17;
//    image[yBreak][j].b = 224;
//  }
//
//  for (int j = yBreak; j < image.size(); j++) {
//    if (image[j][xBreak].r >= 240 && image[j][xBreak].g >= 240 && image[j][xBreak].b >= 240) {
//
//      cout << "Break at x: " << j << '\n';
//      yBreak = j - 10;
//
//      break;
//    }
//
//    image[j][xBreak].r = 127;
//    image[j][xBreak].g = 17;
//    image[j][xBreak].b = 224;
//  }
//
//
//  filter.saveToPNG(image, 500, 500, "my_redbox_old.png");
//
//  return 0;
//}
//
//
//

//
//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//
//#include <algorithm>
//#include <queue>
//#include "../include/common/CommonHeader.hpp"
//#include "../include/common/stb/stb_image.h"
//#include "../include/common/stb/stb_image_write.h"
//#include "../include/common/filter/Filter.cpp"
//#include "../include/types/types.hpp"
//#include "../include/struct/struct.hpp"
//
//struct Pixel {
//  int x;
//  int y;
//
//  Pixel(int x, int y) : x(x), y(y) {}
//};
//
//void bfsProcessImage(std::vector<std::vector<RGB>>& image, int startX, int startY, RGB targetColor, RGB newColor) {
//  int rows = image.size();
//  int cols = image[0].size();
//
//  std::queue<Pixel> pixelQueue;
//  pixelQueue.push(Pixel(startX, startY));
//
//  // Directions for neighboring pixels (N, S, E, W)
//  std::vector<std::pair<int, int>> directions = {
//      {-1, 0}, {1, 0}, {0, -1}, {0, 1}
//  };
//
//  while (!pixelQueue.empty()) {
//    Pixel current = pixelQueue.front();
//    pixelQueue.pop();
//
//    int x = current.x;
//    int y = current.y;
//
//    // Check bounds
//    if (x < 0 || x >= cols || y < 0 || y >= rows) continue;
//
//    // Skip if pixel color does not match target
//    if (image[y][x].r != targetColor.r ||
//      image[y][x].g != targetColor.g ||
//      image[y][x].b != targetColor.b) {
//      continue;
//    }
//
//    // Change pixel color
//    image[y][x] = newColor;
//
//    // Push neighboring pixels
//    for (const auto& dir : directions) {
//      int newX = x + dir.first;
//      int newY = y + dir.second;
//      pixelQueue.push(Pixel(newX, newY));
//    }
//  }
//}
//
//int main() {
//  Filter filter;
//
//  int imageWidth, imageHeight, imageChannels;
//  unsigned char* imageData = stbi_load("C:/Users/Leapfrog/source/repos/simonchaudhary/cpp_training_assignments/Day-12/images/maze.jpg", &imageWidth, &imageHeight, &imageChannels, 3);
//
//  if (imageData == nullptr) {
//    std::cout << "Image loading failed\n";
//    return 1;
//  }
//
//  std::cout << "Image loaded successfully\n";
//
//  auto image = filter.convertTo2D(imageData, imageWidth, imageHeight);
//
//  // Define target and new colors
//  RGB targetColor = { 200, 90, 90 }; // Pixels to be processed
//  RGB newColor = { 0, 255, 26 }; // New color to set
//
//  // Start BFS from a seed point (0, 0) or any point that satisfies your condition
//  bfsProcessImage(image, 0, 0, targetColor, newColor);
//
//  filter.saveToPNG(image, imageWidth, imageHeight, "bfs_output.png");
//
//  stbi_image_free(imageData);
//  return 0;
//}
