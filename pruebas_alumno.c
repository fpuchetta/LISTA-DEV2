#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

struct ctx_contar {
	size_t visitas;
};

bool visitar_contar_todos(void *dato, void *extra)
{
	(void)dato;
	struct ctx_contar *ctx = extra;
	ctx->visitas++;

	return true;
}

struct ctx_buscar_ptr {
	void *objetivo;
	size_t visitas;
	bool encontrado;
};

static int cmp_int_ptr(const void *a, const void *b)
{
	int A = *(const int *)a;
	int B = *(const int *)b;
	return (A > B) - (A < B);
}

bool visitar_corta_en_objetivo(void *dato, void *extra)
{
	struct ctx_buscar_ptr *ctx = extra;
	ctx->visitas++;

	if (dato == ctx->objetivo) {
		ctx->encontrado = true;
		return false;
	}

	return true;
}

void lista_crear_crea_lista_vacia()
{
	lista_t *l = lista_crear();
	pa2m_afirmar(l != NULL, "lista_crear crea lista correctamente");
	pa2m_afirmar(lista_cantidad(l) == 0,
		     "lista_crear crea lista vacía (cantidad 0)");
	lista_destruir(l);
}

void pruebas_lista_crear()
{
	pa2m_nuevo_grupo("lista_crear parametros validos");
	lista_crear_crea_lista_vacia();
}

void lista_vacia_nueva_es_verdadera()
{
	lista_t *l = lista_crear();
	pa2m_afirmar(lista_vacia(l),
		     "lista_vacia sobre lista recién creada es verdadera");
	lista_destruir(l);
}

void lista_vacia_luego_de_agregar_es_falsa()
{
	lista_t *l = lista_crear();
	int v = 1;
	lista_agregar(l, &v);
	pa2m_afirmar(!lista_vacia(l),
		     "lista_vacia devuelve false tras agregar un elemento");
	lista_destruir(l);
}

void lista_vacia_luego_de_eliminar_ultimo_es_verdadera()
{
	lista_t *l = lista_crear();
	int v = 1;
	lista_agregar(l, &v);
	(void)lista_eliminar_elemento(l, 0);
	pa2m_afirmar(
		lista_vacia(l),
		"lista_vacia vuelve a true tras eliminar el último elemento");
	lista_destruir(l);
}

void lista_vacia_lista_nula_devuelve_null()
{
	pa2m_afirmar(lista_vacia(NULL),
		     "lista_vacia con lista NULL devuelve NULL");
}

void pruebas_lista_vacia()
{
	pa2m_nuevo_grupo("lista_vacia parametros validos");
	lista_vacia_nueva_es_verdadera();
	lista_vacia_luego_de_agregar_es_falsa();
	lista_vacia_luego_de_eliminar_ultimo_es_verdadera();

	pa2m_nuevo_grupo("lista_vacia parametros invalidos");
	lista_vacia_lista_nula_devuelve_null();
}

void lista_cantidad_actualiza_correctamente()
{
	lista_t *l = lista_crear();
	int v1 = 1, v2 = 2, v3 = 3;
	pa2m_afirmar(lista_cantidad(l) == 0, "cantidad inicial es 0");
	lista_agregar(l, &v1);
	lista_agregar(l, &v2);
	pa2m_afirmar(lista_cantidad(l) == 2,
		     "cantidad es 2 tras dos agregados");
	lista_eliminar_elemento(l, 1);
	pa2m_afirmar(lista_cantidad(l) == 1,
		     "cantidad decrece a 1 tras eliminar");
	lista_agregar(l, &v3);
	pa2m_afirmar(lista_cantidad(l) == 2,
		     "cantidad vuelve a 2 tras agregar");
	lista_destruir(l);
}

void lista_cantidad_lista_nula_devuelve_cero()
{
	pa2m_afirmar(lista_cantidad(NULL) == 0,
		     "lista_cantidad con lista NULL devuelve 0");
}

void pruebas_lista_cantidad()
{
	pa2m_nuevo_grupo("lista_cantidad parametros validos");
	lista_cantidad_actualiza_correctamente();

	pa2m_nuevo_grupo("lista_cantidad parametros invalidos");
	lista_cantidad_lista_nula_devuelve_cero();
}

void lista_agregar_un_elemento()
{
	lista_t *l = lista_crear();
	int v = 7;
	pa2m_afirmar(lista_agregar(l, &v), "lista_agregar agrega un elemento");
	pa2m_afirmar(lista_cantidad(l) == 1,
		     "lista_cantidad devuelve 1 tras agregar");
	pa2m_afirmar(lista_buscar_elemento(l, 0) == &v,
		     "lista_buscar_elemento(0) devuelve el agregado");
	lista_destruir(l);
}

void lista_agregar_multiples_mantiene_orden()
{
	lista_t *l = lista_crear();
	int v1 = 1, v2 = 2, v3 = 3;
	lista_agregar(l, &v1);
	lista_agregar(l, &v2);
	lista_agregar(l, &v3);
	pa2m_afirmar(lista_cantidad(l) == 3,
		     "lista_agregar suma cantidad correctamente (3)");
	pa2m_afirmar(lista_buscar_elemento(l, 0) == &v1,
		     "posición 0 es el primero agregado");
	pa2m_afirmar(lista_buscar_elemento(l, 1) == &v2,
		     "posición 1 es el segundo");
	pa2m_afirmar(lista_buscar_elemento(l, 2) == &v3,
		     "posición 2 es el tercero");
	lista_destruir(l);
}

void lista_agregar_lista_nula_devuelve_null()
{
	int v = 5;
	pa2m_afirmar(!lista_agregar(NULL, &v),
		     "lista_agregar con lista NULL devuelve NULL");
}

void pruebas_lista_agregar()
{
	pa2m_nuevo_grupo("lista_agregar parametros validos");
	lista_agregar_un_elemento();
	lista_agregar_multiples_mantiene_orden();

	pa2m_nuevo_grupo("lista_agregar parametros invalidos");
	lista_agregar_lista_nula_devuelve_null();
}

