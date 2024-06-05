#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titre[50];
    char auteur[50];
    int prix;
    int ISBN;
    struct Livre *next;
} Livre;

typedef struct {
    char nom[20];
    char prenom[20];
    char adresse_email[50];
    struct emprunteurs *next;
} emprunteurs;

typedef struct {
    int taille;
    emprunteurs *debut;
    emprunteurs *fin;
} List_emprunteur;

typedef struct {
    Livre *sommet;
    int taille;
} Pile_Livres;

void ajouter_emprunteurs(List_emprunteur *L, char N[20], char PN[20], char AE[50]) {
    emprunteurs *Nouvel_emprunt = (emprunteurs *)malloc(sizeof(emprunteurs));
    strcpy(Nouvel_emprunt->nom, N);
    strcpy(Nouvel_emprunt->prenom, PN);
    strcpy(Nouvel_emprunt->adresse_email, AE);
    Nouvel_emprunt->next = NULL;
    if (L->debut == NULL) {
        L->debut = Nouvel_emprunt;
        L->fin = Nouvel_emprunt;
    } else {
        L->fin->next = Nouvel_emprunt;
        L->fin = Nouvel_emprunt;
    }
    L->taille++;
    printf("L'emprunteur %s %s a été ajouté avec succès.\n", N, PN);
}

void supprimer_emprunteur(List_emprunteur *L, char nom[20], char prenom[20]) {
    emprunteurs *courant = L->debut;
    emprunteurs *precedent = NULL;

    while (courant != NULL) {
        if (strcmp(courant->nom, nom) == 0 && strcmp(courant->prenom, prenom) == 0) {
            if (precedent == NULL) {
                L->debut = courant->next;
            } else {
                precedent->next = courant->next;
            }
            free(courant);
            L->taille--;
            return;
        }
        precedent = courant;
        courant = courant->next;
    }
    printf("L'emprunteur %s %s n'a pas été trouvé.\n", nom, prenom);
}

void afficherListeEmprunteurs(List_emprunteur *L) {
    if (L->taille <= 1) {
        printf("La liste des emprunteurs est vide.\n");
    } else {
        emprunteurs *courant = L->debut;
        while (courant != NULL) {
            printf("Nom : %s\n", courant->nom);
            printf("Prénom : %s\n", courant->prenom);
            printf("Adresse e-mail : %s\n", courant->adresse_email);
            courant = courant->next;
        }
    }
}

void ajouter_livre(Pile_Livres *pile, char titre[20], char auteur[20], int prix, int ISBN) {
    Livre *Nouvel_Livre;
    Nouvel_Livre = (Livre *)malloc(sizeof(Livre));
    strcpy(Nouvel_Livre->titre, titre);
    strcpy(Nouvel_Livre->auteur, auteur);
    Nouvel_Livre->prix = prix;
    Nouvel_Livre->ISBN = ISBN;
    Nouvel_Livre->next = pile->sommet;
    pile->sommet = Nouvel_Livre;
    pile->taille++;
}

void supprimer_livre(Pile_Livres *pile, char titre[20]) {
    Livre *temps = NULL;
    Livre *courant = pile->sommet;
    Livre *P = NULL;

    if (strcmp(courant->titre, titre) == 0) {
        pile->sommet = courant->next;
        free(courant);
        pile->taille--;
        return;
    }

    while (courant != NULL && courant->next != NULL) {
        P = courant->next;
        if (strcmp(P->titre, titre) == 0) {
            temps = courant->next;
            courant->next = P->next;
            free(temps);
            pile->taille--;
            return;
        }
        courant = courant->next;
    }
}

void afficherListeLivres(Pile_Livres *pile) {
    if (pile->taille <= 1) {
        printf("La pile est vide.\n");
    } else {
        Livre *courant = pile->sommet;
        while (courant != NULL) {
            printf("Titre : %s\n", courant->titre);
            printf("Auteur : %s\n", courant->auteur);
            printf("Prix : %d\n", courant->prix);
            printf("ISBN : %d\n", courant->ISBN);
            courant = courant->next;
        }
    }
}

void afficherLivresParAuteur(Pile_Livres *pile, char auteur[20]) {
    int found = 0;
    Livre *courant = pile->sommet;

    while (courant != NULL) {
        if (strcmp(courant->auteur, auteur) == 0) {
            found = 1;
            printf("Titre : %s\n", courant->titre);
            printf("Auteur : %s\n", courant->auteur);
            printf("Prix : %d\n", courant->prix);
            printf("ISBN : %d\n", courant->ISBN);
            printf("\n");
        }
        courant = courant->next;
    }

    if (!found) {
        printf("L'auteur %s n'a pas d'œuvres répertoriées.\n", auteur);
    }
}

void emprunter_livre(Pile_Livres *pile, char titre[20]) {
    Livre *courant = pile->sommet;

    while (courant != NULL) {
        if (strcmp(courant->titre, titre) == 0) {
            printf("Le livre %s a été emprunté.\n", titre);
            supprimer_livre(pile, titre);
            return;
        }
        courant = courant->next;
    }
    printf("Le livre %s n'a pas été trouvé.\n", titre);
}

