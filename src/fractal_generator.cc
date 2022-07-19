#include "fractal_generator.h"
#include "fractal_generator_builder.h"

FractalGeneratorBuilder& FractalGenerator::Build() {
    FractalGenerator fg;
    return {fg};
}