void lista_insertar_no_permite_primer_elemento_en_lista_vacia()
{
	lista_t *l = lista_crear();
	int v = 9;
	pa2m_afirmar(
		!lista_insertar(l, &v, 0),
		"lista_insertar NO permite insertar el PRIMER elemento (lista vacía, pos 0)");
	pa2m_afirmar(lista_cantidad(l) == 0, "cantidad sigue en 0 tras fallo");
	lista_destruir(l);
}

void lista_insertar_en_cabeza_con_lista_no_vacia()
{
	lista_t *l = lista_crear();
	int v1 = 10, v2 = 20;
	lista_agregar(l, &v1); // lista no vacía
	pa2m_afirmar(lista_insertar(l, &v2, 0),
		     "lista_insertar en pos 0 con lista NO vacía funciona");
	pa2m_afirmar(lista_cantidad(l) == 2, "cantidad es 2");
	pa2m_afirmar(lista_buscar_elemento(l, 0) == &v2,
		     "nuevo primero es el insertado");
	pa2m_afirmar(lista_buscar_elemento(l, 1) == &v1,
		     "el anterior primero quedó en pos 1");
	lista_destruir(l);
}

void lista_insertar_en_medio()
{
	lista_t *l = lista_crear();
	int v1 = 1, v2 = 2, v3 = 3;
	lista_agregar(l, &v1);
	lista_agregar(l, &v3);
	pa2m_afirmar(lista_insertar(l, &v2, 1),
		     "insertar en posición media (1) funciona");
	pa2m_afirmar(lista_buscar_elemento(l, 0) == &v1, "pos 0 = v1");
	pa2m_afirmar(lista_buscar_elemento(l, 1) == &v2, "pos 1 = v2");
	pa2m_afirmar(lista_buscar_elemento(l, 2) == &v3, "pos 2 = v3");
	lista_destruir(l);
}

void lista_insertar_al_final_equivale_agregar()
{
	lista_t *l = lista_crear();
	int v1 = 4, v2 = 5;
	lista_agregar(l, &v1);
	pa2m_afirmar(
		lista_insertar(l, &v2, lista_cantidad(l)),
		"insertar en pos == cantidad delega en agregar (agrega al final)");
	pa2m_afirmar(lista_buscar_elemento(l, 1) == &v2,
		     "nuevo último es el insertado");
	lista_destruir(l);
}

void lista_insertar_posicion_invalida_falla()
{
	lista_t *l = lista_crear();
	int v = 123;
	pa2m_afirmar(!lista_insertar(l, &v, 5),
		     "lista_insertar con pos > cantidad falla");
	lista_destruir(l);
}

void lista_insertar_lista_nula_devuelve_null()
{
	int v = 7;
	pa2m_afirmar(!lista_insertar(NULL, &v, 0),
		     "lista_insertar con lista NULL devuelve NULL");
}

void pruebas_lista_insertar()
{
	pa2m_nuevo_grupo("lista_insertar parametros validos");
	lista_insertar_en_cabeza_con_lista_no_vacia();
	lista_insertar_en_medio();
	lista_insertar_al_final_equivale_agregar();

	pa2m_nuevo_grupo("lista_insertar parametros invalidos");
	lista_insertar_no_permite_primer_elemento_en_lista_vacia();
	lista_insertar_posicion_invalida_falla();
	lista_insertar_lista_nula_devuelve_null();
}

void lista_eliminar_elemento_en_cabeza()
{
	lista_t *l = lista_crear();
	int v1 = 10, v2 = 20;
	lista_agregar(l, &v1);
	lista_agregar(l, &v2);

	void *e = lista_eliminar_elemento(l, 0);
	pa2m_afirmar(e == &v1, "eliminar pos 0 devuelve el primero");
	pa2m_afirmar(lista_cantidad(l) == 1, "cantidad decrementa a 1");
	pa2m_afirmar(lista_buscar_elemento(l, 0) == &v2,
		     "nuevo primero es el que estaba segundo");
	lista_destruir(l);
}

void lista_eliminar_elemento_en_medio()
{
	lista_t *l = lista_crear();
	int v1 = 1, v2 = 2, v3 = 3;
	lista_agregar(l, &v1);
	lista_agregar(l, &v2);
	lista_agregar(l, &v3);

	void *e = lista_eliminar_elemento(l, 1);
	pa2m_afirmar(e == &v2, "eliminar en medio devuelve el correcto");
	pa2m_afirmar(lista_cantidad(l) == 2, "cantidad ahora es 2");
	pa2m_afirmar(lista_buscar_elemento(l, 0) == &v1 &&
			     lista_buscar_elemento(l, 1) == &v3,
		     "el enlace se mantiene correcto tras eliminar en medio");
	lista_destruir(l);
}

void lista_eliminar_elemento_en_ultimo()
{
	lista_t *l = lista_crear();
	int v1 = 4, v2 = 5;
	lista_agregar(l, &v1);
	lista_agregar(l, &v2);

	void *e = lista_eliminar_elemento(l, 1);
	pa2m_afirmar(e == &v2, "eliminar último devuelve el último");
	pa2m_afirmar(lista_cantidad(l) == 1, "cantidad decrece");
	pa2m_afirmar(lista_buscar_elemento(l, 0) == &v1,
		     "queda solo el primero");
	// verificar que se pueda volver a agregar al final
	int v3 = 6;
	pa2m_afirmar(lista_agregar(l, &v3),
		     "se puede agregar nuevamente al final");
	pa2m_afirmar(lista_buscar_elemento(l, 1) == &v3,
		     "nuevo último es el recién agregado");
	lista_destruir(l);
}

void lista_eliminar_elemento_en_lista_vacia_devuelve_null()
{
	lista_t *l = lista_crear();
	pa2m_afirmar(lista_eliminar_elemento(l, 0) == NULL,
		     "lista_eliminar_elemento en lista vacía devuelve NULL");
	lista_destruir(l);
}

void lista_eliminar_elemento_posicion_invalida_devuelve_null()
{
	lista_t *l = lista_crear();
	int v = 1;
	lista_agregar(l, &v);
	pa2m_afirmar(
		lista_eliminar_elemento(l, 99) == NULL,
		"lista_eliminar_elemento con pos >= cantidad devuelve NULL");
	lista_destruir(l);
}

