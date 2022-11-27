//
// Este archivo contiene las definiciones de las funciones que implementan los ejercicios
//

#include <stdio.h>
#include <iostream>


#include "definiciones.h"
#include "ejercicios.h"
#include "auxiliares.h"


using namespace std;


/******++++**************************** EJERCICIO minasAdyacentes ***********+++***********************/

// O(1)
int minasAdyacentes(tablero& t, pos p) {  // O(1) + O(1) + O(1) + 3*( O(1) + O(1) + 3*( O(1) + O(1) + O(18) + O(2) + O(2) + O(2))) = O(243) = O(1)

    int res = 0;    // O(1)
    int i = -1;     // O(1)
    while(i <= 1){  // O(1) + 3*(linea 23 a 34)

        int j = -1;     // O(1)
        while(j <= 1){  // O(1) + 3*(linea 26 a linea 32)
            int p0 = p.first;   // O(1)
            int p1 = p.second;  // O(1)
            if(esAdyacenteValida(p0, p1, i, j, t) && (t[p0 + i][p1 + j])){  // O(15) + O(3) = O(18)
                res++;                                                         // O(2)
            }
            j++;                                                               // O(2)
        }
        i++;                                                                   // O(2)
    }
    return res;
}

// O(1), el tiempo es constante pues no revisamos ningun tipo de lista, sabemos exactamente cuanto va a tardar
// en ejecutar toda la funcion sin importar el tamaño de entrada.
// siempre chequeamos los mismos 9 elementos de la matriz.

/******++++**************************** EJERCICIO plantarBanderita ***********+++***********************/

// O(n^2)
void cambiarBanderita(tablero& t, jugadas& j, pos p, banderitas& b) { // O(n) + O(1) = O(n)
    if(!contienePosicionBanderita(p, b)){ // O(contienePosicionBanderita) = O(n^2)
        b.push_back(p);                      // O(1)
    }
    else{
        quitarPosicion(p, b);             // O(quitarPosicion) = O(n)
    }
}
// O(n^2), en el peor caso puede ser que la banderita pertenezca a la posicion y debamos sacarla, pero para saber si esta
// banderita pertenece, debemos iterar sobre nuestra lista actual de banderitas, en el peor caso esta en la posicion [n][n] de la matriz
// por lo que la lista seria de n*n elementos, el peor caso es O(n^2).
// Si la banderita está tenemos que iterar nuevamente por la lista para quitarla como se ve en "quitarPosicion()". El peor
// caso es cuando nuestra banderita esta en la ante-ultima posicion.


/******++++**************************** EJERCICIO perdio ***********+++***********************/

// O(n)
bool perdio(tablero& t, jugadas& j) { // O(2) + O(n) = O(n)
    bool res = false; // O(1)

    int i = 0;  // O(1)
    while(i < j.size()){    // O(1) + n*O(linea 60 a 63) = O(1) + O(n*4) = O(n)
        if(tieneUnaMina(t, j[i].first)) { // O(tieneUnaMina) + O(1) = O(1) + O(1) = O(1)
            res = true;                         // O(1)
        }
        i++;    // O(2)
    }

    return res;
}
// O(n)
// en este caso debemos ver si jugamos una posicion con mina. Debemos iterar sobre jugadas y ver si la posicion
// resulta estar sobre una posicion con mina. Como podemos ver el peor caso es que nuestra jugada perdida esté en la ultima
// posición de jugadas. Que es el caso ideal, pues es normal pedir en la pre-condición de una función que la partida
// no esté perdida.


/******++++**************************** EJERCICIO gano ***********+++***********************/

// O(n^3)
bool gano(tablero& t, jugadas& j) { // O(1) + O(1) + O(n^3) + O(n) + O(1) = O(n^3)
    bool gano = true; // O(1)

    int i = 0;  // O(1)
    while(i < t.size()){                  // O(1) + n*O(linea 76 a 85) = O(1) + n*O(1 + n^2 + 2) = O(n^3)
        int k = 0;                        // O(1)
        while(k < t.size()){              // O(1) + n*O(linea 78 a 84) = O(1) + O(n*(6+n)) = O(n^2)
            pos p = newPos(i, k);    // O(1) + O(newPos) = O(1) + O(1) = O(1)
            jugada nuevaJugada = {p, minasAdyacentes(t, p)};       // O(1) + O(minasAdyacentes) = O(1) + O(1) = O(1)
            if(!tieneUnaMina(t, p) &&                                   // O(tieneUnaMina) + O(1) = O(1) + O(1) = O(1)
               !perteneceAJugadas(nuevaJugada, j)) {             // O(perteneceAJugadas) = O(n)
                gano = false;   // O(1)
            }
            k++;    // O(2)
        }
        i++;        // O(2)
    }


    if (perdio(t, j)) { // O(perdio) = O(n)
        gano = false;   // O(1)
    }

    return gano;
}
// O(n^3)
// la idea de esta funcion es ir por cada posicion del tablero y chequear que si no tiene una mina y no pertenece a jugadas
// entonces todavia no se gano, la complejidad viene por parte de tablero que es una matriz cuadrada, luego para chequear si pertenece
// a jugadas debemos iterar sobre jugadas. El peor caso es cuando chequeamos la posicion nxn del tablero y la jugada se encuentra en
// la ultima posicion.


