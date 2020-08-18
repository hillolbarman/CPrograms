#include <stdio.h> 
#include <time.h>
#define V 4 

void printSolution(int reach[][V]); 
void transitiveClosure(int graph[][V]) 
{ 
    int reach[V][V], i, j, k; 
    for (i = 0; i < V; i++) 
        for (j = 0; j < V; j++) 
            reach[i][j] = graph[i][j]; 
  
    
    for (k = 0; k < V; k++) 
    { 
        for (i = 0; i < V; i++) 
        { 
            for (j = 0; j < V; j++) 
            { 
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]); 
            } 
        } 
    } 
  
    printSolution(reach); 
} 
void printSolution(int reach[][V]) 
{ 
    printf ("Following matrix is transitive closure of the given graph\n"); 
    for (int i = 0; i < V; i++) 
    { 
        for (int j = 0; j < V; j++) 
            printf ("%d ", reach[i][j]); 
        printf("\n"); 
    } 
} 

void intitialize(int graph[V][V]){
    int a,b;
    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++)
            scanf("%d", &graph[i][j]);
    }
}
  
// Driver program
int main() 
{ 
    time_t t1, t2, t3;
    t1= time(NULL);
    int graph[V][V];
    intitialize(graph);
    t2= time(NULL);
    // Print the solution 
    transitiveClosure(graph);
    t3= time(NULL);
    printf("\nTime taken for intialization: %lu\n", t2-t1);
    printf("Time taken for main algo: %lu\n", t3-t2);
    printf("Time taken completely: %lu\n", t3-t1);
    return 0; 
} 
/*
1 1 0 1
0 1 1 0
0 0 1 1
0 0 0 1
Following matrix is transitive closure of the given graph
1 1 1 1 
0 1 1 1 
0 0 1 1 
0 0 0 1 

Time taken for intialization: 11
Time taken for main algo: 0
Time taken completely: 11
*/