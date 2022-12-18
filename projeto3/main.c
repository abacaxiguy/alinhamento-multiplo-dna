#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include <gtk/gtk.h> 

static char seq1[101];
static char seq2[101];
static char seq3[101];
static char seq4[101];
static char seq5[101];
static char seq6[101];
static char seq7[101];
static char seq8[101];
static char seq9[101];
static char seq10[101];

static int active1 = 1;
static int active2 = 1;
static int active3 = 0;
static int active4 = 0;
static int active5 = 0;
static int active6 = 0;
static int active7 = 0;
static int active8 = 0;
static int active9 = 0;
static int active10 = 0;

static int sequencias_ativas = 2;
static int max_string_size;

GtkWidget *window;

// Function to open a dialog box with a message
void quick_message(GtkWindow *parent, gchar *message)
{
    GtkWidget *dialog, *label, *content_area;
    GtkDialogFlags flags;

    // Create the widgets
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons("Warning", parent, flags, "OK", GTK_RESPONSE_NONE, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label = gtk_label_new(message);
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);

    // Ensure that the dialog box is destroyed when the user responds
    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);

    // Add the label, and show everything we’ve added
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 25);
    gtk_widget_show_all(dialog);
}

static void disable_entry(GtkWidget *widget, gpointer data)
{
    gtk_widget_set_sensitive(GTK_WIDGET(data), !gtk_widget_get_sensitive(GTK_WIDGET(data)));
}

static int valida_sequencias()
{
    if (active1) {
        if (!verificaCharValidos(seq1) || (strlen(seq1) > 100) || strlen(seq1) == 0) {
            quick_message(GTK_WINDOW(window), "Sequencia 1 invalida");
            return 0;
        }
        if (strlen(seq1) > max_string_size) max_string_size = strlen(seq1);
    }
    if (active2) {
        if (!verificaCharValidos(seq2) || (strlen(seq2) > 100) || strlen(seq2) == 0) {
            quick_message(GTK_WINDOW(window), "Sequencia 2 invalida");
            return 0;
        }
        if (strlen(seq2) > max_string_size) max_string_size = strlen(seq2);
    }
    if (active3) {
        if (!verificaCharValidos(seq3) || (strlen(seq3) > 100) || strlen(seq3) == 0) {
            quick_message(GTK_WINDOW(window), "Sequencia 3 invalida");
            return 0;
        }
        if (strlen(seq3) > max_string_size) max_string_size = strlen(seq3);
    }
    if (active4) {
        if (!verificaCharValidos(seq4) || (strlen(seq4) > 100) || strlen(seq4) == 0) {
            quick_message(GTK_WINDOW(window), "Sequencia 4 invalida");
            return 0;
        }
        if (strlen(seq4) > max_string_size) max_string_size = strlen(seq4);
    }
    if (active5) {
        if (!verificaCharValidos(seq5) || (strlen(seq5) > 100) || strlen(seq5) == 0) {
            quick_message(GTK_WINDOW(window), "Sequencia 5 invalida");
            return 0;
        }
        if (strlen(seq5) > max_string_size) max_string_size = strlen(seq5);
    }

    if (active6){
        if (!verificaCharValidos(seq6) || (strlen(seq6) > 100) || strlen(seq6) == 0) {
            quick_message(GTK_WINDOW(window), "Sequencia 6 invalida");
            return 0;
        }
        if (strlen(seq6) > max_string_size) max_string_size = strlen(seq6);
    }

    if (active7){
        if (!verificaCharValidos(seq7) || (strlen(seq7) > 100) || strlen(seq7) == 0) {
            quick_message(GTK_WINDOW(window), "Sequencia 7 invalida");
            return 0;
        }
        if (strlen(seq7) > max_string_size) max_string_size = strlen(seq7);
    }

    if (active8){
        if (!verificaCharValidos(seq8) || (strlen(seq8) > 100) || strlen(seq8) == 0) {
            quick_message(GTK_WINDOW(window), "Sequencia 8 invalida");
            return 0;
        }
        if (strlen(seq8) > max_string_size) max_string_size = strlen(seq8);
    }

    if (active9){
        if (!verificaCharValidos(seq9) || (strlen(seq9) > 100) || strlen(seq9) == 0) {
            quick_message(GTK_WINDOW(window), "Sequencia 9 invalida");
            return 0;
        }
        if (strlen(seq9) > max_string_size) max_string_size = strlen(seq9);
    }

    if (active10){
        if (!verificaCharValidos(seq10) || (strlen(seq10) > 100) || strlen(seq10) == 0) {
            quick_message(GTK_WINDOW(window), "Sequencia 10 invalida");
            return 0;
        }
        if (strlen(seq10) > max_string_size) max_string_size = strlen(seq10);
    }

    return 1;
}

