

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION


#include "../include/common/CommonHeader.hpp"

#include "../include/common/stb/stb_image.h"
#include "../include/common/stb/stb_image_write.h"

#include "../include/common/filter/Filter.cpp"

#include "../include/types/types.hpp"

#include "../include/struct/struct.hpp"


int main() {

  Filter filter;

  int width, height, channels;

  unsigned char* imageData = stbi_load("C:/Users/Leapfrog/source/repos/simonchaudhary/cpp_training_assignments/Day-10/images/salt-and-pepper-noise.png", &width, &height, &channels, 3);

  if (imageData == nullptr) {
    cout << "Image loading failed\n";
  }

	cout << "Image loaded successfully\n";

  //cout << width << " " << height  << " " << channels;

  //auto image = filter.convertTo2D(imageData, width, height);


  vector<vector<RGB>> myimage = {
         { {10, 20, 30}, {15, 25, 35}, {20, 30, 40} },
         { {12, 22, 32}, {100, 200, 255}, {22, 32, 42} },
         { {14, 24, 34}, {18, 28, 38}, {24, 34, 44} }
  };

  filter.applyMedianFilter(myimage);



  //filter.saveToPNG(image, width, height, "median_filter.png")



  return 0;
}

