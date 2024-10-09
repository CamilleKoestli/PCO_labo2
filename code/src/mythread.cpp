
#include "mythread.h"
#include <iostream>

void bogosort(std::vector<int> seq, ThreadManager* pManager /* TODO */)
{

    while(!pManager->finished){
        // Génération d'une séquence aléatoire
        std::random_shuffle(seq.begin(), seq.end());

        // Vérification si la séquence est triée
        if (std::is_sorted(seq.begin(), seq.end())){
            pManager->finished = true;
            return;
        }
    }
    // Exemple de mise à jour de la barre de progression
    pManager->incrementPercentComputed((double)1);
}


std::vector<int> ThreadManager::startSorting(std::vector<int> seq, unsigned int nbThreads){
    // TODO
    
    
    return seq;
}