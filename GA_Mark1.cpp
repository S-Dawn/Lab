#include<iostream>
#include<cmath>
#include<time.h>

using namespace std;

#define POPULATION_SIZE 4

bool randomBool() {
    return 0 + (rand() % (1 - 0 + 1)) == 1;
}

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
        cout << "   ---> f(x)=" << f(chromosome[i]) << endl;
    }

}


int main () {

    bool chromosome[POPULATION_SIZE][8];

    //initialize population
    for(int i=0; i<POPULATION_SIZE; i++) {
        for(int j=0; j<8; j++) {
            chromosome[i][j] = randomBool();
        }
    }

    display_population(chromosome);

    return 0;
}
