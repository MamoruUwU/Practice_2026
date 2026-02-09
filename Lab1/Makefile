# ====== НАЛАШТУВАННЯ ======
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS  :=

# ====== ШЛЯХИ ======
SRC_DIR  := src
OBJ_DIR  := bin
BIN_DIR  := bin

TARGET   := $(BIN_DIR)/app.exe

# ====== ФАЙЛИ ======
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# ====== ПРАВИЛА ======
.PHONY: all clean run

all: $(TARGET)

# Лінкування
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Компіляція кожного cpp → obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск програми
run: all
	./$(TARGET)

# Очищення
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
