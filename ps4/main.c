#include <stdio.h>
#include "bmp.h"
#include "transformations.h"

int main() {
    
    FILE* fp = fopen("assets/square.4x2.bmp", "rb");
    while (false) {
        struct bmp_image* im = read_bmp(NULL);

        struct bmp_image* new = flip_horizontally(im);

        new = flip_vertically(im);
        
    
        
new = rotate_left(im);

        new = rotate_right(im);

        new = extract(im, "rg");

        new = scale(im, 2);

        free_bmp_image(im);
        new = crop(im, 0, 0, 0, 0);

        FILE* fw = fopen("square.1x1.bmp", "wb");
        write_bmp(fw, new);
            fclose(fw);
    }
    struct bmp_image* test = read_bmp(fp);
    struct bmp_image* rr = rotate_right(test);
    free_bmp_image(test);
    FILE* wr = fopen("o.bmp", "wb");
    write_bmp(wr, rr);
            if (fp != NULL) {
            fclose(fp);
            }
 if (wr != NULL) {
        fclose(wr);
    }   
    free_bmp_image(rr);
    return 0;
}
