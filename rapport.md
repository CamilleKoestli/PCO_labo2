# Laboratoire 2 : Bogosort

Auteur: Camille Koestli

## Description des fonctionnalités du logiciel
Ce logiciel implémente l'algorithme Bogosort. Il s'agit d'un algorithme de tri qui se base sur la génération aléatoire d'une séquence jusqu'à ce qu'elle soit triée. L'objectif de ce laboratoire est donc de paralléliser les tris en utilisant plusieurs threads. Chaque thread travaille sur la séquence. Dès qu'un thread trouve la séquence triée, tous les autres threads s'arrêtent. Le programme met à jour la barre de progression.

Dans le logiciel, nous pouvons définir le nombre de threads à utiliser, les seeds ainsi que la longueur de la séquence.


## Choix d'implémentation
Pour réaliser ce laboratoire, j'ai choisi de divisier le travail sur plusieurs threads qui exécutent individuellement le tri sur la même séquence. Chaque thread mélange la séquence de manière aléatoire jusqu'à ce qu'un thread termine le tri.

### Explication des tâches
- Gestion des threads : La fonction `startSorting` crée et gère les threads.
- Tri Bogosort : Chaque thread va exécuter la fonction `bogosort`, qui s'occupe de mélanger la séquence et vérifie si elle est triée en passant la variable `finished` à `true`.

## Tests effectués


Description de chaque test, et information sur le fait qu'il ait passé ou non