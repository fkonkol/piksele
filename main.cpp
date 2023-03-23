#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define WIDTH 320
#define HEIGHT 200

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

void img_get_brightest_and_darkest_px(img_t img, uint8_t *bright, uint8_t *dark)
{
    uint8_t brightest = 0, darkest = 255;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (img[y][x] < darkest) darkest = img[y][x];
            if (img[y][x] > brightest) brightest = img[y][x];
        }
    }

    *bright = brightest;
    *dark = darkest;
}

static img_t image;

int main(void)
{
    img_load_from_file(image, "przyklad.txt");

    uint8_t brightest, darkest;
    img_get_brightest_and_darkest_px(image, &brightest, &darkest);

    printf("%hhu %hhu\n", brightest, darkest);

    return 0;
}
