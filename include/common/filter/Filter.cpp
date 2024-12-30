#include "./Filter.hpp"

ImageData Filter::convertTo2D(const unsigned char* imageData, int width, int height) {
  ImageData output;
  int length = width * height * 3;
  RGB color;



  for (int i = 0;i < height;++i) {
    PixelRow row;
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

void Filter::saveToPNG(const ImageData& imageData, int width, int height, const char* filename) {
  std::vector<unsigned char> imageFlat;
  imageFlat.reserve(width * height * 3);

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      const RGB& color = imageData[i][j];
      imageFlat.push_back(color.r);
      imageFlat.push_back(color.g);
      imageFlat.push_back(color.b);
    }
  }

  if (stbi_write_png(filename, width, height, 3, imageFlat.data(), width * 3)) {
    std::cout << "Image saved successfully to " << filename << std::endl;
  }
  else {
    std::cout << "Failed to save image!" << std::endl;
  }
}

void Filter::convertToGrayscale(ImageData& imageData, int width, int height) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      RGB& color = imageData[i][j];
      float gray = color.r * 0.2989f + color.r * 0.5870f + color.r * 0.1140f;
      color.r = gray;
      color.g = gray;
      color.b = gray;
    }
  }
}

//void Filter::sobelEdgeDetection(ImageData& imageData, int width, int height, RGB edgeColor, int threshold) {
//  const int Gx[3][3] = {
//      {-1, 0, 1},
//      {-2, 0, 2},
//      {-1, 0, 1}
//  };
//  const int Gy[3][3] = {
//      {-1, -2, -1},
//      { 0,  0,  0},
//      { 1,  2,  1}
//  };
//
//  std::vector<std::vector<RGB>> originalImage = imageData;
//
//  for (int i = 1; i < height - 1; ++i) {
//    for (int j = 1; j < width - 1; ++j) {
//      float gx = 0.0f;
//      float gy = 0.0f;
//
//      for (int k = -1; k <= 1; ++k) {
//        for (int l = -1; l <= 1; ++l) {
//          float intensity = originalImage[i + k][j + l].r;
//          gx += Gx[k + 1][l + 1] * intensity;
//          gy += Gy[k + 1][l + 1] * intensity;
//        }
//      }
//
//      float gradientMagnitude = std::sqrt(gx * gx + gy * gy);
//
//      gradientMagnitude = std::min(std::max(gradientMagnitude, 0.0f), 255.0f);
//
//      //imageData[i][j].r = gradientMagnitude;
//      //imageData[i][j].g = gradientMagnitude;
//      //imageData[i][j].b = gradientMagnitude;
//
//
//
//      // Change the edge pixel to the specified edge color
//      if (gradientMagnitude > threshold) { // Threshold for edge detection
//        imageData[i][j].r = edgeColor.r;
//        imageData[i][j].g = edgeColor.g;
//        imageData[i][j].b = edgeColor.b;
//      }
//      else {
//        // Non-edge pixels remain black or another background color
//        imageData[i][j].r = 0;
//        imageData[i][j].g = 0;
//        imageData[i][j].b = 0;
//      }
//    }
//  }
//}

void Filter::sobelEdgeDetection(ImageData& imageData, int width, int height) {
  const int Gx[3][3] = {
      {-1, 0, 1},
      {-2, 0, 2},
      {-1, 0, 1}
  };
  const int Gy[3][3] = {
      {-1, -2, -1},
      { 0,  0,  0},
      { 1,  2,  1}
  };

  std::vector<std::vector<RGB>> originalImage = imageData;

  for (int i = 1; i < height - 1; ++i) {
    for (int j = 1; j < width - 1; ++j) {
      float gx = 0.0f;
      float gy = 0.0f;

      for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
          float intensity = originalImage[i + k][j + l].r;
          gx += Gx[k + 1][l + 1] * intensity;
          gy += Gy[k + 1][l + 1] * intensity;
        }
      }

      float gradientMagnitude = std::sqrt(gx * gx + gy * gy);

      gradientMagnitude = std::min(std::max(gradientMagnitude, 0.0f), 255.0f);

      imageData[i][j].r = gradientMagnitude;
      imageData[i][j].g = gradientMagnitude;
      imageData[i][j].b = gradientMagnitude;
    }
  }
}

