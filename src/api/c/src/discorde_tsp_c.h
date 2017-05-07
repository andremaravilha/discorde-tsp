#ifndef DISCORDE_TSP_C_H
#define DISCORDE_TSP_C_H

#include <stdlib.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     * Define some constants used by Discorde TSP.
     */
    #ifndef DISCORDE_TSP_CONSTANTS

        /**
         * Returned if the solver has found a feasible tour. It does not 
         * guarantee optimality. For optimality the solver must return 
         * {@code DISCORDE_TSP_RETURN_OK} and the status code must be 
         * {@code DISCORDE_TSP_STATUS_OPTIMAL}.
         */
        #define DISCORDE_TSP_RETURN_OK 0

        /**
         * Returned if the solver was not able to find a feasible tour.
         */
        #define  DISCORDE_TSP_RETURN_FAILURE 1

        /**
         * The solver stopped because the optimal tour was found.
         */
        #define DISCORDE_TSP_STATUS_OPTIMAL 0

        /**
         * The solver stopped because it reached the time limit.
         */
        #define DISCORDE_TSP_STATUS_TIMELIMIT 1

        /**
         * The solver stopped because it found a tour with cost equal or better 
         * than the target value.
         */
        #define DISCORDE_TSP_STATUS_TARGET 2

        /**
         * The solver stopped due to some unknown event.
         */
        #define DISCORDE_TSP_STATUS_UNKNOWN 3

    #endif /* DISCORDE_TSP_CONSTANTS */
    
    
    /**
     * This function solves an instance of the traveling salesman problem (TSP) 
     * using the Concorde solver. Concorde is a branch-and-cut based solver that 
     * solves a TSP instance to optimality, if no time limit or target is set.
     * 
     * @param   n_nodes
     *          Number of nodes.
     * @param   n_edges
     *          Number of edges.
     * @param   edges
     *          An unidimensional array of length {@code 2 * n_edges}. It gives 
     *          the edges in pair of nodes like the original API of Concorde, 
     *          e.g., a list of three edges (a1, a2), (b1, b2), (c1, c2) is 
     *          encoded as an array of six elements given by 
     *          {@code [a1, a2, b1, b2, c1, c2]}.
     * @param   edges_costs
     *          An array of length {@code n_edges} that gives the costs (weights) 
     *          of each edge, following the same order in {@code edges} array.
     * @param   out_tour
     *          An array of length {@code n_nodes} to store the best tour found 
     *          by the solver.
     * @param   out_cost
     *          A pointer to a {@code double} variable to store the cost of the 
     *          best tour ({@code out_tour}) found by the solver.
     * @param   out_status
     *          A pointer to an {@code int} variable which indicates the solver 
     *          status, i.e, which stop criterion has been activated. It may be 
     *          set as {@code NULL} if this information is not desired. The 
     *          values of {@code out_status} at the end of the function may be: 
     *          {@code DISCORDE_TSP_STATUS_OPTIMAL} if a tour has bee found and 
     *          it is optimal; {@code DISCORDE_TSP_STATUS_TIMELIMIT} if the 
     *          solver has stopped because the time limit has been reached; 
     *          {@code DISCORDE_TSP_STATUS_TARGET} if the solver has stopped 
     *          because a tour with cost equal or better than the {@code target} 
     *          value has been found; or {@code DISCORDE_TSP_STATUS_UNKNOWN} if 
     *          the solver has stopped unexpectedly.
     * @param   in_tour
     *          An array of length {@code n_nodes} which gives a starting tour 
     *          in (node, node, ..., node) format. It may be {@code NULL} if no 
     *          feasible tour is known.
     * @param   verbose
     *          If {@code true}, the progress log is printed on the standard 
     *          output. If {@code false}, the progress log is not printed.
     * @param   time_limit
     *          Indicates that the solver should stop as soon as the runtime 
     *          reaches {@code time_limit} seconds. It may be {@code NULL} if no 
     *          time limit is desired.
     * @param   target
     *          Indicates that the solver should stop as soon as it finds a tour 
     *          with cost equal or better than {@code target} value. It may be 
     *          {@code NULL} if no target value is desired.
     * 
     * @return  {@code DISCORDE_TSP_RETURN_OK} if a feasible tour has been found, 
     *          or {@code DISCORDE_TSP_RETURN_FAILURE} otherwise.
     */
    int concorde(int n_nodes, int n_edges, int* edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* out_status, 
            int* in_tour, bool verbose, double* time_limit, double* target);
    
    /**
     * This function solves an instance of the traveling salesman problem (TSP) 
     * using the Concorde solver. Concorde is a branch-and-cut based solver that 
     * solves a TSP instance to optimality, if no time limit or target is set.
     * 
     * @param   n_nodes
     *          Number of nodes.
     * @param   n_edges
     *          Number of edges.
     * @param   edges
     *          An array of dimension {@code n_edges} by {@code 2}. It gives the 
     *          edges in pair of nodes.
     * @param   edges_costs
     *          An array of length {@code n_edges} that gives the costs (weights) 
     *          of each edge, following the same order in {@code edges} array.
     * @param   out_tour
     *          An array of length {@code n_nodes} to store the best tour found 
     *          by the solver.
     * @param   out_cost
     *          A pointer to a {@code double} variable to store the cost of the 
     *          best tour ({@code out_tour}) found by the solver.
     * @param   out_status
     *          A pointer to an {@code int} variable which indicates the solver 
     *          status, i.e, which stop criterion has been activated. It may be 
     *          set as {@code NULL} if this information is not desired. The 
     *          values of {@code out_status} at the end of the function may be: 
     *          {@code DISCORDE_TSP_STATUS_OPTIMAL} if a tour has bee found and 
     *          it is optimal; {@code DISCORDE_TSP_STATUS_TIMELIMIT} if the 
     *          solver has stopped because the time limit has been reached; 
     *          {@code DISCORDE_TSP_STATUS_TARGET} if the solver has stopped 
     *          because a tour with cost equal or better than the {@code target} 
     *          value has been found; or {@code DISCORDE_TSP_STATUS_UNKNOWN} if 
     *          the solver has stopped unexpectedly.
     * @param   in_tour
     *          An array of length {@code n_nodes} which gives a starting tour 
     *          in (node, node, ..., node) format. It may be {@code NULL} if no 
     *          feasible tour is known.
     * @param   verbose
     *          If {@code true}, the progress log is printed on the standard 
     *          output. If {@code false}, the progress log is not printed.
     * @param   time_limit
     *          Indicates that the solver should stop as soon as the runtime 
     *          reaches {@code time_limit} seconds. It may be {@code NULL} if no 
     *          time limit is desired.
     * @param   target
     *          Indicates that the solver should stop as soon as it finds a tour 
     *          with cost equal or better than {@code target} value. It may be 
     *          {@code NULL} if no target value is desired.
     * 
     * @return  {@code DISCORDE_TSP_RETURN_OK} if a feasible tour has been found, 
     *          or {@code DISCORDE_TSP_RETURN_FAILURE} otherwise.
     */
    int concorde_sparse(int n_nodes, int n_edges, int** edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* out_status, 
            int* in_tour, bool verbose, double* time_limit, double* target);
    
    /**
     * This function solves an instance of the traveling salesman problem (TSP) 
     * using the Concorde solver. Concorde is a branch-and-cut based solver that 
     * solves a TSP instance to optimality, if no time limit or target is set.
     * 
     * @param   n_nodes
     *          Number of nodes.
     * @param   cost_matrix
     *          An array of dimension {@code n_nodes} by {@code n_nodes}. It is 
     *          an upper triangular matrix where the element 
     *          {@code cost_matrix[i][j]}, with i less than j, is the cost 
     *          (weight) of the edges (i,j) and (j,i).
     * @param   out_tour
     *          An array of length {@code n_nodes} to store the best tour found 
     *          by the solver.
     * @param   out_cost
     *          A pointer to a {@code double} variable to store the cost of the 
     *          best tour ({@code out_tour}) found by the solver.
     * @param   out_status
     *          A pointer to an {@code int} variable which indicates the solver 
     *          status, i.e, which stop criterion has been activated. It may be 
     *          set as {@code NULL} if this information is not desired. The 
     *          values of {@code out_status} at the end of the function may be: 
     *          {@code DISCORDE_TSP_STATUS_OPTIMAL} if a tour has bee found and 
     *          it is optimal; {@code DISCORDE_TSP_STATUS_TIMELIMIT} if the 
     *          solver has stopped because the time limit has been reached; 
     *          {@code DISCORDE_TSP_STATUS_TARGET} if the solver has stopped 
     *          because a tour with cost equal or better than the {@code target} 
     *          value has been found; or {@code DISCORDE_TSP_STATUS_UNKNOWN} if 
     *          the solver has stopped unexpectedly.
     * @param   in_tour
     *          An array of length {@code n_nodes} which gives a starting tour 
     *          in (node, node, ..., node) format. It may be {@code NULL} if no 
     *          feasible tour is known.
     * @param   verbose
     *          If {@code true}, the progress log is printed on the standard 
     *          output. If {@code false}, the progress log is not printed.
     * @param   time_limit
     *          Indicates that the solver should stop as soon as the runtime 
     *          reaches {@code time_limit} seconds. It may be {@code NULL} if no 
     *          time limit is desired.
     * @param   target
     *          Indicates that the solver should stop as soon as it finds a tour 
     *          with cost equal or better than {@code target} value. It may be 
     *          {@code NULL} if no target value is desired.
     * 
     * @return  {@code DISCORDE_TSP_RETURN_OK} if a feasible tour has been found, 
     *          or {@code DISCORDE_TSP_RETURN_FAILURE} otherwise.
     */
    int concorde_full(int n_nodes, int** cost_matrix, 
            int* out_tour, double* out_cost, int* out_status, 
            int* in_tour, bool verbose, double* time_limit, double* target);
    
    /**
     * This function solves an instance of the traveling salesman problem (TSP) 
     * using the Lin-Kernighan heuristic implemented in Concorde library.
     * 
     * @param   n_nodes
     *          Number of nodes.
     * @param   n_edges
     *          Number of edges.
     * @param   edges
     *          An unidimensional array of length {@code 2 * n_edges}. It gives 
     *          the edges in pair of nodes like the original API of Concorde, 
     *          e.g., a list of three edges (a1, a2), (b1, b2), (c1, c2) is 
     *          encoded as an array of six elements given by 
     *          {@code [a1, a2, b1, b2, c1, c2]}.
     * @param   edges_costs
     *          An array of length {@code n_edges} that gives the costs (weights) 
     *          of each edge, following the same order in {@code edges} array.
     * @param   out_tour
     *          An array of length {@code n_nodes} to store the best tour found 
     *          by the solver.
     * @param   out_cost
     *          A pointer to a {@code double} variable to store the cost of the 
     *          best tour ({@code out_tour}) found by the solver.
     * @param   in_tour
     *          An array of length {@code n_nodes} which gives a starting tour 
     *          in (node, node, ..., node) format. It may be {@code NULL} if no 
     *          feasible tour is known.
     * @param   verbose
     *          If {@code true}, the progress log is printed on the standard 
     *          output. If {@code false}, the progress log is not printed.
     * @param   time_limit
     *          Indicates that the solver should stop as soon as the runtime 
     *          reaches {@code time_limit} seconds. It may be {@code NULL} if no 
     *          time limit is desired.
     * @param   target
     *          Indicates that the solver should stop as soon as it finds a tour 
     *          with cost equal or better than {@code target} value. It may be 
     *          {@code NULL} if no target value is desired.
     * 
     * @return  {@code DISCORDE_TSP_RETURN_OK} if a feasible tour has been found, 
     *          or {@code DISCORDE_TSP_RETURN_FAILURE} otherwise.
     */
    int linkernighan(int n_nodes, int n_edges, int* edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* in_tour, bool verbose, 
            double* time_limit, double* target);
    
    /**
     * This function solves an instance of the traveling salesman problem (TSP) 
     * using the Lin-Kernighan heuristic implemented in Concorde library.
     * 
     * @param   n_nodes
     *          Number of nodes.
     * @param   n_edges
     *          Number of edges.
     * @param   edges
     *          An array of dimension {@code n_edges} by {@code 2}. It gives the 
     *          edges in pair of nodes.
     * @param   edges_costs
     *          An array of length {@code n_edges} that gives the costs (weights) 
     *          of each edge, following the same order in {@code edges} array.
     * @param   out_tour
     *          An array of length {@code n_nodes} to store the best tour found 
     *          by the solver.
     * @param   out_cost
     *          A pointer to a {@code double} variable to store the cost of the 
     *          best tour ({@code out_tour}) found by the solver.
     * @param   in_tour
     *          An array of length {@code n_nodes} which gives a starting tour 
     *          in (node, node, ..., node) format. It may be {@code NULL} if no 
     *          feasible tour is known.
     * @param   verbose
     *          If {@code true}, the progress log is printed on the standard 
     *          output. If {@code false}, the progress log is not printed.
     * @param   time_limit
     *          Indicates that the solver should stop as soon as the runtime 
     *          reaches {@code time_limit} seconds. It may be {@code NULL} if no 
     *          time limit is desired.
     * @param   target
     *          Indicates that the solver should stop as soon as it finds a tour 
     *          with cost equal or better than {@code target} value. It may be 
     *          {@code NULL} if no target value is desired.
     * 
     * @return  {@code DISCORDE_TSP_RETURN_OK} if a feasible tour has been found, 
     *          or {@code DISCORDE_TSP_RETURN_FAILURE} otherwise.
     */
    int linkernighan_sparse(int n_nodes, int n_edges, int** edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* in_tour, bool verbose, 
            double* time_limit, double* target);
    
    /**
     * This function solves an instance of the traveling salesman problem (TSP) 
     * using the Lin-Kernighan heuristic implemented in Concorde library.
     * 
     * @param   n_nodes
     *          Number of nodes.
     * @param   cost_matrix
     *          A array of dimension {@code n_nodes} by {@code n_nodes}. It is 
     *          an upper triangular matrix where the element 
     *          {@code cost_matrix[i][j]}, with i less than j, is the cost 
     *          (weight) of the edges (i,j) and (j,i).
     * @param   out_tour
     *          An array of length {@code n_nodes} to store the best tour found 
     *          by the solver.
     * @param   out_cost
     *          A pointer to a {@code double} variable to store the cost of the 
     *          best tour ({@code out_tour}) found by the solver.
     * @param   in_tour
     *          An array of length {@code n_nodes} which gives a starting tour 
     *          in (node, node, ..., node) format. It may be {@code NULL} if no 
     *          feasible tour is known.
     * @param   verbose
     *          If {@code true}, the progress log is printed on the standard 
     *          output. If {@code false}, the progress log is not printed.
     * @param   time_limit
     *          Indicates that the solver should stop as soon as the runtime 
     *          reaches {@code time_limit} seconds. It may be {@code NULL} if no 
     *          time limit is desired.
     * @param   target
     *          Indicates that the solver should stop as soon as it finds a tour 
     *          with cost equal or better than {@code target} value. It may be 
     *          {@code NULL} if no target value is desired.
     * 
     * @return  {@code DISCORDE_TSP_RETURN_OK} if a feasible tour has been found, 
     *          or {@code DISCORDE_TSP_RETURN_FAILURE} otherwise.
     */
    int linkernighan_full(int n_nodes, int** cost_matrix, 
            int* out_tour, double* out_cost, int* in_tour, bool verbose, 
            double* time_limit, double* target);

#ifdef __cplusplus
}
#endif

#endif /* DISCORDE_TSP_C_H */