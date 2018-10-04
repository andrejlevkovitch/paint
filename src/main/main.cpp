// main.cpp

#include <cstdlib>

//#include "draw.hpp"

#include "image.hpp"

int main(int argc, char *argv[]) {
  const size_t strings = 30;
  const size_t columns = 40;

  image image{columns, strings};

  image.draw_line(vertex{0, 0}, vertex{columns - 1, strings - 1},
                  color{0, 255, 0});

  image.draw_line(vertex{columns - 1, 0}, vertex{0, strings - 1},
                  color{255, 0, 0});

  image.draw_line(vertex{0, 0}, vertex{0, strings - 1}, color{0, 0, 255});

  image.draw_line(vertex{0, 0}, vertex{columns - 1, 0}, color{255, 255, 0});

  image.draw_line(vertex{columns - 1, strings - 1}, vertex{0, strings - 1},
                  color{0, 255, 255});

  image.draw_line(vertex{columns - 1, strings - 1}, vertex{columns - 1, 0},
                  color{255, 0, 255});

  image.draw_cirkle(vertex{(columns - 1) / 2, (strings - 1) / 2}, 13,
                    color{255, 255, 255});

  image.save("lines.ppm");

  image.clear(color{0, 0, 0});

  vertex a{6, 8};
  vertex b{2, 3};
  vertex c{10, 1};
  image.draw_triangle(a, b, c, color{0, 0, 255});

  image.save("triangle.ppm");

  class image image_big {
    500, 500
  };

  std::vector<vertex> vertexes{
      vertex{100, 200}, vertex{150, 300}, vertex{150, 100}, vertex{10, 100},
      vertex{50, 5},    vertex{200, 250}, vertex{300, 300}, vertex{300, 400},
      vertex{400, 250}, vertex{200, 375}, vertex{75, 375},  vertex{100, 450}};
  std::vector<int> indexes{4, 3, 2, 2, 1, 0, 5, 6, 7, 6, 7, 8, 9, 10, 11};

  image_big.draw_triangles_by_indexes(vertexes, indexes, color{250, 250, 0});

  image_big.save("triangles.ppm");

  class image ip {
    500, 500
  };

  ip.draw_ip_triangle(vertex{0, 0}, vertex{255, 127}, vertex{0, 255},
                      color{255, 0, 0}, color{0, 255, 0}, color{0, 0, 255});

  ip.save("ip_triangle.ppm");

  ip.clear();

  ip.draw_ip_triangle(vertex{300, 100}, vertex{100, 350}, vertex{450, 350},
                      color{255, 0, 0}, color{0, 255, 0}, color{0, 0, 255});

  ip.save("ip_triangle1.ppm");

  ip.clear();

  ip.draw_ip_triangle(vertex{300, 100}, vertex{100, 100}, vertex{450, 350},
                      color{255, 0, 0}, color{0, 255, 0}, color{0, 0, 255});

  ip.save("ip_triangle2.ppm");

  return EXIT_SUCCESS;
}
