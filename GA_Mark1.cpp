#include<iostream>
#include<cmath>
#include<time.h>
#include<vector>

using namespace std;

#define POPULATION_SIZE 8
#define VECTOR_LENGTH 8
#define CROSSOVER_RATE 0.9
#define MUTATION_RATE 0.1
#define NUMBER_OF_ITERATIONS 20

bool randomBool() {
    return 0 + (rand() % (1 - 0 + 1)) == 1;
}

bool* randomBoolArray() {
    bool * arr = (bool *) calloc (VECTOR_LENGTH, sizeof(bool));
    for(int i=0; i< VECTOR_LENGTH; i++)
        arr[i] = randomBool();
    return arr;
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
    int n = chromosome.size();

    vector <bool*> new_gen_chromosome;

    double r_wheel[POPULATION_SIZE];

    for(i=0; i<n; i++) {
        total_fitness += f(chromosome[i]);
        if(f(chromosome[i]) > k) {
            k = f(chromosome[i]);
            j = i;
        }
    }

    r_wheel[0] = f(chromosome[0])/total_fitness;
    for(i=1; i<n; i++) {
        r_wheel[i] = r_wheel[i-1] + f(chromosome[i])/total_fitness;
    }
    
    //Elite Gene Selection
    new_gen_chromosome.push_back(chromosome[j]);

    for(i=1;i<POPULATION_SIZE;i++) {
        double r = rand()/RAND_MAX;
        for(j=0; j<n; j++) {
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

vector<bool*> crossover (vector<bool*> chromosome) {
    int crossover_population = CROSSOVER_RATE*POPULATION_SIZE;
    int i, j, k, m;
    bool *arr;

    bool ** parent = (bool **) calloc(2,sizeof(bool*));


    for(i=0, j=0, k=0;;i=(i+1)%VECTOR_LENGTH) {
        if(i==0) arr = randomBoolArray();
        if(!arr[i]) {
            parent[k] = (bool*) calloc(VECTOR_LENGTH, sizeof(bool));
            for(int a=0; a<VECTOR_LENGTH; a++) {
                parent[k][a] = chromosome[i][a];
            }
            k++;
        }

        if(k==2) {
            k=0;
            int index = rand()/RAND_MAX*(VECTOR_LENGTH-2);
            index++;
            bool temp;
            for(m=0; m<index; m++) {
                temp = parent[0][m];
                parent[0][m] = parent[1][m];
                parent[1][m] = temp;
            }

            chromosome.push_back(parent[0]);
            chromosome.push_back(parent[1]);
            j += 2;
        }

        if(j>crossover_population) break;
    }

    return chromosome;
}

vector<bool*> mutation (vector<bool*> chromosome) {
    int mutation_population = MUTATION_RATE*POPULATION_SIZE;
    int i, j, k, m;
    bool *arr;

    for(i=0, j=0, k=0;;i=(i+1)%VECTOR_LENGTH) {
        if(i==0) arr = randomBoolArray();
        if(!arr[i])  {
            int index = rand()/RAND_MAX*(VECTOR_LENGTH-1);
            bool * parent = (bool *) calloc(VECTOR_LENGTH, sizeof(bool));
            for(int a=0; a<VECTOR_LENGTH; a++)
                parent[a] = chromosome[i][a];
            parent[index] = !parent[index];
            chromosome.push_back(parent);
            j++;
        }
        if(j>mutation_population) break;
    }

    return chromosome;
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

    for(int i=0; i<NUMBER_OF_ITERATIONS; i++) {
        chromosome = selection(chromosome);
        chromosome = crossover(chromosome);
        chromosome = mutation(chromosome);
        display_population(chromosome);
    }

    return 0;
}
