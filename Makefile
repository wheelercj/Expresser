OBJS = Calc/Main.cpp Calc/Calc.cpp Calc/Vars.cpp

CC = g++

OBJ_NAME = Main

all :
	$(CC) $(OBJS) -std=c++11 -o $(OBJ_NAME)
	
