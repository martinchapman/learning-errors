#include <iostream> 
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
// Used to define the libalf name space.
#include <libalf/alf.h>
// Angluin's L* algorithm
#include <libalf/algorithm_angluin.h>
#include <vector>
#include <map>
#include "../../file_names.h" // ofer

using namespace std;
using namespace libalf;
int alphabet_size; 
int min_func_idx; // index of first function
bool instrument_branches = false, instrument_functions = false;
int **matrix;
int **instrumented_matrix;
int *first_functions;
int n;
int m;

void m_n_dfs_source(int n, int m, int current, int source);
void predecessors(int m, int current, int *predecessors_list);
void AdjacencyMatrix();
void printArray(int **matrix_to_print, int num_of_v);

void m_n_dfs(int n, int m){
     
	int *pos;

	pos = (int *)malloc(sizeof(int));
	pos = new int;
    *pos = 0;

	// int self_loops[m];
	// for(int i=0; i<m; i++)
		// self_loops[i]=0;

	for( int i=0; i<m; i++)
		m_n_dfs_source( n, m, i, i );

	//copying into a smaller matrix

	//initializing
	instrumented_matrix = (int **)malloc(m*m*sizeof(int));

	//initializing the first_functions list
	first_functions = (int *)malloc(m*sizeof(int));

	// updating matrix and first_functions list
	for (int t = 0; t < m; ++t){
		first_functions[t] = 1;
		for (int j = 0; j < m; ++j){
			instrumented_matrix[j][t] = matrix[j][t];
			if (matrix[j][t] == 1 && j != t)
				first_functions[t] = 0;
		}
	}

	int *predecessors_list;
	predecessors_list = (int *)malloc(m*sizeof(int));

	for( int i=0; i<m; i++){
		for(int j=0; j<m; j++)
			predecessors_list[m]=0;

		predecessors(m, i, predecessors_list);

		for(int t = 0; t < m; t++){
			if( predecessors_list[t] == 1){
				for( int r = 0; r < m; r++){
					if ( (i != r) || (matrix[i][i] == 1) ) 
						instrumented_matrix[i][r] = instrumented_matrix[i][r] || matrix[t][r];
				}
			}
		}
	}
}


void m_n_dfs_source(int n, int m, int current, int source ){
 
    int v;
    
	for(v = 0; v < n; v++)
    {
        if( matrix[current][v] == 1 ){
			matrix[source][v] = 1;
			if( v >= m ){
				m_n_dfs_source( n, m, v, source );
			}
		}
	}
}


void predecessors(int m, int current, int *predecessors_list){

	for( int i = 0; i < m; i++){
		if( (matrix[i][current] == 1) && (predecessors_list[i] == 0) ){
			predecessors_list[i] = 1;
			predecessors(m, i, predecessors_list);
		}
	}

}


// ***************** driver functions ************************************
 
int main()
{
    // int *q;
    printf("Enter the number of vertices\n");
    scanf("%d",&n);
	printf("Enter the number of instrumented vertices\n");
    scanf("%d",&m);
    // q = (int *)malloc(sizeof(int)*n);
	//initializing
	matrix = (int **)malloc(n*n*sizeof(int));
	for(int i = 0; i < n; ++i) {
	     matrix[i] = new int[n];
	}
	printf("matrix initialized\n");
    AdjacencyMatrix();
    m_n_dfs(n, m);
	printf("siblings computed:\n");
	printArray(instrumented_matrix, m );
return 0;
}

void AdjacencyMatrix( ){

    int i,j;
    for(i = 0;i < n; i++)
    {
        for(j = 0;j < n; j++)
        {
            matrix[i][j] = rand()%2;
			// matrix[i][j] = 0;
        }
    }
	// matrix[0][2] = 1;
	// matrix[0][3] = 1;
	// matrix[2][1] = 1;
	// matrix[3][0] = 1;

	printf("Matrix filled with randoms\n");
    printArray(matrix, n);
}

void printArray(int **matrix_to_print, int num_of_v){
    int i,j;
    for(i=0;i< num_of_v;i++)
    {
        for(j=0;j< num_of_v; j++)
        {
            printf("%d\t",matrix_to_print[i][j]);
        }
        printf("\n");
    }
}


