#ifndef CLIENT_H
#define CLIENT_H

typedef struct
{
    char nom[50];
    char cin[10];
    char telephone[15];
} client;

typedef struct NdClient
{
    client c;
    struct NdClient *next;
} Nc;

Nc *ChercherClient(Nc *liste, char *cin);
void AjouterClient(Nc **liste);
void ModifierClient(Nc **liste);
void SupprimerClient(Nc **liste);
void ListerClients(Nc *liste);
void RechercherClient(Nc *liste);

#endif