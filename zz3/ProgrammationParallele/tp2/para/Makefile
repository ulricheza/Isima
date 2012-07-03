# Makefile pour les applications X

CC = mpicc
CFLAGS = -I/usr/include/X11
CPPFLAGS = -L/usr/lib/X11
LDLIBS = -lX11

SRC1 = newton011204.c complexe.c fonctions.c
OBJ1 = $(SRC1:.c=.o)

SRC2 = newton_pixmap04.c complexe.c fonctions.c
OBJ2 = $(SRC2:.c=.o)

newton_pixmap : $(OBJ2)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(OBJ2) $(LDLIBS)


newton : $(OBJ1)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(OBJ1) $(LDLIBS)

.c : 
	$(CC) -c $<

clean:	
	\rm  newton newton_pixmap *.o

