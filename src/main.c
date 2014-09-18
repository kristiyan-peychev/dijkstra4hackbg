#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

extern long int *dijkstra(graph *, node *); /* Look @ dijkstra.c */

int main(int argc, const char *argv[]) {
	graph *G = graph_init();
	node **ns;
	unsigned N = 0, M = 0, cc = 0, wbuf, nbuf, mbuf;
	long int *path;
	scanf("%u %u", &N, &M);
	ns = (node **) malloc(N * sizeof(node *));
	while (cc < N) {
		ns[cc] = node_init(cc);
		cc++;
	}
	cc = 0;
	while (cc < M) {
		scanf("%u %u %u", &nbuf, &mbuf, &wbuf);
		node_add_edge(ns[nbuf], ns[mbuf], wbuf);
		cc++;
	}
	scanf("%u %u", &nbuf, &mbuf);
	cc = 0;
	while (cc < N) {
		graph_add_node(G, ns[cc]);
		cc++;
	}
	/* CALL DIJKSTRA SOMEHOW */
	path = dijkstra(G, G->nodes[nbuf]);
	cc = 0;
	while (path[mbuf] != -1l && path[mbuf] != -1l && path[mbuf] != 0) {
		cc++;
		mbuf = path[mbuf];
	}
	if (path[mbuf] != -1l) {
		printf("%d\n", cc);
	} else {
		printf("-1\n");
	}
return 0;
}

