CC=g++ -std=c++17
FILES=main.cpp
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
OUT=calc-app
LIB_O=static-lib.o

install: clean
	$(CC) -c $(FILES) -o $(LIB_O)
	$(CC) $(LIB_O) -o $(OUT) $(LIBS)

clean:
	rm -rf $(OUT)
	rm -rf *.o
