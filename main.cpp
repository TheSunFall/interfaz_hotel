#include <iostream>
#include <fstream>
#include <clocale>
#include <windows.h>

using namespace std;

struct fecha {
    int dia;
    int mes;
    int anio;
};

struct reserva {
    int codHabitacion;
    fecha fechaInicio;
};

struct huesped {
    char nombre[30];
    char pais[20];
    int id;
    reserva res;
};

struct habitacion {
    int codigo = 0;
    char tipo = '\0';
    int capacidadMax = 0;
    float precioNoche = 0;
    int huespdesActuales = 0;
    huesped huespedes[2] = {"", "", 0, {0, {0, 0, 0}}};
    bool fueraDeServicio = false;
};

void menu(habitacion (&)[8][4]);
void menu_administradores(habitacion (&)[8][4]);
void crear_archivo_usuarios();
void inicializar_archivos();
bool verificar_usuario();
void editar_usuarios_contrasenas();
void ver_habitaciones_disponibles(habitacion (&)[8][4]);
void aniadir_habitacion(habitacion (&)[8][4]);
void colocar_fuera_servicio(habitacion (&)[8][4]);
void modificar_habitacion(habitacion (&)[8][4]);
void registrar_huesped(habitacion (&)[8][4]);
void registrar_salida_huesped(habitacion (&)[8][4]);
void mostrar_huespedes_registrados(habitacion (&)[8][4]);
void generar_boleta(habitacion (&)[8][4]);
void guardar_datos(habitacion hotel[8][4]);
void cargar_datos(habitacion hotel[8][4]);

int main() {
    habitacion hotel[8][4];
    inicializar_archivos();
    cargar_datos(hotel);
    setlocale(LC_ALL, "es_PE");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    menu(hotel);
    return 0;
}

// Menu principal
void menu(habitacion (&hotel)[8][4]) {
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
                guardar_datos(hotel);
                break;
            case 3:
                system("cls");
                registrar_salida_huesped(hotel);
                guardar_datos(hotel);
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
                guardar_datos(hotel);
                break;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
                break;
        }
    } while (opcion != 0);
}

// Menu para admministradores
void menu_administradores(habitacion (&hotel)[8][4]) {
    int opcion;
    bool usuarioValido = false;
    string usuario, contrasena;
    do {
        if (!usuarioValido) {
            usuarioValido = verificar_usuario();
            if (!usuarioValido) {
                cout << "Usuario o contraseña incorrectos. Intente nuevamente.\n";
            }
        } else {
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
                    guardar_datos(hotel);
                    break;
                case 2:
                    system("cls");
                    modificar_habitacion(hotel);
                    guardar_datos(hotel);
                    break;
                case 3:
                    system("cls");
                    colocar_fuera_servicio(hotel);
                    guardar_datos(hotel);
                    break;
                case 4:
                    system("cls");
                    editar_usuarios_contrasenas();
                    break;
                case 0:
                    cout << "Saliendo...\n";
                    system("cls");
                    break;
                default:
                    cout << "Opción inválida. Intente nuevamente.\n";
                    break;
            }
        }
    } while (usuarioValido && opcion != 0);
}

// Funciones de control de usuarios
void crear_archivo_usuarios() {
    ofstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        archivo << "admin admin\n";
        archivo.close();
    } else {
        cout << "Error al crear el archivo de usuarios.\n";
    }
}

