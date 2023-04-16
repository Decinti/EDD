#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

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

bool colaborador(string rut_colaborador, string* lut, int largo){
        for (int i = 0; i < largo; i++){
        if (string(rut_colaborador) == string(lut[i])) {
            return true;
    }}
   return false;
}
/*****
* Bool colaborador
******
* La función identifica si el rut esta o no esta presente dentro del archivo con los saldos de los colaboradores.
******
* Input:
* tipoParámetro NombreParámetro : Descripción Parámetro
* string rut_colaborador : Rut del colaborador identificado.
* string* lut : array con los ruts de los colaboradores.
* int largo : largo del array lut 
******
* Returns:
* return false/true, la funcion retornara true si el rut se encuentra en el array. Retornara false en otro caso.
*****/

bool puedeConsumir(char* rut, int servicio, string consumos_dia){
   string lineaux;
   ifstream saldos("saldos.bin", ios::binary);
   if (saldos.is_open()) {
         int n;
         SaldoColaborador s; //Se crea una variable "s" del struct SaldoColaborador
         saldos.read((char *) &n, sizeof(n));
         string *lut = new string[n]; // Obtener el numero de ruts en el archivo y usarlos para crear arrays dinamicos con los saldos y rut.
         int *desayuno = new int[n];
         int *almuerzo = new int[n];
         int *once = new int[n];
         int *cena = new int[n];
         for (int i = 0; i < n; i++) {            
            saldos.read((char *) &s, sizeof(s));
            lut[i] = s.rut;
            desayuno[i] = s.saldo_desayuno;
            almuerzo[i] = s.saldo_almuerzo;
            once[i] = s.saldo_once;
            cena[i] = s.saldo_cena;
        } 
         saldos.close(); //Cerrar el archivo de saldos dado que ya no es necesario.
         int pos = 0;
         int saux = 0; // Se crea una variable para la posición y un auxiliar que identifica el numero de veces que se ha usado un servicio.
         if (colaborador(rut, lut, n) == true){
            for (int i = 0; i < n; i++){
               if (string(rut) == string(lut[i])) {
                  pos = i;
               }}
            fstream consumo;
            switch (servicio){

               case 0:                  
                  consumo.open(consumos_dia, ios::in);
                  if (!consumo.is_open()){
                     cout << "Error al abrir el archivo" << endl;
                  }else{
                     while (getline(consumo, lineaux)){
                        string Rut_Actual;
                        string Servicio_diario;
                        consumo >> Rut_Actual >> Servicio_diario;
                        if (Rut_Actual == rut and Servicio_diario == "DESAYUNO"){
                           saux += 1;
                           }
                        }
                     consumo.close();
                     consumo.open(consumos_dia, ios::app);
                     
                     if (desayuno[pos]-saux > 0){
                        consumo << rut << " DESAYUNO" << endl;

                        consumo.close();
                     }else{

                        return false;
                     }                     
                     }
                     break;
               case 1:                  
                  consumo.open(consumos_dia, ios::in);
                  if (!consumo.is_open()){
                     cout << "Error al abrir el archivo" << endl;
                  }else{
                     while (getline(consumo, lineaux)){
                        string Rut_Actual;
                        string Servicio_diario;
                        consumo >> Rut_Actual >> Servicio_diario;
                        if (Rut_Actual == rut and Servicio_diario == "ALMUERZO"){
                           saux += 1;
                           }
                        }
                     consumo.close();
                     consumo.open(consumos_dia, ios::app);
                     
                     if (almuerzo[pos]-saux > 0){
                        consumo << rut << " ALMUERZO" << endl;
                        consumo.close();
                     }else{
                        return false;
                     }
                     }
                     break;
               case 2:                  
                  consumo.open(consumos_dia, ios::in);
                  if (!consumo.is_open()){
                     cout << "Error al abrir el archivo" << endl;
                  }else{
                     while (getline(consumo, lineaux)){
                        string Rut_Actual;
                        string Servicio_diario;
                        consumo >> Rut_Actual >> Servicio_diario;
                        if (Rut_Actual == rut and Servicio_diario == "ONCE"){
                           saux += 1;
                           }
                        }
                     consumo.close();
                     consumo.open(consumos_dia, ios::app);
                     
                     if (once[pos]-saux > 0){
                        consumo << rut << " ONCE" << endl;
                        consumo.close();
                     }else{
                        return false;
                     }
                     }
                     break;
               case 3:                 
                  consumo.open(consumos_dia, ios::in);
                  if (!consumo.is_open()){
                     cout << "Error al abrir el archivo" << endl;
                  }else{
                     while (getline(consumo, lineaux)){
                        string Rut_Actual;
                        string Servicio_diario;
                        consumo >> Rut_Actual >> Servicio_diario;
                        if (Rut_Actual == rut and Servicio_diario == "CENA"){
                           saux += 1;
                           }
                        }
                     consumo.close();
                     consumo.open(consumos_dia, ios::app);                     
                     if (cena[pos]-saux > 0){
                        consumo << rut << " CENA" << endl;
                        consumo.close();
                     }else{                       
                        return false;
                     }
                     }
                     break;
               }
          } else{
            // Se evalua con saldo 0 en todos los servicios, por lo que no puede conseguir almuerzo.
            return false;
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
/*****
* Bool puedeConsumir
******
* La función identifica el numero de colaboradores en el archivo saldos.bin y los usa para crear array´s usando memoria dinamica para el rut y los servicios.
* Si el colaborador esta presente en los ruts del archivo saldos.bin, identificara si tiene saldo suficiente para usar el servicio que solicito.
******
* Input:
* tipoParámetro NombreParámetro : Descripción Parámetro
* char* rut : Puntero de un arreglo de caracteres, en este caso, el rut del colaborador.
* int servicio : Identifica quee servicio esta pidiendo segun las constantes int : SERV_DESAYUNO ; SERV_ALMUERZO ; SERV_ONCE ; SERV_CENA.
* string consumos_dia : Es el nombre del archivo ASCII que contiene los consumos del día.
******
* Returns:
* return true/false, La función retornara true si identifica que el colaborador tiene suficiente saldo como para comprar el servicio solicitado, en otro caso, retornara false al no tener saldo suficiente o no estar identificado.
*****/

int main() {
   char rutt[11] = "22222222-2";
   cout << puedeConsumir(rutt, 0, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 0, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 0, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 0, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 0, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 1, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 1, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 1, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 2, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 2, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 2, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 2, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 3, "consumoDiario.txt") << endl;
   cout << puedeConsumir(rutt, 3, "consumoDiario.txt") << endl;
   return 0;
}