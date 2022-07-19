#include "inc/bitmap.h"

int main() {
    Bitmap bitmap{800, 600};
    for (int i = 0; i < 800; i++) {
        for (int j = 0; j < 600; j++)
            if (i == j)
                bitmap.SetPixel(i, j, 255, 0, 0);
    }

    bitmap.Write("test.bmp");
}
