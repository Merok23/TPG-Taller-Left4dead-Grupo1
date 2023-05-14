CC = g++
CFLAGS = -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L

COMMON_DIR = common
CLIENT_DIR = client
SERVER_DIR = server
TARGET_DIR = target

COMMON_SRCS = $(wildcard $(COMMON_DIR)/*.cpp)
CLIENT_SRCS = $(wildcard $(CLIENT_DIR)/*.cpp)
SERVER_SRCS = $(wildcard $(SERVER_DIR)/*.cpp)

COMMON_OBJS = $(patsubst %.c, %.o, $(COMMON_SRCS))
CLIENT_OBJS = $(patsubst %.c, %.o, $(CLIENT_SRCS))
SERVER_OBJS = $(patsubst %.c, %.o, $(SERVER_SRCS))

TARGET = $(TARGET_DIR)/executable

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(COMMON_OBJS) $(CLIENT_OBJS) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(COMMON_DIR)/%.o: $(COMMON_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT_DIR)/%.o: $(CLIENT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_DIR)/%.o: $(SERVER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(COMMON_DIR)/*.o $(CLIENT_DIR)/*.o $(SERVER_DIR)/*.o $(TARGET)