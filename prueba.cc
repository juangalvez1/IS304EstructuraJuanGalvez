#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v(1000000, 42); // Crear un vector con 1 millón de elementos

    cout << "Tamaño antes: " << v.size() << ", Capacidad antes: " << v.capacity() << endl;

    vector<int>().swap(v); // Liberar memoria

    cout << "Tamaño después: " << v.size() << ", Capacidad después: " << v.capacity() << endl;

    return 0;
}
