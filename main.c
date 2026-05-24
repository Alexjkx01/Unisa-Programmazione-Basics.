#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Struttura per rappresentare uno studente
typedef struct{
  char nome[20];
  char cognome[20];
  int matricola;
  float media_voto;
} Studente;
float calcolaMediaClasse( Studente* classe, int n)
{
float somma = 0.0f;
for(int i=0; i<n; i++)
  {
  somma += classe[i].media_voto;
  }
return somma/n;
}
int cercaStudente(Studente* classe, int n, const char* cognome) 
{
  for (int i=0; i<n; i++)
  {
  if (strcmp(classe[i].cognome, cognome) == 0)
    { 
      return i;
    }
  }
return -1;
}
int leggiDaFile(const char* nomefile, Studente** classeOut) {
  FILE* f = fopen(nomefile, "r");
  if (f == NULL)
  {
  printf ("Errore di apertura '%s'. \n", nomefile);
  return -1;
  }
int n=0;
char linea[128];
while (fgets(linea, sizeof(linea), f)) {
  if (strncmp(linea, "Studente: ", 9) == 0) n++;
}
*classeOut = (Studente*)malloc(n*sizeof(Studente));
rewind;
int idx = 0;
while (fgets(linea, sizeof(linea), f) && idx<n){
sscanf(linea, "Studente: %19s %19s | Matricola %d | Media: %f",  (*classeOut)[idx].cognome, (*classeOut)[idx].nome,
               &(*classeOut)[idx].matricola, &(*classeOut)[idx].media_voto);
        idx++;
    }
    fclose(f);
    return n;
}
int main (){
  int n;
  FILE *file_output;
printf("=== UniSa - Gestione Record Studenti ===\n");
printf("Inserisci il numero di studenti da registrare");
  if(scanf("%d", &n) !=1 || n <= 0)
  {
  printf("Errore: Input non valido.\n");
  return 1;
  }
// Allocazione dinamica della memoria con il controllo
Studente* classe = (Studente*)malloc(n * sizeof(Studente));
  if ( classe == NULL)
{
printf("Errore critico: Allocazione memoria fallita.\n");
return 1;
}
// Input dei dati da tastiera
for (int i=0; i<n; i++)
{
  printf("\n--Studente %d---\n", i+1);
  printf("Cognome: ");
  scanf("%19s", classe[i].cognome);
  printf("Nome: ");
  scanf("%19s", classe[i].nome);
  printf("Matricola: ");
  scanf("%d", &classe[i].matricola);
  printf("Media voto: ");
  scanf("%f", &classe[i].media_voto);
}
//Apertura del file per salvare input
file_output = fopen("report_studenti.txt", "w");
  if (file_output == NULL)
{ 
  printf("impossibile creare il file di output.\n");
  free(classe);
  return 1;
}
//Scrittura dei dati su File e su Terminale
fprintf(file_output, "=== REPORT ACCADEMICO ===\n");
printf("\n=== Salvataggio dati... ===\n");
  for ( int i = 0; i<n; i++) 
  {
  //Scrittutra nel file txt
  fprintf(file_output, "Studente: %s %s | Matricola: %d | Media: %.2f\n", classe[i].cognome, classe[i].nome, classe[i].matricola, classe[i].media_voto);
  }
// Liberiamo memoria
fclose(file_output);
free(classe);
printf("\n Dati salvati con successo in 'report_studenti.txt'.\n");
  return 0;
  }
