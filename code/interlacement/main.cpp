
/******************************************************************************
  \file main.cpp
  \author A.Gabriel Catel Torres
  \date 15.09.2021

  This program proposes a code base allowing to discover the pcosyncro library,
  in particular the way to initiate threads. The objective is to understand some
  concepts seen in the theory and to make a first step in the implementation of
  these.
  ****************************************************************************/

#include <iostream>
#include <unistd.h>
#include <signal.h>

#include <pcosynchro/pcothread.h>

using namespace std;

bool programRunning;

void signalHandler(int)
{
    programRunning = false;
}


void run(int tid)
{
    while(programRunning) {
        // TODO
    }
}


int main()
{
    // Get the SIGINT (ctrl+c) sent from the user to end
    // the program execution in a clean way
    signal(SIGINT, signalHandler);

    programRunning = true;

    cout << "Program interlacement -> ctrl+c to stop" << endl;

    // Creation and start of threads
    PcoThread t0(run, 0);
    PcoThread t1(run, 1);
    PcoThread t2(run, 2);

    // Waiting all threads to finish their task
    t0.join();
    t1.join();
    t2.join();

    cout << "End of the program : interlacement" << endl;

    return 0;
}
