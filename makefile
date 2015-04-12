viruses: viruses.o
	gcc -o viruses viruses.o -ggdb
	
viruses.o: viruses.c
	gcc -c viruses.c -ggdb
	
clean:
	rm viruses viruses.o
