#ifndef GRAPH_XIFY978

#define GRAPH_XIFY978

#include <stdlib.h>

#define _TEST_

#ifdef _TEST_
	#include <stdio.h>
#endif

typedef struct _edge {
	long int next; /* The other node's name/label */
	long int weight; /*  Not sire if the weight can be negative or not */
} edge;

edge edge_init(long int, long int); /* Constructor (Label, Weight) */
long int edge_weight(edge); /* Get the edge's weight */
long int edge_next(edge); /* Get the node on the other end */

typedef struct _node {
	long int label; 	/* The node's name */
	edge* edges; 		/* Guess. */
	unsigned edge_sz; 	/* Size of the above array */
	unsigned count; 	/* How many edges are inited */
	unsigned itr_c; 	/* Using it as the iterator counter, because static members are gay. */
} node;

node *node_init(long int);	/* You can add your edges later. */
void node_reset_itr(node *); 	/* Set the iterator counter (itr_c) to unit value. */
edge node_itr_next(node *);	/* Get the next edge in the argument */
unsigned node_edges(node *);	/* Get the edge count */
char node_add_edge(node *, node *, long int); /* The two nodes and the weight of the edge between them. This will ignore a second edge. TODO remove */
void node_destroy(node *); 	/* Destructor, will free the provided pointer */
node *node_copy(node *); 	/* Copy the nodes using this, not = */

typedef struct _graph {
	node **nodes;
	unsigned nodes_sz;
	unsigned count;
	unsigned itr_c;
} graph;

graph *graph_init(void); 	/* Constructor. */
void graph_add_node(graph *, node *); /* Add nodes this way. TODO remove */
void graph_reset_itr(graph *); 	/* Set the iterator counter (itr_c) to unit value. */
node *graph_itr_next(graph *);
unsigned graph_node_c(graph *);
graph *graph_copy(graph *);
void graph_destroy(graph *);

#endif /* end of include guard: GRAPH_XIFY978 */
