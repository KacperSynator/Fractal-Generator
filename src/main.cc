#include "bitmap/bitmap.h"
#include "fractal_generator.h"

int main() {
    FractalGenerator fg = FractalGenerator::Build()
                            .MandelbrotFractal()
                            .BitmapImage(800, 600);
    
    fg.Generate("test");

}
