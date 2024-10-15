
#include "mythread.h"
#include <iostream>

/**
 * @brief bogosort Trie une séquence avec l'algorithme Bogosort déterministe en parallèle
 * @param seq séquence à trier
 * @param pManager Pointeur sur le ThreadManager utilisé pour accéder à l'interface
 * @param startIdx index de début de la séquence à trier
 * @param endIdx index de fin de la séquence à trier
 * @param sortedSeq séquence triée
 */
void bogosort(std::vector<int> seq, ThreadManager *pManager, unsigned startIdx, unsigned endIdx, std::vector<int> *sortedSeq, unsigned totalPerm)
{
    for (unsigned i = startIdx; i <= endIdx; ++i)
    {
        std::vector<int> perm = getPermutation(seq, i);

        // Mise à jour de la progression
        pManager->incrementPercentComputed(1.0 / totalPerm);

        // Si c'est trié, mettre à jour la séquence et terminé
        if (std::is_sorted(perm.begin(), perm.end()))
        {
            pManager->finished = true;
            *sortedSeq = perm;
            break;
        }

        // Vérifie si un autre thread a terminé
        if (pManager->finished)
        {
            break;
        }
    }
}

/**
 * @brief getPermutation Retourne la k-ième permutation d'une liste
 * @param list liste d'entiers
 * @param k index de la permutation
 * @return k-ième permutation
 */
std::vector<int> getPermutation(std::vector<int> list, int k)
{
    size_t n = list.size();
    std::vector<int> permutation;
    std::vector<int> availableElements = list;

    // Vérification si l'indice k est hors des plages
    if (k >= factorial(n))
    {
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

/**
 * @brief factorial Calcule la factorielle d'un entier
 * @param n entier
 * @return factorielle de n
 */
int factorial(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}