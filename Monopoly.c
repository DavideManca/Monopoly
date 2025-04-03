#include "Monopoly.h"

/**Definizione Funzioni**/

void Partita(d_partita *partita,d_giocatore *giocatore,d_aula *tabellone,int n,d_sfiga * lista,int modalita_gioco){

    char scelta;
    bool flag_turno[partita->n_giocatori];
    bool controlo_bancarotta[partita->n_giocatori];
    int dado1,dado2,somma;
    int cont_dado_doppio;//contatore dado doppio
    int cont_sfighe=0;//contatore per far scorrrere le sfighe
    int i;

    //inizializzo a false i 2 vettori
    for(i=0;i<partita->n_giocatori;i++){

        flag_turno[i]=false;

        controlo_bancarotta[i]=false;
    }




    do{//inizio ciclo

        //verifico la bancarotta
        if(partita->n_giocatori!=1){
            //se bancarotta e' uguale a true
            if(controlo_bancarotta[partita->giocatore_attivo]==true&&giocatore[partita->giocatore_attivo].soldi<0){
                //se il budget e' minore di 0

                printf("\n%s Il tuo budget e'negativo,sei in bancarotta,la tua partita finisce qui!!!\n",giocatore[partita->giocatore_attivo].nome);

                for(i=partita->giocatore_attivo;i<partita->n_giocatori;i++){

                    //ordino il vettore
                    controlo_bancarotta[i]=controlo_bancarotta[i+1];

                    flag_turno[i]=flag_turno[i+1];
                }
                    //rimuovo il giocatore
                    giocatore=rimuovi_giocatore(partita,giocatore,tabellone,n,modalita_gioco);

                    partita->giocatore_attivo%=partita->n_giocatori;


            }else{if(controlo_bancarotta[partita->giocatore_attivo]==true&&giocatore[partita->giocatore_attivo].soldi>=0){

                        printf("\n%s Hai racimolato un po' di soldi,non sei più in bancarotta!!!\n",giocatore[partita->giocatore_attivo].nome);
                        controlo_bancarotta[partita->giocatore_attivo]=false;

                }
            }
        }


        //verifico che il giocatore non sia in bagno
        giocatore=controllo_bagno(partita,giocatore,flag_turno);
        if(partita->n_giocatori!=1){
            //se il giocatore attivo e'il primo stampo il budget dei giocatori
            stampa_budget_giocatore(giocatore,partita);

            while(flag_turno[partita->giocatore_attivo]!=true){

                    do{//inizio ciclo menu

                        printf("\n\n %s e' il tuo turno!!!\n\nPremi [t] per lanciare i dadi, Premi [s] per salvare la partita\n",giocatore[partita->giocatore_attivo].nome);
                        scanf("%c",&scelta);
                        while(getchar()!='\n');//svuoto il buffer

                        #ifdef _WIN32

                            system("cls");

                        #endif // _WIN32

                        #ifdef linux

                            system("clear");

                        #endif // linux


                        if(scelta!='t'&&scelta!='s'){

                            printf("\nScelta non consentita \n\n");

                        }

                    }while(scelta!='t'&&scelta!='s');//fine ciclo menu(cicla finche l'utente non effetua una scelta corretta)

                    if(scelta=='s'){//se la scelta e' uguale a s salvo la partita

                        salva_partita(partita,giocatore,tabellone,n,&modalita_gioco);

                        exit(-1);

                    }

                    //se la scelta e' uguale a t
                    dado1=MIN+rand()%(MAX-MIN+1);
                    dado2=MIN+rand()%(MAX-MIN+1);

                    somma=dado1+dado2;

                    printf("\nIl valore del primo dado e': %d Il valore del secondo dado e':%d \n",dado1,dado2);

                    if(dado1==dado2){//se dado1 e dado2 hanno lo stesso valore

                        printf("\nLa fortuna e' dalla tua parte,hai ottenuto DADI DOPPI\n\nHAI A DISPOSIZIONE UN ALTRO LANCIO!!!\n\n");

                        //incremento il contatore del dado doppio
                        cont_dado_doppio++;

                        if(cont_dado_doppio==3){//se il contatore ha valore 3

                            printf("\n La fortuna ha un limite!!!va a pulire i bagni!!!!\n");

                            //sposto il giocatore nei bagni
                            giocatore[partita->giocatore_attivo].posizione=10;
                            //assegno al giocatore il numero di turni che deve stare in bagno
                            giocatore[partita->giocatore_attivo].pulizia_bagno=3;

                            flag_turno[partita->giocatore_attivo]=true;//il giocatore ha finito il suo turno e puo'uscire dal ciclo

                        }else{//se cont_dado_doppio e' diverso da 3

                            giocatore=muovi_giocatore(partita,giocatore,tabellone,n,lista,somma);

                            giocatore=verifica_tipo_posizione_aula(partita,giocatore,tabellone,n,lista,somma,modalita_gioco,&tabellone[giocatore[partita->giocatore_attivo].posizione],&cont_sfighe);

                            if(giocatore[partita->giocatore_attivo].pulizia_bagno!=0){

                                flag_turno[partita->giocatore_attivo]=true;

                                printf("\nSei finito in bagno,Il tuo turno finisce ora!!!\n");
                            }

                        }

                    }else{//dado1 non e' uguale a dado 2

                        giocatore=muovi_giocatore(partita,giocatore,tabellone,n,lista,somma);

                        giocatore=verifica_tipo_posizione_aula(partita,giocatore,tabellone,n,lista,somma,modalita_gioco,&tabellone[giocatore[partita->giocatore_attivo].posizione],&cont_sfighe);

                        flag_turno[partita->giocatore_attivo]=true;//il giocatore ha finito il suo turno e puo'uscire dal ciclo
                    }

            }//fine while

            //se il budeget e minore di zero assegno la bancarotta al giocatore
            if(giocatore[partita->giocatore_attivo].soldi<0){

                controlo_bancarotta[partita->giocatore_attivo]=true;

                printf("\nIl tuo budget e' negativo!!!\nSe entro il prossimo turno non recuperi un po' di soldi entri in bancarotta!!!\n\n");
            }

            flag_turno[partita->giocatore_attivo]=false;
            //azzero il contatore
            cont_dado_doppio=0;

            //incremento il numero turni
            partita->n_turni++;

            //se il giocatore attivo e minore del nimero dei giocatori
            if((partita->giocatore_attivo)<(partita->n_giocatori-1)){

                partita->giocatore_attivo++;//passo al giocatore sucessivo

            }else{

                partita->giocatore_attivo=0;
            }
        }


    }while(partita->n_giocatori!=1);//se rimane un solo giocatore fine ciclo

    printf("\n\n\nGIOCATORE %s SEI IL VINCITORE!!!",giocatore[0].nome);

    exit(-1);

}

