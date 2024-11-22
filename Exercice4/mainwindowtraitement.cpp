#include "mainwindowtraitement.h"
#include "ui_mainwindowtraitement.h"
#include <signal.h>
#include <unistd.h>
#include <mysql.h>


extern char groupe[30];
extern int  position;
extern MainWindowTraitement* w;

MYSQL      *connexion;
MYSQL_RES  *resultat;
MYSQL_ROW  tuple;

void handlerSIGALRM(int sig);
void HandlerSIGUSR1(int s);                                                     //déclaration de mon Handler

int  compteur = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindowTraitement::MainWindowTraitement(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowTraitement)
{
  ui->setupUi(this);
  this->move(1000,position);
  setGroupeTraite(groupe);

  // connection à la BD et récupération de tous les tuples
  fprintf(stderr,"(Traitement %d) Connection a la BD\n",getpid());
  connexion = mysql_init(NULL);
  mysql_real_connect(connexion,"localhost","Student","PassStudent1_","PourStudent",0,0,0);
  char requete[200];
  sprintf(requete,"select * from UNIX_EX3 where groupe='%s' order by nom;",groupe);
  mysql_query(connexion,requete),
  resultat = mysql_store_result(connexion);

  // armement de SIGALRM
  fprintf(stderr,"(Traitement %d) Armement du signal SIGALRM\n",getpid());
  struct sigaction A;
  A.sa_handler = handlerSIGALRM;
  A.sa_flags = 0;
  sigemptyset(&A.sa_mask);
  sigaction(SIGALRM,&A,NULL);

  // armement de SIGUSR1                                                    //Ici on a armer le signale en lui fournissant les 3 donnée de sa structure sigaction,
  struct sigaction B;                               
  B.sa_handler = HandlerSIGUSR1;                                            // Handler signifie qu'elle fonction il doit excecuté quand il reccera le flag
  B.sa_flags = 0;                                                           //ici le flag reste a 0
  sigemptyset(&B.sa_mask);                                                  //sigempty permet de mettre tout les bit a 0 
  
  if(sigaction(SIGUSR1,&B,NULL) == -1)                                    // On effectue la liaison entre SIGUSR1 et notre stucture B le NULL correspond a l'ancienne structure mais dcp est ignoré on procéde également à une vérification
  {
    perror(" Erreur de signaction");
    exit(1);
  }


  // Demande d'envoi de SIGALRM dans 1 seconde
  alarm(1); 
}

MainWindowTraitement::~MainWindowTraitement()
{
  delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowTraitement::setGroupeTraite(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupeTraite->clear();
    return;
  }
  ui->lineEditGroupeTraite->setText(Text);
}

void MainWindowTraitement::setEtudiantTraite(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditEtudiantTraite->clear();
    return;
  }
  ui->lineEditEtudiantTraite->setText(Text);
}

void MainWindowTraitement::setDejaTraites(int nb)
{
  ui->lcdNumberDejaTraites->display(nb);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void handlerSIGALRM(int sig)
{
  fprintf(stderr,"(Traitement %d) Reception du signal SIGALRM (%d)\n",getpid(),sig);
  if ((tuple = mysql_fetch_row(resultat)) == NULL) 
    exit(compteur);

  compteur++;
  w->setEtudiantTraite(tuple[1]);  // !!! HandlerSIGALRM n'est pas une méthode membre de
  w->setDejaTraites(compteur);     // !!! la classe MainWindowTraitement, d'om le w->...                     //ce sera utiliser dans notre fichier mainwindow.cpp

  alarm(1);
}

void HandlerSIGUSR1(int sig)
{
  fprintf(stderr,"Signale recu : %d \n",sig);             //on recoit le signale donc on arrete tout et on rentre dans la fonction HandlerSIGUS1
  exit(compteur);                                         //on exit le compteur pour le recuperer dans le mainwindow même si, on a annuler l'operation
}