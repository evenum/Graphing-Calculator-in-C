#include "callBacks.h"
#include "drawArea.h"

void drawButton(GtkButton *button, gpointer dd_Info)
{
    ddInfo *data = (ddInfo *)dd_Info;
    guint selected = gtk_drop_down_get_selected(GTK_DROP_DOWN(data->dropDown));
    g_print("Selected: %d\n", selected);

    switch (selected)
    {
    case 0:
        gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(data->drawArea), drawSineWave, data, NULL);
        break;
    case 1:
        gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(data->drawArea), drawCosineWave, data, NULL);
        break;
    case 2:
        gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(data->drawArea), drawLinear, data, NULL);
        break;
    case 3:
        gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(data->drawArea), drawTest, data, NULL);
        break;
    }
}

void app_activate(GApplication *app, GFile **files, int n_files, char *hint)
{

    ddInfo *data = g_new(ddInfo, 1);
    GtkWidget *window;
    GtkWidget *boxSideMenu;
    GtkWidget *boxHorizontal;
    GtkWidget *boxEntries;
    GtkWidget *separator;
    GtkWidget *dropDown;
    GtkWidget *entry1;
    GtkWidget *button1;
    GtkWidget *drawArea;
    GtkWidget *scale;
    GtkStringList *stringList;

    char *options[] = {"Sine", "Cosine", "Linear", "Test", NULL};
    stringList = gtk_string_list_new((const char *const *)options);
    dropDown = gtk_drop_down_new(G_LIST_MODEL(stringList), NULL);
    data->dropDown = dropDown;
    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "Graphing Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);

    scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1.0, 100.0, 0.5);
    data->scale = scale;
    boxHorizontal = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    boxSideMenu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    boxEntries = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    button1 = gtk_button_new_with_label("Plot");
    drawArea = gtk_drawing_area_new();
    data->drawArea = drawArea;
    entry1 = gtk_entry_new();

    gtk_window_set_child(GTK_WINDOW(window), boxHorizontal);
    gtk_box_append(GTK_BOX(boxHorizontal), boxSideMenu);
    gtk_box_append(GTK_BOX(boxHorizontal), separator);
    gtk_box_append(GTK_BOX(boxSideMenu), boxEntries);
    gtk_box_append(GTK_BOX(boxSideMenu), scale);
    gtk_box_append(GTK_BOX(boxEntries), dropDown);
    gtk_box_append(GTK_BOX(boxEntries), button1);

    gtk_scale_set_draw_value(GTK_SCALE(scale), TRUE);

    gtk_widget_set_margin_start(boxSideMenu, 10);
    gtk_widget_set_margin_top(boxSideMenu, 40);
    gtk_widget_set_hexpand(entry1, TRUE);

    gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawArea), 1000);
    gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawArea), 1000);
    gtk_widget_set_hexpand(drawArea, TRUE);

    gtk_box_append(GTK_BOX(boxHorizontal), drawArea);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawArea), drawGraph, NULL, NULL);
    g_signal_connect_data(button1, "clicked", G_CALLBACK(drawButton), data, NULL, 0);
    g_signal_connect_data(scale, "value-changed", G_CALLBACK(drawButton), data, NULL, 0);
    gtk_window_present(GTK_WINDOW(window));
}