#include "CImg.h"
namespace cil = cimg_library;
using namespace cil;

int main(int argc, char** argv) {

    // Read image filename from the command line (or set it to "img/parrot_original.ppm" if option '-i' is not provided).
  const char* file_i = cimg_option("-i","input.mnc.gz","Input image");
  const char* file_o = cimg_option("-o","output.mnc","Output image");
  const char* file_t = cimg_option("-t",(char*)0,"Template image");

  CImg<float> img;
  img.load(file_i);

  img.display();

  img.save_minc2(file_o, file_t);

  return 0;
}
