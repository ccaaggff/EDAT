#include <iostream>
#include <math.h> //pow 

using namespace std; 

struct doble_string{
    string cociente; 
    string resto; 
};

//PRINCIPALES
//suma a y b
string suma(string a, string b);
//En el caso de la resta, hará a - b, de modo que si b > a el resultado será negativo
string restar(string a, string b);
//multiplica a por b
//string multiplicacion(string a, string b);
string multiplicacion(string a, string b);
//divide a entre b suponiendo a > b
doble_string division(string a, string b);


//AUXILIARES
string reverse(string a);
void orden(string a, string b, string & mayor, string & menor, int & signo);
void igualar(string a, string b, string & c, string & d);
string intTostring(int x);
bool mAyor(string a, string b); 
bool iguales(string a, string b); 
string qCeros(string a);

int main(){
    
    string s1, s2, s3, s4, s5, s6, r1, r2, r3, r4, r5;
    string s7, s8, r6, r7;
    doble_string r8; 

    s1 = "123";
    s2 = "12";
    s3 = "543";
    s4 = "181";
    s5 = "1234";
    s6 = "224";
    s7 = "145694837598";
    s8 = "123321331232112432423143";
    
    r1 = suma(s1, s2);
    r2 = restar(s5, s3);
    r3 = restar(s2,s1);
    r4 = suma(s5, s3); 
    r5 = multiplicacion(s6, s4); 
    r6 = suma(s7,s8);
    r8 = division(s1, s2);
        
    cout << "123 + 12 = " << r1 << endl;        //135
    cout << "\n1234 - 543 = " << r2 << endl;    //691
    cout << "\n12 - 123 = " << r3 << endl;      //-111
    cout << "\n1234 + 543 = " << r4 << endl;    //1777
    cout << "\n224 * 81 = " << r5 << endl;      //40544
    cout << "\n145694837598 + 123321331232112432423143 = " << r6 << endl; 

    cout << "\n123 / 12 es: " << endl; 
    cout << "cociente = " << r8.cociente << endl; //10
    cout << "resto = " << r8.resto << endl;       //3

    return 0;    
}


string suma(string a, string b){
/*  
    Si la longitud de la cadena a es igual a la longitud de la cadena b entonces la suma se realiza
    recorriendo ambas cadena de derecha a izq. Por eso los bucles recorren desde la longitud de la cadena
    hasta el indice 0 que representamos como (indice > -1). Si las cadenas no tienen la misma longitud, la subrrutina 
    igualar se encarga de poner 0s a la izq de la cadena con menor longitud. Con esto, se efectua la suma 
    utilizando la tabla ascii donde tenemos asociados 0:48, 1:49, ..., 9:57 de esta forma si sumamos los asci 
    de cada char de la cadena y nos quedamos con el resto mod 48 obtenemos el int de la suma. Para almecenar 
    la posible decena que nos llevamos (ej: 9+9 = 18 -> te llevas 1) utilizamos una variable aux. 
    NOTA: int + '0' -> convierte el int en string. 
*/     
    //igualamos la longitud de las cadenas
    string c;
    string d; 
    igualar(a, b, c, d);                                

    string sum_s;                                       //variable para acumular la suma 
    int ll = 0;                                         //variable que acumula la decena en caso de llevada
    int result = 0;                                     //Var aux que calcula la suma de los dos char correspondientes al paso del bucle 
    
    for(int i = c.length() - 1; i > -1; i--){
        result = ( int(c[i]) + int(d[i]) ) % 48;
        result += ll;
        ll = 0; 
        if (result >= 10){
            ll = 1; 
            sum_s += (result - 10) + '0';
            if(i == 0){
                sum_s += '1';
            }
        }else{
            sum_s += result + '0';
        }
    } 
    sum_s = reverse(sum_s); 
    return sum_s;
}

string restar(string a, string b){
    /*La resta tiene una idea similar a la suma, sólo hay que tener cuidado de restar al mayor el menor y si el 
    sustraendo es más grande que el minuendo a la diferencia se le concatena un signo de - delante. 
    */
    //Variables para igualar la longitud de las cadenas y saber cuál natural es más grande.
    string mayor; 
    string menor;  
    string c;
    string d;
    int signo; 
    
    orden(a, b, mayor, menor, signo);                          
    igualar(mayor, menor, c, d);                        //en la salida siempre tendremos que: c > d
    
    string dif_s;
    
    int ll = 0;                                         //unidad de llevada
    int result = 0;                                     //var aux con la diferencia de los char correspondientes al paso del bucle 
    
    for(int i = c.length() - 1; i > -1; i--){
        if (c[i] < d[i]){                               //en este caso al restar me voy a llevar una y se debe 
            result = -1 * (( (int(d[i]) + int(ll)) - int(c[i]) ) % 48);   
        }
        else{
            result = ( int(c[i]) - (int(d[i]) + int(ll))  ) % 48;
        }
        //actualizando
        ll = 0; 
        
        if (result < 0){
            ll = 1; 
            dif_s += (result + 10) + '0';
        }
        else{
            dif_s += result + '0';
        }
    }
    dif_s = reverse(dif_s);

    //restas cuyo diferencia es negativa
    if (signo == -1){
        dif_s = "-" + dif_s;
    }

    return dif_s;
}

