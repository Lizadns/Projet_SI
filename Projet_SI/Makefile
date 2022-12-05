CC=gcc
CFLAGS=-Wall -Werror -g
LIBS=-lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY=-Iheaders

fec: Partie1/Philosophe.c     # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS) -pthread

PC: Partie1/ProducteurConsommateur.c     # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS) -pthread -lrt

EL: Partie1/EcrivainLecteur.c     # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS) -pthread -lrt

tas: Partie2/test_and_set.c     # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS) -pthread

tatas : Partie2/test-and-test-and-set.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS) -pthread


EL2: Partie2/EcrivainLecteur2.c  # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS) -pthread -lrt

clean : 
	rm -f fec
	rm -f PC
	rm -f EL
	rm -f tas
	rm -f tatas
	rm -f EL2

cleancsv :
	rm -f mesuresPhilosophe.csv
	rm -f mesuresProd.csv
	rm -f mesuresEL.csv

cleantest : 
	rm -f mesuresTestAndSet.csv
	rm -f mesuresTestAndTestAndSet.csv
	rm -f mesuresEL2.csv