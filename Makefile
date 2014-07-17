CC=g++ -g3 -Wall -ansi
OBJ=\
Request.o \
Response.o \
RESTChannelHandler.o \
Resty.o

lib: $(OBJ)
	ar rs libresty.a $(OBJ)

install:
	/bin/mkdir -p /usr/local/include/resty
	/bin/cp *.h /usr/local/include/resty/
	/bin/cp *.a /usr/local/lib/

uninstall:
	/bin/rm -rf /usr/local/include/resty/
	/bin/rm -f /usr/local/lib/libresty.a

sample: lib sample.o
	$(CC) -o sample sample.o -L. -lresty -lnetty++ -lSocket -lMyThread -lpthread -lstrmanip++

.cpp.o:
	$(CC) -c $<

clean:
	rm -f *.o

mrproper: clean
	rm -f libresty.a
	rm -f sample

debug: sample
	gdb sample -x gdb.x