d_giocatore* controllo_bagno(d_partita *partita,d_giocatore *giocatore,bool *flag){

    //se il giocatore e' in bagno
    if(giocatore[partita->giocatore_attivo].pulizia_bagno!=0){

        printf("\n\n%s In questo momento sei in bagno;salti il turno!!!!\n",giocatore[partita->giocatore_attivo].nome);

        flag[partita->giocatore_attivo]=true;

        giocatore[partita->giocatore_attivo].pulizia_bagno--;//decremento il contatore turni bagno

        partita->giocatore_attivo++;

        if((partita->giocatore_attivo)>(partita->n_giocatori-1)){

            partita->giocatore_attivo=0;
        }

    }else{

        flag[partita->giocatore_attivo]=false;
    }

    return giocatore;
}

d_giocatore* rimuovi_giocatore(d_partita *partita,d_giocatore *giocatore,d_aula *tabellone,int n,int modalita_gioco){

    int i;

    //decremento il numero dei giocatori
    partita->n_giocatori--;

    //elimino il giocatore dal vettore e sposto li altri di una posizione
    for(i=partita->giocatore_attivo;i<(partita->n_giocatori);i++){

        //sposto di una posizione i giocatori
        giocatore[i]=giocatore[i+1];
    }

    //uso la realloc per elliminare definitivamente il giocatore

    giocatore=(d_giocatore*)realloc(giocatore,(partita->n_giocatori)*sizeof(d_giocatore));

    if(giocatore==NULL){

        exit(-1);
    }
    //assegno tutti i terreni del giocatore elliminato al banco

    for(i=0;i<n;i++){

        if(tabellone[i].proprietario==partita->giocatore_attivo){

            tabellone[i].proprietario=-1;
        }
        if(tabellone[i].proprietario>partita->giocatore_attivo){

            tabellone[i].proprietario--;
        }
        //se la modalita e quella bonus rimuovo scrivania e tenda
        if((tabellone[i].proprietario==partita->giocatore_attivo)&&modalita_gioco==1){

            tabellone[i].flag_scrivania=false;
            tabellone[i].flag_tenda=false;
        }
    }

    return giocatore;

}


