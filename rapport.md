# Laboratoire 2 : Bogosort

Auteur: Camille Koestli

## Description des fonctionnalités du logiciel
Ce logiciel implémente l'algorithme Bogosort déterministe. Il s'agit d'un algorithme de tri qui va véri toutes les permutations possibles d'une séquence et va vérifier si elles sont triées. L'objectif de ce laboratoire est donc de paralléliser les différentes permutations en utilisant plusieurs threads. Chaque thread travaille sur différentes permutations. Dès qu'un thread trouve la séquence triée, tous les autres threads s'arrêtent. Les threads mettent à jour la barre de progression en fonction de leur avancement.

Dans le logiciel, nous pouvons définir le nombre de threads à utiliser, le seed ainsi que la longueur de la séquence.

## Choix d'implémentation
### Décomposition du travail des threads
Pour réaliser ce laboratoire, j'ai choisi de diviser le nombre total de permutations de la séquence entre plusieurs threads. Chaque thread prend en charge un intervalle de permutations et vérifie si l'une des permutations de son intervalle est triée. Dès qu'un thread trouve une permutation triée, il met à jour une variable partagée `finished` pour indiquer aux autres threads de s'arrêter.

### Gestion des threads
La fonction `startSorting` crée et gère la synchronisation des threads.
- Elle calcule le nombre total de permutations possibles de la séquence (en utilisant la factorielle).
- Elle divise ce total par le nombre de threads pour déterminer combien de permutations chaque thread doit traiter.
- Chaque thread traite un intervalle de permutations spécifique.
- Le dernier thread reçoit en plus toutes les permutations restantes, si le total n'est pas divisible par le nombre de threads.
- Après avoir lancé tous les threads, `startSorting` attend que chacun ait terminé son travail en utilisant la méthode `join()`.

### Gestion de la progression
La fonction `incrementPercentComputed()` est utilisée pour mettre à jour la progression. Chaque thread met à jour son avancement en fonction de la proportion de permutations qu'il a déjà traitées par rapport à l'ensemble des permutations qui lui sont assignées.

### Tri Bogosort déterministe
L'algorithme est implémenté dans la fonction `bogosort`. La fonction va devoir :
- Générer la k-ième permutation à partir de l'indice (en utilisant la fonction `getPermutation`).
- Vérifier si cette permutation est triée.
  - Si oui, mettre à jour la séquence triée.
  - Si non, continuer à traiter les permutations suivantes dans son intervalle.

### Concurrence
Après considération des variables partagées, voici les variables qui pourraient poser problème :
- `pManager.finished` : accès seulement en lecture par tous les thread. L'accès en écriture se fera seulement si un thread trouve la séquence triée.
- `*sortedSeq` : normalement, le seul thread qui écrit dedans est le thread avec la séquence triée. Le cas limite est si la séquence possède plusieurs fois les mêmes nombres, mais comme la séquence triée sera la même entre les threads, ça ne devrait pas poser problème. 

## Tests effectués

| Longueur | Threads | Objectif                                                                     |
| -------- | ------- | ---------------------------------------------------------------------------- |
| 3        | 1       | Tester l'algorithme bogosort déterministe                                    |
| 6        | 9       | Tester l'algorithme bogosort déterministe plus complexe                      |
| 10       | 800     | Tester capacité du programme avec beaucoup de threads et une grande séquence |
| 10       | 4       | Tester capacité du programme avec une grande séquence                        |
| 3        | 10      | Tester le programme lorsqu'il y a plus de threads que de permutations        |
| 7        | 13      | Tester la répartition inégale des permutations                               |

### Log de tests

**Test avec 3 éléments générés aléatoirement et 10 threads**
Il n'y a que 6 threads qui démarre vu qu'on en a besoin que de 6 sur les 10.

  ```
  Lancement threads 0 nombre permutation 1
  startIdx 0 endIdx 0
  Lancement threads 1 nombre permutation 1
  startIdx 1 endIdx 1
  Lancement threads 2 nombre permutation 1
  startIdx 2 endIdx 2
  Lancement threads 3 nombre permutation 1
  startIdx 3 endIdx 3
  Lancement threads 4 nombre permutation 1
  startIdx 4 endIdx 4
  Lancement threads 5 nombre permutation 1
  startIdx 5 endIdx 5
  ```

**Test avec 7 éléments générés aléatoirement et 13 threads (total non divisible)**
Le dernier thread récupère toutes les dernières permutations : 5039 - 4466 = 395. Il aura dont 395 permutation alors que les autres en ont 387.

```
Lancement threads 0 nombre permutation 387
startIdx 0 endIdx 386
Lancement threads 1 nombre permutation 387
startIdx 387 endIdx 773
Lancement threads 2 nombre permutation 387
startIdx 774 endIdx 1160
Lancement threads 3 nombre permutation 387
startIdx 1161 endIdx 1547
Lancement threads 4 nombre permutation 387
startIdx 1548 endIdx 1934
Lancement threads 5 nombre permutation 387
startIdx 1935 endIdx 2321
Lancement threads 6 nombre permutation 387
startIdx 2322 endIdx 2708
Lancement threads 7 nombre permutation 387
startIdx 2709 endIdx 3095
Lancement threads 8 nombre permutation 387
startIdx 3096 endIdx 3482
Lancement threads 9 nombre permutation 387
startIdx 3483 endIdx 3869
Lancement threads 10 nombre permutation 387
startIdx 3870 endIdx 4256
Lancement threads 11 nombre permutation 387
startIdx 4257 endIdx 4643
Lancement threads 12 nombre permutation 387
startIdx 4644 endIdx 5039
```