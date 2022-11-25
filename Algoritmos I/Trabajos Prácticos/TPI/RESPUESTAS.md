% Contesten aquí la pregunta sobre complejidad

### Jugadas del tipo nXn:
Seria como un tablero pero con las posiciones jugadas y no jugadas. 
En el tablero ya sabemos donde se ubica cada bomba, en jugadas no.

### JugarPlus:

"JugarPlus" es de complejidad O(n^3) actualmente, la mayor complejidad actualmente es checkear las banderitas (lineal en
la cantidad de banderitas) y checkear las jugadas ya realizadas (lineal en la cantidad de jugadas realizadas).

Teniendo una matriz de las jugadas la complejidad de checkear las jugadas baja a constante (acceso aleatorio a una matriz)

Asi que `JugarPlus` quedaría O(n^3)

### sugerirAutomatico121:

sugerirAutomatico121 es de complejidad O(n^3) porque hay que recorrer todo el tablero y en cada iteracion hay que checkear las
jugadas (O(n)) y las banderitas (O(n)).

Teniendo la matriz la complejidad de las checkear las jugadas se transforma en O(1) (acceso aleatorio a una matriz) pero aun asi
tenemos que checkear las banderitas por lo que `sugerirAutomatico121` seguiria siendo O(n^3)
