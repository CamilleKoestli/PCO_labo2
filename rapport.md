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
**Test avec 3 éléments générés aléatoirement et 1 thread**

- Description : Utilisation d'une séquence de 3 éléments générée aléatoirement, ce qui donne un total de 3! = 6 permutations possibles. Un seul thread est utilisé.
- Objectif : Tester le bon fonctionnement de l'algorithme avec une séquence simple et un seul thread, pour valider l'exécution séquentielle du tri Bogosort.
- Résultat : OK. Le thread a exploré toutes les permutations et a trouvé la permutation triée, terminant le travail correctement.

**Test avec 6 éléments générés aléatoirement et 9 threads**

- Description : Utilisation d'une de 6 éléments est créé aléatoirement, donc 6! = 720 permutations. On utilise 9 threads, chaque thread traite 80 permutations.
- Objectif : Tester le bon fonctionnement du programme avec une séquence un peu plus complexe.
- Résultat : OK.

**Test avec 10 éléments générés aléatoirement 800 threads**

- Description : Utilisation d'une séquence de 10 éléments générée aléatoirement, ce qui donne un total de 10! = 3'628'800 permutations possibles. 800 threads ont été utilisés pour traiter les permutations. Chaque thread traite 4'536 permutations.
- Objectif : Tester la capacité du programme à gérer une grande quantité de permutations avec beaucoup de threads. Ici, chaque thread a été assigné un grand nombre de permutations à traiter.
- Résultat : OK.

**Test avec 10 éléments générés aléatoirement et 4 threads**

- Description : Utilisation d'une séquence de 10 éléments générée aléatoirement, ce qui donne un total de 10! = 3'628'800 permutations possibles en utilisant 4 threads. Chaque thread traite 907'200 permutations.
- Objectif : Tester que le programme peut s'occuper de beaucoup de séquences avec peu de threads et que la répartition du travail est correcte.
- Résultat : OK.

**Test avec 3 éléments générés aléatoirement et 10 threads**

- Description : Utilisation d'une séquence de 3 éléments générée aléatoirement, ce qui donne un total de 3! = 6 permutations, avec 10 threads initialisés. Il y a moins de permutations que de threads, certains threads n'ont pas été démarrés.
- Objectif : Tester le programme lorsqu'il y a plus de threads que de permutations.
- Résultat : OK.
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

- Description : Utilisation d'une séquence de 7 éléments générée aléatoirement, ce qui donne un total de 7! = 5040 permutations en utilisant 13 threads. Ici, le nombre total de permutations n'est pas divisible par le nombre de threads. Chaque thread traite environ 387 permutations.Certaines threads recevront plus de permutations que d'autres.
- Objectif : Tester la répartition inégale des permutations.
- Résultat : OK.