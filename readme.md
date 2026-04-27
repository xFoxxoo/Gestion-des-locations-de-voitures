# Projet EMSI - Gestion des locations de voitures

## Presentation
Mini projet en langage C realise pour l'Ecole Marocaine des Sciences de l'Ingenieur (EMSI). Ce programme permet de gerer un parc automobile, des clients, des reservations et la facturation dans un systeme de location de voitures.

## Objectif
Le projet vise a gerer les operations suivantes pour une agence de location de voitures :
- gestion du parc automobile (marque, modele, matricule, categorie, kilometrage, disponibilite)
- gestion des clients (ajout, modification, recherche, suppression, liste)
- gestion des reservations et annulations
- suivi des historiques de location par client et par voiture
- facturation simple basee sur le kilometrage parcoure

## Fonctionnalites principales
### Gestion des voitures
- Ajouter, modifier, rechercher et supprimer une voiture
- Lister toutes les voitures
- Lister uniquement les voitures disponibles
- Trier les voitures par kilometrage
- Historique de location d'une voiture

### Gestion des clients
- Ajouter, modifier, rechercher et supprimer un client
- Lister tous les clients
- Afficher l'historique des reservations et paiements d'un client

### Gestion des locations
- Effectuer une reservation pour un client et une voiture disponible
- Annuler une reservation
- Consulter la liste des reservations en cours
- Consulter l'historique d'un client ou d'une voiture
- Facturation basee sur le nombre de kilometres parcours

## Architecture du projet
- `main.c` : point d'entree du programme, initialise les listes et lance le menu principal
- `menu.c` / `menu.h` : menu principal et sous-menus ANSI stylises
- `Client.c` / `Client.h` : gestion des clients et des listes chainees de clients
- `Voiture.c` / `Voiture.h` : gestion des voitures et des listes chainees de vehicules
- `Reservation.c` / `Reservation.h` : gestion des reservations, annulations, facturations et historiques

## Style et interface
Le menu utilise des codes ANSI pour un affichage plus professionnel dans le terminal. Les sous-menus sont clairement separés et la saisie est traitee de maniere plus sure pour reduire les erreurs de navigation.

## Compilation
Assurez-vous d'avoir un compilateur C installe (par exemple `gcc`). Depuis le dossier du projet :

```bash
gcc -Wall -Wextra main.c menu.c Client.c Voiture.c Reservation.c -o gestion_voitures.exe
```

## Execution
Lancez l'executable genere :

```bash
./gestion_voitures.exe
```

## Remarques
- Le projet utilise des listes chainees pour stocker les clients, voitures et reservations en memoire.
- Il n'y a pas de persistance sur disque dans la version actuelle : toutes les donnees sont perdues a la fermeture du programme.
- Le tarif de facturation est calcule a 0.5 DH par kilometre parcoure.

## Ameliorations possibles
- Sauvegarde/chargement des donnees dans des fichiers
- meilleure validation des entrees utilisateur
- gestion des modes de paiement (especes, carte, virement)
- interface graphique ou application multiplateforme
