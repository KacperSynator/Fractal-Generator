#include <QApplication>

#include "bitmap/bitmap.h"
#include "fractal_generator.h"
#include "gui/main_window.h"


const auto kMaxIterations{1000};
const auto kImgWidth{800};
const auto kImgHeight{600};

int main(int argc, char* argv[]) {

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    FractalGenerator fg = FractalGenerator::Build()
                            .MandelbrotFractal(kMaxIterations)
                            .BitmapImage(kImgWidth, kImgHeight)
                            .HistColoring(kMaxIterations, kImgWidth, kImgHeight);
                        
    fg.AddZoom( Zoom{kImgWidth / 2, kImgHeight / 2, 4.0 / kImgWidth} );
    fg.AddZoom( Zoom{292, 196, 0.1} );
    fg.AddZoom( Zoom{365, 228, 0.1} );

    fg.Generate("test");

    return a.exec();
}
