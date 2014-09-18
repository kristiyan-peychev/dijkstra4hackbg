#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

static long int get_min_dist_node(long int *Q, unsigned long int *dist, unsigned sz) 
{ /* We're actually looking for the index of the node in Q */
	long int p = -1, i = 0;
	unsigned long int g = (unsigned long int) -1l;
	while (i < sz) {
		if (dist[i] < g && Q[i] >= 0) {
			p = i;
			g = dist[i];
		}
		i++;
	}
return p;
}

long int *dijkstra(graph *G, node *s) 
{ /* Classic dijkstra implementation with arrays. This will return an array of indecies with the shortest path from all nodes to the source node */
	node *u;
	edge buf;
	long int *Q = (long int *) malloc(graph_node_c(G) * sizeof(long int)); /* This array will contain the labels of the nodes which are not checked yet */
	unsigned long int *dist = (unsigned long int *) malloc(graph_node_c(G) * sizeof(unsigned long int)); /* Distance from source */
	/* The above two arrays will be edited in parallel, it's not the best thing I could've used, but it's 
	 * the first thing that came to mind. */
	long int *prev = (long int *) malloc(graph_node_c(G) * sizeof(long int)); /* The previous node list */
	unsigned i = 0, n = 0, tmdist/*, cc = 0*/;
	dist[s->label] = 0; /* Distance from source node to itself is nil */
	while (i < graph_node_c(G)) {
		if (i != s->label) {
			dist[i] = (unsigned) -1l; /* It's actually supposed to be infinity, but ths is the largest we can get using 32-bits */
			prev[i] = -1l; /* And we're using this as an undefined, since all our nodes will be with positive labels */
		}
		i++;
		Q[i] = i;
	}
	n = i; /* n is the size of Q */
	while (n > 0) {
		i = get_min_dist_node(Q, dist, graph_node_c(G)); /* Get the index of the nearest node */
		Q[i] = -1l; /* Check the node to ensure it doesn't get picked again and to ensure that we won't have an infinite loop */
		u = G->nodes[i]; /* Get the actual node */
		node_reset_itr(u); /* Used for iteration */
		printf("Picked node: %u with %u edges\n", i, node_edges(u));
		for (buf = node_itr_next(u); buf.weight != -1; buf = node_itr_next(u)) {  /* Iterate through all neighbours of u */
		/*cc = 0;*/
		/*while (cc < node_edges(u)) {*/
			/*buf = u->edges[cc];*/
			tmdist = (dist[i] == (unsigned long) -1l ? (unsigned) -1 : dist[i] + buf.weight); /* Calculating new distance while perserving */
			if ((unsigned) tmdist < dist[buf.next]) { /* Relaxation step */                   /* the infinity rule - -1l + anything = -1l  */
				dist[buf.next] = tmdist;
				prev[buf.next] = i;
			}
			/*cc++;*/
		}
		n--;
	}
return prev;
}

#ifdef _TEST_DIJKSTRA_ 
int main(int argc, const char *argv[]) {
	unsigned long int *f;
	graph *G = graph_init();
	node *n0 = node_init(0);
	node *n1 = node_init(1);
	node *n2 = node_init(2);
	node *n3 = node_init(3);
	node *n4 = node_init(4);
	node_add_edge(n2, n4, 11);
	node_add_edge(n0, n1, 9);
	node_add_edge(n0, n3, 17);
	node_add_edge(n1, n2, 1);
	node_add_edge(n1, n3, 21);
	node_add_edge(n1, n4, 40);
	node_add_edge(n2, n3, 12);
	node_add_edge(n3, n4, 17);
	graph_add_node(G, n0);
	graph_add_node(G, n1);
	graph_add_node(G, n2);
	graph_add_node(G, n3);
	graph_add_node(G, n4);
	f = dijkstra(G, *G->nodes);
	unsigned i = 0;
	while (i < graph_node_c(G)) {
		printf("%d\n", f[i]);
		i++;
	}
return 0;
}
#endif 