static void
alinha_sequencias(GtkWidget *widget,
             gpointer data)
{
    if (!valida_sequencias()) return;

    char sequencias[sequencias_ativas][101];

    strcpy(sequencias[0], seq1);
    strcpy(sequencias[1], seq2);
    if (active3) strcpy(sequencias[2], seq3);
    if (active4) strcpy(sequencias[3], seq4);
    if (active5) strcpy(sequencias[4], seq5);
    if (active6) strcpy(sequencias[5], seq6);
    if (active7) strcpy(sequencias[6], seq7);
    if (active8) strcpy(sequencias[7], seq8);
    if (active9) strcpy(sequencias[8], seq9);
    if (active10) strcpy(sequencias[9], seq10);

    g_print("\nVocê digitou %d sequencias com tamanho máximo de %d caracteres\n", sequencias_ativas, max_string_size);

    for (int i = 0; i < sequencias_ativas; i++)
    {
        printf("%s\n", sequencias[i]);
    }

    // remove all widgets in grid
    gtk_container_foreach(GTK_CONTAINER(data), (GtkCallback) gtk_widget_destroy, NULL);
}

static void on_sequencia_changed(GtkWidget *widget, gpointer data)
{
    const gchar* entry_text;
    entry_text = gtk_entry_get_text(GTK_ENTRY(widget));

    if(strcmp((char *)data, "1") == 0)
        strcpy(seq1, entry_text);
    else if(strcmp((char *)data, "2") == 0)
        strcpy(seq2, entry_text);
    else if(strcmp((char *)data, "3") == 0)
        strcpy(seq3, entry_text);
    else if(strcmp((char *)data, "4") == 0)
        strcpy(seq4, entry_text);
    else if(strcmp((char *)data, "5") == 0)
        strcpy(seq5, entry_text);
    else if(strcmp((char *)data, "6") == 0)
        strcpy(seq6, entry_text);
    else if(strcmp((char *)data, "7") == 0)
        strcpy(seq7, entry_text);
    else if(strcmp((char *)data, "8") == 0)
        strcpy(seq8, entry_text);
    else if(strcmp((char *)data, "9") == 0)
        strcpy(seq9, entry_text);
    else if(strcmp((char *)data, "10") == 0)
        strcpy(seq10, entry_text);
}

static void on_check_toggled(GtkWidget *widget, gpointer data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) sequencias_ativas++;
    else sequencias_ativas--;

    if(strcmp((char *)data, "1") == 0)
        active1 = !active1;
    else if(strcmp((char *)data, "2") == 0)
        active2 = !active2;
    else if(strcmp((char *)data, "3") == 0)
        active3 = !active3;
    else if(strcmp((char *)data, "4") == 0)
        active4 = !active4;
    else if(strcmp((char *)data, "5") == 0)
        active5 = !active5;
    else if(strcmp((char *)data, "6") == 0)
        active6 = !active6;
    else if(strcmp((char *)data, "7") == 0)
        active7 = !active7;
    else if(strcmp((char *)data, "8") == 0)
        active8 = !active8;
    else if(strcmp((char *)data, "9") == 0)
        active9 = !active9;
    else if(strcmp((char *)data, "10") == 0)
        active10 = !active10;

    g_print("Sequencias ativas: %d\n", sequencias_ativas);
    
}

