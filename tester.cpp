#include "solver.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

#define now chrono::high_resolution_clock::now


int main(int argc, char const *argv[]) {

  /*  Some setup */
  const char* test_cases_path = argv[1];
  const char* res_path = argv[2];
  int reps = (argc >= 4)? atoi(argv[3]) : 100;
  int  algorithm  = (argc >= 5)? atoi(argv[4]) : 4;


  std::ifstream infile;
  infile.open(test_cases_path);

  std::ofstream outfile;
  outfile.open(res_path);

  chrono::high_resolution_clock::time_point t1;
  chrono::high_resolution_clock::time_point t2;
  chrono::duration<double> time_span;


  int i,a;
  vector<encuesta> encuestas;

  while (infile >> i >> a) {
    if (i == 0 && a == 0 ) break;
    int x,y;
    vector<vector<opinion> > enc(i, vector<opinion>(i));
    for (size_t j = 0; j < a; j++) {
      infile >> x >> y;
      if(y < 0) enc[x-1][abs(y)-1].first = 1;
      if(y > 0) enc[x-1][abs(y)-1].second = 1;
    }
    encuestas.push_back(enc);
  }

  for (size_t k = 0; k < encuestas.size(); k++) {
    for (size_t r = 0; r < reps; r++) {
      t1 = now();

      Solucion sol;
      if (algorithm == 0) sol = resolver(encuestas[k].size(),encuestas[k]);
      if (algorithm == 1) sol = resolver_back(encuestas[k].size(),encuestas[k]);
      if (algorithm == 2) sol = resolver_prun1(encuestas[k].size(),encuestas[k]);
      if (algorithm == 3) sol = resolver_prun2(encuestas[k].size(),encuestas[k]);
      if (algorithm == 4) sol = resolver_pruning(encuestas[k].size(),encuestas[k]);

      t2 = now();
      time_span = chrono::duration_cast<chrono::duration<double>>(t2-t1);
      //outfile << sol.agentes_conj.size() << endl;
      outfile << time_span.count() << ";" << sol.calls << endl;
    }
  }



  infile.close();
  outfile.close();

  return 0;



}