void salva_partita(d_partita *partita,d_giocatore *giocatore,d_aula *tabellone,int n,int* modalita_gioco){

    FILE *fp=NULL;


    //apro il file in scrittura
    fp=fopen("Monopoly.bin","wb");

    //verifico sei il file e vuoto
    if(fp==NULL){

        printf("\n il file e' vuoto \n");

        return;
    }

    //scrivo nel file

    //salvo la struct partita

    fwrite(partita,sizeof(d_partita),1,fp);

    //salco la struct giocatori
    fwrite(giocatore,sizeof(d_giocatore),partita->n_giocatori,fp);

    //salvo la stuct tabellone

    fwrite(tabellone,sizeof(d_aula),n,fp);

    //salvo la modalita gioco

    fwrite(modalita_gioco,sizeof(int),1,fp);

    //chiudo il file

    fclose(fp);

    fp=NULL;


}

d_giocatore* muovi_giocatore(d_partita *partita,d_giocatore *giocatore,d_aula *tabellone,int n,d_sfiga *lista,int somma){

    //verifico se il giocatore e'passato dal via
    giocatore=controllo_via(partita,giocatore,n,somma);

    //sposto il giocatore
    giocatore[partita->giocatore_attivo].posizione=(giocatore[partita->giocatore_attivo].posizione+somma)%n;

    return giocatore;
}

d_giocatore*controllo_via(d_partita *partita,d_giocatore *giocatore,int n,int somma){

    //se e' passato dal via
    if((giocatore[partita->giocatore_attivo].posizione+somma)>=n){

        printf("\nSei passato dal via!!!questi 20 euro sono tuoi\n");

        //aggiungo i soldi al budget
        giocatore[partita->giocatore_attivo].soldi+=VIA;
    }

    return giocatore;
}

d_giocatore* verifica_tipo_posizione_aula(d_partita *partita,d_giocatore *giocatore,d_aula *tabellone,int n,d_sfiga *lista,int somma,int modalita_gioco,d_aula *posi,int *cont_sfighe){

    printf("\nTi trovi nella casella:%s\n",posi->nome);

    //verifico il tipo della casella

    switch(posi->tipo){

        case 0:{//tipo aula

            //se il terreno appartiene al banco e la modalita e'quella bonus
            if((posi->proprietario==-1)&&(modalita_gioco==1)){

                    giocatore=compra_aula(partita,giocatore,posi);

            }else{if(posi->proprietario==partita->giocatore_attivo){//se il terreno e del giocatore attivo

                    giocatore=acquista_tenda_scrivania(partita,giocatore,posi);
                 }else{//se non e' del giocatore attivo

                    //paga il pedaggio
                    giocatore=paga_pedaggio(partita,giocatore,posi);
                 }

            }

            break;

        }
        case 1:{//tipo tassa

            giocatore=paga_tassa(partita,giocatore,posi);

            break;
        }
        case 2:{//tipo sfiga

            switch(lista[*cont_sfighe].tipo){//verifico il tipo di sfiga

                case 1:{//sfiga tipo1

                    giocatore=sfiga_tipo_1(partita,giocatore,lista,cont_sfighe);

                    break;
                }

                case 2:{//sfiga tipo 2

                    giocatore=sfiga_tipo_2(partita,giocatore,tabellone,n,lista,cont_sfighe);

                    break;
                }

                case 3:{//sfiga tipo 3

                    printf("\nLeggi ad alta voce!!\n\n %s \n",lista[*cont_sfighe].frase);

                    break;
                }

                case 4:{//sfiga tipo 4

                    //leggo la sfiga
                    printf("\n%s\n",lista[*cont_sfighe].frase);

                    //sposto il giocatore
                    giocatore[partita->giocatore_attivo].posizione=lista[*cont_sfighe].posizione;
                    //verifico l'aula in cui e' stato spostato
                    giocatore=verifica_tipo_posizione_aula(partita,giocatore,tabellone,n,lista,somma,modalita_gioco,&tabellone[giocatore[partita->giocatore_attivo].posizione],cont_sfighe);

                    break;
                }

            }//fine verifica tipo sfiga

            break;

        }
        case 3:{//tipo altro

            //se il giocatore si trova in batcaverna
            if(giocatore[partita->giocatore_attivo].posizione==30){

                printf("\nE'vietato entrare in batcaverna!!!Vai subito a pulire i bagni!!!\n");

                //turni in cui dovrà stare in bagno
                giocatore[partita->giocatore_attivo].pulizia_bagno=3;

                //assegno la posizione del bagno al giocatore
                giocatore[partita->giocatore_attivo].posizione=10;

            }

            break;

        }

    }//fine verifica posizione

    //se il contatore sfighe e minore del totale delle sfighe
    if(*cont_sfighe<(TOT_SFIG-1)){

        //incremento il contatore
        (*cont_sfighe)++;
    }else{//se non e' minore

        //azzero il contatore
        (*cont_sfighe)=0;
    }

    return giocatore;
}