static void creates_all_entries(GtkWidget *grid, GtkWidget **seq1Entry, GtkWidget **seq2Entry, GtkWidget **seq3Entry, GtkWidget **seq4Entry, GtkWidget **seq5Entry, GtkWidget **seq6Entry, GtkWidget **seq7Entry, GtkWidget **seq8Entry, GtkWidget **seq9Entry, GtkWidget **seq10Entry)
{
    *seq1Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq1Entry), "Sequencia 1");
    g_signal_connect(*seq1Entry, "changed", G_CALLBACK(on_sequencia_changed), "1");
    gtk_grid_attach(GTK_GRID(grid), *seq1Entry, 0, 0, 3, 1);

    *seq2Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq2Entry), "Sequencia 2");
    g_signal_connect(*seq2Entry, "changed", G_CALLBACK(on_sequencia_changed), "2");
    gtk_grid_attach(GTK_GRID(grid), *seq2Entry, 0, 1, 3, 1);

    *seq3Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq3Entry), "Sequencia 3");
    g_signal_connect(*seq3Entry, "changed", G_CALLBACK(on_sequencia_changed), "3");
    gtk_grid_attach(GTK_GRID(grid), *seq3Entry, 0, 2, 3, 1);
    gtk_widget_set_sensitive(*seq3Entry, FALSE);

    *seq4Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq4Entry), "Sequencia 4");
    g_signal_connect(*seq4Entry, "changed", G_CALLBACK(on_sequencia_changed), "4");
    gtk_grid_attach(GTK_GRID(grid), *seq4Entry, 0, 3, 3, 1);
    gtk_widget_set_sensitive(*seq4Entry, FALSE);

    *seq5Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq5Entry), "Sequencia 5");
    g_signal_connect(*seq5Entry, "changed", G_CALLBACK(on_sequencia_changed), "5");
    gtk_grid_attach(GTK_GRID(grid), *seq5Entry, 0, 4, 3, 1);
    gtk_widget_set_sensitive(*seq5Entry, FALSE);

    *seq6Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq6Entry), "Sequencia 6");
    g_signal_connect(*seq6Entry, "changed", G_CALLBACK(on_sequencia_changed), "6");
    gtk_grid_attach(GTK_GRID(grid), *seq6Entry, 0, 5, 3, 1);
    gtk_widget_set_sensitive(*seq6Entry, FALSE);

    *seq7Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq7Entry), "Sequencia 7");
    g_signal_connect(*seq7Entry, "changed", G_CALLBACK(on_sequencia_changed), "7");
    gtk_grid_attach(GTK_GRID(grid), *seq7Entry, 0, 6, 3, 1);
    gtk_widget_set_sensitive(*seq7Entry, FALSE);

    *seq8Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq8Entry), "Sequencia 8");
    g_signal_connect(*seq8Entry, "changed", G_CALLBACK(on_sequencia_changed), "8");
    gtk_grid_attach(GTK_GRID(grid), *seq8Entry, 0, 7, 3, 1);
    gtk_widget_set_sensitive(*seq8Entry, FALSE);

    *seq9Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq9Entry), "Sequencia 9");
    g_signal_connect(*seq9Entry, "changed", G_CALLBACK(on_sequencia_changed), "9");
    gtk_grid_attach(GTK_GRID(grid), *seq9Entry, 0, 8, 3, 1);
    gtk_widget_set_sensitive(*seq9Entry, FALSE);

    *seq10Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq10Entry), "Sequencia 10");
    g_signal_connect(*seq10Entry, "changed", G_CALLBACK(on_sequencia_changed), "10");
    gtk_grid_attach(GTK_GRID(grid), *seq10Entry, 0, 9, 3, 1);
    gtk_widget_set_sensitive(*seq10Entry, FALSE);
}

