#ifndef MONOPOLY_H_INCLUDED
#define MONOPOLY_H_INCLUDED

#include "Studente.h"

/**Dichiarazione funzioni**/

void Partita(d_partita *,d_giocatore *,d_aula *,int ,d_sfiga *,int);

//elimina il giocatore dalla partita
d_giocatore* rimuovi_giocatore(d_partita *,d_giocatore *,d_aula *,int,int);

//verifica che il giocatore attivo non sia in bagno
d_giocatore* controllo_bagno(d_partita *,d_giocatore *,bool *);

//salva i dati della partita in un file
void salva_partita(d_partita *,d_giocatore *,d_aula *,int ,int *);

//a seconda del valore dei dadi sposta il giocatore
d_giocatore* muovi_giocatore(d_partita *,d_giocatore *,d_aula *,int ,d_sfiga *,int);

//aggiunge 20 € al budget se il giocatore attivo passa dal via
d_giocatore* controllo_via(d_partita *,d_giocatore *,int,int);

//verifica in che tipo di casella e' finito il giocatore attivo
d_giocatore* verifica_tipo_posizione_aula(d_partita *,d_giocatore *,d_aula *,int,d_sfiga *,int,int,d_aula *,int*);

//permette al giocatore attivo di comprare l'aula(modalita' bonus)
d_giocatore * compra_aula(d_partita *,d_giocatore *,d_aula *);

//verifica se nella casella e' presente una scivania o un aula
d_giocatore * acquista_tenda_scrivania(d_partita *,d_giocatore *,d_aula *);

//permette al giocatore attivo di comprare la scrivania
d_giocatore *acquista_scrivania(d_partita *,d_giocatore *,d_aula *);

//permette al giocatore attivo di comprare una tenda
d_giocatore *acquista_tenda(d_partita *,d_giocatore *,d_aula *);

//verifica il tipo di pedaggio
d_giocatore *paga_pedaggio(d_partita*,d_giocatore *,d_aula *);

//sottrare al giocatore attivo il pedaggio aula
d_giocatore *pedaggio_aula(d_partita*,d_giocatore *,d_aula *);

//sottrare al giocatore attivo il pedaggio scrivania
d_giocatore *pedaggio_scrivania(d_partita*,d_giocatore *,d_aula *);

//sottrae al giocatore attivo il pedaggio tenda
d_giocatore *pedaggio_tenda(d_partita*,d_giocatore *,d_aula *);

//sottrae al giocatore attivo la tassa
d_giocatore *paga_tassa(d_partita*,d_giocatore *,d_aula *);

d_giocatore* sfiga_tipo_1(d_partita *,d_giocatore *,d_sfiga *,int *);

d_giocatore* sfiga_tipo_2(d_partita *,d_giocatore *,d_aula *,int ,d_sfiga *,int *);

#endif // MONOPOLY_H_INCLUDED
