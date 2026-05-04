#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Couleurs ANSI --- */
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

/* --- Structures --- */
typedef struct Client
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

typedef struct Voiture
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

typedef struct Reservation
{
    char cin[10];
    char matricule[10];
    int duree;
    int km;
    float prix;
    int active; // 1 = En cours, 0 = Terminee/Payee
} reservation;

typedef struct NdReservation
{
    reservation r;
    struct NdReservation *next;
} Nr;

/* --- Fonctions Utilitaires --- */
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Entete(char *titre)
{
    clearScreen();
    printf(CYAN BOLD "+-------------------------------------------------+\n");
    printf("| %-47s |\n", titre);
    printf("+-------------------------------------------------+\n" RESET);
}

void Erreur(char *message)
{
    printf(RED BOLD "Erreur: %s\n" RESET, message);
}

void Succes(char *message)
{
    printf(GREEN BOLD "Succes: %s\n" RESET, message);
}

void Pause()
{
    printf(YELLOW "\nAppuyez sur Entree pour continuer..." RESET);
    while (getchar() != '\n')
        ;
    getchar();
}

/* --- RECHERCHES --- */
Nv *rechercherVoiture(Nv *tete, char *matricule)
{
    while (tete != NULL)
    {
        if (strcmp(tete->v.matricule, matricule) == 0)
            return tete;
        tete = tete->next;
    }
    return NULL;
}

Nc *rechercherClient(Nc *tete, char *cin)
{
    while (tete != NULL)
    {
        if (strcmp(tete->c.cin, cin) == 0)
            return tete;
        tete = tete->next;
    }
    return NULL;
}

Nr *rechercherReservationActive(Nr *tete, char *cin, char *matricule)
{
    while (tete != NULL)
    {
        if (tete->r.active == 1 && strcmp(tete->r.cin, cin) == 0 && strcmp(tete->r.matricule, matricule) == 0)
            return tete;
        tete = tete->next;
    }
    return NULL;
}

/* --- GESTION VOITURES --- */
void AfficherV(voiture v)
{
    printf(CYAN "Vehicule: %s %s " RESET "| Mat: %s | Cat: %c | KM: %d | Dispo: ",
           v.marque, v.modele, v.matricule, v.categorie, v.kilometrage);
    if (v.disponible)
        printf(GREEN "Oui\n" RESET);
    else
        printf(RED "Non\n" RESET);
}

void AjouterVoiture(Nv **tete)
{
    voiture v;
    Entete("AJOUTER UNE VOITURE");
    printf("Marque: ");
    scanf(" %[^\n]", v.marque);
    printf("Modele: ");
    scanf(" %[^\n]", v.modele);

    do
    {
        printf("Matricule (unique, 8 carac max): ");
        scanf(" %9s", v.matricule);
        if (rechercherVoiture(*tete, v.matricule) != NULL)
            Erreur("Ce matricule existe deja.");
    } while (rechercherVoiture(*tete, v.matricule) != NULL);

    do
    {
        printf("Categorie (A, B, C): ");
        scanf(" %c", &v.categorie);
    } while (v.categorie != 'A' && v.categorie != 'B' && v.categorie != 'C');

    do
    {
        printf("Kilometrage: ");
        scanf("%d", &v.kilometrage);
    } while (v.kilometrage < 0);

    v.disponible = 1;

    Nv *newE = (Nv *)malloc(sizeof(Nv));
    newE->v = v;
    newE->next = *tete;
    *tete = newE;
    Succes("Voiture ajoutee au parc.");
}

void ModifierVoiture(Nv *tete)
{
    char mat[10];
    Entete("MODIFIER UNE VOITURE");
    printf("Matricule de la voiture: ");
    scanf(" %9s", mat);
    Nv *temp = rechercherVoiture(tete, mat);

    if (temp == NULL)
    {
        Erreur("Voiture introuvable.");
        return;
    }

    printf("Nouvelle Marque (%s): ", temp->v.marque);
    scanf(" %[^\n]", temp->v.marque);
    printf("Nouveau Modele (%s): ", temp->v.modele);
    scanf(" %[^\n]", temp->v.modele);
    do
    {
        printf("Nouvelle Categorie (A, B, C): ");
        scanf(" %c", &temp->v.categorie);
    } while (temp->v.categorie != 'A' && temp->v.categorie != 'B' && temp->v.categorie != 'C');
    Succes("Informations mises a jour.");
}

