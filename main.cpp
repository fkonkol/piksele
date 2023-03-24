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

int img_check_symmetry(img_t img)
{
    int counter = 0;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (img[y][x] != img[y][WIDTH-x-1]) {
                ++counter;
                break;
            }
        }
    }

    return counter;
}

bool img_is_neighbor(int x, int y, int nx, int ny)
{
    for (int y0 = y - 1; y0 <= y + 1; ++y0) {
        for (int x0 = x - 1; x0 <= x + 1; ++x0) {
            if (y0 == y && x0 == x) {
                continue;
            }

            if ((x0 < 0 || x0 >= WIDTH) || (y0 < 0 || y0 >= HEIGHT)) {
                continue;
            }

            if (x0 == nx && y0 == ny) {
                return true;
            }
        }
    }

    return false;
}

bool img_is_contrasting(img_t img, int x, int y, int nx, int ny)
{
    return abs(img[y][x] - img[ny][nx]) >= 128;
}

int img_get_contrasting_px(img_t img)
{
    int nb = 0;
    int counter = 0;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (img_is_neighbor(x, y, x, y - 1) && img_is_contrasting(img, x, y, x, y- 1)) {
                nb = 1;
            }

            if (img_is_neighbor(x, y, x, y + 1) && img_is_contrasting(img, x, y, x, y + 1)) {
                nb = 1;
            }

            if (img_is_neighbor(x, y, x - 1, y) && img_is_contrasting(img, x, y, x - 1, y)) {
                nb = 1;
            }

            if (img_is_neighbor(x, y, x + 1, y) && img_is_contrasting(img, x, y, x + 1, y)) {
                nb = 1;
            }

            if (nb) {
                ++counter;
                nb = 0;
            }
        }
    }

    return counter;
}

int img_get_longest_line(img_t img)
{
    int longest = 1;
    int temp = 1;

    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 1; y < HEIGHT; ++y) {
            if (img[y][x] == img[y-1][x]) {
                temp++;
            } else {
                longest = (temp > longest) ? temp : longest;
                temp = 1;
            }
        }
    }

    return longest;
}

static img_t image;

int main(void)
{
    img_load_from_file(image, "przyklad.txt");

    uint8_t brightest, darkest;
    img_get_brightest_and_darkest_px(image, &brightest, &darkest);

    printf("%hhu %hhu\n", brightest, darkest);

    printf("%d\n", img_check_symmetry(image));

    printf("%d\n", img_get_contrasting_px(image));

    printf("%d\n", img_get_longest_line(image));

    return 0;
}
