/**
  \file mainwindows.h
  \author Guillaume Chacun
  \date 28.08.2024
  \brief Définition de l'interface graphique de l'application qui permet
  de trier un vecteur avec l'algorithme Bogosort déterministe


  Ce fichier contient la définition de la classe MainWindow. Cette classe est
  une interface graphique qui permet à l'utilisateur de proposer la taille
  du vecteur à trier avec plusieurs threads et l'algorithme Bogosort déterministe.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QElapsedTimer>
#include <QTimer>
#include <QtCore>

#include "threadmanager.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 *
 * Cette classe est une interface graphique qui permet à l'utilisateur de
 * choisir la taille d'une séquence à trier avec plusieurs threads.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:

    //! Instance de l'interface graphique.
    Ui::MainWindow *ui;

    //! Instance du thread "Manager" qui gère les autres threads responsable du
    //! tri de la séquence.
    ThreadManager *threadManager;

    //! Chronnomètre qui mesure le temps nécessaire au tri de la séquence.
    QElapsedTimer chronometer;

    //! Tâche non-bloquante qui exécute les threads responsables du tri.
    QFuture<std::vector<int>> sortingAsync;

    //! Utiliser pour signaler la fin de l'exécution des threads responsables
    //! du tri.
    QFutureWatcher<std::vector<int>> sortWatcher;

    //! La valeur de la barre de progression.
    double progress;

    //! Flag qui indique si le programme a trié la séquence.
    bool isSorting;

public:
    /**
     * @brief MainWindow Constructeur simple
     * @param parent Objet parent de l'interface
     */
    explicit MainWindow(QWidget *parent = 0);

private:
    /**
     * @brief generateSequence génère la séquence à trier
     * @param seqLen taille de la séquence à trier
     * @param seed utilisé pour seeder la génération aléatoire de la séquence à trier
     * @return séquence à trier
     */
    std::vector<int> generateSequence(unsigned int seqLen, unsigned int seed);

signals:
    
public slots:
    /**
     * @brief prepareSort Méthode qui récupère les paramètres entrés par
     * l'utilisateur pour trier la séquence.
     */
    void prepareSort();
    /**
     * @brief endSort Méthode pour clean et terminer le programme.
     */
    void endSort();
    /**
     * @brief run Méthode qui incrémente la barre de progression affichée dans
     * l'interface. Cette barre de progression est partagée entre tous les
     * threads.
     */
    void incrementProgressBar(double percent);
};

#endif // MAINWINDOW_H
