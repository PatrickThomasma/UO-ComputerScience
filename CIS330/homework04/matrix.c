#include "matrix.h"

/* Debugging code that prints the BFS result for a particular iteration
   input parameters:
       int  rows	# of vertices
       int* color	array of color for the vertices
       int* distance	array of distance for the vertices
   return parameters:
       none
 */

void print_bfs_matrix_result(int rows, int* color, int* distance)
{
    assert(color);
    assert(distance);

    fprintf(stdout, "---- Print BFS Matrix Result ----\n");
    fprintf(stdout, "Vert\tCol\tDis\n");
    for(int i = 0; i < rows; i++) {
        fprintf(stdout, "%d\t%d\t%d\n", i, color[i], distance[i]);
    }
    fprintf(stdout, "--------\n\n");
}


/* Debugging code that prints a vector
   input parameters:
       int* vector	vector whose content we wish to print
       int  rows	# of elements in the vector
   return parameters:
       none
 */
void print_vector(int* vector, int rows)
{
    assert(vector);

    fprintf(stdout, "---- Print Vector ----\n");
    for(int i = 0; i < rows; i++) {
        fprintf(stdout, "%d\n", vector[i]);
    }
    fprintf(stdout, "--------\n\n");
}


/* Debugging code that prints the content of a 2D matrix
   input parameters:
       int* matrix	2D matrix we wish to print2D matrix we wish to print
       int  rows	# of rows of the input matrix
       int  cols	# of cols of the input matrix
   return parameters:
       none
 */
