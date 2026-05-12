#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ===================== COULEURS ANSI ===================== */
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"
/* ===================== CONSTANTES ===================== */
#define MAX_NOM 100
#define MAX_CIN 20
#define MAX_TEL 20
#define MAX_MARQUE 50
#define MAX_MODELE 50
#define MAX_MATRICULE 20
#define MAX_PAIEMENT 30
/* ===================== STRUCTURES ===================== */
typedef struct Client
{
    char nom[MAX_NOM];
    char cin[MAX_CIN];
    char telephone[MAX_TEL];
} Client;
typedef struct NdClient
{
    Client c;
    struct NdClient *next;
} Nc;
typedef struct Voiture
{
    char marque[MAX_MARQUE];
    char modele[MAX_MODELE];
    char matricule[MAX_MATRICULE];
    char categorie;
    int kilometrage;
    int disponible;
} Voiture;
typedef struct NdVoiture
{
    Voiture v;
    struct NdVoiture *next;
} Nv;
typedef struct Reservation
{
    int idReservation;
    char cin[MAX_CIN];
    char matricule[MAX_MATRICULE];
    int duree;
    int kmParcourus;
    float prix;
    char modePaiement[MAX_PAIEMENT];
    int active;
} Reservation;
typedef struct NdReservation
{
    Reservation r;
    struct NdReservation *next;
} Nr;

