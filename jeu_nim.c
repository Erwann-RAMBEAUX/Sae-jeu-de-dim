#include<stdio.h>
#include<stdlib.h>
#include<time.h>

///////
////    Define
///////

#define Taille (nombre >= MIN && nombre <= MAX)
#define Niv (niveau >= Niv_MIN && niveau <= Niv_MAX)
#define Nb_Case (parametre.nlig * parametre.ncol)

///////
////    Structure
///////
typedef struct
{
    int ligne;
    int colonne;
} T_Case;

typedef struct
{
    T_Case voisins[4];
    int nb_voisine;
} T_Tab_Case;


typedef struct
{
    int nlig;
    int ncol;
    int niveau;
    int next;
} Parametre;


///////
////    Fontions
///////

int Verification_Taille()
{
    int nombre;
    int MAX = 30, MIN = 5;              //Nombre de lignes et colonnes max et min
    scanf("%d", &nombre);
    while (!Taille)                     // simple boucle de vérif
    {
        printf("\n Valeur impossible \nEntrer un nombre entre %d et %d inclus :", MIN, MAX);
        scanf("%d", &nombre);
    } 
    return nombre;
}

int Verification_Niveau()
{
    int niveau;
    int Niv_MAX = 4, Niv_MIN = 1;    //Niveau max et min
    scanf("%d", &niveau);
    while (!Niv)                    // simple boucle de vérif
    {
        printf("\n Niveau demandé impossible \nLe niveau va de 1 à 4 :");
        scanf("%d", &niveau);
    }
    return niveau;
}

int Verification_Joueur()
{
    int joueur;
    scanf("%d", &joueur);
    while (joueur != 1 && joueur != 2) // simple boucle de vérif du joueur qui commence
    {
        printf("\n Le joueur selectionné n'extiste pas \nOrdi (1) Vous (2) : ");
        scanf("%d", &joueur);
    }
    getchar();
    return joueur;
}

void Lire_Entier(Parametre *parametre)        // Fonction pour définir tout les paramètres
{
    printf("Combien de lignes voulez-vous : ");    
    parametre->nlig = Verification_Taille();        // Vérif du nombre de lignes

    printf("Combien de colonnes voulez-vous : ");   // Vérif du nombres de colonnes
    parametre->ncol = Verification_Taille();

    printf("\nNiveau de l'Ordi \n1 : débutant \n2 : moyen \n3 : expert \n4 : virtuose \nNiveau : ");    
    parametre->niveau = Verification_Niveau();      // Vérif du niveau de l'Ordi

    printf("\nQui commence ? (Ordinateur : 1, Vous : 2) : ");
    parametre->next = Verification_Joueur();        // Vérif du joueur qui commence
}

void Voisine(T_Case pion, T_Tab_Case *voisine, Parametre parametre) // Donne les cases voisines d'une case
{
    int compteur = 0;
    if (parametre.nlig - pion.ligne >= 1)       // Vérification pour les voisines sur la ligne
    {
        voisine->voisins[compteur].ligne = pion.ligne + 1;
        voisine->voisins[compteur].colonne = pion.colonne;
        compteur += 1;
        if (parametre.nlig - pion.ligne >= 2)       // Vérification si il y a 2 voisines sur la ligne
        {
            voisine->voisins[compteur].ligne = pion.ligne + 2;
            voisine->voisins[compteur].colonne = pion.colonne;
            compteur += 1;
        }
    }
    if (parametre.ncol - pion.colonne >= 1)     // Vérification pour les voisines sur la colonne 
    {
        voisine->voisins[compteur].colonne = pion.colonne + 1;
        voisine->voisins[compteur].ligne = pion.ligne;
        compteur += 1;
        if (parametre.ncol - pion.colonne >= 2)     // Vérification si il y a 2 voisines sur la colonne
        {
            voisine->voisins[compteur].colonne = pion.colonne + 2;
            voisine->voisins[compteur].ligne = pion.ligne;
            compteur += 1;
        }
    }
    voisine->nb_voisine = compteur;
}

void Init_Pion(T_Case *pion)        //Initialise le placement du pion
{
    pion->colonne = 1;
    pion->ligne = 1;
}

