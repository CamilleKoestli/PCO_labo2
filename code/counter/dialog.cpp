#include "mythread.h"
#include <pcosynchro/pcothread.h>

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    /* Un click sur le bouton start appelera notre méthode startThreads */
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startThreads()));
}

void Dialog::startThreads()
{
    /* Initialisation du compteur à 0 avant de lancer les threads */
    initCounter();

    /* Récupère les paramètres */
    long unsigned int nbIterations   = static_cast<long unsigned int>(ui->editNbIterations->text().toLong());
    long unsigned int nbThreads      = static_cast<long unsigned int>(ui->editNbThreads->text().toLong());

    /* Désactive temporairement le bouton */
    ui->startButton->setEnabled(false);

    /* Affiche une barre de progression animée */
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);

    /* Met à jour les champs de texte avec les nombres parsés (un zéro
     * indiquera une erreur). On passe par une QSting pour pouvoir afficher
     * des long */
    ui->editNbIterations->setText(QString::number(nbIterations));
    ui->editNbThreads->setText(QString::number(nbThreads));

    if (nbIterations && nbThreads)
    {
        /* Affiche le résultat escompté */
        ui->lcdNumberResEspere->display(
                    QString::number(nbIterations*nbThreads));

        /* Crée les threads, on ajoutant leur pointeur à la liste.
           Les threads sont immédiatement lancés par le constructeur. */
        for (long unsigned int i=0; i<nbThreads; i++)
        {
            PcoThread *currentThread = new PcoThread(runTask, nbIterations);
            threadList.push_back(std::unique_ptr<PcoThread>(currentThread));
        }

        /* Attends la fin de chaque thread et libère la mémoire associée.
         * Durant l'attente, l'application est bloquée.
         */
        for (long unsigned int i=0; i<nbThreads; i++)
        {
            threadList[i]->join();
        }
        /* Vide la liste de pointeurs de threads */
        threadList.clear();

        /* Affiche le résultat obtenu (on passe par une QSting pour pouvoir
         * afficher des long) */
        ui->lcdNumberResObtenu->display(QString::number(getCounter()));
        ui->lcdNumberResRatio->display(QString::number(
                            getCounter() * 100 / nbIterations/nbThreads));
    }

    /* Affiche une barre de progression complète */
    ui->progressBar->setMaximum(1);
    ui->progressBar->setValue(1);

    /* Réactive le bouton start */
    ui->startButton->setEnabled(true);
}


Dialog::~Dialog()
{
    delete ui;
}
