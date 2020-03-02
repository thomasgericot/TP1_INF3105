# Makefile pour TP1.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).
#
# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
OPTIONS = -g -O0 -Wall
#OPTIONS = -O2 -Wall


all : tp1

tp1 : tp1.cpp foyer.o quartier.o
	g++ ${OPTIONS} -o tp1 tp1.cpp foyer.o quartier.o
	
foyer.o : foyer.cpp foyer.h
	g++ ${OPTIONS} -c foyer.cpp

quartier.o : quartier.cpp quartier.h foyer.h
	g++ ${OPTIONS} -c quartier.cpp

clean:
	rm -rf tp1 *~ *.o tp1.dSYM

test: tp1
	./tp1 t2.txt