d_giocatore * compra_aula(d_partita *partita,d_giocatore *giocatore,d_aula *posi){

    char scelta;
    do{// inizio ciclo menu

            //chiedo all'utente se vuole comprare l'aula

            printf("\n Vuoi acquistare questo terreno? \nPremi [s] per acquistare,altrimenti premi [n] \n");
            printf("\n Se non aquisti questo terreno dovrai pagare il terreno al banco!\n");

            scanf("%c",&scelta);

            while(getchar()!='\n');//svuoto il buffer

            if(scelta!='n'&&scelta!='s'){

                        printf("\nScelta non consentita \n\n");

            }


    }while(scelta!='n'&&scelta!='s');

    //sela scelta e' s
    if(scelta=='s'){//compra l'aula

        //assegno l'aula al giocatore
        posi->proprietario=partita->giocatore_attivo;

        //incremento il numero di aule del giocatore
        giocatore[partita->giocatore_attivo].numero_aule++;

        //sottraggo il costo dell'aula dal budjet giocatore
        giocatore[partita->giocatore_attivo].soldi-=posi->costo;

        printf("\nHai comprato l'aula!\n");

    }else{//se la scelta e' n

        //non compra l'aula e paga il pedaggio
        giocatore=paga_pedaggio(partita,giocatore,posi);

    }

    return giocatore;
}

d_giocatore * acquista_tenda_scrivania(d_partita *partita,d_giocatore *giocatore,d_aula *posi){


    //se nel'aula non c'e tenda
    if((posi->flag_scrivania==false)&&(posi->flag_tenda==false)){

        //compra la scrivania
        giocatore=acquista_scrivania(partita,giocatore,posi);

    }else{if((posi->flag_scrivania==true)&&(posi->flag_tenda==false)){//se nell'aula c'e' una scrivania

            //compra la tenda
            giocatore=acquista_tenda(partita,giocatore,posi);

        }else{//se c'e' una tenda

            printf("\nHai una tenda in questo terreno\n");
        }
    }

    return giocatore;
}

d_giocatore *acquista_scrivania(d_partita *partita,d_giocatore *giocatore,d_aula *posi){

    char scelta;

    do{// inizio ciclo menu

            printf("\n Vuoi acquistare una scrivania in questo terreno? \nPremi [s] per acquistare,altrimenti premi [n] \n");
            scanf("%c",&scelta);

            while(getchar()!='\n');//svuoto il buffer

            if(scelta!='n'&&scelta!='s'){

                printf("\nScelta non consentita \n\n");

            }


    }while(scelta!='n'&&scelta!='s');

    if(scelta=='s'){//se la scelta e'uguale a s compro la scrivania

        //assegno true al flag scrivania

        posi->flag_scrivania=true;

        giocatore[partita->giocatore_attivo].soldi-=PREZZO_SCRIVANIA*MOLTIPLICATORE_PEDAGGIO;

        printf("\nHai comprato la scrivania!!!\n");

    }else{

        printf("\nNon hai comprato la scrivania!!!\n");

    }

    return giocatore;
}

