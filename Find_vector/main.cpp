#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

using TipoDato = int;

#define MAX_THREAD 4

vector<TipoDato> lista;

int step_i = 0;

TipoDato maximo = 0;

void* hilos(void* arg) {
    int core = step_i++;

    for (int i = core * lista.size() / 4; i < (core + 1) * lista.size() / 4; i++) {
        for (int j = lista.size()-1; j > (lista.size()-1)-(lista.size()/4); j--) {
            if (lista[j] > maximo) {
                maximo = lista[j];
            }
            lista.pop_back();
        }
    }
}

template <class T>
T FindMax () {
    pthread_t threads[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; i++) {
        int* p;
        pthread_create(&threads[i], NULL, hilos, (void*)(p));
    }

    for (int j = 0; j < MAX_THREAD; j++) {
        pthread_join(threads[j], NULL);
    }

    return maximo;
}

int main () {

    lista.push_back(59);
    lista.push_back(10);
    lista.push_back(25);
    lista.push_back(93);
    lista.push_back(53);
    lista.push_back(92);
    lista.push_back(57);
    lista.push_back(34);

    cout << "Vector: ";

    for (int i = 0; i < lista.size(); i++) {
        cout << lista[i] << ((i == (lista.size()-1)) ? (' ') : (','));
    }

    cout << '\n';

    cout << "El maximo es: " << FindMax<TipoDato>() << '\n';

    return 0;

}