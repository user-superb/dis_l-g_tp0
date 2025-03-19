CC:= gcc

SRC_DIR:= src
OBJ_DIR:= obj

INCLUDE_DIR:= -Iinclude

SRC:= $(wildcard $(SRC_DIR)/*.c)
OBJ:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC))

TARGET:= program.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -fno-common $(OBJ) -o $(TARGET) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(INCLUDE_DIR)