ImageData Filter::createCanvas(int width, int height) {
  ImageData canvas;
  RGB color;

  for (int i = 0; i < height; ++i) {
    PixelRow row;
    for (int j = 0; j < width; ++j) {
      color.r = 0;
      color.g = 0;
      color.b = 0;

      row.emplace_back(color);
    }

    canvas.emplace_back(row);

  };

  return canvas;
};

void Filter::placeTileOnCanvas(ImageData& canvas, ImageData& image, int xPos, int yPos, int tileWidth, int tileHeight) {
  for (int i = 0; i < tileHeight; ++i) {
    for (int j = 0; j < tileWidth; ++j) {
      int canvasRow = yPos + i;
      int canvasCol = xPos + j;

      // Check bounds to ensure we don't write out of the canvas
      if (canvasRow >= 0 && canvasRow < canvas.size() && canvasCol >= 0 && canvasCol < canvas[0].size()) {
        canvas[canvasRow][canvasCol] = image[i][j];
      }
    }
  }
};


//vector<vector<RGB>> myimage = {
//       { {10, 20, 30}, {15, 25, 35}, {20, 30, 40} },
//       { {12, 22, 32}, {100, 200, 255}, {22, 32, 42} },
//       { {14, 24, 34}, {18, 28, 38}, {24, 34, 44} }
//};/

//void Filter::applyMedianFilter(ImageData& imageData) {
//
//  std::cout <<  "image size : " << imageData.size() << "width: " << imageData[0].size() << '\n';
//
//  for (auto height : imageData) {
//    for (auto row : height) {
//      cout << (int)row.r << '\n';
//    }
//  }
// 
//}


void Filter::brightenImage(ImageData& image, float brightnessFactor) {
  for (int i = 0; i < image.size(); i++) {
    for (int j = 0; j < image[i].size(); j++) {
      // Brighten each color channel and ensure it doesn't exceed 255
      image[i][j].r = std::min(static_cast<int>(image[i][j].r * brightnessFactor), 255);
      image[i][j].g = std::min(static_cast<int>(image[i][j].g * brightnessFactor), 255);
      image[i][j].b = std::min(static_cast<int>(image[i][j].b * brightnessFactor), 255);
    }
  }
}

template <typename T>
T clamp(T value, T min, T max) {
  return (value < min) ? min : (value > max ? max : value);
}

  
void Filter::sharpen(ImageData& image) {
  int height = image.size();
  if (height == 0) return;
  int width = image[0].size();

  // Sharpen kernel 
  const int kernel[3][3] = {
      {  0, -1,  0 },
      { -1,  5, -1 },
      {  0, -1,  0 }
  };

  // Create a copy of the image to use as reference for computation
  ImageData originalImage = image;

  // Apply kernel to each pixel
  for (int i = 1; i < height - 1; ++i) {
    for (int j = 1; j < width - 1; ++j) {
      int newR = 0, newG = 0, newB = 0;

      // Apply convolution
      for (int ki = -1; ki <= 1; ++ki) {
        for (int kj = -1; kj <= 1; ++kj) {
          newR += kernel[ki + 1][kj + 1] * originalImage[i + ki][j + kj].r;
          newG += kernel[ki + 1][kj + 1] * originalImage[i + ki][j + kj].g;
          newB += kernel[ki + 1][kj + 1] * originalImage[i + ki][j + kj].b;
        }
      }

      // Clamp values to valid range [0, 255]
      image[i][j].r = clamp(newR, 0, 255);
      image[i][j].g = clamp(newG, 0, 255);
      image[i][j].b = clamp(newB, 0, 255);
    }
  }
}