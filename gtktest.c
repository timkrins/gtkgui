#include <gtk/gtk.h>

typedef struct _components {
    GtkWidget *window;
    GtkWidget *previous;
    GtkWidget *next;
    GtkWidget *graphNavigationPanel;
    GtkWidget *mainPanel;
    GtkWidget *drawingArea;
    GdkPixmap *pixMap;
} components;

static     components this;

static void next_handler( GtkWidget *widget,
                   gpointer   data )
{
    g_print ("next %s \n", (gchar *) data);
}

static void previous_handler( GtkWidget *widget,
                   gpointer   data )
{
    g_print ("previous %s \n", (gchar *) data);
}

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    return FALSE;
}

/* Another callback */
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}


static void createWindow() {
    this.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (this.window), 10);
    gtk_window_set_title (GTK_WINDOW (this.window), "Graph Window");

    g_signal_connect (G_OBJECT (this.window), "delete_event",
              G_CALLBACK (delete_event), NULL);

    g_signal_connect (G_OBJECT (this.window), "destroy",
                G_CALLBACK (destroy), NULL);

}


//static void createButtons() {
//    this.next = gtk_button_new_with_label ("Next");
//    this.previous = gtk_button_new_with_label ("Previous");

//    g_signal_connect (G_OBJECT (this.next), "clicked", G_CALLBACK (next_handler), NULL);
//    g_signal_connect (G_OBJECT (this.previous), "clicked", G_CALLBACK (previous_handler), NULL);

//}

static void layoutWidgets() {
    /* Create the graph navigation panel and add it to the window. */
    this.graphNavigationPanel = gtk_hbox_new (FALSE, 0);
    this.mainPanel = gtk_vbox_new(FALSE, 0);

    gtk_container_add  (GTK_CONTAINER (this.window), this.mainPanel);


    /* Add the buttons to the graph navigation panel. */
//    gtk_box_pack_start (GTK_BOX(this.graphNavigationPanel), this.previous, TRUE, TRUE, 0);
//    gtk_box_pack_start (GTK_BOX(this.graphNavigationPanel), this.next,     TRUE, TRUE, 0);


    /*Add the graph navigation panel to the main panel. */
    gtk_box_pack_start (GTK_BOX(this.mainPanel), this.graphNavigationPanel, TRUE, TRUE, 0);
    /* Add the draw-able area to the main panel. */
    gtk_box_pack_start (GTK_BOX(this.mainPanel), this.drawingArea, TRUE, TRUE, 0);



}

static void show() {
    gtk_widget_show (this.drawingArea);
    gtk_widget_show (this.mainPanel);
//    gtk_widget_show (this.next);
//    gtk_widget_show (this.previous);
    gtk_widget_show (this.graphNavigationPanel);
    gtk_widget_show (this.window);
}

/* Draw a rectangle on the screen */
static void
draw_brush (GtkWidget *widget, gdouble x, gdouble y)
{
  GdkRectangle update_rect;

  update_rect.x = x - 5;
  update_rect.y = y - 5;
  update_rect.width = 10;
  update_rect.height = 10;
  gdk_draw_rectangle (this.pixMap,
                widget->style->black_gc,
                TRUE,
              update_rect.x, update_rect.y,
              update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget,
                              update_rect.x, update_rect.y,
                      update_rect.width, update_rect.height);
}

/* Redraw the screen from the backing pixmap */
static gboolean
expose_event( GtkWidget *widget, GdkEventExpose *event )
{
  gdk_draw_drawable(widget->window,
            widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
            this.pixMap,
            event->area.x, event->area.y,
            event->area.x, event->area.y,
            event->area.width, event->area.height);

  return FALSE;
}
/* Create a new backing pixmap of the appropriate size */
static gboolean
configure_event( GtkWidget *widget, GdkEventConfigure *event )
{
  if (this.pixMap)
    g_object_unref(this.pixMap);

  this.pixMap = gdk_pixmap_new(widget->window,
              widget->allocation.width,
              widget->allocation.height,
              -1);

  gdk_draw_rectangle (this.pixMap,
              widget->style->white_gc,
              TRUE,
              0, 0,
              widget->allocation.width,
              widget->allocation.height);

  return TRUE;
}

static gboolean
button_press_event( GtkWidget *widget, GdkEventButton *event )
{
  if (event->button == 1 && this.pixMap != NULL)
      draw_brush (widget, (event->x)-50, (event->y)-50);

  return TRUE;
}

static gboolean
motion_notify_event( GtkWidget *widget, GdkEventMotion *event )
{
  int x, y;
  GdkModifierType state;

  if (event->is_hint)
    gdk_window_get_pointer (event->window, &x, &y, &state);
  else
    {
      x = event->x;
      y = event->y;
      state = event->state;
    }

  if (state & GDK_BUTTON1_MASK && this.pixMap != NULL)
    draw_brush (widget, x+50, y+50);

  return TRUE;
}

static void createDrawingArea() {
    this.drawingArea = gtk_drawing_area_new();

    gtk_signal_connect (GTK_OBJECT (this.drawingArea), "expose_event",
                  (GtkSignalFunc) expose_event, NULL);
    gtk_signal_connect (GTK_OBJECT(this.drawingArea),"configure_event",
                  (GtkSignalFunc) configure_event, NULL);
    gtk_signal_connect (GTK_OBJECT (this.drawingArea), "motion_notify_event",
                  (GtkSignalFunc) motion_notify_event, NULL);
    gtk_signal_connect (GTK_OBJECT (this.drawingArea), "button_press_event",
                  (GtkSignalFunc) button_press_event, NULL);

    gtk_widget_set_events (this.drawingArea, GDK_EXPOSURE_MASK
                 | GDK_LEAVE_NOTIFY_MASK
                 | GDK_BUTTON_PRESS_MASK
                 | GDK_POINTER_MOTION_MASK
                 | GDK_POINTER_MOTION_HINT_MASK);

    gtk_widget_set_size_request(this.drawingArea, 800, 500);
}


int main( int argc,char *argv[])
{
    gtk_init (&argc, &argv);

    createWindow();
    createDrawingArea();
    layoutWidgets();
    show();

    gtk_main ();

    return 0;
}