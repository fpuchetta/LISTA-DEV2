<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP1 LECTURA DE ARCHIVOS

## Alumno: Puchetta Federico - 112853 - fpuchetta@fi.uba.ar

- Para compilar junto a main:

```bash
make tdas
```

- Para compilar junto a pruebas de usuario:

```bash
make pruebas
```

- Para ejecutar:

```bash
./tdas <archivo> <comandos> <modo> <argumento>
```

- Para limpiar archivos:

```bash
make clean
```

- Para aplicar format:

```bash
make format
```

---

##  Eleccion de estructuras:

Para la implementacion del TDA lista, opte por crear el tda `nodo_t` el cual es el que contendra el dato y la conexion con el siguiente nodo, logrando asi formar la conexion entre datos.

Luego, en `lista_t` opte por utilizar dos punteros, uno que apunta al primer nodo (principio), y otro que apunta al ultimo (final), los cuales sirven para cumplir con las complejidades pedidas en el enunciado (pila y cola). Luego, el campo `cantidad` sirve para mantener un recuento de elementos insertados en la lista y facilitar la implementacion de algunas funciones

Luego, para lograr una mejor modularizacion de las funciones a desarrollar, opte por crear el struct `comparador_ctx_t`, el cual me permite reutilizar la funcion `lista_con_cada_elemento` para realizar la busqueda por criterio de usuario, ya que permite encapsular una funcion de comparacion, un flag de encontrado y el elemento a comparar para enviarlo como **extra** a la funcion usada.

El iterador `lista_iterador_t` simplemente cuenta con un puntero a nodo_t el cual representa el nodo actual de la iteracion.

Por ultimo, los TDA `pila_t` y `cola_t` fueron implementados, como pide el enunciado, mediante la misma `lista_t`.



Una vez dispuesto en memoria, el tda lista_t se veria asi:

<div align="center">
<img src="img/lista_memoria.svg">
</div>

Los tda pila_t y cola_t se verian asi:

<div align="center">
<img src="img/lista_y_cola.svg">
</div>

## Funcionamiento: (main)

El archivo pedido `main.c` al ser ejecutado primero garantiza que el programa fue invocado con la cantidad de argumentos exactos para la funcionalidad de la busqueda. Luego, lee el archivo y es guardado en la estructura `tp1_t` para luego ser recorrido cada elemento del tp con `tp1_con_cada_pokemon` y llamar a un cb propio encargado de meter cada pokemon en la lista.

Finalmente, se analiza que comando se debe ejecutar y se realiza la busqueda correspondiente.

---

## Complejidades de primitivas:

### Lista:

#### Funcion `lista_t *lista_crear()`:

Se encarga de reservar la memoria necesaria en el heap para un `lista_t`, por lo cual **su complejidad computacional es O(1)**.

#### Funcion `bool lista_vacia(lista_t *lista)`:

**La complejidad de esta funcion resulta constante O(1)** debido al campo `cantidad` de mi lista_t.

#### Funcion `size_t lista_cantidad(lista_t *lista)`:

**la complejidad de esta funcion resulta constante O(1)** por el mismo motivo que la funcion anterior.

#### Funcion `bool lista_agregar(lista_t *lista, void *dato)`:

La funcion se encarga de agregar un dato al final de la lista, posee **una complejidad computacional O(1)** debido al puntero implementado al final de la lista, lo cual permite que no se deban recorrer los N nodos de la lista para llegar al final de la misma.

#### Funcion `bool lista_insertar(lista_t *lista, void *elemento, size_t posicion)`:

La funcion se encarga de agregar un dato en una posicion arbitraria pasada por parametro, por lo cual, para lograr esto se debe llegar al nodo anterior de la posicion buscada **logrando una complejidad computacional O(n) tomando como variable de analisis la cantidad de nodos** ya que se deben recorrer los N-1 nodos hasta llegar al lugar buscado.

El flujo de este proceso de insercion como el de agregar se puede diagramar de la siguiente forma:

<div align="center">
<img src="img/lista_agregar_insertar.svg">
</div>

#### Funcion `void *lista_eliminar_elemento(lista_t *lista, size_t posicion)`:

Esta funcion, encargada de eliminar un elemento, al igual que la anterior se toma como variable de analisis **la cantidad de nodos (N)**, logrando de esta forma que **la complejidad computacional de la funcion sea O(n)** debido a que nuevamente se debe iterar hasta n-1 para liberar la memoria del elemento pedido.

