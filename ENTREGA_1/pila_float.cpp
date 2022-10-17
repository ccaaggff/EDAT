/* Implementación de las pilas de naturales como una estructura enlazada. Dentro del struct llevamos una variable tamaño que permite conocer en todo momento la longitud de la pila y con ello tener que hacer recorridos innecesarios. */
#include <iostream>

using namespace std; 

//De esta forma conseguimos que la implementación sirva para cualquier tipo de elementof, ya que en esta definición podemos cambiar int por char, float,... 
typedef float elementof; 


struct Nodo{
    elementof dato;  
    Nodo * sig; 
};

struct Pila_float{
    Nodo * ultimo = NULL;
    int tam = 0;
};

//Constructoras
Pila_float crear_pilafloat_vacia(); 
void apilar(Pila_float & p, elementof x); 
 
//Funciones del TAD 
void desapilar(Pila_float & p); 
elementof cima(Pila_float p);
bool es_pilaVacia(Pila_float p); 

//Funciones aux 
void mostrar(Pila_float & p);
void liberar(Pila_float & p); 
/*
int main(){
    Pila_float p = crear_pilafloat_vacia();

    for (int i = 0; i < 10; i++){
        apilar(p,i); 
    }
    mostrar(p); 

    desapilar(p); 
    mostrar(p); 

    int x1 = cima(p);
    cout << x1 << endl;

    liberar(p);   

    return 0; 
}
*/
Pila_float crear_pilafloat_vacia(){
    Pila_float result; 
    return result; 
}

void apilar(Pila_float & p, elementof x){
    Nodo * nodo_superior = new Nodo;
    nodo_superior -> dato = x;
    nodo_superior -> sig = p.ultimo;
    //p.ultimo -> sig = nodo_superior; 
    p.ultimo = nodo_superior;

    p.tam++;
}

void desapilar(Pila_float & p){
    Nodo * aux = p.ultimo -> sig;
    delete p.ultimo; 
    p.ultimo = aux;  
    p.tam--; 
}

elementof cima(Pila_float p){
    return p.ultimo -> dato; 
}

bool es_pilaVacia(Pila_float p){
    return (p.tam == 0);
}

void mostrar(Pila_float & p){
    if(es_pilaVacia(p)){
        cout << "]" << endl;
    }

    Nodo * indice = p.ultimo;

    int contador = 0; 
    while (indice != NULL){
        if (contador > 0){
            cout << ", " << indice -> dato;
        }
        else{
            cout << indice -> dato; 
        }
        contador++;
        indice = indice -> sig; 
    }
    cout << "]" << endl; 
}

void liberar(Pila_float & p){
    while (!es_pilaVacia(p)){
        desapilar(p);
    }
}
