#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <vector>

#include "./stb/stb_image.h"
#include "./stb/stb_image_write.h"

using std::cout;
using std::vector;


struct RGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

using PixelRow = vector<RGB>;         // A single row of pixels
using ImageData = vector<PixelRow>;  // The entire image as a 2D vector

std::vector<std::vector<RGB>> convertTo2D(const unsigned char* imageData, int width, int height) {
  std::vector<std::vector<RGB>> output;
  int length = width * height * 3;
  RGB color;

  for (int i = 0;i < height;++i) {
    std::vector<RGB> row;
    for (int j = 0; j < width * 3;j += 3) {
      color.r = imageData[i * width * 3 + j + 0];
      color.g = imageData[i * width * 3 + j + 1];
      color.b = imageData[i * width * 3 + j + 2];
      row.emplace_back(color);
    }
    output.emplace_back(row);

  }

  return output;
}

ImageData convertTo2D2(const unsigned char* imageDAta, int widhth, int height) {
  ImageData output;

  
}



// Function to convert an image to grayscale
void convertToGrayscale(ImageData& image) {
  for (auto& row : image) {
    for (auto& pixel : row) {

      // Calculate grayscale intensity
      uint8_t gray = static_cast<uint8_t>(pixel.r * 0.2989 + pixel.g * 0.5870 + pixel.b * 0.1140);

      // Set all RGB channels to the calculated intensity
      pixel.r = pixel.g = pixel.b = gray;
    }
  }
}

	

int main() {
  int width,height,channels;

  unsigned char* imageData = stbi_load("C:/Users/Leapfrog/source/repos/simonchaudhary/cpp_training_assignments/Day-9/images/grain_noise.jpeg",&width,&height,&channels,3);

  if(imageData==nullptr){
        cout<<"Image loading failed\n";
  }

  cout << "Image load success\n";


   // Sample 2D image (5x5 grid)
  //ImageData image = {
  //  {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0}, {0, 255, 255}},
  //  {{255, 0, 255}, {128, 128, 128}, {64, 64, 64}, {192, 192, 192}, {0, 0, 0}},
  //  {{255, 255, 255}, {100, 150, 200}, {50, 50, 50}, {0, 255, 128}, {128, 0, 255}},
  //  {{255, 128, 0}, {0, 128, 255}, {128, 255, 0}, {64, 128, 192}, {32, 64, 128}},
  //  {{0, 0, 0}, {255, 255, 255}, {128, 128, 128}, {192, 192, 192}, {64, 64, 64}}
  //};

  //for (const auto& row : image) {
  //  for (const auto& pixel : row) {
  //    cout << "(" << (int)pixel.r << ", " << (int)pixel.g << ", " << (int)pixel.b << ") ";
  //  }

  //  cout << "\n";
  //}

  //convertToGrayscale(image);

  //cout << '\n';

  //for (const auto& row : image) {
  //  for (const auto& pixel : row) {
  //    cout << "(" << (int)pixel.r << ", " << (int)pixel.g << ", " << (int)pixel.b << ") ";
  //  }

  //  cout << "\n";
  //}

  return 0;
}
