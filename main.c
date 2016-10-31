#include "lib.h"

int main()
{
/** @INICIO_DECLARO */
    FILE *PunteroArchivo;
    movie arrayPelicula;
    int selec,controlAcceso=0;
/** @FIN_DECLARO */

/** @INICIO_MENU */
    system("color 3F");
    do
    {
        selec=menu("1) AGREGAR PELICULA\n"
             "2) BORRAR PELICULA\n"
             "3) MODIFICAR PELICULA\n"
             "4) GENERAR PAGINA WEB\n"
             "5) SALIR\n\n",1,5,"* * * * * * * * ERROR / VERIFICAR INGRESO * * * * * * * *",3);
        switch(selec)
        {
        case 1:
            if(cargarPelicula(&arrayPelicula,PunteroArchivo)==1)
            {
                printf("\t\t\t\t* * * * * * * *  PELICULA CARGADA  * * * * * * * *\n\n");
                controlAcceso++;
            }
            else
                printf("\t\t\t\t* * * * * * * *  CARGA NO REALIZADA  * * * * * * * *\n\n");
            break;
        case 2:
            if(controlAcceso>0)
            {
                if((borrarPelicula(arrayPelicula,PunteroArchivo)) ==1)
                    controlAcceso--;
                else
                    printf("\t\t\t\t* * * * * * * *  LA PELICULA NO EXISTE  * * * * * * * *\n\n");
            }
            else
                printf("\t\t\t\t* * * * * * * *  INGRESE PELICULA  * * * * * * * *\n\n");
            break;
        case 3:
            if(controlAcceso>0)
            {
                if(moficarPelicula(arrayPelicula,PunteroArchivo) ==1)
                    printf("\t\t\t\t* * * * * * * *  SE MODIFICO CORRECTAMENTE  * * * * * * * *\n\n");
                else
                    printf("\t\t\t\t* * * * * * * *  ERROR AL MODIFICAR  * * * * * * * *\n\n");
            }
            else
                printf("\t\t\t\t* * * * * * * *  INGRESE PELICULA  * * * * * * * *\n\n");
            break;
        case 4:
            if(controlAcceso>0)
            {
                if(generaHTML(PunteroArchivo)==1)
                {
                    printf("\t\t\t\t* * * * * * * *  ARCHIVO HTML GENERADO  * * * * * * * *\n\n");
                }
                else
                    printf("\t\t\t\t* * * * * * * *  ERROR AL GENERAR ARCHIVO HTML  * * * * * * * *\n\n");
            }
            else
                printf("\t\t\t\t* * * * * * * *  INGRESE PELICULA  * * * * * * * *\n\n");
            break;
        case -1:
            selec=5;
            break;

        }
    }while(selec!=5);

    return 0;
}