void rendre_livre(Pile_Livres *pile, char titre[20]) {
    Livre *Nouvel_Livre;
    Nouvel_Livre = (Livre *)malloc(sizeof(Livre));
    strcpy(Nouvel_Livre->titre, titre);
    Nouvel_Livre->next = pile->sommet;
    pile->sommet = Nouvel_Livre;
    pile->taille++;
}

int main() {
    char auteur[20], titre[20], nom[20], prenom[20], adresse_email[50];
    int choix = 0, choix1 = 0, choix2 = 0, n = 0, prix = 0, ISBN = 0;
    List_emprunteur list = {0, NULL, NULL};
    Pile_Livres pile = {NULL, 0};

    do {
        printf("**************************************************\n");
        printf("Taper 1 pour lister les paramétres d'emprunteurs :\n");
        printf("Taper 2 pour lister les paramétres des livres :\n");
        printf("Taper 3 pour quitter\n");
        printf("*****************************************************\n");
        printf("Saisissez votre choix :");
        scanf("%d", &choix);

        switch (choix) {
            case 1 : {
                do{
                printf("**************************************************\n");
                printf("Apuyer sur 1 pour ajouter un emprunteur.\n");
                printf("Apuyer sur 2 pour afficher la liste des emprunteurs.\n");
                printf("Apuyer sur 3 pour supprimer un emprunteur.\n");
                printf("Apuyer sur 4 pour compter le nombre des emprunteurs.\n");
                printf("Apuyer 5 pour quitter\n");
                printf("**************************************************\n");
                printf("Saisissez votre choix :");
                scanf("%d", &choix1);
                switch (choix1) {
                    case 1:{
                        printf("Entrez le nom de l'emprunteur :");
                        scanf(" %[^\n]s", nom);
                        printf("Entrez le prénom de l'emprunteur :");
                        scanf(" %s", prenom);
                        printf("Entrez l'adresse e-mail de l'emprunteur :");
                        scanf(" %s", adresse_email);
                        ajouter_emprunteurs(&list, nom, prenom, adresse_email);
                        break;}
                    case 2:{
                        printf("Liste des emprunteurs :\n");
                        afficherListeEmprunteurs(&list);
                        break;}
                    case 3:{
                        printf("Entrez le nom de l'emprunteur à supprimer :");
                        scanf(" %s", nom);
                        printf("Entrez le prénom de l'emprunteur à supprimer :");
                        scanf(" %s", prenom);
                        supprimer_emprunteur(&list, nom, prenom);
                        break;}
                    case 4:{
                        printf("Le nombre d'emprunteurs est : %d\n", list.taille);
                        break;}
                }
            }while(choix1!=5);
    break;  }

            case 2 : {
                do{
                printf("**************************************************\n");
                printf("Apuyer sur 1 pour ajouter un livre.\n");
                printf("Apuyer sur 2 pour afficher les livres disponibles.\n");
                printf("Apuyer sur 3 pour afficher les livres d'un auteur.\n");
                printf("Apuyer sur 4 pour compter le nombre des livres.\n");
                printf("Apuyer sur 5 pour emprunter un livre.\n");
                printf("Apuyer sur 6 pour rendre un livre.\n");
                printf("Apuyer 7 pour quitter\n");
                printf("**************************************************\n");
                printf("Saisissez votre choix :");
                scanf("%d", &choix2);
                switch (choix2) {
                    case 1:{
                        printf("Combien de livres vous souhaitez ajouter :");
                        scanf("%d", &n);
                        for (int i = 0; i < n; i++) {
                            printf("***************************************\n");
                            printf("Entrer les détails du livre numéro %d :\n", i + 1);
                            printf("***************************************\n");
                            printf("Titre :");
                            scanf(" %[^\n]s", titre);
                            printf("Auteur :");
                            scanf(" %[^\n]s", auteur);
                            printf("Prix :");
                            scanf("%d", &prix);
                            printf("ISBN :");
                            scanf("%d", &ISBN);
                            ajouter_livre(&pile, titre, auteur, prix, ISBN);
                        }
                        break;
                    }
                    case 2: {
                        printf("Liste des livres disponibles :\n");
                        afficherListeLivres(&pile);
                        break;}
                    case 3:{
                        printf("Saisissez le nom de l'auteur :");
                        scanf(" %[^\n]s", auteur);
                        afficherLivresParAuteur(&pile, auteur);
                        break;
                    case 4:
                        printf("Le nombre de livres est : %d\n", pile.taille);
                        break;}
                    case 5:{
                        printf("Saisissez le titre du livre à emprunter :");
                        scanf(" %[^\n]s", titre);
                        emprunter_livre(&pile, titre);
                        break;}
                    case 6:{
                        printf("Saisissez le titre du livre à rendre :");
                        scanf(" %[^\n]s", titre);
                        rendre_livre(&pile, titre);
                        break;}
                }
            }while(choix2!=7);
       break; }
        }
    } while (choix != 3);
    return 0;
}
