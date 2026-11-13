#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

template <typename T>
class Vec {
    private:
    T* data;            //array de elementos de tipo T
    size_t count;       //numero de elementos insertados
    size_t capacity;    //Numero de elementos que data puede almacenar
    public:

    //Constructores de clase
    Vec() : data(nullptr), count(0), capacity(0) {}
    Vec(size_t c) : data(new T[c]), count(0), capacity(c) {}

    //Constructor de copia
    Vec(const Vec<T>& other) : count(other.count), capacity(other.capacity){
        data = new T[other.capacity];
        for (size_t i = 0; i < other.count; i++){
            data[i] = other.data[i];
        }
    }

    // Operador de asignación
    Vec<T>& operator= (const Vec<T>& right){
        if(this == &right) return *this;

        delete [] data;
        data = new T[right.capacity];
        for (size_t i = 0; i < right.count; i++){
            data[i] = right.data[i];
        }

        count = right.count;
        capacity = right.capacity;
        return *this;
    }

    //Clase destructor
    ~Vec() {delete [] data;}

    size_t size() const {return count;}
    size_t cap() const {return capacity;}

    //Operaciones de acceso (enlaces no verificados)
    T& operator [] (size_t i) {return data[i];}
    const T& operator [] (size_t i) const {return data[i];}

    //Operaciones de acceso (enlaces verificados)
    T& at(size_t i){
        if(i >= size()) throw out_of_range("Invalid index");
        return data[i];
    }

    const T& at(size_t i) const{
        if(i >= size()) throw out_of_range("Invalid index");
        return data[i];
    }

    // Aumentar la capacidad cuando sea necesario
    void reserve(size_t newcap) {
        if (newcap <= capacity) return;
        T* nd = new T[newcap]; 
        for (size_t i = 0; i < count; i++) {
            nd[i] = data[i];  
        }
        delete [] data; // liberar bloque antiguo
        data = nd;
        capacity = newcap;
    }

    void grow() {
        size_t newcap = 1;

        //Si el vector no tiene capacidad (count == capacity), se duplica.
        if (capacity != 0) {
            newcap = capacity * 2;
        }
        reserve(newcap);
    }

    // Añadir un elemento al final
    void push_back(const T& x){
        if (count == capacity){
            grow();
        }
        data[count] = x;
        count++;
    }

    // Imprime el vector, incluyendo tanto las posiciones ocupadas como las libres (*)
    void printVec(){
        cout << "[";
        for (size_t i = 0; i < capacity; i++){
            if(i < count) cout << data[i] << "  ";
            else cout << " " << "*";
        }
        cout << "]" << endl;
    }

    // Elimina el elemento en una posición determinada
    void erase(size_t pos){
        if (pos < count){
            for(size_t i = pos; i < count; i++){
                data[i] = data[i+1];
            }
            count--;
        }else{
            throw out_of_range("Invalid position");
        }
    }

    // Remover el primer elemento
    void pop_front(){
        erase(0);
    }

    // Remover el último elemento
    void pop_back(){
        count--;
    }

    // Inserta un elemento en una posición específica
    void insert(size_t pos, const T& num){
        if (pos > count) {
        throw out_of_range("Invalid position");
        }
        if (count == capacity) grow();

        // Mover los elementos hacia la derecha
        for(size_t i = count; i > pos; i--){
            //Copiar el elemento anterior a la posición actual para evitar que los elementos existentes sean sobrescritos
            data[i] = data[i - 1];
        }
        data[pos] = num;
        count++;
    }

    T& front() {
        if(count == 0) throw out_of_range("Empty vector");
        return data[0]; // Retornar el primer elemento
    }

    T& back() {
        if(count == 0) throw out_of_range("Empty vector");
        return data [size() - 1]; // Retornar el último elemento
    }

    // Elimina todos los elementos en el rango desde "from" hasta "to", excluyendo "to"
    void erase_range(size_t from, size_t to){
        size_t pos_erase = to - from;  // Calcular el número de elementos que se van a eliminar
        for(size_t i = from; i < count - pos_erase; i++){
            data[i] = data[i + pos_erase];
        }
        count = count - pos_erase;
        printVec();
    }

    //Elimina todos los elementos sin modificar la capacidad
    void clear(){
        count = 0;
    }

    //segunda versión de contains utilizando find()
    bool contains(const T &elem) const { // Comprobar si un elemento existe en el vector
        pair<size_t, bool> res = find(elem);

        if (res.second == true) return true;
        else return false;
    }

