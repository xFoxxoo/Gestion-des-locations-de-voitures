# 🚗 Gestion d'Agence de Location de Voitures

<div align="center">

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Console-black.svg)
![Memory](https://img.shields.io/badge/Data%20Structure-Linked%20Lists-green.svg)
![Status](https://img.shields.io/badge/Project-Completed-success.svg)
![EMSI](https://img.shields.io/badge/School-EMSI-red.svg)

### 📚 Mini Projet de Programmation C — EMSI 2025/2026

> Application complète de gestion d'une agence de location de voitures
> développée en langage C avec structures dynamiques, gestion mémoire
> et sauvegarde persistante dans des fichiers texte.

</div>

---

# ✨ Aperçu du Projet

Ce projet est une application console développée en **langage C** permettant de gérer une agence de location de voitures.

Le système permet de :

✅ Gérer les voitures
✅ Gérer les clients
✅ Effectuer des réservations
✅ Retourner les véhicules
✅ Générer des factures
✅ Sauvegarder les données automatiquement
✅ Trier les voitures disponibles
✅ Rechercher par marque
✅ Consulter l’historique des clients

---

# 🖥️ Interface Console ANSI

Le projet utilise des **couleurs ANSI** pour offrir une interface plus moderne et professionnelle.

```c
#define RED "\033[31m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
```

✔ Menus dynamiques
✔ Messages d’erreurs colorés
✔ Validation des saisies
✔ Factures formatées

---

# 📂 Structure du Projet

```bash
📁 Gestion-Location-Voitures
│
├── 📄 main.c
├── 📄 voitures.txt
├── 📄 clients.txt
├── 📄 reservations.txt
├── 📄 README.md
└── 📄 rapport.pdf
```

---

# ⚙️ Fonctionnalités Principales

## 🚘 Gestion des Voitures

* Ajouter une voiture
* Modifier une voiture
* Supprimer une voiture
* Afficher toutes les voitures
* Afficher les voitures disponibles triées
* Rechercher une voiture par marque

---

## 👤 Gestion des Clients

* Ajouter un client
* Modifier un client
* Supprimer un client
* Afficher tous les clients
* Consulter l’historique d’un client

---

## 📋 Gestion des Réservations

* Nouvelle réservation
* Retour d’un véhicule
* Calcul automatique du prix
* Gestion du paiement
* Affichage des réservations

---

# 💾 Sauvegarde & Chargement

Le programme sauvegarde automatiquement les données dans des fichiers texte :

| Fichier            | Description                 |
| ------------------ | --------------------------- |
| `voitures.txt`     | Données des voitures        |
| `clients.txt`      | Données des clients         |
| `reservations.txt` | Historique des réservations |

✔ Persistance des données
✔ Rechargement automatique au lancement

---

# 🧠 Structures de Données Utilisées

Le projet utilise des **listes chaînées simples** afin de permettre une allocation dynamique de mémoire.

## Structure Voiture

```c
typedef struct Voiture
{
    char marque[50];
    char modele[50];
    char matricule[20];
    char categorie;
    int kilometrage;
    int disponible;
} Voiture;
```

---

## Structure Client

```c
typedef struct Client
{
    char nom[100];
    char cin[20];
    char telephone[20];
} Client;
```

---

## Structure Reservation

```c
typedef struct Reservation
{
    int idReservation;
    char cin[20];
    char matricule[20];
    int duree;
    int kmParcourus;
    float prix;
    char modePaiement[30];
    int active;
} Reservation;
```

---

# 🔍 Algorithmes Implémentés

## 🔹 Recherche Linéaire — `O(n)`

Le système parcourt les listes chaînées pour :

* rechercher une voiture
* rechercher un client
* rechercher une réservation

---

## 🔹 Tri à Bulles — `O(n²)`

Les voitures disponibles sont triées par kilométrage croissant.

```c
if (tab[j].kilometrage > tab[j + 1].kilometrage)
{
    Voiture temp = tab[j];
    tab[j] = tab[j + 1];
    tab[j + 1] = temp;
}
```

---

# 💰 Calcul de Facturation

Le prix total est calculé automatiquement selon :

```math
Prix = (Durée × Tarif Catégorie) + (KM × 0.5)
```

## Tarifs

| Catégorie | Tarif  |
| --------- | ------ |
| A         | 150 DH |
| B         | 250 DH |
| C         | 400 DH |

---

# 📸 Exemple d’Exécution

## ✅ Ajout d’une Voiture

```bash
============================================================
AJOUTER UNE VOITURE
============================================================

Marque : Renault
Modele : Clio
Matricule : 1234-A-15
Categorie : A
Kilometrage : 45000

SUCCES : Voiture ajoutee.
```

---

## ✅ Facturation

```bash
============================================================
FACTURE
============================================================

Client        : Aymane Bilal
Voiture       : Dacia Logan
Duree         : 3 jours
KM            : 200
Paiement      : Carte Bancaire
TOTAL         : 850.00 DH
```

---

# 🛡️ Sécurité & Validations

✔ Vérification des doublons de matricule
✔ Vérification des CIN existants
✔ Validation des catégories A/B/C
✔ Validation des kilomètres positifs
✔ Blocage de suppression si réservation active
✔ Gestion mémoire avec `malloc()` et `free()`

---

# 🧹 Gestion Mémoire

Le programme libère toute la mémoire avant de quitter :

```c
free(tmp);
```

✔ Aucun memory leak
✔ Allocation dynamique optimisée

---

# 🏗️ Compilation

## ▶ Sous Linux / Mac

```bash
gcc main.c -o gestion
./gestion
```

---

## ▶ Sous Windows (MinGW)

```bash
gcc main.c -o gestion.exe
gestion.exe
```

---

# 📚 Concepts C Utilisés

* Structures
* Pointeurs
* Listes chaînées
* Allocation dynamique
* Fichiers texte
* ANSI Colors
* Modularité
* Tableaux
* Fonctions
* Boucles
* Conditions
* Gestion mémoire

---

# 🚀 Améliorations Futures

* Interface graphique (GUI)
* Base de données SQLite
* Authentification Admin
* Statistiques de location
* Export PDF des factures
* Système multi-utilisateurs
* Gestion des dates réelles

---

# 👨‍💻 Réalisé Par

## 🎓 EMSI — 2ème Année Préparatoire

### 👤 Aymane Bilal

### 👤 Aya Kasmi

---

# 📖 Bibliographie

* The C Programming Language — Kernighan & Ritchie
* Documentation ANSI C
* Cours EMSI 2025/2026
* cppreference.com

---

<div align="center">

# ⭐ Merci d’avoir visité ce projet !

Si le projet vous plaît, n’hésitez pas à laisser une ⭐ sur GitHub.

</div>
