#ifndef _MY_CALLBACKS_H
#define _MY_CALLBACKS_H

#include <gtk/gtk.h>

typedef struct
{
    GtkWidget *drawArea;
    GtkWidget *dropDown;
    GtkWidget *scale;
} ddInfo;

void app_activate(GApplication *app, GFile **files, int n_files, char *hint);
void drawButton(GtkButton *button, gpointer dd_Info);

#endif