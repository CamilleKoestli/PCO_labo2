
#include <QRandomGenerator>
#include <iostream>
#include <cmath>

#include "threadmanager.h"
#include "mythread.h"



ThreadManager::ThreadManager(QObject *parent) :
    QObject(parent)
{}


/**
 * @brief Cette fonction trie une séquence générée aléatoirement
 * @param seq séquence à trier
 * @param nbThreads le nombre de threads à lancer
 * @return séquence triée
 */
std::vector<int> ThreadManager::startSorting(
        std::vector<int> seq,
        unsigned int nbThreads
)
{
    finished = false;
    
    // TODO création des threads et du vecteur de résultats
    // TODO lancement des threads avec la fonction Bogosort
    // TODO arrêt des threads et récupération du tableau trié
    // TODO retourner le tableau trié

    // Création du résultat du vecteur trié
    std::vector<int> seqSorting;

    // Liste de tous les threads
    std::vector<PcoThread*> threads;

    // Calcul du nombre total de permutations    
    unsigned totalPerm = factorial(seq.size());
    
    // Calcul le nombre de permutations par thread
    unsigned permsPerThread = ceil((double)totalPerm / (double)nbThreads);
    

    // Lancement des threads
    for (unsigned int i = 0; i < nbThreads; i++){

        unsigned startIdx = i * permsPerThread;
        unsigned endIdx = (i + 1) * permsPerThread - 1;
        
        // Si c'est le dernier thread, il prend les permutations restantes
        if (i == nbThreads - 1) {
            endIdx = totalPerm - 1;
        }
        PcoThread* thread = new PcoThread(bogosort, seq, this, startIdx, endIdx, &seqSorting);
        threads.push_back(thread);
    }

    // Arrêt de tous les threads
    for (PcoThread* thread : threads) {
        thread->join(); 
        delete thread; 
    }

    return seqSorting; 
}


void ThreadManager::incrementPercentComputed(double percentComputed)
{
    emit sig_incrementPercentComputed(percentComputed);
}
