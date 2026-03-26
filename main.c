#include <stdio.h>

void GestionVoiture()
{
    int menuv;
    do
    {
        printf("Menu Voiture (1-7): (Retour au menu principal: 0) ");
        scanf("%d", &menuv);
        switch (menuv)
        {
        case 1:
            AjouterVoiture();
            break;
        case 2:
            ModifierVoiture();
            break;
        case 3:
            ChercherVoiture();
            break;
        case 4:
            SupprimerVoiture();
            break;
        case 5:
            ListerVoitures();
            break;
        case 6:
            ListerVoituresDisponibles();
            break;
            case 7:
            HistoriqueLocationVoiture();
            break;
        default:
            printf("Choix invalide\n");
        case 0:
            break;
        }
    } while (menuv);
}

void GestionClient()
{
    int menuc;
    do
    {
        printf("Menu Client (1-6): (Retour au menu principal: 0) ");
        scanf("%d", &menuc);
        switch (menuc)
        {
        case 1:
            AjouterClient();
            break;
        case 2:
            ModifierClient();
            break;
        case 3:
            ChercherClient();
            break;
        case 4:
            SupprimerClient();
            break;
        case 5:
            ListerClients();
            break;
            case 6:
            HistoriqueLocationPaimentClient();
        default:
            printf("Choix invalide\n");
        case 0:
            break;
        }
    } while (menuc);
}

void GestionLocation()
{
    int menul;
    do
    {
        printf("Menu Location (1-2): (Retour au menu principal: 0) ");
        scanf("%d", &menul);
        switch (menul)
        {
        case 1:
            GestionReservation();
            break;
        case 2:
            Facturation();
            break;
        default:
            printf("Choix invalide\n");
        case 0:
            break;
        }
    } while (menul);
}
void GestionReservation()
{
    int menur;
    do
    {
        printf("Menu Reservation (1-5): (Retour au menu Location: 0) ");
        scanf("%d", &menur);
        switch (menur)
        {
        case 1:
            EffectuerReservation();
            break;
        case 2:
            ModifierReservation();
            break;
        case 3:
            AnnulerReservation();
            break;
        case 4:
            SupprimerReservation();
            break;
        case 5:
            ListerReservations();
            break;
        default:
            printf("Choix invalide\n");
        case 0:
            break;
        }
    } while (menur);
}

int main()
{
    int menup;
    do
    {
        printf("Menu Principale (1-3): ");
        scanf("%d", &menup);
        switch (menup)
        {
        case 1:
            GestionVoiture();
            break;
        case 2:
            GestionClient();
            break;
        case 3:
            GestionLocation();
            break;
        default:
            printf("Choix invalide\n");
        case 0:
            printf("Au revoir!\n");
            break;
        }
    } while (menup);
    return 0;
}