// cola con estructura enlazada

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std; 
typedef int elemento;

struct nodo {
	elemento dato;
	nodo* sig;
	nodo* ant;
};	

struct cola{
	nodo* primero = NULL;
	nodo* ultimo = NULL;
	int profundidad = -1;
};

cola cola_vacia(){
	cola resultado;
	return resultado;
};

bool es_vacia(cola c){
	return c.profundidad == -1;
};

void en_cola(cola & c, elemento e){
	if(c.ultimo == NULL) {
		nodo* aux = new nodo;
		aux -> dato = e;
		aux -> sig = c.ultimo;
		aux -> ant = c.primero;
		c.primero = aux;
		c.ultimo = aux;
	}else{
		nodo* aux = new nodo;
		aux -> dato = e;
		aux -> sig = NULL;
		aux -> ant = c.ultimo;
		c.ultimo -> sig = aux;
		c.ultimo = aux;
	};
	c.profundidad = c.profundidad +1;
};

void fuera_cola(cola & c){
	nodo* aux = c.primero -> sig;
	delete c.primero;
	c.primero = aux;
	c.profundidad = c.profundidad - 1;
};

elemento ultimo_en_cola(cola c) {
	return c.ultimo -> dato;
};

//requiere cola no vacia
elemento primero_en_cola(cola c) {
	return c.primero -> dato;
};

int cant_elementos(cola c){
	return c.profundidad + 1;
};

int main(){
	cola c = cola_vacia();
	elemento e;
    string respuesta;
    std::cout<<"\nDesea agregar un dato (s/n): ";
    std::cin>>respuesta;
	while(respuesta=="s"){
		std::cout<<"Escribe un dato: ";
		std::cin>>e;
		en_cola(c,e);
		std::cout<<"\nDesea agregar otro dato (s/n): ";
		std::cin>>respuesta;
	}
	std::cout<<"\nSacando ";
	std::cout<<cant_elementos(c);
	std::cout<<" elementos de la cola: ";
	while(!es_vacia(c)){
		std::cout<<primero_en_cola(c);
		fuera_cola(c);
		std::cout<<", ";
	}
	std::cout<<"FIN.";
	return 0;
};
