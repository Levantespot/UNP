CFLAGS = -g -O2 -Wall

LIBS = -pthread

OBJECTIVE_FILES = wrapsocket.o wrapunix.o error.o wrapio.o wrapstdio.o basic_socket.o

unpL.a: unpL.h $(OBJECTIVE_FILES);
	ar rcs unpL.a $(OBJECTIVE_FILES)

wrapsocket.o: wrapsocket.c
	gcc -c $(CFLAGS) -o $@ $^ $(LIBS)

wrapunix.o: wrapunix.c
	gcc -c $(CFLAGS) -o $@ $^ $(LIBS)

error.o: error.c
	gcc -c $(CFLAGS) -o $@ $^ $(LIBS)

wrapio.o: wrapio.c
	gcc -c $(CFLAGS) -o $@ $^ $(LIBS)

wrapstdio.o: wrapstdio.c
	gcc -c $(CFLAGS) -o $@ $^ $(LIBS)

basic_socket.o: basic_socket.c
	gcc -c $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm $(OBJECTIVE_FILES) unpL.a