
#include "mythread.h"
#include <iostream>

void bogosort(std::vector<int> seq, ThreadManager *pManager, unsigned startIdx, unsigned endIdx, std::vector<int>* sortedSeq)
{
    unsigned totalWork = endIdx - startIdx + 1;
    for (unsigned i = startIdx; i <= endIdx; ++i)
    {
        std::vector<int> perm = getPermutation(seq, i);
        if (std::is_sorted(perm.begin(), perm.end()))
        {
            pManager->finished = true;
            *sortedSeq = perm;
            break;
        }

        if (pManager->finished)
        {
            break;
        }

        double progress = 100.0 * (i - startIdx + 1) / totalWork; 
        pManager->incrementPercentComputed(progress);
    }

    // Exemple de mise à jour de la barre de progression
    //pManager->incrementPercentComputed((double)1);
}


std::vector<int> getPermutation(std::vector<int> list, int k)
{
    size_t n = list.size();
    std::vector<int> permutation;
    std::vector<int> availableElements = list;

    if (k >= factorial(n)) {
        throw std::out_of_range("k est out of range");
    }

    for (size_t i = 0; i < n; i++)
    {
        int fact = factorial(n - 1 - i);
        int index = k / fact;
        permutation.push_back(availableElements.at(index));
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