d_giocatore *acquista_tenda(d_partita *partita,d_giocatore *giocatore,d_aula *posi){

    char scelta;

    do{// inizio ciclo menu

            printf("\n Vuoi acquistare una tenda in questo terreno? \nPremi [s] per acquistare,altrimenti premi [n] \n");
            scanf("%c",&scelta);

            while(getchar()!='\n');//svuoto il buffer

            if(scelta!='n'&&scelta!='s'){

                printf("\nScelta non consentita \n\n");

            }


    }while(scelta!='n'&&scelta!='s');

    if(scelta=='s'){//se la scelta e'uguale a s compro la scrivania

        //assegno true al flag scrivania

        posi->flag_scrivania=false;

        posi->flag_tenda=true;

        giocatore[partita->giocatore_attivo].soldi-=PREZZO_TENDA*MOLTIPLICATORE_PEDAGGIO;

        printf("\nHai comprato la tenda!!!\n");

    }else{

        printf("\nNon hai comprato la tenda!!!\n");

    }

    return giocatore;
}

d_giocatore* paga_pedaggio(d_partita* partita,d_giocatore *giocatore,d_aula* posi){

    //se il terreno non appartiene al giocatore attivo e il proprietario non e' in bagno
    if((partita->giocatore_attivo!=posi->proprietario)&&(giocatore[posi->proprietario].pulizia_bagno==0)){

        //se non c'e'scrivania ne tenda
        if((posi->flag_scrivania==false)&&(posi->flag_tenda==false)){

            //paga pedaggio aula
            giocatore=pedaggio_aula(partita,giocatore,posi);

        }else{
                //se 'c'e' una scrivania
                if(posi->flag_scrivania){

                    giocatore=pedaggio_scrivania(partita,giocatore,posi);

                }else{
                    //se c'e' una tenda
                    giocatore=pedaggio_tenda(partita,giocatore,posi);

                }

        }

    }else{if(partita->giocatore_attivo!=posi->proprietario&&giocatore[posi->proprietario].pulizia_bagno!=0){

                printf("\nL'aula in cui sei finito non ti appartiene,ma questa volta la fortuna e' dalla tua parte\n"
                    "il proprietatio in questo momento si trova in bagno e non paghi il pedaggio!!!!\n");

        }
    }

    return giocatore;
}

d_giocatore* pedaggio_aula(d_partita *partita,d_giocatore *giocatore,d_aula* posi){


    if(posi->proprietario!=-1){

        printf("\nIl terreno appartiene a %s,"
               "devi pagare %d euro di pedaggio\n",giocatore[posi->proprietario].nome,posi->prezzo_passaggio*MOLTIPLICATORE_PEDAGGIO);

        giocatore[posi->proprietario].soldi+=(posi->prezzo_passaggio*MOLTIPLICATORE_PEDAGGIO);

    }else{

        printf("\nIl terreno appartiene alla banca',devi pagare %d euro di pedaggio\n",posi->prezzo_passaggio*MOLTIPLICATORE_PEDAGGIO);

    }

    giocatore[partita->giocatore_attivo].soldi-=(posi->prezzo_passaggio*MOLTIPLICATORE_PEDAGGIO);

    return giocatore;

}

d_giocatore* pedaggio_scrivania(d_partita *partita,d_giocatore *giocatore,d_aula* posi){

if(posi->proprietario!=-1){

        printf("\nIl terreno appartiene a %s,"
               "devi pagare %d euro di pedaggio scrivania\n",giocatore[posi->proprietario].nome,posi->prezzo_passaggio_scrivania*MOLTIPLICATORE_PEDAGGIO);

        //incremento il pedaggio dal budget
        giocatore[posi->proprietario].soldi+=(posi->prezzo_passaggio_scrivania*MOLTIPLICATORE_PEDAGGIO);

    }else{

        printf("\nIl terreno appartiene alla banca',devi pagare %d euro di pedaggio scrivania\n",posi->prezzo_passaggio_scrivania*MOLTIPLICATORE_PEDAGGIO);

    }
    //decremento il pedaggio dal budget
    giocatore[partita->giocatore_attivo].soldi-=(posi->prezzo_passaggio_scrivania*MOLTIPLICATORE_PEDAGGIO);

    return giocatore;

}



