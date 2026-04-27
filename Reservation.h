#ifndef RESERVATION_H
#define RESERVATION_H

#include "client.h"
#include "voiture.h"

typedef struct
{
    char cin[10];
    char matricule[10];
    int duree;
    int km;
    float prix;
} reservation;

typedef struct NdReservation
{
    reservation r;
    struct NdReservation *next;
} Nr;

void EffectuerReservation(Nr **lr, Nv *lv, Nc *lc);
void AnnulerReservation(Nr **lr, Nv *lv);
void ListerReservations(Nr *lr);

// HISTORIQUES
void HistoriqueClient(Nr *lr);
void HistoriqueVoiture(Nr *lr);

void Facturation(Nr *lr, Nv *lv);

#endif