#include <stdlib.h>
#include <string.h>
#include "data.h"

void InitTestData(Nc **lc, Nv **lv, Nr **lr)
{
    /* Add test clients */
    Nc *client1 = malloc(sizeof(Nc));
    strcpy(client1->c.nom, "Ahmed Bennani");
    strcpy(client1->c.cin, "AB123456789");
    strcpy(client1->c.telephone, "0612345678");
    client1->next = *lc;
    *lc = client1;

    Nc *client2 = malloc(sizeof(Nc));
    strcpy(client2->c.nom, "Fatima Idrissi");
    strcpy(client2->c.cin, "FI987654321");
    strcpy(client2->c.telephone, "0687654321");
    client2->next = *lc;
    *lc = client2;

    Nc *client3 = malloc(sizeof(Nc));
    strcpy(client3->c.nom, "Mohammad Alaoui");
    strcpy(client3->c.cin, "MA456789012");
    strcpy(client3->c.telephone, "0698765432");
    client3->next = *lc;
    *lc = client3;

    /* Add test vehicles */
    Nv *voiture1 = malloc(sizeof(Nv));
    strcpy(voiture1->v.marque, "Toyota");
    strcpy(voiture1->v.modele, "Corolla");
    strcpy(voiture1->v.matricule, "03AB1234");
    voiture1->v.categorie = 'A';
    voiture1->v.kilometrage = 45000;
    voiture1->v.disponible = 1;
    voiture1->next = *lv;
    *lv = voiture1;

    Nv *voiture2 = malloc(sizeof(Nv));
    strcpy(voiture2->v.marque, "Renault");
    strcpy(voiture2->v.modele, "Scenic");
    strcpy(voiture2->v.matricule, "16CD5678");
    voiture2->v.categorie = 'B';
    voiture2->v.kilometrage = 32000;
    voiture2->v.disponible = 1;
    voiture2->next = *lv;
    *lv = voiture2;

    Nv *voiture3 = malloc(sizeof(Nv));
    strcpy(voiture3->v.marque, "Mercedes");
    strcpy(voiture3->v.modele, "C-Class");
    strcpy(voiture3->v.matricule, "92EF9012");
    voiture3->v.categorie = 'C';
    voiture3->v.kilometrage = 28500;
    voiture3->v.disponible = 0;
    voiture3->next = *lv;
    *lv = voiture3;

    /* Add test reservation */
    Nr *res1 = malloc(sizeof(Nr));
    strcpy(res1->r.cin, "AB123456789");
    strcpy(res1->r.matricule, "92EF9012");
    res1->r.duree = 7;
    res1->r.km = 250;
    res1->r.prix = 125.50;
    res1->next = *lr;
    *lr = res1;
}
