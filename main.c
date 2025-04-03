#include "Monopoly.h"

int main()
{

    //creo un vettore di tipo d_aula e lo inizializzo

      d_aula tabellone [N_TAB]={

        {0,0,0,0,{"VIA!"},3,false,false,-1},
        {60,3,6,12,{"AULA G"},0,false,false,-1},
        {0,0,0,0,{"SFIGA!"},2,false,false,-1},
        {60,3,6,12,{"AULA C"},0,false,false,-1},
        {80,4,8,16,{"AULA F"},0,false,false,-1},
        {0,100,0,0,{"TASSE!"},1,false,false,-1},
        {100,5,10,20,{"AULA STUDIO"},0,false,false,-1},
        {0,0,0,0,{"SFIGA!"},2,false,false,-1},
        {100,5,10,20,{"SIMAZ"},0,false,false,-1},
        {120,6,12,24,{"LAORATORIO T"},0,false,false,-1},
        {0,0,0,0,{"BAGNI"},3,false,false,-1},
        {140,7,14,28,{"VAX"},0,false,false,-1},
        {0,0,0,0,{"SFIGA!"},2,false,false,-1},
        {140,7,14,82,{"G.A.R."},0,false,false,-1},
        {160,8,16,32,{"BIBBLIOTECA"},0,false,false,-1},
        {0,150,0,0,{"TASSE!"},1,false,false,-1},
        {180,9,18,36,{"AULA B"},0,false,false,-1},
        {0,0,0,0,{"SFIGA!"},2,false,false,-1},
        {180,9,18,36,{"SEGRETERIA"},0,false,false,-1},
        {200,10,20,40,{"AULA A"},0,false,false,-1},
        {0,0,0,0,{"CORRIDOIO"},3,false,false,-1},
        {220,11,22,44,{"UFFICIO SCATENI"},0,false,false,-1},
        {0,0,0,0,{"SFIGA!"},2,false,false,-1},
        {220,11,22,44,{"BAGNO PROFESSORI"},0,false,false,-1},
        {240,12,24,48,{"AULA D"},0,false,false,-1},
        {0,200,0,0,{"TASSE!"},1,false,false,-1},
        {260,13,26,52,{"LAB 3"},0,false,false,-1},
        {260,13,26,52,{"LAB 4"},0,false,false,-1},
        {0,0,0,0,{"SFIGA!"},2,false,false,-1},
        {280,14,28,56,{"LAB M"},0,false,false,-1},
        {0,0,0,0,{"BATCAVERNA"},3,false,false,-1},
        {300,15,30,60,{"AULA M FISICA"},0,false,false,-1},
        {0,0,0,0,{"SFIGA!"},2,false,false,-1},
        {300,15,30,60,{"AULA M CHIMICA"},0,false,false,-1},
        {320,16,32,64,{"AULA M MATEMATICA"},0,false,false,-1},
        {0,250,0,0,{"TASSE!"},1,false,false,-1},
        {360,18,36,72,{"BAR ROTONDO"},0,false,false,-1},
        {0,0,0,0,{"SFIGA!"},2,false,false,-1},
        {360,18,36,72,{"AULA ANATOMICA"},0,false,false,-1},
        {400,20,40,80,{"AULA COSTA"},0,false,false,-1}

    };

    // creo il menu
    int scelta;

    int modalita_gioco=0;
    //variabili di tipo struttura
    d_partita partita;
    d_giocatore *giocatore=NULL;
    d_sfiga *lista=NULL;


    srand(time(NULL));



    do{
            printf("*************************************************************************\n");
            printf("************************Benvenuto in MonopolyCube************************\n");
            printf("*************************************************************************\n");


            printf(" Per iniziare una nuova partita prema [1]\n\n Per caricare la partita prema [2]\n\n Scelta:");
            scanf("%d",&scelta);
            while(getchar()!='\n');//svuoto il buffer


            if(scelta==1){

                    #ifdef _WIN32

                        system("cls");

                    #endif // _WIN32

                    #ifdef linux

                        system("clear");

                    #endif // linux

                    Nuova_Partita(&partita,giocatore,tabellone,N_TAB,lista,modalita_gioco);


                    return 0;



            }else if(scelta==2){

                        printf("\nModalita' Carica Partita \n");

                        Carica_Partita(giocatore,tabellone,N_TAB,partita,lista,modalita_gioco);

                 }else{

                    printf("\nScelta non consentita \n\n");
                 }


        }while(scelta!=1&&scelta!=2);



    return 0;

}
