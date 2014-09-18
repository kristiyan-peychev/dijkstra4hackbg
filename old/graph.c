#include "graph.h"

edge edge_init(node *next, long int weight) 
{
	edge ret = (edge *) malloc(1 * sizeof(edge));
	ret.next = next;
	ret.weight = weight;
return ret;
}

long int edge_weight(edge *target) 
{
	return target->weight; /* Not sure if I'll use this at all. */
}

node *edge_next(edge *target) 
{
	return target->next; /* This too. */
}

/* Nodes up */

node *node_init(long int label) 
{
	node *ret = (node *) malloc(1 * sizeof(node));
	ret->label = label;
	ret->edge_sz = 4; /* Initializing the array to four, because I doubt anyone will use more */
	ret->edges = (edge *) malloc(ret->edge_sz * sizeof(edge));
	ret->count = ret->itr_c = 0;
return ret;
}

/*inline */void node_reset_itr(node *target) 
{
	target->itr_c = 0;
}

edge node_itr_next(node *target) 
{
	if (target->itr_c == target->count) 
		return NULL;
return *(target->edges + target_itr_c++);
}

char node_add_edge(node *target, edge victim)
{
	edge buf;
	for (node_reset_itr(target), buf = node_itr_next(target); buf = node_itr_next(target); cc++) 
		if (buf.next == victim.next) 	/* Since we're not in a multigraph, we can't have more than one edge */
			return 0;		/* between each two nodes. We're just ignoring the new weight. */
	edge f = edge_init(target, victim->weight);
return rl_node_add_edge(target, victim) & rl_node_add_edge(victim.next, f); /* Add the edge on both sides */
}

static char rl_node_add_edge(node *target, edge victim) 
{
	edge *buff, buf;
	unsigned cb0 = 0;
	if (target->edge_sz == target->count) {
		buff = (edge *) malloc((target->edge_sz >> 1) * sizeof(edge));
		if (buff == NULL)
			return 1; /* Holy crap, how can this even happen */
		for (node_reset_itr(target), buf = node_itr_next(target); buf = node_itr_next(target); cb0++) 
			*(buff + cb0) = buf; /* You won't see me using fors for other things */
		free(target->edges);
		target->edges = buff;
		target->edge_sz >>= 1; /* *= 2 */
	}
	*(target->edges + target->count) = victim;
	target->count++;
return 0;
}

unsigned node_edges(node *target) 
{
	return target->count;
}

node *node_copy(node *target) 
{
	node *ret = node_init(target->label);
	unsigned cc = 0;
	ret->edges = (edge *) malloc(target->edge_sz * sizeof(edge));
	while (cc < target->edge_count) {
		*(ret->edges + cc) = *(target_edges + cc);
		cc++;
	}
	ret->edge_sz = target->edge_sz;
	ret->count = target->count;
	ret->itr_c = target->itr_c;
return ret;
}

void node_destroy(node *target)
{
	free(target->edges);
	free(target);
}

/* At last - the graph */

graph *init_graph(void) 
{
	graph *ret = (graph *) malloc(1 * sizeof(graph));
	ret->nodes_sz = 4; /* Defaulting to four nodes */
	ret->nodes = (node **) malloc(ret->nodes_sz * sizeof(node *));
	ret->count = ret->itr_c = 0;
return ret;
}

/*inline */void graph_reset_itr(graph *target) 
{
	target->itr_c = 0;
}

node *graph_itr_next(graph *target) 
{
	if (target->itr_c == target->count) 
		return NULL;
return *(target->nodes + target->itr_c++);
}

void graph_add_node(graph *target, node *victim) 
{
	node **nbuf, *buf;
	unsigned cb0 = 0;
	if (target->count == target->nodes_sz) {
		nbuf = (node **) malloc((target->nodes_sz >> 1) * sizeof(node *));
		for (graph_reset_itr(target), buf = graph_itr_next(target); buf = graph_itr_next; cb0++) {
			*(nbuf + cb0) = buf;
			node_destroy(buf); /* Calling the destructor for each node, otherwise we will leak memory */
		}
		free(target->nodes);
		target->nodes = nbuf;
		target->nodes_sz >>= 1; /* *= 2 */
	}
	for (graph_reset_itr(target), buf = graph_itr_next(target); buf = graph_itr_next;) 
		if (buf->label == victim->label) /* Since we identify our nodes by their label, this is a problem */
			return;
	*(target->nodes + target->count++) = node_copy(victim);
