pipefile: pipeit.c
	gcc pipeit.c -o pipefile
run: pipefile
	./pipefile