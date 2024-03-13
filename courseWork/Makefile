noLib:
	gcc backpack.c Program\ Files/components.c -o backpack.exe -lm

static:
	gcc -c backpack.c  Program\ Files/components.c 
	mv *.o Program\ Files
	ar r libSTATIC.a Program\ Files/components.o
	gcc Program\ Files/backpack.o -L. -lSTATIC -o backpack.exe -lm

dynamic:
	gcc -c backpack.c
	gcc -c -fPIC Program\ Files/components.c
	mv *.o Program\ Files
	gcc -shared -o libDYNAMIC.so Program\ Files/components.o
	gcc -o backpack.exe Program\ Files/backpack.o -L. -lDYNAMIC -Wl,-rpath,. -lm
	
clean:
	rm -rf *.exe *.so *.a Program\ Files/*.o