#include<iostream>
#include<cmath>

using namespace std;

#define POPULATION_SIZE 4

double f(bool sol_vector[]) {
    double res = 0, x;
    for(int i=7; i>=0; i--)
        res += pow(2,i)*(int)sol_vector[i];
    x = res*8/255;
    return x*(8-x);
}

void display_population(bool chromosome[POPULATION_SIZE][8]) {
    for(int i=0; i<POPULATION_SIZE; i++) {
        for(int j=0; j<8; j++) {
            cout << chromosome[i][j] << " ";
        }
        cout << endl;
    }

}

int main () {

    bool chromosome[POPULATION_SIZE][8];

    display_population(chromosome);

    return 0;
}