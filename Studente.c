#include "Studente.h"

/**Definizione Funzioni**/

void Nuova_Partita(d_partita *partita,d_giocatore *giocatore,d_aula *tabellone,int n,d_sfiga *lista,int modalita_gioco){

    //inizializzo a 0 il giocatore attivo e il numero di turni
    partita->giocatore_attivo=0;
    partita->n_turni=0;

    do{
            //chiedo all'utente di scegliere la modalità di gioco
            printf("\nSCEGLI LA MODALITA' DI GIOCO\n\nPremi [0] per la modalita gioco classica\nPremi [1] per la modalita gioco bonus\n\nMODALITA':");
            scanf("%d",&modalita_gioco);

            while(getchar()!='\n');

    }while(modalita_gioco!=0 && modalita_gioco!=1);

    if(modalita_gioco==0){//modalita' classica

        #ifdef _WIN32

            system("cls");

        #endif // _WIN32

        #ifdef linux

            system("clear");

        #endif // linux

        printf("\nMODALITA CLASSICA APERTA!!!\n");

        partita=inizializza_n_giocatori(partita);

        distribuisci_terreni(tabellone,n,partita);

        giocatore=inizializza_dati_giocatori(partita,giocatore,tabellone,n);

        lista=inizializza_sfighe(lista);

        lista=mischia_sfighe(lista);

        #ifdef _WIN32

            system("cls");

        #endif // _WIN32

        #ifdef linux

            system("clear");

        #endif // linux

        Partita(partita,giocatore,tabellone,n,lista,modalita_gioco);

    }else{//modalita' bonus

        printf("\nMODALITA BONUS APERTA!!!\n");

        partita=inizializza_n_giocatori(partita);

        giocatore=inizializza_dati_giocatori(partita,giocatore,tabellone,n);

        lista=inizializza_sfighe(lista);

        lista=mischia_sfighe(lista);

        Partita(partita,giocatore,tabellone,n,lista,modalita_gioco);

    }



}
d_partita* inizializza_n_giocatori(d_partita *partita){

     do{
            printf("\nInserisci il numero di giocatori!!!\n");
            printf("Il numero di giocatori non deve essere minore di 2 e maggiore di 8\n");
            printf("\nNUMERO GIOCATORI:");
            scanf("%d",&partita->n_giocatori);
            #ifdef _WIN32

                system("cls");

            #endif // _WIN32

            #ifdef linux

                system("clear");

            #endif // linux


            while(getchar()!='\n');

            if((partita->n_giocatori<2)||(partita->n_giocatori>8)){

                printf("\nERRORE,il numero di giocatori non valido!!!\n");
            }

     }while((partita->n_giocatori<2)||(partita->n_giocatori>8));

     printf("\nNUMERO GIOCATORI:%d\n",partita->n_giocatori);

     return partita;

 }

void distribuisci_terreni(d_aula *tabellone,int n,d_partita *partita){

    int i,j;
     //uttilizzo questo contatore per assegnare il proprietario all'aula
    int id=0;

    int esci=0;

    do{//inizio ciclo
        //assegno casualmente un terreno a i
        i=0;
        esci=0;

        i=rand()%n;

        //verifico che sia un aula e che non appartenga a nessun giocatore
        if(tabellone[i].tipo==0&&tabellone[i].proprietario==-1){


            tabellone[i].proprietario=id;

            //probabilita' 3 su 2 scrivania
            if(rand()%3==2){

                tabellone[i].flag_scrivania=true;
            }

            if(id<(partita->n_giocatori-1)){

            //incremento il contatore
                id++;

            }else{

                //inizializzo a 0 il contatore
                id=0;
            }
        }




        //verifico se tutte le aule sono state consegnate
        for(j=0;j<n;j++){

            if((tabellone[j].proprietario==-1)&&(tabellone[j].tipo==0)){

                esci++;
            }
        }


    }while(esci);//fine di ciclo

}

 d_giocatore *inizializza_dati_giocatori(d_partita *partita,d_giocatore *giocatore,d_aula *tabellone,int n){

     int i,j;
     int tot;

     //alloco dinamicamente il giocatore
     giocatore=(d_giocatore*)malloc(sizeof(d_giocatore)*(partita->n_giocatori));

     //verifico che il file non sia vuoto
     if(giocatore==NULL){

        printf("\n C'e' stato un errore!!\n");
        exit(-1);

     }
     //inserisco i dati del giocatore
     for(i=0;i<(partita->n_giocatori);i++){

        tot=0;

        printf("\nInserisci il nome del giocatore %d!!!\nNome:",i+1);
        scanf("%s",giocatore[i].nome);
        while(getchar()!='\n');

        giocatore[i].id=i;
        giocatore[i].numero_aule=0;
        giocatore[i].posizione=0;
        giocatore[i].pulizia_bagno=0;
        giocatore[i].soldi=0;

        //incremento il numero di aule del giocatore
        for(j=0;j<n;j++){

            if(tabellone[j].proprietario==i){

                //incremento il numero delle aule del giocatore
                giocatore[i].numero_aule++;

                //sommo il prezzo delle aule alla variabile tot
                tot+=tabellone[j].costo;
            }
        }

        //assegno il budget al giocatore
        giocatore[i].soldi=((12000/(partita->n_giocatori))-tot);

        }


     return giocatore;
 }



