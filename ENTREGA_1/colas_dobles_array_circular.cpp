#include <iostream> 
#include <exception>

using namespace std; 

int const CAP_INC = 10;

template <typename T>
struct ColaD{
    T * datos = new T[CAP_INC];
    int dr = -1; 
    int izq = 0;
    int tam = CAP_INC;   
};

//Constructoras 
template <typename T>
ColaD<T> crear_colaDVacia(){
    ColaD<T> result; 
    return result; 
}

template <typename T>  
bool es_colaDVacia(ColaD<T> c){
    return (c.dr == -1);
}

template <typename T>  
bool es_colaDLlena(ColaD<T> c){
    return ((c.dr == 0 && c.izq == c.tam - 1) || c.dr == c.izq + 1);
}

template <typename T> 
void doblar_cap(ColaD<T> & c){
    int const NUEVA_CAP = 2 * c.tam;
    T * nuevos_datos = new T[NUEVA_CAP];

    if(c.izq >= c.dr){ 
        for (int i = c.dr; i < c.izq; i++){
            nuevos_datos[i] = c.datos[i]; 
        }
    }
    else{
        for (int i = c.dr; i < c.tam; i++){
            nuevos_datos[i] = c.datos[i];
        }
        
        for (int i = 0; i < c.izq; i++){
            nuevos_datos[i] = c.datos[i];
        }
    }
    
    delete[] c.datos; 
    c.datos = nuevos_datos; 
}

template <typename T>
void encolarD_dr(ColaD<T> & c, T x){
    //Inserta un elemento por delante
    if(es_colaDLlena(c)){
        doblar_cap(c); 
        encolarD_dr(c, x);
    }
    //cola vacia 
    if(es_colaDVacia(c)){
        c.dr = 0; 
        c.izq = 0; 
    } 
    //c.pr está al principio de la cola 
    else if(c.dr == 0){
        c.dr = c.tam - 1; 
    }
    else{
        c.dr--; 
    }
    c.datos[c.dr] = x; 
}

template <typename T> 
void encolarD_izq(ColaD<T> & c, T x){
    //Insertar un elemento al final de la cola
    if(es_colaDLlena(c)){
        doblar_cap(c); 
        encolarD_izq(c,x); 
        //cout << "*" << endl; 
    }
    if(es_colaDVacia(c)){
        c.dr = 0; 
        c.izq = 0;
    }
    //c.izq está al final de la cola 
    else if(c.izq == c.tam - 1){
        c.izq = 0; 
    }
    else{
        c.izq++; 
    }
    c.datos[c.izq] = x; 
}

//Funciones del TAD
template <typename T> 
void desencolarD_der(ColaD<T> & c){
    if(es_colaDVacia(c)){
        throw runtime_error("Cola vacia");
        return; 
    }

    //la cola sólo tiene un elemento 
    if(c.dr == c.izq){
        c.dr = -1; 
        c.izq = -1; 
    }
    //volver a la posicion inicial 
    else if(c.dr == c.tam - 1){
            c.dr = 0; 
        }
    //resto de casos 
    else{
        c.dr++; 
    }
}

template <typename T>
void desencolarD_izq(ColaD<T> & c){
    if(es_colaDVacia(c)){
        throw runtime_error("Cola vacia");
        return; 
    }
    //la cola sólo tiene un elemento 
    if(c.dr == c.izq){
        c.dr = -1; 
        c.izq = -1; 
    }
    else if(c.izq == 0){
        c.izq = c.tam - 1; 
    }
    else{
        c.izq--; 
    }
}

template <typename T>  
T primeroD(ColaD<T> c){
    if(es_colaDVacia(c)){
        throw runtime_error("Cola vacia");
        return -1; 
    }
    return c.datos[c.izq];
}

template <typename T>
T ultimoD(ColaD<T> c){
    if(es_colaDVacia(c)){
        throw runtime_error("Cola vacia");
        return -1; 
    }
    return c.datos[c.dr];
}

template <typename T>
void mostrarD(ColaD<T> & c){
    // for (int i = 0; i < c.tam - 1; i++){
    //     cout << c.datos[i] << ", ";
    // }
    // cout << c.datos[c.tam - 1] << endl;

    if(!es_colaDVacia(c)){
        cout << "[[";
        if(c.izq >= c.dr){ 
            for (int i = c.dr; i < c.izq; i++){
                cout << c.datos[i] << ", "; 
            }
            cout << c.datos[c.izq];  
        }
        else{
            for (int i = c.dr; i < c.tam; i++){
                cout << c.datos[i] << ", ";
            }
            
            for (int i = 0; i < c.izq; i++){
                cout << c.datos[i] << ", ";
            }
            cout << c.datos[c.izq];  
        }
    }
    cout << "]]" << endl; 
}

template <typename T> 
void liberarD(ColaD<T> & c){
    delete[] c.datos; 
} 

int main(){

    ColaD<int> c = crear_colaDVacia<int>();

    for (int i = 0; i < 5; i++){
        encolarD_dr(c,i);
    }
    
    cout << "Encolamos del 0 al 4 por la derecha: " << endl; 
    mostrarD(c); 

    for (int i = 10; i < 15; i++){
        encolarD_izq(c,i);
    }
    cout << "Encolamos del 10 al 14 por la izquierda: " << endl; 
    mostrarD(c); 

    int iz = primeroD(c); 
    int dr = ultimoD(c);
    cout << "Los elementos primero y ultimo de la cola son: " << iz << ", " << dr << endl;

    cout << "-------------" << endl; 

    desencolarD_der(c); 
    desencolarD_izq(c); 

    int iz2 = primeroD(c); 
    int dr2 = ultimoD(c);
    cout << "Tras desencolar por izquierda y derecha, los elementos primero y ultimo de la cola son: " << iz2 << ", " << dr2 << endl;
    mostrarD(c); 
    cout << "-------------" << endl; 
    cout << "MAL" << endl; 
    cout << "Hasta ahora todo lo que hemos hecho no suponia aumentar el tamaño por defecto de la cola." << endl; 

    for (int i = 110; i < 200; i++){
        encolarD_dr(c,i);
    }
    mostrarD(c);
    for (int i = 210; i < 215; i++){
        encolarD_izq(c,i);
    }
    mostrarD(c);


    return 0; 
}