void inicializar_archivos() {
    ifstream archivoUsuarios("usuarios.txt");
    if (!archivoUsuarios.is_open()) {
        crear_archivo_usuarios();
    } else {
        archivoUsuarios.close();
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
// Funciones del sistema


void ver_habitaciones_disponibles(habitacion (&hotel)[8][4]) {
    cout << "====================================\n";
    cout << "Habitaciones disponibles\n";
    cout << "====================================\n";
    for (int i = 0; i < 8; i++) {
        int e = 0;
        cout << i + 1 << "° piso: \n";
        for (int j = 0; j < 4; j++) {
            if (hotel[i][j].codigo != 0) {
                e++;
                cout << "Habitación " << hotel[i][j].codigo << "\n";
                if (hotel[i][j].huespdesActuales < hotel[i][j].capacidadMax && !hotel[i][j].fueraDeServicio) {
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
                    cout << endl;
                } else {
                    cout << "No disponible\n" << endl;
                }
            }
        }
        if (e == 0) {
            cout << "No hay habitaciones disponibles en este piso.\n";
        }
    }
}

void registrar_huesped(habitacion (&hotel)[8][4]) {
    int piso, numero;
    huesped nuevoHuesped;
    cout << "Ingrese el piso de la habitacion: ";
    cin >> piso;
    cout << "Ingrese el número de la habitacion: ";
    cin >> numero;

    if (hotel[piso - 1][numero - 1].codigo == 0) {
        system("cls");
        cout << "La habitacion no existe\n";
        return;
    }
    if (hotel[piso - 1][numero - 1].huespdesActuales >= hotel[piso - 1][numero - 1].capacidadMax) {
        system("cls");
        cout << "La habitacion esta llena\n";
        return;
    }
    if (hotel[piso - 1][numero - 1].fueraDeServicio) {
        system("cls");
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
    system("cls");
    cout << "Huesped registrado exitosamente\n";
}

void registrar_salida_huesped(habitacion (&hotel)[8][4]) {
    int piso, numero, id;
    cout << "Ingrese el piso de la habitacion: ";
    cin >> piso;
    cout << "Ingrese el número de la habitacion: ";
    cin >> numero;

    if (hotel[piso - 1][numero - 1].codigo == 0) {
        system("cls");
        cout << "La habitacion no existe\n";
        return;
    }
    if (hotel[piso - 1][numero - 1].huespdesActuales == 0) {
        system("cls");
        cout << "No hay huespedes en esta habitacion\n";
        return;
    }

    cout << "Huespedes en la habitacion:\n";
    for (int i = 0; i < hotel[piso - 1][numero - 1].huespdesActuales; i++) {
        cout << "ID: " << hotel[piso - 1][numero - 1].huespedes[i].id << ", Nombre: "
             << hotel[piso - 1][numero - 1].huespedes[i].nombre << endl;
    }

    cout << "Ingrese el ID del huesped que va a salir: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < hotel[piso - 1][numero - 1].huespdesActuales; i++) {
        if (hotel[piso - 1][numero - 1].huespedes[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        system("cls");
        cout << "Huesped no encontrado\n";
        return;
    }

    for (int i = index; i < hotel[piso - 1][numero - 1].huespdesActuales - 1; i++) {
        hotel[piso - 1][numero - 1].huespedes[i] = hotel[piso - 1][numero - 1].huespedes[i + 1];
    }

    hotel[piso - 1][numero - 1].huespdesActuales--;
    system("cls");
    cout << "Huesped registrado como salido exitosamente\n";
}

void generar_boleta(habitacion (&hotel)[8][4]) {
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

    for (int i = 0; i < hotel[piso - 1][numero - 1].huespdesActuales; ++i) {
        huesped &h = hotel[piso - 1][numero - 1].huespedes[i];
        cout << "Datos del huésped:\n";
        cout << "Nombre: " << h.nombre << endl;
        cout << "País: " << h.pais << endl;
        cout << "ID: " << h.id << endl;
        cout << "Fecha de inicio: " << h.res.fechaInicio.dia << "/" << h.res.fechaInicio.mes << "/"
             << h.res.fechaInicio.anio << endl;
        cout << "----------------------------\n";
    }

    char respuesta;
    cout << "¿Desea descargar la boleta? (s/n): ";
    cin >> respuesta;
    if (respuesta == 's' || respuesta == 'S') {
        ofstream archivo("boleta_cliente.txt");
        if (archivo.is_open()) {
            archivo << "Boleta electrónica\n";
            archivo << "Habitación: " << hotel[piso - 1][numero - 1].codigo << "\n";
            archivo << "Total a pagar: $" << total << "\n";
            archivo << "----------------------------\n";

            for (int i = 0; i < hotel[piso - 1][numero - 1].huespdesActuales; ++i) {
                huesped &h = hotel[piso - 1][numero - 1].huespedes[i];
                archivo << "Datos del huésped:\n";
                archivo << "Nombre: " << h.nombre << endl;
                archivo << "País: " << h.pais << endl;
                archivo << "ID: " << h.id << endl;
                archivo << "Fecha de inicio: " << h.res.fechaInicio.dia << "/" << h.res.fechaInicio.mes << "/"
                        << h.res.fechaInicio.anio << endl;
                archivo << "----------------------------\n";
            }
            archivo.close();
            cout << "Boleta descargada exitosamente en boleta_cliente.txt\n";
        } else {
            cout << "Error al crear el archivo de boleta.\n";
        }
    }
}

void aniadir_habitacion(habitacion (&hotel)[8][4]) {
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
        system("cls");
        cout << "Error: la habitación " << piso * 100 + numero << " ya existe\n";
    }
}

void colocar_fuera_servicio(habitacion (&hotel)[8][4]) {
    cout << "====================================\n";
    cout << "Habitacion fuera de servicio\n";
    cout << "====================================\n";
    int piso, numero;
    char h;
    cout << "Ingrese el piso de la habitación: ";
    cin >> piso;
    cout << "Ingrese el número de la habitación: ";
    cin >> numero;

    if (hotel[piso - 1][numero - 1].codigo == 0) {
        system("cls");
        cout << "La habitación no existe\n";
    } else {
        if (!hotel[piso - 1][numero - 1].fueraDeServicio) {
            hotel[piso - 1][numero - 1].fueraDeServicio = true;
            hotel[piso - 1][numero - 1].huespdesActuales = 0;
            for (int i = 0; i < 2; i++){
                hotel[piso-1][numero-1].huespedes[i] = {"", "", 0, {0, {0, 0, 0}}};
            }
            system("cls");
            cout << "Habitación colocada fuera de servicio y huéspedes desalojados\n";
        } else {
            cout << "Esta habitación ya está fuera de servicio. \n¿Desea volver a habilitarla? (s/n): ";
            cin >> h;
            switch (h) {
                case 's':
                case 'S':
                    hotel[piso - 1][numero - 1].fueraDeServicio = false;
                    break;
                case 'n':
                case 'N':
                default:
                    break;
            }
            system("cls");
            cout << "Habitación reactivada para su uso\n";
        }
    }
}

void modificar_habitacion(habitacion (&hotel)[8][4]) {
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
        system("cls");
        cout << "Habitación modificada exitosamente\n";
    } else {
        system("cls");
        cout << "Error: la habitación " << piso * 100 + numero << " no existe\n";
    }
}

void mostrar_huespedes_registrados(habitacion (&hotel)[8][4]) {
    cout << "====================================\n";
    cout << "Huéspedes registrados en el hotel\n";
    cout << "====================================\n";
    bool hayHuespedes = false;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (hotel[i][j].codigo != 0 && hotel[i][j].huespdesActuales > 0) {
                cout << "Piso " << i + 1 << ", Habitación " << hotel[i][j].codigo << ":\n";
                for (int k = 0; k < hotel[i][j].huespdesActuales; k++) {
                    huesped& h = hotel[i][j].huespedes[k];
                    cout << "Nombre: " << h.nombre << endl;
                    cout << "País: " << h.pais << endl;
                    cout << "ID: " << h.id << endl;
                    cout << "Fecha de inicio: " << h.res.fechaInicio.dia << "/" << h.res.fechaInicio.mes << "/" << h.res.fechaInicio.anio << endl;
                    cout << "------------------------------\n";
                }
                hayHuespedes = true;
            }
        }

    }
    if (!hayHuespedes) {
        cout << "No hay huéspedes registrados en el hotel actualmente.\n";
    }

    cout << "Presiona Enter para volver al menú principal...";
    cin.ignore();
    cin.get();
}

