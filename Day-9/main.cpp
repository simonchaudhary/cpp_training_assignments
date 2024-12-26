

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include<iostream>
#include<vector>
#include "./stb/stb_image.h"
#include "./stb/stb_image_write.h"

struct RGB{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct coordinate{
    int x;
    int y;
};

std::vector<std::vector<RGB>> convertTo2D(const unsigned char* imageData,int width, int height){
    std::vector<std::vector<RGB>> output;
    int length = width*height*3;
    RGB color;



    for(int i=0;i<height;++i){
        std::vector<RGB> row;
        for(int j=0; j<width*3;j+=3){
            color.r = imageData[i*width*3+j+0];
            color.g = imageData[i*width*3+j+1];
            color.b = imageData[i*width*3+j+2];
            row.emplace_back(color);
        }
        output.emplace_back(row);

    }

    return output;
}

void saveToPNG(const std::vector<std::vector<RGB>>& imageData, int width, int height, const char* filename) {
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
    } else {
        std::cout << "Failed to save image!" << std::endl;
    }
}

void convertToGrayscale(std::vector<std::vector<RGB>>& imageData,int width, int height){
     for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            RGB& color = imageData[i][j];
            float gray = color.r * 0.2989f+color.r * 0.5870f+color.r * 0.1140f;
            color.r = gray;
            color.g = gray;
            color.b = gray;
        }
    }
}

void sobelEdgeDetection(std::vector<std::vector<RGB>>& imageData, int width, int height, RGB edgeColor,int threshold) {
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

            //imageData[i][j].r = gradientMagnitude;
            //imageData[i][j].g = gradientMagnitude;
            //imageData[i][j].b = gradientMagnitude;



            // Change the edge pixel to the specified edge color
            if (gradientMagnitude > threshold) { // Threshold for edge detection
                imageData[i][j].r = edgeColor.r;
                imageData[i][j].g = edgeColor.g;
                imageData[i][j].b = edgeColor.b;
            }
            else {
                // Non-edge pixels remain black or another background color
                imageData[i][j].r = 0;
                imageData[i][j].g = 0;
                imageData[i][j].b = 0;
            }
        }
    }
}

void applyTransparency(std::vector<std::vector<RGB>>& imageData, std::vector<std::vector<uint8_t>>& alphaChannel, int width, int height, RGB transparentColor = { 0, 0, 0 }) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            const RGB& pixel = imageData[i][j];

            // Check if the pixel matches the transparent color
            if (pixel.r == transparentColor.r && pixel.g == transparentColor.g && pixel.b == transparentColor.b) {
                alphaChannel[i][j] = 0; // Fully transparent
            }
            else {
                alphaChannel[i][j] = 255; // Fully opaque
            }
        }
    }
}


void drawRect(std::vector<std::vector<RGB>>& input, int x, int y, int width, int height, RGB stroke={0,0,0}, RGB fill={0xff,0xff,0xff}){
    for(int i=x;i<x+width;++i){
        input[y][i]= stroke;
        input[y+height][i]= stroke;
    }
    for(int i=y;i<y+height;++i){
        input[i][x] = stroke;
        input[i][x+width] = stroke;
    }
    for(int i=x+1; i<x+width;++i){
        for(int j=y+1;j<y+height;++j){
            input[j][i] = fill;
        }
    }
}

void normalizePic(std::vector<std::vector<RGB>>& firstImage, std::vector<std::vector<RGB>>& secondImage)
{
    for (int i = 0; i < firstImage.size(); ++i)
    {
        for (int j = 0; j < firstImage[i].size(); ++j)
        {
            RGB& color1 = firstImage[i][j];
            RGB& color2 = secondImage[i][j];

            color1.r = (color1.r + color2.r) / 2;
            color1.g = (color1.g + color2.g) / 2;
            color1.b = (color1.b + color2.b) / 2;
        }
    }
};

void saveToPNGWithAlpha(const std::vector<std::vector<RGB>>& imageData, const std::vector<std::vector<uint8_t>>& alphaChannel, int width, int height, const char* filename) {
    std::vector<unsigned char> imageFlat;
    imageFlat.reserve(width * height * 4); // RGBA

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            const RGB& color = imageData[i][j];
            imageFlat.push_back(color.r); // Red
            imageFlat.push_back(color.g); // Green
            imageFlat.push_back(color.b); // Blue
            imageFlat.push_back(alphaChannel[i][j]); // Alpha
        }
    }

    if (stbi_write_png(filename, width, height, 4, imageFlat.data(), width * 4)) {
        std::cout << "Image with transparency saved successfully to " << filename << std::endl;
    }
    else {
        std::cout << "Failed to save image with transparency!" << std::endl;
    }
}


void drawPloy(std::vector<std::vector<RGB>>& input, int width, int height, const std::vector<coordinate>& coor, RGB stroke, RGB fill){

}

std::vector<std::vector<RGB>> createCanvas(int width, int height) {
  std::vector<std::vector<RGB>> canvas;
  RGB color;

  for (int i = 0; i < height; ++i) {
    std::vector<RGB> row;
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

void placeTileOnCanvas(std::vector<std::vector<RGB>>& canvas, std::vector<std::vector<RGB>>& image, int xPos, int yPos, int tileWidth, int tileHeight) {
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
}



int main(){
   /* int width,height,channels;

    unsigned char* imageData = stbi_load("C:/Users/Leapfrog/source/repos/simonchaudhary/cpp_training_assignments/Day9/images/image1.png",&width,&height,&channels,3);

    std::cout << "Start image\n";

    if(imageData==nullptr){
        std::cout<<"Image loading failed\n";
    }

    std::vector<std::vector<RGB>> image1 = convertTo2D(imageData, width, height);*/

    int width = 1100;
    int height = 1100;

    // Create canvas of 1100 x 1100px
    auto mycanvas =  createCanvas(width, height);

    

    //saveToPNG(mycanvas, width, height, "mycanvas.jpg");

   int imageWidth, imageHeight, imageChannels;

    unsigned char* imageData = stbi_load("C:/Users/Leapfrog/source/repos/simonchaudhary/cpp_training_assignments/Day-9/images/tile.jpg", &imageWidth, &imageHeight, &imageChannels, 3);

    if (imageData == nullptr) {
      std::cout << "Image loading failed\n";
    }

    auto image = convertTo2D(imageData,imageWidth, imageHeight);

    //std::vector<std::vector<RGB>> finalImage;

    std::cout << "imagewidth: " << (int)imageWidth  << "width: " << (int)width << '\n';

    int padding = 10;
    
    int repeatWidth = (width +10)/ (imageWidth+10);

    int repeatHeight = (height +10)/ (imageHeight+10);

    std::cout << "start repeating\n";

    for (int i = 0; i < repeatHeight;++i) {
      for (int j = 0; j < repeatWidth; ++j) {
        int xPos = j * (imageWidth + 10);
        int yPos = i * (imageHeight + 10);

        std::cout << xPos << " : " << yPos << '\n';

        placeTileOnCanvas(mycanvas, image,xPos, yPos, imageWidth, imageHeight);
      }
    }

    std::cout << "complete repeating\n";

    saveToPNG(mycanvas, width, height, "tiled_image_with_padding.png");

    std::cout << "Save success\n";

    //std::cout << "repeat " << repeatWidth << '\n';

    /*for (int i = 0;i < 600;i += 200) {
      finalImage.emplace_back(image);
    }

    saveToPNG(finalImage, 600, 600, "mycanvasFinal.jpg");
    */

    return 0;
}

