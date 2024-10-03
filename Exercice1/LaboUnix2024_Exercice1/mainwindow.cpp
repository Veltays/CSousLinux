#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

typedef struct
{
  int   id;
  char  nom[40];
  char  email[40];
} ELEMENT;

ELEMENT Elm[] = 
{ 
  {0,"",""},
  {1,"aaa","aaa@gmail.com"},
  {2,"bbb","bbb@gmail.com"},
  {3,"ccc","ccc@gmail.com"},
  {4,"ddd","ddd@gmail.com"},
  {5,"eee","eee@gmail.com"},
  {0,"",""}
};
static int CPTelem = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //***** A modifier ***********************
  setNom(Elm[0].nom);
  setEmail(Elm[0].email);
  //****************************************
}

MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::setNom(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditNom->clear();
    return;
  }
  ui->lineEditNom->setText(Text);
}

void MainWindow::setEmail(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditEmail->clear();
    return;
  }
  ui->lineEditEmail->setText(Text);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_pushButtonSuivant_clicked()
{

  if (CPTelem < 5)
  {
    CPTelem +=1;
    fprintf(stderr,"Clic sur le bouton >>>\n"); 
    printf("L'ID est %d",Elm[CPTelem].id);

    setNom(Elm[CPTelem].nom);
    setEmail(Elm[CPTelem].email);
  }

}

void MainWindow::on_pushButtonPrecedent_clicked()
{

  if (CPTelem > 1)
  {
    CPTelem -=1;
    printf("Clic sur le bouton <<<\n");
    printf("L'ID est %d",Elm[CPTelem].id);

    setNom(Elm[CPTelem].nom);
    setEmail(Elm[CPTelem].email);
  }
  
}

void MainWindow::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  exit(0);
}