void SupprimerVoiture(Nv **tete)
{
    char mat[10];
    Entete("SUPPRIMER UNE VOITURE");
    printf("Matricule de la voiture: ");
    scanf(" %9s", mat);

    Nv *temp = *tete, *prev = NULL;
    while (temp != NULL)
    {
        if (strcmp(temp->v.matricule, mat) == 0)
        {
            if (temp->v.disponible == 0)
            {
                Erreur("Impossible: Vehicule actuellement loue.");
                return;
            }
            if (prev == NULL)
                *tete = temp->next;
            else
                prev->next = temp->next;
            free(temp);
            Succes("Voiture supprimee.");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    Erreur("Voiture introuvable.");
}

void AfficherToutesVoitures(Nv *tete)
{
    Entete("LISTE DU PARC AUTOMOBILE");
    if (!tete)
    {
        printf("Parc vide.\n");
        return;
    }
    while (tete)
    {
        AfficherV(tete->v);
        tete = tete->next;
    }
}

void AfficherVoituresDisponibles(Nv *tete)
{
    Entete("VEHICULES DISPONIBLES");
    int found = 0;
    while (tete)
    {
        if (tete->v.disponible)
        {
            AfficherV(tete->v);
            found = 1;
        }
        tete = tete->next;
    }
    if (!found)
        printf("Aucun vehicule disponible actuellement.\n");
}

/* --- GESTION CLIENTS --- */
void AfficherClient(client c)
{
    printf(CYAN "CIN: %-10s " RESET "| Nom: %-20s | Tel: %s\n", c.cin, c.nom, c.telephone);
}

void AjouterClient(Nc **tete)
{
    client c;
    Entete("NOUVEAU CLIENT");

    do
    {
        printf("CIN (unique): ");
        scanf(" %9s", c.cin);
        if (rechercherClient(*tete, c.cin) != NULL)
            Erreur("Ce CIN existe deja.");
    } while (rechercherClient(*tete, c.cin) != NULL);

    printf("Nom complet: ");
    scanf(" %[^\n]", c.nom);
    printf("Telephone: ");
    scanf(" %14s", c.telephone);

    Nc *newE = (Nc *)malloc(sizeof(Nc));
    newE->c = c;
    newE->next = *tete;
    *tete = newE;
    Succes("Client enregistre.");
}

void ModifierClient(Nc *tete)
{
    char cin[10];
    Entete("MODIFIER UN CLIENT");
    printf("CIN du client: ");
    scanf(" %9s", cin);
    Nc *temp = rechercherClient(tete, cin);
    if (!temp)
    {
        Erreur("Client introuvable.");
        return;
    }
    printf("Nouveau nom (%s): ", temp->c.nom);
    scanf(" %[^\n]", temp->c.nom);
    printf("Nouveau Tel (%s): ", temp->c.telephone);
    scanf(" %14s", temp->c.telephone);
    Succes("Client mis a jour.");
}

void AfficherTousClients(Nc *tete)
{
    Entete("LISTE DES CLIENTS");
    if (!tete)
    {
        printf("Aucun client.\n");
        return;
    }
    while (tete)
    {
        AfficherClient(tete->c);
        tete = tete->next;
    }
}

void SupprimerClient(Nc **teteC, Nr *teteR)
{
    char cin[10];
    Entete("SUPPRIMER UN CLIENT");
    printf("CIN du client a supprimer: ");
    scanf(" %9s", cin);

    // Verifier si le client a une location en cours
    Nr *tr = teteR;
    while (tr)
    {
        if (strcmp(tr->r.cin, cin) == 0 && tr->r.active == 1)
        {
            Erreur("Ce client a une reservation en cours. Suppression impossible.");
            return;
        }
        tr = tr->next;
    }

    Nc *temp = *teteC, *prev = NULL;
    while (temp)
    {
        if (strcmp(temp->c.cin, cin) == 0)
        {
            if (prev == NULL)
                *teteC = temp->next;
            else
                prev->next = temp->next;
            free(temp);
            Succes("Client supprime.");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    Erreur("Client introuvable.");
}

/* --- GESTION RESERVATIONS ET FACTURATION --- */
void EffectuerReservation(Nr **teteR, Nv *teteV, Nc **teteC)
{
    Entete("EFFECTUER UNE RESERVATION");
    if (!teteV)
    {
        Erreur("Le parc automobile est vide.");
        return;
    }

    int choixC;
    printf("1. Nouveau Client\n");
    printf("2. Ancien Client\n");
    printf("Votre choix : ");
    scanf("%d", &choixC);

    char cin_res[10];
    if (choixC == 1)
    {
        AjouterClient(teteC);
        strcpy(cin_res, (*teteC)->c.cin); // Le dernier ajoute est en tête
    }
    else
    {
        printf("Saisir le CIN : ");
        scanf(" %9s", cin_res);
        if (!rechercherClient(*teteC, cin_res))
        {
            Erreur("Client introuvable.");
            return;
        }
    }

    char mat_res[10];
    printf("\nVehicules disponibles :\n");
    AfficherVoituresDisponibles(teteV);
    printf("\nMatricule du vehicule choisi : ");
    scanf(" %9s", mat_res);

    Nv *v = rechercherVoiture(teteV, mat_res);
    if (!v)
    {
        Erreur("Vehicule introuvable.");
        return;
    }
    if (!v->v.disponible)
    {
        Erreur("Vehicule non disponible.");
        return;
    }

    reservation r;
    strcpy(r.cin, cin_res);
    strcpy(r.matricule, mat_res);
    printf("Duree prevue (en jours) : ");
    scanf("%d", &r.duree);
    r.active = 1;
    r.km = 0; // Sera defini au retour
    r.prix = 0.0;

    Nr *newR = (Nr *)malloc(sizeof(Nr));
    newR->r = r;
    newR->next = *teteR;
    *teteR = newR;

    v->v.disponible = 0; // Rendre la voiture indisponible
    Succes("Reservation effectuee avec succes.");
}

void AfficherReservationsEnCours(Nr *tete)
{
    Entete("RESERVATIONS EN COURS");
    int count = 0;
    while (tete)
    {
        if (tete->r.active)
        {
            printf(CYAN "Client: %s " RESET "| Voiture: %s | Duree: %d jours\n",
                   tete->r.cin, tete->r.matricule, tete->r.duree);
            count++;
        }
        tete = tete->next;
    }
    if (count == 0)
        printf("Aucune reservation en cours.\n");
}

void RetourVehiculeEtFacturation(Nr *teteR, Nv *teteV, Nc *teteC)
{
    char cin[10], mat[10];
    Entete("RETOUR VEHICULE & FACTURATION");

    printf("CIN du Client: ");
    scanf(" %9s", cin);
    printf("Matricule du vehicule: ");
    scanf(" %9s", mat);

    Nr *res = rechercherReservationActive(teteR, cin, mat);
    if (!res)
    {
        Erreur("Aucune reservation active trouvee pour ce couple Client/Vehicule.");
        return;
    }

    Nv *v = rechercherVoiture(teteV, mat);
    Nc *c = rechercherClient(teteC, cin);

    printf("\nKilometres parcourus lors de la location : ");
    int km_parcourus;
    scanf("%d", &km_parcourus);

    // Mise a jour de l'objet reservation
    res->r.km = km_parcourus;
    res->r.active = 0; // La location est terminee

    // Mise a jour de la voiture
    v->v.kilometrage += km_parcourus;
    v->v.disponible = 1;

    // Calcul du prix : 0.5dh par KM + un prix de base par jour selon categorie (bonus)
    float prix_jour = (v->v.categorie == 'A') ? 150 : (v->v.categorie == 'B') ? 250
                                                                              : 400;
    res->r.prix = (res->r.duree * prix_jour) + (km_parcourus * 0.5);

    // Affichage de la facture
    clearScreen();
    printf(BOLD MAGENTA "=================================================\n");
    printf("                  FACTURE DETAILS                  \n");
    printf("=================================================\n" RESET);
    printf("Client    : %s (CIN: %s)\n", c->c.nom, c->c.cin);
    printf("Vehicule  : %s %s (Mat: %s)\n", v->v.marque, v->v.modele, v->v.matricule);
    printf("-------------------------------------------------\n");
    printf("Duree de location : %d jours (Tarif base: %.2f DH/j)\n", res->r.duree, prix_jour);
    printf("Distance parcourue: %d Km (Tarif KM: 0.50 DH/Km)\n", km_parcourus);
    printf("-------------------------------------------------\n");
    printf(BOLD GREEN "TOTAL A PAYER     : %.2f DH\n" RESET, res->r.prix);
    printf(BOLD MAGENTA "=================================================\n\n" RESET);

    int paiement;
    printf("Modes de paiement:\n1. Carte Bancaire\n2. Virement\n3. Especes\nChoix du paiement: ");
    scanf("%d", &paiement);
    Succes("Paiement valide. Vehicule restitue au parc.");
}

void HistoriqueLocationsClient(Nr *teteR, char *cin)
{
    int count = 0;
    while (teteR)
    {
        if (strcmp(teteR->r.cin, cin) == 0)
        {
            printf("- Vehicule: %s | Jours: %d | KM: %d | Total Paye: %.2f DH | Statut: %s\n",
                   teteR->r.matricule, teteR->r.duree, teteR->r.km, teteR->r.prix,
                   teteR->r.active ? "En cours" : "Terminee");
            count++;
        }
        teteR = teteR->next;
    }
    if (count == 0)
        printf("Aucun historique pour ce client.\n");
}

/* --- FONCTION DE LIBERATION MEMOIRE --- */
void LibererTout(Nv *teteV, Nc *teteC, Nr *teteR)
{
    Nv *tv;
    while (teteV)
    {
        tv = teteV;
        teteV = teteV->next;
        free(tv);
    }
    Nc *tc;
    while (teteC)
    {
        tc = teteC;
        teteC = teteC->next;
        free(tc);
    }
    Nr *tr;
    while (teteR)
    {
        tr = teteR;
        teteR = teteR->next;
        free(tr);
    }
}



/* --- FONCTION DE DONNEES DE TEST (MOCK DATA) --- */
void GenererDonneesTest(Nv **teteV, Nc **teteC, Nr **teteR) {
    // 1. Ajout de Voitures de test
    Nv *v1 = (Nv *)malloc(sizeof(Nv));
    strcpy(v1->v.marque, "Renault"); strcpy(v1->v.modele, "Clio 4"); strcpy(v1->v.matricule, "11111111");
    v1->v.categorie = 'A'; v1->v.kilometrage = 45000; v1->v.disponible = 1;
    v1->next = *teteV; *teteV = v1;

    Nv *v2 = (Nv *)malloc(sizeof(Nv));
    strcpy(v2->v.marque, "Dacia"); strcpy(v2->v.modele, "Duster"); strcpy(v2->v.matricule, "22222222");
    v2->v.categorie = 'B'; v2->v.kilometrage = 12000; v2->v.disponible = 1;
    v2->next = *teteV; *teteV = v2;

    Nv *v3 = (Nv *)malloc(sizeof(Nv));
    strcpy(v3->v.marque, "Mercedes"); strcpy(v3->v.modele, "Classe C"); strcpy(v3->v.matricule, "33333333");
    v3->v.categorie = 'C'; v3->v.kilometrage = 5000; v3->v.disponible = 0; // Celle-ci sera en location
    v3->next = *teteV; *teteV = v3;

    // 2. Ajout de Clients de test
    Nc *c1 = (Nc *)malloc(sizeof(Nc));
    strcpy(c1->c.nom, "Ahmed Alaoui"); strcpy(c1->c.cin, "EE12345"); strcpy(c1->c.telephone, "0600112233");
    c1->next = *teteC; *teteC = c1;

    Nc *c2 = (Nc *)malloc(sizeof(Nc));
    strcpy(c2->c.nom, "Sara Benali"); strcpy(c2->c.cin, "EE98765"); strcpy(c2->c.telephone, "0699887766");
    c2->next = *teteC; *teteC = c2;

    // 3. Ajout d'une Réservation en cours (Ahmed loue la Mercedes)
    Nr *r1 = (Nr *)malloc(sizeof(Nr));
    strcpy(r1->r.cin, "EE12345"); strcpy(r1->r.matricule, "33333333");
    r1->r.duree = 5; r1->r.km = 0; r1->r.prix = 0.0; r1->r.active = 1; // En cours
    r1->next = *teteR; *teteR = r1;

    printf(GREEN BOLD "=> [DEV] Données de test injectées avec succès !\n" RESET);
    Pause();
}
/* --- MENUS --- */
int main()
{
    Nv *teteV = NULL;
    Nc *teteC = NULL;
    Nr *teteR = NULL;
    int choixP, choixV, choixC, choixL, choixR;
    GenererDonneesTest(&teteV, &teteC, &teteR);
    do
    {
        Entete("MENU PRINCIPAL");
        printf("  " YELLOW "1." RESET " GESTION DES VOITURES\n");
        printf("  " YELLOW "2." RESET " GESTION DES CLIENTS\n");
        printf("  " YELLOW "3." RESET " GESTION DES LOCATIONS\n");
        printf("  " RED "4. QUITTER\n" RESET);
        printf("\nVOTRE CHOIX : ");
        scanf("%d", &choixP);

        switch (choixP)
        {
        case 1: // Menu Voitures
            do
            {
                Entete("GESTION DES VOITURES");
                printf("  1. Ajouter Voiture\n  2. Modifier Voiture\n  3. Chercher Voiture\n  4. Supprimer Voiture\n");
                printf("  5. Liste des Voitures\n  6. Liste des Voitures Disponibles\n  7. Historique d'une voiture\n  0. Retour\n");
                printf("\nVOTRE CHOIX : ");
                scanf("%d", &choixV);
                switch (choixV)
                {
                case 1:
                    AjouterVoiture(&teteV);
                    Pause();
                    break;
                case 2:
                    ModifierVoiture(teteV);
                    Pause();
                    break;
                case 3:
                {
                    char mat[10];
                    printf("Matricule: ");
                    scanf(" %9s", mat);
                    Nv *v = rechercherVoiture(teteV, mat);
                    if (v)
                        AfficherV(v->v);
                    else
                        Erreur("Non trouvee.");
                    Pause();
                    break;
                }
                case 4:
                    SupprimerVoiture(&teteV);
                    Pause();
                    break;
                case 5:
                    AfficherToutesVoitures(teteV);
                    Pause();
                    break;
                case 6:
                    AfficherVoituresDisponibles(teteV);
                    Pause();
                    break;
                case 7:
                {
                    char mat[10];
                    printf("Matricule: ");
                    scanf(" %9s", mat);
                    Entete("HISTORIQUE VOITURE");
                    Nr *tr = teteR;
                    int found = 0;
                    while (tr)
                    {
                        if (strcmp(tr->r.matricule, mat) == 0)
                        {
                            printf("Client: %s | Jours: %d | KM ajoutes: %d | Statut: %s\n",
                                   tr->r.cin, tr->r.duree, tr->r.km, tr->r.active ? "En location" : "Terminee");
                            found = 1;
                        }
                        tr = tr->next;
                    }
                    if (!found)
                        printf("Aucun historique pour ce vehicule.\n");
                    Pause();
                    break;
                }
                }
            } while (choixV != 0);
            break;

        case 2: // Menu Clients
            do
            {
                Entete("GESTION DES CLIENTS");
                printf("  1. Ajouter Client\n  2. Modifier infos Client\n  3. Chercher Client\n  4. Supprimer Client\n");
                printf("  5. Liste des Clients\n  6. Historique locations/paiements Client\n  0. Retour\n");
                printf("\nVOTRE CHOIX : ");
                scanf("%d", &choixC);
                switch (choixC)
                {
                case 1:
                    AjouterClient(&teteC);
                    Pause();
                    break;
                case 2:
                    ModifierClient(teteC);
                    Pause();
                    break;
                case 3:
                {
                    char cin[10];
                    printf("CIN: ");
                    scanf(" %9s", cin);
                    Nc *c = rechercherClient(teteC, cin);
                    if (c)
                        AfficherClient(c->c);
                    else
                        Erreur("Introuvable.");
                    Pause();
                    break;
                }
                case 4:
                    SupprimerClient(&teteC, teteR);
                    Pause();
                    break;
                case 5:
                    AfficherTousClients(teteC);
                    Pause();
                    break;
                case 6:
                {
                    char cin[10];
                    printf("CIN du Client: ");
                    scanf(" %9s", cin);
                    Entete("HISTORIQUE CLIENT");
                    HistoriqueLocationsClient(teteR, cin);
                    Pause();
                    break;
                }
                }
            } while (choixC != 0);
            break;

        case 3: // Menu Locations
            do
            {
                Entete("GESTION DES LOCATIONS");
                printf("  1. Gestion des reservations\n");
                printf("  2. Facturation et paiements (Retour de vehicule)\n");
                printf("  0. Retour\n");
                printf("\nVOTRE CHOIX : ");
                scanf("%d", &choixL);

                if (choixL == 1)
                { // Sous-menu Reservations
                    do
                    {
                        Entete("GESTION DES RESERVATIONS");
                        printf("  1. Effectuer une Reservation\n  2. Annuler une Reservation\n  3. Liste des Reservations en cours\n  0. Retour\n");
                        printf("\nVOTRE CHOIX : ");
                        scanf("%d", &choixR);
                        switch (choixR)
                        {
                        case 1:
                            EffectuerReservation(&teteR, teteV, &teteC);
                            Pause();
                            break;
                        case 2:
                        {
                            char cin[10], mat[10];
                            printf("CIN: ");
                            scanf(" %9s", cin);
                            printf("Matricule: ");
                            scanf(" %9s", mat);
                            Nr *temp = teteR, *prev = NULL;
                            while (temp != NULL)
                            {
                                if (strcmp(temp->r.cin, cin) == 0 && strcmp(temp->r.matricule, mat) == 0 && temp->r.active == 1)
                                {
                                    Nv *v = rechercherVoiture(teteV, mat);
                                    if (v)
                                        v->v.disponible = 1;
                                    if (prev == NULL)
                                        teteR = temp->next;
                                    else
                                        prev->next = temp->next;
                                    free(temp);
                                    Succes("Reservation annulee.");
                                    break;
                                }
                                prev = temp;
                                temp = temp->next;
                            }
                            if (!temp)
                                Erreur("Reservation active non trouvee.");
                            Pause();
                            break;
                        }
                        case 3:
                            AfficherReservationsEnCours(teteR);
                            Pause();
                            break;
                        }
                    } while (choixR != 0);
                }
                else if (choixL == 2)
                {
                    RetourVehiculeEtFacturation(teteR, teteV, teteC);
                    Pause();
                }
            } while (choixL != 0);
            break;
        }
    } while (choixP != 4);

    LibererTout(teteV, teteC, teteR);
    printf(GREEN BOLD "\nMerci d'avoir utilise notre systeme. Au revoir !\n" RESET);
    return 0;
}