#include "bitmap/bitmap.h"
#include "fractal_generator.h"

const auto kMaxIterations{1000};
const auto kImgWidth{800};
const auto kImgHeight{600};

int main() {
    FractalGenerator fg = FractalGenerator::Build()
                            .MandelbrotFractal(kMaxIterations)
                            .BitmapImage(kImgWidth, kImgHeight)
                            .HistColoring(kMaxIterations, kImgWidth, kImgHeight);
                        
    
    fg.Generate("test");
}
