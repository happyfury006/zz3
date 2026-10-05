#define cimg_display 0
#include <CImg.h>   // ou le chemin que le squelette utilise déjà

#include "algebrique.hpp"

using namespace cimg_library;

// Remplit img avec l'ensemble de Mandelbrot sur la région [min ; max].
// Pour chaque pixel (complexe c) : z0 = 0, z(i+1) = z(i)^2 + c,
// on s'arrête dès que |z| > 2 ou que maxIter itérations sont faites.
// Couleur = iterations / maxIter (0 = diverge tout de suite, 1 = dans l'ensemble).
void mandelbrot(CImg<unsigned char> &img, unsigned maxIter,
                const Algebrique &min, const Algebrique &max) {
  const int w = img.width();
  const int h = img.height();
  const double dx = (max.getRe() - min.getRe()) / (w - 1);
  const double dy = (max.getIm() - min.getIm()) / (h - 1);

  for (int py = 0; py < h; ++py) {
    for (int px = 0; px < w; ++px) {
      // pixel -> complexe c (y de l'image vers le bas, axe imaginaire vers le haut)
      const double cRe = min.getRe() + px * dx;
      const double cIm = max.getIm() - py * dy;

      double zRe = 0.0, zIm = 0.0;
      unsigned i = 0;
      // |z| <= 2  <=>  |z|^2 <= 4 (évite une racine carrée par itération)
      while (i < maxIter && zRe * zRe + zIm * zIm <= 4.0) {
        const double nRe = zRe * zRe - zIm * zIm + cRe;  // Re(z^2 + c)
        zIm = 2.0 * zRe * zIm + cIm;                     // Im(z^2 + c)
        zRe = nRe;
        ++i;
      }

      const double ratio = static_cast<double>(i) / maxIter;  // dans [0 ; 1]
      const unsigned char colour[3] = {
          static_cast<unsigned char>(255 * ratio),
          static_cast<unsigned char>(255 * ratio),
          static_cast<unsigned char>(255 * ratio)};

      for (int k = 0; k < img.spectrum() && k < 3; ++k)
        img(px, py, 0, k) = colour[k];
    }
  }
}

int main() {
  CImg<unsigned char> img(1200, 800, 1, 3, 0);
  mandelbrot(img, 200, Algebrique(-2.2, -1.2), Algebrique(1.0, 1.2));
  img.save_bmp("mandelbrot.bmp");
  return 0;
}
