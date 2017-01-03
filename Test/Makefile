IDIR = ../Include
ODIR = ../Objects

CFLAGS = -I$(IDIR)

HEADERS = \
	$(IDIR)/object.h \
	$(IDIR)/intobject.h \
	$(IDIR)/consobject.h \
	$(IDIR)/boolobject.h \
	$(IDIR)/nilobject.h \
	$(IDIR)/floatobject.h

OBJECTS = \
	$(ODIR)/object.o \
	$(ODIR)/intobject.o \
	$(ODIR)/consobject.o \
	$(ODIR)/boolobject.o \
	$(ODIR)/nilobject.o \
	$(IDIR)/floatobject.o 


all: $(OBJECTS) test.c $(HEADERS)
	gcc $(OBJECTS) test.c -o test.o $(CFLAGS)


$(ODIR)/object.o: $(ODIR)/object.c $(HEADERS)
	gcc -c $(ODIR)/object.c -o $(ODIR)/object.o $(CFLAGS)

$(ODIR)/intobject.o: $(ODIR)/intobject.c $(HEADERS)
	gcc -c $(ODIR)/intobject.c -o $(ODIR)/intobject.o $(CFLAGS)

$(ODIR)/consobject.o: $(ODIR)/consobject.c $(HEADERS)
	gcc -c $(ODIR)/consobject.c -o $(ODIR)/consobject.o $(CFLAGS)

$(ODIR)/boolobject.o: $(ODIR)/boolobject.c $(HEADERS)
	gcc -c $(ODIR)/boolobject.c -o $(ODIR)/boolobject.o $(CFLAGS)

$(ODIR)/nilobject.o: $(ODIR)/nilobject.c $(HEADERS)
	gcc -c $(ODIR)/nilobject.c -o $(ODIR)/nilobject.o $(CFLAGS)
$(ODIR)/floatobject.o:$(ODIR)/floatobject.c $(HEADERS)
    gcc -c $(ODIR)/floatobject.c -o $(ODIR)/floatobject.o $(CFLAGS)

clean:
	rm $(OBJECTS) test.o
