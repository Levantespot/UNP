# CFLAGS = -I /home/lee/UNP/unp/lib -g -O0 -Wall
# LIBS = /home/lee/UNP/unp/libunp.a -pthread

CFLAGS = -g -O0 -Wall
LIBS = ../lib/unpL.a
LIBS_FLAG = -pthread

PROGS = echocli echocli3 echosrv echosrv2 echosrv3

.PHONY: all clean

all: $(PROGS)

echocli: echocli.c $(LIBS)
	gcc $(CFLAGS) -o $@ $^ $(LIBS_FLAG)

echocli3: echocli3.c $(LIBS)
	gcc $(CFLAGS) -o $@ $^ $(LIBS_FLAG)

echosrv: echosrv.c $(LIBS)
	gcc $(CFLAGS) -o $@ $^ $(LIBS_FLAG)

echosrv2: echosrv2.c $(LIBS)
	gcc $(CFLAGS) -o $@ $^ $(LIBS_FLAG)

echosrv3: echosrv3.c $(LIBS)
	gcc $(CFLAGS) -o $@ $^ $(LIBS_FLAG)

clean:
	-rm $(PROGS)