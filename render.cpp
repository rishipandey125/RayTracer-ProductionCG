#include <iostream>
// perspective rendering: set origin and fire ray through viewport
// orthogonal rendering: fire ray direct from each grid point in the viewport
  //build viewport around camera origin
void render_frame() {
  int image_width = 500;
  int image_height = 500;
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  for (int j = image_height-1; j >= 0; j--) {
    for (int i = 0; i < image_width; i++) {
      int r = static_cast<int>(255*0.5);
      int g = static_cast<int>(255*0.5);
      int b = static_cast<int>(255*0.5);
      std::cout << r << ' ' << g << ' ' << b << '\n';
    }
  }
}
