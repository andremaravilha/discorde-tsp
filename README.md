# Discorde TSP

Discorde TSP is an easy-to-use API for Concorde TSP solver in C and C++ programming languages. [Concorde](http://www.math.uwaterloo.ca/tsp/concorde.html) is a solver for the symmetric traveling salesman problem (TSP) written in ANSI C programming language and is freely available for academic purposes. Concorde is a cutting-plane-based exact TSP solver (using [QSopt LP](http://www.math.uwaterloo.ca/~bico/qsopt/) or [CPLEX](http://www.ibm.com/software/commerce/optimization/cplex-optimizer/)).

Concorde solver may be called directly from the command line interface or from C code using its libary that offers an API. However, Concorde API for C is not so well documented and it may be difficult to be used by new users. Therefore, Discorde TSP offers a simple interface for calling Concorde TSP solver from C and C++ programming languages.


## API

### Constants

When calling any of the functions of the Discorde TSP API, one of the following values is returned:

* `DISCORDE_RETURN_OK` : If the solver has found a feasible tour. It does not guarantee optimality. To check optimality, the solver must return DISCORDE_RETURN_OK and the status code must be equal to DISCORDE_STATUS_OPTIMAL.
* `DISCORDE_RETURN_FAILURE` : Returned if the solver was not able to find a feasible tour.

Once a call to a function of the Discorde TSP API has returned, the status code attribute is set to one the possible values. The attribute takes an integer value, but we recommend using one of the pre-defined status constants to check the status in your program.

* `DISCORDE_STATUS_OPTIMAL` : The solver stopped because the optimal tour was found.
* `DISCORDE_STATUS_TIMELIMIT` : The solver stopped because it reached the time limit.
* `DISCORDE_STATUS_TARGET` : The solver stopped because it found a tour with cost equal or better than the target value.
* `DISCORDE_STATUS_UNKNOWN` : The solver stopped due to some unknown event.


### Functions


#### Concorde branch-and-cut based method


##### Concorde style:

###### C:
```c
int concorde(int n_nodes, int n_edges, int* edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* out_status, 
            int* in_tour, bool verbose, double* time_limit, double* target)
```

###### C++:
```c++
int discorde::concorde(int n_nodes, int n_edges, int* edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* out_status = NULL, 
            int* in_tour = NULL, bool verbose = false, double* time_limit = NULL, 
            double* target = NULL)
```

###### Arguments:

Name | Description
-----|------------
n_nodes | Number of nodes.
n_edges | Number of edges.
edges | An unidimensional array of length `2 * n_edges`.  It gives the edges in pair of nodes like the original API of Concorde, e.g., a list of three edges (a1, a2), (b1, b2), (c1, c2) is encoded as an array of six elements given by [a1, a2, b1, b2, c1, c2].
edges_costs | An array of length `n_edges` that gives the costs (weights) of each edge, following the same order in `edges` array.
out_tour | An array of length `n_nodes` to store the best tour found by the solver.
out_cost | A pointer to a `double` variable to store the cost of the best tour (`out_tour`) found by the solver.
out_status | A pointer to an `int` variable which is set by one of the status code (described in section Constant). It may be set as `NULL` if this information is not desired.
in_tour | An array of length `n_nodes` which gives a starting tour in (node, node, ..., node) format. It may be `NULL` if no feasible tour is known.
verbose | If `true`, the progress log is printed on the standard output. If `false`, the progress log is not printed.
time_limit | Indicates that the solver should stop as soon as the runtime reaches `time_limit` seconds. It may be `NULL` if no time limit is desired.
target | Indicates that the solver should stop as soon as it finds a tour with cost equal or better than `target` value. It may be `NULL` if no target value is desired.

###### Return:

`DISCORDE_RETURN_OK` if a feasible tour has been found, `DISCORDE_RETURN_FAILURE` otherwise.


##### Sparse graphs:

###### C:
```c
int concorde_sparse(int n_nodes, int n_edges, int** edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* out_status, 
            int* in_tour, bool verbose, double* time_limit, double* target)
```

###### C++:
```c++
int discorde::concorde_sparse(int n_nodes, int n_edges, int** edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* out_status = NULL, 
            int* in_tour = NULL, bool verbose = false, double* time_limit = NULL, 
            double* target = NULL)
```

###### Arguments:

Name | Description
-----|------------
n_nodes | Number of nodes.
n_edges | Number of edges.
edges | An array of dimension `n_edges` by 2. It gives the edges in pair of nodes.
edges_costs | An array of length `n_edges` that gives the costs (weights) of each edge, following the same order in `edges` array.
out_tour | An array of length `n_nodes` to store the best tour found by the solver.
out_cost | A pointer to a `double` variable to store the cost of the best tour (`out_tour`) found by the solver.
out_status | A pointer to an `int` variable which is set by one of the status code (described in section Constant). It may be set as `NULL` if this information is not desired.
in_tour | An array of length `n_nodes` which gives a starting tour in (node, node, ..., node) format. It may be `NULL` if no feasible tour is known.
verbose | If `true`, the progress log is printed on the standard output. If `false`, the progress log is not printed.
time_limit | Indicates that the solver should stop as soon as the runtime reaches `time_limit` seconds. It may be `NULL` if no time limit is desired.
target | Indicates that the solver should stop as soon as it finds a tour with cost equal or better than `target` value. It may be `NULL` if no target value is desired.

###### Return:

`DISCORDE_RETURN_OK` if a feasible tour has been found, `DISCORDE_RETURN_FAILURE` otherwise.


##### Dense graphs:

###### C:
```c
int concorde_full(int n_nodes, int** cost_matrix, 
            int* out_tour, double* out_cost, int* out_status, 
            int* in_tour, bool verbose, double* time_limit, double* target)
```

###### C++:
```c++
int discorde::concorde_full(int n_nodes, int** cost_matrix, 
            int* out_tour, double* out_cost, int* out_status = NULL, 
            int* in_tour = NULL, bool verbose = false, double* time_limit = NULL, 
            double* target = NULL)
```

###### Arguments:

Name | Description
-----|------------
n_nodes | Number of nodes.
cost_matrix | A array of dimension `n_nodes` by `n_nodes`. It is an upper triangular matrix where the element `cost_matrix[i][j]`, with `i` < `j`, is the cost (weight) of the edges (i,j) and (j,i).
out_tour | An array of length `n_nodes` to store the best tour found by the solver.
out_cost | A pointer to a `double` variable to store the cost of the best tour (`out_tour`) found by the solver.
out_status | A pointer to an `int` variable which is set by one of the status code (described in section Constant). It may be set as `NULL` if this information is not desired.
in_tour | An array of length `n_nodes` which gives a starting tour in (node, node, ..., node) format. It may be `NULL` if no feasible tour is known.
verbose | If `true`, the progress log is printed on the standard output. If `false`, the progress log is not printed.
time_limit | Indicates that the solver should stop as soon as the runtime reaches `time_limit` seconds. It may be `NULL` if no time limit is desired.
target | Indicates that the solver should stop as soon as it finds a tour with cost equal or better than `target` value. It may be `NULL` if no target value is desired.

###### Return:

`DISCORDE_RETURN_OK` if a feasible tour has been found, `DISCORDE_RETURN_FAILURE` otherwise.


#### Lin-Kernighan heuristic


##### Concorde style:

###### C:
```c
int linkernighan(int n_nodes, int n_edges, int* edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* in_tour, bool verbose, 
            double* time_limit, double* target)
```

###### C++:
```c++
int discorde::linkernighan(int n_nodes, int n_edges, int* edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* in_tour = NULL, 
            bool verbose = false, double* time_limit = NULL, double* target = NULL)
```

###### Arguments:

Name | Description
-----|------------
n_nodes | Number of nodes.
n_edges | Number of edges.
edges | An unidimensional array of length `2 * n_edges`.  It gives the edges in pair of nodes like the original API of Concorde, e.g., a list of three edges (a1, a2), (b1, b2), (c1, c2) is encoded as an array of six elements given by [a1, a2, b1, b2, c1, c2].
edges_costs | An array of length `n_edges` that gives the costs (weights) of each edge, following the same order in `edges` array.
out_tour | An array of length `n_nodes` to store the best tour found by the solver.
out_cost | A pointer to a `double` variable to store the cost of the best tour (`out_tour`) found by the solver.
in_tour | An array of length `n_nodes` which gives a starting tour in (node, node, ..., node) format. It may be `NULL` if no feasible tour is known.
verbose | If `true`, the progress log is printed on the standard output. If `false`, the progress log is not printed.
time_limit | Indicates that the solver should stop as soon as the runtime reaches `time_limit` seconds. It may be `NULL` if no time limit is desired.
target | Indicates that the solver should stop as soon as it finds a tour with cost equal or better than `target` value. It may be `NULL` if no target value is desired.

###### Return:

`DISCORDE_RETURN_OK` if a feasible tour has been found, `DISCORDE_RETURN_FAILURE` otherwise.


##### Sparse graphs:

###### C:
```c
int linkernighan_sparse(int n_nodes, int n_edges, int** edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* in_tour, bool verbose, 
            double* time_limit, double* target)
```

###### C++:
```c++
int discorde::linkernighan_sparse(int n_nodes, int n_edges, int** edges, int* edges_costs, 
            int* out_tour, double* out_cost, int* in_tour = NULL, 
            bool verbose = false, double* time_limit = NULL, double* target = NULL)
```

###### Arguments:

Name | Description
-----|------------
n_nodes | Number of nodes.
n_edges | Number of edges.
edges | An array of dimension `n_edges` by 2. It gives the edges in pair of nodes.
edges_costs | An array of length `n_edges` that gives the costs (weights) of each edge, following the same order in `edges` array.
out_tour | An array of length `n_nodes` to store the best tour found by the solver.
out_cost | A pointer to a `double` variable to store the cost of the best tour (`out_tour`) found by the solver.
in_tour | An array of length `n_nodes` which gives a starting tour in (node, node, ..., node) format. It may be `NULL` if no feasible tour is known.
verbose | If `true`, the progress log is printed on the standard output. If `false`, the progress log is not printed.
time_limit | Indicates that the solver should stop as soon as the runtime reaches `time_limit` seconds. It may be `NULL` if no time limit is desired.
target | Indicates that the solver should stop as soon as it finds a tour with cost equal or better than `target` value. It may be `NULL` if no target value is desired.

###### Return:

`DISCORDE_RETURN_OK` if a feasible tour has been found, `DISCORDE_RETURN_FAILURE` otherwise.


##### Dense graphs:

###### C:
```c
int linkernighan_full(int n_nodes, int** cost_matrix, 
            int* out_tour, double* out_cost, int* in_tour, bool verbose, 
            double* time_limit, double* target)
```

###### C++:
```c++
int discorde::linkernighan_full(int n_nodes, int** cost_matrix, 
            int* out_tour, double* out_cost, int* in_tour = NULL, 
            bool verbose = false, double* time_limit = NULL, double* target = NULL)
```

###### Arguments:

Name | Description
-----|------------
n_nodes | Number of nodes.
cost_matrix | A array of dimension `n_nodes` by `n_nodes`. It is an upper triangular matrix where the element `cost_matrix[i][j]`, with `i` < `j`, is the cost (weight) of the edges (i,j) and (j,i).
out_tour | An array of length `n_nodes` to store the best tour found by the solver.
out_cost | A pointer to a `double` variable to store the cost of the best tour (`out_tour`) found by the solver.
in_tour | An array of length `n_nodes` which gives a starting tour in (node, node, ..., node) format. It may be `NULL` if no feasible tour is known.
verbose | If `true`, the progress log is printed on the standard output. If `false`, the progress log is not printed.
time_limit | Indicates that the solver should stop as soon as the runtime reaches `time_limit` seconds. It may be `NULL` if no time limit is desired.
target | Indicates that the solver should stop as soon as it finds a tour with cost equal or better than `target` value. It may be `NULL` if no target value is desired.

###### Return:

`DISCORDE_RETURN_OK` if a feasible tour has been found, `DISCORDE_RETURN_FAILURE` otherwise.


## Building and Running the examples

To build and run the examples, we refer to the files in `examples` directory. There are an example using C programming language (at `examples/c`) and another using C++ programming language (at `examples/cpp`). In addition to the source code showing how to use the Discorde API, it is provided a `Makefile` to compile the example and a `CMakeLists.txt` file for those who prefer to use CMAKE. For both examples the `Makefile` and `CMakeLists.txt` assume a 64-bit Linux distribution, with Concorde's library `libconcorde.a` compiled for CPLEX and stored in `/opt/concorde` directory, and CPLEX installed in `/opt/ibm/ILOG/CPLEX_Studio1271/`.

If you want to create your own project using a Makefile or CMAKE to build a C or C++ program that uses Concorde TSP software through Discorde TSP API, you can adapt the `Makefile` or `CMakeLists.txt` files. The details will depend on your platform and development environment, but we'd like to point out a few tips:

* The program must link Discorde TSP libraries (i.e., `libdiscorde.a`, `libdiscorde_cpp.a`), Condorde TSP libraries (i.e., `libconcorde.a`), and CPLEX (or QSopt LP) libraries (i.e., `libconcert.a, libilocplex.a, libcplex`).
* A C++ program that uses Discorde TSP API must link both Discorde C++ library (i.e., `libdiscorde_cpp.a`) and  Discorde C library (i.e., `libdiscorde.a`). However, for a C program, just the Discorde C library must be linked.


The code has been tested with CPLEX 12.7. If you have used it with a newer version of CPLEX or other solver, please let me know.

