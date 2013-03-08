CC ?= gcc

.PHONY:all
all: 
	$(MAKE) compile


compile:
	$(CC) -o procstat -O0 -g main.c procstat.c

clean:
	rm -rf procstat *.o
