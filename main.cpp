#include <iostream>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

using namespace std;

// Struct para almacenar la fecha
struct fecha
{
    int dia;
    int mes;
    int anio;
};

struct reserva
{
    int codHabitacion;
    fecha fechaInicio;
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
    bool fueraDeServicio = false; // Nuevo atributo para indicar si la habitación está fuera de servicio
};

void admin(habitacion (&)[8][4]);
void registrar_huesped(habitacion (&)[8][4]);
void registrar_salida_huesped(habitacion (&)[8][4]);
void ver_habitaciones_disponibles(habitacion (&)[8][4]);
void aniadir_habitacion(habitacion (&)[8][4]);
void colocar_fuera_servicio(habitacion (&)[8][4]);
void modificar_habitacion(habitacion (&)[8][4]);

int main()
{
    FILE *passwd, *cpasswd;
    habitacion hotel[8][4];
    char p[15] = {'\000'}, p2[15] = {'\000'},c;
    int op = 1, size;
    setlocale(LC_ALL,"es_PE");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    cout << "¡Bienvenido!" << endl;
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
        case 1:system("cls");
            ver_habitaciones_disponibles(hotel);
            break;
        case 2:system("cls");
            registrar_huesped(hotel);
            break;
        case 3:system("cls");
            registrar_salida_huesped(hotel);
            break;
        case 4:system("cls");
            passwd = fopen("ps.dat", "rb");
            if (passwd == NULL)
            {
                cpasswd = fopen("ps.dat", "wb");
                cout << "Cree una nueva contrasena: ";
                cin.ignore();
                cin.getline(p, 15);
                fwrite(p, 1, sizeof(p), cpasswd);
                fclose(cpasswd);
                admin(hotel);
            }
            else
            {
                fseek(passwd, 0, SEEK_END);
                size = ftell(passwd);
                rewind(passwd);
                fread(p, sizeof(char), size, passwd);
                cout << "Ingrese la contrasena: ";
                cin >> p2;
                if (strcmp(p, p2) == 0)
                {
                    admin(hotel);
                }
                else
                {
                    cout << "Contrasena incorrecta\n";
                }
            }
            break;
        case 0:system("cls");
            cout << "Saliendo... \n";
            break;
        default:
            cout << "Opcion no valida, intente de nuevo\n";
            break;
        }
        cout << "Ingrese cualquier caracter (no especial) para continuar...";
        cin >> c;
        system("cls");
    }
}
void admin(habitacion (&hotel)[8][4])
{
    int op = 1;
    while (op)
    {
        cout << "Bienvenido\n";
        cout << "---------------------------------------------\n";
        cout << "1. Añadir habitación\n";
        cout << "2. Colocar habitación fuera de servicio\n";
        cout << "3. Modificar habitación\n";
        cout << "0. Regresar a la interfaz principal\n";
        cout << "---------------------------------------------\n";
        cout << "-> ";
        cin >> op;
        switch (op)
        {
        case 1:
            aniadir_habitacion(hotel);
            break;
        case 2:
            colocar_fuera_servicio(hotel);
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
}
void registrar_huesped(habitacion (&hotel)[8][4])
{
    int piso, numero;
    huesped nuevoHuesped;
    cout << "Ingrese el piso de la habitacion: ";
    cin >> piso;
    cout << "Ingrese el número de la habitacion: ";
    cin >> numero;

    if (hotel[piso - 1][numero - 1].codigo == 0)
    {
        cout << "La habitacion no existe\n";
        return;
    }
    if (hotel[piso - 1][numero - 1].huespdesActuales >= hotel[piso - 1][numero - 1].capacidadMax)
    {
        cout << "La habitacion esta llena\n";
        return;
    }
    if (hotel[piso - 1][numero - 1].fueraDeServicio)
    {
        cout << "La habitacion está fuera de servicio\n";
        return;
    }

    cout << "Ingrese el nombre del huesped: ";
    cin.ignore();
    cin.getline(nuevoHuesped.nombre, 30);
    cout << "Ingrese el pais del huesped: ";
    cin.getline(nuevoHuesped.pais, 20);
    cout << "Ingrese el ID del huesped: ";
    cin >> nuevoHuesped.id;

    cout << "Ingrese la fecha de inicio (DD MM AAAA): ";
    cin >> nuevoHuesped.res.fechaInicio.dia >> nuevoHuesped.res.fechaInicio.mes >> nuevoHuesped.res.fechaInicio.anio;

    nuevoHuesped.res.codHabitacion = hotel[piso - 1][numero - 1].codigo;

    hotel[piso - 1][numero - 1].huespedes[hotel[piso - 1][numero - 1].huespdesActuales] = nuevoHuesped;
    hotel[piso - 1][numero - 1].huespdesActuales++;

    cout << "Huesped registrado exitosamente\n";
}

void registrar_salida_huesped(habitacion (&hotel)[8][4])
{
    int piso, numero, id;
    cout << "Ingrese el piso de la habitacion: ";
    cin >> piso;
    cout << "Ingrese el número de la habitacion: ";
    cin >> numero;

    if (hotel[piso - 1][numero - 1].codigo == 0)
    {
        cout << "La habitacion no existe\n";
        return;
    }
    if (hotel[piso - 1][numero - 1].huespdesActuales == 0)
    {
        cout << "No hay huespedes en esta habitacion\n";
        return;
    }

    cout << "Huespedes en la habitacion:\n";
    for (int i = 0; i < hotel[piso - 1][numero - 1].huespdesActuales; i++)
    {
        cout << "ID: " << hotel[piso - 1][numero - 1].huespedes[i].id << ", Nombre: " << hotel[piso - 1][numero - 1].huespedes[i].nombre << endl;
    }

    cout << "Ingrese el ID del huesped que va a salir: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < hotel[piso - 1][numero - 1].huespdesActuales; i++)
    {
        if (hotel[piso - 1][numero - 1].huespedes[i].id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Huesped no encontrado\n";
        return;
    }

    for (int i = index; i < hotel[piso - 1][numero - 1].huespdesActuales - 1; i++)
    {
        hotel[piso - 1][numero - 1].huespedes[i] = hotel[piso - 1][numero - 1].huespedes[i + 1];
    }

    hotel[piso - 1][numero - 1].huespdesActuales--;

    cout << "Huesped registrado para salida exitosamente\n";
}
void ver_habitaciones_disponibles(habitacion (&hotel)[8][4])
{
    for (int i = 0; i < 8; i++)
    {
        int e = 0;
        cout << i + 1 << "° piso: \n";
        for (int j = 0; j < 4; j++)
        {
            if (hotel[i][j].huespdesActuales < hotel[i][j].capacidadMax && !hotel[i][j].fueraDeServicio)
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

void colocar_fuera_servicio(habitacion (&hotel)[8][4])
{
    int piso, numero;
    cout << "Ingrese el piso de la habitacion: ";
    cin >> piso;
    cout << "Ingrese el número de la habitacion: ";
    cin >> numero;

    if (hotel[piso - 1][numero - 1].codigo == 0)
    {
        cout << "La habitacion no existe\n";
        return;
    }

    hotel[piso - 1][numero - 1].fueraDeServicio = true;
    hotel[piso - 1][numero - 1].huespdesActuales = 0; // Desalojar a los huéspedes

    cout << "Habitacion colocada fuera de servicio y huéspedes desalojados\n";
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