void lista_eliminar_elemento_lista_nula_devuelve_null()
{
	pa2m_afirmar(lista_eliminar_elemento(NULL, 0) == NULL,
		     "lista_eliminar_elemento con lista NULL devuelve NULL");
}

void pruebas_lista_eliminar_elemento()
{
	pa2m_nuevo_grupo("lista_eliminar_elemento parametros validados");
	lista_eliminar_elemento_en_cabeza();
	lista_eliminar_elemento_en_medio();
	lista_eliminar_elemento_en_ultimo();

	pa2m_nuevo_grupo("lista_eliminar_elemento parametros invalidos");
	lista_eliminar_elemento_en_lista_vacia_devuelve_null();
	lista_eliminar_elemento_posicion_invalida_devuelve_null();
	lista_eliminar_elemento_lista_nula_devuelve_null();
}

void lista_buscar_posicion_encuentra_primera_coincidencia()
{
	lista_t *l = lista_crear();
	int a = 10, b = 20, c = 20, d = 30;
	lista_agregar(l, &a);
	lista_agregar(l, &b);
	lista_agregar(l, &c);
	lista_agregar(l, &d);

	int clave = 20;
	int pos = lista_buscar_posicion(l, &clave, cmp_int_ptr);
	pa2m_afirmar(
		pos == 1,
		"lista_buscar_posicion encuentra la PRIMERA coincidencia (pos 1)");

	lista_destruir(l);
}

void lista_buscar_posicion_no_encuentra_devuelve_menos_uno()
{
	lista_t *l = lista_crear();
	int a = 1, b = 2, c = 3;
	lista_agregar(l, &a);
	lista_agregar(l, &b);
	lista_agregar(l, &c);

	int clave = 99;
	int pos = lista_buscar_posicion(l, &clave, cmp_int_ptr);
	pa2m_afirmar(pos == -1,
		     "lista_buscar_posicion con clave inexistente devuelve -1");

	lista_destruir(l);
}

void lista_buscar_posicion_lista_vacia_devuelve_menos_uno()
{
	lista_t *l = lista_crear();
	int clave = 5;
	int pos = lista_buscar_posicion(l, &clave, cmp_int_ptr);
	pa2m_afirmar(pos == -1,
		     "lista_buscar_posicion en lista vacía devuelve -1");
	lista_destruir(l);
}

void lista_buscar_posicion_lista_nula_devuelve_null()
{
	int clave = 5;
	int pos = lista_buscar_posicion(NULL, &clave, cmp_int_ptr);
	pa2m_afirmar(pos == -1,
		     "lista_buscar_posicion con lista NULL devuelve NULL");
}

void lista_buscar_posicion_cmp_nulo_devuelve_null()
{
	lista_t *l = lista_crear();
	int a = 1, clave = 1;
	lista_agregar(l, &a);
	int pos = lista_buscar_posicion(l, &clave, NULL);
	pa2m_afirmar(pos == -1,
		     "lista_buscar_posicion con comparador NULL devuelve NULL");
	lista_destruir(l);
}

void pruebas_lista_buscar_posicion()
{
	pa2m_nuevo_grupo("lista_buscar_posicion parametros validos");
	lista_buscar_posicion_encuentra_primera_coincidencia();
	lista_buscar_posicion_no_encuentra_devuelve_menos_uno();
	lista_buscar_posicion_lista_vacia_devuelve_menos_uno();

	pa2m_nuevo_grupo("lista_buscar_posicion parametros invalidos");
	lista_buscar_posicion_lista_nula_devuelve_null();
	lista_buscar_posicion_cmp_nulo_devuelve_null();
}

void lista_buscar_elemento_indices_validos()
{
	lista_t *l = lista_crear();
	int v1 = 1, v2 = 2, v3 = 3;
	lista_agregar(l, &v1);
	lista_agregar(l, &v2);
	lista_agregar(l, &v3);

	pa2m_afirmar(lista_buscar_elemento(l, 0) == &v1,
		     "buscar pos 0 devuelve v1");
	pa2m_afirmar(lista_buscar_elemento(l, 1) == &v2,
		     "buscar pos 1 devuelve v2");
	pa2m_afirmar(lista_buscar_elemento(l, 2) == &v3,
		     "buscar pos 2 devuelve v3");

	lista_destruir(l);
}

void lista_buscar_elemento_indices_invalidos_devuelve_null()
{
	lista_t *l = lista_crear();
	int v = 9;
	lista_agregar(l, &v);

	pa2m_afirmar(lista_buscar_elemento(l, 1) == NULL,
		     "buscar pos == cantidad devuelve NULL");
	pa2m_afirmar(lista_buscar_elemento(l, 99) == NULL,
		     "buscar pos > cantidad devuelve NULL");
	lista_destruir(l);
}

void lista_buscar_elemento_lista_vacia_devuelve_null()
{
	lista_t *l = lista_crear();
	pa2m_afirmar(lista_buscar_elemento(l, 0) == NULL,
		     "lista_buscar_elemento en lista vacía devuelve NULL");
	lista_destruir(l);
}

void lista_buscar_elemento_lista_nula_devuelve_null()
{
	pa2m_afirmar(lista_buscar_elemento(NULL, 0) == NULL,
		     "lista_buscar_elemento con lista NULL devuelve NULL");
}

void pruebas_lista_buscar_elemento()
{
	pa2m_nuevo_grupo("lista_buscar_elemento parametros validos");
	lista_buscar_elemento_indices_validos();

	pa2m_nuevo_grupo("lista_buscar_elemento parametros invalidos");
	lista_buscar_elemento_indices_invalidos_devuelve_null();
	lista_buscar_elemento_lista_vacia_devuelve_null();
	lista_buscar_elemento_lista_nula_devuelve_null();
}

void lista_con_cada_elemento_recorre_todos_y_cuenta()
{
	lista_t *l = lista_crear();
	int a = 1, b = 2, c = 3, d = 4;
	lista_agregar(l, &a);
	lista_agregar(l, &b);
	lista_agregar(l, &c);
	lista_agregar(l, &d);

	struct ctx_contar ctx = { 0 };
	size_t visitas = lista_con_cada_elemento(l, visitar_contar_todos, &ctx);

	pa2m_afirmar(visitas == 4 && ctx.visitas == 4,
		     "lista_con_cada_elemento recorre todos los elementos (4)");
	lista_destruir(l);
}

