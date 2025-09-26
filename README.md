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

Por ultimo,

Una vez dispuesto en memoria, el tda lista_t se veria asi:

<div align="center">
<img src="img/lista_memoria.svg">
</div>



### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
Incluír acá las respuestas a las preguntas del enunciado (si aplica).
