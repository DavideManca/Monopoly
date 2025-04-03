#ifndef STUDENTE_H_INCLUDED
#define STUDENTE_H_INCLUDED
/**Librerie**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>
/**dichiarazione costanti**/
#define MIN 1//risultato min dado
#define MAX 6//risultato max dado
#define NOME 23 //dimensione stringa nome giocatore e casella
#define N_TAB 40//dimensione tabellone
#define FRASE 140//dimensione frase sfiga
#define TOT_SFIG 39//numero totale di sfighe
#define VIA 20
#define PREZZO_TENDA 100//costo tenda
#define PREZZO_SCRIVANIA 50//costo scrivania
#define MOLTIPLICATORE_PEDAGGIO 1


/**Dichiarazione enumerazione**/
typedef enum{aula,tassa,sfiga,altro_tipo}casella;
typedef enum{d1=-1,d2,d3,d4,d5,d6,d7,d8,d9}segnaposto;
typedef enum{tipo1=1,tipo2=2,tipo3=3,tipo4=4}tiposfiga;

/**Dichiarazione Strutture**/

//Struttura gestione dettagli Partita

typedef struct DettaglioPartita{

int n_giocatori;
int n_turni;
int giocatore_attivo;

} d_partita;



// Struttura gestione Dettagli Aula

typedef struct DettaglioAula{

int costo;
int prezzo_passaggio;
int prezzo_passaggio_scrivania;
int prezzo_passaggio_tenda;
char nome[NOME+1];
casella tipo;//dichiarazione variabile di tipo casella(enumerazione)
bool flag_scrivania;
bool flag_tenda;
int proprietario;

} d_aula;



//Struttura gestione Dettagli Giocatore

typedef struct DettaglioGiocatore{

char nome[NOME+1];
segnaposto id; //dichiarazione variabile di tipo segnaposto (enumerazione)
int soldi;
int pulizia_bagno;
int numero_aule;
int posizione;

}d_giocatore;

//stuttura gestione sfighe

typedef struct DettaglioSfiga{

    char frase[FRASE+1];
    tiposfiga tipo;
    int posizione;
    int tassa;
    int aula;
    int scrivania;
    int tenda;


}d_sfiga;





/**Dichiarazione Funzioni**/
//inizia una nuva partita
void Nuova_Partita(d_partita*,d_giocatore*,d_aula*,int,d_sfiga*,int);
//chiede il numero di giocatori
d_partita* inizializza_n_giocatori(d_partita*);
//distribuisce i terreni al giocaore(Modalità classica)
void distribuisci_terreni(d_aula *,int ,d_partita *);
//permette di inserire i dati del giocatore
d_giocatore *inizializza_dati_giocatori(d_partita *,d_giocatore *,d_aula *,int);
//legge le sfighe dal file e le scrive e le allocca dinamicamente
d_sfiga* inizializza_sfighe(d_sfiga*);
//permette di misciare le sfighe
d_sfiga* mischia_sfighe(d_sfiga*);
//ogni qual volgta sia il turno del giocatore zero stampa il budget
void stampa_budget_giocatore(d_giocatore*,d_partita*);

//carica la partita salvata
void Carica_Partita(d_giocatore *,d_aula *,int ,d_partita ,d_sfiga *,int);

#endif // STUDENTE_H_INCLUDED
