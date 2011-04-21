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

/**
 * SECTION:element-colorseg
 *
 * FIXME:Describe colorseg here.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch -v -m fakesrc ! colorseg ! fakesink silent=TRUE
 * ]|
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/video/video.h>

#include "colorseg.h"

#include "gstcolorseg.h"

/* debug variable definition */
GST_DEBUG_CATEGORY (gst_color_seg_debug);

/* Filter signals and args */
enum
{
  /* FILL ME */
  LAST_SIGNAL
};

enum
{
  PROP_0,
  PROP_DRAW_MODE,
};

/* the capabilities of the inputs and outputs.
 */
static GstStaticPadTemplate sink_template =
GST_STATIC_PAD_TEMPLATE (
  "sink",
  GST_PAD_SINK,
  GST_PAD_ALWAYS,
  GST_STATIC_CAPS ("video/x-raw-yuv, "
        "format = (fourcc) YUY2")
);

static GstStaticPadTemplate src_template =
GST_STATIC_PAD_TEMPLATE (
  "src",
  GST_PAD_SRC,
  GST_PAD_ALWAYS,
  GST_STATIC_CAPS ("video/x-raw-yuv, "
        "format = (fourcc) YUY2")
);

#define DEFAULT_PROP_DRAW_MODE COLOR_SEG_NORMAL

#define GST_TYPE_COLOR_SEG_METHOD (gst_color_seg_method_get_type())
static GType
gst_color_seg_method_get_type (void)
{
  static GType color_seg_method_type = 0;

  static const GEnumValue color_seg_methods[] = {
    {COLOR_SEG_NORMAL, "Normal", "normal"},
    {COLOR_SEG_OVERLAY, "Overlay", "overlay"},
    {COLOR_SEG_MIX, "Mix", "mix"},
    {0, NULL, NULL},
  };

  if (!color_seg_method_type) {
    color_seg_method_type =
        g_enum_register_static ("ColorSegMethod", color_seg_methods);
  }
  return color_seg_method_type;
}

GST_BOILERPLATE (GstColorSeg, gst_color_seg, GstVideoFilter,
    GST_TYPE_VIDEO_FILTER);

static void gst_color_seg_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_color_seg_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);

static GstFlowReturn gst_color_seg_transform_ip (GstBaseTransform * base,
    GstBuffer * outbuf);
static gboolean gst_color_seg_set_caps (GstBaseTransform * base, GstCaps * incaps, GstCaps * outcaps);

/* GObject vmethod implementations */

static void
gst_color_seg_base_init (gpointer klass)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);

  gst_element_class_set_details_simple (element_class,
    "ColorSeg",
    "Filter/Effect/Video",
    "Misc operations",
    "Rémi Koenig <remi.koenig@telecom-bretagne.eu>");

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&src_template));
  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&sink_template));
}

/* initialize the colorseg's class */
static void
gst_color_seg_class_init (GstColorSegClass * klass)
{
  GObjectClass *gobject_class;

  gobject_class = (GObjectClass *) klass;
  gobject_class->set_property = gst_color_seg_set_property;
  gobject_class->get_property = gst_color_seg_get_property;

  g_object_class_install_property (gobject_class, PROP_DRAW_MODE,
    g_param_spec_enum ("draw-mode", "Draw mode", "0, 1 or 2",
          GST_TYPE_COLOR_SEG_METHOD, DEFAULT_PROP_DRAW_MODE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  GST_BASE_TRANSFORM_CLASS (klass)->transform_ip =
      GST_DEBUG_FUNCPTR (gst_color_seg_transform_ip);
  GST_BASE_TRANSFORM_CLASS (klass)->set_caps =
      GST_DEBUG_FUNCPTR (gst_color_seg_set_caps);
}

/* initialize the new element
 * initialize instance structure
 */
static void
gst_color_seg_init (GstColorSeg *filter, GstColorSegClass * klass)
{
  filter->draw_mode = DEFAULT_PROP_DRAW_MODE;
}

static void
gst_color_seg_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstColorSeg *filter = GST_COLORSEG (object);

  switch (prop_id) {
    case PROP_DRAW_MODE:
      filter->draw_mode = g_value_get_enum (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_color_seg_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstColorSeg *filter = GST_COLORSEG (object);

  switch (prop_id) {
    case PROP_DRAW_MODE:
      g_value_set_enum (value, filter->draw_mode);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static gboolean
gst_color_seg_set_caps (GstBaseTransform * base, GstCaps * incaps, GstCaps * outcaps)
{
  GstColorSeg *filter = GST_COLORSEG (base);
  gboolean ret = TRUE;

  ret = gst_video_format_parse_caps (incaps, NULL,
        &filter->width, &filter->height);
  if (!ret)
    return ret;

  g_print ("Caps negotiation succeeded with %dx%d\n",
	   (gint)filter->width, (gint)filter->height);

  return ret;
}


/* GstBaseTransform vmethod implementations */

/* this function does the actual processing
 */
static GstFlowReturn
gst_color_seg_transform_ip (GstBaseTransform * base, GstBuffer * outbuf)
{
  GstColorSeg *filter = GST_COLORSEG (base);

  draw_segmentation(outbuf->data, filter->width, filter->height, filter->draw_mode);

  return GST_FLOW_OK;
}


/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
static gboolean
colorseg_init (GstPlugin * colorseg)
{
  if (!gst_element_register (colorseg, "colorseg", GST_RANK_NONE,
      GST_TYPE_COLORSEG))
    return FALSE;
  GST_DEBUG_CATEGORY_INIT (gst_color_seg_debug, "colorseg", 0,
      "colorseg element");
  return TRUE;
}

/* gstreamer looks for this structure to register colorsegs
 */
GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    "colorseg",
    "Color segmentation",
    colorseg_init,
    VERSION,
    "LGPL",
    "GStreamer",
    "http://gstreamer.net/"
)
