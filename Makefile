# Kompiliatorius
CXX = g++
CXXFLAGS = -Wall -Wextra -g

# Pagrindinis vykdomasis failas
TARGET = v0_1.exe

# Objektiniai failai
OBJS = v0_1.o functions.o

# Pagrindinė taisyklė – kompiliuoti visą projektą
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# .cpp → .o kompiliavimas
v0_1.o: v0_1.cpp functions.h
	$(CXX) $(CXXFLAGS) -c v0_1.cpp

functions.o: functions.cpp functions.h my_library.h
	$(CXX) $(CXXFLAGS) -c functions.cpp

# Komanda „make run“ paleidžia programą
run: $(TARGET)
	./$(TARGET)

# Komanda „make clean“ ištrina sukurtus failus
clean:
	rm -f $(TARGET) $(OBJS)
