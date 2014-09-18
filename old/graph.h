#ifndef GRAPH_2JNW1902

#define GRAPH_2JNW1902

typedef struct _edge {
	node *next;
	long int weight; /* Not sure if the weight can or cannot be negative */
} edge;

edge edge_init(node *, long int); /* Constructor! */
long int edge_weight(edge *); 	/* Get the edge's weight */
node *edge_next(edge *); 	/* Get the node on the other side of the edge */

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
char node_add_edge(node *, edge); /* Yes. TODO remove */
void node_destroy(node *); 	/* Destructor, will free the provided pointer */

typedef struct _graph {
	node **nodes;
	unsigned nodes_sz;
	unsigned count_c;
	unsigned itr_c;
} graph;

graph *init_graph(void); 	/* Constructor. */
char graph_add_node(graph *, node *); /* Add nodes this way. TODO remove */
void graph_reset_itr(graph *); 	/* Set the iterator counter (itr_c) to unit value. */
node *graph_itr_next(graph *);
unsigned graph_node_c(graph *);
graph *graph_copy(graph *);
void graph_destroy(graph *);

#endif /* end of include guard: GRAPH_2JNW1902 */
