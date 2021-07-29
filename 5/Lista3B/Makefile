SRC = src/
HEAD = headers/
LIB = lib/
BIN = bin/
FLAGS = -c -Wall -pedantic -std=c99
FLAGS2 = -c -Wall -std=c99 -pedantic -fPIC

all: $(LIB)libmoja.so

$(LIB)libmoja.so: DaddL.c DaddW.c DconsW.c DdaInt.c DdelL.c DdelW.c DeqStr.c DinvL.c DinvW.c DpurLiW.c Dqualitas.c DviaWW.c DvidL.c DvidW.c DvotW.c STRUCT.c
















all: GRAF

static: main.o $(LIB)libSt.a
	gcc -o $(BIN)GrafSt main.o $(LIB)libSt.a

shared: $(LIB)libDyn.so
	gcc -o $(BIN)GrafDyn $(SRC)main.c -L. -lmoja1
	cp libDyn.so $(LIB)libDyn.so
	rm libDyn.so

$(LIB)libDyn.so: DaddL.o DaddW.o DconsW.o DdaInt.o DdelL.o DdelW.o DeqStr.o DinvL.o DinvW.o DpurLiW.o Dqualitas.o DviaWW.o DvidL.o DvidW.o DvotW.o STRUCT.o
	gcc -shared -o $(LIB)libDyn.so DaddL.o DaddW.o DconsW.o DdaInt.o DdelL.o DdelW.o DeqStr.o DinvL.o DinvW.o DpurLiW.o Dqualitas.o DviaWW.o DvidL.o DvidW.o DvotW.o STRUCT.o

$(LIB)libSt.a: DaddL.o DaddW.o DconsW.o DdaInt.o DdelL.o DdelW.o DeqStr.o DinvL.o DinvW.o DpurLiW.o Dqualitas.o DviaWW.o DvidL.o DvidW.o DvotW.o STRUCT.o
	ar -r $(LIB)libSt.a DaddL.o DaddW.o DconsW.o DdaInt.o DdelL.o DdelW.o DeqStr.o DinvL.o DinvW.o DpurLiW.o Dqualitas.o DviaWW.o DvidL.o DvidW.o DvotW.o STRUCT.o
 
main.o: $(SRC)main.c $(HEAD)STRUCT.h $(HEAD)DaddL.h $(HEAD)DaddW.h $(HEAD)DconsW.h $(HEAD)DdaInt.h $(HEAD)DdelL.h $(HEAD)DdelW.h $(HEAD)DeqStr.h $(HEAD)DinvL.h $(HEAD)DinvW.h $(HEAD)DpurLiW.h $(HEAD)Dqualitas.h $(HEAD)DviaWW.h $(HEAD)DvidL.h $(HEAD)DvidW.h $(HEAD)DvotW.h
	gcc $(FLAGS) $(SRC)main.c

DaddL.o: $(SRC)DaddL.c $(HEAD)DeqStr.h $(HEAD)STRUCT.h $(HEAD)DinvL.h
	gcc -c -Wall-pedantic -std=c99 $(SRC)DaddL.c

DaddW.o: $(SRC)DaddW.c $(HEAD)DinvW.h $(HEAD)STRUCT.h
	gcc -c -Wall-pedantic -std=c99 $(SRC)DaddW.c

DconsW.o: $(SRC)DconsW.c $(HEAD)DinvW.h $(HEAD)DeqStr.h $(HEAD)STRUCT.h
	gcc -c -Wall-pedantic -std=c99 $(SRC)DconsW.c

DdaInt.o: $(SRC)DdaInt.c
	gcc -c -Wall-pedantic -std=c99 $(SRC)DdaInt.c

DdelL.o: $(SRC)DdelL.c $(HEAD)DeqStr.h $(HEAD)STRUCT.h
	gcc $(FLAGS) $(SRC)DdelL.c

DdelW.o: $(SRC)DdelW.c $(HEAD)DdelL.h $(HEAD)DeqStr.h $(HEAD)STRUCT.h
	gcc $(FLAGS) $(SRC)DdelW.c

DeqStr.o: $(SRC)DeqStr.c
	gcc $(FLAGS) $(SRC)DeqStr.c

DinvL.o: $(SRC)DinvL.c $(HEAD)DeqStr.h $(HEAD)STRUCT.h
	gcc $(FLAGS) $(SRC)DinvL.c

DinvW.o: $(SRC)DinvW.c $(HEAD)DeqStr.h $(HEAD)STRUCT.h
	gcc $(FLAGS) $(SRC)DinvW.c

DpurLiW.o: $(SRC)DpurLiW.c $(HEAD)STRUCT.h
	gcc $(FLAGS) $(SRC)DpurLiW.c

Dqualitas.o: $(SRC)Dqualitas.c
	gcc $(FLAGS) $(SRC)Dqualitas.c

DviaWW.o: $(SRC)DviaWW.c $(HEAD)DeqStr.h $(HEAD)DinvW.h $(HEAD)STRUCT.h
	gcc $(FLAGS) $(SRC)DviaWW.c

DvidL.o: $(SRC)DvidL.c $(HEAD)STRUCT.h
	gcc $(FLAGS) $(SRC)DvidL.c

DvidW.o: $(SRC)DvidW.c $(HEAD)DvidL.h $(HEAD)STRUCT.h
	gcc $(FLAGS) $(SRC)DvidW.c

DvotW.o: $(SRC)DvotW.c $(HEAD)STRUCT.h $(HEAD)DeqStr.h $(HEAD)DinvW.h
	gcc $(FLAGS) $(SRC)DvotW.c

STRUCT.o: $(SRC)STRUCT.c $(HEAD)STRUCT.h
	gcc $(FLAGS) $(SRC)STRUCT.c





clean:
	rm -f *.o

