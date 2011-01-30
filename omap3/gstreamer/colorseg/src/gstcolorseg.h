/* 
 * GStreamer ColorSeg plugin
 * Copyright (C) 2010 Rémi <<user@hostname.org>>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
 
#ifndef __GST_COLORSEG_H__
#define __GST_COLORSEG_H__

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/video/gstvideofilter.h>

#include "colorseg.h"

G_BEGIN_DECLS

GST_DEBUG_CATEGORY_EXTERN (gst_color_seg_debug);
#define GST_CAT_DEFAULT gst_color_seg_debug

#define GST_TYPE_COLORSEG \
  (gst_color_seg_get_type())
#define GST_COLORSEG(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_COLORSEG,GstColorSeg))
#define GST_COLORSEG_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_COLORSEG,GstColorSegClass))
#define GST_IS_COLORSEG(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_COLORSEG))
#define GST_IS_COLORSEG_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_COLORSEG))

typedef struct _GstColorSeg      GstColorSeg;
typedef struct _GstColorSegClass GstColorSegClass;

struct _GstColorSeg {
  GstVideoFilter element;
  ColorSegMethod draw_mode;
  unsigned int width, height;
};

struct _GstColorSegClass {
  GstVideoFilterClass parent_class;
};

GType gst_color_seg_get_type (void);

G_END_DECLS

#endif /* __GST_COLORSEG_H__ */
