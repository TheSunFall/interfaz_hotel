#include <iostream>
#include <fstream>
#include <cstring>
#include <locale.h>
#include <windows.h>
using namespace std;
struct fecha {
    int dia;
    int mes;
    int anio;
};
struct reserva {
    fecha fechaInicio;
    fecha fechaFin;
};
struct huesped {
    char nombre[50];
    char pais[50];
    int id;
    reserva res;
};
struct habitacion {
    int codigo;
    char tipo;
    float precioNoche;
    int capacidadMax;
    int huespdesActuales;
    bool fueraDeServicio;
    huesped huespedes[2];
};

void crear_archivo_usuarios() {
    ofstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        archivo << "admin admin\n";
        archivo.close();
    } else {
        cout << "Error al crear el archivo de usuarios.\n";
    }
}
void crear_archivo_datos_hotel() {
    habitacion hotel[8][4] = {0};
    ofstream archivo("datos_hotel.dat", ios::binary);
    if (archivo.is_open()) {
        archivo.write((char*)hotel, sizeof(hotel));
        archivo.close();
    } else {
        cout << "Error al crear el archivo de datos del hotel.\n";
    }
}
void inicializar_archivos() {
    ifstream archivoUsuarios("usuarios.txt");
    if (!archivoUsuarios.is_open()) {
        crear_archivo_usuarios();
    } else {
        archivoUsuarios.close();
    }
    ifstream archivoDatosHotel("datos_hotel.dat", ios::binary);
    if (!archivoDatosHotel.is_open()) {
        crear_archivo_datos_hotel();
    } else {
        archivoDatosHotel.close();
    }
}
bool verificar_usuario() {
    cout << "====================================\n";
    cout << "Menú de administración\n";
    cout << "====================================\n";
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios.\n";
        return false;
    }
    string usuario, contrasena, usuarioIngresado, contrasenaIngresada;
    cout << "Ingrese el usuario: ";
    cin >> usuarioIngresado;
    cout << "Ingrese la contraseña: ";
    cin >> contrasenaIngresada;
    while (archivo >> usuario >> contrasena) {
        if (usuario == usuarioIngresado && contrasena == contrasenaIngresada) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}
