#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<bool> bits;

void imprimir_bits(vector< pair<char,bits> > alfa){
    for(size_t i = 0; i < alfa.size(); ++i){
        cout << alfa[i].first << ": ";
        for(size_t j = 0; j < alfa[0].second.size(); ++j){
            cout << alfa[i].second[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void imprimir_D(bits D){
    for(size_t i = 0; i < D.size(); ++i){
        cout << D[i] << " ";
    }
    cout << endl;
}

void obtener_alfabeto(string texto, string patron, vector< pair<char,bits> > &alfa){
    sort(texto.begin(), texto.end());
    texto.erase(unique(texto.begin(), texto.end()), texto.end());
    string alfabeto = texto;
    for(size_t i = 0; i < alfabeto.size(); ++i){
        alfa.push_back(make_pair(alfabeto[i],bits(patron.size())));
        for(size_t j = 0; j < patron.size(); j++){
            if(alfa[i].first == patron[j]) alfa[i].second[j] = true;
        }
    }
}

bits obtener_bits(vector< pair<char,bits> > alfabeto, char letra){
    for(size_t i = 0; i < alfabeto.size(); ++i){
        if(alfabeto[i].first == letra) return alfabeto[i].second;
    }
}


bits operacion(bits D, bits alfabeto){
    size_t i;
    bits temp = D;
    for(i = 0; i < D.size()-1; ++i){
        D[i+1] = temp[i];
    }
    D[0] = true;
    for(i = 0; i < D.size(); ++i){
        D[i] = D[i] & alfabeto[i];
    }
    return D;
}

int shift_and(string texto, string patron){
    vector<pair<char,bits>> alfabeto;
    obtener_alfabeto(texto, patron, alfabeto);
    imprimir_bits(alfabeto);
    bits D(patron.size());
    size_t n = texto.size();
    size_t m = patron.size();
    for(size_t j = 0; j < n; ++j){
        D = operacion(D, obtener_bits(alfabeto, texto[j]));
        if( D[m-1] != 0 ) return j - m + 1;
    }
    return 0;
}

int main(){
    string patron;
    string texto;
    cout << "Ingrese el texto: ";
    cin >> texto;
    cout << "Ingrese el patron: ";
    cin >> patron;
    cout << endl;
    int rpta = shift_and(texto, patron);
    if(rpta == 0){
        cout << "No se encuentra la subcadena" << endl;
    }
    else{
        cout << "La subcadena empieza en la posicion " << rpta << " del texto" << endl;
    }
    return 0;
}