int compteurReservation = 1;
/* ===================== UTILITAIRES ===================== */
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void Pause()
{
    printf(YELLOW "\nAppuyez sur ENTREE pour continuer..." RESET);
    while (getchar() != '\n')
        ;
    getchar();
}
void Entete(char titre[])
{
    clearScreen();
    printf(CYAN BOLD);
    printf("============================================================\n");
    printf("%s\n", titre);
    printf("============================================================\n");
    printf(RESET);
}
void Erreur(char message[])
{
    printf(RED BOLD "ERREUR : %s\n" RESET, message);
}
void Succes(char message[])
{
    printf(GREEN BOLD "SUCCES : %s\n" RESET, message);
}
/* ===================== RECHERCHES ===================== */
Nv *RechercherVoiture(Nv *tete, char matricule[])
{
    while (tete != NULL)
    {
        if (!strcmp(tete->v.matricule, matricule))
            return tete;
        tete = tete->next;
    }
    return NULL;
}
Nc *RechercherClient(Nc *tete, char cin[])
{
    while (tete != NULL)
    {
        if (!strcmp(tete->c.cin, cin))
            return tete;
        tete = tete->next;
    }
    return NULL;
}
Nr *RechercherReservationActive(Nr *tete, char cin[], char matricule[])
{
    while (tete != NULL)
    {
        if (!strcmp(tete->r.cin, cin) && !strcmp(tete->r.matricule, matricule) && tete->r.active)
            return tete;
        tete = tete->next;
    }
    return NULL;
}
/* ===================== AFFICHAGE ===================== */
void AfficherVoiture(Voiture v)
{
    printf(CYAN);
    printf("Marque      : %s\n", v.marque);
    printf("Modele      : %s\n", v.modele);
    printf("Matricule   : %s\n", v.matricule);
    printf("Categorie   : %c\n", v.categorie);
    printf("Kilometrage : %d KM\n", v.kilometrage);
    printf("Disponible  : ");
    if (v.disponible)
        printf(GREEN "Oui\n"RESET);
    else
        printf(RED "Non\n"RESET);
    printf("----------------------------------------------\n");
}
void AfficherClient(Client c)
{
    printf(CYAN);
    printf("Nom       : %s\n", c.nom);
    printf("CIN       : %s\n", c.cin);
    printf("Telephone : %s\n"RESET, c.telephone);
    printf(RESET);
    printf("----------------------------------------------\n");
}
/* ===================== GESTION VOITURES ===================== */
void AjouterVoiture(Nv **tete)
{
    Voiture v;
    Entete("AJOUTER UNE VOITURE");
    printf("Marque : ");
    scanf(" %[^\n]", v.marque);
    printf("Modele : ");
    scanf(" %[^\n]", v.modele);
    do
    {
        printf("Matricule : ");
        scanf(" %19s", v.matricule);
        if (RechercherVoiture(*tete, v.matricule) != NULL)
            Erreur("Ce matricule existe deja.");
    } while (RechercherVoiture(*tete, v.matricule) != NULL);
    do
    {
        printf("Categorie (A/B/C) : ");
        scanf(" %c", &v.categorie);
    } while (v.categorie != 'A' &&v.categorie != 'B' && v.categorie != 'C');
    do
    {
        printf("Kilometrage : ");
        scanf("%d", &v.kilometrage);
    } while (v.kilometrage < 0);
    v.disponible = 1;
    Nv *newNode = (Nv *)malloc(sizeof(Nv));
    newNode->v = v;
    newNode->next = *tete;
    *tete = newNode;
    Succes("Voiture ajoutee.");
}
void AfficherToutesVoitures(Nv *tete)
{
    Entete("LISTE DES VOITURES");
    if (tete == NULL)
    {
        printf("Aucune voiture.\n");
        return;
    }
    while (tete != NULL)
    {
        AfficherVoiture(tete->v);
        tete = tete->next;
    }
}
void AfficherVoituresDisponiblesTriees(Nv *tete)
{
    Entete("VOITURES DISPONIBLES TRIEES");
    Voiture tab[1000];
    int n = 0;
    while (tete != NULL)
    {
        if (tete->v.disponible)
        {
            tab[n++] = tete->v;
        }
        tete = tete->next;
    }
    if (n == 0)
    {
        printf("Aucune voiture disponible.\n");
        return;
    }
    /* TRI A BULLES */
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (tab[j].kilometrage > tab[j + 1].kilometrage)
            {
                Voiture temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        AfficherVoiture(tab[i]);
    }
}
void RechercherParMarque(Nv *tete)
{
    char marque[MAX_MARQUE];
    int found = 0;
    Entete("RECHERCHE PAR MARQUE");
    printf("Entrer la marque : ");
    scanf(" %[^\n]", marque);
    while (tete != NULL)
    {
        if (!strcmp(tete->v.marque, marque) && tete->v.disponible)
        {
            AfficherVoiture(tete->v);
            found = 1;
        }
        tete = tete->next;
    }
    if (!found)
    {
        printf("Aucune voiture disponible pour cette marque.\n");
    }
}
void ModifierVoiture(Nv *tete)
{
    char matricule[MAX_MATRICULE];
    Entete("MODIFIER UNE VOITURE");
    printf("Matricule : ");
    scanf(" %19s", matricule);
    Nv *v = RechercherVoiture(tete, matricule);
    if (v == NULL)
    {
        Erreur("Voiture introuvable.");
        return;
    }
    printf("Nouvelle marque : ");
    scanf(" %[^\n]", v->v.marque);
    printf("Nouveau modele : ");
    scanf(" %[^\n]", v->v.modele);
    do
    {
        printf("Nouveau kilometrage : ");
        scanf("%d", &v->v.kilometrage);
    } while (v->v.kilometrage < 0);
    Succes("Voiture modifiee.");
}
void SupprimerVoiture(Nv **tete)
{
    char matricule[MAX_MATRICULE];
    Entete("SUPPRIMER UNE VOITURE");
    printf("Matricule : ");
    scanf(" %19s", matricule);
    Nv *temp = *tete;
    Nv *prev = NULL;
    while (temp != NULL)
    {
        if (!strcmp(temp->v.matricule, matricule))
        {
            if (!temp->v.disponible)
            {
                Erreur("Voiture actuellement louee.");
                return;
            }
            if (prev == NULL)
            {
                *tete = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp);
            Succes("Voiture supprimee.");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    Erreur("Voiture introuvable.");
}
/* ===================== GESTION CLIENTS ===================== */
void AjouterClient(Nc **tete)
{
    Client c;
    Entete("AJOUTER CLIENT");
    do
    {
        printf("CIN : ");
        scanf(" %19s", c.cin);
        if (RechercherClient(*tete, c.cin) != NULL)
        {
            Erreur("CIN deja utilise.");
        }
    } while (RechercherClient(*tete, c.cin) != NULL);
    printf("Nom : ");
    scanf(" %[^\n]", c.nom);
    printf("Telephone : ");
    scanf(" %19s", c.telephone);
    Nc *newNode = (Nc *)malloc(sizeof(Nc));
    newNode->c = c;
    newNode->next = *tete;
    *tete = newNode;
    Succes("Client ajoute.");
}
void AfficherTousClients(Nc *tete)
{
    Entete("LISTE CLIENTS");
    if (tete == NULL)
    {
        printf("Aucun client.\n");
        return;
    }
    while (tete != NULL)
    {
        AfficherClient(tete->c);
        tete = tete->next;
    }
}
void ModifierClient(Nc *tete)
{
    char cin[MAX_CIN];
    Entete("MODIFIER CLIENT");
    printf("CIN : ");
    scanf(" %19s", cin);
    Nc *c = RechercherClient(tete, cin);
    if (c == NULL)
    {
        Erreur("Client introuvable.");
        return;
    }
    printf("Nouveau nom : ");
    scanf(" %[^\n]", c->c.nom);
    printf("Nouveau telephone : ");
    scanf(" %19s", c->c.telephone);
    Succes("Client modifie.");
}
void SupprimerClient(Nc **tete, Nr *reservations)
{
    char cin[MAX_CIN];
    Entete("SUPPRIMER CLIENT");
    printf("CIN : ");
    scanf(" %19s", cin);
    Nr *r = reservations;
    while (r != NULL)
    {
        if (strcmp(r->r.cin, cin) == 0 &&
            r->r.active == 1)
        {
            Erreur("Client possede une reservation active.");
            return;
        }
        r = r->next;
    }
    Nc *temp = *tete;
    Nc *prev = NULL;
    while (temp != NULL)
    {
        if (strcmp(temp->c.cin, cin) == 0)
        {
            if (prev == NULL)
            {
                *tete = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp);
            Succes("Client supprime.");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    Erreur("Client introuvable.");
}
/* ===================== RESERVATIONS ===================== */
void EffectuerReservation(Nr **reservations, Nv *voitures, Nc **clients)
{
    Entete("NOUVELLE RESERVATION");
    if (voitures == NULL)
    {
        Erreur("Aucune voiture.");
        return;
    }
    int choix;
    printf("1. Nouveau client\n");
    printf("2. Ancien client\n");
    do
    {
        printf("Choix : ");
        scanf("%d", &choix);
    } while (choix != 1 && choix != 2);
    char cin[MAX_CIN];
    if (choix == 1)
    {
        AjouterClient(clients);
        strcpy(cin, (*clients)->c.cin);
    }
    else
    {
        printf("CIN : ");
        scanf(" %19s", cin);
        if (RechercherClient(*clients, cin) == NULL)
        {
            Erreur("Client introuvable.");
            return;
        }
    }
    AfficherVoituresDisponiblesTriees(voitures);
    char matricule[MAX_MATRICULE];
    printf("Matricule voiture : ");
    scanf(" %19s", matricule);
    Nv *v = RechercherVoiture(voitures, matricule);
    if (v == NULL)
    {
        Erreur("Voiture introuvable.");
        return;
    }
    if (!v->v.disponible)
    {
        Erreur("Voiture indisponible.");
        return;
    }
    Reservation r;
    r.idReservation = compteurReservation++;
    strcpy(r.cin, cin);
    strcpy(r.matricule, matricule);
    do
    {
        printf("Duree (jours) : ");
        scanf("%d", &r.duree);
    } while (r.duree <= 0);
    r.kmParcourus = 0;
    r.prix = 0;
    strcpy(r.modePaiement, "Non paye");
    r.active = 1;
    Nr *newNode = (Nr *)malloc(sizeof(Nr));
    newNode->r = r;
    newNode->next = *reservations;
    *reservations = newNode;
    v->v.disponible = 0;
    Succes("Reservation effectuee.");
}
void AfficherReservations(Nr *tete)
{
    Entete("LISTE DES RESERVATIONS");
    if (tete == NULL)
    {
        printf("Aucune reservation.\n");
        return;
    }
    while (tete != NULL)
    {
        printf(CYAN);
        printf("ID            : %d\n", tete->r.idReservation);
        printf("Client CIN    : %s\n", tete->r.cin);
        printf("Matricule     : %s\n", tete->r.matricule);
        printf("Duree         : %d jours\n", tete->r.duree);
        printf("KM Parcourus  : %d\n", tete->r.kmParcourus);
        printf("Prix          : %.2f DH\n", tete->r.prix);
        printf("Paiement      : %s\n", tete->r.modePaiement);
        printf("Etat          : ");
        if (tete->r.active)
        {
            printf(GREEN "ACTIVE\n");
        }
        else
        {
            printf(RED "TERMINEE\n");
        }
        printf(RESET);
        printf("----------------------------------------------\n");
        tete = tete->next;
    }
}
void RetourVehicule(Nr *reservations,
                    Nv *voitures,
                    Nc *clients)
{
    char cin[MAX_CIN];
    char matricule[MAX_MATRICULE];
    Entete("RETOUR VEHICULE");
    printf("CIN : ");
    scanf(" %19s", cin);
    printf("Matricule : ");
    scanf(" %19s", matricule);
    Nr *res = RechercherReservationActive(reservations,
                                          cin,
                                          matricule);
    if (res == NULL)
    {
        Erreur("Reservation introuvable.");
        return;
    }
    Nv *v = RechercherVoiture(voitures, matricule);
    Nc *c = RechercherClient(clients, cin);
    int km;
    do
    {
        printf("Kilometres parcourus : ");
        scanf("%d", &km);
    } while (km < 0);
    res->r.kmParcourus = km;
    float prixJour;
    if (v->v.categorie == 'A')
    {
        prixJour = 150;
    }
    else if (v->v.categorie == 'B')
    {
        prixJour = 250;
    }
    else
    {
        prixJour = 400;
    }
    res->r.prix =
        (res->r.duree * prixJour) + (km * 0.5);
    int paiement;
    do
    {
        printf("\n1. Carte Bancaire\n");
        printf("2. Virement\n");
        printf("3. Especes\n");
        printf("Choix paiement : ");
        scanf("%d", &paiement);
    } while (paiement < 1 || paiement > 3);
    switch (paiement)
    {
    case 1:
        strcpy(res->r.modePaiement, "Carte Bancaire");
        break;
    case 2:
        strcpy(res->r.modePaiement, "Virement");
        break;
    case 3:
        strcpy(res->r.modePaiement, "Especes");
        break;
    }
    res->r.active = 0;
    v->v.kilometrage += km;
    v->v.disponible = 1;
    Entete("FACTURE");
    printf(GREEN BOLD);
    printf("Client        : %s\n", c->c.nom);
    printf("Voiture       : %s %s\n",
           v->v.marque,
           v->v.modele);
    printf("Duree         : %d jours\n",
           res->r.duree);
    printf("KM            : %d\n",
           km);
    printf("Paiement      : %s\n",
           res->r.modePaiement);
    printf("TOTAL         : %.2f DH\n",
           res->r.prix);
    printf(RESET);
    Succes("Vehicule retourne.");
}
/* ===================== HISTORIQUE ===================== */
void HistoriqueClient(Nr *tete, char cin[])
{
    int found = 0;
    while (tete != NULL)
    {
        if (strcmp(tete->r.cin, cin) == 0)
        {
            found = 1;
            printf(CYAN);
            printf("Reservation ID : %d\n",
                   tete->r.idReservation);
            printf("Voiture        : %s\n",
                   tete->r.matricule);
            printf("Duree          : %d jours\n",
                   tete->r.duree);
            printf("Prix           : %.2f DH\n",
                   tete->r.prix);
            printf("Paiement       : %s\n",
                   tete->r.modePaiement);
            printf("Etat           : %s\n",
                   tete->r.active ? "ACTIVE" : "TERMINEE");
            printf(RESET);
            printf("----------------------------------------------\n");
        }
        tete = tete->next;
    }
    if (!found)
    {
        printf("Aucun historique.\n");
    }
}
/* ===================== SAUVEGARDE ===================== */
void SauvegarderVoitures(Nv *tete)
{
    FILE *f = fopen("voitures.txt", "w");
    if (f == NULL)
    {
        return;
    }
    while (tete != NULL)
    {
        fprintf(f,
                "%s;%s;%s;%c;%d;%d\n",
                tete->v.marque,
                tete->v.modele,
                tete->v.matricule,
                tete->v.categorie,
                tete->v.kilometrage,
                tete->v.disponible);
        tete = tete->next;
    }
    fclose(f);
}
void SauvegarderClients(Nc *tete)
{
    FILE *f = fopen("clients.txt", "w");
    if (f == NULL)
    {
        return;
    }
    while (tete != NULL)
    {
        fprintf(f,
                "%s;%s;%s\n",
                tete->c.nom,
                tete->c.cin,
                tete->c.telephone);
        tete = tete->next;
    }
    fclose(f);
}
void SauvegarderReservations(Nr *tete)
{
    FILE *f = fopen("reservations.txt", "w");
    if (f == NULL)
    {
        return;
    }
    while (tete != NULL)
    {
        fprintf(f,
                "%d;%s;%s;%d;%d;%.2f;%s;%d\n",
                tete->r.idReservation,
                tete->r.cin,
                tete->r.matricule,
                tete->r.duree,
                tete->r.kmParcourus,
                tete->r.prix,
                tete->r.modePaiement,
                tete->r.active);
        tete = tete->next;
    }
    fclose(f);
}
/* ===================== CHARGEMENT ===================== */
void ChargerVoitures(Nv **tete)
{
    FILE *f = fopen("voitures.txt", "r");
    if (f == NULL)
    {
        return;
    }
    while (!feof(f))
    {
        Nv *newNode = (Nv *)malloc(sizeof(Nv));
        if (fscanf(f,
                   " %49[^;];%49[^;];%19[^;];%c;%d;%d\n",
                   newNode->v.marque,
                   newNode->v.modele,
                   newNode->v.matricule,
                   &newNode->v.categorie,
                   &newNode->v.kilometrage,
                   &newNode->v.disponible) == 6)
        {
            newNode->next = *tete;
            *tete = newNode;
        }
        else
        {
            free(newNode);
        }
    }
    fclose(f);
}
void ChargerClients(Nc **tete)
{
    FILE *f = fopen("clients.txt", "r");
    if (f == NULL)
    {
        return;
    }
    while (!feof(f))
    {
        Nc *newNode = (Nc *)malloc(sizeof(Nc));
        if (fscanf(f,
                   " %99[^;];%19[^;];%19[^\n]\n",
                   newNode->c.nom,
                   newNode->c.cin,
                   newNode->c.telephone) == 3)
        {
            newNode->next = *tete;
            *tete = newNode;
        }
        else
        {
            free(newNode);
        }
    }
    fclose(f);
}
void ChargerReservations(Nr **tete)
{
    FILE *f = fopen("reservations.txt", "r");
    if (f == NULL)
    {
        return;
    }
    int maxID = 0;
    while (!feof(f))
    {
        Nr *newNode = (Nr *)malloc(sizeof(Nr));
        if (fscanf(f,
                   "%d;%19[^;];%19[^;];%d;%d;%f;%29[^;];%d\n",
                   &newNode->r.idReservation,
                   newNode->r.cin,
                   newNode->r.matricule,
                   &newNode->r.duree,
                   &newNode->r.kmParcourus,
                   &newNode->r.prix,
                   newNode->r.modePaiement,
                   &newNode->r.active) == 8)
        {
            if (newNode->r.idReservation > maxID)
            {
                maxID = newNode->r.idReservation;
            }
            newNode->next = *tete;
            *tete = newNode;
        }
        else
        {
            free(newNode);
        }
    }
    compteurReservation = maxID + 1;
    fclose(f);
}
/* ===================== LIBERATION MEMOIRE ===================== */
void LibererTout(Nv *voitures,
                 Nc *clients,
                 Nr *reservations)
{
    while (voitures != NULL)
    {
        Nv *tmp = voitures;
        voitures = voitures->next;
        free(tmp);
    }
    while (clients != NULL)
    {
        Nc *tmp = clients;
        clients = clients->next;
        free(tmp);
    }
    while (reservations != NULL)
    {
        Nr *tmp = reservations;
        reservations = reservations->next;
        free(tmp);
    }
}
/* ===================== MAIN ===================== */
int main()
{
    Nv *voitures = NULL;
    Nc *clients = NULL;
    Nr *reservations = NULL;
    ChargerVoitures(&voitures);
    ChargerClients(&clients);
    ChargerReservations(&reservations);
    int choixPrincipal;
    do
    {
        Entete("MENU PRINCIPAL");
        printf("1. Gestion Voitures\n");
        printf("2. Gestion Clients\n");
        printf("3. Gestion Reservations\n");
        printf("4. Quitter\n");
        printf("\nChoix : ");
        scanf("%d", &choixPrincipal);
        switch (choixPrincipal)
        {
        case 1:
        {
            int choixVoiture;
            do
            {
                Entete("GESTION VOITURES");
                printf("1. Ajouter voiture\n");
                printf("2. Modifier voiture\n");
                printf("3. Supprimer voiture\n");
                printf("4. Afficher voitures\n");
                printf("5. Afficher disponibles triees\n");
                printf("6. Rechercher par marque\n");
                printf("0. Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choixVoiture);
                switch (choixVoiture)
                {
                case 1:
                    AjouterVoiture(&voitures);
                    Pause();
                    break;
                case 2:
                    ModifierVoiture(voitures);
                    Pause();
                    break;
                case 3:
                    SupprimerVoiture(&voitures);
                    Pause();
                    break;
                case 4:
                    AfficherToutesVoitures(voitures);
                    Pause();
                    break;
                case 5:
                    AfficherVoituresDisponiblesTriees(voitures);
                    Pause();
                    break;
                case 6:
                    RechercherParMarque(voitures);
                    Pause();
                    break;
                }
            } while (choixVoiture != 0);
            break;
        }
        case 2:
        {
            int choixClient;
            do
            {
                Entete("GESTION CLIENTS");
                printf("1. Ajouter client\n");
                printf("2. Modifier client\n");
                printf("3. Supprimer client\n");
                printf("4. Afficher clients\n");
                printf("5. Historique client\n");
                printf("0. Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choixClient);
                switch (choixClient)
                {
                case 1:
                    AjouterClient(&clients);
                    Pause();
                    break;
                case 2:
                    ModifierClient(clients);
                    Pause();
                    break;
                case 3:
                    SupprimerClient(&clients, reservations);
                    Pause();
                    break;
                case 4:
                    AfficherTousClients(clients);
                    Pause();
                    break;
                case 5:
                {
                    char cin[MAX_CIN];
                    printf("CIN : ");
                    scanf(" %19s", cin);
                    HistoriqueClient(reservations, cin);
                    Pause();
                    break;
                }
                }
            } while (choixClient != 0);
            break;
        }
        case 3:
        {
            int choixReservation;
            do
            {
                Entete("GESTION RESERVATIONS");
                printf("1. Nouvelle reservation\n");
                printf("2. Retour vehicule\n");
                printf("3. Afficher reservations\n");
                printf("0. Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choixReservation);
                switch (choixReservation)
                {
                case 1:
                    EffectuerReservation(&reservations,
                                         voitures,
                                         &clients);
                    Pause();
                    break;
                case 2:
                    RetourVehicule(reservations,
                                   voitures,
                                   clients);
                    Pause();
                    break;
                case 3:
                    AfficherReservations(reservations);
                    Pause();
                    break;
                }
            } while (choixReservation != 0);
            break;
        }
        case 4:
            SauvegarderVoitures(voitures);
            SauvegarderClients(clients);
            SauvegarderReservations(reservations);
            LibererTout(voitures,
                        clients,
                        reservations);
            printf(GREEN BOLD);
            printf("\nMerci d'avoir utilise le systeme.\n");
            printf(RESET);
            break;
        default:
            Erreur("Choix invalide.");
            Pause();
        }
    } while (choixPrincipal != 4);
    return 0;
}