void Affichage_Plateau(T_Case pion, Parametre parametre)        // Affiche le plateau
{
    int ligne, colonne;
    for(ligne = 0; ligne <= parametre.nlig; ligne++)        // boucle de ligne
    {
        printf("\n");
        if (ligne == 0)     // if permettant d'afficher l'indice des colonne
        {
            printf("   \t");
            for(colonne = 1; colonne <= parametre.ncol; colonne++)
            {
                printf("%2d \t", colonne);                  
            }
        }
        else
        {
            for (colonne = 0; colonne <= parametre.ncol; colonne++)
            {
                if (colonne == 0)   // if permettant d'afficher l'indice des lignes
                {
                   printf("%d\t", ligne);
                }
                else if (ligne == pion.ligne && colonne == pion.colonne) // if permettant d'afficher l'emplacement du pion
                {
                    printf("\e[1;38;5;208m|♟️|\e[0m\t");        // Affiche le pion ainsi que la case sur laquelle il se trouve en orange 
                }
                else
                {
                    printf("\e[1;38;5;26m|-|\e[0m\t");      // Affiche les cases en bleu
                }
            }
        }
        printf("\n");
    }
}

int Nimber(T_Case voisine, Parametre parametre) // Calcul le nimber d'une case
{
    if ((parametre.nlig-voisine.ligne)%3 - ((parametre.ncol-voisine.colonne)%3) == 0) // formule qui trouve si la case est le nimber
        {
            return 0;
        }
    return 1;
}

void Coup_joueur(T_Case *pion, T_Tab_Case voisine) // propose les coup possible au joueur
{
    char val;
    int possible = 0;
    int position;
    printf("Choisir la destination : ");
    for (int compteur = 0; compteur < voisine.nb_voisine; compteur++)       // Boucle qui permet d'afficher les destinations possibles pour jouer son coup
    {
        printf("%d:(%d,%d)  ", compteur+1, voisine.voisins[compteur].ligne,voisine.voisins[compteur].colonne);
    }
    printf("\n");
    printf("Destination choisi :");     
    while (!possible)           // Boucle qui tourne le temps que le coup choisit soit possible
    {
        char test[30];      // Variable temporaire pour l'input
        val = atoi(fgets(test, sizeof(test), stdin));   // Permet de convertir la valeur entrer en int
        for (int compteur = 1; compteur <= voisine.nb_voisine; compteur++)  // Boucle pour vérfier si l'input est un coup possible
        {   
            if (val == compteur)
            {
                possible = 1;                      
                position = compteur;
                break;
            }
        }
        if (!possible)
        {
            printf("Erreur!!!\n");
            printf("Destination choisi :");
        }
    }
    pion->ligne = voisine.voisins[position-1].ligne;        // Déplace le pion sur le coup choisit
    pion->colonne = voisine.voisins[position-1].colonne;
    printf("\a");                                           // Fait un bip pour dire que le pion a été déplacé
}   

void Coup_Ordi_Hasard(T_Case *pion, T_Tab_Case voisine) // gère le coup au hasard de l'ordi
{
    int random = rand()%voisine.nb_voisine+1;   // Nombre aléatoire entre 1 et le nombre de voisine pour choisir le coup aléatoire
    pion->ligne = voisine.voisins[random-1].ligne;  // On déplace le pion par rapport à la voisine (-1 car on ne prend pas en compte l'emplacement de tab[0] dans le random au dessus)
    pion->colonne = voisine.voisins[random-1].colonne;
    printf("\nL'ordinateur déplace le pion en (%d,%d)\n", pion->ligne, pion->colonne);
}

void Coup_Ordi_Gagnant(T_Case *pion, T_Tab_Case voisine, Parametre parametre) // gère le coup gagnant de l'ordi
{
    int compteur;
    int reussi = 0;                             // Permet de savoir si l'ordi a jouer un coup ou nan
    for (compteur = 1; compteur <= voisine.nb_voisine; compteur++)
    {
        if (Nimber(voisine.voisins[compteur-1], parametre) == 0)       //Fonction qui vérifie le nimber
        {
            pion->ligne = voisine.voisins[compteur-1].ligne;
            pion->colonne = voisine.voisins[compteur-1].colonne;
            reussi = 1;
            printf("\nL'ordinateur déplace le pion en (%d,%d)\n", pion->ligne, pion->colonne);
            break;
        }
    }
    if (!reussi)
        Coup_Ordi_Hasard(pion, voisine);   // Si l'ordi n'a pas jouer il joue un coup au hasard
}

