#include "FichierUtilisateur.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int estPresent(const char *nom)
{
  UTILISATEUR temp;
  int fd, posi = 1;
  if ((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1)
    return -1;

  while (read(fd, &temp, sizeof(UTILISATEUR)) > 0){
    if (strcmp(temp.nom, nom) == 0){
        close(fd);
        cout << "return posi" << posi << endl;
        return posi;
      }
    posi++;
  }
  close(fd);
  cout << "return 0" << endl;
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////         OK
int Hash(const char *motDePasse)
{
  int i = 0, hasher = 0;

  while (motDePasse[i] != '\0')
  {
    hasher = hasher + (i+1) * motDePasse[i];
    i++;
  }
  return hasher % 97;
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char *nom, const char *motDePasse)
{
  UTILISATEUR temp;
  int fd;
  if ((fd = open(FICHIER_UTILISATEURS, O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1)
  {
    cerr << "Une erreur lors de l'ouverture du fichier est survenue lors de l'ajout du fichier" << endl;
    return;
  }
   if (nom == nullptr || motDePasse == nullptr) {
        cerr << "Le nom ou le mot de passe ne peut pas être null" << endl;
        return;  
    }

  strcpy(temp.nom, nom);
  temp.hash = Hash(motDePasse);
  write(fd,&temp,sizeof(UTILISATEUR));
  close(fd);
}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char *motDePasse)
{
  UTILISATEUR temp;
  int fd;
  if ((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1)
  {
    cerr << "Une erreur lors de l'ouverture du fichier est survenue" << endl;
    return -1;
  }

  lseek(fd, (pos-1) * sizeof(UTILISATEUR), SEEK_SET);
  read(fd, &temp, sizeof(UTILISATEUR));
  cout <<" le pseudo de ce que tu recherche c " << temp.nom ;
  close(fd);
  if (temp.hash == Hash(motDePasse))
    return 1;
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  int fd,cpt = 0;
  if ((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1)
  {
    cerr << "Une erreur lors de l'ouverture du fichier est survenue" << endl;
    return -1;
  }

  while(cpt < 50 && read(fd,&vecteur[cpt],sizeof(UTILISATEUR)) > 0)
    cpt++;
  close(fd);
  return cpt;

}
