// image.cpp

#include "image.hpp"
#include <fstream>

image::image(size_t width, size_t height)
    : buf_(width * height, color{0, 0, 0}), width_{width}, height_{height} {}

void image::clear(color color) {
  for (auto &i : buf_) {
    i = color;
  }
}

color &image::operator()(vertex v) { return buf_[v.y * width_ + v.x]; }

void image::draw_line(vertex a, vertex b, color color) {
  auto temp = a - b;
  temp.x = std::abs(temp.x);
  temp.y = std::abs(temp.y);

  vertex current = a;
  vertex destination = b;
  if (temp.y < temp.x) {

    int dif_x = (current.x <= destination.x) ? 1 : -1;
    int dif_y = (current.y <= destination.y) ? 1 : -1;

    int fault = 0;
    int adder = temp.y;
    int difirence = temp.x;
    while (current.x != destination.x + dif_x) {
      if (fault >= difirence) {
        fault -= difirence;
        current.y += dif_y;
      }
      (*this)(current) = color;
      current.x += dif_x;
      fault += adder;
    }
  } else {
    vertex current = a;
    vertex destination = b;

    int dif_x = (current.x <= destination.x) ? 1 : -1;
    int dif_y = (current.y <= destination.y) ? 1 : -1;

    int fault = 0;
    int adder = temp.x;
    int difirence = temp.y;
    while (current.y != destination.y + dif_y) {
      if (fault >= difirence) {
        fault -= difirence;
        current.x += dif_x;
      }
      (*this)(current) = color;
      current.y += dif_y;
      fault += adder;
    }
  }
}

void image::draw_cirkle(vertex center, unsigned short radius, color color) {
  int x = 0;
  int y = radius;
  int delta = 1 - 2 * radius;
  int error = 0;
  while (y >= 0) {
    (*this)(center + vertex(x, y)) = color;
    (*this)(center + vertex(-x, -y)) = color;
    (*this)(center + vertex(-x, y)) = color;
    (*this)(center + vertex(x, -y)) = color;
    error = 2 * (delta + y) - 1;
    if (delta < 0 && error <= 0) {
      delta += 2 * ++x + 1;
      continue;
    }
    if (delta > 0 && error > 0) {
      delta -= 2 * --y + 1;
      continue;
    }
    delta += 2 * (++x - y--);
  }
}

void image::draw_triangle(vertex a, vertex b, vertex c, color color) {
  if (a.y > b.y)
    std::swap(a, b);
  if (a.y > c.y)
    std::swap(a, c);
  if (b.y > c.y)
    std::swap(b, c);

  float delta_x_ac{};
  float delta_x_ab{};
  float delta_x_bc{};

  if (a.y != c.y) {
    delta_x_ac = float(a.x - c.x) / (a.y - c.y);
  }
  if (a.y != b.y) {
    delta_x_ab = float(a.x - b.x) / (a.y - b.y);
  }
  if (b.y != c.y) {
    delta_x_bc = float(b.x - c.x) / (b.y - c.y);
  }

  float left_x = a.x;
  float right_x = a.x;

  float delta_left{delta_x_ab};
  float delta_right{delta_x_ac};

  if (b.x > a.x) {
    std::swap(delta_left, delta_right);
  }

  for (int i = a.y; i < b.y; ++i) {
    for (int j = left_x; j <= right_x; ++j) {
      buf_[i * width_ + j] = color;
    }
    left_x += delta_left;
    right_x += delta_right;
  }

  if (b.x > a.x) {
    delta_right = delta_x_bc;
    right_x = b.x;
  } else {
    delta_left = delta_x_bc;
    left_x = b.x;
  }

  for (int i = b.y; i <= c.y; ++i) {
    for (int j = left_x; j <= right_x; ++j) {
      buf_[i * width_ + j] = color;
    }
    left_x += delta_left;
    right_x += delta_right;
  }
}

void image::draw_triangles_by_indexes(const std::vector<vertex> &vertexes,
                                      const std::vector<int> &indexes,
                                      color color) {
  for (int i = 0; i < indexes.size() / 3; ++i) {
    int index = i * 3;
    draw_triangle(vertexes[indexes[index]], vertexes[indexes[index + 1]],
                  vertexes[indexes[index + 2]], color);
  }
}

