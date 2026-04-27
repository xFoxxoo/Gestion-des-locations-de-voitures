#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

static void ClearScreen(void)
{
    printf("\x1b[2J\x1b[H");
}

static void PrintTitle(const char *title)
{
    ClearScreen();
    printf("\x1b[1;37;44m%s\x1b[0m\n", title);
    printf("\x1b[1;34m==============================================================\x1b[0m\n");
}

static int ReadMenuChoice(void)
{
    int choice = -1;
    char line[32];

    if (!fgets(line, sizeof(line), stdin))
        return 0;

    choice = (int)strtol(line, NULL, 10);
    return choice;
}

static void Pause(void)
{
    printf("\n\x1b[33mAppuyez sur Entree pour continuer...\x1b[0m");
    fflush(stdout);
    getchar();
}

static void ShowInvalidOption(void)
{
    printf("\n\x1b[1;31mOption invalide. Veuillez choisir une option valide.\x1b[0m\n");
    Pause();
}

static void MenuVoiture(Nv **liste)
{
    int option;

    do
    {
        PrintTitle("Gestion des Voitures");
        printf("\x1b[1;36m1\x1b[0m. Ajouter une voiture\n");
        printf("\x1b[1;36m2\x1b[0m. Modifier une voiture\n");
        printf("\x1b[1;36m3\x1b[0m. Rechercher une voiture\n");
        printf("\x1b[1;36m4\x1b[0m. Supprimer une voiture\n");
        printf("\x1b[1;36m5\x1b[0m. Lister toutes les voitures\n");
        printf("\x1b[1;36m6\x1b[0m. Lister les voitures disponibles\n");
        printf("\x1b[1;36m7\x1b[0m. Trier les voitures par kilometrage\n");
        printf("\x1b[1;36m0\x1b[0m. Retour au menu principal\n");
        printf("\nVotre choix: ");

        option = ReadMenuChoice();

        switch (option)
        {
        case 1:
            AjouterVoiture(liste);
            break;
        case 2:
            ModifierVoiture(liste);
            break;
        case 3:
            RechercherVoiture(*liste);
            break;
        case 4:
            SupprimerVoiture(liste);
            break;
        case 5:
            ListerVoitures(*liste);
            Pause();
            break;
        case 6:
            ListerVoituresDisponibles(*liste);
            Pause();
            break;
        case 7:
            TrierVoitures(liste);
            printf("\n\x1b[32mTri termine.\x1b[0m\n");
            Pause();
            break;
        case 0:
            break;
        default:
            ShowInvalidOption();
            break;
        }
    } while (option != 0);
}

static void MenuClient(Nc **liste)
{
    int option;

    do
    {
        PrintTitle("Gestion des Clients");
        printf("\x1b[1;36m1\x1b[0m. Ajouter un client\n");
        printf("\x1b[1;36m2\x1b[0m. Modifier un client\n");
        printf("\x1b[1;36m3\x1b[0m. Rechercher un client\n");
        printf("\x1b[1;36m4\x1b[0m. Supprimer un client\n");
        printf("\x1b[1;36m5\x1b[0m. Lister tous les clients\n");
        printf("\x1b[1;36m0\x1b[0m. Retour au menu principal\n");
        printf("\nVotre choix: ");

        option = ReadMenuChoice();

        switch (option)
        {
        case 1:
            AjouterClient(liste);
            break;
        case 2:
            ModifierClient(liste);
            break;
        case 3:
            RechercherClient(*liste);
            break;
        case 4:
            SupprimerClient(liste);
            break;
        case 5:
            ListerClients(*liste);
            Pause();
            break;
        case 0:
            break;
        default:
            ShowInvalidOption();
            break;
        }
    } while (option != 0);
}

static void MenuReservation(Nr **lr, Nv *lv, Nc *lc)
{
    int option;

    do
    {
        PrintTitle("Gestion des Locations");
        printf("\x1b[1;36m1\x1b[0m. Effectuer une reservation\n");
        printf("\x1b[1;36m2\x1b[0m. Annuler une reservation\n");
        printf("\x1b[1;36m3\x1b[0m. Lister les reservations\n");
        printf("\x1b[1;36m4\x1b[0m. Historique d'un client\n");
        printf("\x1b[1;36m5\x1b[0m. Historique d'une voiture\n");
        printf("\x1b[1;36m6\x1b[0m. Facturation\n");
        printf("\x1b[1;36m0\x1b[0m. Retour au menu principal\n");
        printf("\nVotre choix: ");

        option = ReadMenuChoice();

        switch (option)
        {
        case 1:
            EffectuerReservation(lr, lv, lc);
            break;
        case 2:
            AnnulerReservation(lr, lv);
            break;
        case 3:
            ListerReservations(*lr);
            Pause();
            break;
        case 4:
            HistoriqueClient(*lr);
            Pause();
            break;
        case 5:
            HistoriqueVoiture(*lr);
            Pause();
            break;
        case 6:
            Facturation(*lr, lv);
            Pause();
            break;
        case 0:
            break;
        default:
            ShowInvalidOption();
            break;
        }
    } while (option != 0);
}

void MenuPrincipal(Nc **lc, Nv **lv, Nr **lr)
{
    int option;

    do
    {
        PrintTitle("Location de voitures - Menu principal");
        printf("\x1b[1;36m1\x1b[0m. Gestion des voitures\n");
        printf("\x1b[1;36m2\x1b[0m. Gestion des clients\n");
        printf("\x1b[1;36m3\x1b[0m. Gestion des locations\n");
        printf("\x1b[1;36m0\x1b[0m. Quitter\n");
        printf("\nVotre choix: ");

        option = ReadMenuChoice();

        switch (option)
        {
        case 1:
            MenuVoiture(lv);
            break;
        case 2:
            MenuClient(lc);
            break;
        case 3:
            MenuReservation(lr, *lv, *lc);
            break;
        case 0:
            printf("\n\x1b[32mMerci d'avoir utilise le gestionnaire de locations. A bientot !\x1b[0m\n");
            break;
        default:
            ShowInvalidOption();
            break;
        }
    } while (option != 0);
}
