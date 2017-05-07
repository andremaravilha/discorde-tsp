#include "discorde_tsp_cpp.h"
#include <discorde_tsp_c.h>


int discorde_tsp::concorde(int n_nodes, int n_edges, int* edges, int* edges_costs, 
        int* out_tour, double* out_cost, int* out_status, int* in_tour, 
        bool verbose, double* time_limit, double* target)
{
    return ::concorde(n_nodes, n_edges, edges, edges_costs, out_tour, out_cost, 
            out_status, in_tour, verbose, time_limit, target);
}

int discorde_tsp::concorde_sparse(int n_nodes, int n_edges, int** edges, 
        int* edges_costs, int* out_tour, double* out_cost, int* out_status, 
        int* in_tour, bool verbose, double* time_limit, double* target)
{
    return ::concorde_sparse(n_nodes, n_edges, edges, edges_costs, out_tour, 
            out_cost, out_status, in_tour, verbose, time_limit, target);
}

int discorde_tsp::concorde_full(int n_nodes, int** cost_matrix, 
        int* out_tour, double* out_cost, int* out_status, 
        int* in_tour, bool verbose, double* time_limit, double* target)
{
    return ::concorde_full(n_nodes, cost_matrix, out_tour, out_cost, out_status, 
            in_tour, verbose, time_limit, target);
}

int discorde_tsp::linkernighan(int n_nodes, int n_edges, int* edges, 
        int* edges_costs, int* out_tour, double* out_cost, int* in_tour, 
        bool verbose, double* time_limit, double* target)
{
    return ::linkernighan(n_nodes, n_edges, edges, edges_costs, out_tour, 
            out_cost, in_tour, verbose, time_limit, target);
}

int discorde_tsp::linkernighan_sparse(int n_nodes, int n_edges, int** edges, 
        int* edges_costs, int* out_tour, double* out_cost, int* in_tour, 
        bool verbose, double* time_limit, double* target)
{
    return ::linkernighan_sparse(n_nodes, n_edges, edges, edges_costs, out_tour, 
            out_cost, in_tour, verbose, time_limit, target);
}

int discorde_tsp::linkernighan_full(int n_nodes, int** cost_matrix, 
        int* out_tour, double* out_cost, int* in_tour, 
        bool verbose, double* time_limit, double* target)
{
    return ::linkernighan_full(n_nodes, cost_matrix, out_tour, out_cost, in_tour, 
            verbose, time_limit, target);
}