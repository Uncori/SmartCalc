#include <cairo.h>
#include <gtk/gtk.h>
#include <locale.h>

#include "s21_calc.h"
#include "s21_parsing.h"

typedef struct backpack {
    GtkEntryBuffer *buffer;
    GtkApplication *app;
    GtkWidget *widget;
    GtkWidget *widget_x;
    GtkWidget *grid;
    GtkWidget *button;
} st_b;
typedef struct drow {
    GtkEntryBuffer *buffer;
    GtkApplication *app;
    GtkWidget *widget;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *buffer_x;
    GtkWidget *buffer_y;
    GtkWidget *buffer_str;
    double x;
    double y;
} st_drow;

static void quit_cb(GtkWindow *window) { gtk_window_close(window); }
static void delete_text(const GtkWidget *widget, gpointer data) {
    if (widget) {
    } else {
    }
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    unsigned len = gtk_entry_buffer_get_length(buffer);
    gtk_entry_buffer_delete_text(buffer, len - 1, 1);
}
static void add_func(const GtkWidget *widget, gpointer data) {
    if (widget) {
    } else {
    }
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    const char *str = gtk_button_get_label(GTK_BUTTON(widget));
    gtk_entry_buffer_insert_text(buffer, gtk_entry_buffer_get_length(buffer),
                                 str, -1);
}
static void add_bracket(const GtkWidget *widget, gpointer data) {
    if (widget) {
    } else {
    }
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    gtk_entry_buffer_insert_text(buffer, gtk_entry_buffer_get_length(buffer),
                                 "(", -1);
}
static void delete_all_text(const GtkWidget *widget, gpointer data) {
    if (widget) {
    } else {
    }
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    if (gtk_entry_buffer_get_length(buffer) > 0) {
        gtk_entry_buffer_emit_deleted_text(buffer, 0,
                                           gtk_entry_buffer_get_length(buffer));
    }
}
static void add_pi(const GtkWidget *widget, gpointer data) {
    if (widget) {
    } else {
    }
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    gtk_entry_buffer_insert_text(buffer, gtk_entry_buffer_get_length(buffer),
                                 "3.1415926", -1);
}
static void add_exp(const GtkWidget *widget, gpointer data) {
    if (widget) {
    } else {
    }
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    gtk_entry_buffer_insert_text(buffer, gtk_entry_buffer_get_length(buffer),
                                 "2.7182818", -1);
}
static void draw_func(const GtkDrawingArea *drawing_area, cairo_t *cr,
                      int width, int height, gpointer data) {
    if (drawing_area) {
    } else {
    }

    st_drow *stab = (st_drow *)data;

    cairo_set_source_rgb(cr, 0, 0, 0);     // color
    cairo_set_line_width(cr, 0.5);         // shirina
    cairo_move_to(cr, 0, height / 2);      // kuda postapit
    cairo_line_to(cr, width, height / 2);  // do kude
    cairo_move_to(cr, width / 2, 0);
    cairo_line_to(cr, width / 2, height);
    GtkEntryBuffer *buffer_str =
        gtk_entry_get_buffer(GTK_ENTRY(stab->buffer_str));
    char *str = (char *)gtk_entry_buffer_get_text(buffer_str);
    cairo_stroke(cr);  // risovat'

    // double step = stab->x / 10000;
    char *pars_x = (char *)calloc(MAX_LINE, sizeof(char));
    cairo_set_source_rgb(cr, 0, 0, 0.1);

    cairo_translate(cr, width / 2, height / 2);
    cairo_scale(cr, 3, 3);  // mashtab
    cairo_set_line_width(cr, 1);
    for (double i = -stab->x; i < stab->x; i += 0.1) {
        snprintf(pars_x, MAX_LINE, "%lf", i);
        double y = parsing(str, pars_x);
        if (y == y) {
            cairo_line_to(cr, i, -y);
        }
    }
    free(pars_x);

    cairo_stroke(cr);  // risovat'
}