void lista_con_cada_elemento_corta_en_objetivo()
{
	lista_t *l = lista_crear();
	int a = 10, b = 20, c = 30, d = 40;
	lista_agregar(l, &a);
	lista_agregar(l, &b);
	lista_agregar(l, &c);
	lista_agregar(l, &d);

	struct ctx_buscar_ptr ctx = { .objetivo = &c,
				      .visitas = 0,
				      .encontrado = false };
	size_t visitas =
		lista_con_cada_elemento(l, visitar_corta_en_objetivo, &ctx);

	pa2m_afirmar(ctx.encontrado,
		     "con_cada_elemento corta al encontrar el objetivo");
	pa2m_afirmar(
		visitas == 3 && ctx.visitas == 3,
		"cantidad de visitas coincide con el índice del encontrado + 1 (3)");
	lista_destruir(l);
}

void lista_con_cada_elemento_lista_vacia_visitas_cero()
{
	lista_t *l = lista_crear();
	struct ctx_contar ctx = { 0 };
	size_t visitas = lista_con_cada_elemento(l, visitar_contar_todos, &ctx);
	pa2m_afirmar(visitas == 0 && ctx.visitas == 0,
		     "con_cada_elemento en lista vacía visita 0 elementos");
	lista_destruir(l);
}

void lista_con_cada_elemento_lista_nula_devuelve_cero()
{
	struct ctx_contar ctx = { 0 };
	size_t visitas =
		lista_con_cada_elemento(NULL, visitar_contar_todos, &ctx);
	pa2m_afirmar(visitas == 0,
		     "lista_con_cada_elemento con lista NULL devuelve 0");
}

void pruebas_lista_con_cada_elemento()
{
	pa2m_nuevo_grupo("lista_con_cada_elemento parametros validos");
	lista_con_cada_elemento_recorre_todos_y_cuenta();
	lista_con_cada_elemento_corta_en_objetivo();
	lista_con_cada_elemento_lista_vacia_visitas_cero();

	pa2m_nuevo_grupo("lista_con_cada_elemento parametros invalidos");
	lista_con_cada_elemento_lista_nula_devuelve_cero();
}

void lista_destruir_todo_con_elementos_heap_y_free_funciona_correctamente()
{
	lista_t *l = lista_crear();

	/* elementos en heap para que free sea pertinente */
	int *p1 = malloc(sizeof(int));
	int *p2 = malloc(sizeof(int));
	int *p3 = malloc(sizeof(int));
	if (p1)
		*p1 = 1;
	if (p2)
		*p2 = 2;
	if (p3)
		*p3 = 3;

	pa2m_afirmar(lista_agregar(l, p1), "agrego p1");
	pa2m_afirmar(lista_agregar(l, p2), "agrego p2");
	pa2m_afirmar(lista_agregar(l, p3), "agrego p3");

	/* Caja negra: solo validamos que no rompa */
	lista_destruir_todo(l, free);
	pa2m_afirmar(true,
		     "lista_destruir_todo con free funciona correctamente");
}

void lista_destruir_todo_con_elementos_null_y_free_funciona_correctamente()
{
	lista_t *l = lista_crear();

	/* mezclar NULL y punteros válidos: free(NULL) es seguro */
	int *p = malloc(sizeof(int));
	if (p)
		*p = 7;

	pa2m_afirmar(lista_agregar(l, NULL), "agrego NULL");
	pa2m_afirmar(lista_agregar(l, p), "agrego puntero valido");
	pa2m_afirmar(lista_agregar(l, NULL), "agrego otro NULL");

	lista_destruir_todo(l, free);
	pa2m_afirmar(
		true,
		"lista_destruir_todo con elementos NULL funciona correctamente");
}

void lista_destruir_todo_en_lista_vacia_funciona_correctamente()
{
	lista_t *l = lista_crear();
	lista_destruir_todo(l, free);
	pa2m_afirmar(
		true,
		"lista_destruir_todo sobre lista vacía funciona correctamente");
}

void lista_destruir_todo_lista_nula_devuelve_null()
{
	lista_destruir_todo(NULL, free);
	pa2m_afirmar(true, "lista_destruir_todo con lista NULL devuelve NULL");
}

void lista_destruir_todo_destructor_null_devuelve_null()
{
	lista_t *l = lista_crear();
	int a = 1, b = 2;
	lista_agregar(l, &a);
	lista_agregar(l, &b);

	lista_destruir_todo(l, NULL);
	pa2m_afirmar(true,
		     "lista_destruir_todo con destructor NULL devuelve NULL");
}

void pruebas_lista_destruir_todo()
{
	pa2m_nuevo_grupo("lista_destruir_todo parametros validos");
	lista_destruir_todo_con_elementos_heap_y_free_funciona_correctamente();
	lista_destruir_todo_con_elementos_null_y_free_funciona_correctamente();
	lista_destruir_todo_en_lista_vacia_funciona_correctamente();

	pa2m_nuevo_grupo("lista_destruir_todo parametros invalidos");
	lista_destruir_todo_lista_nula_devuelve_null();
	lista_destruir_todo_destructor_null_devuelve_null();
}

void lista_destruir_lista_vacia()
{
	lista_t *l = lista_crear();
	lista_destruir(l);
	pa2m_afirmar(true,
		     "lista_destruir destruye una lista vacía sin errores");
}

void lista_destruir_lista_con_elementos()
{
	lista_t *l = lista_crear();
	int a = 1, b = 2, c = 3;
	lista_agregar(l, &a);
	lista_agregar(l, &b);
	lista_agregar(l, &c);
	lista_destruir(l);
	pa2m_afirmar(
		true,
		"lista_destruir destruye una lista con elementos sin errores");
}

void lista_destruir_lista_nula_devuelve_null()
{
	lista_destruir(NULL);
	pa2m_afirmar(
		true,
		"lista_destruir con lista NULL devuelve NULL (no hace nada)");
}

