ROOT_PATH=$(shell pwd)
BIN=httpd
CC=gcc
SRC=httpd.c
OBJ=$(SRC:.c=.o) #.c->.o
LIB=-lpthread
FLAGS= #-D_DEBUG_
CGI=$(ROOT_PATH)/htdoc/cgi $(ROOT_PATH)/mysql_connect

.PHONY:all
all:$(BIN) cgi

$(BIN):$(OBJ)
	$(CC) -o $@ $^ $(LIB)
%.o:%.c
	$(CC) -c $< $(FLAGS)
.PHONY:cgi
cgi:
	for name in `echo $(CGI)`;\
    do\
        cd $$name;\
        make;\
        cd -;\
    done
	cp mysql_connect/cgi_insert htdoc/cgi
	cp mysql_connect/cgi_select htdoc/cgi
.PHONY:clean
clean:
	rm -rf *.o $(BIN) outpout
	for name in `echo $(CGI)`;\
		do\
		   cd $$name;\
		   make clean;\
		   cd -;\
		done
.PHONY:output
output:
	mkdir -p output/lib
	mkdir -p output/htdoc/cgi
	mkdir -p output/htdoc/imag
	cp -f httpd output
	cp htdoc/cgi/cgi_math output/htdoc/cgi
	cp htdoc/imag/* output/htdoc/imag
	cp htdoc/index.html output/htdoc
	cp mysql_connect/cgi_insert output/htdoc/cgi
	cp mysql_connect/cgi_select output/htdoc/cgi
	cp start.sh output
	cp lib/lib/* output/lib
	cp readme.md output
