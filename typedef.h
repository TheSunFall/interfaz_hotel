// Evita que se redeclare los structs al importarse varias veces
#ifndef LIST_H_
#define LIST_H_
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
    int codigo;
    char tipo;
    int capacidadMax;
    int huespdesActuales = 0;
    float precioNoche;
    huesped huespedes[];
};
#endif