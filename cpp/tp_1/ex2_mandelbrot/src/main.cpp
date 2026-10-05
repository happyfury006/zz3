#define cimg_display 0
#include <CImg.h>

// #include <algebrique.hpp>

using Image = cimg_library::CImg<unsigned char>;

/* void mandelbrot(Image& img, int maxIter, Algebrique min, Algebrique max) {
  for(int y = 0; y < img.height(); ++y) {
    for(int x = 0; x < img.width(); ++x) {
      double re = min.getRe() + (max.getRe() - min.getRe()) * x / (img.width() - 1);
      double im = min.getIm() + (max.getIm() - min.getIm()) * y / (img.height() - 1);
      Algebrique c(re, im);

      // ICI

      unsigned char colour = 0;

      img(x, y, 0) = colour;
      img(x, y, 1) = colour;
      img(x, y, 2) = colour;
    }
  }
} */

int main() {
  Image img(640, 480, 1, 3, 0);

  // mandelbrot(img, 100, {-2.0, -1.0}, {1.0, 1.0});

  img.save_bmp("mandelbrot.bmp");
}
