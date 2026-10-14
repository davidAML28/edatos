/*
Para compilar: 
g++ -o prueba clasesVec.cpp
Para ejecutar: 
./vector
*/
#include <iostream>
using namespace std;

class Vec {
    private:
        int* data;
        size_t count;
        size_t capacity;
 public:
    
    Vec() : data(nullptr), count(0), capacity(0){} //Constructor por defecto
    Vec(size_t c) : data(new int[c]), count(0), capacity(c) {} //Constructor con capacidad inicial
    ~Vec(){
        delete[] data; //Liberar memoria (destructor)
    }

    size_t size() const { return count; } //Devuelve el número de elementos


    void push_back(int elem){
        if(count == capacity){
            grow();
        }
        data[count] = elem;
        count++;
    }
    
    
    void grow(){
        size_t new_capacity = (capacity*2);
        int* newblock = new int[new_capacity];  //Duplicar la capacidad
        for(size_t i = 0; i < count; i++){
            newblock[i] = data[i]; //Copiar elementos al nuevo bloque
    }
    delete[] data; //Liberar memoria del bloque antiguo
    data = newblock; //Actualizar el puntero al nuevo bloque
    capacity = new_capacity; //Actualizar la capacidad
}

};


int main(){
    cout <<"Vectores!!"<< endl;
    Vec w(2);
    for(int i=0; i<100; i++){
        w.push_back(i);
    }
    //w.push_back(10);
    //w.push_back(20);
    //w.push_back(30);
    //w.push_back(40);
    //w.push_back(50);
    cout<< w.size() << endl;
    return 0;

}