    pair<size_t, bool> find(const T &elem) const{ // Encuentra la primera aparición de un elemento en el vector
        for(int i = 0; i < count; i++){
            if (data[i] == elem) return make_pair(i, true); // devuelve el índice y confirma que lo ha encontrado.
        }
        return make_pair(0, false);
    }

    // Eliminar la primera aparición de un elemento del vector
    void remove(const T &elem){
        pair<size_t, bool> res = find(elem);

        if (res.second == true){
            for(size_t i = res.first; i < count; i++){
                data[i] = data[i+1];
            }
            count--;
        }
    }

    // Reemplazar la primera aparición de un valor con un nuevo valor
    void replace(const T &oldVal, const T &newVal){
        pair<size_t, bool> res = find(oldVal);

        if(res.second == true){
            data[res.first] = newVal;
        }
    }

    //Eliminar todas las apariciones de un elemento
    void remove_all(const T &elem){
        size_t idx = 0; //para guardar el índice en el que se almacenarán los distintos elementos

        for(size_t i = 0; i < count; i++){
            if(elem != data[i]){
                data[idx] = data[i];
                idx++;
            }
        }
        count = idx;
    }

    // Reemplazar todas las apariciones de un elemento en el vector
    void replace_all(const T &oldVal, const T &newVal){
        for(size_t i = 0; i < count; i++){
            if(oldVal == data[i]){
                data[i] = newVal;
            }
        }
    }

    // Cuenta cuántas veces aparece un elemento
    size_t count_elem(const T &elem) const{
        size_t counter = 0;
        for(size_t i= 0; i < count; i++){
            if(elem == data[i]){
                counter++;
            }
        }
        return counter;
    }

    Vec<size_t> indices_of(const T& elem) const{
        Vec<size_t> indexes;
        for(size_t i = 0; i < count; i++){
            if(data[i]  == elem){
                indexes.push_back(i);
            }
        }
        return indexes;
    }

    //Intercambia los elementos en los índices i y j del vector.
    void swap(size_t i, size_t j){

        if(i >= count || j >= count){
            throw out_of_range("Invalid index");
        }
        if(i == j) return;

        //temporal variable tmp
        T tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }

    // Invertir los elementos del vector
    void reverse(){
        if(count == 0) return; //En caso de que el vector esté vacío
        size_t i = 0;
        size_t j = count - 1;

        while(i < j){
            swap(i, j);
            i++;
            j--;
        }
        
    }

   // Desplazar los elementos hacia la izquierda k posiciones
    void rotate_left(size_t k){ //El elemento en el índice k se convierte en el nuevo primer elemento
        if(count == 0) return;

       // Reducir k al tamaño del vector
        k = k % count; // k - número de posiciones a rotar
        if(k == 0) return;

        // Invertir los primeros k elementos
        size_t i = 0;
        size_t j = k - 1;

        while(i < j){
            swap(i, j);
            i++;
            j--;
        }

        // Invertir los elementos restantes
        i = k;
        j = count - 1;

        while(i < j){
            swap(i, j);
            i++;
            j--;
        }

       // Invertir todo el vector
        reverse();
    }

    //Desplazar los elementos hacia la derecha k posiciones
    void rotate_right(size_t k){ //El elemento en el índice sz - k se convierte en el nuevo primer elemento
        if(count == 0) return;
        k = k % count;
        rotate_left(count - k);
    }

    //Ordenar los elementos en orden ascendente
    void sort(){
        if(count <= 1) return;
        quick_sort(0, count - 1);
    }

    void quick_sort(size_t low, size_t high){
        if(low >= high) return; //Comprobar si hay algo que deba organizarse

        int m = (low + high)/2;

        swap(m, high);

        T pivot = data[high]; 
        size_t idx = low; //Indica dónde se encuentra el siguiente elemento menor que el pivote.

        for(size_t j = low; j < high; j++){
            if(data[j] < pivot){
                swap(idx, j);
                idx++;
            }
        }

        // Coloca el pivote en su posición correcta
        swap(idx, high);
        size_t pivot_idx = idx;

        // Ordenar la parte izquierda
        if(pivot_idx > low){
            quick_sort(low, pivot_idx - 1);
        }

        // Ordenar la parte derecha
        if(pivot_idx < high){
            quick_sort(pivot_idx + 1, high);
        }
    }

    // Suma los elementos de un vector a otro vector
    void append(const Vec<T>& other){

        //En caso de que el mismo vector se pase como argumento, se crea una copia del vector y se llama a la función append con la copia.
        if(this == &other){
            //para invocar el constructor de copia
            Vec<T> copy = other;
            append(copy);
            return;
        }

        for(size_t i = 0; i < other.count; i++){
            push_back(other[i]);
        }
    }

