#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//NOTA IMPORTANTE: AL TERMINAR EL CODIGO, BORRAR TODOS LOS COUT, SI NO, SE EVALUARA DE FORMA NEGATIVA.
/*NOTA COSAS QUE FALTAN:
1.- Verificar que servicio se esta pidiendo
2.- Crear el archivo ASCII que registra todos los servicios del dia, el servicio se guarda en mayusculas y registrar los siguientes servicios.
3.- Verificar si el comprador puede seguir comprando con su sueldo*/

int const SERV_DESAYUNO = 0; //Indica que servicio es
int const SERV_ALMUERZO = 1;
int const SERV_ONCE = 2;
int const SERV_CENA = 3;

struct SaldoColaborador { //No actualizar, solo consultar.
      char rut [11];
      int saldo_desayuno ;
      int saldo_almuerzo ;
      int saldo_once ;
      int saldo_cena ;
   };

bool trabajador(string rut_trabajador, string* lut, int largo){
        for (int i = 0; i < largo; i++){
        if (std::string(rut_trabajador) == std::string(lut[i])) {
            return true;
    }}
   return false;

}

bool puedeConsumir(char* rut, int servicio, string consumos_dia){

   ifstream saldos("saldos.bin", ios::binary);
   if (saldos.is_open()) {
        int n;
        saldos.read(reinterpret_cast<char*>(&n), sizeof(n));
        string *lut = new string[n]; // Obtener el numero de ruts en el archivo y usarlos para crear arrays dinamicos con los saldos y rut.
        int *desayuno = new int[n];
        int *almuerzo = new int[n];
        int *once = new int[n];
        int *cena = new int[n];
        for (int i = 0; i < n; i++) {
            SaldoColaborador sc;
            saldos.read(reinterpret_cast<char*>(&sc), sizeof(sc));
            
            lut[i] = sc.rut;
            desayuno[i] = sc.saldo_desayuno;
            almuerzo[i] = sc.saldo_almuerzo;
            once[i] = sc.saldo_once;
            cena[i] = sc.saldo_cena;
            cout << lut[i] << " Desayuno: " << desayuno[i] << " Almuerzo: "<< almuerzo[i] << " Once: " << once[i] << " Cena: " << cena[i] << endl;  //Para comprobar si los datos se guardaron correctamente Nota: Borrar cuando el codigo este listo

            /* if (std::string(rut) == std::string(sc.rut)) { -- ¿Ignorar yo creo? Era para comprobar una cosa mas que nada

               cout << "Rut valido" << endl;
            

            } else {
               cout << "Rut Invalido" << endl;
            } */ 

            /*cout << "Rut: " << sc.rut << endl;
            cout << "Saldo Desayuno: " << sc.saldo_desayuno << endl;
            cout << "Saldo Almuerzo: " << sc.saldo_almuerzo << endl;
            cout << "Saldo Once: " << sc.saldo_once << endl;
            cout << "Saldo Cena: " << sc.saldo_cena << endl;
            cout << endl;*/
        } 
          //empezar desde aqui el resto del codigo?
          //1°, Comprobar que el rut forma parte de los trabajadores
          
          if (trabajador(rut, lut, n) == true){
            // Evaluar con los respectivos saldos de los servicios.
            cout << "Existe" << endl;
          } else{
            // Evaluar con saldo 0 en todos los servicios.
            cout << "No existe" << endl;
          }
            
          
        
        
        
        
        
          delete[] lut; //Borrar la memoria dinamica
          delete[] desayuno;
          delete[] almuerzo;
          delete[] once;
          delete[] cena;
    } else {
        cout << "Error al abrir el archivo" << endl;
    }

   saldos.close();
   return true;
}

int main() {

   cout << puedeConsumir("22222222-2", 0, "consumoDiario.txt") << endl;

   return 0;
}