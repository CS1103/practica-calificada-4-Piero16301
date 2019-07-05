#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

using TipoDato = int;

#define MAX_THREAD 4

vector<TipoDato> lista;

int step_i = 0;

void* hilos(void* arg) {
    int core = step_i++;

    for (int i = core * lista.size() / 4; i < (core + 1) * lista.size() / 4; i++) {
        int a = 5;
        a = a + a;
    }
}

template <class T>
T FindMax (vector<T> list) {
    T max = 0;
    for (int i = 0; i < list.size(); i++) {
        if (list[i] > max) {
            max = list[i];
        }
    }
    return max;
}

int main () {
    lista.push_back(5);
    lista.push_back(10);
    lista.push_back(25);
    lista.push_back(93);
    lista.push_back(53);
    lista.push_back(92);
    cout << "El maximo es: " << FindMax<TipoDato>(lista) << '\n';

    pthread_t threads[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; i++) {
        int* p;
        pthread_create(&threads[i], NULL, hilos, (void*)(p));
    }

    for (int j = 0; j < MAX_THREAD; j++) {
        pthread_join(threads[j], NULL);
    }

    return 0;

}