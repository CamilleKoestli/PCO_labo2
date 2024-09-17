/**
  \file mythread.h
  \author Yann Thoma
  \date 07.02.2017
  \brief Classe pour la mise en évidence du problème de concurrence.


  Ce fichier contient la définition de la classe MyThread, qui permet de
  mettre en avant le problème d'accès concurrent à une variable partagée.
*/


#ifndef MYTHREAD_H
#define MYTHREAD_H


/**
 * \brief fonction exécutée par les threads
 *
 * Cette fonction lance une boucle incrémentant un compteur.
 * Celui-ci est partagé par l'ensemble des threads et doit donc
 * être protégé.
 */
void runTask(long unsigned int nbIterations);

/**
 * @brief Initializes the counter
 */
void initCounter();

/**
 * @brief Gets the counter value
 * @return The current value of the counter
 */
long unsigned int getCounter();

#endif // MYTHREAD_H
