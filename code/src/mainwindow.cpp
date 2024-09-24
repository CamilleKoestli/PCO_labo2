#include <QMessageBox>
#include <QtConcurrent>

#include "mainwindow.h"
#include "threadmanager.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    threadManager(new ThreadManager(parent))
{
    /*
     * ui est l'instance de la classe représentant notre interface graphique
     */
    ui->setupUi(this);

    /*
     * On connecte les signaux sur les slots:
     *
     * - L'appui du bouton btnSort déclenche notre méthode prepareSort
     * - Le signal finished du sortWatcher (indiquant que la fonction
     *   startSort de notre threadManager
     *   a retourné) déclenche notre méthode endSort
     * - Le signal incrementPercentComputed du threadManager déclanche notre
     *   méthode incrementProgressBar.
     *   Ce signal transmet en paramètre un double
     */
    connect(
                ui->btnSort,
                SIGNAL(clicked()),
                this,
                SLOT(prepareSort()));
    connect(
                &sortWatcher,
                SIGNAL(finished()),
                this,
                SLOT(endSort()));
    connect(
                threadManager,
                SIGNAL(sig_incrementPercentComputed(double)),
                this,
                SLOT(incrementProgressBar(double)));

    isSorting = false;
}

/**
 * @brief MainWindow::prepareSort La fonction ci-dessous est exécutée à chaque appui sur le bouton "Sort!"
 */
void MainWindow::prepareSort()
{
    /*
     * Un meme évènement sous QT est traité de manière séquentielle dans tous
     * les cas. Le test ci-dessous permet donc d'éviter qu'on lance deux groupes
     * de threads, en cliquant deux fois sur le bouton.
     */
    if (isSorting)
        return;

    QString inputError("");

    /*
     * Controle de saisie
     */
    if (ui->inputThreads->text().toInt() <= 0)
       inputError =     "Error: the number of threads must be greather than 0.";

    if (ui->inputSeed->text().toInt() < 0)
       inputError =     "Error: the seed must be a positive integer.";

    if (ui->inputSeqLen->text().toInt() <= 0)
       inputError =     "Error: the sequence length must be greater than 0.";
    else if (ui->inputSeqLen->text().toInt() > 15)
       inputError =     "Error: the sequence length must be less or equal than 15 (15! = 1.3076744e+12 permutations).";


    if (inputError.length()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erreur");
        msgBox.setText(inputError);
        msgBox.exec();
        return;
    }

    /*
     * Si le controle de saisie est passé, on met le flag isSorting à true et on
     * initialise la progression à zéro.
     */
    isSorting       = true;
    progress        = 0;

    /*
     * Désactivation des champs du formulaire
     */
    ui->btnSort->setEnabled(false);
    ui->inputSeqLen->setEnabled(false);
    ui->inputSeed->setEnabled(false);
    ui->inputThreads->setEnabled(false);

    /*
     *  Génération aléatoire de la séquence à trier
     */
    unsigned int seqLen = ui->inputSeqLen->text().toInt();
    unsigned int seed = ui->inputSeed->text().toInt();
    std::vector<int> seq = generateSequence(seqLen, seed);

    /*
     * Démarrage du chronomètre
     */
    chronometer.start();
    /*
     * Appel de la fonction startSorting du threadManager de manière non
     * bloquante.
     */
    sortingAsync = QtConcurrent::run(
                threadManager,
                &ThreadManager::startSorting,
                seq,
                ui->inputThreads->text().toInt());
    /*
     * Ajout d'un watcher permettant de signaler à MainWindow la fin de la tache
     * asynchrone
     */
    sortWatcher.setFuture(sortingAsync);
}

/**
 * @brief MainWindow::incrementProgressBar La fonction ci-dessous est exécutée à chaque réception d'un signal
 * incrementPercentComputed en provenance de threadManager
 * @param percent progression à ajouter à la barre de chargement
 */
void MainWindow::incrementProgressBar(double percent)
{
    progress += percent;
    ui->progressBar->setValue(100*progress);
}

/**
 * @brief Cette fonction génère aléatoirement une séquence de nombres de la taille requise
 * @param seqLen la taille de la séquence à trier
 * @param seed utilisé pour seeder la génération aléatoire de la séquence à trier
 * @return séquence à trier
 */
std::vector<int> MainWindow::generateSequence(unsigned int seqLen, unsigned int seed)
{
    QRandomGenerator generator(seed);

    std::vector<int> randomSequence;
    randomSequence.reserve(seqLen);

    for (unsigned int i = 0; i < seqLen; ++i) {
        int randomValue = generator.bounded(100); // [0,100[
        randomSequence.push_back(randomValue);
    }

    return randomSequence;
}

/**
 * @brief MainWindow::endSort La fonction ci-dessous est exécutée à la réception d'un signal
 * finished en provenance du sortWatcher, indiquant que la fonction
 * startSorting du sortWatcher a retourné.
 */
void MainWindow::endSort()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle("Results");

    // Récupérer la séquence triée et la convertir en QString pour l'affichage
    std::vector<int> sortedSeq = sortingAsync.result();
    QStringList stringList;
    for (int value : sortedSeq) {
        stringList << QString::number(value);
    }
    QString result = stringList.join(", ");

    if (result.length() > 0) {
        msgBox.setText("Sequence is sorted!\nSequence: " + result +
                       "\nElapsed Time: " + QString::number(chronometer.elapsed()) + " ms");
    } else {
        msgBox.setText("Not finished... \nElapsed time: " +
                       QString::number(chronometer.elapsed()) + " ms");
    }

    /*
     * Affichage de la boite de dialogue. L'appel est bloquant et la
     * fenetre est modale.
     */
    msgBox.exec();

    ui->progressBar->setValue(0);
    ui->btnSort->setEnabled(true);
    ui->inputSeqLen->setEnabled(true);
    ui->inputSeed->setEnabled(true);
    ui->inputThreads->setEnabled(true);

    isSorting = false;
}
