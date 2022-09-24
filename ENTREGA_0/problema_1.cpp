#include<iostream>

using namespace std; 

int const N = 10;

struct Lista_int{
    int pos[N];
    int num_ap = 0;
};

void mostrar(Lista_int & l); 
Lista_int apariciones(string s1,string s2);


int main(){
    Lista_int l; 
    l = apariciones("Hola","Hola,Hola,Hola");
    mostrar(l);
    
    return 0; 
}

Lista_int apariciones(string s1,string s2){
    Lista_int result;                                       //donde se almacenan las posiciones y la cantidad de posiciones significativas que hay
    int n1 = 0;                                             //var para recorrer s1
    int indice = 0;                                         //var para introducir los valores en result.pos[indice]
    int n2 = 0;                                             //var para recorrer s2

    while (n2 < s2.length()){
        while (n1 < s1.length()){
            if ((s1[n1] == s2[n2])){
                n1++;
                n2++;
                if (n1 == s1.length() - 1){
                    result.num_ap++; 
                    result.pos[indice] = n2 - n1;
                    indice++; 
                } 
            }
            else{
                n1 = s1.length();
                n2++; 
            }
        }  
        n1 = 0; 
    }
    return result; 
}



void mostrar(Lista_int & l){
    cout << "[";
    for(int i = 0; i < l.num_ap; i++){
        if (i != l.num_ap - 1 ){
           cout << l.pos[i] << ", ";
        }
        else{
            cout << l.pos[i];
        }
    }
    cout << "]" << endl; 
} 