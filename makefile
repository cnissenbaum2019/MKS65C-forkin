make: forkin.c
	gcc forkin.c

run: a.out
	./a.out

clean: a.out
	rm a.out

a.out: forkin.c
	gcc forkin.c