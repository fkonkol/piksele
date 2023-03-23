#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define WIDTH 4
#define HEIGHT 4

typedef uint8_t img_t[HEIGHT][WIDTH];

void img_load_from_file(img_t img, const char *file_path)
{
    FILE *f = fopen(file_path, "r");

    if (f == NULL) {
        fprintf(stderr, "ERROR: could not open file %s: %m\n", file_path);
        exit(1);
    }

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            fscanf(f, "%hhu", &img[y][x]);
        }
    }

    fclose(f);
}

static img_t image;

int main(void)
{
    img_load_from_file(image, "danee.txt");

    return 0;
}
