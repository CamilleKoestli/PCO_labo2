# Laboratoire 2 : Bogosort

Auteur: Camille Koestli

## Description des fonctionnalités du logiciel
Ce logiciel implémente l'algorithme Bogosort déterministe. Il s'agit d'un algorithme de tri qui va chercher toutes les permutations possibles d'une séquence et va les vérifier si elles sont triées. L'objectif de ce laboratoire est donc de paralléliser les différentes permutations en utilisant plusieurs threads. Chaque thread travaille sur différentes permutations. Dès qu'un thread trouve la séquence triée, tous les autres threads s'arrêtent. Le programme met à jour la barre de progression.

Dans le logiciel, nous pouvons définir le nombre de threads à utiliser, les seeds ainsi que la longueur de la séquence.


## Choix d'implémentation
### Décomposition du travail des threads
Pour réaliser ce laboratoire, j'ai choisi de diviser le nombre total de permutations de la séquence entre plusieurs threads. Chaque thread prend en charge un intervalle de permutations et vérifie si l'une des permutations de son intervalle est triée. Dès qu'un thread trouve une permutation triée, il met à jour une variable partagée `finished` pour indiquer aux autres threads de s'arrêter.

### Gestion des threads
La fonction `startSorting` crée et gère la synchronisation des threads.
- Elle calcule le nombre total de permutations possibles de la séquence (en utilisant la factorielle).
- Elle divise ce total par le nombre de threads pour déterminer combien de permutations chaque thread doit traiter.
- Chaque thread traite un intervalle de permutations spécifique.
- Le dernier thread reçoit toutes les permutations restantes, si le total n'est pas divisible par le nombre de threads.
- Après avoir lancé tous les threads, startSorting attend que chacun ait terminé son travail en utilisant la méthode join().

### Gestion de la progression
La fonction `incrementPercentComputed()` est utilisée pour mettre à jour la progression. Chaque thread met à jour son avancement en fonction de la proportion de permutations qu'il a déjà traitées par rapport à l'ensemble des permutations qui lui sont assignées.

### Tri Bogosort déterministe
L'algorithme est implémenté dans la fonction `bogosort`. La fonction va devoir :
- Générer la k-ième permutation à partir de l'indice (en utilisant la fonction getPermutation).
- Vérifier si cette permutation est triée.
  - Si oui, mettre à jour la séquence triée et arrête les threads.
  - Si non, continuer à traiter les permutations suivantes dans son intervalle.

## Tests effectués
**Test avec une séquence de 3 éléments et un thread**
- Description : Une séquence de 3 éléments si le tri fonctionne correctement avec un petit ensemble de permutations et un seul thread.
- Résultat : OK

**Test avec une séquence de 6 éléments et 9 threads**
- Description : Une séquence de 6 éléments si le tri fonctionne correctement avec un plus grand ensemble de permutations et plusieurs threads.
- Résultat : OK

**Test avec une séquence de 15 éléments et 1000 threads**
- Description : Une séquence de 15 éléments si le tri fonctionne correctement avec un plus grand ensemble de permutations et plusieurs threads.
- Résultat : OK

**Test avec une séquence de 15 éléments et 999 threads**
- Description : Une séquence de 15 éléments si le tri fonctionne correctement avec un plus grand ensemble de permutations et plusieurs threads.
- Résultat : OK