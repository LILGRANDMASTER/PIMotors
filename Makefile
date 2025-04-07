# Компилятор и флаги
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Iinclude

# Исходные файлы
SRC_DIR := src
SRCS := $(SRC_DIR)/motor_interface.cpp
OBJS := $(SRCS:.cpp=.o)
TEST_SRC := $(SRC_DIR)/test_motor.cpp
TEST_OBJ := $(TEST_SRC:.cpp=.o)
TEST_TARGET := test_motor

# Правила сборки
all: lib test

lib: $(OBJS)
	ar rcs libmotor_interface.a $^

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lwiringPi

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TEST_OBJ) libmotor_interface.a $(TEST_TARGET)

.PHONY: all lib test clean