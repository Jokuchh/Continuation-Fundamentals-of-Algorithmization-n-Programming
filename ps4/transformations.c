#include "transformations.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

int get_position_in_image(struct bmp_header* header, int height, int width) {
    int return_position = header->width * height + width;
    return return_position;
}

void update_size(struct bmp_image* image) {
    image->header->image_size =  image->header->width * image->header->height*3 + image->header->height*(image->header->width%4);
    image->header->size = 54 + image->header->image_size;
}

int get_vertically_mirror_image(struct bmp_header* header, int height, int width) {
    int return_position = header->width * header->height - header->width *(++height) + width;
    return return_position;
}

struct bmp_image* flip_vertically(const struct bmp_image* image) {
    if (image == NULL) {
        return NULL;
    }
    if (image->header == NULL || image->data == NULL) {
        return NULL;
    }
    int my_height = image->header->height;
    struct bmp_image* vertically_flipped_image = malloc(sizeof(struct bmp_image));
    vertically_flipped_image->header = calloc(1, sizeof(struct bmp_header));

    memcpy(vertically_flipped_image->header, image->header, sizeof(struct bmp_header));
    
    int total_length = my_height * image->header->width;
    vertically_flipped_image->data = calloc(total_length, sizeof(struct pixel));
    //memcpy(vertically_flipped_image->data, image->data, sizeof(struct pixel) * total_length);
    int calc_pos= 0;
    int i=0;
    while(i<my_height){
	for (int j=0; j<image->header->width; j++) {
            calc_pos = get_position_in_image(image->header, i,j);
            vertically_flipped_image->data[calc_pos] = image->data[total_length - calc_pos -1];
       		}
	i++;}
	int calc_pos2 = 0;
	int i=0;
	while(i<my_height){
	for (int j=0; j<image->header->width; j++) {
            calc_pos = get_position_in_image(vertically_flipped_image->header, i, j);
            calc_pos2 = get_vertically_mirror_image(vertically_flipped_image->header, i, j);
            vertically_flipped_image->data[calc_pos] = image->data[calc_pos2];
        }
	i++;
	}
    return vertically_flipped_image;
}

int get_horizontally_mirror_image(struct bmp_header* header, int height, int width) {
    int return_position = get_position_in_image(header, height, width) + header->width -1 - 2*width;
    return return_position;
}

struct bmp_image* flip_horizontally(const struct bmp_image* image) {
    if (image == NULL) {
        return NULL;
    }
    if (image->header == NULL || image->data == NULL) {
        return NULL;
    }
    int my_height = image->header->height;
    struct bmp_image* horizontally_flipped_image = malloc(sizeof(struct bmp_image));
    horizontally_flipped_image->header = calloc(1, sizeof(struct bmp_header));

    memcpy(horizontally_flipped_image->header, image->header, sizeof(struct bmp_header));
    
    int total_length = my_height * image->header->width;
    horizontally_flipped_image->data = calloc(total_length, sizeof(struct pixel));
    //memcpy(horizontally_flipped_image->data, image->data, sizeof(struct pixel) * total_length);
    int calc_pos= 0;
    int i=0;
    while(i<my_height){for (int j=0; j<image->header->width; j++) {
            calc_pos = get_position_in_image(image->header, i,j);
            horizontally_flipped_image->data[calc_pos] = image->data[total_length - calc_pos -1];
        }
	i++;
	}

   	int calc_pos2 = 0;
	int i=0;
	while(i<my_height;){for (int j=0; j<image->header->width; j++) {
            calc_pos = get_position_in_image(horizontally_flipped_image->header, i, j);
            calc_pos2 = get_horizontally_mirror_image(horizontally_flipped_image->header, i, j);
            horizontally_flipped_image->data[calc_pos] = image->data[calc_pos2];
        }i++;}
   
    return horizontally_flipped_image;
}

int get_rotate_right_position(struct bmp_header* header, int height, int width) {
    int return_position = header->width * width + header->width -1 - height;
    return return_position;
}

struct bmp_image* rotate_right(const struct bmp_image* image) {
    if (image == NULL) {
        return NULL;
    }
    if (image->header == NULL || image->data == NULL) {
        return NULL;
    }
    int my_height = image->header->height;
    struct bmp_image* rotate_right_image = malloc(sizeof(struct bmp_image));
    rotate_right_image->header = calloc(1, sizeof(struct bmp_header));

    memcpy(rotate_right_image->header, image->header, sizeof(struct bmp_header));
    
