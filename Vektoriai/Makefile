start: v0_1.o functions.o
	g++ v0_1.o functions.o -o v0_1.exe
	@if exist v0_1.o del v0_1.o
	@if exist functions.o del functions.o

v0_1.o: v0_1.cpp functions.h ../my_library.h
	g++ -c v0_1.cpp -o v0_1.o

functions.o: functions.cpp functions.h ../my_library.h
	g++ -c functions.cpp -o functions.o
