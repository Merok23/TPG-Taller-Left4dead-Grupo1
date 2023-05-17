#Makefile hecho con ayuda de chatGPT
CC = g++
CFLAGS = -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L

COMMON_DIR = common
CLIENT_DIR = client
SERVER_DIR = server
TARGET_DIR = target

COMMON_SRCS = $(wildcard $(COMMON_DIR)/*.cpp)
CLIENT_SRCS = $(filter-out $(CLIENT_DIR)/Qt/%.cpp $(CLIENT_DIR)/Qt/%.pro $(CLIENT_DIR)/Qt/%.ui $(CLIENT_DIR)/Qt/%.h, $(wildcard $(CLIENT_DIR)/*.cpp))
SERVER_SRCS = $(wildcard $(SERVER_DIR)/*.cpp)

COMMON_OBJS = $(patsubst %.cpp, %.o, $(COMMON_SRCS))
CLIENT_OBJS = $(patsubst %.cpp, %.o, $(CLIENT_SRCS))
SERVER_OBJS = $(patsubst %.cpp, %.o, $(SERVER_SRCS))

CLIENT_TARGET = $(TARGET_DIR)/client_executable
SERVER_TARGET = $(TARGET_DIR)/server_executable

.PHONY: all clean

all: $(CLIENT_TARGET) $(SERVER_TARGET)

$(CLIENT_TARGET): $(COMMON_OBJS) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(SERVER_TARGET): $(COMMON_OBJS) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(COMMON_DIR)/%.o: $(COMMON_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT_DIR)/%.o: $(CLIENT_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_DIR)/%.o: $(SERVER_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(COMMON_DIR)/*.o $(CLIENT_DIR)/*.o $(SERVER_DIR)/*.o $(CLIENT_TARGET) $(SERVER_TARGET)