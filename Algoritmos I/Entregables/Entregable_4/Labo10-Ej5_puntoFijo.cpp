#include <vector>
#include <iostream>

using namespace std;

int puntoFijo(vector<int> v){

    int low = 0;
    int high = v.size() - 1;

    while(low <= high){

        int mid = (low + high) / 2;

        if(v[mid] == mid && v[mid-1] != mid - 1){
            return mid;
        }

        if(v[mid] < mid){
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
	return -1;
}

int main() {
    /* No hace falta modificar el main */
    // Leo las entradas
    int n;
    cin >> n;
    int i = 0;
    int x;
    vector<int> v;// En v leo el vector
    while (i<n){
        cin >> x;
        v.push_back(x);
        i++;
    }
    
    // Calculo el punto fijo de v
    int res = puntoFijo(v);
    
    // Imprimo la salida
    cout << res;
    
    return 0;
}