void pruebas_lista_destruir()
{
	pa2m_nuevo_grupo("lista_destruir parametros validos");
	lista_destruir_lista_vacia();
	lista_destruir_lista_con_elementos();

	pa2m_nuevo_grupo("lista_destruir parametros invalidos");
	lista_destruir_lista_nula_devuelve_null();
}

void lista_iterar_itera_correctamente()
{
	lista_t *l = lista_crear();
	int a = 10, b = 20, c = 30, d = 40, e = 50;
	lista_agregar(l, &a);
	lista_agregar(l, &b);
	lista_agregar(l, &c);
	lista_agregar(l, &d);
	lista_agregar(l, &e);
	int *esperados[] = { &a, &b, &c, &d, &e };
	int posicion = 0;

	lista_iterador_t *li = NULL;
	for (li = lista_iterador_crear(l); lista_iterador_hay_mas_elementos(li);
	     lista_iterador_siguiente(li)) {
		int *elemento = lista_iterador_obtener_actual(li);
		pa2m_afirmar(
			elemento == esperados[posicion],
			"Elemento en iterador externo coincide con el esperado (esperado:%i | obtenido:%i)",
			*esperados[posicion], *elemento);
		posicion++;
	}
	pa2m_afirmar(posicion == 5,
		     "Se recorrieron los 5 elementos con el iterador externo");
	lista_iterador_destruir(li);
	lista_destruir(l);
}

void probar_iterador_externo_con_parametros_invalidos()
{
	lista_iterador_t *it_null = NULL;
	pa2m_afirmar(!lista_iterador_hay_mas_elementos(it_null),
		     "iterador NULL no tiene elementos por recorrer");
	pa2m_afirmar(lista_iterador_obtener_actual(it_null) == NULL,
		     "iterador NULL devuelve NULL al obtener elemento");
	lista_iterador_siguiente(it_null);
	pa2m_afirmar(
		true,
		"iterador NULL no ocasiona comportamiento indeterminado al avanzar iteración");
	lista_iterador_destruir(NULL);
	pa2m_afirmar(
		true,
		"Destruir iterador NULL no ocasiona comportamiento indeterminado");
}

void pruebas_lista_iterador()
{
	pa2m_nuevo_grupo("Pruebas iterador externo");
	lista_iterar_itera_correctamente();

	pa2m_nuevo_grupo("Pruebas invalidas iterador externo");
	probar_iterador_externo_con_parametros_invalidos();
}

void correr_pruebas_lista()
{
	pa2m_nuevo_grupo("Pruebas solo lista");
	pruebas_lista_crear();
	pruebas_lista_vacia();
	pruebas_lista_cantidad();
	pruebas_lista_agregar();
	pruebas_lista_insertar();
	pruebas_lista_eliminar_elemento();
	pruebas_lista_buscar_posicion();
	pruebas_lista_buscar_elemento();
	pruebas_lista_con_cada_elemento();
	pruebas_lista_destruir_todo();
	pruebas_lista_destruir();

	pa2m_nuevo_grupo("Pruebas lista_iterador");
	pruebas_lista_iterador();
}

// ===========================

void cola_crear_crea_cola_vacia()
{
	cola_t *c = cola_crear();
	pa2m_afirmar(c != NULL, "Cola_crear crea cola correctamente");

	pa2m_afirmar(cola_cantidad(c) == 0, "Cola_crear crea cola vacia");

	cola_destruir(c);
}

void pruebas_cola_crear()
{
	pa2m_nuevo_grupo("cola_crear parametros validos");
	cola_crear_crea_cola_vacia();
}

void cola_encolar_un_elemento()
{
	cola_t *c = cola_crear();
	int valor = 42;

	pa2m_afirmar(cola_encolar(c, &valor),
		     "Puedo encolar un elemento en una cola vacía");
	pa2m_afirmar(cola_cantidad(c) == 1,
		     "La cantidad es 1 después de encolar un elemento");
	pa2m_afirmar(cola_ver_primero(c) == &valor,
		     "El primero de la cola es el elemento encolado");

	cola_destruir(c);
}

void cola_encolar_encola_muchos_elementos()
{
	cola_t *c = cola_crear();
	int v1 = 1, v2 = 2, v3 = 3;

	pa2m_afirmar(cola_encolar(c, &v1), "Puedo encolar un primer elemento");
	pa2m_afirmar(cola_encolar(c, &v2), "Puedo encolar un segundo elemento");
	pa2m_afirmar(cola_encolar(c, &v3), "Puedo encolar un tercer elemento");

	pa2m_afirmar(
		cola_cantidad(c) == 3,
		"La cantidad es correcta después de encolar varios elementos");

	cola_destruir(c);
}

void cola_encolar_mantiene_cantidad_correcta()
{
	cola_t *c = cola_crear();
	int valores[10];
	for (int i = 0; i < 10; i++)
		valores[i] = i;

	bool ok = true;
	for (int i = 0; i < 10; i++) {
		if (!cola_encolar(c, &valores[i])) {
			ok = false;
			break;
		}
	}
	pa2m_afirmar(ok, "Puedo encolar 10 elementos correctamente");
	pa2m_afirmar(cola_cantidad(c) == 10,
		     "La cantidad coincide con los elementos encolados");

	cola_destruir(c);
}

void cola_encolar_preserva_orden()
{
	cola_t *c = cola_crear();
	int v1 = 100, v2 = 200, v3 = 300;

	cola_encolar(c, &v1);
	cola_encolar(c, &v2);
	cola_encolar(c, &v3);

	pa2m_afirmar(cola_ver_primero(c) == &v1,
		     "El primero es siempre el primero encolado");

	cola_desencolar(c);
	pa2m_afirmar(cola_ver_primero(c) == &v2,
		     "El primero cambia al segundo después de desencolar");

	cola_desencolar(c);
	pa2m_afirmar(cola_ver_primero(c) == &v3,
		     "El primero cambia al tercero después de desencolar");

	cola_destruir(c);
}

