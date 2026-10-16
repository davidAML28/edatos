#include <iostream>
#include <cassert>

using namespace std;

template <typename T> //sirve para crear funciones o clases que puedan trabajar con diferentes tipos de datos sin tener que escribir el mismo código varias veces.
class Vec {
    private:
        T* data;
        size_t count;
        size_t capacity;
    public:
    Vec() : data(nullptr), count(0), capacity(0){} //Constructor
    Vec(size_t c) : data(new T[c]), count(0), capacity(c) {}

    ~Vec(){
        delete[] data;
    }

    size_t size() const { return count; }
    size_t cap() const {return capacity; }

    //Operaciones de acceso
    T& operator[] (size_t i) {return data[i];}
    const T& operator[] (size_t i) const {return data[i];}

    T& at(size_t i) {
        assert(i < count);
        return data[i];
    }

    const T& at(size_t i) const {
        assert(i < count);
        return data[i];
    }

    void push_back(const T& elem){
        if (count == capacity){
            grow();
        }
        data[count] = elem;
        count++;
    }

    void push_front(const T& x){
        insert(0, x);
    }

    const T& back() const{
        return data[count-1];
    }

    T& back(){
        return data[count-1];
    }

    const T& front() const{
        return data[0];
    }

    T& front(){
        return data[0];
    }

    void grow(){
        size_t newcap = 1;
        if(capacity != 0){
            newcap = capacity * 2;
        }
        reserve(newcap);
    }

    void reserve(size_t newcap){
        if (newcap <= capacity){
            return;
        }
        T* newblock = new T[newcap];
        //Copiar todos los elementos del arreglo "Viejo" al "Nuevo"
        for(size_t i = 0; i < count; i++){
            newblock[i] = data [i];
        }
        delete[] data;
        data = newblock;
        capacity = newcap;
    }

    void insert(size_t i, const T& x){
        if(count ==capacity){
            grow();        
        }
        for(size_t j = count; j > i; j--){
            data[j] = data[j-1];
        }
        data[i] = x;
        count++;
    }

    void erase(size_t i){
        for(size_t j = i; j < count-1; j++){
            data[j] = data[j+1];
        }
        count--;
    }

    void pop_front(){
        erase(0);
    }

    void pop_back(){
        erase(count-1);
    }

    void print() const{
        cout << "[";
        for(size_t i = 0; i < capacity; i++){
            if(i < count)
                cout << " " << data[i];
            else 
                cout << "_";
            
    }
    cout << " ]" << endl;
    }

};

int main(){
    cout << "Vectores!!" << endl;
    Vec<int> x;

    for(int i = 0; i < 10; i++){
        x.push_back(i+1);
    }
    x.print();
    //cout << x.at(1000000) << endl;
    
    return 0;
}
