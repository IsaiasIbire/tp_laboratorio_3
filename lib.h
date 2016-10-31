#ifndef LIB_H_included
#define LIB_H_included

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define             UBICACION_ARCHIVO               "peliculas.dat"

/** INICIO_ESTADOS @ESTRUCTURA */
#define             CARGADO                         1
#define             BAJA_LOGICA                     -1
/** FIN_ESTADOS @ESTRUCTURA */

#endif // LIB_H_included

/** INICIO_ESTRUCTURA @DECLARO */
typedef struct
{
    char titulo[51],genero[51],descripcion[101],linkImagen[1024];
    float puntaje;
    int duracion,flag;
}movie;
/** FIN_ESTRUCTURA @DECLARO */

/** @INICIO_PROTOTIPO */

/**
* /brief    VALIDA NROS / LETRAS
* /param    ADENA A VALIDAR
* /param    TIPO DE VALIDACION (1 -> NRO. / 2 -> Letra)
* /return   !=0 SI ES EL DATO CORRESPONDIENTE */
int validaString(char chain[],int acc);

/**
* /brief    VALIDA EL LARGO DE UN STRING
* /param    CADENA A VALIDAR
* /param    MINIMO QUE DEBE TENER LA CADENA
* /param    MAXIMO QUE DEBE TENER LA CADENA
* /return   == 1 SI ES EL DATO CORRESPONDIENTE */
int validarLargoString(char chain[],int minCaracter,int maxCaracter);

/**
* /brief    MUESTRA MENU
* /param    MSJ PRINTF
* /param    MINIMO PERMITIDO
* /param    MAXIMO PERMITIDO
* /param    MSJ OCURRE UN ERROR
* /param    CANT ERRORES PERMITIDOS
* /return   DEVUELVE LA SELECCIÓN
* IMPORTANTE: SI SE CUMPLE LA CANTIDAD MAXIMA DE ERRORES PERMITIDOS Y NO QUIERE CONTINUAR RETORNA -1 */
int menu(char screenPrint[],int min,int max,char screenPrintError[],int cantError);

/**
* /brief    GUARDA UNA PELICULA
* /param    PUNTERO DE ESTRUCTURA TIPO MOVIE
* /param    PUNTERO TIPO FILE
* /return   !=0 SI SE GUARDO CORRECTAMENTE */
int guardarPelicula(movie *arrayPelicula,FILE *PunteroArchivo);

/**
* /brief    CARGA LA ESTRUCTURA PARA LUEGO GUARDARLA
* /param    PUNTERO DE ESTRUCTURA TIPO MOVIE
* /param    PUNTERO TIPO FILE
* /return   !=0 SI SE CARGO CORRECTAMENTE */
int cargarPelicula(movie *arrayPelicula,FILE *PunteroArchivo);

/**
* /brief    BUSCA UNA PELICULA EN EL ARCHIVO
* /param    PUNTERO DE ESTRUCTURA TIPO MOVIE
* /param    PUNTERO TIPO FILE
* /return   !=0 SI SE ENCONTRO CORRECTAMENTE */
int buscarPelicula(movie *arrayPelicula,FILE *PunteroArchivo);

/**
* /brief    BORRA LOGICAMENTE UNA PELICULA DEL ARCHIVO
* /param    ESTRUCTURA TIPO MOVIE
* /param    PUNTERO TIPO FILE
* /return   !=0 SI SE BORRO CORRECTAMENTE */
int borrarPelicula(movie arrayPelicula,FILE *PunteroArchivo);

/**
* /brief    MODIFICA UNA PELICULA
* /param    ESTRUCTURA TIPO MOVIE
* /param    PUNTERO TIPO FILE
* /return   !=0 SI SE MODIFICO CORRECTAMENTE */
int moficarPelicula(movie arrayPelicula,FILE *PunteroArchivo);

int generaHTML(FILE *PunteroArchivo);