void cola_encolar_encola_elemento_null()
{
	cola_t *c = cola_crear();

	pa2m_afirmar(cola_encolar(c, NULL),
		     "cola_encolar con elemento NULL devuelve NULL");
	pa2m_afirmar(cola_cantidad(c) == 1,
		     "La cantidad aumenta al encolar un elemento NULL");

	cola_destruir(c);
}

void cola_encolar_no_encola_con_cola_nula()
{
	int valor = 5;
	pa2m_afirmar(!cola_encolar(NULL, &valor),
		     "cola_encolar con cola NULL devuelve NULL");
}

void pruebas_cola_encolar()
{
	pa2m_nuevo_grupo("cola_encolar parametros validos");
	cola_encolar_un_elemento();
	cola_encolar_encola_muchos_elementos();
	cola_encolar_mantiene_cantidad_correcta();
	cola_encolar_preserva_orden();

	pa2m_nuevo_grupo("cola_encolar parametros invalidos");
	cola_encolar_encola_elemento_null();
	cola_encolar_no_encola_con_cola_nula();
}

void cola_desencolar_desencola_un_elemento()
{
	cola_t *c = cola_crear();
	int valor = 42;

	cola_encolar(c, &valor);

	void *desencolado = cola_desencolar(c);
	pa2m_afirmar(
		desencolado == &valor,
		"cola_desencolar devuelve el mismo puntero que fue encolado");

	pa2m_afirmar(
		cola_cantidad(c) == 0,
		"La cola queda vacía después de desencolar el único elemento");

	cola_destruir(c);
}

void cola_desencolar_desencola_muchos_elementos()
{
	cola_t *c = cola_crear();
	int v1 = 1, v2 = 2, v3 = 3;

	cola_encolar(c, &v1);
	cola_encolar(c, &v2);
	cola_encolar(c, &v3);

	void *e1 = cola_desencolar(c);
	pa2m_afirmar(
		e1 == &v1,
		"cola_desencolar devuelve el primer puntero encolado (FIFO)");

	void *e2 = cola_desencolar(c);
	pa2m_afirmar(e2 == &v2,
		     "cola_desencolar devuelve el segundo puntero encolado");

	void *e3 = cola_desencolar(c);
	pa2m_afirmar(e3 == &v3,
		     "cola_desencolar devuelve el tercer puntero encolado");

	pa2m_afirmar(
		cola_cantidad(c) == 0,
		"La cola queda vacía después de desencolar todos los elementos");

	cola_destruir(c);
}

void cola_desencolar_desencola_cola_vacia()
{
	cola_t *c = cola_crear();

	pa2m_afirmar(cola_desencolar(c) == NULL,
		     "cola_desencolar en cola vacía devuelve NULL");

	cola_destruir(c);
}

void cola_desencolar_cola_nula()
{
	pa2m_afirmar(cola_desencolar(NULL) == NULL,
		     "cola_desencolar con cola NULL devuelve NULL");
}

void pruebas_cola_desencolar()
{
	pa2m_nuevo_grupo("cola_desencolar parametros validos");
	cola_desencolar_desencola_un_elemento();
	cola_desencolar_desencola_muchos_elementos();
	cola_desencolar_desencola_cola_vacia();

	pa2m_nuevo_grupo("cola_desencolar parametros invalidos");
	cola_desencolar_cola_nula();
}

void cola_ver_primero_cola_vacia_devuelve_null()
{
	cola_t *c = cola_crear();

	pa2m_afirmar(cola_ver_primero(c) == NULL,
		     "cola_ver_primero en cola vacía devuelve NULL");

	cola_destruir(c);
}

void cola_ver_primero_funciona_al_sacar_elementos()
{
	cola_t *c = cola_crear();
	int v1 = 11, v2 = 22, v3 = 33;

	cola_encolar(c, &v1);
	cola_encolar(c, &v2);
	cola_encolar(c, &v3);

	pa2m_afirmar(cola_ver_primero(c) == &v1,
		     "cola_ver_primero ve el primer elemento encolado");

	cola_desencolar(c);
	pa2m_afirmar(cola_ver_primero(c) == &v2,
		     "cola_ver_primero ve el nuevo primero tras un desencolar");

	cola_desencolar(c);
	pa2m_afirmar(
		cola_ver_primero(c) == &v3,
		"cola_ver_primero ve el último elemento cuando queda uno solo");

	cola_destruir(c);
}

void cola_ver_primero_ve_elemento_correcto()
{
	cola_t *c = cola_crear();
	int v1 = 5, v2 = 10;

	cola_encolar(c, &v1);
	cola_encolar(c, &v2);

	pa2m_afirmar(
		cola_ver_primero(c) == &v1,
		"cola_ver_primero devuelve siempre el primero (sin desencolar)");

	// verificamos que no se haya modificado la cola
	pa2m_afirmar(cola_cantidad(c) == 2,
		     "cola_ver_primero no altera la cantidad de elementos");

	cola_destruir(c);
}

void cola_ver_primero_cola_nula_devuelve_null()
{
	pa2m_afirmar(cola_ver_primero(NULL) == NULL,
		     "cola_ver_primero con cola NULL devuelve NULL");
}

void pruebas_cola_ver_primero()
{
	pa2m_nuevo_grupo("cola_ver_primero parametros validos");
	cola_ver_primero_cola_vacia_devuelve_null();
	cola_ver_primero_funciona_al_sacar_elementos();
	cola_ver_primero_ve_elemento_correcto();

	pa2m_nuevo_grupo("cola_ver_primero parametros invalidos");
	cola_ver_primero_cola_nula_devuelve_null();
}

void cola_cantidad_cola_vacia_devuelve_cero()
{
	cola_t *c = cola_crear();

	pa2m_afirmar(cola_cantidad(c) == 0,
		     "cola_cantidad en cola vacía devuelve 0");

	cola_destruir(c);
}

void cola_cantidad_cola_con_muchos_elementos_cuenta_correctamente()
{
	cola_t *c = cola_crear();
	int v1 = 1, v2 = 2, v3 = 3;

	cola_encolar(c, &v1);
	cola_encolar(c, &v2);
	cola_encolar(c, &v3);

	pa2m_afirmar(cola_cantidad(c) == 3,
		     "cola_cantidad encola 3 elementos y devuelve 3");

	cola_destruir(c);
}