#### Funcion `int lista_buscar_posicion(lista_t *lista, void *elemento, int (*comparador)(const void *, const void *))`:

La funcion encargada de buscar un elemento mediante un comparador, toma como variable de analisis la cantidad de nodos nuevamente, por lo cual, al tener que realizar un acceso en cada nodo hasta encontrar el buscado mediante el comparador pasado por parametro **se habla de una complejidad computacional O(n)**. En esta funcion, opte por implementarla mediante la funcion `lista_con_cada_elemento` y el struct explicado previamente para lograr una mejor modularizacion del codigo.

#### Funcion `void *lista_buscar_elemento(lista_t *lista, size_t posicion)`:

Esta funcion es similar a la anterior, simplemente que esta no necesita comparador ya que se itera hasta la posicion pasada por parametro, por lo cual, nuevamente se habla de **una complejidad computacional O(n)** si consideramos que nuestra lista tiene N elementos.

Los flujos de este proceso de busqueda y del anterior se pueden diagramar de la siguiente forma:

<div align="center">
<img src="img/lista_buscar_flujo.svg">
</div>

#### Funcion `size_t lista_con_cada_elemento(lista_t *lista, bool (*f)(void *, void *), void *extra)`:

Esta funcion se encarga de **recorrer toda la lista**, y por cada elemento aplicarle una funcion pasada por parametro. Por esto mismo, y tomando como variable de analisis a la cantidad de nodos, se considera que **la funcion tiene una complejidad computacional O(n)**.

#### Funciones `void lista_destruir(lista_t *lista)` y `void lista_destruir_todo(lista_t *lista, void (*destructor)(void *))`:

Las funciones encargadas de destruir la lista son practicamente iguales, por lo cual **comparten sus complejidades las cuales son O(n)** debido a que se deben liberar TODOS LOS NODOS.

#### Funciones de `lista_iterador`:

Las funciones del iterador **poseen todas complejidades computacionales constantes O(1)** debido a como esta implementado, solo avanzan un nodo a la vez. La complejidad se torna lineal en caso de aplicarlo para recorrer TODA la lista, pero eso no depende de las primitivas.

#### Funciones `cola_t` y `pila_t`:

**Todas las funciones** tanto de `cola_t` como de `pila_t` (sacando de lado las destructoras), **poseen una complejidad computacional O(1)**. Esto es asi, debido a que ambos tdas estan implementados con la implementacion de `lista_t`, pero con las restricciones de los respectivos TDA.

Por el lado de la pila, en cada funcion se llama a su correspondiente de lista pero siempre utilizando el puntero de `lista_t` que apunta al principio de la lista, logrando de esta forma que siempre tengan complejidades constantes.

Por el lado de la cola, a su vez se utiliza un campo de `lista_t` y sus funciones correspondientes, pero en esta ocasion se utilizan **ambos punteros**, se decide que el `principio` sera por donde salen los elementos (logrando la complejidad constante) y el `final` sera por donde entren (logrando nuevamente la complejidad constante).

Finalmente, ambas funciones de destruccion al estar implementadas con `lista_destruir` adoptan la complejidad de dicha funcion, **tornandose con complejidad computacional O(n)**.

Los diagramas correspondientes ya fueron mostrados en los respectivos analisis de cada funcion de `lista_t`, en caso de `pila_apilar` seria la insercion en la posicion cero. En caso de `cola_encolar` seria la insercion al final de la lista.

---

## Respuestas a las preguntas teoricas

- Explicar que es una lista, lista enlazada y lista doblemente enlazada.
- Explicar las caracteristicas de cada una.
- Explicar las diferencias internas de implementacion.
- Explicar ventajas y desventajas de cada una, si existen.


Una lista es un TDA que agrupa elementos ordenados en los que cada uno (excepto el primero y el ultimo) tiene un **predecesor** y un **sucesor**. Puede implementarse de distintas formas, por ejemplo, como **lista secuencial** (usando un arreglo) o como **lista enlazada** (usando nodos que contienen referencias a otros nodos).