    int total_length = my_height * image->header->width;
    rotate_right_image->data = calloc(total_length, sizeof(struct pixel));
    //memcpy(horizontally_flipped_image->data, image->data, sizeof(struct pixel) * total_length);
    int calc_pos = 0;
    int calc_pos2 = 0;
    rotate_right_image->header->height = rotate_right_image->header->width;
    rotate_right_image->header->width = my_height;
    for (int i=0; i<rotate_right_image->header->height; i++) {
        for (int j=0; j<my_height; j++) {
            calc_pos = get_position_in_image(rotate_right_image->header, i, j);
            calc_pos2 = get_rotate_right_position(image->header, i, j);
            rotate_right_image->data[calc_pos] = image->data[calc_pos2];
        }
    }
    //printf("%d %d\n", rotate_right_image->header->image_size, rotate_right_image->header->size);
    update_size(rotate_right_image);
    //printf("%d %d\n", rotate_right_image->header->image_size, rotate_right_image->header->size);
    return rotate_right_image;
}

struct bmp_image* rotate_left(const struct bmp_image* image){
  if(image == NULL){
  return NULL;
  }
  else{
    if(image->header == NULL || image->data == NULL){
      return NULL;
    }
   else{
      if(image->header->type != 19778){
         return 0;
      }
      else if(image->header->width <= 0 ||image->header->width > 10000){
        return 0;
       }
      else if(image->header->height <= 0 ||image->header->height > 10000){
        return 0;
       }
      else{
        struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
        new_image->header = malloc(sizeof(struct bmp_header));
        memcpy(new_image->header,image->header,sizeof(struct bmp_header));
        new_image->header->width = image->header->height;
        new_image->header->height = image->header->width;
        size_t index1, index2;
        size_t h1 = (size_t)new_image->header->height;
        size_t w2 = (size_t)new_image->header->width;
        size_t help = w2*image->header->bpp/8;
        while(help%4 != 0){
         help++;
        }
        new_image->header->image_size = (uint32_t)(help*h1);
        new_image->header->size = (uint32_t)(h1*help + 54);
        new_image->data = calloc(h1*w2,sizeof(struct pixel));
        for(index1= 0; index1 < h1; index1++){
          for(index2 = 0; index2 < w2; index2++){
             new_image->data[index1*w2 + w2 - index2 -1].blue = image->data[index2*h1+index1].blue;
             new_image->data[index1*w2 + w2 - index2 -1].green = image->data[index2*h1+index1].green;
             new_image->data[index1*w2 + w2 - index2 -1].red = image->data[index2*h1+index1].red;
          }
        }
       return new_image;
   }
  }
 }
return 0;

}

