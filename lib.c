#include "lib.h"

int validaString(char chain[],int acc)
{
    int i,cantCaracter,nroFlotante=-1,nroNegativo=-1,retorno=1;
    cantCaracter=strlen(chain);
    switch(acc)
    {
        case 1:
            nroFlotante=strcspn(chain,".");
            nroNegativo=strcspn(chain,"-");
            for(i=0;i<cantCaracter;i++)
            {
                if(i==0&&nroNegativo==i)
                    continue;
                if(nroNegativo==0&&(i==nroFlotante&&nroFlotante>1))
                    continue;
                if(nroNegativo==-1&&(i==nroFlotante&&nroFlotante>0))
                    continue;
                if(isdigit(chain[i])==0)
                {
                    retorno=0;
                    break;
                }
            }
            break;
        case 2:
            for(i=0;i<cantCaracter;i++)
            {
                if(isalpha(chain[i])==0)
                {
                    retorno=0;
                    break;
                }
            }
    }
    return retorno;
}

int validarLargoString(char chain[],int minCaracter,int maxCaracter)
{
    int cont,retorno=1;
    cont=strlen(chain);
    if(cont<minCaracter||cont>maxCaracter)
        retorno=0;
    return retorno;
}

int menu(char screenPrint[],int min,int max,char screenPrintError[],int cantError)
{
    int selection,contCantError=0,resp,validation;
    char selectionChain[128];

    do{
        puts(screenPrint);
        fflush(stdin);
        gets(selectionChain);
        validation=validaString(selectionChain,1);
        if(validation==0)
        {
            contCantError++;
            printf("\t\t\t\tINGRESE NRO. SOLAMENTE\n\n\n");
            system("pause");
            system("cls");
        }
        else
        {
            selection=atoi(selectionChain);
            if(contCantError!=cantError&&(selection<min||selection>max))
            {
                contCantError++;
                system("cls");
                printf("\t\t\t\t%s\n\n\n",screenPrintError);
                system("pause");
                system("cls");
            }
            if(contCantError==cantError)
            {
                do
                {
                    printf("FUERA DE RANGO VARIAS VECES - %cQUERES CONTINUAR?\n",168);
                    printf("\n0 --> CONTINUAR\n"
                            "1 --> SALIR\n");

                    scanf("%d",&resp);

                    if(resp==1)
                    {
                        selection=-1;
                        break;
                    }
                    else
                    {
                        system("cls");
                        contCantError=0;
                    }
                }while(resp!=0&&resp!=1);
            }
        }
    }while(validation==0||resp==0||selection<min||selection>max);
    system("cls");
    return selection;
}

int guardarPelicula(movie *arrayPelicula,FILE *PunteroArchivo)
{
    int retorno=1;

    if( (PunteroArchivo=fopen("peliculas.dat","rb+")) == NULL)
    {
        if( (PunteroArchivo=fopen("peliculas.dat","wb+")) == NULL)
        {
            printf("\t\t\t\t* * * * * * * *  ERROR EN ARCHIVO  * * * * * * * *\n\n");
            retorno=0;
            exit(1);
        }
    }

    fflush(stdin);
    fseek(PunteroArchivo,0L,SEEK_END);
    if(fwrite((arrayPelicula),sizeof(movie),1,PunteroArchivo)!=1)
        retorno=0;

    fclose(PunteroArchivo);

    return retorno;
}

int cargarPelicula(movie *arrayPelicula,FILE *PunteroArchivo)
{
    int retorno=1,OK;
    char string[1024];

    do
    {
        printf("TITULO: ");
        fflush(stdin);
        gets(string);
        if( (OK=validarLargoString(string,1,50)) ==0)
            printf("INGRESE ENTRE 1 Y 50 CARACTERES\n");
        else
            strcpy((arrayPelicula)->titulo,string);
    }while(OK==0);

    do
    {
        printf("GENERO: ");
        fflush(stdin);
        gets(string);
        if( (OK=validarLargoString(string,1,50)) ==0)
            printf("INGRESE ENTRE 1 Y 50 CARACTERES\n");
        else
            strcpy((arrayPelicula)->genero,string);
    }while(OK==0);

    do
    {
        printf("DURACION: ");
        fflush(stdin);
        gets(string);
        if( (OK=validaString(string,1)) ==0 )
        {
            printf("INGRESE NROS SOLAMENTE\n");
            continue;
        }
        else
            (arrayPelicula)->duracion=atoi(string);
        if((arrayPelicula)->duracion<0)
        {
            printf("LA DURACION DEBE SER UN NUMERO POSITIVO");
        }
    }while(OK==0);

    do
    {
        printf("DESCRIPCION: ");
        fflush(stdin);
        gets(string);
        if( (OK=validarLargoString(string,1,100)) ==0)
            printf("INGRESE ENTRE 1 Y 100 CARACTERES\n");
        else
            strcpy((arrayPelicula)->descripcion,string);
    }while(OK==0);

    do
    {
        printf("PUNTAJE: ");
        fflush(stdin);
        gets(string);
        if( (OK=validaString(string,1)) ==0)
        {
            printf("INGRESE NRO.\n");
            continue;
        }
        else
            (arrayPelicula)->puntaje=atof(string);
            if((arrayPelicula)->puntaje<0||(arrayPelicula)->puntaje>10)
                printf("PUNTAJE ENTRE 0 Y 10\n");
    }while(OK==0 || (arrayPelicula)->puntaje<0 || (arrayPelicula)->puntaje>10);

    printf("Link imagen: ");
    fflush(stdin);
    gets(string);
    strcpy((arrayPelicula)->linkImagen,string);

    (arrayPelicula)->flag=CARGADO;

    if(guardarPelicula((arrayPelicula),PunteroArchivo)==0) retorno=0;

    return retorno;
}