    Vec<size_t> slice(size_t from, size_t to){
        Vec<size_t> elem;
        if(from > to || to > count){
            throw out_of_range("Invalid index");
        }
        for(size_t i = from; i < to; i++){
            elem.push_back(data[i]);
        }
        return elem;
    }


};

int main() {
    cout << "Vectors!" << endl;

    cout << "Vector p:" << endl;
    Vec<int> p(10);
    for (size_t i = 1; i <= 10; i++){
        p.push_back(i);
    }cout <<endl;

    p.printVec();
    cout << "Size: " <<p.size() << endl;
    cout << "Capacity: " <<p.cap() << endl;

    //cout <<p[3] << endl; // Utilizar desde main operacion operator no constante

    cout << "Using pops: " << endl;
    p.pop_front();
    p.printVec();
    p.pop_back();
    p.printVec();

    cout << "Using insert: " << endl;
    p.insert(2, 99);
    p.printVec();

    cout << "Erase in a range: " <<endl;
    p.erase_range(2, 5);
    p.printVec();

    bool contain = p.contains(6);
    if(contain == true) cout<< "Vector contains the element"<<endl;
    else cout<< "Vector doesn't contains the element" <<endl;

    p.push_back(6);
    p.printVec();

    pair<size_t, bool> res = p.find(6);

    if(res.second) cout <<"Element was found in the position " << res.first <<endl;
    else cout << "Element was not found." << endl;

    cout<<"Using remove: " <<endl;
    p.remove(6);
    p.printVec();

    cout<<"Using replace: " <<endl;
    p.replace(6, 10);
    p.printVec();

    p.insert(1, 8);
    p.insert(2, 6);
    p.insert(4, 8);
    p.printVec();

    cout<<"Using remove all : " <<endl;
    p.remove_all(8);
    p.insert(3, 6);
    p.insert(5, 6);
    p.printVec();

    cout<<"Using repalce all: "<<endl;
    p.replace_all(6, 1);
    p.printVec();

    cout<< "Element appears: "<< p.count_elem(1) << endl;
 
    Vec<size_t>idx;
    idx = p.indices_of(1);
    cout<<"Using indices of, for obtain new vector: "<<endl;
    idx.printVec();

    cout<<"Using swap: "<<endl;
    p.swap(2,6);
    p.printVec();

    // cout <<"Using clear:"<<endl;
    // p.clear();
    // p.printVec();
    // cout << "Size: " <<p.size() << endl;
    // cout << "Capacity: " <<p.cap() << endl;

    cout<<"Using reverse: "<<endl;
    p.reverse();
    p.printVec();

    cout<<"Using rotate left: "<<endl;
    p.rotate_left(3);
    p.printVec();

    cout<<"Using rotate right: "<<endl;
    p.rotate_right(3);
    p.printVec();

    cout<<"Using sort:"<<endl;
    p.sort();
    p.printVec();
    cout <<endl;

    Vec<int> n(5);
    n.push_back(5);
    n.push_back(10);
    n.push_back(15);
    n.push_back(20);
    n.push_back(25);
    n.printVec();

    p.append(p);
    p.printVec();

    Vec<size_t>elems;
    elems = p.slice(3,9);
    cout<<"Using a range, for obtain new vector: "<<endl;
    elems.printVec();

    cout<< "Calling the assignment operator"<<endl;
    Vec<size_t> v; 
    v.printVec();
    v = elems;
    v.printVec();
    v[2]= 6;
    v.printVec();
    elems.printVec();

    //to call the copy constructor
    // Vec<int> v(p);
    // v.printVec();


    /*cout << "Vector q:" << endl;
    Vec<int> q(5);
    q.push_back(5);
    q.push_back(10);
    q.push_back(15);
    q.push_back(20);
    q.push_back(25);

    q.printVec();
    cout<< "First element of the vector: " << q.front() <<endl;
    cout<< "Last element of the vector: " << q.back() <<endl;
    cout << "The middle element of the vector is: " << q.at(2) << endl;

    q[1] = 100;

    q.printVec();

    Vec<string> s(5);
    cout << "Vector s" << endl;

    s.push_back("the");
    s.push_back("quick");
    s.push_back("brown");
    s.push_back("fox");
    s.push_back("jumps");

    s.printVec();
    cout << "Size: " <<s.size() << endl;
    cout << "Capacity: " <<s.cap() << endl;

    s.insert(1, "system");
    s.printVec();

    cout << "Size: " <<s.size() << endl;
    cout << "Capacity: " <<s.cap() << endl;

    s.pop_front();
    s.printVec();
    s.pop_back();
    s.printVec();

    s.erase(2);
    s.printVec();
    */

    return 0;
}