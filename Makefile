DEBUG= 
EXECS= server client 

all:	$(EXECS)

server:	server.c defs.h
	gcc $(DEBUG) -o server server.c

client:	client.c defs.h
	gcc $(DEBUG) -o client client.c

clean:
	rm -f $(EXECS)
