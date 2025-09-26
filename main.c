#include "src/lista.h"
#include "src/tp1.h"
#include "src/functions.h"

#include <stdio.h>
#include "string.h"

struct ctx_busqueda {
	int id;
	const char *nombre;
	struct pokemon *resultado;
};

void imprimir_pokemon(const struct pokemon *pokemon)
{
	printf("%s(%i) - Tipo:%s A:%u D:%u V:%u\n", pokemon->nombre,
	       pokemon->id, calcular_tipo((struct pokemon *)pokemon),
	       pokemon->ataque, pokemon->defensa, pokemon->velocidad);
}

bool buscar_por_id_cb(void *dato, void *extra)
{
	struct pokemon *p = dato;
	struct ctx_busqueda *ctx = extra;

	if (p->id == ctx->id) {
		ctx->resultado = p;
		return false;
	}
	return true;
}

bool buscar_por_nombre_cb(void *dato, void *extra)
{
	struct pokemon *p = dato;
	struct ctx_busqueda *ctx = extra;

	if (strcmp(p->nombre, ctx->nombre) == 0) {
		ctx->resultado = p;
		return false;
	}
	return true;
}

struct pokemon *buscar_por_id(lista_t *lista, int id)
{
	struct ctx_busqueda ctx = { .id = id, .resultado = NULL };
	lista_con_cada_elemento(lista, buscar_por_id_cb, &ctx);

	return ctx.resultado;
}

struct pokemon *buscar_por_nombre(lista_t *lista, char *nombre)
{
	struct ctx_busqueda ctx = { .nombre = nombre, .resultado = NULL };
	lista_con_cada_elemento(lista, buscar_por_nombre_cb, &ctx);

	return ctx.resultado;
}

bool agregar_a_lista(struct pokemon *p, void *ctx)
{
	lista_t *lista = ctx;
	return lista_agregar(lista, p);
}

bool validar_argumentos(int argc, char *argv[])
{
	const char *op = argv[2];
	int esperado = 0;

	if (strcmp(op, "buscar") == 0)
		esperado = 5;
	else {
		printf("Error: Operacion '%s' no reconocida.\n", op);
		return false;
	}

	if (argc != esperado) {
		printf("Error: cantidad de argumentos invalida para '%s'.\n",
		       op);
		return false;
	}

	return true;
}

void lista_buscar_pokemon(int argc, char *argv[], lista_t *l)
{
	const struct pokemon *p = NULL;
	if (strcmp(argv[3], "id") == 0)
		p = buscar_por_id(l, atoi(argv[4]));
	else if (strcmp(argv[3], "nombre") == 0)
		p = buscar_por_nombre(l, argv[4]);

	if (!p) {
		printf("Pokemon con %s %s no encontrado.\n", argv[3], argv[4]);
		return;
	}

	imprimir_pokemon(p);
	return;
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("Uso:\n  %s <archivo.csv> buscar <id|nombre> <valor>\n",
		       argv[0]);
		return -1;
	}

	if (!validar_argumentos(argc, argv))
		return -1;

	tp1_t *tp = tp1_leer_archivo(argv[1]);
	if (!tp) {
		fprintf(stderr, "Error al leer archivo %s\n", argv[1]);
		return 1;
	}

	lista_t *lista = lista_crear();
	if (!lista) {
		tp1_destruir(tp);
		return 1;
	}

	tp1_con_cada_pokemon(tp, agregar_a_lista, lista);

	lista_buscar_pokemon(argc, argv, lista);

	lista_destruir(lista);
	tp1_destruir(tp);

	return 0;
}
