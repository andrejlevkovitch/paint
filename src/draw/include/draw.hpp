// draw.hpp

#pragma once

#include <cstdint>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <string>
#include <fstream>

struct color {
  color(uint8_t r_, uint8_t g_, uint8_t b_) : r{r_}, g{g_}, b{b_} {};
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

using image = std::vector<color>;

struct vertex {
  vertex(int8_t x_, int8_t y_) : x{x_}, y{y_} {};
  vertex operator-(vertex rhs) {
    return vertex(x - rhs.x, y - rhs.y);
  };
  int8_t x;
  int8_t y;
};

template <size_t S, size_t C>
void draw_line(image &image, vertex a, vertex b) {
  auto temp = a - b;
  temp.x = std::abs(temp.x);
  temp.y = std::abs(temp.y);
  if (temp.x >= temp.y) {
    vertex current{0, 0};
    vertex destination{0, 0};

    if (a.x <= b.x) {
      current = a;
      destination = b;
    } else {
      current = b;
      destination = a;
    }
    int fault = 0;
    int adder = temp.y;
    int difirence = temp.x;
    while (current.x <= destination.x) {
      if (fault > difirence) {
        fault -=difirence;
        ++current.y;
      }
      image[current.y * C + current.x] = color{0, 255, 0};
      ++current.x;
      fault += adder;
    }
  } else {
    vertex current{0, 0};
    vertex destination{0, 0};

    if (a.y <= b.y) {
      current = a;
      destination = b;
    } else {
      current = b;
      destination = a;
    }
    int fault = 0;
    int adder = temp.x;
    int difirence = temp.y;
    while (current.y <= destination.y) {
      if (fault > difirence) {
        fault -=difirence;
        ++current.x;
      }
      image[current.y * C + current.x] = color{0, 255, 0};
      ++current.y;
      fault += adder;
    }
  }
}

template <size_t S, size_t C>
void save(image image, const std::string &file_name) {
  std::ofstream fout;
  fout.open(file_name);
  if (fout.is_open()) {
    fout << "P6\n" << S << ' ' << C << "\n";
    fout.write(static_cast<const char *>(&image[0].r), image.size() * sizeof(image[0]));
  }
}
