INCLUDE=-Icontrib/
CC=g++ -std=c++11 -Wall $(CFLAGS)
OBJ=\
Request.o \
Response.o \
RESTChannelHandler.o \
Resty.o

lib: $(OBJ)
	ar rs libresty.a $(OBJ)

install: lib
	/bin/mkdir -p /usr/local/include/resty
	/bin/cp *.h /usr/local/include/resty/
	/bin/cp *.a /usr/local/lib/

uninstall:
	/bin/rm -rf /usr/local/include/resty/
	/bin/rm -f /usr/local/lib/libresty.a

sample: lib sample.o
	$(CC) -o sample sample.o -Lcontrib/MySocket -Lcontrib/MyThread -Lcontrib/netty++ -Lcontrib/libstrmanip++ -L. -lresty -lnetty++ -lSocket -lMyThread -lpthread -lstrmanip++ -lboost_regex

.cpp.o:
	$(CC) $(INCLUDE) -c $<

clean:
	rm -f *.o

mrproper: clean
	rm -f libresty.a
	rm -f sample

debug: sample
	gdb sample -x gdb.x
