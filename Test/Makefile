IDIR = ../Include
ODIR = ../Objects

CFLAGS = -I$(IDIR)

HEADERS = \
	$(IDIR)/object.h \
	$(IDIR)/intobject.h \
	$(IDIR)/consobject.h \
	$(IDIR)/boolobject.h \
	$(IDIR)/nilobject.h \
	$(IDIR)/floatobject.h \
	$(IDIR)/symbolobject.h \
	$(IDIR)/list.h \
	$(IDIR)/environment.h \
	$(IDIR)/stringobject.h \
	$(IDIR)/types.h \
	$(IDIR)/primprocobject.h \
	$(IDIR)/closureobject.h \
	$(IDIR)/eval_apply.h \
	$(IDIR)/lexer.h \
	$(IDIR)/token.h \
	$(IDIR)/parser.h \
	$(IDIR)/interpret.h

OBJECTS = \
	$(ODIR)/object.o \
	$(ODIR)/intobject.o \
	$(ODIR)/consobject.o \
	$(ODIR)/boolobject.o \
	$(ODIR)/nilobject.o \
	$(ODIR)/floatobject.o \
	$(ODIR)/symbolobject.o \
	$(ODIR)/list.o \
	$(ODIR)/environment.o \
	$(ODIR)/stringobject.o \
	$(ODIR)/types.o \
	$(ODIR)/primprocobject.o \
	$(ODIR)/closureobject.o \
	$(ODIR)/eval_apply.o \
	$(ODIR)/lexer.o \
	$(ODIR)/token.o \
	$(ODIR)/parser.o \
	$(ODIR)/interpret.o


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

$(ODIR)/floatobject.o: $(ODIR)/floatobject.c $(HEADERS)
	gcc -c $(ODIR)/floatobject.c -o $(ODIR)/floatobject.o $(CFLAGS)

$(ODIR)/symbolobject.o: $(ODIR)/symbolobject.c $(HEADERS)
	gcc -c $(ODIR)/symbolobject.c -o $(ODIR)/symbolobject.o $(CFLAGS)

$(ODIR)/list.o: $(ODIR)/list.c $(HEADERS)
	gcc -c $(ODIR)/list.c -o $(ODIR)/list.o $(CFLAGS)

$(ODIR)/environment.o: $(ODIR)/environment.c $(HEADERS)
	gcc -c $(ODIR)/environment.c -o $(ODIR)/environment.o $(CFLAGS)

$(ODIR)/stringobject.o: $(ODIR)/stringobject.c $(HEADERS)
	gcc -c $(ODIR)/stringobject.c -o $(ODIR)/stringobject.o $(CFLAGS)

$(ODIR)/types.o: $(ODIR)/types.c $(HEADERS)
	gcc -c $(ODIR)/types.c -o $(ODIR)/types.o $(CFLAGS)

$(ODIR)/primprocobject.o: $(ODIR)/primprocobject.c $(HEADERS)
	gcc -c $(ODIR)/primprocobject.c -o $(ODIR)/primprocobject.o $(CFLAGS)

$(ODIR)/closrueobject.o: $(ODIR)/closrueobject.c $(HEADERS)
	gcc -c $(ODIR)/closrueobject.c -o $(ODIR)/closrueobject.o $(CFLAGS)

$(ODIR)/eval_apply.o: $(ODIR)/eval_apply.c $(HEADERS)
	gcc -c $(ODIR)/eval_apply.c -o $(ODIR)/eval_apply.o $(CFLAGS)

$(ODIR)/lexer.o: $(ODIR)/lexer.c $(HEADERS)
	gcc -c $(ODIR)/lexer.c -o $(ODIR)/lexer.o $(CFLAGS)

$(ODIR)/token.o: $(ODIR)/token.c $(HEADERS)
	gcc -c $(ODIR)/token.c -o $(ODIR)/token.o $(CFLAGS)

$(ODIR)/parser.o: $(ODIR)/parser.c $(HEADERS)
	gcc -c $(ODIR)/parser.c -o $(ODIR)/parser.o $(CFLAGS)

$(ODIR)/interpret.o: $(ODIR)/interpret.c $(HEADERS)
	gcc -c $(ODIR)/interpret.c -o $(ODIR)/interpret.o $(CFLAGS)

clean:
	rm $(OBJECTS) test.o
