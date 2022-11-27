### : ¿qué pasaría si la estructura jugadas fuera una matriz conteniendo en cada posición la 
### cantidad de minas adyacentes (o -1 si la casilla no fue jugada)?
Haria nuestro programa mas rapido en general. En vez de buscar en la lista de jugadas, simplemente accedemos a la matriz y vemos si el valor que nos devuelve es un numero entre 0 y 8 o -1 en caso de no haberse jugado. Mas que nada afecta a la funcion "perteneceAJugada()", en vez de iterar n*n veces en el peor caso, simplemente accederiamos a la matriz que es una operacion constante.

### COMPLEJIDAD CON JUGADAS NORMAL:

## JugarPlus():
O(n^4)
En el peor caso recorremos toda la matriz por lo cual la cantidad de candidatos totales es igual a n^2. Luego se tiene que buscar si una jugada pertenece a la lista de jugadas, en el peor caso esta jugada estará al final de la lista. La lista es de tamaño n^2 en el peor caso porque representan 1 posicion jugada en un tablero de tamaño n*n por lo que "perteneceAJugadas()" será de O(n^2).
Para cada candidato debo recorrer "perteneceAJugadas()", entonces en el peor caso tengo n^2 candidatos y una lista con n^2 jugadas.
Por lo tanto la complejidad total es de O(n^4). 

## sugerirAutomatico121():
O(n^4)
Debemos ver si hay una posicion sugerible, para esto buscamos en el tablero 3 posiciones que cumplen la estrategia 121
pero primero debemos ver que estas posiciones no sean ni jugar ni banderita, por lo que lo vuelve de complejidad O(n^4)
pues iteramos n*n veces sobre la matriz y luego n^2 veces sobre jugadas y banderitas ya que en el peor caso, buscamos hasta final de la lista.


### COMPLEJIDAD CON JUGADAS = MATRIZ CON MINASADYACENTES ó -1 SI NO SE JUGÓ:

## JugarPlus():
O(n^2)
"JugarPlus" es de complejidad O(n^2) cuando jugadas es una matriz.
Teniendo una matriz de las jugadas la complejidad de checkear las jugadas baja a constante (solo accedemos a la matriz y vemos si es jugada o no).
Supongamos que clickeamos en la casilla t[0][0] y la única bomba se encuentra en la posicion t[n][n]. Entonces la cantidad de candidatos es igual a 
n*n - 1. Luego para ver si mi candidato no fue jugado, deberiamos buscarlo en "Jugadas". Si "Jugadas" es una matriz, simplemente
accedemos a la posicion y vemos si nos devuelve las minas adyacentes o nos devuelve '-1' en caso de no haber sido jugado, pero como sabemos, acceder
a una matriz es de complejidad constante.

Asi que `JugarPlus` quedaría O(n^2)

## sugerirAutomatico121():
O(n^4)
En "esAdyacente121" debemos verificar que existe una jugada 121 vertical u horizontal, para eso revisamos si 3 posiciones pertenecen a jugadas. 
Si "Jugadas" es una matriz, entonces revisar estas 3 posiciones es de complejidad constante pues solo accedemos a la matriz y revisamos su valor.
Esto implica que "esAdyacente121()" es de complejidad constante. 
"hayPosicionSugerible()"  itera sobre todo el tablero buscando si la posicion actual tiene "adyacente121" que es constante pero tambien busca que la posicion no pertenezca a jugadas o a banderitas. Hay un problema, que todas las posiciones en el tablero sean banderitas. En JugarPlus no nos afectaba porque si hay una banderitas, no se 'expande' "JugarPlus". Ahora, si todas las posiciones son banderitas, "hayPosicionSugerible()" itera sobre todo el tablero, o sea nxn, y luego busca en la lista de banderitas si esa posicion pertenece. En el peor caso la posicion está al final de la lista, una lista de tamaño nxn. Entonces "hayPosicionSugerible()" es de complejidad O(n^4). Entonces "sugerirAutomatico121()" es de complejidad O(n^4).