/******++++**************************** EJERCICIO jugarPlus ***********+++***********************/

//O(n^4)
void jugarPlus(tablero& t, banderitas& b, pos p, jugadas& j) { // O(5) + O(n^2) = O(n^2)

    vector<pos> candidatos = {};     // O(1)

    if(!tieneUnaMina(t, p)){        // O(1)
        candidatos.push_back(p);    // O(1)
    }

    j.push_back({p, minasAdyacentes(t, p)});    // O(1) + O(minasAdyacentes) = O(1) + O(1) = O(1)

    int i = 0;                                          // O(1)
    while (i < candidatos.size()) {                     // O(1) + n*O(linea 118 a 144) = O(n^4)

        if(minasAdyacentes(t, candidatos[i]) == 0){     // O(minasAdyacentes) + O(1) + O(1) = O(1) + O(1) + O(1) = O(3) = O(1)

            int x = -1;                                       // O(1)
            while(x <= 1){                                    // O(1) + 3*(linea 120 a 138) = O(1) + 3*O(1 + n) = O(n^4)
                int y = -1;                                   // O(1)
                while(y <= 1){                                // O(1) + 3*(linea 122 a 136) = O(1) + 3* O(14 + 2n) = O(n^3)
                    int p0 = candidatos[i].first;             // O(2)
                    int p1 = candidatos[i].second;            // O(2)
                    pos nuevoCandidato;
                    nuevoCandidato.first = p0 + x;            // O(2)
                    nuevoCandidato.second = p1 + y;           // O(2)
                    if(posicionValida(nuevoCandidato, t) && // O(posicionValida) + O(1) = O(1) + O(1) = O(2) = O(1)
                       !tieneUnaMina(t, nuevoCandidato) &&  // O(tieneUnaMina) + O(1) = O(1) + O(1) = O(2) = O(1)
                       !contienePosicionBanderita(nuevoCandidato, b) &&      // O(n)
                       !perteneceAJugadas({nuevoCandidato, minasAdyacentes(t, nuevoCandidato)}, j))     // O(n^2) 
                    {
                        candidatos.push_back(nuevoCandidato); // O(1)
                        j.push_back({nuevoCandidato, minasAdyacentes(t, nuevoCandidato)}); // O(1) + O(minasAdyacentes) = O(1) + O(1) = O(1)
                    }
                    y++;    // O(2)
                }
                x++;    // O(2)
            }
        }
        i++;    // O(2)
    }
}
// O(n^4)
// En el peor caso recorremos toda la matriz por lo que la cantidad de candidatos total es igual a n^2. Luego se tiene que buscar si una jugada pertenece
// a la lista de jugadas, en el peor caso esta jugada estará al final de la lista. La lista es de tamaño n^2 (cantidad de posiciones jugables) por lo que "perteneceAJugadas()" EN ESTE CASO
// será de n^2.
// Para cada candidato debo recorrer "perteneceAJugadas()", entonces en el peor caso tengo n^2 candidatos y una lista con n^2 jugadas.
// por lo tanto la complejidad total es de O(n^4) 


/******++++**************************** EJERCICIO sugerirAutomatico121 ***********+++***********************/

// O(n^4)
bool sugerirAutomatico121(tablero& t, banderitas& b, jugadas& j, pos& p) {
    return(hayPosicionSugerible(j, b, t, p)); // O(n^4)
}
// O(n^4)
// Debemos ver si hay una posicion sugerible, para esto buscamos en el tablero 3 posiciones que cumplen la estrategia 121
// pero primero debemos ver que estas posiciones no sean ni jugar ni banderita, por lo que lo vuelve de complejidad O(n^4)
// pues iteramos n*n veces sobre la matriz y luego n^2 veces sobre jugadas ya que en el peor caso, buscamos al final de la lista.
















