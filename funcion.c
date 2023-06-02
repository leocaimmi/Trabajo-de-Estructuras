#include "pila.h"
#include "funcion.h"

void cleanWindows()
{
    system("cls");
}


/**Crear una funci�n que cargue un archivo de alumnos.
 Abrirlo de manera tal de verificar si el archivo ya est� creado previamente. Cargar el archivo con 5 datos.
Cerrarlo dentro de la funci�n */

stAlumno cargaUnAlumno() ///p de persona
{

    stAlumno p;

    printf("Ingrese el Nombre y Apellido: ");
    fflush(stdin);
    gets(p.nombreYapellido);
    printf("Ingrese la edad: ");
    fflush(stdin);
    scanf("%i",&p.edad);
    printf("Ingrese el legajo: ");
    fflush(stdin);
    scanf("%i",&p.legajo);
    printf("Ingrese el a�o que se encuentra cursando: ");
    fflush(stdin);
    scanf("%i",&p.anio);

    return p;
}

void cargarAlumnos(char archivo[])
{

    FILE* archi;
    stAlumno p;
    char op = 's';

    archi = fopen(archivo,"ab");

    if(archi != NULL)
    {

        while(op == 's'|| op == 'S')
        {
            p = cargaUnAlumno();
            op = operador();

            fwrite(&p,sizeof(stAlumno),1,archi);
        }

        fclose(archi);
    }

}

int operador()
{
    char op = 's';
    printf("(S/N)Para continuar la carga: ");
    fflush(stdin);
    scanf("%c",&op);
    return op;
}

///Crear una funci�n que muestre por pantalla los registros de un archivo de alumnos. Modularizar.


void mostrarAlumno(stAlumno p)
{
    printf("\n------------------------------DATOS----------------------------\n");
    printf("Nombre y apellido es: %s\n",p.nombreYapellido);
    printf("La edad es: %i\n",p.edad);
    printf("El nro de legajo es: %i\n",p.legajo);
    printf("El a�o de cursada es: %i\n",p.anio);
    printf("------------------------------------------------------------------\n");

}

void mostrarArchivo( char archivo[])
{

    FILE* archi;
    stAlumno p;
    int i = 0;
    archi=fopen(archivo,"rb");

    if(archi!= NULL)
    {

        while(fread(&p,sizeof(stAlumno),1,archi)>0)
        {
            mostrarAlumno(p);
        }

        fclose(archi);
    }

}

/**Crear una funci�n que permita agregar de a un elemento al final del archivo. O sea, se debe abrir el archivo,
 se piden los datos (se llena una variable de tipo struct alumno), se escribe en el archivo y se cierra.*/

void agregarElemento(char archivo[])
{

    FILE * buffer;
    buffer = fopen(archivo,"ab");
    stAlumno archi;

    if(buffer!= NULL)
    {
        printf("-------------------Cargue un alumno------------------\n");
        archi = cargaUnAlumno();
        fwrite(&archi, sizeof(stAlumno), 1, buffer);
        fclose(buffer);
    }
}

/// Crear una funci�n que pase a una pila los n�meros de legajo de los alumnos mayores de edad.

void pasarLegajoToPila(char archivo[],Pila* mayoresLegajos)
{

    FILE* archi;
    archi = fopen(archivo,"rb");
    stAlumno persona;

    int mayor = 18;

    if(archi !=NULL)
    {
        while(fread(&persona,sizeof(stAlumno),1,archi)>0)
        {
            if(persona.edad >= mayor)
            {
                apilar(mayoresLegajos,persona.legajo);
            }
        }
        fclose(archi);
    }
}

///Dado un archivo de alumnos, hacer una funci�n que cuente la cantidad de alumnos mayores a edad espec�fica que se env�a por par�metro.

int preguntarDato()
{
    int edad = 0;
    printf("Ingrese el dato: ");
    fflush(stdin);
    scanf("%i",&edad);
    return edad;
}