void print_matrix(int **matrix, int rows, int cols)
{
    assert(matrix);

    fprintf(stdout, "---- Print Matrix ----\n");
    fprintf(stdout, "This matrix is %d x %d\n", rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            fprintf(stdout, "%d ", matrix[i][j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "--------\n\n");

}


/* This function takes in a 2D matrix (src), transposes it and 
   then stores it in a destination 2D matrix (dst).
   Transpose operation takes each src[i][j] element and stores it
   in dst[j][i]
   
   input parameters:
       int** dst	Where you store the transpose of src
                        Dimensions are cols x rows
       int** src	Matrix you want to transpose
                        Dimensions are rows x cols
       int   rows	# of rows of input matrix (src)
       int   cols	# of cols of input matrix (src)
   return parameters:
       none
 */
void matrix_transpose(int** dst, int** src, int rows, int cols)
{
    assert(dst);
    assert(src);
    assert(rows == cols);

    int i, j;
    for (i = 0; i < cols; ++i) {
	    for (j = 0; j < rows; ++j) {
		    dst[i][j] = src[j][i];
	    }
    }
}







/* This function 'resets a vetor to have all
   zero value
   input parameters:
       int* vector	the input vector to reset
       int  rows	the number of elements in the vector
   return parameters:
       none
 */
void reset_vector(int* vector, int rows)
{
    assert(vector);

    for(int i = 0; i < rows; i++) {
        vector[i] = 0;
    }
}


/* SpMV-based BFS implementation
   input parameters:
   These are 'consumed' by this function
       int** int_array	input array representing the adjacency
                        matrix
       int   rows	# of rows of the adajcency matrix
       int   cols	# of cols of the adajcency matrix
       int   source	source vertex for the BFS
   These are 'produced' by this function
       int*  color	color array
       int*  distance	distance array
   return parameters:
       none
  */
void bfs_spmv(int** int_array, int rows, int cols, int source,
              int* color, int* distance)
{
    // check the input parameters to see if they are valid
    if(rows != cols) {
        fprintf(stderr, "Not an adjacency matrix\n");
	exit(EXIT_FAILURE);
    }
    if(source >= rows) {
        fprintf(stderr, "Invalid source vertex\n");
	exit(EXIT_FAILURE);
    }
    assert(int_array);
    assert(color);
    assert(distance);

    fprintf(stdout, "Breadth first search on the graph using SpMV ... ");

    // Transpose the adjacency matrix
    int** mat_trans = NULL;
    init_2d_array(&mat_trans, cols, rows);
    matrix_transpose(mat_trans, int_array, rows, cols);
    //print_matrix(mat_trans, cols, rows);
    // Initialize the various data structures
    int* vec = (int*) malloc(sizeof(int) * rows);
    assert(vec);
    for(int i = 0; i < rows; i++) {
        if(i == source) {
            vec[i] = 1;
            color[i] = 2;
            distance[i] = 0;
        } else {
            vec[i] = 0;
            color[i] = 0;
            distance[i] = -1;
        }
    }
    int* res = (int*) malloc(sizeof(int) * cols);
    assert(res);
    reset_vector(res, cols);


    int iter = 1;
    int done = 0;
    int *src = vec;
    int *dst = res;
    // Do BFS until done
    while(!done) {
	    for (int k = 0; k < cols; k++) {
		    if (src[k] != 0) {
			    color[k] = 2;
		    }
	    }
	     //before spmv color visited nodes too 2

	    for (int i = 0; i < rows; i++) {
		    for (int j = 0; j < cols; j++) {
			    dst[i] += src[j] * mat_trans[i][j];
		    }
	    } //spmv multiplication to get everything from source into destination
	    for (int t = 0; t < cols; t++) {
		    if (dst[t] != 0) {
			    if (color[t] == 2) {
				    dst[t] = 0; //set vector to 0 if it has been visited
			    }
		    }
	    } //if the color is 2 then node has bene visited if not then oh well
	    for (int p = 0; p < cols; p++) {
		    if (dst[p] != 0) {
			    distance[p] = iter;
		    }
	    } //if node hasnt been visited it should be a 1 and thus update the distance

	    for (int f = 0; f < cols; f++) {
		    src[f] = dst[f];
	    }
	    done = 1; //set done = 1 so if there is still 1's then it'll go back to 0
	    for (int z = 0; z < cols; z++)
	    {
		    if (dst[z] != 0) {
			    done = 0; //done back to 0 if there is a 1
		    }
	    }
               //reset vectors at the end
	    reset_vector(dst,cols);
	    iter++;


    }
    

		    



	    //implement spmv algorithm, once I have that line of dst then use dst as
	    // adjacency vector, for the given vector go through it and color each node
	    // appropriately based on whether or not there is a adjacency to it, after updating
	    // the colors, update the dst vector to reflect the new colors if you have visited 
	    // all nodes then make dst 0 copy dst into src check if dst is all 0's
	    


        // INSERT YOUR CODE HERE

        // given a vector of source vetices, find the neighbors
        // HINT: spmv 

        // color the source vertices for this iteration `black'

        // store the distance for the newly discovered neighbors

        // Before we begin, eliminate vertices that have already been visited

        // Check to see if no neighbors were found,
        // in which case, we are done

        // iter is equivalent to each `breadth' searched (i.e., distance from
        // the source vertex

    fprintf(stdout, "done\n");

    #if DEBUG
        print_bfs_matrix_result(rows, color, distance);
    #endif

    free_2d_array(mat_trans, cols);
    free(vec);
    free(res);
}


/* This function allocates memory for a 2D array of size rows x cols
   input parameters
       int*** arr		reference to the 2D array you want to init
       int    rows		# of rows in the 2D array
       int    cols		# of columns in the 2D array
   return parameters:
        none
 */
void init_2d_array(int*** arr, int rows, int cols)
{
    int** tmpArr = (int**) malloc(sizeof(int*) * rows);
    assert(tmpArr);
    for(int i = 0; i < rows; i++) {
        tmpArr[i] = (int*) malloc(sizeof(int) * cols);
        assert(tmpArr[i]);
    }
    *arr = tmpArr;

}


/* This function frees memory allocated to a 2D array.
   input parameters:
       int** arr	the 2D array to deallocate
       int   rows	# of rows of the matrix
   return parameters:
       none
 */
void free_2d_array(int** arr, int rows)
{
    for(int i = 0; i < rows; i++) {
        // free each row
        free(arr[i]);
    }
    // free the matrix
    free(arr);
}
