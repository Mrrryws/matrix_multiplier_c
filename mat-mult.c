#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

//Function checking the number of arguments given by the user
void argument_check(int nr_of_arguments){
    if(nr_of_arguments != 4){
        printf("Please use only 3 arguments in the command line: <M> <N> <seed>\n");
        exit(-1);
    }
}

//Function that generates a matrix with random numbers
void generate_matrix(int rows, int cols, int **matrix){
for(int i = 0; i < rows; i++) {
    	for(int j = 0; j < cols; j++) {
            matrix[i][j] = rand()%100;
    	}
    }
}

//Function that prints a given matrix
void print_matrix(int rows, int cols, int **matrix){
for(int i = 0; i < rows; i++) {
    	for(int j = 0; j < cols; j++) {
    		printf("%d ", matrix[i][j]);
    	}
    	printf("\n");
    }
}

//Function that multiplies two given matrices
void multiply_matrix(int rowsmat1, int colsmat2, int rowsmat2, int **matrix1, int **matrix2, int **result){
for(int i = 0; i < rowsmat1; i++) {
    	for(int j = 0; j < colsmat2; j++) {
            for(int k = 0; k < rowsmat2; k++){
                result[i][j] = result[i][j] + matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

//Main
int main(int argc, char **argv) {
    //Input validation
    argument_check(argc);
    
    double m = atoi(argv[1]);
    double n = atoi(argv[2]);
    double seed = atoi(argv[3]);
    
    //Initialising the seed generation
    srand(seed);

    //Checking the input values are correct
    if(m <= 0 || n <= 0 || seed < -1){
        printf("Please enter values greater than 0 for m and n, and positive values for seed!\n");
        exit(-1);
    }

    // Allocating memory for the first matrix
    int **matrix1;
    matrix1 = malloc(m * sizeof(int *));
    if(matrix1 == NULL){
        return -1;
    }
    for(int i = 0; i < m; i++){
        matrix1[i] = malloc(n * sizeof(int *));
        if(matrix1[i] == NULL){
            return -1;
        }
    }

    // Allocating memory for the second matrix
    int **matrix2;
    matrix2 = malloc(n * sizeof(int *));
    if(matrix2 == NULL){
        return -1;
    }
    for(int i = 0; i < n; i++){
        matrix2[i] = malloc(m * sizeof(int *));
        if(matrix2[i] == NULL){
            return -1;
        }
    }

    // Allocating memory for the resulting matrix
    int **result;
    result = malloc(m * sizeof(int *));
    if(result == NULL){
        return -1;
    }
    for(int i = 0; i < m; i++){
        result[i] = malloc(m * sizeof(int *));
        if(result[i] == NULL){
            return -1;
        }
        for(int j = 0; j < m; j++){
            result[i][j] = 0;
        }
    }

    
    // Printing the first matrix
    printf("MATRIX 1:\n");
    generate_matrix(m,n,matrix1);
    print_matrix(m,n,matrix1);

    // Printing the second matrix
    printf("MATRIX 2:\n");
    generate_matrix(n,m,matrix2);
    print_matrix(n,m,matrix2);

    // Calculating the resulting matrix
    printf("RESULT:\n");

    //Starting the clock before the multiplication
    clock_t start = clock();

    //Performing the matrix multiplication
    multiply_matrix(m, m, n, matrix1, matrix2, result);

    //Ending the clock after the multiplication
    clock_t end = clock();

    //Free the allocated memory of the first matrix
    for(int i = 0; i < m; i++){
        free(matrix1[i]);
    }
    free(matrix1);

    //Free the allocated memory of the second matrix
    for(int i = 0; i < n; i++){
        free(matrix2[i]);
    }
    free(matrix2);
    
    // Printing the resulting matrix
    print_matrix(m,m,result);

    //Free the allocated memory of the resulting matrix
    for(int i = 0; i < m; i++){
        free(result[i]);
    }
    free(result);


    //Calculating the execution time    
    double time_taken = (double)(end - start)/CLOCKS_PER_SEC;

    //Printing the execution time
    printf("EXECUTION TIME: %f\n", time_taken);
    
    return 0;
}