int contarMayores(char archivo[],int edad)
{

    FILE* archi;
    archi = fopen(archivo,"rb");
    stAlumno persona;
    int i = 0;

    if(archi !=NULL)
    {
        while(fread(&persona,sizeof(stAlumno),1,archi)>0)
        {
            if(persona.edad > edad)
            {
                i++;
            }
        }
        fclose(archi);
    }
    return i;
}

void mostrarCantidad(int edad)
{
    if(edad != 0)
    {
        puts("\n------------CANTIDAD SOLICITADA---------------------");
        printf("La cantidad de alumnos es:(%i)\n",edad);
        puts("-----------------------------------------------------\n");
    }
    else if(edad <=0)
    {
        puts("-------------------------------------------------------");
        printf("El dato solicitado es (0) o es invalido\n");
        puts("-------------------------------------------------------\n");
    }
}

/**Dado un archivo de alumnos,
 mostrar por pantalla el nombre de todos los alumnos entre un rango de edades espec�fico (por ejemplo, entre 17 y 25 a�os).
Dicho rango debe recibirse por par�metro. Modularizar*/

void rangoNombres(char archivo[],int desde,int hasta)
{

    FILE* archi;
    archi = fopen(archivo,"rb");
    stAlumno persona;
    int i = 0;

    if(archi !=NULL)
    {
        while(fread(&persona,sizeof(stAlumno),1,archi)>0)
        {
            if(persona.edad >= desde && persona.edad <= hasta)
            {
                mostrarAlumno(persona);
            }
        }
        fclose(archi);
    }
}

int rangoEdades(int*hasta)
{

    int desde = 0;

    printf("DESDE donde quiere mostrar los alumnos: ");
    fflush(stdin);
    scanf("%i",&desde);
    printf("HASTA donde quiere mostrar los alumnos: ");
    fflush(stdin);
    scanf("%i",hasta);

    return desde;
}
/**Dado un archivo de alumnos, mostrar los datos del alumno de mayor edad. Modularizar.*/

void encontrarMayorAlumno(char archivo[])
{

    FILE* archi;
    archi = fopen(archivo,"rb");
    stAlumno persona;
    stAlumno auxMayor;

    if(archi !=NULL)
    {
        while(fread(&persona,sizeof(stAlumno),1,archi)>0)
        {
            if(persona.edad > auxMayor.edad)
            {
                auxMayor = persona;
            }
        }
        fclose(archi);
    }
    mostrarAlumno(auxMayor);
}
/**Crear una funci�n que retorne la cantidad de alumnos que cursan un determinado a�o. El a�o buscado se pasa por par�metro. */

int alumnosXAnio(char archivo[],int BuscarAnio)
{

    FILE* archi;
    archi = fopen(archivo,"rb");
    stAlumno persona;
    int i = 0;
    if(archi !=NULL)
    {
        while(fread(&persona,sizeof(stAlumno),1,archi)>0)
        {
            if(persona.anio == BuscarAnio)
            {
                i++;
            }
        }
        fclose(archi);
    }
    return i;
}

/**Crear una funci�n que reciba como par�metro un arreglo de tipo alumno y lo copie en el archivo.
 Asimismo, realice otra funci�n que pase los elementos del archivo a un arreglo de alumnos, filtrando los estudiantes de un a�o en particular.*/

int cargarArregloAlumnos(stAlumno p[])
{
    stAlumno aux;
    int i = 0;
    char op = 's';
    while(i<DIM_MAX && (op=='s' || op== 's'))
    {
        aux = cargaUnAlumno();
        p[i] = aux;
        i++;
        op = operador();
    }
    return i;
}

void arregloToArchivo(char archivo[],stAlumno p[],int validos)
{
    int i = 0;
    FILE* archi;
    archi = fopen(archivo,"ab");
    if(archi != NULL)
    {
        while(i<validos)
        {
            fwrite(&p[i],sizeof(stAlumno),1,archi);
            i++;
        }
        fclose(archi);
    }
}

