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

  if ((idQ = msgget(CLE, IPC_CREAT | 0666)) == -1) //Va créer une file de msg
    fprintf(stderr, "(SERVEUR) Probleme lors de la creation de la fille \n");
  else
    fprintf(stderr, "(SERVEUR) la fille à bien été créer \n\n");



  // Attente de connection de 2 clients
  fprintf(stderr, "(SERVEUR) Attente de connection d'un premier client...\n");
  msgrcv(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 1, 0); //Recoit le pid du premier client
  pid1 = requete.expediteur;
  printf("PID DU 1er Client = %d ---------- \n", pid1);

  fprintf(stderr, "(SERVEUR) Attente de connection d'un second client...\n");
  msgrcv(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 1, 0); //Recoit le pid du second client
  pid2 = requete.expediteur;
  printf("PID DU 2e Client = %d ---------- \n", pid2);



  // Boucle while de renvoie de


  while (1)
  {
    fprintf(stderr, "(SERVEUR) Attente d'une requete...\n");

    if ((msgrcv(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 1, 0)) == -1)
    {
      fprintf(stderr, "(SERVEUR) Probleme lors la reception du fichier\n");
      exit(0);
    }

    printf("Message reçu (destination : %ld) : %s du processus avec le pid %d\n\n", requete.type, requete.texte, requete.expediteur);

    if(requete.expediteur == pid1)
    {
      fprintf(stderr, "(SERVEUR) Envoi de la reponse a %d\n", pid2); // envoie de le réponse

      strcpy(requete.texte, concatServeur(requete.texte));
      requete.type = pid2;
      requete.expediteur = 1;

      if ((msgsnd(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 0)) == -1)
      {
        fprintf(stderr, "(SERVEUR) Le message n'a pas pu étre envoyer\n");
        exit(1);
      }

      fprintf(stderr, "(SERVEUR) Le message a été envoyer avec succes\n");
      kill(requete.type, SIGUSR1);
    }
    
    else if(requete.expediteur == pid2)
    {
      fprintf(stderr, "(SERVEUR) Envoi de la reponse a %d\n", pid1); // envoie de le réponse

      strcpy(requete.texte, concatServeur(requete.texte));
      requete.type = pid1;
      requete.expediteur = 1;

      if ((msgsnd(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 0)) == -1)
      {
        fprintf(stderr, "(SERVEUR) Le message n'a pas pu étre envoyer\n");
        exit(1);
      }

      fprintf(stderr, "(SERVEUR) Le message a été envoyer avec succes au %d\n",requete.type);

      kill(pid1, SIGUSR1);
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