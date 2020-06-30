#include<bits/stdc++.h>

using namespace std;

typedef struct Edge
{ 
    int src, dest, weight; 
}Edge;
 
typedef struct Graph
{
    int V, E;
    struct Edge* edge; 
}Graph;

Graph *createGraph(int V, int E) 
{ 
    struct Graph* graph = new Graph; 
    graph->V = V; 
    graph->E = E; 
    graph->edge = new Edge[E]; 
    return graph; 
}

void printPaths(int parent[], int dist[], int n, int src) 
{
    for (int i = 0; i < n; ++i)
    {
    	stack<int> s;
        printf("\nVertex %d: Distance %d Path ", i, dist[i]);
        int j = i;
        while(j!=src)
        {
        	s.push(parent[j]);
        	j = parent[j];
	}
	while(!s.empty())
	{
		printf("%d ", s.top());
		s.pop();
	}
	printf("%d", i);
    } 
}

void BellmanFord(Graph* graph, int src) 
{ 
    int V = graph->V; 
    int E = graph->E; 
    int dist[V];
    int parent[V];
    int exit_flag = 0;
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0;
    parent[src]=src;
    for (int i = 1; i <= V - 1; i++)
    { 
        for (int j = 0; j < E; j++)
        { 
            int u = graph->edge[j].src; 
            int v = graph->edge[j].dest; 
            int weight = graph->edge[j].weight; 
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                exit_flag = 1;
            }
        } 
    }
    if(exit_flag == 1)
    {
    	exit_flag = 1;
	for (int i = 0; i < E; i++)
	{ 
		int u = graph->edge[i].src; 
		int v = graph->edge[i].dest; 
		int weight = graph->edge[i].weight; 
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
		{ 
		    printf("Graph contains negative weight cycle"); 
		    return;
		} 
	}
    }
    printPaths(parent, dist, V, src);
}

int main() 
{
    int V = 0;
    int E = 0;
    int i = 0;
    printf("Enter vertices count: ");
    scanf("%d", &V);
    printf("Enter edges count: ");
    scanf("%d", &E);
    Graph* graph = createGraph(V, E);
    for(i=0; i<E; i++)
    {
    	printf("Enter edge:\n");
    	printf("Source: ");
    	scanf("%d", &graph->edge[i].src);
    	printf("Destination: ");
    	scanf("%d", &graph->edge[i].dest);
    	printf("Weight: ");
    	scanf("%d", &graph->edge[i].weight);
    }
    BellmanFord(graph, 0);
    printf("\n");
    return 0; 
} 