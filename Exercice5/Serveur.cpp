#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include "protocole.h" // contient la cle et la structure d'un message
#include <fcntl.h>
#include <cstring>

int idQ;
int pid1, pid2;

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

    if ((msgrcv(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 1, 0)) == -1)
      fprintf(stderr, "(SERVEUR) Probleme lors la reception du fichier");
    else
    {
      printf("Message reçu de (type %ld) : %s vers %d\n", requete.type, requete.texte, requete.expediteur);
      destinataire = requete.expediteur;

      if ((msgsnd(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 0)) == -1)
        fprintf(stderr, "(SERVEUR) Le message n'a pas pu étre envoyer\n");
      else
        fprintf(stderr, "(SERVEUR) Le message a été envoyer avec succes\n");
    
  } 





  // Attente de connection de 2 clients
  fprintf(stderr, "(SERVEUR) Attente de connection d'un premier client...\n");
  // TO DO (etape 5)
  fprintf(stderr, "(SERVEUR) Attente de connection d'un second client...\n");
  // TO DO (etape 5)





  //while(1)
  {
    // TO DO (etapes 3, 4 et 5)
    fprintf(stderr, "(SERVEUR) Attente d'une requete...\n");

    fprintf(stderr, "(SERVEUR) Requete recue de %d : --%s--\n", requete.expediteur, requete.texte);

    fprintf(stderr, "(SERVEUR) Envoi de la reponse a %d\n", destinataire);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO DO (etape 6)
