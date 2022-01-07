CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

# creates chess executable
chess: Chess.o CreatePiece.o Board.o main.o King.o Queen.o Rook.o Bishop.o Knight.o Pawn.o
	$(CC) -o chess Chess.o CreatePiece.o Board.o main.o King.o Queen.o Rook.o Bishop.o Knight.o Pawn.o

main.o: main.cpp Chess.h
	$(CC) $(CFLAGS) -c main.cpp


Chess.o: Chess.cpp Chess.h
	$(CC) $(CFLAGS) -c Chess.cpp

Board.o: Board.cpp Board.h
	$(CC) $(CFLAGS) -c Board.cpp

CreatePiece.o: CreatePiece.cpp CreatePiece.h King.h Queen.h Rook.h Bishop.h Knight.h Pawn.h Mystery.h Piece.h 
	$(CC) $(CFLAGS) -lm -c CreatePiece.cpp


King.o: King.h King.cpp
	$(CC) $(CFLAGS) -lm -c King.cpp

Queen.o: Queen.h Queen.cpp
	$(CC) $(CFLAGS) -lm -c Queen.cpp

Rook.o: Rook.h Rook.cpp
	$(CC) $(CFLAGS) -lm -c Rook.cpp

Bishop.o: Bishop.h Bishop.cpp
	$(CC) $(CFLAGS) -lm -c Bishop.cpp

Knight.o: Knight.h Knight.cpp
	$(CC) $(CFLAGS) -lm -c Knight.cpp

Pawn.o: Pawn.h Pawn.cpp
	$(CC) $(CFLAGS) -lm -c Pawn.cpp

Mystery.o: Mystery.h Mystery.cpp
	$(CC) $(CFLAGS) -lm -c Mystery.cpp

# 'make clean' will remove all intermediate & executable files
clean:
	rm -f *.o chess Board_Test

