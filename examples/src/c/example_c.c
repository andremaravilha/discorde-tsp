#include <stdlib.h>
#include <stdio.h>
#include <discorde_c.h>

int main(int argc, char** argv) {
    
    /* ************************************************************************
     * Variables
     * ************************************************************************/
    
    /* Indices for loops */
    int i, j;
    
    /* Problem data */
    int n_nodes;
    int** cost_matrix;
    
    /* Lin-Kernighan solution */
    int* lk_tour;
    double lk_cost;
    int lk_return;
    
    /* Concorde solution */
    int* cc_tour;
    double cc_cost;
    int cc_return;
    int cc_status;
    int* cc_start;

    
    /* ************************************************************************
     * Create a random problem
     * ************************************************************************/
    
    /* Initialize the random number generator */
    srand(0);
    
    /* Set the number of nodes */
    n_nodes = 100;

    /* Create a random cost matrix */
    cost_matrix = (int**) malloc(sizeof(int*) * n_nodes);
    for (i = 0; i < n_nodes; ++i) {
        cost_matrix[i] = (int*) malloc(sizeof(int) * n_nodes);
    }
    for (i = 0; i < n_nodes; ++i) {
        cost_matrix[i][i] = 0;
        for (j = i + 1; j < n_nodes; ++j) {
            cost_matrix[i][j] = 10 + (rand() % 91);
            cost_matrix[j][i] = cost_matrix[i][j];
        }
    }
    
    
    /* ************************************************************************
     * Solve the problem
     * ************************************************************************/
    
    /* Allocate resources to store the solution from Lin-Kernighan heuristic */
    lk_tour = (int*) malloc(sizeof(int) * n_nodes);
    
    /* Solve the problem using Lin-Kernighan heuristic */
    lk_return = linkernighan_full(n_nodes, cost_matrix, lk_tour, &lk_cost, NULL, true, NULL, NULL);
    
    /* Allocate resources to store the solution from Concorde solver */
    cc_tour = (int*) malloc(sizeof(int) * n_nodes);
    
    /* Solve the problem using Concorde solver (using the tour obtained previously 
       with Lin-Kernighan heuristic as a starting solution, if any was found) */
    cc_start = (lk_return == DISCORDE_RETURN_OK ? lk_tour : NULL);
    cc_return = concorde_full(n_nodes, cost_matrix, cc_tour, &cc_cost, NULL, cc_start, false, NULL, NULL);


    /* ************************************************************************
     * Print results
     * ************************************************************************/
    
    /* Lin-Kernighan results */
    printf("=================================================================\n");
    printf("Lin-Kernighan heuristic\n");
    printf("=================================================================\n\n");
    printf("Tour: [ ");
    for (i = 0; i < n_nodes; ++i) {
        printf("%d ", lk_tour[i]);
    }
    printf("]\n\n");
    printf("Cost: %f\n", lk_cost);
    printf("Is feasible? %s\n\n", ((lk_return == DISCORDE_RETURN_OK) ? "yes" : "no"));
    
    /* Concorde results */
    printf("=================================================================\n");
    printf("Concorde solver\n");
    printf("=================================================================\n\n");
    printf("Tour: [ ");
    for (i = 0; i < n_nodes; ++i) {
        printf("%d ", cc_tour[i]);
    }
    printf("]\n\n");
    printf("Cost: %f\n", cc_cost);
    printf("Is feasible? %s\n", ((cc_return == DISCORDE_RETURN_OK) ? "yes" : "no"));
    printf("Is optimal? %s\n\n", ((cc_return == DISCORDE_RETURN_OK && cc_status == DISCORDE_STATUS_OPTIMAL) ? "yes" : "no"));
    
    
    /* ************************************************************************
     * Free resources
     * ************************************************************************/

    for (i = 0; i < n_nodes; ++i) {
        free(cost_matrix[i]);
    }
    free(cost_matrix);
    free(lk_tour);
    free(cc_tour);

    return 0;
}
