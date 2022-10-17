/* Implementación de las pilas de naturales como una estructura enlazada. Dentro del struct llevamos una variable tamaño que permite conocer en todo momento la longitud de la pila y con ello tener que hacer recorridos innecesarios. */
#include <iostream>

using namespace std;

// De esta forma conseguimos que la implementación sirva para cualquier tipo de elemento, ya que en esta definición podemos cambiar int por char, float,...
typedef char elemento;

struct NodoC
{
    elemento dato;
    NodoC *sig;
};

struct Pila_char
{
    NodoC *ultimo = NULL;
    int tam = 0;
};

// Constructoras
Pila_char crear_pilachar_vacia();
void apilarChar(Pila_char &p, elemento x);

// Funciones del TAD
void desapilarChar(Pila_char &p);
elemento cimaChar(Pila_char p);
bool es_pilaVaciaChar(Pila_char p);

// Funciones aux
void mostrarChar(Pila_char &p);
void liberarChar(Pila_char &p);
/*
int main()
{
    Pila_char p = crear_pilachar_vacia();

    apilarChar(p,'a');
    apilarChar(p,'b');
    apilarChar(p,'c');
    apilarChar(p,'d');
    mostrarChar(p);

    desapilarChar(p);
    mostrarChar(p);

    char x1 = cimaChar(p);
    cout << x1 << endl;

    liberarChar(p);

    return 0;
}
*/
Pila_char crear_pilachar_vacia()
{
    Pila_char result;
    return result;
}

void apilarChar(Pila_char &p, elemento x)
{
    NodoC *nodo_superior = new NodoC;
    nodo_superior->dato = x;
    nodo_superior->sig = p.ultimo;
    // p.ultimo -> sig = nodo_superior;
    p.ultimo = nodo_superior;

    p.tam++;
}

void desapilarChar(Pila_char &p)
{
    NodoC *aux = p.ultimo->sig;
    delete p.ultimo;
    p.ultimo = aux;
    p.tam--;
}

elemento cimaChar(Pila_char p)
{
    return p.ultimo->dato;
}

bool es_pilaVaciaChar(Pila_char p)
{
    return (p.tam == 0);
}

void mostrarChar(Pila_char &p)
{
    if (es_pilaVaciaChar(p))
    {
        cout << "]" << endl;
    }

    NodoC *indice = p.ultimo;

    int contador = 0;
    while (indice != NULL)
    {
        if (contador > 0)
        {
            cout << ", " << indice->dato;
        }
        else
        {
            cout << indice->dato;
        }
        contador++;
        indice = indice->sig;
    }
    cout << "]" << endl;
}

void liberarChar(Pila_char &p){
    //Como en desapilar ya tenemos un delete, lo aprovechamos para liberar memoria
    while (!es_pilaVaciaChar(p)){
        desapilarChar(p);
    }
}
