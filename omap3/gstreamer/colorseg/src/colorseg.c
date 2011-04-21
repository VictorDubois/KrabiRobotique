#include <stdio.h>
#include <stdlib.h>
//#define NDEBUG
#include <assert.h>

#include "colorseg.h"
#include "threshold.h"


#define min(a, b) ((a<b)?a:b)
#define max(a, b) ((a>b)?a:b)


static inline color_class get_color_class(unsigned char *pixel) {
    // Segmentation super rapide
    // [Y/U/V]Class sont définis dans threshold.h
    return YClass[pixel[0]] & UClass[pixel[1]] & VClass[pixel[2]];
}

static inline color_class get_color_class_YUY2(unsigned char *data, unsigned int pixel_nb) {
    unsigned int offset = pixel_nb / 2;
    unsigned int add = pixel_nb % 2;
    unsigned char Y=data[4*offset + 2*add], U=data[4*offset + 1], V=data[4*offset + 3];
    return YClass[Y] & UClass[U] & VClass[V];
}

static inline void set_pixel_YUY2(unsigned char *data, unsigned int pixel_nb, unsigned char Y, unsigned char U, unsigned char V) {
    unsigned int offset = pixel_nb / 2;
    unsigned int add = pixel_nb % 2;
    data[4*offset + 2*add] = Y, data[4*offset + 1] = U, data[4*offset + 3] = V;
}

static inline void get_color_from_class(unsigned char *Y, unsigned char *U, unsigned char *V, color_class class) {
    switch (class) {
        case 0:
            *Y = 0; *U = *V = 128;
            break;
        case 1:
            *Y = 76; *U = 85; *V = 255;
            break;
        case 2:
            *Y = 30; *U = 255; *V = 107;
            break;
        case 4:
            *Y = 152; *U = 42; *V = 202;
            break;
        case 8:
            *Y = 226; *U = 1; *V = 149;
            break;
        default:
            *Y = 255; *U = *V = 128;
            break;
    }
}

void draw_segmentation(unsigned char *data, unsigned int width, unsigned int height, unsigned char mode) {
    unsigned int i, j;
    unsigned char Y, U, V;
    for (j=0;j<height;j++) {
        for (i=0;i<width;i+=2) {
            color_class class = get_color_class_YUY2(data+width*j*2, i);
            get_color_from_class(&Y, &U, &V, class);
            unsigned char *l = data + width*2*j + 2*i;
            if (mode == 0 || (mode == 1 && class != 0)) {
                l[0] = Y;
                l[1] = U;
                l[2] = Y;
                l[3] = V;
            } else if (mode == 2) {
                l[0] = ((l[0]>>1) + (Y>>1));
                l[1] = ((l[1]>>1) + (U>>1));
                l[2] = ((l[2]>>1) + (Y>>1));
                l[3] = ((l[3]>>1) + (V>>1));
            }
        }
    }
}