// creates_all_checkboxes(grid, &check1, &check2, &check3, &check4, &check5);
static void creates_all_checkboxes(GtkWidget *grid, GtkWidget **check1, GtkWidget **check2, GtkWidget **check3, GtkWidget **check4, GtkWidget **check5, GtkWidget **check6, GtkWidget **check7, GtkWidget **check8, GtkWidget **check9, GtkWidget **check10)
{
    *check1 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check1, 4, 0, 1, 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(*check1), TRUE);
    g_signal_connect(*check1, "toggled", G_CALLBACK(on_check_toggled), "1");
    gtk_widget_set_sensitive(*check1, FALSE);

    *check2 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check2, 4, 1, 1, 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(*check2), TRUE);
    g_signal_connect(*check2, "toggled", G_CALLBACK(on_check_toggled), "2");
    gtk_widget_set_sensitive(*check2, FALSE);

    *check3 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check3, 4, 2, 1, 1);
    g_signal_connect(*check3, "toggled", G_CALLBACK(on_check_toggled), "3");

    *check4 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check4, 4, 3, 1, 1);
    g_signal_connect(*check4, "toggled", G_CALLBACK(on_check_toggled), "4");

    *check5 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check5, 4, 4, 1, 1);
    g_signal_connect(*check5, "toggled", G_CALLBACK(on_check_toggled), "5");

    *check6 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check6, 4, 5, 1, 1);
    g_signal_connect(*check6, "toggled", G_CALLBACK(on_check_toggled), "6");

    *check7 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check7, 4, 6, 1, 1);
    g_signal_connect(*check7, "toggled", G_CALLBACK(on_check_toggled), "7");

    *check8 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check8, 4, 7, 1, 1);
    g_signal_connect(*check8, "toggled", G_CALLBACK(on_check_toggled), "8");

    *check9 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check9, 4, 8, 1, 1);
    g_signal_connect(*check9, "toggled", G_CALLBACK(on_check_toggled), "9");

    *check10 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check10, 4, 9, 1, 1);
    g_signal_connect(*check10, "toggled", G_CALLBACK(on_check_toggled), "10");
}

static void
activate(GtkApplication *app,
         gpointer user_data)
{
    GtkWidget *grid;
    GtkWidget *button;

    GtkWidget *seq1Entry, *seq2Entry, *seq3Entry, *seq4Entry, *seq5Entry, *seq6Entry, *seq7Entry, *seq8Entry, *seq9Entry, *seq10Entry;

    GtkWidget *check1, *check2, *check3, *check4, *check5, *check6, *check7, *check8, *check9, *check10;

    /* create a new window, and set its title */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Alinhamento Múltiplo de Sequências");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    // change background color
    // GdkRGBA color = (GdkRGBA){1.0, 0.2, 0.3, 1.0};
    // gtk_widget_override_background_color(window, GTK_STATE_FLAG_NORMAL, &color);


    grid = gtk_grid_new();

    gtk_container_add(GTK_CONTAINER(window), grid);

    creates_all_entries(grid, &seq1Entry, &seq2Entry, &seq3Entry, &seq4Entry, &seq5Entry, &seq6Entry, &seq7Entry, &seq8Entry, &seq9Entry, &seq10Entry);
    creates_all_checkboxes(grid, &check1, &check2, &check3, &check4, &check5, &check6, &check7, &check8, &check9, &check10);

    g_signal_connect(check1, "toggled", G_CALLBACK(disable_entry), seq1Entry);
    g_signal_connect(check2, "toggled", G_CALLBACK(disable_entry), seq2Entry);
    g_signal_connect(check3, "toggled", G_CALLBACK(disable_entry), seq3Entry);
    g_signal_connect(check4, "toggled", G_CALLBACK(disable_entry), seq4Entry);
    g_signal_connect(check5, "toggled", G_CALLBACK(disable_entry), seq5Entry);
    g_signal_connect(check6, "toggled", G_CALLBACK(disable_entry), seq6Entry);
    g_signal_connect(check7, "toggled", G_CALLBACK(disable_entry), seq7Entry);
    g_signal_connect(check8, "toggled", G_CALLBACK(disable_entry), seq8Entry);
    g_signal_connect(check9, "toggled", G_CALLBACK(disable_entry), seq9Entry);
    g_signal_connect(check10, "toggled", G_CALLBACK(disable_entry), seq10Entry);

    // space between rows and columns
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);

    // width of a entry
    gtk_entry_set_width_chars(GTK_ENTRY(seq1Entry), 100);

    // space
    GtkWidget *space = gtk_label_new(" ");
    gtk_grid_attach(GTK_GRID(grid), space, 0, 10, 4, 1);

    button = gtk_button_new_with_label("Alinhar");
    g_signal_connect(button, "clicked", G_CALLBACK(alinha_sequencias), grid);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 11, 6, 2);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("add.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}