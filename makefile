CC=gcc
CFLAGS = -Wall -Wfatal-errors 
LDFLAGS = -lm  

all: bobail.x

print_board.o: print_board.c
	$(CC) $(CFLAGS) -c $< -o $@

test_end.o: test_end.c
	$(CC) $(CFLAGS) -c $< -o $@

get.o: get.c 
	$(CC) $(CFLAGS) -c $< -o $@

destroy_board.o: destroy_board.c 
	$(CC) $(CFLAGS) -c $< -o $@

swap.o: swap.c 
	$(CC) $(CFLAGS) -c $< -o $@

modify_board.o: modify_board.c 
	$(CC) $(CFLAGS) -c $< -o $@

is_legal.o: is_legal_bis.c 
	$(CC) $(CFLAGS) -c $< -o $@

is_path_empty.o: is_path_empty.c
	$(CC) $(CFLAGS) -c $< -o $@

bobail.o: bobail.c
	$(CC) $(CFLAGS) -c $< -o $@

bobail.x: print_board.o test_end.o get.o destroy_board.o swap.o modify_board.o is_legal_bis.o is_path_empty.o bobail.o
	$(CC) $^ -o $@ $(LDFLAGS)


clean:
	rm -f *.o bobail.x 

rebuild: clean all

run: all
	./bobail.x