int Hasard(Parametre parametre, T_Case *pion) // Retourne un nombre aléatoire pour choisir si l'ordi joue au hasard ou un bon coup
{
    int aleatoire = rand()%3+1; // Nombre aléatoire entre 1 et 3 pour savoir si le coup de l'ordi sera aléatoire ou alors un coup gagnant
    // Return 1 représene un coup aléatoire
    // Return 2 représente un coup gagnat de l'ordi
    if (parametre.niveau == 1)
    {
        return 1;
    }
    else if (parametre.niveau == 2)
    {
        if (aleatoire == 3)     // Représente 1 chance sur 3 que le coup soit gagnant
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    else if (parametre.niveau == 3)
    {
        if (aleatoire == 1)     // Représente 1 chance sur 3 que le coup soit aléatoire
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 2;
    }
    
}

int Fin(T_Case pion, Parametre parametre)
{
    if (pion.colonne == parametre.ncol && pion.ligne == parametre.nlig)     // Vérification pour savoir si la partie est terminée
    {
        return 1;
    }
    return 0;
}

void Vainqueur(int gagnant)
{
    if (gagnant == 1)       //Vérification du gagant 
    {
        printf("\n\n\e[1;38;5;9mLe vainqueur est l'ordi. Retente ta chance.\e[0m\n");       // Affiche en rouge gras si l'ordi gagne 
    }
    else
    {
        printf("\n\n\e[1;38;5;45mBravo tu as gagné 🏆. \nRejoue contre un ordi plus fort.\e[0m\n");     // Affiche en bleu gras si le joueur gagne
    }
}

void Jouer_Partie() // Joue la partie dans l'ordre choisi
{
    Parametre parametre; 
    Lire_Entier(&parametre);
    T_Case pion;
    Init_Pion(&pion);
    int terminer = 0, gagnant;
    while(!terminer)
    {
        T_Tab_Case voisine;
        if(parametre.next == 1)
        {
            Voisine(pion, &voisine, parametre);
            if (Hasard(parametre, &pion) == 1)  // Vérif si l'ordi doit jouer un coup aléatoire ou un coup gagant
            {
                Coup_Ordi_Hasard(&pion, voisine);
            }
            else
            {
                Coup_Ordi_Gagnant(&pion, voisine, parametre);
            }
            
            if (Fin(pion, parametre))   // Vérification pour savoir si le pion se trouve sur le puit et donc une fin de partie
            {
                Affichage_Plateau(pion, parametre);
                terminer = 1;
                gagnant = 1;            // Gagant 2 represente la victoire du joueur alors que 1 représente la victoire de l'ordi
                break;
            }
            Voisine(pion, &voisine, parametre);
            Affichage_Plateau(pion, parametre);
            Coup_joueur(&pion, voisine);
            if (Fin(pion, parametre))
            {
                Affichage_Plateau(pion, parametre);
                terminer = 1;
                gagnant = 2;
                break;
            }
        }
        else
        {
            Voisine(pion, &voisine, parametre);
            Affichage_Plateau(pion, parametre);
            Coup_joueur(&pion, voisine);
            if (Fin(pion, parametre))
            {
                Affichage_Plateau(pion, parametre);
                terminer = 1;
                gagnant = 2;
                break;
            }
            Voisine(pion, &voisine, parametre);
            if (Hasard(parametre, &pion) == 1)  // Vérif si l'ordi doit jouer un coup aléatoire ou un coup gagant
            {
                Coup_Ordi_Hasard(&pion, voisine);
            }
            else
            {
                Coup_Ordi_Gagnant(&pion, voisine, parametre);
            }
            if (Fin(pion, parametre))
            {
                Affichage_Plateau(pion, parametre);
                terminer = 1;
                gagnant = 1;
                break;
            }
        }
    }
    Vainqueur(gagnant);
}

///////
////    Programme Principal
///////
int main()
{
    srand((unsigned int)time(NULL));
    Jouer_Partie();
}
