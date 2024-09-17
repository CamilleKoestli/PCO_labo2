/******************************************************************************
  \file main.cpp
  \author A.Gabriel Catel Torres
  \date 15.09.2021

  This application aims to raise awareness of a basic concept of concurrency,
  which is the concurrent access to a variable shared by several threads. Two
  threads are launched to execute a simple task and the goal is to analyse the
  execution behaviour.
  ****************************************************************************/

#include <iostream>
#include <unistd.h>
#include <signal.h>

#include <pcosynchro/pcothread.h>
#include <pcosynchro/pcologger.h>

using namespace std;

int sharedVar;

void run(int tid)
{
    sharedVar = tid;
}

int main()
{

    // Create and start threads
    PcoThread t0(run, 0);
    PcoThread t1(run, 1);

    sharedVar = 2;

    // Waiting that both threads ended their task
    t0.join();
    t1.join();

    cout << "Final value -> " << sharedVar << endl;
    cout << "End of the program : order" << endl;

    return 0;
}
