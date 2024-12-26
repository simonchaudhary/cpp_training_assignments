#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

#include "../struct/struct.hpp"

using std::vector;

using PixelRow = vector<RGB>;          // A single row of pixels
using ImageData = vector<PixelRow>;    // The entire image as a 2D vector

#endif // TYPES_HPP