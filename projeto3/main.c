#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include <gtk/gtk.h> 

static char seq1[123];
static char seq2[123];
static char seq3[123];
static char seq4[123];
static char seq5[123];
static char seq6[123];
static char seq7[123];
static char seq8[123];
static char seq9[123];
static char seq10[123];

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
GtkWidget *scrolled_window;
GtkWidget *headerbar;

void load_css()
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *css_file = "style.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(css_file), &error);
    g_object_unref(provider);
}

// Function to open a dialog box with a message
void quick_message(GtkWindow *parent, gchar *type, gchar *message)
{
    GtkWidget *dialog, *label, *content_area;
    GtkDialogFlags flags;

    // Create the widgets
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons(type, parent, flags, "OK", GTK_RESPONSE_NONE, NULL);
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

static void info_button_clicked(GtkWidget *widget, gpointer data)
{
    quick_message(GTK_WINDOW(window), "Informações", "SCORE:\n(α * ∑α) + (β * ∑β) + (δ * ∑δ)\n\nα = 2 // (A + A)\nβ = -1 // (A + T)\nδ = 1 // (A + -) // (- + -)\n\nPesos:\npGapsJuntos = nº de gaps * ilhas de gaps - 1)\npGapsFinais = (∑ posição dos gaps) + (nº de gaps)\n\nFÓRMULA = score + pGapsFinais - pGapsJuntos");
}

static void disable_entry(GtkWidget *widget, gpointer data)
{
    gtk_widget_set_sensitive(GTK_WIDGET(data), !gtk_widget_get_sensitive(GTK_WIDGET(data)));
    gtk_entry_set_text(GTK_ENTRY(data), "");
}

static int valida_sequencias()
{
    if (active1) {
        if (!verificaCharValidos(seq1) || (strlen(seq1) > 100) || strlen(seq1) == 0) {
            quick_message(GTK_WINDOW(window),  "Atenção!", "Sequencia 1 invalida");
            return 0;
        }
        if (strlen(seq1) > max_string_size) max_string_size = strlen(seq1);
    }
    if (active2) {
        if (!verificaCharValidos(seq2) || (strlen(seq2) > 100) || strlen(seq2) == 0) {
            quick_message(GTK_WINDOW(window),  "Atenção!", "Sequencia 2 invalida");
            return 0;
        }
        if (strlen(seq2) > max_string_size) max_string_size = strlen(seq2);
    }
    if (active3) {
        if (!verificaCharValidos(seq3) || (strlen(seq3) > 100) || strlen(seq3) == 0) {
            quick_message(GTK_WINDOW(window),  "Atenção!", "Sequencia 3 invalida");
            return 0;
        }
        if (strlen(seq3) > max_string_size) max_string_size = strlen(seq3);
    }
    if (active4) {
        if (!verificaCharValidos(seq4) || (strlen(seq4) > 100) || strlen(seq4) == 0) {
            quick_message(GTK_WINDOW(window),  "Atenção!", "Sequencia 4 invalida");
            return 0;
        }
        if (strlen(seq4) > max_string_size) max_string_size = strlen(seq4);
    }
    if (active5) {
        if (!verificaCharValidos(seq5) || (strlen(seq5) > 100) || strlen(seq5) == 0) {
            quick_message(GTK_WINDOW(window),  "Atenção!", "Sequencia 5 invalida");
            return 0;
        }
        if (strlen(seq5) > max_string_size) max_string_size = strlen(seq5);
    }

    if (active6){
        if (!verificaCharValidos(seq6) || (strlen(seq6) > 100) || strlen(seq6) == 0) {
            quick_message(GTK_WINDOW(window),  "Atenção!", "Sequencia 6 invalida");
            return 0;
        }
        if (strlen(seq6) > max_string_size) max_string_size = strlen(seq6);
    }

    if (active7){
        if (!verificaCharValidos(seq7) || (strlen(seq7) > 100) || strlen(seq7) == 0) {
            quick_message(GTK_WINDOW(window),  "Atenção!", "Sequencia 7 invalida");
            return 0;
        }
        if (strlen(seq7) > max_string_size) max_string_size = strlen(seq7);
    }

    if (active8){
        if (!verificaCharValidos(seq8) || (strlen(seq8) > 100) || strlen(seq8) == 0) {
            quick_message(GTK_WINDOW(window),  "Atenção!", "Sequencia 8 invalida");
            return 0;
        }
        if (strlen(seq8) > max_string_size) max_string_size = strlen(seq8);
    }

    if (active9){
        if (!verificaCharValidos(seq9) || (strlen(seq9) > 100) || strlen(seq9) == 0) {
            quick_message(GTK_WINDOW(window),  "Atenção!", "Sequencia 9 invalida");
            return 0;
        }
        if (strlen(seq9) > max_string_size) max_string_size = strlen(seq9);
    }

    if (active10){
        if (!verificaCharValidos(seq10) || (strlen(seq10) > 100) || strlen(seq10) == 0) {
            quick_message(GTK_WINDOW(window),  "Atenção!", "Sequencia 10 invalida");
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

    char sequencias[sequencias_ativas][123];

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

    // remove all widgets in grid
    gtk_container_foreach(GTK_CONTAINER(data), (GtkCallback)gtk_widget_destroy, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);

    g_print("\nVocê digitou %d sequencias com tamanho máximo de %d caracteres\n", sequencias_ativas, max_string_size);

    imprimirSequencia(sequencias, sequencias_ativas);

    g_print("\nAlinhamento com gaps no final:\n\n");
    preencheGapFinal(sequencias, sequencias_ativas, &max_string_size);

    imprimirSequencia(sequencias, sequencias_ativas);

    alinhaSequencias(sequencias, max_string_size, sequencias_ativas);

    g_print("\nMelhor alinhamento:\n\n");

    imprimirSequencia(sequencias, sequencias_ativas);

    printf("\n");

    int info[6];
    int *score;
    score = calcular_score(sequencias, sequencias_ativas, max_string_size, info);
    char score_signed[10];

    if (score[0] >= 0) {
        sprintf(score_signed, "+%d", score[0]);
    } else {
        sprintf(score_signed, "%d", score[0]);
    }

    char score_string[164];
    sprintf(score_string, "SCORE:\n(α * %d) + (β * %d) + (δ * %d) + %d - %d = %s", score[1], score[2], score[3], score[4], score[5], score_signed);

    GtkWidget *label = gtk_label_new(score_string);
    gtk_widget_set_name(label, "score");
    gtk_grid_attach(GTK_GRID(data), label, 0, 0, 1, 1);
    gtk_widget_set_halign(label, GTK_ALIGN_START);

    // create <small>
    GtkWidget *small = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(small), "Para mais informações, clique no botão acima!");
    gtk_widget_set_name(small, "small");
    gtk_grid_attach(GTK_GRID(data), small, 0, 1, 1, 1);
    gtk_widget_set_halign(small, GTK_ALIGN_START);

    int i;
    for (i = 0; i < sequencias_ativas; i++) {
        // container
        GtkWidget *container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

        // for each letter, create a label
        int j;
        for (j = 0; j < max_string_size; j++) {
            char lowercased[2];
            lowercased[0] = tolower(sequencias[i][j]);
            lowercased[1] = '\0';

            GtkWidget *label = gtk_label_new(NULL);
            GtkStyleContext *context;
            context = gtk_widget_get_style_context(label);
            gtk_style_context_add_class(context, "letter");

            gtk_widget_set_name(label, lowercased);
            gchar *letter = g_strdup_printf("%c", sequencias[i][j]);
            gtk_label_set_text(GTK_LABEL(label), letter);
            gtk_box_pack_start(GTK_BOX(container), label, FALSE, FALSE, 0);
        }

        gtk_widget_set_name(container, "container");
        gtk_grid_attach(GTK_GRID(data), container, 0, i+2, 1, 1);
    }
    gtk_grid_set_row_spacing(GTK_GRID(data), 0);
    gtk_widget_show_all(data);
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
    g_signal_connect(*seq1Entry, "changed", G_CALLBACK(on_sequencia_changed), "1");
    gtk_grid_attach(GTK_GRID(grid), *seq1Entry, 0, 2, 3, 1);

    *seq2Entry = gtk_entry_new();
    g_signal_connect(*seq2Entry, "changed", G_CALLBACK(on_sequencia_changed), "2");
    gtk_grid_attach(GTK_GRID(grid), *seq2Entry, 0, 3, 3, 1);

    *seq3Entry = gtk_entry_new();
    g_signal_connect(*seq3Entry, "changed", G_CALLBACK(on_sequencia_changed), "3");
    gtk_grid_attach(GTK_GRID(grid), *seq3Entry, 0, 4, 3, 1);
    gtk_widget_set_sensitive(*seq3Entry, FALSE);

    *seq4Entry = gtk_entry_new();
    g_signal_connect(*seq4Entry, "changed", G_CALLBACK(on_sequencia_changed), "4");
    gtk_grid_attach(GTK_GRID(grid), *seq4Entry, 0, 5, 3, 1);
    gtk_widget_set_sensitive(*seq4Entry, FALSE);

    *seq5Entry = gtk_entry_new();
    g_signal_connect(*seq5Entry, "changed", G_CALLBACK(on_sequencia_changed), "5");
    gtk_grid_attach(GTK_GRID(grid), *seq5Entry, 0, 6, 3, 1);
    gtk_widget_set_sensitive(*seq5Entry, FALSE);

    *seq6Entry = gtk_entry_new();
    g_signal_connect(*seq6Entry, "changed", G_CALLBACK(on_sequencia_changed), "6");
    gtk_grid_attach(GTK_GRID(grid), *seq6Entry, 0, 7, 3, 1);
    gtk_widget_set_sensitive(*seq6Entry, FALSE);

    *seq7Entry = gtk_entry_new();
    g_signal_connect(*seq7Entry, "changed", G_CALLBACK(on_sequencia_changed), "7");
    gtk_grid_attach(GTK_GRID(grid), *seq7Entry, 0, 8, 3, 1);
    gtk_widget_set_sensitive(*seq7Entry, FALSE);

    *seq8Entry = gtk_entry_new();
    g_signal_connect(*seq8Entry, "changed", G_CALLBACK(on_sequencia_changed), "8");
    gtk_grid_attach(GTK_GRID(grid), *seq8Entry, 0, 9, 3, 1);
    gtk_widget_set_sensitive(*seq8Entry, FALSE);

    *seq9Entry = gtk_entry_new();
    g_signal_connect(*seq9Entry, "changed", G_CALLBACK(on_sequencia_changed), "9");
    gtk_grid_attach(GTK_GRID(grid), *seq9Entry, 0, 10, 3, 1);
    gtk_widget_set_sensitive(*seq9Entry, FALSE);

    *seq10Entry = gtk_entry_new();
    g_signal_connect(*seq10Entry, "changed", G_CALLBACK(on_sequencia_changed), "10");
    gtk_grid_attach(GTK_GRID(grid), *seq10Entry, 0, 11, 3, 1);
    gtk_widget_set_sensitive(*seq10Entry, FALSE);
}

// creates_all_checkboxes(grid, &check1, &check2, &check3, &check4, &check5);
static void creates_all_checkboxes(GtkWidget *grid, GtkWidget **check1, GtkWidget **check2, GtkWidget **check3, GtkWidget **check4, GtkWidget **check5, GtkWidget **check6, GtkWidget **check7, GtkWidget **check8, GtkWidget **check9, GtkWidget **check10)
{
    *check1 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check1, 4, 2, 1, 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(*check1), TRUE);
    g_signal_connect(*check1, "toggled", G_CALLBACK(on_check_toggled), "1");
    gtk_widget_set_sensitive(*check1, FALSE);

    *check2 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check2, 4, 3, 1, 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(*check2), TRUE);
    g_signal_connect(*check2, "toggled", G_CALLBACK(on_check_toggled), "2");
    gtk_widget_set_sensitive(*check2, FALSE);

    *check3 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check3, 4, 4, 1, 1);
    g_signal_connect(*check3, "toggled", G_CALLBACK(on_check_toggled), "3");

    *check4 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check4, 4, 5, 1, 1);
    g_signal_connect(*check4, "toggled", G_CALLBACK(on_check_toggled), "4");

    *check5 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check5, 4, 6, 1, 1);
    g_signal_connect(*check5, "toggled", G_CALLBACK(on_check_toggled), "5");

    *check6 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check6, 4, 7, 1, 1);
    g_signal_connect(*check6, "toggled", G_CALLBACK(on_check_toggled), "6");

    *check7 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check7, 4, 8, 1, 1);
    g_signal_connect(*check7, "toggled", G_CALLBACK(on_check_toggled), "7");

    *check8 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check8, 4, 9, 1, 1);
    g_signal_connect(*check8, "toggled", G_CALLBACK(on_check_toggled), "8");

    *check9 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check9, 4, 10, 1, 1);
    g_signal_connect(*check9, "toggled", G_CALLBACK(on_check_toggled), "9");

    *check10 = gtk_check_button_new_with_label("Ativo");
    gtk_grid_attach(GTK_GRID(grid), *check10, 4, 11, 1, 1);
    g_signal_connect(*check10, "toggled", G_CALLBACK(on_check_toggled), "10");
}

