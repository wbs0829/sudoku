OBJS = SudokuMaker.o SudokuSolver.o Sudoku.o SudokuBase.o Task.o Cell.o Main.o SudokuFrame.o WorkingPanel.o
CC = g++
DEBUG = 
INCLUDEDIRS = $(shell wx-config --cflags)
LIBS = $(shell wx-config --libs)
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Sudoku : $(OBJS)
	$(CC) $(LFLAGS) $(INCLUDEDIRS) $(OBJS) $(LIBS) -o Sudoku

Main.o : Main.cpp SudokuFrame.h
	$(CC) $(CFLAGS) Main.cpp  $(INCLUDEDIRS)
WorkingPanel.o : WorkingPanel.cpp WorkingPanel.h SudokuFrame.h
	$(CC) $(CFLAGS) WorkingPanel.cpp  $(INCLUDEDIRS)
SudokuFrame.o : SudokuFrame.cpp SudokuFrame.h WorkingPanel.h
	$(CC) $(CFLAGS) SudokuFrame.cpp  $(INCLUDEDIRS)

SudokuMaker.o : SudokuMaker.cpp SudokuMaker.h SudokuSolver.h Sudoku.h SudokuBase.h
	$(CC) $(CFLAGS) SudokuMaker.cpp 
SudokuSolver.o : SudokuSolver.cpp SudokuSolver.h Sudoku.h SudokuBase.h Task.h Cell.h
	$(CC) $(CFLAGS) SudokuSolver.cpp 
Sudoku.o : Sudoku.cpp Sudoku.h SudokuBase.h Cell.h
	$(CC) $(CFLAGS) Sudoku.cpp 
SudokuBase.o : SudokuBase.cpp SudokuBase.h
	$(CC) $(CFLAGS) SudokuBase.cpp 
Task.o : Task.cpp Task.h Cell.h
	$(CC) $(CFLAGS) Task.cpp 
Cell.o : Cell.cpp Cell.h
	$(CC) $(CFLAGS) Cell.cpp 
