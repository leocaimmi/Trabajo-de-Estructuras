#ifndef FUNCION_H_INCLUDED
#define FUNCION_H_INCLUDED
#define DIM_MAX 30

typedef struct
{

    int legajo;
    char nombreYapellido [DIM_MAX];
    int edad;
    int anio;

} stAlumno;

void cleanWindows();

stAlumno cargaUnAlumno();
void cargarAlumnos(char archivo[]);
int operador();

void mostrarArchivo(char archivo[]);
void mostrarAlumno(stAlumno p);
void agregarElemento(char archivo[]);
void pasarLegajoToPila(char archivo[],Pila* mayoresLegajos);

int preguntarDato();
int contarMayores(char archivo[],int edad);
void mostrarCantidad(int edad);

void rangoNombres(char archivo[],int desde,int hasta);

void encontrarMayorAlumno(char archivo[]);

int alumnosXAnio(char archivo[],int BuscarAnio);

int cargarArregloAlumnos(stAlumno p[]);
void arregloToArchivo(char archivo[],stAlumno p[],int validos);
void mostrarArregloAlumnos(stAlumno p[],int validos);

void archivoToArreglo(char archivo[]);

int contarAlumnos(char archivo[]);

void mostrarPosPedida(char archivo[]);

 void modificarUnAlumno(stAlumno* b);
 void modificarAlumnos(char archivo[]);


void menu(char archivo[],stAlumno persona[],Pila* legajos);
void opciones();


#endif // FUNCION_H_INCLUDED
