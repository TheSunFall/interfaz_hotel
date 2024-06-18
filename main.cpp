#include <iostream>
#include <fstream>
#include <locale.h>
#include <string.h>

using namespace std;
// TODO: guardar la contaseña en un txt
struct reserva
{
    int codHabitacion;
    char fechaInicio[9];
    char fechaFin[9];
};
struct huesped
{
    char nombre[30];
    char pais[20];
    int id;
    reserva res;
};
struct habitacion
{
    int codigo = 0;
    char tipo = '\0';
    int capacidadMax = 0;
    float precioNoche = 0;
    int huespdesActuales = 0;
    huesped huespedes[2];
};
void admin(habitacion (&)[8][4]);
void aniadir_habitacion(habitacion (&)[8][4]);
void ver_habitaciones_disponibles(habitacion (&)[8][4]);
void modificar_habitacion(habitacion (&)[8][4]);
int main()
{
    setlocale(LC_ALL, "es_PE");
    habitacion hotel[8][4];
    char passwd[15] = {'\000'}, p[15] = {'\000'};
    int op = 1;
    cout << "¡Bienvenido!\n";
    while (op)
    {
        cout << "---------------------------------------------\n";
        cout << "1. Ver habitaciones disponibles\n";
        cout << "2. Registrar huesped\n";
        cout << "3. Registrar salida de huesped\n";
        cout << "4. Interfaz administrativa\n";
        cout << "0. Salir\n";
        cout << "---------------------------------------------\n";
        cout << "-> ";
        cin >> op;
        switch (op)
        {
        case 1:
            ver_habitaciones_disponibles(hotel);
            break;
        case 2:
            /* code */

            break;
        case 3:
            /* code */
            break;
        case 4:
            if (passwd[0] == '\000')
            {
                cout << "Cree una nueva contrasena: ";
                fflush(stdin);
                gets(passwd);
                admin(hotel);
            }
            else
            {
                while (strcmp(passwd, p) != 0)
                {
                    cout << "Ingrese contrasena: ";
                    fflush(stdin);
                    gets(p);
                    if (strcmp(p, passwd) == 0)
                    {
                        admin(hotel);
                    }
                    else
                    {
                        cout << "Contrasena incorrecta, intente de nuevo";
                    }
                }
            }
            break;
        case 0:
            cout << "Saliendo... \n";
            break;
        default:
            cout << "Opcion no valida, intente de nuevo";
            break;
        }
    }
}
void ver_habitaciones_disponibles(habitacion (&hotel)[8][4])
{
    for (int i = 0; i < 8; i++)
    {
        int e = 0;
        cout << i + 1 << "° piso: \n";
        for (int j = 0; j < 4; j++)
        {
            if (hotel[i][j].huespdesActuales < hotel[i][j].capacidadMax)
            {
                cout << "Habitacion " << hotel[i][j].codigo << "\n";
                cout << "Tipo: ";
                switch (hotel[i][j].tipo)
                {
                case 's':
                case 'S':
                    cout << "Simple\n";
                    break;
                case 'd':
                case 'D':
                    cout << "Doble\n";
                    break;
                default:
                    cout << "Desconocido\n";
                    break;
                }
                cout << "Capacidad máxima: " << hotel[i][j].capacidadMax << "\n";
                cout << "Precio por noche: " << hotel[i][j].precioNoche << "\n";
                e++;
                cout << endl;
            }
        }
        if (e == 0)
        {
            cout << "No hay habitaciones disponibles en este piso.\n";
        }
    }
}
void admin(habitacion (&hotel)[8][4])
{
    int op = 1;
    while (op)
    {
        cout << "Bienvenido\n";
        cout << "---------------------------------------------\n";
        cout << "1. Añadir habitacion\n";
        cout << "2. Colocar habitación fuera de servicio\n";
        cout << "3. Editar habitacion\n";
        cout << "0. Regresar a la interfaz principal\n";
        cout << "---------------------------------------------\n";
        cout << "-> ";
        cin >> op;
        switch (op)
        {
        case 1:
            aniadir_habitacion(hotel);
            break;
        case 3:
            modificar_habitacion(hotel);
            break;
        case 0:
            cout << "Regresando a la interfaz principal\n";
            break;
        default:
            cout << "Operacion no valida, intente de nuevo\n";
            break;
        }
    }
};
void aniadir_habitacion(habitacion (&hotel)[8][4])
{
    int piso, numero;
    float precio;
    char tipo;
    cout << "Ingrese el piso de la habitacion: ";
    cin >> piso;
    cout << "Ingrese el número de la habitacion: ";
    cin >> numero;
    if (hotel[piso - 1][numero - 1].codigo == 0)
    {
        cout << "Precio por noche para esta habitacion: ";
        cin >> precio;
        cout << "Ingrese tipo de habitacion ((s)imple, (d)oble): ";
        cin >> tipo;
        hotel[piso - 1][numero - 1].codigo = piso * 100 + numero;
        hotel[piso - 1][numero - 1].precioNoche = precio;
        hotel[piso - 1][numero - 1].tipo = tipo;
        if (tipo == 's' || tipo == 'S')
        {
            hotel[piso - 1][numero - 1].capacidadMax = 1;
        }
        else if (tipo == 'd' || tipo == 'D')
        {
            hotel[piso - 1][numero - 1].capacidadMax = 2;
        }
        cout << "Habitacion creada exitosamente\n";
    }
    else
    {
        cout << "Error: la habitacion " << piso * 100 + numero << " ya existe\n";
    }
}
void modificar_habitacion(habitacion (&hotel)[8][4])
{
    int piso, numero;
    cout << "Ingrese el piso de la habitacion a modificar: ";
    cin >> piso;
    cout << "Ingrese el número de la habitacion a modificar: ";
    cin >> numero;
    if (hotel[piso - 1][numero - 1].codigo != 0)
    {
        char tipo;
        float precio;
        cout << "Precio por noche para esta habitacion: ";
        cin >> precio;
        cout << "Ingrese tipo de habitacion ((s)imple, (d)oble): ";
        cin >> tipo;
        hotel[piso - 1][numero - 1].precioNoche = precio;
        hotel[piso - 1][numero - 1].tipo = tipo;
        if (tipo == 's' || tipo == 'S')
        {
            hotel[piso - 1][numero - 1].capacidadMax = 1;
        }
        else if (tipo == 'd' || tipo == 'D')
        {
            hotel[piso - 1][numero - 1].capacidadMax = 2;
        }
        cout << "Habitacion modificada exitosamente\n";
    }
    else
    {
        cout << "Error: la habitacion " << piso * 100 + numero << " no existe\n";
    }
}