void editar_usuarios_contrasenas() {
    cout << "====================================\n";
    cout << "Editar usuarios y contraseñas\n";
    cout << "====================================\n";
    ofstream archivo("usuarios.txt", ios::app);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios.\n";
        return;
    }
    string usuario, contrasena;
    cout << "Ingrese el nuevo usuario: ";
    cin >> usuario;
    cout << "Ingrese la nueva contraseña: ";
    cin >> contrasena;
    archivo << usuario << " " << contrasena << endl;
    archivo.close();
    cout << "Usuario y contraseña agregados exitosamente.\n";
}
void ver_habitaciones_disponibles(habitacion hotel[8][4]) {
    cout << "====================================\n";
    cout << "Habitaciones disponibles\n";
    cout << "====================================\n";
    for (int i = 0; i < 8; i++) {
        int e = 0;
        cout << i + 1 << "° piso: \n";
        for (int j = 0; j < 4; j++) {
            if (hotel[i][j].huespdesActuales < hotel[i][j].capacidadMax && !hotel[i][j].fueraDeServicio) {
                cout << "Habitación " << hotel[i][j].codigo << "\n";
                cout << "Tipo: ";
                switch (hotel[i][j].tipo) {
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
        if (e == 0) {
            cout << "No hay habitaciones disponibles en este piso.\n";
        }
    }
}
void aniadir_habitacion(habitacion hotel[8][4]) {
    cout << "====================================\n";
    cout << "Añadir habitación\n";
    cout << "====================================\n";
    int piso, numero;
    float precio;
    char tipo;
    cout << "Ingrese el piso de la habitación: ";
    cin >> piso;
    cout << "Ingrese el número de la habitación: ";
    cin >> numero;
    if (hotel[piso - 1][numero - 1].codigo == 0) {
        cout << "Precio por noche para esta habitación: ";
        cin >> precio;
        cout << "Ingrese tipo de habitación ((s)imple, (d)oble): ";
        cin >> tipo;
        hotel[piso - 1][numero - 1].codigo = piso * 100 + numero;
        hotel[piso - 1][numero - 1].precioNoche = precio;
        hotel[piso - 1][numero - 1].tipo = tipo;
        if (tipo == 's' || tipo == 'S') {
            hotel[piso - 1][numero - 1].capacidadMax = 1;
        } else if (tipo == 'd' || tipo == 'D') {
            hotel[piso - 1][numero - 1].capacidadMax = 2;
        }
        cout << "Habitación creada exitosamente\n";
    } else {
        cout << "Error: la habitación " << piso * 100 + numero << " ya existe\n";
    }
}
void colocar_fuera_servicio(habitacion hotel[8][4]) {
    cout << "====================================\n";
    cout << "Habitacion fuera de servicio\n";
    cout << "====================================\n";
    int piso, numero;
    cout << "Ingrese el piso de la habitación: ";
    cin >> piso;
    cout << "Ingrese el número de la habitación: ";
    cin >> numero;

    if (hotel[piso - 1][numero - 1].codigo == 0) {
        cout << "La habitación no existe\n";
        return;
    }

    hotel[piso - 1][numero - 1].fueraDeServicio = true;
    hotel[piso - 1][numero - 1].huespdesActuales = 0;

    cout << "Habitación colocada fuera de servicio y huéspedes desalojados\n";
}
void modificar_habitacion(habitacion hotel[8][4]) {
    cout << "====================================\n";
    cout << "Modificar habitación\n";
    cout << "====================================\n";
    int piso, numero;
    cout << "Ingrese el piso de la habitación a modificar: ";
    cin >> piso;
    cout << "Ingrese el número de la habitación a modificar: ";
    cin >> numero;
    if (hotel[piso - 1][numero - 1].codigo != 0) {
        char tipo;
        float precio;
        cout << "Precio por noche para esta habitación: ";
        cin >> precio;
        cout << "Ingrese tipo de habitación ((s)imple, (d)oble): ";
        cin >> tipo;
        hotel[piso - 1][numero - 1].precioNoche = precio;
        hotel[piso - 1][numero - 1].tipo = tipo;
        if (tipo == 's' || tipo == 'S') {
            hotel[piso - 1][numero - 1].capacidadMax = 1;
        } else if (tipo == 'd' || tipo == 'D') {
            hotel[piso - 1][numero - 1].capacidadMax = 2;
        }
        cout << "Habitación modificada exitosamente\n";
    } else {
        cout << "Error: la habitación " << piso * 100 + numero << " no existe\n";
    }
}
void guardar_datos_habitaciones(habitacion hotel[8][4]) {
    ofstream archivo("datos_hotel.dat", ios::binary);
    if (archivo.is_open()) {
        archivo.write((char*)hotel, sizeof(hotel));
        archivo.close();
    } else {
        cout << "Error al guardar los datos del hotel.\n";
    }
}
void cargar_datos_habitaciones(habitacion hotel[8][4]) {
    ifstream archivo("datos_hotel.dat", ios::binary);
    if (archivo.is_open()) {
        archivo.read((char*)hotel, sizeof(hotel));
        archivo.close();
    } else {
        cout << "Error al cargar los datos del hotel.\n";
    }
}
void generar_boleta(habitacion hotel[8][4]) {
    cout << "====================================\n";
    cout << "Generar Boleta\n";
    cout << "====================================\n";
    int piso, numero;
    cout << "Ingrese el piso de la habitación para generar la boleta: ";
    cin >> piso;
    cout << "Ingrese el número de la habitación para generar la boleta: ";
    cin >> numero;

    if (hotel[piso - 1][numero - 1].codigo == 0) {
        cout << "La habitación no existe\n";
        return;
    }

    float total = hotel[piso - 1][numero - 1].precioNoche * hotel[piso - 1][numero - 1].huespdesActuales;
    cout << "====================================\n";
    cout << "Boleta electrónica\n";
    cout << "====================================\n";
    cout << "Habitación: " << hotel[piso - 1][numero - 1].codigo << "\n";
    cout << "Total a pagar: $" << total << "\n";
    cout << "----------------------------\n";
}
void registrar_huesped(habitacion hotel[8][4]) {
    cout << "====================================\n";
    cout << "Registrar huésped\n";
    cout << "====================================\n";
    int piso, numero;
    cout << "Ingrese el piso de la habitación: ";
    cin >> piso;
    cout << "Ingrese el número de la habitación: ";
    cin >> numero;

    if (hotel[piso - 1][numero - 1].codigo == 0) {
        cout << "La habitación no existe\n";
        return;
    }

    if (hotel[piso - 1][numero - 1].huespdesActuales == hotel[piso - 1][numero - 1].capacidadMax) {
        cout << "La habitación está llena\n";
        return;
    }
    huesped nuevoHuesped;
    cout << "Nombre del huésped: ";
    cin.ignore();
    cin.getline(nuevoHuesped.nombre, 50);
    cout << "País del huésped: ";
    cin.getline(nuevoHuesped.pais, 50);
    cout << "ID del huésped: ";
    cin >> nuevoHuesped.id;
    cout << "Fecha de inicio de la reserva (dd mm aaaa): ";
    cin >> nuevoHuesped.res.fechaInicio.dia >> nuevoHuesped.res.fechaInicio.mes >> nuevoHuesped.res.fechaInicio.anio;
    cout << "Fecha de fin de la reserva (dd mm aaaa): ";
    cin >> nuevoHuesped.res.fechaFin.dia >> nuevoHuesped.res.fechaFin.mes >> nuevoHuesped.res.fechaFin.anio;

    hotel[piso - 1][numero - 1].huespedes[hotel[piso - 1][numero - 1].huespdesActuales] = nuevoHuesped;
    hotel[piso - 1][numero - 1].huespdesActuales++;

    cout << "Huésped registrado exitosamente.\n";
}

void registrar_salida_huesped(habitacion hotel[8][4]) {
    cout << "====================================\n";
    cout << "Registrar salida de huésped\n";
    cout << "====================================\n";
    int piso, numero;
    cout << "Ingrese el piso de la habitación: ";
    cin >> piso;
    cout << "Ingrese el número de la habitación: ";
    cin >> numero;

    if (hotel[piso - 1][numero - 1].codigo == 0) {
        cout << "La habitación no existe\n";
        return;
    }

    if (hotel[piso - 1][numero - 1].huespdesActuales == 0) {
        cout << "No hay huéspedes en esta habitación\n";
        return;
    }

    int id;
    cout << "Ingrese el ID del huésped que desea registrar salida: ";
    cin >> id;

    bool encontrado = false;
    for (int i = 0; i < hotel[piso - 1][numero - 1].huespdesActuales; i++) {
        if (hotel[piso - 1][numero - 1].huespedes[i].id == id) {
            // Eliminar huésped moviendo los siguientes hacia atrás
            for (int j = i; j < hotel[piso - 1][numero - 1].huespdesActuales - 1; j++) {
                hotel[piso - 1][numero - 1].huespedes[j] = hotel[piso - 1][numero - 1].huespedes[j + 1];
            }
            hotel[piso - 1][numero - 1].huespdesActuales--;
            cout << "Registro de salida exitoso para el huésped con ID " << id << ".\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontró un huésped con el ID proporcionado.\n";
    }
}

void menu_administradores(habitacion hotel[8][4]);

void menu(habitacion hotel[8][4]) {
    int opcion;
    do {
        cout << "====================================\n";
        cout << "¡Bienvenido!\n";
        cout << "====================================\n";
        cout << "1. Ver habitaciones disponibles\n";
        cout << "2. Registrar huésped\n";
        cout << "3. Registrar salida de huésped\n";
        cout << "4. Generar boleta de pago\n";
        cout << "5. Menu para administradores\n";
        cout << "0. Salir\n";
        cout << "====================================\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                system("cls");
                ver_habitaciones_disponibles(hotel);
                break;
            case 2:
                system("cls");
                registrar_huesped(hotel);
                break;
            case 3:
                system("cls");
                registrar_salida_huesped(hotel);
                break;
            case 4:
                system("cls");
                generar_boleta(hotel);
                break;
            case 5:
                system("cls");
                menu_administradores(hotel);
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
                break;
        }
    } while (opcion != 0);
}

void menu_administradores(habitacion hotel[8][4]) {
    bool usuarioValido = false;
    string usuario, contrasena;
    do {

        if (!usuarioValido) {
            usuarioValido = verificar_usuario();
            if (!usuarioValido) {
                cout << "Usuario o contraseña incorrectos. Intente nuevamente.\n";
            }
        } else {
            system("cls");
            int opcion;
            cout << "====================================\n";
            cout << "Menú de administración\n";
            cout << "====================================\n";
            cout << "1. Añadir habitación\n";
            cout << "2. Modificar habitación\n";
            cout << "3. Colocar habitación fuera de servicio\n";
            cout << "4. Editar usuarios y contraseñas\n";
            cout << "0. Salir\n";
            cout << "====================================\n";
            cout << "Ingrese su opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    system("cls");
                    aniadir_habitacion(hotel);
                    break;
                case 2:
                    system("cls");
                    modificar_habitacion(hotel);
                    break;
                case 3:
                    system("cls");
                    colocar_fuera_servicio(hotel);
                    break;
                case 4:
                    system("cls");
                    editar_usuarios_contrasenas();
                    break;
                case 0:
                    cout << "Saliendo...\n";
                    system("cls");
                    menu(hotel);
                    break;
                default:
                    cout << "Opción inválida. Intente nuevamente.\n";
                    break;
            }
        }
    } while (usuarioValido);
}

int main() {
    habitacion hotel[8][4];
    inicializar_archivos();
    cargar_datos_habitaciones(hotel);
    setlocale(LC_ALL, "es_PE");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    int opcion;
    menu(hotel);
    guardar_datos_habitaciones(hotel);
    return 0;
}
