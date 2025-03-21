start: deque_main.o deque_functions.o
	g++ deque_main.o deque_functions.o -o deque_program.exe
	@if exist deque_main.o del deque_main.o
	@if exist deque_functions.o del deque_functions.o

deque_main.o: deque_main.cpp deque_functions.h ../my_library.h
	g++ -c deque_main.cpp -o deque_main.o

deque_functions.o: deque_functions.cpp deque_functions.h ../my_library.h
	g++ -c deque_functions.cpp -o deque_functions.o
