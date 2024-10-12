
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

    std::vector<int> seqSorting;

    std::vector<PcoThread*> threads;
    //QVector<std::vector<int>> results(nbThreads);
    
    unsigned totalPerm = factorial(seq.size());
    
    unsigned permsPerThread = ceil((double)totalPerm / (double)nbThreads);
    

    // Lancement des threads
    for (unsigned int i = 0; i < nbThreads; i++){
        PcoThread* thread = new PcoThread(bogosort, seq, this, i * permsPerThread, (i + 1) * permsPerThread - 1, &seqSorting);
        threads.push_back(thread);
        
        //TODO last thread
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
