//
// Este archivo contiene las definiciones de las funciones auxiliares
// que ustedes necesiten implementar. Tienen que coincidir con las 
// declaraciones de auxiliares.h
//

#include <iostream>

#include "definiciones.h"
#include "ejercicios.h"
#include "auxiliares.h"

using namespace std;

/******++++**************************** EJERCICIO minasAdyacentes ***********+++***********************/
/*
    -Una bomba no puede estar en nuestra Posicion.
    -Mi mina adyacente, está dentro del tablero?.
*/

// O(1)
bool esAdyacenteValida(int p0, int p1, int i, int j, tablero& t){ // O(5) + O(5) + O(5) = O(15) = O(1)
    return(coordenadaValida(p0, i, t) && coordenadaValida(p1, j, t) && (i != 0 || j != 0));
}

// O(1)
bool coordenadaValida(int p, int x, tablero& t){
    return (p + x < t.size() && p + x >= 0); // O(5) = O(1)
}

/******++++**************************** EJERCICIO cambiarBanderita ***********+++***********************/

// O(n^2)
bool contienePosicionBanderita(pos p, banderitas& b){ // O(1) + O(1) + O(1) + n * O( O(1) + O(1) + O(2)) = O(4n+3) = O(n^2)

    bool pertenece = false;     // O(1)

    int i = 0;                  // O(1)
    while(i < b.size()){        // O(1) + n*O(linea 40 a 43)
        if(b[i] == p){          // O(1)
            pertenece =  true;  // O(1)
        }
        i++;                    // O(2)
    }

    return pertenece;
}

// O(n)
void quitarPosicion(pos p, banderitas& b){ // O(1) + O(1) + n*O(O(2) + O(2) + O(1) + O(4) + O(3) + O(2)) = O(n)

    int i = 0;              // O(1)
    while(i < b.size()){    // O(1) + n*O(linea 53 a 62)
        if(b[i] == p){      // O(2)
            if(i == b.size()-1){    // O(2)
                b.pop_back();       // O(1)
            }
            else{
                b[i] = b[i+1];      // O(4)
                b[i+1] = p;         // O(3)
            }
        }
        i++;                        // O(2)
    }
}


/******++++**************************** EJERCICIO perdio ***********+++***********************/

// O(1)
bool tieneUnaMina(tablero& t, pos p){
    return t[p.first][p.second]; // O(1)
}

/******++++**************************** EJERCICIO gano ***********+++***********************/

// O(n)
bool perteneceAJugadas(jugada jugada, jugadas& jugadas){ // O(1) + O(1) + O(n) = O(n)
    bool pertenece = false; // O(1)

    int i = 0; // O(1)
    while(i < jugadas.size()){        // O(n * (linea 71 a 74)) = O( n*(O(5))) = O(5n) = O(n)
        if(jugadas[i] == jugada){          // O(2)
            pertenece = true;   // O(1)
        }
        i++;                    // O(2)
    }

    return pertenece;
}

// O(1)
pos newPos(int x, int y) {  // O(1) + O(1) = O(2) = O(1)
    pos p;
    p.first = x;            // O(1)
    p.second = y;           // O(1)
    return p;
}


/******++++**************************** EJERCICIO jugarPlus ***********+++***********************/

/******++++**************************** EJERCICIO sugerirAutomatico121 ***********+++***********************/

// O(n^4)
bool hayPosicionSugerible(jugadas& j, banderitas& b, tablero& t, pos& p){

    bool hayPosicion = false; // O(1)

    int i = 0;                // O(1)
    while(i < t.size()){      // O(1) + n*(linea 99 a 110) = O(1) + n*( O( 1 + n^2 + 2))= O(n^4)
        int k = 0;            // O(1)
        while(k < t.size()){  // O(1) + n*(linea 101 a 108) = O(1) + n*( O(1 + n + n + 1 + 1 + 1 + 2) = O(n^2)
            pos pos1 = newPos(i, k); // O(1) + O(newPos) = O(2) = O(1)
            if(esPosicionSinJugarYSinBanderita(pos1, j, b, t) && // O(n^2)
               esAdyacente121(pos1, j)){  // O(esAdyacente121) = O(n^2)
                hayPosicion = true; // O(1)
                p.first = pos1.first; // O(1)
                p.second = pos1.second; 
            }
            k++; // O(2)
        }
        i++; // O(2)
    }

    return hayPosicion;
}

// O(n^2)
bool esPosicionSinJugarYSinBanderita(pos p, jugadas& j, banderitas& b, tablero& t){ // O(1) + O(1) + O(n) + O(n) = O(n)
    jugada newJugada = {{p}, minasAdyacentes(t, p)};   // O(1) + O(minasAdyacentes) = O(2) = O(1)
    return(posicionValida(p, t) &&                     // O(posicionValida) + O(1) = O(2) = O(1)
          !perteneceAJugadas(newJugada, j) &&          // O(perteneceAJugadas) = O(n^2) (EN ESTE CASO)
          !contienePosicionBanderita(p, b));           // O(contienePosicionBanderita) = O(n^2)
}

// O(1)
bool posicionValida(pos p, tablero& t){             // O(7) = O(1)
    return(0 <= p.first && p.first < t.size() &&    // O(1) + O(1) + O(1) + O(1)
           0 <= p.second && p.second < t.size());   // O(1) + O(1) + O(1)
}

// O(n^2)
bool esAdyacente121(pos p, jugadas& j){ // O(n^2)
    int p0 = p.first;                                    // O(1)
    int p1 = p.second;                                   // O(1)
    return(es121Horizontal({p0-1, p1}, j) || // O(es121Horizontal) + O(1) + O(1)  = O(n+2)  = O(n^2)
           es121Horizontal({p0+1, p1}, j) || // O(es121Horizontal) + O(1) + O(1)  = O(n+2)  = O(n^2)
           es121Vertical({p0, p1-1}, j) ||   // O(es121Vertical)   + O(1) + O(1)  = O(n+2)  = O(n^2)
           es121Vertical({p0, p1+1}, j));    // O(es121Vertical)   + O(1)         = O(n+1)  = O(n^2)
}

// O(n^2)
bool es121Horizontal(pos p, jugadas& j){ // O(n^2)
    return( perteneceAJugadas({{p.first, p.second - 1}, 1}, j) && // O(perteneceAJugadas) + O(1) + O(1) = O(n+2) = O(n^2)
            perteneceAJugadas({{p.first, p.second}, 2}, j)   &&   // O(perteneceAJugadas) + O(1) = O(n+1) = O(n^2)
            perteneceAJugadas({{p.first, p.second + 1}, 1}, j));   // O(perteneceAJugadas) + O(1) = O(n+1) = O(n^2)
}

// O(n^2)
bool es121Vertical(pos p, jugadas& j){
    return( perteneceAJugadas({{p.first - 1, p.second}, 1}, j) &&    // O(perteneceAJugadas) + O(1) + O(1) = O(n+2) = O(n^2)
            perteneceAJugadas({{p.first, p.second}, 2}, j)   &&     // O(perteneceAJugadas) + O(1) = O(n+1) = O(n^2)
            perteneceAJugadas({{p.first + 1, p.second}, 1}, j));    // O(perteneceAJugadas) + O(1) = O(n+1) = O(n^2)
}