string multiplicacion(string c, string d){
/* 
    Para multiplicar dos números tenemos un problema con las unidades que de la llevada, 
    debido a que hay productos de números del 0 al 9 cuyo resultado es mayor que 48, por
    lo que al hacer el resultado de los ascii modulo 48 no se obtiene el resultado deseado 
    (por ej: 9 * 9 = 33). En este caso la filosofía de la implementación ha sido pasar 
    cada caracter a int y guardar los resultados en result. Para las llevadas tenemos que
    distinguir la última pasada del bucle, del resto pues en la último no hay llevada.
    Finalmente, para obtener el resultado hacemos
        2 2 4 
      x 1 8 1
      --------
            2 2 4 -> 224  * 10^0 -> Concateno 0 ceros al final del string
      + 1 7 9 2   -> 1792 * 10^1 -> Concateno 1 ceros al final del string
        2 2 4     -> 225  * 10^2 -> Concateno 2 ceros al final del string
    hay que tener distinguir, en este caso, el primer paso del bucle para no concatenar nada.
*/
    int result = 0; 
    int ll = 0;    

    //var aux del calculo
    string next_s = ""; 
    string prod_s;
    string ceros;

    //igualamos la longitud de las cadenas
    string a;
    string b; 
    igualar(c, d, a, b);


    for(int i = a.length() - 1; i > -1; i--){
        for(int j = b.length() - 1; j > -1; j--){
            result = (b[i]-'0') * (a[j]-'0') + ll;
            ll = 0;
            if (result >= 10){
                if(j == 0){
                    ll = result / 10;
                    prod_s += ((result % 10) + '0');
                    prod_s += (ll + '0');
                }
                else{
                    ll = result / 10;
                    prod_s += (result % 10) + '0';
                }    
           }
           else{
                prod_s += result + '0';
           }
        }
        
        prod_s = reverse(prod_s); 

        if (i != a.length() - 1){
            ceros += '0';
            prod_s = prod_s + ceros;  
            next_s = suma(next_s, prod_s);    
        }
        else{
            next_s = suma(next_s, prod_s);
        }
        prod_s = ""; 
        ll = 0; 
    }
    return next_s; 
}

doble_string division(string a, string b){
/*
    El funcionamiento se basa en ir restando tantas veces como sea necesario, hasta que el resto sea 
    menor que divisor.  
*/    
    doble_string result; 
    result.cociente = ""; 
    result.resto = suma(b, "1"); //inicialización para que no de problema con las condiciones del parada

    string c = "0";             //el número de veces que se recorre el bucle es el cociente de la división entera
    
    while (mAyor(result.resto, b) || iguales(result.resto, b)){
        c = suma(c, "1");
        result.cociente = restar(a, b); 
        result.resto = qCeros(result.cociente); 
        a = result.cociente; 
    }
    
    result.cociente = c; 

    return result; 
}

//FUNCIONES AUXILIARES
void igualar(string a, string b, string & c, string & d){
    //Iguala las longitudes de las cadenas a y b poniendo 0s a la izq de la cadena más corta
    int dif = a.length() - b.length();
    string ceros_a; 
    string ceros_b; 
    c = a; 
    d = b; 
    
    if (dif < 0){   //longgitud de la cadena a menor que la longitud de la cadena b
        for (int i = 0; i < abs(dif); i++){
            ceros_a += '0';
        }
        c = ceros_a + a; 
    }
    else{           //longgitud de la cadena b menor que la longitud de la cadena a
        for (int i = 0; i < dif; i++){
            ceros_b += '0';
        }
        d = ceros_b + b; 
    }
}

void orden(string a, string b, string & mayor, string & menor, int & signo){ 
    /*Devuelve en mayor la cadena que tiene el int más grande. En signo guarda un 1 si a > b y un -1 si a < b
    de forma que si el sustraendo es mayor que el minuendo la diferencia será negativa*/
    if(a.length() == b.length()){
        if(a[0] > b[0]){
            mayor = a;
            menor = b;
            signo = 1;   
        }
        else{
            mayor = b;
            menor = a;
            signo = -1; 
        }
    }
    else if(a.length() > b.length()){
        mayor = a;
        menor = b;
        signo = 1;
    }
    else{
        mayor = b;
        menor = a;
        signo = -1; 
    } 
}

string intTostring(int x){
    string result; 
    int digito = x;
    int cifra;  

    while (digito != 0){
        cifra = digito % 10;
        result += cifra - '0';
        digito /= 10; 
    }
     
    return result; 
}

int stringToint(string s){
    int result; 
    int N = 0;  

    for (int i = 0; i < s.length(); i++){
        result += (s[i] - '0') * pow(10,N);
        N++;
    }

    return result; 
}

string qCeros(string a){
    string result; 
    if (a.length() > 1){
        for (int i = 1; i < a.length(); i++){
            if ((a[i] != '0') || (a[i-1] != '0')){
            result += a[i]; 
            }
        }
    }
    else{
        result = a; 
    }
    return result; 
}

bool iguales(string a, string b){
    bool result = false; 
    int n = 0;

    while((n < a. length()) && (a.length() == b.length())){
        if (int(a[n]) == int(b[n])){
            result = true; 
        }
        else{
            result = false;
            break;
        }
        n++;
    }
    
    return result;
}

bool mAyor(string a, string b){
    bool result;
    bool aux; 
    aux = iguales(a,b); 
    if(aux){
        return false; 
    } 
    if(a.length() == b.length()){
        if(a[0] > b[0] || iguales(a,b)){
            result = true;   
        }
        else{
            result = false; 
        }
    }
    else if(a.length() > b.length()){
        result = true; 
    }
    else{
        result = false;  
    } 

    return result; 
}

string reverse(string a){
//Devuelve la cadena invertida
    string result;
    if (a.length() == 1){
        result = a; 
    }
    else{
        for (int i = a.length(); i > -1; i--){
            result += a[i];       
        }
    } 
    return result; 
}