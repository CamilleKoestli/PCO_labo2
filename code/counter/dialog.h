/**
  \file dialog.h
  \author Magali Fröhlich
  \date 10.02.2017
  \brief Interface graphique pour tester l'incrémentation du compteur.

  Ce fichier contient la définition de la classe Dialog. Cette interface permet
  de lancer les threads et d'afficher le résultat du compteur.
*/


#ifndef DIALOG_H
#define DIALOG_H

#include <memory>

#include <QDialog>
#include <QList>

#include <pcosynchro/pcothread.h>

#include "mythread.h"

namespace Ui {
class Dialog;
}

/**
 * \brief The Dialog class
 *
 * Cette classe est une interface graphique de type QDialog qui permet
 * de lancer les threads MyThread qui incrémentent un compteur partager.
 * A la fin de l'exécution le résultat est affiché.
 */

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * \brief Dialog Constructeur simple
     * \param parent Objet parent du thread
     */
    explicit Dialog(QWidget *parent = nullptr);

    /**
     * \brief Dialog Destructeur
     */
    ~Dialog();
    
private:

    //! Liste des threads MyThread qui incrémente le compteur partagé.
    std::vector<std::unique_ptr<PcoThread>> threadList;

    //! Conteneur qui affiche les éléments graphiques (Boutons, Labels, etc.)
    Ui::Dialog *ui;

private slots:

    /**
     * \brief startThreads Méthode appelée lorsqu'on press le bouton start.
     */
    void startThreads();
};

#endif // DIALOG_H
