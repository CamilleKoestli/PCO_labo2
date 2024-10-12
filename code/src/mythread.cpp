
#include "mythread.h"
#include <iostream>

void bogosort(std::vector<int> seq, ThreadManager *pManager /* TODO */)
{

    // TODO
    while (!pManager->finished)
    {
        // Génération d'une séquence aléatoire
        std::random_shuffle(seq.begin(), seq.end());

        // Vérification si la séquence est triée
        if (std::is_sorted(seq.begin(), seq.end()))
        {
            pManager->finished = true;
            return;
        }
    }

    // Exemple de mise à jour de la barre de progression
    pManager->incrementPercentComputed((double)1);
}

std::vector<int> getPermutation(std::vector<int> list, int k)
{
    size_t n = list.size();
    std::vector<int> permutation;
    std::vector<int> availableElements = permutation;

    for (size_t i = 0; i < n; i++)
    {
        int fact = factorial(n - 1 - i);
        int index = k / fact;
        permutation.push_back(availableElements[index]);
        availableElements.erase(availableElements.begin() + index);
        k = k % fact;
    }

    return permutation;
}

int factorial(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}