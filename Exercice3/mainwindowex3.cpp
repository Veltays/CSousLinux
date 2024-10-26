#include "mainwindowex3.h"
#include "ui_mainwindowex3.h"

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
using namespace std;

MainWindowEx3::MainWindowEx3(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindowEx3)
{
  ui->setupUi(this);
}

MainWindowEx3::~MainWindowEx3()
{
  delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::setGroupe1(const char *Text)
{
  fprintf(stderr, "---%s---\n", Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx3::setGroupe2(const char *Text)
{
  fprintf(stderr, "---%s---\n", Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx3::setGroupe3(const char *Text)
{
  fprintf(stderr, "---%s---\n", Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx3::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text, "%d", nb);
  fprintf(stderr, "---%s---\n", Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx3::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text, "%d", nb);
  fprintf(stderr, "---%s---\n", Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx3::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text, "%d", nb);
  fprintf(stderr, "---%s---\n", Text);
  if (strlen(Text) == 0)
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx3::recherche1Selectionnee()
{
  return ui->checkBoxRecherche1->isChecked();
}

bool MainWindowEx3::recherche2Selectionnee()
{
  return ui->checkBoxRecherche2->isChecked();
}

bool MainWindowEx3::recherche3Selectionnee()
{
  return ui->checkBoxRecherche3->isChecked();
}

const char *MainWindowEx3::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  {
    strcpy(groupe1, ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char *MainWindowEx3::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  {
    strcpy(groupe2, ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char *MainWindowEx3::getGroupe3()
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
void MainWindowEx3::on_pushButtonLancerRecherche_clicked()
{
  fprintf(stderr, "Clic sur le bouton Lancer Recherche\n");
  int idFils1 =, idFils2, idFils3;
  int status;
  int x;
  int cpt = 0;

  if (recherche1Selectionnee())     //SI le bouton 1 est selectionner
  {
    idFils1 = fork();               //creation du clone appeler IdFils1
    if (idFils1 == 0)
    {
      cout << "Voici le PID l'enfant 1 - " << getpid() << endl
           << "Voici la PPID du père - " << getppid() << endl; 
      execl("./Lecture", "Lecture", getGroupe1(), NULL); //changement de son type de processus, il finira sa tache et mourera ici
                                                         //"./Lecture" correspond au fichier a lancer, tandis que "Lecture" et "g2202" sont les argument a lancer dans le bash pour recuperer lancer la recherche, "NULL" signifie la fin des arg
    } 
    cpt++;  //on incrémente le compteur de processus, afin de savoir combien de wait attendre
  }


  //Le pere lui continuera sa route ici verifiant ainsi tout les processus 1 par 1
  if (recherche2Selectionnee())
  {
    idFils2 = fork();
    if (idFils2 == 0)
    {
      cout << "Voici le PID l'enfant 2 - " << getpid() << endl
           << "Voici la PPID du père - " << getppid() << endl;
      execl("./Lecture", "Lecture", getGroupe2(), NULL);    }
    cpt++;
  }



  if (recherche3Selectionnee())
  {
    idFils3 = fork();
    if (idFils3 == 0)
    {
      cout << "Voici le PID l'enfant 3 - " << getpid() << endl
           << "Voici la PPID du père - " << getppid() << endl;
      execl("./Lecture", "Lecture", getGroupe3(), NULL);  }
    cpt++;
  }

  for (int i = 0; i < cpt; i++)   //on va boucler xfois le nombre de processus crée 
  {
    x = wait(&status);            //on attend de recevoir le message de fin du fils
    if (WIFEXITED(status)) //permet de tester si on a bien recu une valeur a l'exit
    {
      if (x == idFils1)           //on verifie le qu'elle est mort
      {
        setResultat1(WEXITSTATUS(status));
      }
      if (x == idFils2)
      {
        setResultat2(WEXITSTATUS(status));
      }
      if (x == idFils3)
      {
        setResultat3(WEXITSTATUS(status));
      }
    }
  }
}


void MainWindowEx3::on_pushButtonVider_clicked()
{
  fprintf(stderr, "Clic sur le bouton Vider\n");
  ui->lineEditResultat1->clear();         //Fonction utilisé pour clear le champ Resultat1,2,3
  ui->lineEditResultat2->clear();  
  ui->lineEditResultat3->clear();
  setGroupe1("");
  setGroupe2("");
  setGroupe3("");

}

void MainWindowEx3::on_pushButtonQuitter_clicked()
{
  fprintf(stderr, "Clic sur le bouton Quitter\n");
  exit(0);
}
