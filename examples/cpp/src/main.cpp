#include <cstdlib>
#include <iostream>
#include <discorde_cpp.h>

using namespace std;


int main(int argc, char** argv) {

    // =========================================================================
    // Create a random problem
    // =========================================================================

    // Initialize the random number generator
    srand(0);

    // Set the number of nodes
    int n_nodes = 100;

    // Create a random costs matrix
    int** cost_matrix = new int*[n_nodes];
    for (int i = 0; i < n_nodes; ++i) {
        cost_matrix[i] = new int[n_nodes];
    }
    for (int i = 0; i < n_nodes; ++i) {
        cost_matrix[i][i] = 0;
        for (int j = i + 1; j < n_nodes; ++j) {
            cost_matrix[i][j] = 10 + (rand() % 91);
            cost_matrix[j][i] = cost_matrix[i][j];
        }
    }


    // =========================================================================
    // Solve the problem
    // =========================================================================

    // Allocate resources to store the solution from Lin-Kernighan heuristic
    int* lk_tour = new int[n_nodes];
    double lk_cost;
    int lk_return;

    // Solve the problem using Lin-Kernighan heuristic
    lk_return = discorde::linkernighan_full(n_nodes, cost_matrix, lk_tour, &lk_cost);

    // Allocate resources to store the solution from Concorde solver
    int* cc_tour = new int[n_nodes];
    double cc_cost;
    int cc_return;
    int cc_status;

    // Solve the problem using Concorde solver (using the tour obtained previously
    // with Lin-Kernighan heuristic as a starting solution, if any was found)
    int* cc_start = (lk_return == DISCORDE_RETURN_OK ? lk_tour : NULL);
    cc_return = discorde::concorde_full(n_nodes, cost_matrix, cc_tour, &cc_cost, &cc_status, cc_start);


    // =========================================================================
    // Print results
    // =========================================================================

    // Lin-Kernighan results
    cout << "=================================================================" << endl;
    cout << "Lin-Kernighan heuristic" << endl;
    cout << "=================================================================" << endl;
    cout << endl;
    cout << "Tour: [ ";
    for (int i = 0; i < n_nodes; ++i) {
        cout << lk_tour[i] << " ";
    }
    cout << "]" << endl << endl;
    cout << "Cost: " << lk_cost << endl;
    cout << "Is feasible? " << ((lk_return == DISCORDE_RETURN_OK) ? "yes" : "no") << endl << endl;

    // Concorde results
    cout << "=================================================================" << endl;
    cout << "Concorde solver" << endl;
    cout << "=================================================================" << endl;
    cout << endl;
    cout << "Tour: [ ";
    for (int i = 0; i < n_nodes; ++i) {
        cout << cc_tour[i] << " ";
    }
    cout << "]" << endl << endl;
    cout << "Cost: " << cc_cost << endl;
    cout << "Is feasible? " << ((cc_return == DISCORDE_RETURN_OK) ? "yes" : "no") << endl;
    cout << "Is optimal? " << ((cc_return == DISCORDE_RETURN_OK && cc_status == DISCORDE_STATUS_OPTIMAL) ? "yes" : "no") << endl << endl;


    // =========================================================================
    // Free resources
    // =========================================================================

    for (int i = 0; i < n_nodes; ++i) {
        delete[] cost_matrix[i];
    }
    delete[] cost_matrix;
    delete[] lk_tour;
    delete[] cc_tour;

    return 0;
}
