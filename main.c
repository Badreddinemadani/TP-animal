#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct animal
{
    char *nom;
    int nbrpts; // nombre de pattes de l'animal
    struct animal *suivant;
} animal;

// Fonction pour verifier si la pile est vide
bool estVide(animal **sommet)
{
    return *sommet == NULL;
}

// Fonction pour retirer un animal de la pile
struct animal *depiler(animal **sommet)
{
    if (*sommet == NULL)
    {
        printf("Pile vide\n");
        return NULL;
    }
    struct animal *temp = *sommet;
    *sommet = (*sommet)->suivant;
    return temp;
}

// Fonction pour creer un nouvel animal
animal *creerAnimal(char *nom, int nbrpts)
{
    animal *nouvelAnimal = malloc(sizeof(animal));
    nouvelAnimal->nom = nom;
    nouvelAnimal->nbrpts = nbrpts;
    nouvelAnimal->suivant = NULL;
    return nouvelAnimal;
}

// Fonction pour ajouter un animal à la pile
void ajouterAnimal(animal **sommet, char *nom, int nbrpts)
{
    animal *nouvelAnimal = creerAnimal(nom, nbrpts);
    if (*sommet == NULL)
    {
        *sommet = nouvelAnimal;
    }
    else
    {
        nouvelAnimal->suivant = *sommet;
        *sommet = nouvelAnimal;
    }
}

// Fonction pour consulter l'animal en haut de la pile sans le retirer
struct animal *regarder(animal **sommet)
{
    if (*sommet == NULL)
    {
        printf("Pile vide, impossible de regarder\n");
        return NULL;
    }
    return *sommet;
}

// Fonction pour echanger les deux animaux en haut de la pile
void echanger(animal **sommet)
{
    if (*sommet == NULL || (*sommet)->suivant == NULL)
    {
        printf("Impossible d'echanger, la pile contient moins de deux animaux\n");
        return;
    }

    animal *premier = *sommet;
    animal *deuxieme = premier->suivant;

    premier->suivant = deuxieme->suivant;
    deuxieme->suivant = premier;
    *sommet = deuxieme;
}

// Fonction pour dupliquer l'animal en haut de la pile
void dupliquer(animal **sommet)
{
    if (*sommet == NULL)
    {
        printf("La pile est vide, impossible de dupliquer.\n");
        return;
    }

    animal *animalSommet = *sommet;
    animal *nouveauAnimal = creerAnimal(animalSommet->nom, animalSommet->nbrpts);
    nouveauAnimal->suivant = *sommet;
    *sommet = nouveauAnimal;

    printf("Animal duplique et place en haut de la pile.\n");
}

// Fonction pour supprimer les animaux bipèdes (2 pattes) de la pile
void supprimerBipedes(animal **sommet)
{
    if (*sommet == NULL)
    {
        printf("La pile est vide, aucune suppression necessaire.\n");
        return;
    }

    animal *actuel = *sommet;
    animal *precedent = NULL;

    while (actuel != NULL)
    {
        if (actuel->nbrpts == 2)
        {
            if (precedent == NULL)
            {
                *sommet = actuel->suivant;
                free(actuel);
                actuel = *sommet;
            }
            else
            {
                precedent->suivant = actuel->suivant;
                free(actuel);
                actuel = precedent->suivant;
            }
        }
        else
        {
            precedent = actuel;
            actuel = actuel->suivant;
        }
    }

    printf("Animaux bipèdes supprimes de la pile.\n");
}

// Fonction pour afficher les elements de la pile
void afficherPile(animal **sommet)
{
    if (*sommet == NULL)
    {
        printf("La pile est vide.\n");
        return;
    }

    printf("Contenu de la pile :\n");
    animal *actuel = *sommet;
    while (actuel != NULL)
    {
        printf("Nom: %s, Nombre de pattes: %d\n", actuel->nom, actuel->nbrpts);
        actuel = actuel->suivant;
    }
}

int main()
{
    animal *sommet = NULL;

    // Ajouter des animaux à la pile
    ajouterAnimal(&sommet, "Lion", 4);
    ajouterAnimal(&sommet, "Chien", 4);
    ajouterAnimal(&sommet, "Oiseau", 2);

    // Afficher la pile avant les operations
    printf("Pile avant les operations :\n");
    afficherPile(&sommet);

    // Consulter l'animal en haut de la pile sans le retirer
    animal *animalHaut = regarder(&sommet);
    if (animalHaut != NULL)
    {
        printf("\nAnimal en haut de la pile (sans retirer) :\n");
        printf("Nom: %s, Nombre de pattes: %d\n", animalHaut->nom, animalHaut->nbrpts);
    }

    // Echanger les deux animaux en haut de la pile
    echanger(&sommet);

    // Dupliquer l'animal en haut de la pile
    dupliquer(&sommet);

    // Afficher la pile après les operations
    printf("\nPile après les operations :\n");
    afficherPile(&sommet);

    // Supprimer les animaux bipèdes (2 pattes) de la pile
    supprimerBipedes(&sommet);

    // Afficher la pile après la suppression des animaux bipèdes
    printf("\nPile après la suppression des animaux bipèdes :\n");
    afficherPile(&sommet);

    return 0;
}