int get_crop_position(struct bmp_header* header, struct bmp_header* header_after, int height, int width, int s_y, int s_x) {
    int help_me_calculate_this_position = s_y + header_after->height;
    help_me_calculate_this_position -= header->height;
    help_me_calculate_this_position *= -1;
    //int help_me_calculate_this_position = header->height - (s_y + header_after->height);
    int return_position = header->width*help_me_calculate_this_position + height*header->width + s_x + width;

    return return_position;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width) {
    if (image == NULL) {
        return NULL;
    }
    if (image->header == NULL || image->data == NULL) {
        return NULL;
    }

    /////////////////////////////////////

    // return null if is out of range //

    ///////////////////////////////////
    int s_y = start_y;
    int s_x = start_x;

    if (s_x >= 0 && s_y >= 0) {
        if (s_x <= image->header->width && s_y <= image->header->height) {
            if (s_x > image->header->width - width || s_y > image->header->height - height) {
                return NULL;
            }
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
    
    //int my_height = image->header->height;
    struct bmp_image* crop_image = malloc(sizeof(struct bmp_image));
    crop_image->header = calloc(1, sizeof(struct bmp_header));

    memcpy(crop_image->header, image->header, sizeof(struct bmp_header));
    
    int total_length = height * width;
    crop_image->data = calloc(total_length, sizeof(struct pixel));
    //memcpy(horizontally_flipped_image->data, image->data, sizeof(struct pixel) * total_length);
    int calc_pos = 0;
    int calc_pos2 = 0;
    crop_image->header->height = height;
    crop_image->header->width = width;
    for (int i=0; i<height; i++) {
        for (int j=0; j<crop_image->header->width; j++) {
            calc_pos = get_position_in_image(crop_image->header, i, j);
            calc_pos2 = get_crop_position(image->header, crop_image->header, i, j, s_y, s_x);
            crop_image->data[calc_pos].red = image->data[calc_pos2].red;
            crop_image->data[calc_pos].blue = image->data[calc_pos2].blue;
            crop_image->data[calc_pos].green = image->data[calc_pos2].green;
        }
    }
    update_size(crop_image);
    return crop_image;
}


struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep) {
    if (image == NULL) {
        return NULL;
    }
    if (image->header == NULL || image->data == NULL) {
        return NULL;
    }
    int my_height = image->header->height;
    if (colors_to_keep == NULL) {
        return NULL;
    }
    struct bmp_image* extracted_image = malloc(sizeof(struct bmp_image));
    extracted_image->header = calloc(1, sizeof(struct bmp_header));

    memcpy(extracted_image->header, image->header, sizeof(struct bmp_header));
    int counter;
    int red_green_blue[3] = {0, 0, 0};
    for (counter = 0; colors_to_keep[counter] != '\0'; counter++) {
        if (colors_to_keep[counter] == 'g' && red_green_blue[1] != 1) {
            red_green_blue[1] = 1;
        }
        else if (colors_to_keep[counter] == 'r' && red_green_blue[0] != 1) {
            red_green_blue[0] = 1;
        }
        else if (colors_to_keep[counter] == 'b' && red_green_blue[2] != 1) {
            red_green_blue[2] = 1;
        }
        else {
            free(extracted_image->header);
            extracted_image = NULL;
            free(extracted_image);
            extracted_image = NULL;
            return NULL;
        }
    }
    if (counter == 0) {
        free(extracted_image->header);
        extracted_image = NULL;
        free(extracted_image);
        extracted_image = NULL;
        return NULL;
    }
    int total_length = my_height * image->header->width;
    extracted_image->data = calloc(total_length, sizeof(struct pixel));
    //memcpy(vertically_flipped_image->data, image->data, sizeof(struct pixel) * total_length);
    int calc_pos= 0;
    int i=0;
    while(i<my_height) {
	int j=0;
        while(j<image->header->width) {
            calc_pos = get_position_in_image(image->header, i,j);
            extracted_image->data[calc_pos] = image->data[total_length - calc_pos -1];
        j++;}
     i++;}
    int i=0;
    while(i<my_height) {
	int j=0;
        while(j<image->header->width) {
            calc_pos = get_position_in_image(extracted_image->header, i, j);
            extracted_image->data[calc_pos] = image->data[calc_pos];
	j++;} 
i++;}
    uint8_t zero = 0;
    for (int i=0; i<my_height; i++) {
        for (int j=0; j<image->header->width; j++) {
            calc_pos = get_position_in_image(extracted_image->header, i, j);
            if (red_green_blue[2] == 0) {
                extracted_image->data[calc_pos].blue = zero;
            }
            extracted_image->data[calc_pos].red *= red_green_blue[0];
            if (red_green_blue[1] == 0) {
                extracted_image->data[calc_pos].green = 0;
            } 
        }
    }
    return extracted_image;
}

int get_scale_position(struct bmp_header* header, struct bmp_header* header_before, int height, int width) {
    int help_me_calculate_this_y_position = (height * header_before->height)/header->height;
    int help_me_calculate_this_x_position = (width * header_before->width)/header->width;
    int return_position = help_me_calculate_this_y_position * header_before->width + help_me_calculate_this_x_position;

    return return_position;
}

struct bmp_image* scale(const struct bmp_image* image, float factor) {
    if (image == NULL) {
        return NULL;
    }
    if (image->header == NULL || image->data == NULL) {
        return NULL;
    }
    if (factor < 0) {
        return NULL;
    }

    int my_height = image->header->height;
    struct bmp_image* scale_image = malloc(sizeof(struct bmp_image));
    scale_image->header = calloc(1, sizeof(struct bmp_header));

    memcpy(scale_image->header, image->header, sizeof(struct bmp_header));
    
    int total_length = round(my_height * factor) * round(image->header->width * factor);
    if (total_length <= 0) {
        free(scale_image->header);
        scale_image->header = NULL;
        free(scale_image);
        scale_image = NULL;
        return NULL;
    }
    scale_image->data = calloc(total_length, sizeof(struct pixel));
    //memcpy(scale_image->data, image->data, sizeof(struct pixel) * total_length);
    scale_image->header->height = round(my_height * factor);
    scale_image->header->width = round(scale_image->header->width * factor);
    int calc_pos= 0;
    for (int i=0; i<my_height; i++) {
        for (int j=0; j<image->header->width; j++) {
            calc_pos = get_position_in_image(image->header, i,j) * 0;
            scale_image->data[calc_pos] = image->data[0];
        }
    }
    int calc_pos2 = 0;
    for (int i=0; i<scale_image->header->height; i++) {
        for (int j=0; j<scale_image->header->width; j++) {
            calc_pos = get_position_in_image(scale_image->header, i, j);
            calc_pos2 = get_scale_position(scale_image->header, image->header, i, j);
            scale_image->data[calc_pos] = image->data[calc_pos2];
        }
    }
    update_size(scale_image);
    return scale_image;
}