d_giocatore* pedaggio_tenda(d_partita *partita,d_giocatore *giocatore,d_aula* posi){

    if(posi->proprietario!=-1){

        printf("\nIl terreno appartiene a %s,"
               "devi pagare %d euro di pedaggio tenda\n",giocatore[posi->proprietario].nome,posi->prezzo_passaggio_tenda*MOLTIPLICATORE_PEDAGGIO);

        //incremento il pedaggio dal budget
        giocatore[posi->proprietario].soldi+=(posi->prezzo_passaggio_tenda*MOLTIPLICATORE_PEDAGGIO);

    }else{

        printf("\nIl terreno appartiene alla banca',devi pagare %d euro di pedaggio tenda\n",posi->prezzo_passaggio_tenda*MOLTIPLICATORE_PEDAGGIO);

    }

    //decremento il pedaggio dal budget
    giocatore[partita->giocatore_attivo].soldi-=(posi->prezzo_passaggio_tenda*MOLTIPLICATORE_PEDAGGIO);

    return giocatore;

}

d_giocatore * paga_tassa(d_partita *partita,d_giocatore *giocatore,d_aula* posi){

    printf("\nDevi pagare %d euro di tassa!!!\n",posi->prezzo_passaggio*MOLTIPLICATORE_PEDAGGIO);

    //decremento la tassa dal budget
    giocatore[partita->giocatore_attivo].soldi-=(posi->prezzo_passaggio*MOLTIPLICATORE_PEDAGGIO);

    return giocatore;

}

d_giocatore* sfiga_tipo_1(d_partita *partita,d_giocatore *giocatore,d_sfiga *lista,int *cont_sfighe){

    //leggo la sfiga
    printf("\n%s\n",lista[*cont_sfighe].frase);
    //sottraggo la tassa al giocatore
    giocatore[partita->giocatore_attivo].soldi-=(lista[*cont_sfighe].tassa*MOLTIPLICATORE_PEDAGGIO);

    printf("\nHai pagato %d euro\n",lista[*cont_sfighe].tassa*MOLTIPLICATORE_PEDAGGIO);

    return giocatore;

}

d_giocatore* sfiga_tipo_2(d_partita *partita,d_giocatore *giocatore,d_aula *tabellone,int n,d_sfiga *lista,int *cont_sfighe){

    int i;

    int tot=0;

    //leggo la sfiga
    printf("\n%s\n",lista[*cont_sfighe].frase);

    //faccio scorrere le aule
    for(i=0;i<n;i++){

        //se il proprietario del terreno e' uguale al giocatore attivo
        if(tabellone[i].proprietario==partita->giocatore_attivo){

            //se non c'e' ne tenda ne scrivania
            if((tabellone[i].flag_scrivania==false)&&(tabellone[i].flag_tenda==false)){

                tot+=lista[*cont_sfighe].aula;

            }else{if((tabellone[i].flag_tenda==true)&&(tabellone[i].flag_scrivania==false)){//se c'e' una tenda

                    tot+=lista[*cont_sfighe].tenda;

                }else{//se c'e' una scrivania

                    tot+=lista[*cont_sfighe].scrivania;
                }

            }

        }
    }

    printf("\nDeve pagare %d euro\n",tot*MOLTIPLICATORE_PEDAGGIO);

    giocatore[partita->giocatore_attivo].soldi-=(tot*MOLTIPLICATORE_PEDAGGIO);

    return giocatore;
}

bool assegna_bancarotta(d_partita *partita,d_giocatore *giocatore,bool *bancarotta,int n){

    if(giocatore[partita->giocatore_attivo].soldi<0){

        bancarotta[n]=false;
    }

    return bancarotta;
}
