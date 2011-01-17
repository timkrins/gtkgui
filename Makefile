PROGRAM = gtktest

SOURCES = $(PROGRAM).c
CC = $(ARCH)gcc

.PHONY: all program clean

all:
	windres $(PROGRAM).rc $(PROGRAM).o
	$(CC) $(SOURCES) $(PROGRAM).o -o $(PROGRAM).exe -mwindows -mms-bitfields -IC:/MinGW/include/gtk-2.0 -IC:/MinGW/lib/gtk-2.0/include -IC:/MinGW/include/atk-1.0 -IC:/MinGW/include/cairo -IC:/MinGW/include/gdk-pixbuf-2.0 -IC:/MinGW/include/pango-1.0 -IC:/MinGW/include/glib-2.0 -IC:/MinGW/lib/glib-2.0/include -IC:/MinGW/include/pixman-1 -IC:/MinGW/include -IC:/MinGW/include/freetype2 -IC:/MinGW/include/libpng14  -LC:/MinGW/lib -lgtk-win32-2.0 -lgdk-win32-2.0 -latk-1.0 -lgio-2.0 -lpangowin32-1.0 -lgdi32 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lpango-1.0 -lcairo -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lglib-2.0 -lintl
	size $(PROGRAM).exe

clean:
	rm -rf $(PROGRAM).exe