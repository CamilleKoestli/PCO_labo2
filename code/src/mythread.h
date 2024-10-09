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
 */
void bogosort(std::vector<int> seq, ThreadManager* pManager /* TODO */);

/** 
 * @brief startSorting Fonction qui démarre le tri d'une séquence avec l'algorithme Bogosort déterministe
 * @param seq séquence à trier
 * @param nbThreads nombre de threads à utiliser
 */
std::vector<int> ThreadManager::startSorting(std::vector<int> seq, unsigned int nbThreads);

#endif // MYTHREAD_H
