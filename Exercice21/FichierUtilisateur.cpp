#include "FichierUtilisateur.h"

using namespace std;

int estPresent(const char *nom)
{
  UTILISATEUR tempo;
  int fd, posi = 1;
  if ((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1)
    return -1;

  while (read(fd, &tempo, sizeof(UTILISATEUR)) > 0)
  {
    cout << tempo.nom << endl;
    if (strcmp(tempo.nom, nom) == 0)
      {
        close(fd);
        return posi;
      }
    posi++;
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int Hash(const char *motDePasse)
{
  cout << motDePasse << "-----------------------------FIN" << endl;
  int i = 0, hasher = 0;

  while (motDePasse[i] != '\0')
  {
    cout << motDePasse[i] << endl;
    hasher = hasher + (i+1) * motDePasse[i];
    i++;
  }
  hasher = hasher % 97;
  cout << "hash =" << hasher;

  return hasher;
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char *nom, const char *motDePasse)
{
  UTILISATEUR temp;
  int fd;
  if ((fd = open(FICHIER_UTILISATEURS, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
  {
    cerr << "Une erreur lors de l'ouverture du fichier est survenue" << endl;
    exit(0);
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
  if ((fd = open(FICHIER_UTILISATEURS, O_RDONLY, 0777)) == -1)
  {
    cerr << "Une erreur lors de l'ouverture du fichier est survenue" << endl;
    return -1;
  }

  lseek(fd, (pos-1) * sizeof(UTILISATEUR), SEEK_SET);
  read(fd, &temp, sizeof(UTILISATEUR));
  close(fd);

  cout <<" le pseudo de ce que tu recherche c " << temp.nom ;
  if (temp.hash == Hash(motDePasse))
    return 1;
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  int fd,cpt = 0;
  if ((fd = open(FICHIER_UTILISATEURS, O_RDONLY, 0444)) == -1)
  {
    cerr << "Une erreur lors de l'ouverture du fichier est survenue" << endl;
    return -1;
  }

  while(cpt < 50 && read(fd,&vecteur[cpt],sizeof(UTILISATEUR)) > 0)
    cpt++;
  close(fd);
  return cpt;

}
