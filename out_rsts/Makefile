#
#
#
SRV=server
CLN=client

SRVOBJ=server.o
CLNOBJ=client.o

all: $(SRV) $(CLN)

$(SRV): $(SRVOBJ)
	$(CC) -o $(SRV) $(SRVOBJ)

$(CLN): $(CLNOBJ)
	$(CC) -o $(CLN) $(CLNOBJ)

server.o: server.c server.h
client.o: client.c server.h

clean:
	rm -rf $(SRV) $(CLN) $(SRVOBJ) $(CLNOBJ)