void archivoToArreglo(char archivo[])
{

    stAlumno aux[DIM_MAX];
    int i = 0;
    int anio = 0;
    FILE* archi;
    archi = fopen(archivo,"rb");
    anio = preguntarDato();

    if(archi != NULL)
    {
        while(fread(&aux[i],sizeof(stAlumno),1,archi)>0)
        {
            if(anio == aux[i].anio)
            {
                i++;
            }
        }
        fclose(archi);
    }
    mostrarArregloAlumnos(aux,i);
}

void mostrarArregloAlumnos(stAlumno p[],int validos)
{
    for(int i = 0; i<validos; i++)
    {
        printf("Nombre: %s \n",p[i].nombreYapellido);
        printf("Edad: %i\n",p[i].edad);
        printf("Legajo: %i\n",p[i].legajo);
        printf("A�o que cursa: %i\n",p[i].anio);
    }
}

/**Crear una funci�n que retorne la cantidad de registros que tiene el archivo. Usar fseek y ftell.
 Puede pensar la funci�n para uso gen�rico,
  que sirva para averiguar la cantidad de registros de cualquier archivo.*/

int contarAlumnos(char archivo[]){

int cantRegistro;
FILE* archi;
archi = fopen(archivo,"rb");
if(archi !=NULL){
    fseek(archi,0,SEEK_END);
    cantRegistro = ftell(archi)/sizeof(stAlumno);
    fclose(archi);
}
return cantRegistro;
}

/**Dado un archivo de alumnos, que tenga al menos 10 registros,
hacer una funci�n que muestre el contenido de un registro, cuyo n�mero (entre 0 y 9) se pase por par�metro.
Controlar no sobrepasar los l�mites del archivo.*/

void mostrarPosPedida(char archivo[]){

stAlumno b;

puts("INGRESE UN DATO ENTRE 1 Y 9\n");
int dato = preguntarDato()-1;

FILE* archi;
archi= fopen(archivo,"rb");
if(dato > 0 && dato<9){

    if(archi != NULL){
        fseek(archi,sizeof(stAlumno)*dato,SEEK_SET );
        fread(&b,sizeof(stAlumno),1,archi);
        fclose(archi);
        mostrarAlumno(b);
    }
}else{
printf("ERROR NUMERO INVALIDO");
}
}

/**Realice una (o varias) funciones que permitan modificar un registro existente en el archivo de alumnos.
 La misma debe permitir modificar uno o todos los campos de la estructura
 y sobreescribir el registro existente en el archivo.*/

 void modificarAlumnos(char archivo[]){

int cantAlumnos = contarAlumnos(archivo);
int datoModificar = preguntarDato()-1;
stAlumno b;

FILE* archi;
archi = fopen(archivo,"r+b");
if(archi != NULL){

       if(datoModificar >= 0 && datoModificar < cantAlumnos){
        fseek(archi,sizeof(stAlumno)*datoModificar,SEEK_SET);
        fread(&b,sizeof(stAlumno),1,archi);
        modificarUnAlumno(&b);
        fseek(archi,sizeof(stAlumno)*-1, SEEK_CUR);
        fwrite(&b,sizeof(stAlumno),1,archi);

            }
    fclose(archi);
        }
    }

void modificarUnAlumno(stAlumno* b){

    int op = 0;
    cleanWindows();
    puts("-----------ALUMNO ELEGIDO-------\n");
    mostrarAlumno(*b);


    printf("Que desea cambiar\n");
    printf("1-MODIFICAR NOMBRE Y APELLIDO\n");
    printf("2-MODIFICAR EDAD\n");
    printf("3-MODIFICAR LEGAJO");
    printf("4-MODIFICAR ANIO QUE CURSA\n");
    printf("5-MODIFICAR TODO\n");
    printf("6-NO MODIFICAR NADA\n");
    puts("QUE OPCION ELIGE: \n");
    scanf("%i",&op);

switch(op){
case 1:
    printf("Ingrese el nuevo nombre y apellido\n");
    fflush(stdin);
    gets(b->nombreYapellido);
break;
case 2:
    printf("ingrese la nueva edad\n");
    fflush(stdin);
    scanf("i",&b->edad);
break;
case 3:
    printf("Ingrese el nuevo legajo\n");
    fflush(stdin);
    scanf("%i",&b->legajo);
break;
case 4:
    printf("Ingrese el nuevo anio de cursada\n");
    fflush(stdin);
    scanf("%i",&b->anio);
break;
case 5:
    (*b) = cargaUnAlumno();
break;
case 6:
    op == 7;
break;
default:
    printf("OPCION NO VALIDA\n");
}
puts("-----------ALUMNO MODIFICADO-------\n");
    mostrarAlumno(*b);


}

