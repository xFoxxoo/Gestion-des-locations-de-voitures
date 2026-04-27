#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voiture.h"

Nv *ChercherVoiture(Nv *liste, char *m)
{
    while (liste)
    {
        if (!strcmp(liste->v.matricule, m))
            return liste;
        liste = liste->next;
    }
    return NULL;
}

void AjouterVoiture(Nv **liste)
{
    Nv *v = malloc(sizeof(Nv));

    scanf("%49s", v->v.marque);
    scanf("%49s", v->v.modele);

    do
    {
        scanf("%9s", v->v.matricule);
    } while (ChercherVoiture(*liste, v->v.matricule));

    scanf(" %c", &v->v.categorie);
    scanf("%d", &v->v.kilometrage);

    v->v.disponible = 1;

    v->next = *liste;
    *liste = v;
}

void ModifierVoiture(Nv **liste)
{
    char m[10];
    scanf("%9s", m);

    Nv *v = ChercherVoiture(*liste, m);

    if (v)
    {
        scanf("%49s", v->v.marque);
        scanf("%49s", v->v.modele);
        scanf(" %c", &v->v.categorie);
        scanf("%d", &v->v.kilometrage);
    }
}

void SupprimerVoiture(Nv **liste)
{
    char m[10];
    scanf("%9s", m);

    Nv *cur = *liste, *prev = NULL;

    while (cur)
    {
        if (!strcmp(cur->v.matricule, m))
        {
            if (prev) prev->next = cur->next;
            else *liste = cur->next;

            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void ListerVoitures(Nv *liste)
{
    while (liste)
    {
        printf("%s | %s | %s | %d | %s\n",
               liste->v.marque,
               liste->v.modele,
               liste->v.matricule,
               liste->v.kilometrage,
               liste->v.disponible ? "Disponible" : "Louee");
        liste = liste->next;
    }
}

void ListerVoituresDisponibles(Nv *liste)
{
    while (liste)
    {
        if (liste->v.disponible)
            printf("%s | %s | %d\n",
                   liste->v.marque,
                   liste->v.matricule,
                   liste->v.kilometrage);
        liste = liste->next;
    }
}

void RechercherVoiture(Nv *liste)
{
    char m[10];
    scanf("%9s", m);

    Nv *v = ChercherVoiture(liste, m);

    if (v)
        printf("%s | %s\n", v->v.marque, v->v.matricule);
}

void TrierVoitures(Nv **liste)
{
    Nv *i, *j;
    voiture tmp;

    for (i = *liste; i; i = i->next)
    {
        for (j = i->next; j; j = j->next)
        {
            if (i->v.kilometrage > j->v.kilometrage)
            {
                tmp = i->v;
                i->v = j->v;
                j->v = tmp;
            }
        }
    }
}