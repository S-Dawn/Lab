#include<iostream>
#include<cmath>
#include<time.h>
#include<vector>

using namespace std;

#define POPULATION_SIZE 4
#define VECTOR_LENGTH 8

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

void display_population(vector <bool*> chromosome) {
    for(int i=0; i<POPULATION_SIZE; i++) {
        for(int j=0; j<8; j++) {
            cout << chromosome[i][j] << " ";
        }
        cout << "   ---> f(x)=" << f(chromosome[i]) << endl;
    }

}

vector<bool *> selection (vector <bool*> chromosome) {

    double total_fitness=0;
    int i, j, k=-1;

    vector <bool*> new_gen_chromosome;

    double r_wheel[POPULATION_SIZE];

    for(i=0; i<POPULATION_SIZE; i++) {
        total_fitness += f(chromosome[i]);
        if(f(chromosome[i]) > k) {
            k = f(chromosome[i]);
            j = i;
        }
    }

    r_wheel[0] = f(chromosome[0])/total_fitness;
    for(i=1; i<POPULATION_SIZE; i++) {
        r_wheel[i] = r_wheel[i-1] + f(chromosome[i])/total_fitness;
    }
    
    //Elite Gene Selection
    new_gen_chromosome.push_back(chromosome[j]);

    for(i=1;i<POPULATION_SIZE;i++) {
        double r = rand()/RAND_MAX;
        for(j=0; j<POPULATION_SIZE; j++) {
            if(r<r_wheel[i]) {
                j = i;
            }
            else {
                break;
            }
        }
        new_gen_chromosome.push_back(chromosome[j]);
    }

    return new_gen_chromosome;
}




int main () {

    vector <bool*> chromosome;

    //initialize population
    for(int i=0; i<POPULATION_SIZE; i++) {
        chromosome.push_back((bool *) calloc(8, sizeof(bool)));
        for(int j=0; j<8; j++) {
            chromosome[i][j] = randomBool();
        }
    }

    display_population(chromosome);

    return 0;
}
