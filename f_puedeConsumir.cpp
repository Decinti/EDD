#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

int const SERV_DESAYUNO = 0;
int const SERV_ALMUERZO = 1;
int const SERV_ONCE = 2;
int const SERV_CENA = 3;

struct SaldoColaborador {
char rut [11];
int saldo_desayuno ;
int saldo_almuerzo ;
int saldo_once ;
int saldo_cena ;
};

// Funcion de apoyo
// Función para registrar un consumo en el archivo de texto
void registrarConsumo(const char* rut, int servicio) {
    // Aquí debes implementar la escritura en el archivo de texto para registrar el consumo del colaborador en el servicio indicado.
    
    // Crear un archivotxt donde se almacene el rut del que consumio + el servicio que usó.


}

// Funcion de apoyo
// Función para obtener el saldo de un colaborador en un servicio específico
int obtenerSaldo(const char* rut, int servicio) {
    // Aquí debes implementar la lectura del archivo saldos.bin y devolver el saldo del colaborador y servicio solicitado.
    int N, saldo=0;
    ifstream fp;
    fp.open("saldos.bin", ios::binary);
    if (!fp.is_open()){
        cerr<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }
    fp.read((char *)&N,sizeof(int));
    //cout<<N<<endl;
    SaldoColaborador colaborador;
    for (int i = 0 ; i<N ; i++){
        fp.read((char *)&colaborador, sizeof(SaldoColaborador));
        cout<< colaborador.rut <<"<---"<<endl;
        if (colaborador.rut== string(rut)){
            cout<<"Colaborador encontrado"<<endl;
            if (servicio==0){
                saldo = colaborador.saldo_desayuno;
                return saldo;
            }else if(servicio==1){
                saldo = colaborador.saldo_almuerzo;
                return saldo;
            }else if(servicio==2){
                saldo = colaborador.saldo_once;
                return saldo;
            }else if(servicio==3){
                saldo = colaborador.saldo_cena;
                return saldo;
            }
        }    
    }
    return saldo;
}

// Función para obtener el saldo de un colaborador en un servicio específico
bool puedeConsumir(char* rut, int servicio, string consumos_dia) {
    // Aquí debes implementar la lectura del archivo saldos.bin y devolver el saldo del colaborador y servicio solicitado.


}

int main(){
    string run = "28738231-0";
    bool f;
    string archivotxt="Consumos_dia"; 
    int serv;
    cout<<"seleccione su servicio(0, 1, 2, 3): "<<endl;
    cin>>serv;
    string servicio; 
    if (serv==0){
        servicio = "desayuno";
    }else if(serv==1){
        servicio = "almuerzo";
    }else if(serv==2){
        servicio = "once";
    }else if(serv==3){
        servicio = "cena";
    }
    int serv_colab;

    //probando serv_colab (debe devolver el saldo del colaborador en el servicio ingresado)
    serv_colab = obtenerSaldo(run.c_str(), serv);
    cout<<"el saldo del colaborador en el servicio "<<servicio<<" es "<<serv_colab<<endl;



    /*f = puedeConsumir(&run[0], N, archivotxt)
    if (f)[
        cout<<"si puede consumir"<<endl;
    ] else {
        cout<<"no puede consumir"<<endl;
    }*/


    return 0;
}

