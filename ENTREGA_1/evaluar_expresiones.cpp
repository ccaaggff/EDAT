#include<iostream>
#include<string>
#include<exception>


using namespace std;

//las dos lineas siguientes son equivalentes a poner aquí el contenido de los dos archivos
#include "pila_char.cpp"
#include "pila_float.cpp"

typedef float elementoev; // cambiar float por el tipo de datos adecuado

struct tabla_valores{
      elementoev valores[256];
      bool asignado[256];
};

void inicializa(tabla_valores & t){
     for(int i = 0;i < 256;i++){
       t.asignado[i] = false;
     }
}

bool asignado(const tabla_valores & t, char  c){
     return t.asignado[c];
}

elementoev get_value(const tabla_valores & t, char c){
    if(t.asignado[c]){
      return t.valores[c];
    }
    else{
      throw runtime_error(c+" no está asignado");
    }
}

void put_value(tabla_valores  & t, char c, elementoev val){
     t.valores[c] = val;
     t.asignado[c] = true;
}

bool precedencia(char var, char cIma){
     //cima >= precedencia de var -> True  
     if(((var == '+') || (var == '-')) && (cIma == '*' || cIma == '/')){
          return true;
     } 
     else if(((var == '*') || (var == '/')) && (cIma == '+' || cIma == '-')){
          return false;
     }
     else{ //var == cIma
          return true; 
     }
}

void operar(Pila_float & p, char operador){
     elementoev x, y;
     elementoev resultado;  
     //es una pila, entonces para operar x op y hay que tener en cuenta que primero sacamos y, después x.
     y = cima(p);
     desapilar(p);
     x = cima(p); 
     desapilar(p);

     if(operador == '+'){
          apilar(p, x + y);
     } else if(operador == '-'){
          apilar(p, x - y);
     } else if(operador == '*'){
          apilar(p, x * y);
     } else if(operador == '/'){
          apilar(p, x / y);
     }
}

elementoev evaluar(const tabla_valores & t, string s){
     Pila_char pila_operadores = crear_pilachar_vacia(); 
     Pila_float pila_numeros = crear_pilafloat_vacia(); 
     elementoev result; 

     //Si hay una letra pasa directa
     //( y +, -, *, / -> se aplica 
     //Al apilar comprobamos si debajo tiene un operador con precedencia mayor, en tal caso se sacan y se apila el resultado 
     // ) -> Sale todo hasta encontrar( . 
     //El resultado final quedará como único elementoev de la pila 
     
     //Recorremos toda la expresión 
     for(int i = 0; i < s.length(); i++){
          char var = s[i];
          //Parentesis abierto -> apilar 
          if(var == '('){
               apilarChar(pila_operadores, var); 
          }
          //tenemos operadores apilados y el primero no es '(' y la cima de la pila tiene más precedencia que var, entonces operar y apilar.
          else if(var == '+' || var == '-' || var == '*' || var == '/'){
               while(!es_pilaVaciaChar(pila_operadores) &&  cimaChar(pila_operadores) != '(' && precedencia(var, cimaChar(pila_operadores))){
                    char quitar = cimaChar(pila_operadores);
                    desapilarChar(pila_operadores); 
                    operar(pila_numeros, quitar);
               }
               apilarChar(pila_operadores, var);  
          }
          //parentesis cerrado -> operar y desapilar 
          else if(var == ')'){
               while(cimaChar(pila_operadores) != '('){
                    char quitar = cimaChar(pila_operadores);
                    desapilarChar(pila_operadores); 
                    operar(pila_numeros, quitar);
               }
               desapilarChar(pila_operadores);
          } 
          //numero -> apila 
          else{
               apilar(pila_numeros, get_value(t, var));
          }  
     //mostrar(pila_numeros);
     //mostrarChar(pila_operadores); 
     }
     //Una vez recorrido todo el string, la pila puede contener más de un operador, en cualquier caso sólo quedaría operarlos porque no serían parentesis. Hay que operar hasta agotar los operadores. 
     while (!es_pilaVaciaChar(pila_operadores)){
          char quitar = cimaChar(pila_operadores);
          desapilarChar(pila_operadores); 
          operar(pila_numeros, quitar);
     }
     
     result = cima(pila_numeros);
     return result; 
}

int main(){
    tabla_valores t;
    inicializa(t);
    string s;
    cin >> s;
    while(s!="exit"){
       char v=s[0];
       float valor;
       if(s.find("<-")!=-1){
            valor = stof(s.substr(3));
            put_value(t,v,valor);
       }
       else if (s.find("=")!=-1){
          valor = evaluar(t,s.substr(2));
          put_value(t,v,valor);
       }
       else{
            cout << get_value(t,v) << endl;
       }
       cin >> s;
     }
    
    return 0;
}
