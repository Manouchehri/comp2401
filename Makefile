cc := gcc
CFLAGS := -D_GNU_SOURCE -D_POSIX_C_SOURCE=199309L -Wall -Wextra -Wmissing-prototypes -std=c11 -g -ggdb3 -g3

SERVER_SRC := server.c list.c protocol.c
SERVER_OBJ := $(SERVER_SRC:.c=.o)
SERVER_BIN := server

CLIENT_SRC := client.c protocol.c
CLIENT_OBJ := $(CLIENT_SRC:.c=.o)
CLIENT_BIN := client

.PHONY: all dev

dev: clean all
	ctags -f .tags -R .

all: $(CLIENT_BIN) $(SERVER_BIN)

$(CLIENT_BIN): $(CLIENT_OBJ)
	$(cc) $(CFLAGS) $(CLIENT_OBJ) -o $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_OBJ)
	$(cc) $(CFLAGS) $(SERVER_OBJ) -o $(SERVER_BIN)

clean:
	rm -f $(CLIENT_BIN) $(SERVER_BIN) $(CLIENT_OBJ) $(SERVER_OBJ)
