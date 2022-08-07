#include <QApplication>

#include "bitmap/bitmap.h"
#include "fractal_generator.h"
#include "gui/gui.h"


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    auto gui = Gui::CreateGui();

    // FractalGenerator fg = FractalGenerator::Build(kImgWidth, kImgHeight, kMaxIterations)
    //                                        .MandelbrotFractal()
    //                                        .BitmapImage()
    //                                        .HistColoring();

    // fg.AddColorRange(0.0, 0, 0, 255);
    // fg.AddColorRange(0.05, 255, 99, 71);
    // fg.AddColorRange(0.08, 255, 215, 0);
    // fg.AddColorRange(1.0, 255, 255, 255);

    // fg.AddZoom(Zoom{kZoomStartX, kZoomStartY, kZoomStartSCale});
    // fg.AddZoom(Zoom{292, 196, 0.1});
    // fg.AddZoom(Zoom{365, 228, 0.1});

    // fg.Generate("test");

    return a.exec();
}