void cola_cantidad_cuenta_bien_al_sacar_elementos()
{
	cola_t *c = cola_crear();
	int v1 = 7, v2 = 8;

	cola_encolar(c, &v1);
	cola_encolar(c, &v2);

	pa2m_afirmar(cola_cantidad(c) == 2,
		     "cola_cantidad devuelve 2 después de encolar 2 elementos");

	cola_desencolar(c);
	pa2m_afirmar(
		cola_cantidad(c) == 1,
		"cola_cantidad devuelve 1 después de desencolar un elemento");

	cola_desencolar(c);
	pa2m_afirmar(cola_cantidad(c) == 0,
		     "cola_cantidad devuelve 0 cuando la cola queda vacía");

	cola_destruir(c);
}

void cola_cantidad_cola_nula_devuelve_cero()
{
	pa2m_afirmar(cola_cantidad(NULL) == 0,
		     "cola_cantidad con cola NULL devuelve 0");
}

void pruebas_cola_cantidad()
{
	pa2m_nuevo_grupo("cola_cantidad parametros validos");
	cola_cantidad_cola_vacia_devuelve_cero();
	cola_cantidad_cola_con_muchos_elementos_cuenta_correctamente();
	cola_cantidad_cuenta_bien_al_sacar_elementos();

	pa2m_nuevo_grupo("cola_cantidad parametros invalidos");
	cola_cantidad_cola_nula_devuelve_cero();
}

void cola_destruir_cola_vacia()
{
	cola_t *c = cola_crear();

	cola_destruir(c);

	pa2m_afirmar(true, "cola_destruir destruye una cola vacía sin errores");
}

void cola_destruir_cola_con_elementos()
{
	cola_t *c = cola_crear();
	int v1 = 10, v2 = 20;

	cola_encolar(c, &v1);
	cola_encolar(c, &v2);

	cola_destruir(c);

	pa2m_afirmar(
		true,
		"cola_destruir destruye una cola con elementos sin errores");
}

void cola_destruir_cola_null()
{
	cola_destruir(NULL);

	pa2m_afirmar(
		true,
		"cola_destruir con cola NULL no hace nada y funciona correctamente");
}

void pruebas_cola_destruir()
{
	pa2m_nuevo_grupo("cola_destruir parametros validos");
	cola_destruir_cola_vacia();
	cola_destruir_cola_con_elementos();

	pa2m_nuevo_grupo("cola_destruir parametros invalidos");
	cola_destruir_cola_null();
}

void correr_pruebas_cola()
{
	pa2m_nuevo_grupo("Pruebas solo cola");
	pruebas_cola_crear();
	pruebas_cola_encolar();
	pruebas_cola_desencolar();
	pruebas_cola_ver_primero();
	pruebas_cola_cantidad();
	pruebas_cola_destruir();
}

// ===========================

void pila_crear_crea_pila_vacia()
{
	pila_t *p = pila_crear();

	pa2m_afirmar(p != NULL, "pila_crear crea una pila correctamente");
	pa2m_afirmar(pila_cantidad(p) == 0, "pila_crear crea una pila vacía");

	pila_destruir(p);
}

void pruebas_pila_crear()
{
	pa2m_nuevo_grupo("pila_crear parametros validos");
	pila_crear_crea_pila_vacia();
}

void pila_apilar_un_elemento()
{
	pila_t *p = pila_crear();
	int valor = 42;

	pa2m_afirmar(pila_apilar(p, &valor),
		     "pila_apilar apila un elemento correctamente");
	pa2m_afirmar(pila_cantidad(p) == 1,
		     "La pila tiene 1 elemento tras apilar");
	pa2m_afirmar(pila_ver_primero(p) == &valor,
		     "pila_ver_primero devuelve el último elemento apilado");

	pila_destruir(p);
}

void pila_apilar_muchos_elementos()
{
	pila_t *p = pila_crear();
	int v1 = 1, v2 = 2, v3 = 3;

	pa2m_afirmar(pila_apilar(p, &v1), "Elemento %i apilado correctamente",
		     v1);
	pa2m_afirmar(pila_apilar(p, &v2), "Elemento %i apilado correctamente",
		     v2);
	pa2m_afirmar(pila_apilar(p, &v3), "Elemento %i apilado correctamente",
		     v3);

	pa2m_afirmar(
		pila_cantidad(p) == 3,
		"pila_apilar aumenta la cantidad correctamente con muchos elementos");
	pa2m_afirmar(pila_ver_primero(p) == &v3,
		     "pila_ver_primero devuelve el último apilado (LIFO)");

	pila_destruir(p);
}

void pila_apilar_elemento_null()
{
	pila_t *p = pila_crear();

	pa2m_afirmar(pila_apilar(p, NULL),
		     "pila_apilar con elemento NULL devuelve NULL");
	pa2m_afirmar(pila_cantidad(p) == 1, "La pila cuenta el elemento NULL");

	pila_destruir(p);
}

void pila_apilar_pila_null()
{
	int valor = 7;
	pa2m_afirmar(!pila_apilar(NULL, &valor),
		     "pila_apilar con pila NULL devuelve NULL");
}

void pruebas_pila_apilar()
{
	pa2m_nuevo_grupo("pila_apilar parametros validos");
	pila_apilar_un_elemento();
	pila_apilar_muchos_elementos();

	pa2m_nuevo_grupo("pila_apilar parametros invalidos");
	pila_apilar_elemento_null();
	pila_apilar_pila_null();
}

void pila_desapilar_un_elemento()
{
	pila_t *p = pila_crear();
	int valor = 10;

	pila_apilar(p, &valor);

	void *desapilado = pila_desapilar(p);
	pa2m_afirmar(desapilado == &valor,
		     "pila_desapilar devuelve el mismo puntero apilado");
	pa2m_afirmar(pila_cantidad(p) == 0,
		     "La pila queda vacía tras desapilar el único elemento");

	pila_destruir(p);
}

