all:
    cc -S def.c -o def.S
    cc def.S -o def.o
    cc -S main.c -o main.S
    cc main.S -o main.o
    cc main.o def.o -o main