int buscarPelicula(movie *arrayPelicula,FILE *PunteroArchivo)
{
    int retorno=1,cont=1;
    char buscaString[51];

    if((PunteroArchivo=fopen("peliculas.dat","rb+")) ==NULL)
    {
        retorno=0;
        exit(1);
    }
    do
    {
        printf("INGRESE EL TITULO A BUSCAR: ");
        fflush(stdin);
        gets(buscaString);
    }while(validarLargoString(buscaString,1,50)==0);

    while(!feof(PunteroArchivo))
    {
        fread((arrayPelicula),sizeof(movie),1,PunteroArchivo);
            if(((arrayPelicula)->flag!=BAJA_LOGICA) && (stricmp((arrayPelicula)->titulo,buscaString) ==0))
            {
                retorno=1;
                break;
            }
            else
            {
                retorno=0;
                fseek(PunteroArchivo,(cont*sizeof(movie)),SEEK_SET);
                cont++;
            }
    }
    fclose(PunteroArchivo);
    return retorno;
}

int borrarPelicula(movie arrayPelicula,FILE *PunteroArchivo)
{
    int retorno=1;
    if(buscarPelicula(&arrayPelicula,PunteroArchivo) !=0)
    {
        printf("\nBORRANDO %s\n\n",arrayPelicula.titulo);
        system("pause");
        arrayPelicula.flag=BAJA_LOGICA;
        guardarPelicula(&arrayPelicula,PunteroArchivo);
    }
    else retorno=0;
    system("cls");
    return retorno;
}

int moficarPelicula(movie arrayPelicula,FILE *PunteroArchivo)
{
    int retorno=1;

    printf("\t\t\t\t* * * * * * * *  MODIFICAR  * * * * * * * *\n\n");

    if(buscarPelicula(&arrayPelicula,PunteroArchivo)!=0)
    {
        cargarPelicula(&arrayPelicula,PunteroArchivo);
    }
    else retorno=0;

    return retorno;
}

/** IMPORTANTE VERIFICAR Y TERMINAR ESTA FUNCION */
int generaHTML(FILE *PunteroArchivo)
{
    /** INICIO_DECLARACION */
    movie *peliculas;   FILE *HTML;  int retorno=1,contReserva=1,i; char copiar[7168];
    char html_1[]=("<article class='col-md-4 article-intro'>"
            "<a href='#'>"
            "<img class='img-responsive img-rounded' src='");
    char html_2[]=("' alt=''></a><h3><a href='#'>"),html_3[]=("</a></h3><ul><li>Género: ");
    char html_4[]=("</li><li>Puntaje: "),html_5[]=("</li><li>Duración: "),html_6[]=("</li></ul><p>");
    char html_7[]=("</p></article>");
    /** FIN_DECLARACION */

    /** ABRO ARCHIVOS */
    if((PunteroArchivo=fopen("peliculas.dat","rb+")) ==NULL)
    {
        retorno=0;
        exit(1);
    }

    if( (HTML=fopen("index.html","rb+")) == NULL)
    {
        if( (HTML=fopen("index.html","wb+")) == NULL)
        {
            printf("\t\t\t\t* * * * * * * *  ERROR EN ARCHIVO  * * * * * * * *\n\n");
            retorno=0;
            exit(1);
        }
    }

    /** RESERVO MEMORIA DINAMICA */
    peliculas=calloc(contReserva,sizeof(movie));
    /** RECORRO EL ARCHIVO */
    while(!feof(PunteroArchivo))
    {
        if(fread((peliculas),sizeof(movie),1,PunteroArchivo) !=1)
        {
            retorno=0;
            printf("%d",retorno);
            break;
        }
        fseek(PunteroArchivo,(contReserva*sizeof(movie)),SEEK_SET);
        peliculas=realloc(peliculas,(contReserva*sizeof(movie)));
        contReserva++;
    }
    if(retorno==1)
    {

        for(i=1;i<contReserva;i++)
        {
            sprintf(copiar,"%s %s\n\n %s %s %s %s %s %.2f %s %d %s %s %s",html_1,(peliculas+i)->linkImagen,html_2,(peliculas+i)->titulo,html_3,
                      (peliculas+i)->genero,html_4,(peliculas+i)->puntaje,html_5,(peliculas+i)->duracion,html_6,(peliculas+i)->descripcion,
                      html_7);
            fflush(stdin);
            fseek(PunteroArchivo,0L,SEEK_END);
            if(fwrite(copiar,sizeof(movie),1,HTML) !=1)
            {
                retorno=0;
                break;
            }
        }
    }

    return retorno;
}
