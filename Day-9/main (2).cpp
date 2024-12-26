

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

int main(){
    //int width,height,channels;

    //int width2, height2, channels2;
    //unsigned char* imageData = stbi_load("C:/Users/Leapfrog/source/repos/simonchaudhary/cpp_training_assignments/Day9/images/image1.png",&width,&height,&channels,3);
    //unsigned char* imageData2 = stbi_load("C:/Users/Leapfrog/source/repos/simonchaudhary/cpp_training_assignments/Day9/images/image2.png", &width2, &height2, &channels2, 3);


    //std::cout << "Start image\n";

    //if(imageData==nullptr || imageData2 == nullptr){
    //    std::cout<<"Image loading failed\n";
    //}

    //std::vector<std::vector<RGB>> image1 = convertTo2D(imageData, width, height);

    //std::vector<std::vector<RGB>> image2 = convertTo2D(imageData2, width, height);

    //RGB edgeColor = { 67, 255, 100 }; // Red color

    //sobelEdgeDetection(image1, width, height, edgeColor,200);

    // Create an alpha channel initialized to fully opaque
    //std::vector<std::vector<uint8_t>> alphaChannel(height, std::vector<uint8_t>(width, 255));

    //applyTransparency(image1, alphaChannel, width, height);
    //saveToPNG(image1, width, height,"grayscaleimage.png");

    //normalizePic(image1, image2);

       // Save the image with transparency
    //saveToPNGWithAlpha(image2, alphaChannel, width, height, "sobel_transparent.png");
    


    // Normalize the two images
    //normalizePic(image1, image2);

    //std::cout << "Images normalized successfully.\n";

    // Save the normalized image

     std::vector<std::vector<RGB>> image = {
  {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
  {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
  {{255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}},
  {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
  {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}}
    };

    std::cout << "Saved 1" << '\n';

    saveToPNG(image, 5, 5, "normalized_image2.png");

    std::cout << "Saved" << '\n';

    //errosion
    // dilation.


 /*   for (int i = 0; i < width ;i += 3) {
        
        imageData[i] = 255;
        imageData[i+1] = 255;
        imageData[i+2] = 0;
    }

    stbi_write_png("leapfrog.png", width, height, 3, imageData, width * 3);*/

    
    /*auto image = convertTo2D(imageData,width,height);


    convertToGrayscale(image,width,height);
    sobelEdgeDetection(image,width,height);
    saveToPNG(image,width,height,"test.png");
    stbi_image_free(imageData);*/
    return 0;
}

