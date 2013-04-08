#include <iostream> 
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
// Used to define the libalf name space.
//#include <libalf/alf.h>
// Angluin's L* algorithm
//#include <libalf/algorithm_angluin.h>
#include <vector>
#include <map>
#include "../../file_names.h" // ofer

using namespace std;
//using namespace libalf;
int alphabet_size; 
int min_func_idx; // index of first function
bool instrument_branches = false, instrument_functions = false;
bool **matrix;
bool **instrumented_matrix;
bool *first_functions;
int n;
int m;

void m_n_dfs_source(int n, int m, int current, int source);
int cnt;
void predecessors(int m, int current, int *predecessors_list);
void AdjacencyMatrix();
void printArray(bool **matrix_to_print, int num_of_v);

void m_n_dfs(int n, int m){
    

	for( int i=0; i<m; i++){
		for( int j = m; j< n; j++) {
			if( matrix[i][j] == 1 ){
				m_n_dfs_source( n, m, j, i );
			}
		}
	}

	// updating instrumented matrix and first_functions list
	// to be replaced with dfs from main
	for (int t = 0; t < m; ++t){
		first_functions[t] = 1;
		for (int j = 0; j < m; ++j){
			instrumented_matrix[j][t] = matrix[j][t];
			if (matrix[j][t] == 1 && j != t)
				first_functions[t] = 0;
		}
	} 

	int *predecessors_list;
	// predecessors_list = (int *)malloc(m*sizeof(int));
	predecessors_list = new int[m];

	for( int i=0; i<m; i++) {
		for(int j=0; j<m; j++)
			predecessors_list[j]=-1;
		cnt = 0;
		predecessors(m, i, predecessors_list);
		printf(" i = %d: ", i);
	    for( int j=0; j<m; j++) printf("% d ", predecessors_list[j]);
		printf("\n");

		int tmp;
		for(int t = 0; (tmp = predecessors_list[t]) > -1; t++){
				for( int r = 0; r < m; r++){
					int flag = 0;
					if ( (!matrix[tmp][r]) || instrumented_matrix[i][r]) continue;
					for(int tt = 0; predecessors_list[tt] > -1; tt++){
						if (r == predecessors_list[tt]){
							flag = 1;
							break; // if r is one of i's predecessors, it cannot follow i.
						}
					}
					if (i != r && !flag) 
						instrumented_matrix[i][r] = 1;
				}			
		}
	}
	delete(predecessors_list);
	// free( predecessors_list);
}


void m_n_dfs_source(int n, int m, int current, int source ){
 
    int v;
    
	for(v = 0; v < n; v++)
    {
        if(matrix[current][v] == 1) {
			if (v < m) {
				matrix[source][v] = 1;
				return;
			}
			if( v != current){
				m_n_dfs_source( n, m, v, source );
			}
		}
	}
}


void predecessors(int m, int current, int *predecessors_list){
	
	int flag = 0;

	for( int i = 0; i < m; i++){
		flag = 0;
		for(int tt = 0; predecessors_list[tt] > -1; tt++) {
			if (i == predecessors_list[tt]){
				flag = 1;
				break;
			}
		}
		if( (matrix[i][current] == 1) && !flag ){
			predecessors_list[cnt++] = i;
			predecessors(m, i, predecessors_list);
		}
	}

}

// ***************** driver functions ************************************
 
int main()
{
    
    printf("Enter the number of vertices\n");
    scanf("%d",&n);
	printf("Enter the number of instrumented vertices\n");
    scanf("%d",&m);
	
	// initializing the original matrix
	matrix = (bool **)malloc(n*sizeof(bool));
	for(int i = 0; i < n; ++i) {
	     matrix[i] = new bool[n];
	}

	//initializing the instrumented matrix
	instrumented_matrix = (bool **)malloc(m*sizeof(bool));
	for(int i = 0; i < m; ++i) {
	      instrumented_matrix[i] = new bool[m];
	}

	//initializing the first_functions list
	// first_functions = (bool *)malloc(sizeof(bool));
	first_functions = new bool[m];

	printf("matrix initialized\n");
    AdjacencyMatrix();
    m_n_dfs(n, m);
	printf("siblings computed:\n");
	printArray(instrumented_matrix, m );

	// free(matrix);
	// free(instrumented_matrix);
	// free(first_functions);
return 0;
}

void AdjacencyMatrix( ){

    int i,j;

    for(i = 0;i < n; i++)
    {
		for(j = 0;j < n; j++)
        {
			// matrix[i][j] = rand()%2;
			 matrix[i][j] = 0;
        }
    }
	 matrix[0][2] = 1;
	 matrix[0][3] = 1;
	 matrix[2][1] = 1;
//	 matrix[3][0] = 1;

	/*matrix[0][1] = 1;
	matrix[0][2] = 1;
	matrix[2][3] = 1;

	*/
	printf("Matrix filled with randoms\n");
    printArray(matrix, n);
}

void printArray(bool **matrix_to_print, int num_of_v){
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