void image::draw_ip_triangle(vertex a, vertex b, vertex c, color x, color y,
                             color z) {
  if (a.y > b.y) {
    std::swap(a, b);
    std::swap(x, y);
  }
  if (a.y > c.y) {
    std::swap(a, c);
    std::swap(x, z);
  }
  if (b.y > c.y) {
    std::swap(b, c);
    std::swap(y, z);
  }

  float delta_x_ac{};
  float delta_x_ab{};
  float delta_x_bc{};

  f_color alfa(x.r, x.g, x.b);
  f_color beta(y.r, y.g, y.b);
  f_color charli(z.r, z.g, z.b);

  std::pair<f_color, f_color> delta_color_ac{{0, 0, 0}, {0, 0, 0}};
  std::pair<f_color, f_color> delta_color_ab{{0, 0, 0}, {0, 0, 0}};
  std::pair<f_color, f_color> delta_color_bc{{0, 0, 0}, {0, 0, 0}};

  if (a.y != c.y) {
    delta_x_ac = float(a.x - c.x) / (a.y - c.y);
    delta_color_ac.second = (alfa - charli) / (a.y - c.y);
    if (a.x != c.x) {
      delta_color_ac.first = (alfa - charli) / (a.x - c.x);
    }
  }
  if (a.y != b.y) {
    delta_x_ab = float(a.x - b.x) / (a.y - b.y);
    delta_color_ab.second = (alfa - beta) / (a.y - b.y);
    if (a.x != b.x) {
      delta_color_ab.first = (alfa - beta) / (a.x - b.x);
    }
  }
  if (b.y != c.y) {
    delta_x_bc = float(b.x - c.x) / (b.y - c.y);
    delta_color_bc.second = (beta - charli) / (b.y - c.y);
    if (b.x != c.x) {
      delta_color_bc.first = (beta - charli) / (b.x - c.x);
    }
  }

  float left_x = a.x;
  float right_x = a.x;

  float delta_left{delta_x_ab};
  float delta_right{delta_x_ac};

  auto delta_color_left{delta_color_ab};
  auto delta_color_right{delta_color_ac};

  if (b.x > a.x) {
    std::swap(delta_left, delta_right);
    std::swap(delta_color_left, delta_color_right);
  }

  color cur_color{0, 0, 0};
  f_color color_left = alfa;
  f_color color_right = alfa;

  for (int i = a.y; i < b.y; ++i) {
    auto temp_color_left = delta_color_left.second * (i - a.y) + color_left;
    auto temp_color_right = delta_color_right.second * (i - a.y) + color_right;
    auto temp_delta_color =
        (temp_color_left - temp_color_right) / (left_x - right_x);
    for (int j = left_x; j <= right_x; ++j) {
      cur_color = temp_color_left;
      buf_[i * width_ + j] = cur_color;
      temp_color_left = temp_color_left + temp_delta_color;
    }
    left_x += delta_left;
    right_x += delta_right;
  }

  if (b.x > a.x) {
    delta_right = delta_x_bc;
    delta_color_right = delta_color_bc;
    color_right = beta;
    color_left = delta_color_left.second * (b.y - a.y) + color_left;
    right_x = b.x;
  } else {
    delta_left = delta_x_bc;
    delta_color_left = delta_color_bc;
    color_left = beta;
    color_right = delta_color_right.second * (b.y - a.y) + color_right;
    left_x = b.x;
  }

  for (int i = b.y; i <= c.y; ++i) {
    auto temp_color_left = delta_color_left.second * (i - b.y) + color_left;
    auto temp_color_right = delta_color_right.second * (i - b.y) + color_right;
    auto temp_delta_color =
        (temp_color_left - temp_color_right) / (left_x - right_x);
    for (int j = left_x; j <= right_x; ++j) {
      cur_color = temp_color_left;
      buf_[i * width_ + j] = cur_color;
      temp_color_left = temp_color_left + temp_delta_color;
    }
    left_x += delta_left;
    right_x += delta_right;
  }
}

void image::save(const std::string &file_name) {
  std::ofstream fout;
  fout.open(file_name);
  if (fout.is_open()) {
    fout << "P6\n" << width_ << ' ' << height_ << "\n" << 225 << "\n";
    fout.write(reinterpret_cast<const char *>(&buf_[0]),
               buf_.size() * sizeof(buf_[0]));
    fout.close();
  }
}