/**Dado un archivo de alumnos, hacer una funci�n que invierta los elementos del mismo.
No se puede usar otro archivo auxiliar ni un arreglo auxiliar.
Debe trabajar sobre el archivo. Puede utilizar variables de tipo alumno auxiliares.*/


void menu(char archivo[],stAlumno persona[],Pila* legajos){

///DEF variables para que no esten en el switch
    int edad = 0;
    int contEdad = 0;
    int desde = 0;
    int hasta = 0;
    int anio = 0;
    int cantidadAnio = 0;
    int validos = 0;
    int cantidadAlumnos = 0;

char op;
int opcionCase;
do{
opciones();
printf("........QUE OPCION ELIGE........\n");
scanf("%i",&opcionCase);

switch(opcionCase){
    case 1:
    cargarAlumnos(archivo);
break;
    case 2:
    pasarLegajoToPila(archivo,&legajos);
    mostrar(&legajos);
break;
    case 3:
    edad = preguntarDato();
    contEdad = contarMayores(archivo,edad);
    mostrarCantidad(contEdad);
break;
    case 4:
    puts("----------------------DESDE-------------------------------\n");
    desde = preguntarDato();                                    ///EN EL SWITCH ACLARAR QUE DATO ESTA INGRESANDO EL USER
    puts("----------------------HASTA------------------------------\n");
    hasta = preguntarDato();
    rangoNombres(archivo,desde,hasta);
break;
    case 5:
    encontrarMayorAlumno(archivo);
break;
    case 6:
    anio = preguntarDato();
    cantidadAnio = alumnosXAnio(archivo,anio);
    mostrarCantidad(cantidadAnio);
break;
    case 7:
    validos = cargarArregloAlumnos(persona);
    arregloToArchivo(archivo,persona,validos);
break;
    case 8:
    archivoToArreglo(archivo);
break;
    case 9:
    mostrarArchivo(archivo);
break;
    case 10:
    cantidadAlumnos = contarAlumnos(archivo);
    mostrarCantidad(cantidadAlumnos);
break;
    case 11:
   puts("\n------------------------------------------------------\n");
    mostrarPosPedida(archivo);
break;
    case 12:
    mostrarArchivo(archivo);
    modificarAlumnos(archivo);
break;
    case 13:

break;

default:
    puts("...........................................................\n");
    printf("ERROR... NO DISPONIBLE U OPCION INVALIDA");
    puts("\n...........................................................\n");
    }
    puts("\n........................QUE DESEA REALIZAR......................\n");
    op = operador();
cleanWindows();


}while(op == 's' || op == 'S');

}

void opciones(){
puts("\n.............................ELEGIR OPCION...........................\n");
printf("1-Cargar alumnos\n");
printf("2-Pasar legajos elegidos\n");
printf("3-Mostrar cantidad por edad\n");
printf("4-Desde que edad y hasta que edad desea ver la informacion de los alumno\n");
printf("5-Averiguar la persona mas longeba\n");
printf("6-Averiguar la cantidad de personas por el anio en que cursa\n");
printf("7-Cargar un arreglo con alumnos(solo a�ade mas)\n");
printf("8-Muestra los alumnos por a�o que cursan\n");
printf("9-Muestra todos los alumnos\n");
printf("10-Saber cuantos alumnos hay en el archivo\n");
printf("11-Elegir para ver un alumno entre la posicion 1 y 9 \n");
printf("12-Modificar alumno\n");
printf("13-NO DISPONIBLE\n");

}
