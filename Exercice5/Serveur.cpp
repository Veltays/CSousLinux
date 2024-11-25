#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include "protocole.h" // contient la cle et la structure d'un message
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int idQ;
int pid1, pid2;

char *concatServeur(char *);

int main()
{
  MESSAGE requete;
  pid_t destinataire;

  // Armement du signal SIGINT
  // TO DO (etape 6)

  // Creation de la file de message
  fprintf(stderr, "(SERVEUR) Creation de la file de messages\n");
  // TO DO (etape 2)

  if ((idQ = msgget(CLE, IPC_CREAT | 0666)) == -1) //Va créer une file de msg
    fprintf(stderr, "(SERVEUR) Probleme lors de la creation de la fille \n");
  else
    fprintf(stderr, "(SERVEUR) la fille à bien été créer");

  // Attente de connection de 2 clients
  fprintf(stderr, "(SERVEUR) Attente de connection d'un premier client...\n");
  // TO DO (etape 5)
  fprintf(stderr, "(SERVEUR) Attente de connection d'un second client...\n");
  // TO DO (etape 5)

  while (1)
  {
    // TO DO (etapes 3, 4 et 5)
    fprintf(stderr, "(SERVEUR) Attente d'une requete...\n");

    if ((msgrcv(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 1, 0)) == -1)
    {
      fprintf(stderr, "(SERVEUR) Probleme lors la reception du fichier");
      exit(0);
    }
    else
    {
      printf("Message reçu (type %ld) : %s vers %d\n", requete.type, requete.texte, requete.expediteur);

      fprintf(stderr, "(SERVEUR) Envoi de la reponse a %d\n", requete.expediteur); // envoie de le réponse

      strcpy(requete.texte, concatServeur(requete.texte));
      requete.type = requete.expediteur;
      requete.expediteur = getpid();

      if ((msgsnd(idQ, &requete, sizeof(MESSAGE)-sizeof(long), 0)) == -1)
      {
        fprintf(stderr, "(SERVEUR) Le message n'a pas pu étre envoyer\n");
        exit(1);
      }
      else
      {
        fprintf(stderr, "(SERVEUR) Le message a été envoyer avec succes\n");
        kill(requete.type, SIGUSR1);
        sleep(1);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO DO (etape 6)

char *concatServeur(char *texte)
{
  char temp[80];
  strcpy(temp, "(Serveur)");
  strcat(temp, texte);
  strcpy(texte, temp);
  return texte;
}