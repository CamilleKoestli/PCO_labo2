/******************************************************************************
  \file main.cpp
  \author Yann Thoma
  \date 15.09.2021

  This program launches several threads allowing the retrieval of timestamps
  that allow the retrieval of context changes that have occurred. A python
  script is executed with the retrieved data to visualise the behaviour of
  the execution
  ****************************************************************************/

#include <iostream>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include <limits>

#include <pcosynchro/pcothread.h>

#include <sched.h>

using namespace std;

chrono::high_resolution_clock::time_point start;

constexpr size_t NB = 40000;
constexpr size_t NUM_THREADS = 3;

vector<vector<std::pair<uint64_t, uint64_t> > > vec;
vector<PcoThread*> threads;

/**
 * Fill container with timestamps
 *
 * Code executed from the threads to get the timestamp of passage in the loop
 * Tese timestamps will then be used to defines context switches timings
 *
 * @param vec Contains timestamps
 *
 */
void running(int /*tid*/, vector<std::pair<uint64_t, uint64_t> > &vec)
{
    unsigned int cpu = -1;
    for (size_t i = 0; i < NB; i++) {
        auto end = chrono::high_resolution_clock::now();
        getcpu(&cpu, NULL); // https://man7.org/linux/man-pages/man2/getcpu.2.html
        auto diff = chrono::duration_cast<chrono::nanoseconds>(end - start);
        vec[i].first = diff.count();
        vec[i].second = cpu;
    }
}

/**
 * Create a CSV file with thread timestamps.
 *
 * @param switches Contains context switches
 *
 */
void createCSVts(vector<vector<std::pair<uint64_t, uint64_t> > >& data)
{
    ofstream csvfile;
    csvfile.open("timestamps.csv");
    csvfile << "time" << "," << "threadID" << "," << "CPU" << endl;
    size_t id = 0;
    for (auto& v : data) {
        for (auto& e : v) {
            csvfile << e.first << "," << id << "," << e.second << endl;
        }
        id++;
    }
    csvfile.close();
}

int main()
{
    for(size_t i = 0; i < NUM_THREADS; ++i) {
        vec.push_back(vector<std::pair<uint64_t, uint64_t> >(NB));
    }
    start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < NUM_THREADS; ++i) {
        threads.push_back(new PcoThread(running, 0, ref(vec[i])));
    }

    for (auto& t : threads) {
        t->join();
        delete t;
    }

    createCSVts(vec);

    // This command directly displays the graphical results
    system("./show_graphic_from_exec.py");
    return 0;
}
