#include<iostream>

using namespace std; 

typedef int elemento; 

struct Nodo{
    elemento dato; 
    Nodo * ant; 
    Nodo * sig; 
}; 


struct ColaD{
    Nodo * primero = NULL; 
    Nodo * ultimo = primero; 
    int tam = 0; 
}; 

//Constructoras 
ColaD crear_colaDVacia(); 
void encolarD_der(ColaD & c, elemento x);
void encolarD_izq(ColaD & c, elemento x); 

//Funciones del TAD 
void desencolarD_der(ColaD & c);
void desencolarD_izq(ColaD & c);  
elemento primeroD(ColaD c);
elemento ultimoD(ColaD c);  
bool es_colaDVacia(ColaD c); 

//Funciones aux 
void mostrarD(ColaD & c); 
void liberarD(ColaD & c); 

int main(){
    ColaD c = crear_colaDVacia(); 
    
    cout << "Creamos una cola con su constructor y esta nace vacía:" << endl; 
    mostrarD(c);

    for (int i = 0; i < 10; i++){
        encolarD_der(c, i); 
    }
    cout << "Encolamos los números del 0 al 9 por la derecha: " << endl; 
    mostrarD(c); 

    for (int i = 10; i < 20; i++){
        encolarD_izq(c,i);
    }
    cout << "Encolamos los números del 10 al 19 por la izquierda: " << endl; 
    mostrarD(c); 

    
    desencolarD_der(c); 
    cout << "Llamamos a desencolar por la derecha una vez y obtenemos: " << endl; 
    mostrarD(c);

    desencolarD_izq(c); 
    cout << "Llamamos a desencolar por la izquierda una vez y obtenemos: " << endl; 
    mostrarD(c); 

    elemento x1 = primeroD(c);
    cout << "El primer elemento de la cola será: " << x1 << endl;
    
    elemento x2 = ultimoD(c);
    cout << "El ultimo elemento de la cola será: " << x2 << endl; 

    liberarD(c); 
    
    return 0; 
}

ColaD crear_colaDVacia(){
    ColaD result; 
    return result;
}

void encolarD_der(ColaD & c, elemento x){
    Nodo * nuevo_ultimo = new Nodo; 
    nuevo_ultimo -> dato = x; 
    nuevo_ultimo -> sig = NULL; 
    nuevo_ultimo -> ant = NULL; 
     
    //Si la cola es vacia
    if(c.ultimo == NULL){
       c.primero = nuevo_ultimo; 
       c.ultimo = nuevo_ultimo;
    }
    else{
       c.ultimo -> sig = nuevo_ultimo;
       nuevo_ultimo -> ant = c. ultimo; 
       c.ultimo = nuevo_ultimo;
    }
    c.tam++; 

} 
 
void encolarD_izq(ColaD & c, elemento x){
    Nodo * nuevo_primero = new Nodo; 
    nuevo_primero -> dato = x;
    nuevo_primero -> sig = NULL; 
    nuevo_primero -> ant = NULL;



    //Si la cola es vacia 
    if(c.ultimo == NULL){
        c.primero = nuevo_primero; 
        c.ultimo = nuevo_primero;
    }
    else{
        c.primero -> ant = nuevo_primero; 
        nuevo_primero -> sig = c.primero;
        c.primero = nuevo_primero;
          
    }
    c.tam++; 
}

void desencolarD_der(ColaD & c){
    if(c.tam == 0){
        cout << "Nada que desencolar." << endl; 
    }
    else{
     
        Nodo * aux_borrar = c.ultimo;

        
        if(c.primero == aux_borrar){
            c.primero = NULL;
            c.ultimo = c.primero;
             
        }
        else{
            
            c.ultimo -> ant -> sig = NULL;
            
            c.ultimo = c.ultimo -> ant;
        }
        
         
        delete aux_borrar;  
        
         
        c.tam--; 
    }
}

void desencolarD_izq(ColaD & c){
    if(c.tam == 0){
        cout << "Nada que desencolar. La cola es vacia." << endl; 
    }
    else{
         
        Nodo * aux_borrar = c.primero; 
     
        if(c.ultimo == aux_borrar){
            c.primero = NULL;
            c.ultimo = c.primero;
             
        }
        else{
            c.primero -> sig -> ant = NULL; 
            c.primero = c.primero -> sig;  
        }
        
        //Borramos 
        delete aux_borrar; 
        
        c.tam--; 
    }
}

elemento primeroD(ColaD c){
    elemento result = c.primero -> dato;
    return result;
}

elemento ultimoD(ColaD c){
    elemento result = c.ultimo -> dato; 
    return result; 
}

bool es_colaDVacia(ColaD c){
    return (c.tam == 0); 
}

void mostrarD(ColaD & c){
    cout << "[[";
    if(es_colaDVacia(c)){
        cout << "]]" << endl; 
    }
    else{
        Nodo * indice = c.primero;

        for (int i = 0; i < c.tam; i++){
            if(i < c.tam - 1){
                cout << indice -> dato << ", "; 
            }
            else{
                cout << indice -> dato;
            }
            indice = indice -> sig; 
        }
        cout << "]]" << endl;
    }
}
 
void liberarD(ColaD & c){
    while(!(es_colaDVacia(c))){
        desencolarD_izq(c);
    }
}

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
           
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
