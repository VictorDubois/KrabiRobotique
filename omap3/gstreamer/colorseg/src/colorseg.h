#ifndef COLORSEG_INCLUDED
#define COLORSEG_INCLUDED

typedef enum {
  COLOR_SEG_NORMAL,
  COLOR_SEG_OVERLAY,
  COLOR_SEG_MIX,
  COLOR_SEG_NONE
} ColorSegMethod;

typedef unsigned char color_class;

void draw_segmentation(unsigned char *data, unsigned int width, unsigned int height, unsigned char mode);

#endif // COLORSEG_INCLUDED