void pila_desapilar_muchos_elementos()
{
	pila_t *p = pila_crear();
	int v1 = 1, v2 = 2, v3 = 3;

	pila_apilar(p, &v1);
	pila_apilar(p, &v2);
	pila_apilar(p, &v3);

	pa2m_afirmar(pila_desapilar(p) == &v3,
		     "pila_desapilar devuelve el último apilado (LIFO)");
	pa2m_afirmar(pila_desapilar(p) == &v2,
		     "pila_desapilar devuelve el segundo último apilado");
	pa2m_afirmar(pila_desapilar(p) == &v1,
		     "pila_desapilar devuelve el primero apilado");
	pa2m_afirmar(pila_cantidad(p) == 0,
		     "La pila queda vacía después de desapilar todo");

	pila_destruir(p);
}

void pila_desapilar_pila_vacia()
{
	pila_t *p = pila_crear();

	pa2m_afirmar(pila_desapilar(p) == NULL,
		     "pila_desapilar en pila vacía devuelve NULL");

	pila_destruir(p);
}

void pila_desapilar_pila_null()
{
	pa2m_afirmar(pila_desapilar(NULL) == NULL,
		     "pila_desapilar con pila NULL devuelve NULL");
}

void pruebas_pila_desapilar()
{
	pa2m_nuevo_grupo("pila_desapilar parametros validos");
	pila_desapilar_un_elemento();
	pila_desapilar_muchos_elementos();
	pila_desapilar_pila_vacia();

	pa2m_nuevo_grupo("pila_desapilar parametros invalidos");
	pila_desapilar_pila_null();
}

void pila_ver_primero_funciona_correctamente()
{
	pila_t *p = pila_crear();
	int v1 = 5, v2 = 10;

	pila_apilar(p, &v1);
	pila_apilar(p, &v2);

	pa2m_afirmar(pila_ver_primero(p) == &v2,
		     "pila_ver_primero devuelve el último elemento apilado");
	pa2m_afirmar(pila_cantidad(p) == 2,
		     "pila_ver_primero no altera la cantidad");

	pila_destruir(p);
}

void pila_ver_primero_pila_vacia()
{
	pila_t *p = pila_crear();

	pa2m_afirmar(pila_ver_primero(p) == NULL,
		     "pila_ver_primero en pila vacía devuelve NULL");

	pila_destruir(p);
}

void pila_ver_primero_pila_null()
{
	pa2m_afirmar(pila_ver_primero(NULL) == NULL,
		     "pila_ver_primero con pila NULL devuelve NULL");
}

void pruebas_pila_ver_primero()
{
	pa2m_nuevo_grupo("pila_ver_primero parametros validos");
	pila_ver_primero_funciona_correctamente();
	pila_ver_primero_pila_vacia();

	pa2m_nuevo_grupo("pila_ver_primero parametros invalidos");
	pila_ver_primero_pila_null();
}

void pila_cantidad_pila_vacia_devuelve_cero()
{
	pila_t *p = pila_crear();

	pa2m_afirmar(pila_cantidad(p) == 0,
		     "pila_cantidad en pila vacía devuelve 0");

	pila_destruir(p);
}

void pila_cantidad_con_elementos()
{
	pila_t *p = pila_crear();
	int v1 = 1, v2 = 2;

	pila_apilar(p, &v1);
	pila_apilar(p, &v2);

	pa2m_afirmar(
		pila_cantidad(p) == 2,
		"pila_cantidad devuelve la cantidad correcta tras apilar elementos");

	pila_destruir(p);
}

void pila_cantidad_cambia_al_desapilar()
{
	pila_t *p = pila_crear();
	int v = 7;

	pila_apilar(p, &v);
	pa2m_afirmar(pila_cantidad(p) == 1,
		     "pila_cantidad devuelve 1 tras apilar un elemento");

	pila_desapilar(p);
	pa2m_afirmar(
		pila_cantidad(p) == 0,
		"pila_cantidad devuelve 0 tras desapilar el único elemento");

	pila_destruir(p);
}

void pila_cantidad_pila_null()
{
	pa2m_afirmar(pila_cantidad(NULL) == 0,
		     "pila_cantidad con pila NULL devuelve 0");
}

void pruebas_pila_cantidad()
{
	pa2m_nuevo_grupo("pila_cantidad parametros validos");
	pila_cantidad_pila_vacia_devuelve_cero();
	pila_cantidad_con_elementos();
	pila_cantidad_cambia_al_desapilar();

	pa2m_nuevo_grupo("pila_cantidad parametros invalidos");
	pila_cantidad_pila_null();
}

void pila_destruir_pila_vacia()
{
	pila_t *p = pila_crear();
	pila_destruir(p);

	pa2m_afirmar(true, "pila_destruir destruye una pila vacía sin errores");
}

void pila_destruir_pila_con_elementos()
{
	pila_t *p = pila_crear();
	int v1 = 11, v2 = 22;

	pila_apilar(p, &v1);
	pila_apilar(p, &v2);

	pila_destruir(p);

	pa2m_afirmar(
		true,
		"pila_destruir destruye una pila con elementos sin errores");
}

void pila_destruir_pila_null()
{
	pila_destruir(NULL);

	pa2m_afirmar(
		true,
		"pila_destruir con pila NULL no hace nada y funciona correctamente");
}

void pruebas_pila_destruir()
{
	pa2m_nuevo_grupo("pila_destruir parametros validos");
	pila_destruir_pila_vacia();
	pila_destruir_pila_con_elementos();

	pa2m_nuevo_grupo("pila_destruir parametros invalidos");
	pila_destruir_pila_null();
}

void correr_pruebas_pila()
{
	pa2m_nuevo_grupo("Pruebas solo pila");
	pruebas_pila_crear();
	pruebas_pila_apilar();
	pruebas_pila_desapilar();
	pruebas_pila_ver_primero();
	pruebas_pila_cantidad();
	pruebas_pila_destruir();
}

int main()
{
	pa2m_nuevo_grupo("============== Pruebas lista ===============");
	correr_pruebas_lista();

	pa2m_nuevo_grupo("============== Pruebas pila y cola ===============");
	correr_pruebas_pila();
	correr_pruebas_cola();

	return pa2m_mostrar_reporte();
}