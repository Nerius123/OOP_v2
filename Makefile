# Kompiliatorius
CXX = g++
CXXFLAGS = -Wall -Wextra -g

# Pagrindinis vykdomasis failas
TARGET = v0_1.exe

# Objektiniai failai
OBJS = v0_1.o functions.o

# Pagrindinė taisyklė – kompiliuoti visą projektą (su išvalymu)
all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# .cpp → .o kompiliavimas
v0_1.o: v0_1.cpp functions.h
	$(CXX) $(CXXFLAGS) -c v0_1.cpp -o v0_1.o

functions.o: functions.cpp functions.h my_library.h
	$(CXX) $(CXXFLAGS) -c functions.cpp -o functions.o

# Komanda „make run“: išvalo, kompiliuoja ir paleidžia
run: all
	./$(TARGET)

# Komanda „make clean“ ištrina objektinius failus
clean:
	@if exist $(TARGET) del $(TARGET)
	@if exist v0_1.o del v0_1.o
	@if exist functions.o del functions.o

.PHONY: all clean run