static void
activate(GtkApplication *app,
         gpointer user_data)
{
    load_css();
    
    GtkWidget *grid;
    GtkWidget *button;

    GtkWidget *seq1Entry, *seq2Entry, *seq3Entry, *seq4Entry, *seq5Entry, *seq6Entry, *seq7Entry, *seq8Entry, *seq9Entry, *seq10Entry;

    GtkWidget *check1, *check2, *check3, *check4, *check5, *check6, *check7, *check8, *check9, *check10;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Alinhamento Múltiplo de Sequências");
    gtk_window_set_default_size(GTK_WINDOW(window), 1100, 510);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_NEVER);

    headerbar = gtk_header_bar_new();
    gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "Alinhamento de Sequências");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    gtk_header_bar_set_has_subtitle(GTK_HEADER_BAR(headerbar), FALSE);
    gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(headerbar), "close:menu");
    gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);

    GtkWidget *info_button = gtk_button_new_from_icon_name("dialog-information", GTK_ICON_SIZE_BUTTON);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), info_button);
    g_signal_connect(info_button, "clicked", G_CALLBACK(info_button_clicked), "1");

    grid = gtk_grid_new();

    gtk_container_add(GTK_CONTAINER(scrolled_window), grid);

    //title
    GtkWidget *title = gtk_label_new("Alinhamento Múltiplo de Sequências");
    gtk_grid_attach(GTK_GRID(grid), title, 0, 0, 11, 1);
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(title, GTK_ALIGN_CENTER);
    gtk_widget_set_name(title, "title");

    GtkWidget *space1 = gtk_label_new(" ");
    gtk_grid_attach(GTK_GRID(grid), space1, 0, 1, 1, 1);

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
    gtk_entry_set_width_chars(GTK_ENTRY(seq1Entry), 120);

    // space
    GtkWidget *space = gtk_label_new(" ");
    gtk_grid_attach(GTK_GRID(grid), space, 0, 12, 1, 1);

    button = gtk_button_new_with_label("Alinhar");
    g_signal_connect(button, "clicked", G_CALLBACK(alinha_sequencias), grid);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 13, 6, 2);

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