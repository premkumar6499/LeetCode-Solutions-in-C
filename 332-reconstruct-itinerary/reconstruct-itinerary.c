#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* dest;
    int used;
} Edge;

typedef struct {
    char* src;
    Edge* edges;
    int edgeCount;
} Node;

Node* graph;
int graphSize = 0;
char** result;
int resIdx = 0;

// Comparison function for sorting destinations alphabetically
int compareEdges(const void* a, const void* b) {
    return strcmp(((Edge*)a)->dest, ((Edge*)b)->dest);
}

// Find or create a node for an airport
int getNodeIdx(char* airport) {
    for (int i = 0; i < graphSize; i++) {
        if (strcmp(graph[i].src, airport) == 0) return i;
    }
    graph[graphSize].src = strdup(airport);
    graph[graphSize].edges = NULL;
    graph[graphSize].edgeCount = 0;
    return graphSize++;
}

void dfs(char* curr) {
    int idx = -1;
    for (int i = 0; i < graphSize; i++) {
        if (strcmp(graph[i].src, curr) == 0) {
            idx = i;
            break;
        }
    }
    
    if (idx != -1) {
        for (int i = 0; i < graph[idx].edgeCount; i++) {
            if (!graph[idx].edges[i].used) {
                graph[idx].edges[i].used = 1;
                dfs(graph[idx].edges[i].dest);
            }
        }
    }
    result[resIdx++] = strdup(curr);
}

char** findItinerary(char*** tickets, int ticketsSize, int* ticketsColSize, int* returnSize) {
    graph = malloc(sizeof(Node) * (ticketsSize + 1));
    graphSize = 0;
    
    // Build graph
    for (int i = 0; i < ticketsSize; i++) {
        int uIdx = getNodeIdx(tickets[i][0]);
        graph[uIdx].edges = realloc(graph[uIdx].edges, sizeof(Edge) * (graph[uIdx].edgeCount + 1));
        graph[uIdx].edges[graph[uIdx].edgeCount].dest = strdup(tickets[i][1]);
        graph[uIdx].edges[graph[uIdx].edgeCount].used = 0;
        graph[uIdx].edgeCount++;
    }
    
    // Sort edges for each node for lexical order
    for (int i = 0; i < graphSize; i++) {
        qsort(graph[i].edges, graph[i].edgeCount, sizeof(Edge), compareEdges);
    }
    
    result = malloc(sizeof(char*) * (ticketsSize + 1));
    resIdx = 0;
    dfs("JFK");
    
    // Reverse the result
    for (int i = 0; i < resIdx / 2; i++) {
        char* tmp = result[i];
        result[i] = result[resIdx - 1 - i];
        result[resIdx - 1 - i] = tmp;
    }
    
    *returnSize = resIdx;
    return result;
}
