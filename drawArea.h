#ifndef _DRAW_AREA_H
#define _DRAW_AREA_H

#include <gtk/gtk.h>
#include <cairo.h>

void drawGraph(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data);
void drawLinear(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data);
void drawSineWave(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data);
void drawCosineWave(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data);

#endif // _DRAW_AREA_H