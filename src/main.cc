#include <QApplication>

#include "bitmap/bitmap.h"
#include "fractal_generator.h"
#include "gui/gui.h"


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    auto gui = Gui::CreateGui();

    return a.exec();
}
