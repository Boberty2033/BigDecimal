# Указываем компилятор
CXX = g++

# Флаги компилятора
CXXFLAGS = -std=c++17 -Wall

# Исходные файлы
SRC = big_decimal.cpp test.cpp

# Исполнимый файл
TARGET = test_program

# Цель по умолчанию: сборка проекта
all: $(TARGET)

# Правило для компиляции исходников в исполнимый файл
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Цель для запуска тестов
test: $(TARGET)
	./$(TARGET)

# Очистка: удаление исполнимого файла
clean:
	rm -f $(TARGET)
