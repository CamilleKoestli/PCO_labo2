
#include "mythread.h"
#include <iostream>

void bogosort(std::vector<int> seq, ThreadManager* pManager /* TODO */)
{

    // Vérification si la séquence est triée
    if (isSorted(seq)){
        pManager->requestStop();
        return;
    }

    // Exemple de mise à jour de la barre de progression
    pManager->incrementPercentComputed((double)1);
}


std::vector<int> ThreadManager::startSorting(std::vector<int> seq, unsigned int nbThreads){
    // TODO
    return seq;
}

bool isSorted(const std::vector<int>& seq) {
    return std::is_sorted(seq.begin(), seq.end());
}