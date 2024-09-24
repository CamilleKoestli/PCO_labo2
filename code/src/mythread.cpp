
#include "mythread.h"
#include <iostream>

void bogosort(std::vector<int> seq, ThreadManager* pManager /* TODO */)
{
    // TODO

    // Exemple de mise à jour de la barre de progression
    pManager->incrementPercentComputed((double)1);
}
