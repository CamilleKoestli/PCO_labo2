/**
  \file mythread.h
  \author Guillaume Chacun
  \date 28.08.2024
  \brief Code qui définit le comportement des threads qui trient un vecteur
  avec l'algorithme Bogosort déterministe.


  Ce fichier contient la définition du comportement des threads qui trient
  un vecteur avec l'algorithme Bogosort déterministe.
*/

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pcosynchro/pcothread.h>

#include "threadmanager.h"


/**
 * @brief bogosort Trie une séquence avec l'algorithme Bogosort déterministe en parallèle
 * @param seq séquence à trier
 * @param pManager Pointeur sur le ThreadManager utilisé pour accéder à l'interface
 * @param startIdx index de début de la séquence à trier
 * @param endIdx index de fin de la séquence à trier
 * @param sortedSeq séquence triée
 * @param totalPerm nombre total de permutations
 */
void bogosort(std::vector<int> seq, ThreadManager *pManager, unsigned startIdx, unsigned endIdx, std::vector<int>* sortedSeq, unsigned totalPerm);

/**
 * @brief getPermutation Retourne la k-ième permutation d'une liste
 * @param list liste d'entiers
 * @param k index de la permutation
 * @return k-ième permutation
 */
std::vector<int> getPermutation(std::vector<int> list, int k);

/**
 * @brief factorial Calcule la factorielle d'un entier
 * @param n entier
 * @return factorielle de n
 */
int factorial(int n);

#endif // MYTHREAD_H
