CC = g++
FLAGS= -lglut -lGL -lGLU -lSOIL
OUTPUT= main
compilar:
		$(CC) -g *.cpp */*.cpp $(FLAGS) -o $(OUTPUT)

executar: compilar
	./$(OUTPUT)

limpar:
		rm *.o -f