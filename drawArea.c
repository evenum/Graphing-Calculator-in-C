#include <math.h>
#include "drawArea.h"
#include "callBacks.h"

// double bezierControlPointY(double cpy, double t)
// {
//     return (cpy * (6 * pow(t, 3) - 9 * pow(t, 2) - 3 * t));
// }

void drawGraph(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data)
{
    // Draw Grid
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_paint(cr);

    cairo_set_line_width(cr, 1);
    cairo_set_source_rgb(cr, 0, 0, 0);

    // Move origin to center of screen and flip y to make positive upwards
    cairo_translate(cr, width / 2, height / 2);
    cairo_scale(cr, 1, -1);

    // Draw X and Y axes
    cairo_move_to(cr, -width / 2.0, 0.0);
    cairo_line_to(cr, width / 2.0, 0.0);
    cairo_move_to(cr, 0.0, -height / 2.0);
    cairo_line_to(cr, 0.0, height / 2.0);
    cairo_stroke(cr);

    // Draw grid lines
    int num_lines = 10;
    double spacing = width / (2.0 * num_lines);
    cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
    for (int i = 1; i <= num_lines; ++i)
    {
        // Vertical lines
        cairo_move_to(cr, i * spacing, -height / 2.0);
        cairo_line_to(cr, i * spacing, height / 2.0);
        cairo_move_to(cr, -i * spacing, -height / 2.0);
        cairo_line_to(cr, -i * spacing, height / 2.0);
        // Horizontal lines
        cairo_move_to(cr, -width / 2.0, i * spacing);
        cairo_line_to(cr, width / 2.0, i * spacing);
        cairo_move_to(cr, -width / 2.0, -i * spacing);
        cairo_line_to(cr, width / 2.0, -i * spacing);
    }
    cairo_stroke(cr);
}

void drawSineWave(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data)
{

    ddInfo *data = (ddInfo *)user_data;
    drawGraph(area, cr, width, height, user_data);
    double scale, x, y;

    double cpx = G_PI;
    double cpyS = (2 * sqrt(3));

    scale = gtk_range_get_value(GTK_RANGE(data->scale));
    x = y = 0.0;
    cairo_set_source_rgb(cr, 0.1, 0.3, 0.3);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr, x, 0);
    double cpxS = x + G_PI * scale;
    cpyS = cpyS * scale;
    for (x = 0; x <= width;)
    {
        cairo_curve_to(cr, cpxS, cpyS, cpxS, -cpyS, x + (2 * G_PI) * scale, 0);
        x = x + (2 * G_PI) * scale;
        cpxS = cpxS + (2 * G_PI) * scale;
    }
    cairo_stroke(cr);
}

void drawCosineWave(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data)
{

    ddInfo *data = (ddInfo *)user_data;
    drawGraph(area, cr, width, height, user_data);
    double scale, x, y;
    scale = gtk_range_get_value(GTK_RANGE(data->scale));
    x = y = 0.0;
    cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
    cairo_set_line_width(cr, 2.0);

    for (x = -width; x <= width; x += 0.01)
    {
        y = cos(x) * scale;
        cairo_line_to(cr, x * scale, y);
    }
    cairo_stroke(cr);
}

void drawLinear(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data)
{

    drawGraph(area, cr, width, height, user_data);
    double x, y;
    x = y = 0;
    cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
    cairo_set_line_width(cr, 2.0);

    for (x = -width; x <= width; x += 0.01)
    {
        y = x;
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);
}

void drawTest(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data)
{

    ddInfo *data = (ddInfo *)user_data;
    drawGraph(area, cr, width, height, user_data);
    double scale, x, y;

    double cpx = G_PI;
    double cpyS = (2 * sqrt(3));

    scale = gtk_range_get_value(GTK_RANGE(data->scale));
    x = y = 0.0;
    cairo_set_source_rgb(cr, 1, 0.3, 0.3);
    cairo_set_line_width(cr, 6.0);
    cairo_move_to(cr, x, 0);
    double cpxS = x + G_PI * scale;
    cpyS = cpyS * scale;
    for (x = 0; x <= width;)
    {
        cairo_curve_to(cr, cpxS, cpyS, cpxS, -cpyS, x + (2 * G_PI) * scale, 0);
        x = x + (2 * G_PI) * scale;
        cpxS = cpxS + (2 * G_PI) * scale;
    }
    cairo_stroke(cr);

    cairo_set_source_rgb(cr, 0.1, 0.3, 0.3);
    cairo_set_line_width(cr, 2.0);

    for (x = -width; x <= width; x += 0.01)
    {
        y = sin(x) * scale;
        cairo_line_to(cr, x * scale, y);
    }
    cairo_stroke(cr);
}