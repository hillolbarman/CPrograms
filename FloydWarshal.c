#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define size 5     //Edges
#define order 4    //Vertices
 
typedef struct {
    unsigned int first;
    unsigned int second;
    int weight;
} weighted_arc;
 
int **floyd_warshall(const weighted_arc *arcs)
{
    unsigned int i, j, k;
    int **distances = malloc(order * sizeof(int *));
    /* Initialise the distance table */
    for (i = 0; i < order; i++) {
        distances[i] = malloc(order * sizeof(int));
        for (j = 0; j < order; j++) {
            if (i == j) {
                distances[i][j] = 0;
            }
            else {
                distances[i][j] = INT_MAX;
            }
        }
    }
    /* Add the distance for each edge */
    for (i = 0; i < size; i++) {
        distances[arcs[i].first][arcs[i].second] = arcs[i].weight;
    }
    /* Calculate the rest of the distances */
    for (i = 0; i < order; i++) {
        for (j = 0; j < order; j++) {
            for (k = 0; k < order; k++) {
                const int djk = distances[j][k];
                const int dji = distances[j][i];
                const int dik = distances[i][k];
                if (dji != INT_MAX && dik != INT_MAX && djk > dji + dik)
                {
                    distances[j][k] = dji + dik;
                }
            }
        }
    }
    return distances;
}
 
/* Connect two edges */
void weighted_arc_connect(weighted_arc *arcs, unsigned int first, unsigned int second, int weight, unsigned int *pos)
{
    arcs[*pos].first = first;
    arcs[*pos].second = second;
    arcs[*pos].weight = weight;
    (*pos)++;
}
 
/* Print a distance table */
void print_distances(int **distances)
{
    unsigned int i, j;
    printf("\nSHORTEST DISTANCE MATRIX:-\n");
    for (i = 0; i < order; i++) {
        for (j = 0; j < order; j++) {
            printf("%d ", distances[i][j]);
        }
        putchar('\n');
    }
}
 
int main(void)
{
    time_t t1, t2, t3;
    t1= time(NULL);
    unsigned int i = 0;
    int f,s,w;
    int **distances;
    weighted_arc *arcs = malloc(size * sizeof(weighted_arc));
    for (int k=1; k<=size; k++)
    {
        scanf("%d %d %d",&f,&s,&w);
        weighted_arc_connect(arcs, f, s, w, &i);
    }
    t2=time(NULL);
    distances = floyd_warshall(arcs);
    print_distances(distances);
    free(arcs);
    for (i = 0; i < order; i++) {
        free(distances[i]);
    }
    free(distances);
    t3=time(NULL);

    printf("Time taken for intialization: %lu\n", t2-t1);
    printf("Time taken for main algo: %lu\n", t3-t2);
    printf("Time taken completely: %lu\n", t3-t1);
    return 0;
}

/*
0 2 -2
1 0 4
1 2 3
2 3 2
3 1 -1

SHORTEST DISTANCE MATRIX:-
0 -1 -2 0 
4 0 2 4 
5 1 0 2 
3 -1 1 0 
Time taken for intialization: 14
Time taken for main algo: 0
Time taken completely: 14
*/