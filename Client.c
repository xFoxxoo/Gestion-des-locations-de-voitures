#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

Nc *ChercherClient(Nc *liste, char *cin)
{
    while (liste)
    {
        if (!strcmp(liste->c.cin, cin))
            return liste;
        liste = liste->next;
    }
    return NULL;
}

void AjouterClient(Nc **liste)
{
    Nc *c = malloc(sizeof(Nc));

    printf("Nom: ");
    scanf("%49s", c->c.nom);

    do
    {
        printf("CIN (unique): ");
        scanf("%9s", c->c.cin);
    } while (ChercherClient(*liste, c->c.cin));

    printf("Telephone: ");
    scanf("%14s", c->c.telephone);

    c->next = *liste;
    *liste = c;
}

void ModifierClient(Nc **liste)
{
    char cin[10];
    scanf("%9s", cin);

    Nc *c = ChercherClient(*liste, cin);

    if (c)
    {
        scanf("%49s", c->c.nom);
        scanf("%14s", c->c.telephone);
    }
}

void SupprimerClient(Nc **liste)
{
    char cin[10];
    scanf("%9s", cin);

    Nc *cur = *liste, *prev = NULL;

    while (cur)
    {
        if (!strcmp(cur->c.cin, cin))
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

void ListerClients(Nc *liste)
{
    while (liste)
    {
        printf("%s | %s | %s\n",
               liste->c.nom,
               liste->c.cin,
               liste->c.telephone);
        liste = liste->next;
    }
}

void RechercherClient(Nc *liste)
{
    char cin[10];
    scanf("%9s", cin);

    Nc *c = ChercherClient(liste, cin);

    if (c)
        printf("%s | %s | %s\n",
               c->c.nom,
               c->c.cin,
               c->c.telephone);
}