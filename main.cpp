#include <iostream>
using namespace std;
#include <stdlib.h>
#include <string.h>
#define TML 5
#include "Cliente.h"
#include "Fecha.h"
#include "Abono.h"
#include "Cuenta.h"

int menu(){
    int op;
    cout << "MENU DE OPCIONES\n";
    cout << "1. Agregar clientes a la lista\n";
    cout << "2. Agregar cuenta a la lista\n";
    cout << "3. Hacer abonos\n";
    cout << "4. Mostrar lista de clientes\n";
    cout << "5. Mostrar lista de cuentas\n";
    cout << "6. Mostrar detalles de la cuenta\n";
    cout << "7. Salir\n";
    cout << "Digite la opcion : ";
    cin >> op;
    return op;

}

Cliente *BuscarCliente(Cliente *lst[], int cont, int db){
    bool encontrado = false;
    int contador = 0;
    Cliente *cli = NULL;
    while (contador < cont && !encontrado){
        if (lst[contador]->getIdCliente() == db){
            encontrado = true;
            cli = lst[contador];
        }
        else{
            contador++;
        }
    }
    return cli;
}

Cuenta *BuscarCuenta(Cuenta *lst[], int cont, int db){
    bool encontrado = false;
    int contador = 0;
    Cuenta *cu = NULL;
    while (contador < cont && !encontrado){
        if (lst[contador]->getNumeroCuenta() == db){
            encontrado = true;
            cu = lst[contador];
        }
        else{
            contador++;
        }
    }
    return cu;
}

Cliente *agregarCliente(){
    int id;
    string n, a;
    Cliente *cli;
    cout << "Digite el id del cliente : ";
    cin >> id;
    cout << "Digite el nombre del cliente : ";
    cin >> n;
    cout << "Digite el apellido del cliente : ";
    cin >> a;
    cli = new Cliente(id, n, a);
    return cli;
}

Cuenta *agregarCuenta(Cliente *cli){
    int nc;
    float sl;
    Cuenta *cnt;
    cout << "Digite el numero de la cuenta : ";
    cin >> nc;
    cout << "Digite el saldo : ";
    cin >> sl;
    cnt = new Cuenta(nc, cli);
    return cnt;
}

void registrarAbono(Cuenta *cnt){
    int d,m,a;
    Fecha *fa;
    float mp;
    Abono *ab;
    cout << "Digite la fecha del abono : \n";
    cin >> d;
    cin >> m;
    cin >> a;
    cout << "Digite el monto del pago : ";
    cin >> mp;
    fa = new Fecha(d,m,a);
    ab = new Abono(fa, mp);
    cnt->agregarAbono(ab);
}

void mostrarDetalles(Cuenta *cnt){
    cout << "El numero : " << cnt->getNumeroCuenta() << endl;
    cout << "Cliente : " << cnt->getCliente()->getNombre() << " " << cnt->getCliente()->getApellido() << endl;
    cout << "Saldo : " << cnt->getSaldo() << endl;
    if (cnt->getContadorAbonos() == 0){
        cout << "No tienes abonos registrados\n";
    }
    else{
        Abono **lista = cnt->getLstAbonos();
        cout << "No\tFecha\tMonto\n";
        for (int i=0;i<cnt->getContadorAbonos();i++){
            cout << (i+1) << "\t";
            lista[i]->getFechaAbono()->mostrarFecha();
            cout << "\t" << lista[i]->getMontoAbono() << endl;
        }
    }
}

int main(){
    Cliente *lstCliente[TML];
    Cuenta *lstCuenta[TML];
    Cliente *cli=NULL;
    Cuenta *cnt=NULL;


    int opc, contCli=0, contCnt=0, idCli, idCnt;
    do{
        system("cls");
        opc = menu();
        switch(opc){
            case 1:
                ///Agregar clientes
                if(contCli < TML){
                    lstCliente[contCli] = agregarCliente();
                    contCli++;
                    cout << "El cliente se agrego con exito\n";
                }
                else{
                    cout << "La lista de clientes esta llena\n";
                }
                break;
            case 2:
                ///Agregar cuentas
                if(contCnt < TML){
                    cout << "Digite el id del cliente : ";
                    cin >> idCli;
                    cli = BuscarCliente(lstCliente, contCli, idCli);
                    if (cli){
                        lstCuenta[contCnt] = agregarCuenta(cli);
                        contCnt = contCnt + 1;
                        cout << "El prestamo se agrego con exito\n";
                    }
                    else{
                        cout << "La lista de prestamos esta llena\n";
                    }
                }
                else{
                    cout << "La lista esta llena\n";
                }
                break;
            case 3:
                ///Hacer abonos
                cout << "Digite el numero de la cuenta : ";
                cin >> idCnt;
                cnt = BuscarCuenta(lstCuenta, contCnt, idCnt);
                if (cnt){
                    registrarAbono(cnt);
                    cout << "El abono se registro con exito\n";
                }
                else{
                    cout << "El cliente no existe, no se puede agregar el abono\n";
                }
                break;
            case 4:
                ///Mostrar clientes
                if (contCli == 0){
                    cout << "La lista esta vacia\n";
                }
                else{
                    cout << "id\tNombre\tApellido\n";
                    for (int i=0;i<contCli;i++){
                        cout << lstCliente[i]->getIdCliente() << "\t";
                        cout << lstCliente[i]->getNombre() << "\t";
                        cout << lstCliente[i]->getApellido() << "\n";
                    }
                }
                break;
            case 5:
                ///Mostrar cuentas
                if (contCli == 0){
                    cout << "La lista esta vacia\n";
                }
                else{
                    cout << "No\tCliente\tSaldo\n";
                    for (int i=0;i<contCnt;i++){
                        cout << lstCuenta[i]->getNumeroCuenta() << "\t";
                        cout << lstCuenta[i]->getCliente()->getNombre() << " " << lstCuenta[i]->getCliente()->getApellido() << "\t";
                        cout << lstCuenta[i]->getSaldo() << endl;
                    }
                }
                break;
            case 6:
                ///Ver detalles de prestamo
                cout << "Digite el numero de la cuenta : ";
                cin >> idCnt;
                cnt = BuscarCuenta(lstCuenta, contCnt, idCnt);
                if (cnt){
                    mostrarDetalles(cnt);
                }
                else{
                    cout << "la cuenta no existe, no se pueden validar los detalles";
                }
                break;
            case 7:
                cout << "Saliendo del programa\n";
                break;
            default:
                cout << "Error, esa opcion no es valida\n";
                break;
        }
        system("pause");
    }while (opc!=7);

    return 0;
}
