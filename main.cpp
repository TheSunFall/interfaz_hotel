#include <iostream>
#include <string.h>
#include "admin.cpp"
#include "typedef.h"

using namespace std;
// TODO: guardar la contaseña en un txt
int main()
{
    habitacion hotel[8][4];
    char passwd[15] = {'\000'};
    int op = 1;
    cout << "¡Bienvenido!";
    while (op)
    {
        cout << "---------------------------------------------\n";
        cout << "1. Ver habitaciones disponibles\n";
        cout << "2. Registrar huésped\n";
        cout << "3. Registrar salida de huésped\n";
        cout << "4. Interfaz administrativa\n";
        cout << "0. Salir\n";
        cout << "---------------------------------------------\n";
        cout << "-> ";
        cin >> op;
        switch (op)
        {
        case 1:
            for (int i = 0; i < 8; i++)
            {
                int e = 0;
                cout << i << "° piso: \n";
                for (int j = 0; j > 4; j++)
                {
                    if (hotel[i][j].huespdesActuales < hotel[i][j].capacidadMax)
                    {
                        cout << "Habitacion N°: " << hotel[i][j].codigo;
                        cout << "Tipo: " << hotel[i][j].tipo; // TODO: implementar switch
                        e++;
                    }
                }
                if (e == 0)
                {
                    cout << "No hay habitaciones disponibles en este piso.";
                }
            }
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            if (passwd[0] = '\000')
            {
                cout << "Cree una nueva contrasena\n";
                fgets(passwd, 15, stdin);
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    char p[15] = {'\000'};
                    cout << "Ingrese contrasena: ";
                    fgets(p, 15, stdin);
                    if (strcmp(p, passwd) == 0)
                    {
                        admin();
                    }
                    else
                    {
                        cout << "Contrasena incorrecta, intente de nuevo";
                    }
                }
            }
        case 0:
            cout << "Saliendo... \n";
            break;
        default:
            cout << "Opcion no valida, intente de nuevo";
            break;
        }
    }
}