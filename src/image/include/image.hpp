// image.hpp

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

struct color {
  color(uint8_t r_, uint8_t g_, uint8_t b_) : r{r_}, g{g_}, b{b_} {};
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct f_color {
  f_color(float r_, float g_, float b_) : r{r_}, g{g_}, b{b_} {};
  f_color operator-(f_color rhs) {
    return f_color(this->r - rhs.r, this->g - rhs.g, this->b - rhs.b);
  };
  f_color operator/(int d) {
    return f_color(this->r / d, this->g / d, this->b / d);
  }
  f_color operator*(int d) {
    return f_color(this->r * d, this->g * d, this->b * d);
  }
  f_color operator+(f_color rhs) {
    return f_color(this->r + rhs.r, this->g + rhs.g, this->b + rhs.b);
  }
  operator color() { return color(this->r, this->g, this->b); }

  float r;
  float g;
  float b;
};

struct vertex {
  vertex(int x_, int y_) : x{x_}, y{y_} {};
  vertex operator-(vertex rhs) { return vertex(x - rhs.x, y - rhs.y); };
  vertex operator+(vertex rhs) { return vertex(x + rhs.x, y + rhs.y); };
  vertex operator*(float rhs) { return vertex(x * rhs, y * rhs); };
  int x;
  int y;
};

using buffer = std::vector<color>;
using vertexes = std::vector<vertex>;

class image {
public:
  image(size_t width, size_t height);
  void clear(color color = {0, 0, 0});
  color &operator()(vertex v);
  void draw_line(vertex a, vertex b, color color);
  void draw_cirkle(vertex center, unsigned short radius, color color);
  void draw_triangle(vertex a, vertex b, vertex c, color color);
  void draw_triangles_by_indexes(const std::vector<vertex> &vertexes,
                                 const std::vector<int> &indexes, color color);
  void draw_ip_triangle(vertex a, vertex b, vertex c, color one, color second,
                        color third);
  void save(const std::string &file_name);

private:
  buffer buf_;
  size_t width_;
  size_t height_;
};
