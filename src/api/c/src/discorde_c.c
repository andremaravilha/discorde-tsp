#include "discorde_c.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <concorde.h>


int concorde(int n_nodes, int n_edges, int* edges, int* edges_costs, 
        int* out_tour, double* out_cost, int* out_status, 
        int* in_tour, bool verbose, double* time_limit, double* target)
{
    
    /* Auxiliary variables */
    time_t timestamp;
    int return_value;
    
    /* Variables and structures used by Concorde solver */
    double* in_cost;    /* Initial upper bound (optional) */
    char* filename;     /* Name of temporary files created by Concorde */
    int silent;         /* Verbosity level */
    int success;        /* Output flag: set to 1 if a feasible tour is found */
    int optimal;        /* Output flag: set to 1 if tour found is optimal */
    int hit_timelimit;  /* Output flag: set to 1 if the time limit is reached */
    CCrandstate rstate; /* Rand state structure defined by Concorde library */
    
    /* Initialize Concorde structures */
    CCutil_sprand(rand(), &rstate);
    
    /* Initial upper bound as NULL (a feasible tour may be set in its place) */
    in_cost = NULL;
    
    /* Set a name for temporary files created by Concorde */
    filename = (char*) malloc(sizeof(char) * 1024);
    timestamp = time(NULL);
    sprintf(filename, "concorde_%ld", timestamp);
    
    /* Verbosity level */
    silent = verbose ? 0 : 1;
    
    /* Call Concorde solver */
    CCtsp_solve_sparse(n_nodes, n_edges, edges, edges_costs, in_tour, 
            out_tour, in_cost, out_cost, &optimal, &success, filename, time_limit, 
            &hit_timelimit, silent, &rstate);
    
    /* Set solver status */
    if (out_status != NULL) {
        if (success == 1 && optimal != 0) {
            *out_status = DISCORDE_STATUS_OPTIMAL;
        } else if (hit_timelimit == 1) {
            *out_status = DISCORDE_STATUS_TIMELIMIT;
        } else if (success == 1 && *out_cost <= *target) {
            *out_status = DISCORDE_STATUS_TARGET;
        } else {
            *out_status = DISCORDE_STATUS_UNKNOWN;
        }
    }
    
    /* Set the return value */
    if (success == 1) {
        return_value = DISCORDE_RETURN_OK;
    } else {
        return_value = DISCORDE_RETURN_FAILURE;
    }
    
    /* Free resources */
    free(filename);
    
    return return_value;
}

int concorde_sparse(int n_nodes, int n_edges, int** edges, int* edges_costs, 
        int* out_tour, double* out_cost, int* out_status, 
        int* in_tour, bool verbose, double* time_limit, double* target)
{
    
    /* Auxiliary variables */
    int i, index_edge;
    int return_value;
    
    /* Variables to format data as required by Concorde solver */
    int* edges_list;
    
    /* Create a list of edges as used by Concorde solver */
    edges_list = (int*) malloc(sizeof(int) * n_edges * 2);
    index_edge = 0;
    for (i = 0; i < n_edges; ++i) {
        edges_list[index_edge++] = edges[i][0];
        edges_list[index_edge++] = edges[i][1];
    }
    
    /* Call Concorde solver */
    return_value = concorde(n_nodes, n_edges, edges_list, edges_costs, out_tour, 
            out_cost, out_status, in_tour, verbose, time_limit, target);
    
    /* Free resources */
    free(edges_list);
    
    return return_value;
}

int concorde_full(int n_nodes, int** cost_matrix, 
        int* out_tour, double* out_cost, int* out_status, 
        int* in_tour, bool verbose, double* time_limit, double* target)
{
    
    /* Auxiliary variables */
    int i, j, index_edge, index_cost;
    int return_value;
    
    /* Variables to format data as required by Concorde solver */
    int n_edges;            /* Number of edges */
    int* edges_list;        /* List of edges (unidimensional) */
    int* edges_costs;       /* Edges costs */
    
    /* Calculate the number of edges */
    n_edges = ((n_nodes * (n_nodes + 1)) / 2) - n_nodes;
    
    /* Allocate resources */
    edges_costs = (int*) malloc(sizeof(int) * n_edges);
    edges_list = (int*) malloc(sizeof(int) * 2 * n_edges);
    
    /* Initialize the list of edges and costs as used by Concorde solver */
    index_edge = 0;
    index_cost = 0;
    for (i = 0; i < n_nodes; ++i) {
        for (j = i + 1; j < n_nodes; ++j) {
            edges_costs[index_cost++] = cost_matrix[i][j];
            edges_list[index_edge++] = i;
            edges_list[index_edge++] = j;
        }
    }
    
    /* Call Concorde solver */
    return_value = concorde(n_nodes, n_edges, edges_list, edges_costs, out_tour, 
            out_cost, out_status, in_tour, verbose, time_limit, target);
    
    /* Free resources */
    free(edges_list);
    free(edges_costs);
    
    return return_value;
}

