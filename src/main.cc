#include "bitmap/bitmap.h"
#include "fractal_generator.h"

int main() {
    FractalGenerator& bitmap = FractalGenerator::Build()
                                .MandelbrotFractal()
                                .BitmapImage(800, 600);
    
}
