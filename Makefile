# Устанавливаем компилятор
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Исходные файлы
SRC = big_decimal.cpp test.cpp
OBJ = big_decimal.o test.o
OUT = test_program

# Основная цель - сборка программы
all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT)

# Компиляция исходных файлов в объектные файлы
big_decimal.o: big_decimal.cpp
	$(CXX) $(CXXFLAGS) -c big_decimal.cpp

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

# Запуск тестов
test: $(OUT)
	./$(OUT)

# Очистка объектов и исполнимого файла
clean:
	rm -f $(OBJ) $(OUT)
