/**
  \file threadmanager.h
  \author Guillaume Chacun
  \date 28.08.2024
  \brief Classe pour trier une séquence avec du Bogosort déterministe.


  Ce fichier contient la définition de la classe ThreadManager, qui permet de
  trier une séquence avec du Bogosort déterministe.
*/
#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <cstdint>

#include <QObject>
#include <QString>
#include <QElapsedTimer>
#include <QCryptographicHash>
#include <QVector>


/**
 * @brief The ThreadManager class
 *
 * Cette classe permet de trier une séquence avec du Bogosort déterministe.
 */
class ThreadManager: public QObject
{
    Q_OBJECT

public:
    /**
     * @brief ThreadManager Constructeur simple
     * @param parent Objet parent de l'interface
     */
    ThreadManager(QObject *parent);

    /**
     * @brief startSorting tâche qui s'occupe de générer la séquence à trier et de
     * démarrer le tri.
     * @param seq séquence à trier
     * @return séquence triée
     */
    std::vector<int> startSorting(
            std::vector<int> seq,
            unsigned int nbThreads
    );

    /**
     * @brief incrementPercentComputed fonction qui indique que le pourcentage
     * de test effectué pour trier la séquence.
     * @param percentComputed double pourcentage de tests effectués pour
     * trier la séquence
     */
    void incrementPercentComputed(double percentComputed);

    /** To indicate that one thread has sinished **/
    bool finished{false};

signals:
    /**
     * @brief sig_incrementPercentComputed signal qui indique que le pourcentage
     * de test effectué pour trier la séquence.
     * @param percentComputed double pourcentage de tests effectués pour
     * trier la séquence
     */
    void sig_incrementPercentComputed(double percentComputed);

};

#endif // THREADMANAGER_H