d_sfiga* inizializza_sfighe(d_sfiga* lista){

    FILE *fp;

    int i,s1,s2,s3,s4;

    //apro il file ListaSfighe in modalità lettura

    fp=fopen("ListaSfighe.txt","r");

    if(fp==NULL){

        exit(-1);
    }

    //leggo il numero delle sfighe dal file di testo

    fscanf(fp,"%d %d %d %d",&s1,&s2,&s3,&s4);
    fscanf(fp,"\n");

    //allocco dinamicamente le sfighe

    lista=(d_sfiga*)malloc(sizeof(d_sfiga)*(TOT_SFIG));

    //verifico che il file sia alloccato corretamente

    if(lista==NULL){

        exit(-1);
    }

    //leggo le sfighe dal file,le alloco dinamicamente in memoria e le suddivido nei vari tipi

    //alloco le sfighe del primo tipo

    for(i=0;i<s1;i++){

        fscanf(fp,"%d %[^\n]s",&lista[i].tassa,lista[i].frase);
        fscanf(fp,"\n");

        lista[i].tipo=1;
        lista[i].posizione=0;
        lista[i].aula=0;
        lista[i].scrivania=0;
        lista[i].tenda=0;


    }
    //alloco le sfighe del secondo tipo

    for(i=s1;i<(s1+s2);i++){

        fscanf(fp,"%d %d %d %[^\n]s",&lista[i].aula,&lista[i].scrivania,&lista[i].tenda,lista[i].frase);
        fscanf(fp,"\n");

        lista[i].tipo=2;
        lista[i].posizione=0;
        lista[i].tassa=0;
    }

    //alloco le sfighe del terzo tipo

    for(i=s1+s2;i<(TOT_SFIG-s4);i++){

        fscanf(fp,"%[^\n]s",lista[i].frase);
        fscanf(fp,"\n");

        lista[i].tipo=3;
        lista[i].posizione=0;
        lista[i].tassa=0;
        lista[i].aula=0;
        lista[i].scrivania=0;
        lista[i].tenda=0;
    }

    //alloco le sfighe del quarto tipo

    for(i=(TOT_SFIG-s4);i<TOT_SFIG;i++){

        fscanf(fp,"%d %[^\n]s",&lista[i].posizione,lista[i].frase);
        fscanf(fp,"\n");

        lista[i].tipo=4;
        lista[i].tassa=0;
        lista[i].aula=0;
        lista[i].scrivania=0;
        lista[i].tenda=0;
    }

    //chiudo il file

    fclose(fp);

    return lista;

}



d_sfiga * mischia_sfighe(d_sfiga *lista){//Deitel

    d_sfiga temp;//variabile di tipo sfiga temporanea

    int i;
    int j=0;
    //cicla finche' i e minore del totale dell sfighe
    for(i=0;i<TOT_SFIG;i++){

        j=rand()%(TOT_SFIG);

        temp=lista[i];
        lista[i]=lista[j];
        lista[j]=temp;

    }




    return lista;

}

void stampa_budget_giocatore(d_giocatore *giocatore,d_partita *partita){

    //se il turno e' del primo giocatore
    if(partita->giocatore_attivo==0){

        int i;
        //cilca finche i e minore del numero dei giocatori
        for(i=0;i<(partita->n_giocatori);i++){

            //verifico il tipo di id e stampo a video il segnaposto
            switch(giocatore[i].id){

                case 0:{

                    printf("\nSegnaposto: Automobile\n");
                    break;
                }

                case 1:{

                    printf("\nSegnaposto: Ferro Da Stiro\n");
                    break;
                }

                case 2:{

                    printf("\nSegnaposto: Barca\n");
                    break;
                }

                case 3:{

                    printf("\nSegnaposto: Ditale\n");
                    break;
                }

                case 4:{

                    printf("\nSegnaposto: Scarpa\n");
                    break;
                }

                case 5:{

                    printf("\nSegnaposto: Carriola\n");
                    break;
                }

                case 6:{

                    printf("\nSegnaposto: Cane\n");
                    break;
                }

                case 7:{

                    printf("\nSegnaposto: Cappello\n");
                    break;
                }

            }
            //stampo a video nome,budget e numero aule
            printf("Nome: %s \nBudget: %d \nNumero Aule %d \n",giocatore[i].nome,giocatore[i].soldi,giocatore[i].numero_aule);
        }
    }
}


void Carica_Partita(d_giocatore *giocatore,d_aula *tabellone,int n,d_partita partita,d_sfiga *lista,int modalita_gioco){


    FILE *fp=NULL;
    d_aula *tab=NULL;
    int i;


    //apro il file in modalità lettura
    fp=fopen("Monopoly.bin","rb");

    //verifico che il file sia stato aperto correttamente
    if(fp==NULL){

        printf("\nNessuna Partita Salvata!!!\n");

        exit(-1);

    }

    fread(&partita,sizeof(d_partita),1,fp);

    giocatore=(d_giocatore*)malloc(sizeof(d_giocatore)*partita.n_giocatori);

    fread(giocatore,sizeof(d_giocatore),partita.n_giocatori,fp);

    tab=(d_aula*)malloc(sizeof(d_aula)*n);

    fread(tab,sizeof(d_aula),n,fp);

    fread(&modalita_gioco,sizeof(int),1,fp);

    fclose(fp);//chiudo il file


    for(i=0;i<n;i++){

        tabellone[i]=tab[i];
    }


    lista=inizializza_sfighe(lista);

    lista=mischia_sfighe(lista);

    Partita(&partita,giocatore,tabellone,n,lista,modalita_gioco);

    fp = NULL;
}
