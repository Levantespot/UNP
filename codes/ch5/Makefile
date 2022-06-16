# CFLAGS = -I /home/lee/UNP/unp/lib -g -O2 -Wall
# LIBS = /home/lee/UNP/unp/libunp.a -pthread

CFLAGS = -g -O2 -Wall
LIBS = ../lib/unpL.a
LIBS_FLAG = -pthread

PROGS = echocli echosrv

all: $(PROGS)

echocli: echocli.c $(LIBS)
	gcc $(CFLAGS) -o $@ $^ $(LIBS_FLAG)

echosrv: echosrv.c $(LIBS)
	gcc $(CFLAGS) -o $@ $^ $(LIBS_FLAG)

clean:
	-rm $(PROGS)