static void open_window(const GtkWidget *widget, gpointer data) {
    if (widget) {
    } else {
    }
    st_drow *stab = (st_drow *)data;
    GtkWidget *window;
    GtkWidget *drawing_area;

    window = gtk_application_window_new(GTK_APPLICATION(stab->app));
    gtk_window_set_title(GTK_WINDOW(window), "Drawing Area");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_can_focus(window, FALSE);

    GtkEntryBuffer *buffer_x = gtk_entry_get_buffer(GTK_ENTRY(stab->buffer_x));
    char *x = (char *)gtk_entry_buffer_get_text(buffer_x);

    double i_x;
    sscanf(x, "%lf", &i_x);
    stab->x = i_x;

    GtkEntryBuffer *buffer_y = gtk_entry_get_buffer(GTK_ENTRY(stab->buffer_y));
    char *y = (char *)gtk_entry_buffer_get_text(buffer_y);

    double i_y;
    sscanf(y, "%lf", &i_y);
    stab->y = i_y;

    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 400, 400);
    gtk_window_set_child(GTK_WINDOW(window), drawing_area);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area),
                                   (GtkDrawingAreaDrawFunc)draw_func, stab,
                                   NULL);
    gtk_widget_show(window);
}
static void swap(const GtkWidget *widget, gpointer data) {
    if (widget) {
    } else {
    }
    st_b *stab = (st_b *)data;
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(stab->widget));
    char *calk = (char *)gtk_entry_buffer_get_text(buffer);

    GtkEntryBuffer *buffer_x = gtk_entry_get_buffer(GTK_ENTRY(stab->widget_x));

    char *x = (char *)gtk_entry_buffer_get_text(buffer_x);

    double result = parsing(calk, x);
    char *res = (char *)calloc(MAX_LINE, sizeof(char));
    snprintf(res, MAX_LINE, "%.7lf", result);
    gtk_entry_buffer_set_text(buffer, res, strlen(res));
    free(res);
}
static void open_window_x(const GtkWidget *widget, gpointer data) {
    if (widget) {
    } else {
    }
    st_drow *stab = (st_drow *)data;
    GtkWidget *okno;
    GtkEntryBuffer *buffer;
    GtkWidget *grid;
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *label;
    window = gtk_application_window_new(GTK_APPLICATION(stab->app));
    gtk_window_set_title(GTK_WINDOW(window), "domain/range");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    grid = gtk_grid_new();

    gtk_window_set_child(GTK_WINDOW(window), grid);

    label = gtk_label_new("  X  ");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

    label = gtk_label_new("  Y  ");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);

    buffer = gtk_entry_buffer_new("", -1);
    okno = gtk_entry_new_with_buffer(buffer);
    gtk_grid_attach(GTK_GRID(grid), okno, 1, 0, 2, 1);
    stab->buffer_x = okno;

    buffer = gtk_entry_buffer_new("", -1);
    okno = gtk_entry_new_with_buffer(buffer);
    gtk_grid_attach(GTK_GRID(grid), okno, 1, 1, 2, 1);
    stab->buffer_y = okno;

    button = gtk_button_new_with_label("enter");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 6, 3, 1);
    g_signal_connect(button, "clicked", G_CALLBACK(open_window), stab);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(quit_cb), window);

    gtk_widget_show(window);
}
static void find_x(const GtkWidget *widget, gpointer data) {
    if (widget) {
    } else {
    }
    st_b *stab = (st_b *)data;
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(stab->widget));
    unsigned len = gtk_entry_buffer_get_length(buffer);
    char *in_calk = (char *)gtk_entry_buffer_get_text(buffer);
    int flag = FAILURE;
    for (size_t i = 0; i < len && flag == FAILURE; ++i) {
        if (in_calk[i] == 'x') {
            flag = SUCCESS;
        }
    }
    if (flag == SUCCESS) {
        GtkEntryBuffer *v_okne;
        GtkWidget *okno;
        GtkWidget *grid;
        GtkWidget *window;
        GtkWidget *button;
        window = gtk_application_window_new(GTK_APPLICATION(stab->app));
        gtk_window_set_title(GTK_WINDOW(window), "Enter X");
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

        grid = gtk_grid_new();
        gtk_window_set_child(GTK_WINDOW(window), grid);

        v_okne = gtk_entry_buffer_new("", -1);
        okno = gtk_entry_new_with_buffer(v_okne);
        gtk_grid_attach(GTK_GRID(grid), okno, 0, 0, 1, 1);

        button = gtk_button_new_with_label("enter");
        gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);
        stab->widget_x = okno;

        g_signal_connect(button, "clicked", G_CALLBACK(swap), stab);
        g_signal_connect_swapped(button, "clicked", G_CALLBACK(quit_cb),
                                 window);
        gtk_widget_show(window);
    } else {
        char *calk = (char *)gtk_entry_buffer_get_text(buffer);
        double result = parsing(calk, "0");
        char *res = (char *)calloc(MAX_LINE, sizeof(char));
        snprintf(res, MAX_LINE, "%.7lf", result);
        gtk_entry_buffer_set_text(buffer, res, strlen(res));
        free(res);
    }
}
static void activate(GtkApplication *app, gpointer user_data) {
    if (user_data) {
    } else {
    }
    setlocale(LC_ALL, "C");
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *okno;
    GtkEntryBuffer *v_okne;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Mabobbi calculator");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_can_focus(window, FALSE);

    grid = gtk_grid_new();

    gtk_window_set_child(GTK_WINDOW(window), grid);

    v_okne = gtk_entry_buffer_new("", -1);
    okno = gtk_entry_new_with_buffer(v_okne);
    gtk_grid_attach(GTK_GRID(grid), okno, 0, 0, 8, 1);

    button = gtk_button_new_with_label("delete");
    g_signal_connect(button, "clicked", G_CALLBACK(delete_all_text), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);
    button = gtk_button_new_with_label("graph");
    static st_drow drow;
    drow.app = app;
    drow.widget = okno;
    drow.buffer = v_okne;
    drow.grid = grid;
    drow.button = button;
    drow.buffer_str = okno;
    g_signal_connect(button, "clicked", G_CALLBACK(open_window_x), &drow);
    // g_signal_connect(button, "clicked", G_CALLBACK(open_window), app);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 1, 1, 1);
    button = gtk_button_new_with_label("asin");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 1, 1);
    button = gtk_button_new_with_label("acos");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 3, 1, 1);
    button = gtk_button_new_with_label("atan");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 1, 1);
    button = gtk_button_new_with_label("pi");
    g_signal_connect(button, "clicked", G_CALLBACK(add_pi), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 5, 1, 1);

    button = gtk_button_new_with_label("sin");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 2, 1, 1);
    button = gtk_button_new_with_label("cos");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 3, 1, 1);
    button = gtk_button_new_with_label("tan");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 4, 1, 1);
    button = gtk_button_new_with_label("EXP");
    g_signal_connect(button, "clicked", G_CALLBACK(add_exp), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 5, 1, 1);

    button = gtk_button_new_with_label("x");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 1, 1, 1);
    button = gtk_button_new_with_label("ln");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 2, 1, 1);
    button = gtk_button_new_with_label("log");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 3, 1, 1);
    button = gtk_button_new_with_label("sqrt");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    g_signal_connect(button, "clicked", G_CALLBACK(add_bracket), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 4, 1, 1);
    button = gtk_button_new_with_label("^");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 5, 1, 1);

    button = gtk_button_new_with_label("(");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 1, 1, 1);
    button = gtk_button_new_with_label("7");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 2, 1, 1);
    button = gtk_button_new_with_label("4");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 3, 1, 1);
    button = gtk_button_new_with_label("1");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 4, 1, 1);
    button = gtk_button_new_with_label("0");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 5, 1, 1);

    button = gtk_button_new_with_label(")");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 5, 1, 1, 1);
    button = gtk_button_new_with_label("8");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 5, 2, 1, 1);
    button = gtk_button_new_with_label("5");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 5, 3, 1, 1);
    button = gtk_button_new_with_label("2");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 5, 4, 1, 1);
    button = gtk_button_new_with_label(".");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 5, 5, 1, 1);

    button = gtk_button_new_with_label("%");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 6, 1, 1, 1);
    button = gtk_button_new_with_label("9");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 6, 2, 1, 1);
    button = gtk_button_new_with_label("6");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 6, 3, 1, 1);
    button = gtk_button_new_with_label("3");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 6, 4, 1, 1);
    button = gtk_button_new_with_label("=");
    static st_b prov_x;
    prov_x.app = app;
    prov_x.widget = okno;
    prov_x.buffer = v_okne;
    prov_x.grid = grid;
    prov_x.button = button;
    g_signal_connect(button, "clicked", G_CALLBACK(find_x), &prov_x);
    // g_signal_connect(button, "clicked", G_CALLBACK(ok_lets_go), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 6, 5, 1, 1);

    button = gtk_button_new_with_label("AC");
    g_signal_connect(button, "clicked", G_CALLBACK(delete_text), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 7, 1, 1, 1);
    button = gtk_button_new_with_label("/");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 7, 2, 1, 1);
    button = gtk_button_new_with_label("*");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 7, 3, 1, 1);
    button = gtk_button_new_with_label("-");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 7, 4, 1, 1);
    button = gtk_button_new_with_label("+");
    g_signal_connect(button, "clicked", G_CALLBACK(add_func), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 7, 5, 1, 1);

    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