int linkernighan(int n_nodes, int n_edges, int* edges, int* edges_costs, 
        int* out_tour, double* out_cost, int* in_tour, 
        bool verbose, double* time_limit, double* target)
{
    
    /* Auxiliary variables */
    int return_value;
    
    /* Variables and structures used by Lin-Kernighan heuristic */
    double time_limit_value; /* Time limit */
    double target_value;     /* target value */
    int silent;              /* Verbosity level */
    CCrandstate rstate;      /* Rand state structure (in Concorde library) */
    CCdatagroup data;        /* Coordinate data defined by Concorde library */
    int kicktype;            /* Type of kick */
    int stallcount;          /* Maximum number of 4-swaps without progress */
    int repeatcount;         /* Number of 4-swap kicks */
    
    /*
     * Available values for type of kick are:
     *  - CC_LK_RANDOM_KICK
     *  - CC_LK_GEOMETRIC_KICK
     *  - CC_LK_CLOSE_KICK
     *  - CC_LK_WALK_KICK
     */
    
    /* Initialize Lin-Kernighan structures */
    CCutil_sprand(rand(), &rstate);
    kicktype = CC_LK_RANDOM_KICK;
    stallcount = 100000000;
    repeatcount = -1;
    
    /* Initialize the coordinate data */
    CCutil_init_datagroup (&data);
    CCutil_graph2dat_sparse(n_nodes, n_edges, edges, edges_costs, 0, &data);
    
    /* Verbosity */
    silent = verbose ? 0 : 1;
    
    /* Set time limit value */
    time_limit_value = -1;
    if (time_limit != NULL) {
        time_limit_value = *time_limit;
    }
    
    /* Set target value */
    target_value = -1;
    if (target != NULL) {
        target_value = *target;
    }
    
    /* Call Lin-Kernighan heuristic */
    CClinkern_tour(n_nodes, &data, n_edges, edges, stallcount, repeatcount, 
            in_tour, out_tour, out_cost, silent, time_limit_value, target_value, 
            NULL, kicktype, &rstate);
    
    /* Set return value */
    return_value = DISCORDE_RETURN_OK;
    
    return return_value;
}

int linkernighan_sparse(int n_nodes, int n_edges, int** edges, int* edges_costs, 
        int* out_tour, double* out_cost, int* in_tour, 
        bool verbose, double* time_limit, double* target)
{
    
    /* Auxiliary variables */
    int i, index_edge;
    int return_value;
    
    /* Variables to format data as required by Concorde solver */
    int* edges_list;
    
    /* Create a list of edges as used by Concorde solver */
    edges_list = (int*) malloc(sizeof(int) * n_edges * 2);
    index_edge = 0;
    for (i = 0; i < n_edges; ++i) {
        edges_list[index_edge++] = edges[i][0];
        edges_list[index_edge++] = edges[i][1];
    }
    
    /* Call Lin-Kernighan heuristic */
    return_value = linkernighan(n_nodes, n_edges, edges_list, edges_costs, 
        out_tour, out_cost, in_tour, verbose, time_limit, target);
        
    /* Free resources */
    free(edges_list);
    
    return return_value;
}

int linkernighan_full(int n_nodes, int** cost_matrix, 
            int* out_tour, double* out_cost, int* in_tour, bool verbose, 
            double* time_limit, double* target)
{
    
    /* Auxiliary variables */
    int i, j, index_edge, index_cost;
    int return_value;
    
    /* Variables to format data as required by Concorde solver */
    int n_edges;            /* Number of edges */
    int* edges_list;        /* List of edges (unidimensional) */
    int* edges_costs;       /* Edges costs */
    
    /* Calculate the number of edges */
    n_edges = ((n_nodes * (n_nodes + 1)) / 2) - n_nodes;
    
    /* Allocate resources */
    edges_costs = (int*) malloc(sizeof(int) * n_edges);
    edges_list = (int*) malloc(sizeof(int) * 2 * n_edges);
    
    /* Initialize the list of edges and costs as used by Concorde solver */
    index_edge = 0;
    index_cost = 0;
    for (i = 0; i < n_nodes; ++i) {
        for (j = i + 1; j < n_nodes; ++j) {
            edges_costs[index_cost++] = cost_matrix[i][j];
            edges_list[index_edge++] = i;
            edges_list[index_edge++] = j;
        }
    }
    
    /* Call Lin-Kernighan heuristic */
    return_value = linkernighan(n_nodes, n_edges, edges_list, edges_costs, 
            out_tour, out_cost, in_tour, verbose, time_limit, target);
    
    /* Free resources */
    free(edges_list);
    free(edges_costs);
    
    return return_value;
}