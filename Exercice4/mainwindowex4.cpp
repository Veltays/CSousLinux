#include "mainwindowex4.h"
#include "ui_mainwindowex4.h"

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

using namespace std;


extern MainWindowEx4 *w;

int idFils1, idFils2, idFils3;
// TO DO : HandlerSIGCHLD
void HandlerSIGCHLD(int sig);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindowEx4::MainWindowEx4(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindowEx4)
{
  ui->setupUi(this);
  ui->pushButtonAnnulerTous->setVisible(false);

  struct sigaction Armer;

  // Configuration de la structure sigaction
  Armer.sa_handler = HandlerSIGCHLD;  // Pointeur vers votre handler
  sigemptyset(&Armer.sa_mask);        // Aucun masque
  Armer.sa_flags = 0;                 // Pas d'options spécifiques

  // Armement du signal SIGCHLD
  if (sigaction(SIGCHLD, &Armer, NULL) == -1) {
      perror("Erreur lors de sigaction");
      exit(EXIT_FAILURE);
}

}

MainWindowEx4::~MainWindowEx4()
{
  delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx4::setGroupe1(const char *Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx4::setGroupe2(const char *Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx4::setGroupe3(const char *Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx4::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text, "%d", nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx4::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text, "%d", nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx4::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text, "%d", nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx4::traitement1Selectionne()
{
  return ui->checkBoxTraitement1->isChecked();
}

bool MainWindowEx4::traitement2Selectionne()
{
  return ui->checkBoxTraitement2->isChecked();
}

bool MainWindowEx4::traitement3Selectionne()
{
  return ui->checkBoxTraitement3->isChecked();
}

const char *MainWindowEx4::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  {
    strcpy(groupe1, ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char *MainWindowEx4::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  {
    strcpy(groupe2, ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char *MainWindowEx4::getGroupe3()
{
  if (ui->lineEditGroupe3->text().size())
  {
    strcpy(groupe3, ui->lineEditGroupe3->text().toStdString().c_str());
    return groupe3;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


void MainWindowEx4::on_pushButtonDemarrerTraitements_clicked()
{
  int fTrace = open("Trace.log", O_WRONLY | O_CREAT | O_APPEND, 0777);   // on creer un fichier de sortie nommer Trace.log
  if (fTrace == -1)
  {
    perror("Erreur lors de l'ouverture du fichier");                  // si erreur
    exit(0);
  } 
  if (dup2(fTrace, STDERR_FILENO) == -1)                               //ici on lit la redictions stdeer dans le Ftrace
  {
    perror("Erreur lors de la redirection de stderr");                 // si erreur
    exit(0);
  }


  fprintf(stderr, "Clic sur le bouton Demarrer Traitements\n");

  if (traitement1Selectionne())
  {
    cout << "Traitement  1 select" << endl;
    idFils1 = fork();
    if (idFils1 == 0)
    {
      cout << "le fils 1 a bien été crée voici son pid" << getpid() << endl <<
      "voici celui du père " << getppid() << endl;
      execl("./Traitement","Traitement", getGroupe1(), "200", NULL);
      perror("Erreur de execl");
      exit(1);
    }
    
  }
  if (traitement2Selectionne())
  {
    cout << "Traitement  2 select" << endl;
    idFils2 = fork();
    if (idFils2 == 0)
    {
      cout << "le fils 2 a bien été crée voici son pid" << getpid() << endl <<
      "voici celui du père " << getppid() << endl;
      execl("./Traitement","Traitement", getGroupe2(), "450", NULL);
      perror("Erreur de execl");
      exit(1);
    }
  }

  if (traitement3Selectionne())
  {
    cout << "Traitement  3 select" << endl;
    idFils3 = fork();
    if (idFils3 == 0)
    {
      cout << "le fils 3 a bien été crée voici son pid" << getpid() << endl <<
      "voici celui du père " << getppid() << endl;
      execl("./Traitement","Traitement", getGroupe3(), "700", NULL);
      perror("Erreur de execl");
      exit(1);
    }
  }
}

void MainWindowEx4::on_pushButtonVider_clicked()
{
  fprintf(stderr, "Clic sur le bouton Vider\n");
  fprintf(stderr, "Clic sur le bouton Vider\n");
  ui->lineEditResultat1->clear(); //Fonction utilisé pour clear le champ Resultat1,2,3
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();
  setGroupe1("");
  setGroupe2("");
  setGroupe3("");
}

void MainWindowEx4::on_pushButtonQuitter_clicked()
{
  fprintf(stderr, "Clic sur le bouton Quitter\n");
  exit(0);
}

void MainWindowEx4::on_pushButtonAnnuler1_clicked()
{
  fprintf(stderr, "Clic sur le bouton Annuler1\n");
  kill(idFils1,SIGUSR1);
}

void MainWindowEx4::on_pushButtonAnnuler2_clicked()
{
  fprintf(stderr, "Clic sur le bouton Annuler2\n");
  kill(idFils2,SIGUSR1);
}

void MainWindowEx4::on_pushButtonAnnuler3_clicked()
{
  fprintf(stderr, "Clic sur le bouton Annuler3\n");
  kill(idFils3, SIGUSR1);
}

void MainWindowEx4::on_pushButtonAnnulerTous_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler tout\n");
  // NOTHING TO DO --> bouton supprimé
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Handlers de signaux //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TO DO : HandlerSIGCHLD
void HandlerSIGCHLD(int sig){
  int status;
  int x = wait(&status);
  cout <<"fils mort signal recu " << sig << endl;

  
    if(x == idFils1)
      w->setResultat1(WEXITSTATUS(status));
  
    if(x == idFils2)
      w->setResultat2(WEXITSTATUS(status));
    
    if(x == idFils3)
      w->setResultat3(WEXITSTATUS(status));

}