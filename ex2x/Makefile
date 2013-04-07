FLAGS = -std=gnu99 -Wall -lrt

all: list.o tree.o tree_avl.o utils.o auto_test.o main.o
	gcc $(FLAGS) obj/list.o obj/tree.o obj/tree_avl.o obj/utils.o obj/auto_test.o obj/main.o -o ex2

list.o:
	gcc $(FLAGS) lib/list.c -c -o obj/list.o

tree.o:
	gcc $(FLAGS) lib/tree.c -c -o obj/tree.o

tree_avl.o:
	gcc $(FLAGS) lib/tree_avl.c -c -o obj/tree_avl.o

utils.o:
	gcc $(FLAGS) lib/utils.c -c -o obj/utils.o

main.o:
	gcc $(FLAGS) main.c -c -o obj/main.o

auto_test.o:
	gcc $(FLAGS) lib/auto_test.c -c -o obj/auto_test.o 

clean:
	rm -f obj/*.o dot/* ex2

test:	all
	valgrind --leak-check=full ./ex2	

dot: all
	./scripts/gen-dot.sh

graphs:
	gnuplot ./scripts/plot
