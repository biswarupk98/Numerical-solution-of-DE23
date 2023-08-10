#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <array>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector> 
#include <sstream>
using namespace std;

int main(int argc, char *argv[]) {
 cout << "        This program  solves viscous burgers equation  for alpha=0.001     " << endl;
   // reading input file
    ifstream input_file("input.txt");
    string line;
    while (getline(input_file, line)) {
        vector<string> tokens;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        int N = stoi(tokens[0]);
        double j = stod(tokens[1]);

        double *u = new double[N];
        double *u_new = new double[N];
        double dx = 1.0 / (N - 1);
        double dt = 0.0004;
        double alph=0.001;
        double rd = (alph * dt)/(dx * dx);

        //Initial condition
        double x = 0.0000;
        for(int i = 0; i < N; i++) {
            u[i] = sin(4 * M_PI * x) + sin(6 * M_PI * x) + sin(10 * M_PI * x);
            x += dx;
        }

        // Use of update formula to update value to next time step
        double t = 0.0;
        while(t <= j) {
            for(int i = 1; i < N - 1; i++) {
                double rc = (u[i] * dt)/(2 * dx);
                u_new[i] = (rd - rc) * u[i+1] + (1-2*rd) * u[i] + (rd + rc) * u[i-1];
            }
            double rc = (u[0] * dt)/(2 * dx);
            u_new[0] =  (rd - rc) * u[1] + (1-2*rd) * u[0] + (rd + rc) * u[N-2];
            u_new[N - 1] = u_new[0];
            t += dt;
            copy(u_new, u_new + N, u);
            
            // writting the output file
                ofstream output_file;
                output_file.open("q1_b_" + to_string(N) + "_" + to_string(j) + ".txt");
                for (int i = 0; i < N; i++) {
                    output_file << u_new[i] << "\n";
                }
                output_file.close();

        
           
        }
        delete[] u;
        delete[] u_new;
    }
    
    return 0;
}
