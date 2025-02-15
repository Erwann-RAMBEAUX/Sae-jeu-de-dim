# 🎮 Jeu de Nim  

## 📌 Description  
Ce projet, réalisé dans le cadre de ma 1ère année de BUT Informatique, consiste en l’implémentation d’un **jeu de Nim** en **langage C**.  

### 🕹️ Règles du jeu  
Deux joueurs s’affrontent sur une grille **nlig × ncol** où un pion démarre en position **(1,1)**.  
À tour de rôle, un joueur déplace le pion vers la droite ou vers le bas (1 ou 2 cases).  
Le but ? **Forcer l’adversaire à tomber dans la case finale (nlig, ncol), appelée "le puits".**  
L’ordinateur peut jouer avec différents niveaux de difficulté et utiliser une **stratégie gagnante**.

## 🚀 Fonctionnalités du programme  
- 🎲 Paramétrage du jeu : nombre de lignes, colonnes, niveau de difficulté.  
- 🧠 Intelligence artificielle :  
  - **Débutant** : coups aléatoires.  
  - **Moyen** : coups gagnants avec une proba de 1/3.  
  - **Expert** : coups gagnants avec une proba de 2/3.  
  - **Virtuose** : toujours gagnant.  
- 🎯 Application de la **stratégie gagnante** basée sur les **nimbers**.  
- 💻 Interface en **mode texte** avec affichage dynamique de la grille.  

## 📂 Structure du projet  
```
/Sae-jeu-de-nim
│── nim.c              # Code source du jeu  
│── nim                # Le jeu executable
│── SAE1_02_22_23.pdf  # Fichier de l'objectif du projet
```

## 🛠️ Exécution  
1. Compiler le projet avec **`make`** :  
   ```sh
   ./nim
   ```
