#ifndef VOITURE_H
#define VOITURE_H

typedef struct
{
    char marque[50];
    char modele[50];
    char matricule[10];
    char categorie;
    int kilometrage;
    int disponible;
} voiture;

typedef struct NdVoiture
{
    voiture v;
    struct NdVoiture *next;
} Nv;

Nv *ChercherVoiture(Nv *liste, char *matricule);
void AjouterVoiture(Nv **liste);
void ModifierVoiture(Nv **liste);
void SupprimerVoiture(Nv **liste);
void ListerVoitures(Nv *liste);
void ListerVoituresDisponibles(Nv *liste);
void RechercherVoiture(Nv *liste);
void TrierVoitures(Nv **liste);

#endif