CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
SRC = src/*.c

tdas: $(SRC) main.c
	gcc $(CFLAGS) $^ -o $@

pruebas: $(SRC) pruebas_alumno.c
	gcc $(CFLAGS) $^ -o $@

valgrind: tdas
	valgrind --leak-check=full ./tdas archivo.csv operacion modo valor

clean:
	rm -f tdas pruebas

format:
	clang-format -i -style=file $(SRC) src/*.h *.c *.h
