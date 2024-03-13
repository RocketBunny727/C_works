data_maker:
	gcc data_maker.c -o data_make.exe

nolib:
	gcc main.c func.c -o main.exe -lncurses

static:
	gcc -c main.c func.c
	ar r libSTATIC.a func.o
	gcc main.o -L. -lSTATIC -o main.exe -lm -lncurses

dynamic:
	gcc -c main.c
	gcc -c -fPIC func.c
	gcc -shared -o libDYNAMIC.so func.c
	gcc -o main.exe main.o -L. -lDYNAMIC -Wl,-rpath,. -lm -lncurses

clean:
	rm -rf *.o

full_clean:
	rm -rf *.exe *.so *.a *.o *.txt