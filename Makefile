CFLAGS = -I/usr/local/include 
LIBS=-L/usr/local/lib -lsndfile -lm

thx:	thx.o
	$(CC) -o thx $(CFLAGS) thx.o $(LIBS)
