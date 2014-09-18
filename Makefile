CC = gcc
CFLAGS = -c
OUTNAME = dijkstra

default: graph.o dijkstra.o main.o
	$(CC) graph.o dijkstra.o main.o -o $(OUTNAME)

graph.o: 
	$(CC) $(CFLAGS) src/graph.c 

min_heap.o: graph.o
	$(CC) $(CFLAGS) src/min_heap.c

dijkstra.o: graph.o
	$(CC) $(CFLAGS) src/dijkstra.c

main.o:
	$(CC) $(CFLAGS) src/main.c 

# Sorta dangerous
clean.o:
	rm ./*.o

clean: clean.o
	rm ./$(OUTNAME)*

