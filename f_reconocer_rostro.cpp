#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct SaldoColaborador {
char rut [11];
int saldo_desayuno ;
int saldo_almuerzo ;
int saldo_once ;
int saldo_cena ;
};

// Función que simula el reconocimiento facial (pidiendo el rut) y 
// devuelve el mismo RUT (si fue reconocido como colaborador) o un string vacío si no se reconoce

string reconocerRostro() {
    string rut;
    cout<<"ingrese su Rut: \n";
    cin>> rut;
    int N;
    ifstream fp; 
    fp.open("saldos.bin", ios::binary);
    if (!fp.is_open()){
        cerr<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }
    SaldoColaborador colaborador;
    fp.read((char *)&N, sizeof(int));
    cout<<"Cantidad de structs: "<<N<<endl;
    for (int i = 0; i<N ; i++) {
        fp.read((char *)&colaborador, sizeof(SaldoColaborador));
        cout<< colaborador.rut <<"<---"<<endl;
        if (colaborador.rut==rut){
            cout<<"Colaborador confirmado"<<endl;
            return rut;

        }
    }
    return "";
    return "No es colaborador";  //cuando se entregue la tarea hay que dejarlo de la forma --return "";
                            //le puse el "string vacio para que sea mas claro cuando no empareja el rut"
     
}

int main(){
    string run = reconocerRostro();
    cout<<"Rut: "<<run<<endl;
    return 0;
}



