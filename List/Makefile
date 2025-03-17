start: list_main.o list_functions.o
	g++ list_main.o list_functions.o -o list_program.exe
	@if exist list_main.o del list_main.o
	@if exist list_functions.o del list_functions.o

list_main.o: list_main.cpp list_functions.h my_library.h
	g++ -c list_main.cpp -o list_main.o

list_functions.o: list_functions.cpp list_functions.h my_library.h
	g++ -c list_functions.cpp -o list_functions.o
