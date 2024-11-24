#include "windowclient.h"
#include "ui_windowclient.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

extern WindowClient *w;

#include "protocole.h" // contient la cle et la structure d'un message


void HandlerSIGUSR1(int sig)

extern char nomClient[40];
int idQ; // identifiant de la file de message
MESSAGE requeteC;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowClient::WindowClient(QWidget *parent) : QMainWindow(parent), ui(new Ui::WindowClient)
{
  ui->setupUi(this);
  setWindowTitle(nomClient);

  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr, "(CLIENT %s %d) Recuperation de l'id de la file de messages\n", nomClient, getpid());
  // TO DO (etape 2)

  if ((idQ = msgget(CLE, IPC_CREAT | 0666)) == -1)
    fprintf(stderr, "(CLIENT) Probleme lors de la connexion de la fille\n");
  else
    fprintf(stderr, "(CLIENT) la file à bien été trouver \n");

  // Envoi d'une requete d'identification
  // TO DO (etape 5)

  // Armement du signal SIGUSR1
  // 
  struct sigaction A;

  A.sa_handler = HandlerSIGUSR1;
  sigemptyset(&A.sa_mask);
  A.sa_flags = 0;
}

WindowClient::~WindowClient()
{
  delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setRecu(const char *Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditRecu->clear();
    return;
  }
  ui->lineEditRecu->setText(Text);
}

void WindowClient::setAEnvoyer(const char *Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditEnvoyer->clear();
    return;
  }
  ui->lineEditEnvoyer->setText(Text);
}

const char *WindowClient::getAEnvoyer()
{
  if (ui->lineEditEnvoyer->text().size())
  {
    strcpy(aEnvoyer, ui->lineEditEnvoyer->text().toStdString().c_str());
    return aEnvoyer;
  }
  return NULL;
}

const char *WindowClient::getRecu()
{
  if (ui->lineEditRecu->text().size())
  {
    strcpy(recu, ui->lineEditRecu->text().toStdString().c_str());
    return recu;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::on_pushButtonEnvoyer_clicked()
{
  fprintf(stderr, "Clic sur le bouton Envoyer\n");
  //Initialition du message
  strcpy(requeteC.texte, getAEnvoyer()); // On copie ce qui est écrit dans le programme dans ma structure
  requeteC.type = 1;
  requeteC.expediteur = getpid();
  fprintf(stderr, "(CLIENT) voici votre message %s \n", requeteC.texte);

  if ((msgsnd(idQ, &requeteC, sizeof(MESSAGE) - sizeof(long), 0)) == -1)
    fprintf(stderr, "(CLIENT) Le message n'a pas pu étre envoyer\n");
  else
    fprintf(stderr, "(CLIENT) Le message a été envoyer avec succes\n");
  // TO DO (etapes 2, 3, 4)

  if ((msgrcv(idQ, &requeteC, sizeof(MESSAGE) - sizeof(long), 1, 0)) == -1)
    fprintf(stderr, "(CLIENT) Le message n'a pas pu étre recuperer\n");
  else
  {
    fprintf(stderr, "(CLIENT) Le message a pas pu étre recuperer !!! \n");
    printf("Message reçu de (type %ld) : %s vers %d\n", requeteC.type, requeteC.texte, requeteC.expediteur);
    setRecu(requeteC.texte);

  }
}

void WindowClient::on_pushButtonQuitter_clicked()
{
  fprintf(stderr, "Clic sur le bouton Quitter\n");
  exit(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO DO (etape 4)
void HandlerSIGUSR1(int sig)
{

}