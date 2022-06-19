# CFLAGS = -I /home/lee/UNP/unp/lib -g -O2 -Wall
# LIBS = /home/lee/UNP/unp/libunp.a -pthread

CFLAGS = -g -O2 -Wall
LIBS = ../lib/unpL.a
LIBS_FLAG = -pthread

PROGS = daytimecli daytimesrv

all: $(PROGS)

daytimecli: daytimecli.c $(LIBS)
	gcc $(CFLAGS) -o $@ $^ $(LIBS) $(LIBS_FLAG)

daytimesrv: daytimesrv.c $(LIBS)
	gcc $(CFLAGS) -o $@ $^ $(LIBS) $(LIBS_FLAG)

clean:
	$(PROGS)