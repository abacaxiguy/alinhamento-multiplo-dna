#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include <gtk/gtk.h>

static char seq1[100];
static char seq2[100];
static char seq3[100];
static char seq4[100];
static char seq5[100];
static int sequencias = 2;

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

static void
printa_nomes(GtkWidget *widget,
             gpointer data)
{
    if (!verificaCharValidos(seq1) 
    || !verificaCharValidos(seq2)
    || !verificaCharValidos(seq3)
    || !verificaCharValidos(seq4)
    || !verificaCharValidos(seq5))
    {
        quick_message(GTK_WINDOW(window), "Sequencias com caracteres invalidos");
        return;
    }

    if (sequencias < 2)
    {
        quick_message(GTK_WINDOW(window), "Selecione pelo menos 2 sequencias");
        return;
    }

    g_print("Sequencia 1: %s\n", seq1);
    g_print("Sequencia 2: %s\n", seq2);
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
}

static void on_check_toggled(GtkWidget *widget, gpointer data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) sequencias++;
    else sequencias--;

    g_print("Sequencias ativas: %d", sequencias);
}

static void creates_all_entries(GtkWidget *grid, GtkWidget **seq1Entry, GtkWidget **seq2Entry, GtkWidget **seq3Entry, GtkWidget **seq4Entry, GtkWidget **seq5Entry)
{
    *seq1Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq1Entry), "Sequencia 1");
    g_signal_connect(*seq1Entry, "changed", G_CALLBACK(on_sequencia_changed), "1");
    gtk_grid_attach(GTK_GRID(grid), *seq1Entry, 0, 0, 1, 1);

    *seq2Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq2Entry), "Sequencia 2");
    g_signal_connect(*seq2Entry, "changed", G_CALLBACK(on_sequencia_changed), "2");
    gtk_grid_attach(GTK_GRID(grid), *seq2Entry, 0, 1, 1, 1);

    *seq3Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq3Entry), "Sequencia 3");
    g_signal_connect(*seq3Entry, "changed", G_CALLBACK(on_sequencia_changed), "3");
    gtk_grid_attach(GTK_GRID(grid), *seq3Entry, 0, 2, 1, 1);

    *seq4Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq4Entry), "Sequencia 4");
    g_signal_connect(*seq4Entry, "changed", G_CALLBACK(on_sequencia_changed), "4");
    gtk_grid_attach(GTK_GRID(grid), *seq4Entry, 0, 3, 1, 1);

    *seq5Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(*seq5Entry), "Sequencia 5");
    g_signal_connect(*seq5Entry, "changed", G_CALLBACK(on_sequencia_changed), "5");
    gtk_grid_attach(GTK_GRID(grid), *seq5Entry, 0, 4, 1, 1);
}

// creates_all_checkboxes(grid, &check1, &check2, &check3, &check4, &check5);
static void creates_all_checkboxes(GtkWidget *grid, GtkWidget **check1, GtkWidget **check2, GtkWidget **check3, GtkWidget **check4, GtkWidget **check5)
{
    *check1 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check1, 1, 0, 1, 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(*check1), TRUE);
    g_signal_connect(*check1, "toggled", G_CALLBACK(on_check_toggled), "1");
    gtk_widget_set_sensitive(*check1, FALSE);

    *check2 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check2, 1, 1, 1, 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(*check2), TRUE);
    g_signal_connect(*check2, "toggled", G_CALLBACK(on_check_toggled), "2");
    gtk_widget_set_sensitive(*check2, FALSE);

    *check3 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check3, 1, 2, 1, 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(*check3), TRUE);
    g_signal_connect(*check3, "toggled", G_CALLBACK(on_check_toggled), "3");

    *check4 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check4, 1, 3, 1, 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(*check4), TRUE);
    g_signal_connect(*check4, "toggled", G_CALLBACK(on_check_toggled), "4");

    *check5 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check5, 1, 4, 1, 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(*check5), TRUE);
    g_signal_connect(*check5, "toggled", G_CALLBACK(on_check_toggled), "5");
}

static void
activate(GtkApplication *app,
         gpointer user_data)
{
    GtkWidget *grid;
    GtkWidget *button;

    GtkWidget *seq1Entry, *seq2Entry, *seq3Entry, *seq4Entry, *seq5Entry;

    GtkWidget *check1, *check2, *check3, *check4, *check5;

    /* create a new window, and set its title */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Alinhamento Múltiplo de Sequências");
    gtk_container_set_border_width(GTK_CONTAINER(window), 30);

    /* Here we construct the container that is going pack our buttons */
    grid = gtk_grid_new();

    /* Pack the container in the window */
    gtk_container_add(GTK_CONTAINER(window), grid);

    creates_all_entries(grid, &seq1Entry, &seq2Entry, &seq3Entry, &seq4Entry, &seq5Entry);
    creates_all_checkboxes(grid, &check1, &check2, &check3, &check4, &check5);

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