void cargar_datos(habitacion hotel[8][4]) {
    ifstream file("datos_hotel.txt");
    ifstream fileHuespedes("datos_huespedes.txt");
    if (!file || !fileHuespedes) {
        cerr << "Error al abrir el archivo para cargar o archivo no existe\n";
        return;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            hotel[i][j] = habitacion(); // Resetear la estructura
        }
    }

    while (!file.eof()) {
        int piso, numero;
        habitacion temp;
        file >> temp.codigo >> temp.tipo >> temp.capacidadMax >> temp.precioNoche >> temp.huespdesActuales >> temp.fueraDeServicio;

        if (file.eof()) break;

        piso = temp.codigo / 100 - 1;
        numero = temp.codigo % 100 - 1;

        hotel[piso][numero] = temp;

        for (int k = 0; k < temp.huespdesActuales; k++) {
            huesped tempHuesped;
            fileHuespedes >> tempHuesped.nombre >> tempHuesped.pais >> tempHuesped.id >> tempHuesped.res.codHabitacion >> tempHuesped.res.fechaInicio.dia >> tempHuesped.res.fechaInicio.mes >> tempHuesped.res.fechaInicio.anio;
            file >> tempHuesped.nombre >> tempHuesped.pais >> tempHuesped.id >> tempHuesped.res.fechaInicio.dia
                 >> tempHuesped.res.fechaInicio.mes >> tempHuesped.res.fechaInicio.anio;
            hotel[piso][numero].huespedes[k] = tempHuesped;
        }
    }
    file.close();
    fileHuespedes.close();
    cout << "Datos cargados exitosamente\n";
}

void guardar_datos(habitacion hotel[8][4]) {
    ofstream file("datos_hotel.txt");
    if (!file) {
        cerr << "Error al abrir el archivo para guardar\n";
        return;
    }

    ofstream fileHuespedes("datos_huespedes.txt");
    if (!fileHuespedes) {
        cerr << "Error al abrir el archivo de huéspedes para guardar\n";
        return;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (hotel[i][j].codigo != 0) {
                file << hotel[i][j].codigo << " " << hotel[i][j].tipo << " " << hotel[i][j].capacidadMax << " "
                     << hotel[i][j].precioNoche << " " << hotel[i][j].huespdesActuales << " "
                     << hotel[i][j].fueraDeServicio << "\n";
                for (int k = 0; k < hotel[i][j].huespdesActuales; k++) {
                    fileHuespedes << hotel[i][j].huespedes[k].nombre << " " << hotel[i][j].huespedes[k].pais << " "
                                  << hotel[i][j].huespedes[k].id << " " << hotel[i][j].huespedes[k].res.codHabitacion
                                  << " " << hotel[i][j].huespedes[k].res.fechaInicio.dia << " "
                                  << hotel[i][j].huespedes[k].res.fechaInicio.mes << " "
                                  << hotel[i][j].huespedes[k].res.fechaInicio.anio << "\n";
                }
            }
        }
    }
    file.close();
    fileHuespedes.close();
    cout << "Datos guardados exitosamente\n";
}
