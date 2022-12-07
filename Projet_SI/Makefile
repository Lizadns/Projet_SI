CC=gcc
CFLAGS=-Wall -Werror -g
LIBS=-lcunit -lpthread -lrt
INCLUDE_HEADERS_DIRECTORY=-Iheaders

all: 
	make Philosophe
	make PC
	make EL
	make tas
	make tatas
	make EL2
	make Philosophe2
	make PC2

Philosophe: Partie1/Philosophe.c     # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS) 

PC: Partie1/ProducteurConsommateur.c     # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS) 

EL: Partie1/EcrivainLecteur.c     # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS) 

tas: Partie2/test_and_set.c     # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS) 

tatas : Partie2/main-test-and-test-and-set.c Partie2/test-and-test-and-set.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS)

EL2: Partie2/EcrivainLecteur2.c Partie2/test-and-test-and-set.o Partie2/semaphore.o # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS)

Philosophe2: Partie2/Philosophe2.c Partie2/test-and-test-and-set.o Partie2/semaphore.o  # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS)

PC2: Partie2/ProducteurConsommateur2.c Partie2/test-and-test-and-set.o Partie2/semaphore.o  # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) -o $@ $^ $(LIBS)

clean : 
	rm -f Philosophe
	rm -f PC
	rm -f EL
	rm -f tas
	rm -f tatas
	rm -f EL2
	rm -f PC2
	rm -f Philosophe2
	rm -f Partie2/*.o

cleancsv :
	rm -f mesuresPhilosophe.csv
	rm -f mesuresProd.csv
	rm -f mesuresEL.csv
	rm -f mesuresTas.csv
	rm -f mesuresTatas.csv
	rm -f mesuresEL2.csv
	rm -f mesuresPC2.csv
	rm -f mesuresPhilosophe2.csv
	