Una lista enlazada es una implementacion particular del TDA lista que se construye a partir de nodos. Cada nodo almacena un elemento y un puntero al siguiente nodo, lo que permite mantener la secuencia logica de los elementos sin necesidad de que esten almacenados de manera contigua en memoria. De esta forma, el orden de la lista esta definido por los enlaces entre nodos, no por la ubicacion fisica de los datos.

Una lista simplemente enlazada se puede ver asi:

<div align="center">
<img src="img/lista_simple_enlazada.svg">
</div>

En una lista doblemente enlazada, cada nodo incorpora dos punteros: uno al nodo siguiente y otro al nodo anterior. Esto permite recorrer la lista en ambos sentidos (hacia adelante y hacia atras). La contrapartida es que este tipo de implementacion requiere mas memoria que una lista simplemente enlazada, ya que cada nodo debe guardar dos referencias en lugar de una. Sin embargo, facilita operaciones como la eliminacion de nodos sin necesidad de conocer el predecesor de antemano.

Una lista doblemente enlazada se puede ver asi:

<div align="center">
<img src="img/lista_doble_enlazada.svg">
</div>


En ambas implementaciones (simple y doblemente enlazada), los elementos pueden estar almacenados en cualquier lugar de la memoria, siempre que los punteros esten correctamente definidos. Esta flexibilidad evita la necesidad de bloques de memoria contiguos, pero tambien implica que no se dispone de acceso aleatorio como en un arreglo: para llegar a un elemento arbitrario es necesario recorrer la lista nodo a nodo, lo que se denomina acceso secuencial.

---

- Explicar que es una lista circular y de que maneras se puede implementar.

Una lista circular es otra variante del TDA lista.
Su particularidad es que el ultimo nodo no apunta a NULL, sino que enlaza nuevamente con el primer nodo, formando un ciclo que conecta el final con el comienzo.

Al igual que las listas tradicionales, puede implementarse con enlace simple o con enlace doble:

- En una lista circular simplemente enlazada, el ultimo nodo apunta al primero, lo que permite recorrer la lista desde el **final hacia el inicio**.

- En una lista circular doblemente enlazada, ademas de lo anterior, cada nodo conoce tambien a su predecesor, lo que habilita recorrerla en **ambos sentidos** sin importar el punto de partida.

Cabe destacar que, aunque la estructura sea circular, **la cantidad de elementos de la lista es la misma que tendria una lista no circular**; lo que cambia es la forma en que los nodos se conectan entre si.

Estas implementaciones se pueden ver asi:

<div align="center">
<img src="img/listas_circulares.svg">
</div>

---

- Explicar la diferencia de funcionamiento entre cola y pila.

Tanto la **pila** como la **cola** pueden entenderse como **listas con ciertas restricciones en su uso**.

Una pila sigue la regla **LIFO (Last In, First Out)**, lo que significa que el ultimo elemento en entrar sera el primero en salir. Todas las operaciones se realizan desde un unico extremo llamado tope, al cual se pueden insertar o eliminar elementos. Los elementos que quedan mas abajo en la pila permanecen inaccesibles hasta que se retiren los superiores.

La cual puede verse asi:

<div align="center">
<img src="img/pila.svg">
</div>


Por su parte, una cola respeta la regla **FIFO (First In, First Out)**: el primer elemento en entrar es tambien el primero en salir. En este caso, la insercion se realiza por un extremo (final de la cola) y la eliminacion por el otro (frente o cabecera), de manera que el acceso directo solo se tiene al primer elemento en la cola.

La cual puede verse asi:

<div align="center">
<img src="img/cola.svg">
</div>

---

- Explicar la diferencia entre un iterador interno y uno externo.


Un **iterador interno** es aquel cuya logica de recorrido esta **encapsulada** dentro de la propia implementacion del TDA. **El usuario no controla como se realiza la iteracion**, sino que simplemente recibe los elementos uno a uno hasta que se cumple una condicion de corte. En otras palabras, el manejo del recorrido queda “oculto” para el usuario.

En cambio, un **iterador externo** es un mecanismo diseñado para recorrer un TDA de manera mas flexible y controlada. Para lograrlo, se implementa un nuevo TDA (el iterador) que **conoce la estructura interna** de la coleccion y proporciona al usuario operaciones especificas para avanzar, retroceder o consultar elementos durante el recorrido. De esta forma, **el usuario tiene mayor control sobre la logica de iteracion** sin necesidad de conocer directamente la implementacion del TDA original.