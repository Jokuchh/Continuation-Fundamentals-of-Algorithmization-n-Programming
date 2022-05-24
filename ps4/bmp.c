#include "bmp.h"
#include <stdlib.h>

struct bmp_header* read_bmp_header(FILE* stream) {
	if (stream == NULL) {
        return NULL;
    }
	struct bmp_header* bmp_h;
    fseek(stream, 0, SEEK_SET);
	bmp_h = malloc(sizeof(struct bmp_header));
    int n;
	n = fread(bmp_h, sizeof(struct bmp_header), 1, stream);
    if (n != 1) {
        free(bmp_h);
        bmp_h = NULL;
        return NULL;
    }


	return bmp_h;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header) {
	if (stream == NULL || header == NULL) {
        return NULL;
    }
	struct pixel* p_pisxel_x;

	size_t s_size_z = header->width * header->height;

	p_pisxel_x = (struct pixel*)malloc(s_size_z * sizeof(struct pixel));


	fseek(stream, header->offset, SEEK_SET);

	int n;
    int skip = header->width % 4;
    for (int i=0; i<header->height; i++) {
        n = fread(&p_pisxel_x[header->width*i], sizeof(struct pixel), header->width, stream);
    
        if (n != header->width) {
            free(p_pisxel_x);
            p_pisxel_x = NULL;
            return NULL;
        }
        /*
        while (skip != 0) {
            fseek(stream, 1, SEEK_CUR);
            skip--;
        }
        skip = header->width % 4;*/
        fseek(stream, skip, SEEK_CUR);
    }

	return p_pisxel_x;
}

struct bmp_image* read_bmp(FILE* stream) {
	if (stream == NULL || stream == NULL) {
		return NULL;
	}
	struct bmp_image* bmp_i;
	bmp_i = (struct bmp_image*)malloc(sizeof(struct bmp_image));
	bmp_i->header = read_bmp_header(stream);


	if (bmp_i->header == NULL || bmp_i->header->type != 0x4d42) {
		fprintf(stderr, "Error: This is not a BMP file.\n");
        free(bmp_i);
        bmp_i = NULL;
		return NULL;
	}
	bmp_i->data = read_data(stream, bmp_i->header);

	if (bmp_i->data == NULL) {
		fprintf(stderr, "Error: Corrupted BMP file.\n");
        free(bmp_i->header);
        bmp_i->header = NULL;
        free(bmp_i);
        bmp_i = NULL;
		return NULL;
	}

	return bmp_i;
}

bool write_bmp(FILE* stream, const struct bmp_image* image) {
	if (image == NULL || stream == NULL) {
        return false;
    }
    if (image->data == NULL || image->header == NULL) {
        return false;
    }
    else {
        fseek(stream, 0, SEEK_SET);
    }
	int n = fwrite(image->header, sizeof(struct bmp_header), 1, stream);
	if (n < 1) {
		return false;
	}
    int skip = image->header->width % 4;
	//fseek(stream, image->header->offset, SEEK_SET);
    for (int i=0; i<image->header->height; i++) {
        n = fwrite(&image->data[image->header->width*i], sizeof(struct pixel), image->header->width, stream);
    
        if (n != image->header->width) {
            return false;
        }/*
        while (skip != 0) {
            fwrite(PADDING_CHAR, 1, 1, stream);
            skip--;
        }
        skip = image->header->width % 4;*/
        fwrite(PADDING_CHAR, 1, skip, stream);
    }

	if (n < 1) {
		return false;
	}
    //fseek(stream, 0, SEEK_SET);
    //fwrite(image, sizeof(struct bmp_image), 1, stream);
	return true;
}

void free_bmp_image(struct bmp_image* image) {
	if (image != NULL) {
        if (image->header != NULL) {
            free(image->header);
            image->header = NULL;
         }
         if (image->data != NULL) {
            free(image->data);
            image->data = NULL;
         }
         free(image);
         image = NULL;
    }
    return;
}
