#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#if 0
long int get_min_dist_node(long int *Q, unsigned long int *dist, unsigned sz) 
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
#endif

long int *dijkstra(graph *G, node *s) 
{
	min_heap *Q = min_heap_init();
	node *u;
	edge buf;
	node_dist next;
	/*unsigned long int *Q = (unsigned long int *) malloc(graph_node_c(G) * sizeof(unsigned long int));*/
	/*unsigned long int *dist = (unsigned long int *) malloc(graph_node_c(G) * sizeof(unsigned long int)); [> Distance from source <]*/
	long int *prev = (long int *) malloc(graph_node_c(G) * sizeof(long int)); /* The previous node list */
	unsigned i = 0, n = 0, tmdist, cc = 0;
	/*dist[s->label] = 0; [> Distance from source node to itself is nil <]*/
	min_heap_insert(Q, node_dist_init(s, 0)); /* ^ */
	while (i < graph_node_c(G)) {
		if (i != s->label) {
			/*dist[i] = (unsigned) -1l; [> It's actually supposed to be infinity, but ths is the largest we can get using 32-bits <]*/
			min_heap_insert(Q, node_dist_init(G->nodes[i], (unsigned long int) -1l)); /* Initializing the distance with the closest to infinity we can get */
			prev[i] = -1l; /* And we're using this as an undefined, since all our nodes will be with positive labels, hopefully */
		}
		i++;
	}
	n = i; /* n will be the size of Q */
	while (n > 0) {
		/*i = get_min_dist_node(Q, dist, graph_node_c(G));*/
		/*Q[i] = -1l;*/
		next = min_heap_pull(Q);
		u = next.np;
		node_reset_itr(u);
		printf("Picked node: %u with %u edges\n", i, node_edges(u));
		/* for (buf = node_itr_next(u); buf.weight != -1; buf = node_itr_next(u)) { */
		cc = 0;
		while (cc < node_edges(u)) {
			buf = u->edges[cc];
			printf("Looping though node %u\n", buf.next);
			tmdist = (dist[i] == (unsigned long long) -1l ? (unsigned) -1 : dist[i] + buf.weight); /* Err... */
			printf("CMP: %u, %u\n", tmdist, dist[buf.next]);
			if ((unsigned) tmdist < dist[buf.next]) {
				printf("DM SUCCEDED: %u with %u\n", tmdist, dist[buf.next]);
				dist[buf.next] = tmdist;
				prev[buf.next] = i;
			}
			cc++;
		}
		printf("Next.\n");
		n--;
	}
return prev;
}

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
