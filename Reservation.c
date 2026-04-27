#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"

void EffectuerReservation(Nr **lr, Nv *lv, Nc *lc)
{
    char cin[10], mat[10];

    scanf("%9s", cin);

    Nc *c = ChercherClient(lc, cin);
    if (!c) return;

    scanf("%9s", mat);

    Nv *v = ChercherVoiture(lv, mat);
    if (!v || !v->v.disponible) return;

    Nr *r = malloc(sizeof(Nr));

    strcpy(r->r.cin, cin);
    strcpy(r->r.matricule, mat);

    scanf("%d", &r->r.duree);

    r->r.km = 0;
    r->r.prix = 0;

    v->v.disponible = 0;

    r->next = *lr;
    *lr = r;
}

void AnnulerReservation(Nr **lr, Nv *lv)
{
    char mat[10];
    scanf("%9s", mat);

    Nr *cur = *lr, *prev = NULL;

    while (cur)
    {
        if (!strcmp(cur->r.matricule, mat))
        {
            Nv *v = ChercherVoiture(lv, mat);
            if (v) v->v.disponible = 1;

            if (prev) prev->next = cur->next;
            else *lr = cur->next;

            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void ListerReservations(Nr *lr)
{
    while (lr)
    {
        printf("%s | %s | %d\n",
               lr->r.cin,
               lr->r.matricule,
               lr->r.duree);
        lr = lr->next;
    }
}

void HistoriqueClient(Nr *lr)
{
    char cin[10];
    scanf("%9s", cin);

    while (lr)
    {
        if (!strcmp(lr->r.cin, cin))
            printf("%s | KM:%d | Prix:%.2f\n",
                   lr->r.matricule,
                   lr->r.km,
                   lr->r.prix);
        lr = lr->next;
    }
}

void HistoriqueVoiture(Nr *lr)
{
    char mat[10];
    scanf("%9s", mat);

    while (lr)
    {
        if (!strcmp(lr->r.matricule, mat))
            printf("Client:%s | KM:%d | Prix:%.2f\n",
                   lr->r.cin,
                   lr->r.km,
                   lr->r.prix);
        lr = lr->next;
    }
}

void Facturation(Nr *lr, Nv *lv)
{
    char mat[10];
    int km;

    scanf("%9s", mat);
    scanf("%d", &km);

    Nv *v = ChercherVoiture(lv, mat);
    if (!v) return;

    float prix = km * 0.5;

    while (lr)
    {
        if (!strcmp(lr->r.matricule, mat) && lr->r.km == 0)
        {
            lr->r.km = km;
            lr->r.prix = prix;
            break;
        }
        lr = lr->next;
    }

    v->v.kilometrage += km;
    v->v.disponible = 1;

    printf("Prix: %.2f DH\n", prix);
}