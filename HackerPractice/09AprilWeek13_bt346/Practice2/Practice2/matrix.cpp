//
//  matrix.cpp
//  lab2 version
//
//  Created by Beitong Tian on 3/2/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#include "matrix.hpp"

/**
 Product two Sparse matrix and save the result in another spase matrix.

 @param A*X = B.
 @return the state of the product process.
 */
int productAx(Matrix* A, Matrix* X, Matrix* B){
    if(A == NULL || X== NULL ) return FAILED;
    if(A->col != X -> row) {
        printf("Cannot Do Matrix Product.\n");
        return FAILED;
    }
    int startRow = 0;
    int endRow =0;
    int startCol = 0;
    int endCol =0;
    int r = A->row;
    int c = X->col;
    
    for (int i = 0; i < r; i++) {
        startRow = (A->rowIndex)[i];
        endRow = (A->rowIndex)[i+1];
        
        for (int j = 0; j < c; j ++) {
            
            (B->matrix)[i*c+j] = 0.0;
            for(int p = startRow;p<endRow;p++){
                
                double left = (A->matrix)[p];
                int colNum = (A->colIndex)[p];
                
                
                startCol = (X->rowIndex)[colNum];
                endCol = (X->rowIndex)[colNum + 1];
                
                for (int q = startCol; q < endCol; q++)
                {
                    int colNum2 = (X->colIndex)[q];
                    double right = (X->matrix)[q];
                    if (colNum2 == j){
                        (B->matrix)[i*c+j] += left * right;
                        
                    }
                }
            }
        }
    }
    return SUCCESS;
    
}


/**
 Print all the elements in Sparse matrix
 Print the matrix in full matrix format.
 Print the total non zero elements in matrix.
 Print the non zero values in matrix.
 Print the row index of the matrix.
 Print the col index of the matrix.
 
 @param A is the Sparse to be printed.
 @return nothing.
 */
void printMatrixAll(Matrix *A)
{
    
    printMatrix(A);
    printMatrixNumber(A);
    printMatrixValues(A);
    printMatrixRowIndex(A);
    printMatrixColIndex(A);
}

/**
 Print the matrix in full matrix format.
 
 @param A is the Sparse to be printed.
 @return nothing.
 */
void printMatrix(Matrix *A) {
    int count = 0;
    printf("My matrix is:\n");
    for (int i = 0; i< A -> row; i++) {
        for(int j = 0; j< A->col; j++) {
            if(j==A->colIndex[count] && count < A->rowIndex[i+1]) {
                printf("%10f   ",A->matrix[count]);
                count ++;
            }
            else
                printf("%10f   ",0.0);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 Print the row index in matrix.
 
 @param A is the Sparse to be printed.
 @return nothing.
 */
void printMatrixRowIndex(Matrix *A) {
    printf("Row Index:   ");
    for (int i = 0; i< (A -> row + 1); i++) {
        printf("%10d ", (A->rowIndex)[i]);
    }
    printf("\n");
    printf("\n");
}

/**
 Print the column index in matrix.
 
 @param A is the Sparse to be printed.
 @return nothing.
 */
void printMatrixColIndex(Matrix *A) {
    printf("Colum Index: ");
    for (int i = 0; i< A -> totalElement; i++) {
        printf("%10d ", (A->colIndex)[i]);
    }
    printf("\n");
    printf("\n");
}

/**
 Print the total non zero elements in matrix.
 
 @param A is the Sparse to be printed.
 @return nothing.
 */
void printMatrixValues(Matrix *A) {
    printf("Values:      ");
    for (int i = 0; i< A -> totalElement; i++) {
        printf("%e ", (A->matrix)[i]);
    }
    printf("\n");
    printf("\n");
}

/**
 Print the total non zero elements in matrix.
 
 @param A is the Sparse to be printed.
 @return nothing.
 */
void printMatrixNumber(Matrix *A) {
    printf("The total nonzero element number is:  ");
    printf("%d. \n", (A->totalElement));
    printf("\n");
}



/**
 Generate the sparse matrix. Used in the construtor.
 
 @param matrix is the double array which contains all the matrix non zero values.
 @param outmatrix is the double array which will contain all the non zero values .
 @param rowId is the int array which will contain all the row index .
 @param colId is the int array which will contain all the col index .
 @param row is the row number.
 @param col is the col number.

 @return nothing.
 */
int retrieveElement(double *matrix, double **outmatrix, int **rowId, int **colId, int row, int col) {
    int totalElement = 0;
    *outmatrix = new double[row*col]();
    *colId = new int[row*col]();
    *rowId = new int[row+1]();
    
    if(*outmatrix == NULL || *colId == NULL || *rowId == NULL)
        return 0;
    
    *rowId[0] = 0;
    for (int i = 0; i< row; i++) {
        for (int j = 0; j< col; j++) {
            //printf("%f\n",matrix[i*col+j]);
            if(matrix[i*col+j] != 0) {
                (*outmatrix)[totalElement] = matrix[i*col+j];
                (*colId)[totalElement] = j;
                totalElement ++;
            }
        }
        (*rowId)[i+1] = totalElement;
        
    }
    *colId = (int*)realloc(*colId, totalElement*sizeof(int));
    *outmatrix = (double*)realloc(*outmatrix, totalElement*sizeof(double));
    
    return totalElement;
}

/**
 Free the heap space
 
 @param A is the sparse to be freed.

 @return nothing.
 */
void freeMemory(Matrix *A) {
    delete [] A->matrix;
    delete [] A->rowIndex;
    delete [] A->colIndex;
    A->matrix = NULL;
    A->rowIndex = NULL;
    A->colIndex = NULL;

}

/**
    Process the jacobi solver on the matrix. And save the result in the result matrix
 
 @param A*C = B
 
 @return the state.
 */
int Jacobi(Matrix *A, Matrix *B, Matrix *C) {
    double maxnum = 0;
    double *resultHis = new double[C->row]();
    for(int i = 0; i < C->row; i++) {
        resultHis[i] = 0;
    }

    int count = 0;
    
    do {
        maxnum = 0;
        for (int i = 0; i < C->row; i++) {
            int rowNow = i;
            int rowStart = (A->rowIndex)[i];
            int rowEnd = (A->rowIndex)[i+1];
            double sum = 0;
            double rowcol = 0;
            for(int j = rowStart; j< rowEnd; j++) {
                int colNow = (A->colIndex)[j];
                double aNow = 0;
                aNow = (A->matrix)[j];
                if(colNow!=rowNow)
                {
                    sum+= aNow*resultHis[colNow];
                }
                else {
                    rowcol = aNow;
                }
            }
            double bNow = 0;
            if((B->rowIndex)[i] == (B->rowIndex)[i+1]) bNow = 0;
            else bNow = (B->matrix)[(B->rowIndex)[i]];
            (C->matrix)[i] = (bNow - sum)/rowcol;
            maxnum = std::max(maxnum,abs((C->matrix)[i] - resultHis[i]));
            
        }
        for(int p = 0; p<C->row;p++) {
            resultHis[p] = (C->matrix)[p];
        }
        count ++;
        
       } while (abs(maxnum)>1e-10);

    delete [] resultHis;

    //std::cout << count << std::endl;
    return SUCCESS;
}


/**
 Subtract two double array
 
 @param A the minuend double array
 @param B the subtrahend double array
 @param length the length of the array

 @return the pointer of the new array.
 */
double* twoArraySub(double *A, double*B, int length) {
    double *result = new double[length]();
    for (int i = 0; i< length; i++) {
        result[i] = A[i] - B[i];
    }
    return result;
}

/**
 Calculate the second norm of the array
 
 @param A the array to be calculated
 @param length the length of the array
 
 @return the second_norm.
 */
double second_Norm(double *A, int length) {
    double sum = 0;
    for (int i = 0; i< length; i++) {
        sum+=A[i]*A[i];
    }
    return sqrt(sum);
}

/**
 To judge if the matrix will convergence
 Guarantee the diagonal dominance or largest eigenvalues of the matrix.
 @param A the array to be detected
 
 @return nothing.
 */
void isConvergenceC(Matrix *A){
    for (int i = 0;i<(A->row);i++)
    {   double sum = 0;
        int finddiag = 0;
        double diagno = 0;
        int start = (A->rowIndex)[i];
        int end = (A->rowIndex)[i+1];
        for (int j = start; j < end; j++) {
            if(((A->colIndex)[j])!= i) {
                sum+=(A->matrix)[j];
            }
            else{
                diagno =(A->matrix)[j];
                finddiag = 1;
            }
        }
        if(finddiag == 0) {
            std::cout << "COLINDEX = " <<start << " "<< end << std::endl;
            std::cout << "ERROR. NO DIAG AT: " << i<<" "<< i<< std::endl;
            break;
        }
        if(diagno <= sum) {
            std::cout << "ERROR. DIAG <= SUM! DIAG = " << diagno<<"  SUM = "<< sum<< std::endl;
            break;
        }
    }
    std::cout << "This matrix will convergence!"<<std::endl;
}

/**
 Calculate the ||B-AX||2 / ||B||2
 
 @param A
 @param B
 @param X

 @return nothing.
 */
double calResidual(Matrix *A, double *B, Matrix *X) {
    
    double resultProductTemp[5000] = {0};
    for (int i = 0; i< 5000; i++) {
        resultProductTemp[i] = 1.0;
    }
    Matrix *Product = new Matrix(resultProductTemp,5000,1);
    
    productAx(A, X, Product);
    int rank = A->row;
    double *B_AX = twoArraySub(Product->matrix, B, rank);
    double result1 = second_Norm(B_AX, rank);
    
    double result2 = second_Norm(B, rank);
    double out = result1 / result2;
    return out;
}

/**
 Read the matrix values in a pre-declared matrix A
 
 @param A The matrix to be filled in

 @return nothing.
 */
void readValues(Matrix *A) {
    //read in the values
    int elements = A->totalElement;
    int rank = A-> row;
    ifstream valuesIn("value.csv");
    for (int l = 0; l < elements; l++)
    {
        double m;
        valuesIn >> m;
        (A -> matrix)[l] = m;
    }
    valuesIn.close();
    
    //read in the rowIndex
    ifstream rowIndexIn("rowPtr.csv");
    for (int l = 0; l < rank+1; l++)
    {
        double m;
        rowIndexIn >> m;
        (A -> rowIndex)[l] = (int)(m-1);
    }
    rowIndexIn.close();
    
    //read in the colIndex
    ifstream colIndexIn("colInd.csv");
    for (int l = 0; l < elements; l++)
    {
        double m;
        colIndexIn >> m;
        (A -> colIndex)[l] = (int)(m-1);
    }
    colIndexIn.close();
    //finish reading
}

/**
 Test the product method
 Method:Compare the sum of A multiply 1 vector and the sum of A.
 
 @param A The matrix to be producted
 
 @return the test result.
 */
double mattixProductTest(Matrix *A) {
    double sumAll = 0;
    for (int i = 0; i< A->totalElement; i++) {
        sumAll = sumAll+(A->matrix)[i];
    }
    
    double *result = new double[A->row];
    fill_n(result,5000,1.0);
    Matrix *B = new Matrix(result,A->row,1);
    
    double *Xtemp = new double[A->row];
    fill_n(Xtemp,5000,1.0);
    Matrix *X = new Matrix(Xtemp,A->row,1);
    
    productAx(A, X, B);
    
    double sumAll2 = 0;
    for (int i = 0; i< B->totalElement;i++) {
        sumAll2 +=(B->matrix)[i];
    }
    delete [] result;
    delete [] Xtemp;
    return abs(sumAll - sumAll2);
    
    
}

/**
 Return the current memory usage.
 
 @return the current memory usage.
 */
long long current_used_mem(){
    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;
    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    long long used_memory;
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                          (host_info64_t)&vm_stats, &count))
    {
        used_memory = ((int64_t)vm_stats.active_count +
                                 (int64_t)vm_stats.inactive_count +
                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
    }
    return used_memory;
}

/**
 Test the constructor
 Method:Compare the origin matrix and the reconstructed matrix from the sparse matrix
 
 @param A The sparse matrix
 @param B The original matrix
 
 @return the test result.
 */
double testConstructor(Matrix *A,double * B) {
    double sum = 0;
    int count = 0;
    int colNum = A->col;
    for (int i = 0; i< A -> row; i++) {
        for(int j = 0; j< A->col; j++) {
            if(j==A->colIndex[count] && count < A->rowIndex[i+1]) {
                sum+= (A->matrix[count]- B[i*colNum + j])*(A->matrix[count]- B[i*colNum + j]);
                count ++;
            }
            else {sum+= (0.0- B[i*colNum + j])*(0.0- B[i*colNum + j]);}
        }
    }
    return sqrt(sum);
}

void copyMatrix(Matrix *sourse, Matrix *copy) {
    *(copy->matrix) = *(sourse->matrix);
    copy->col = sourse->col;
    *(copy->colIndex) = *(sourse->colIndex);
    copy->row = sourse->row;
    *(copy->rowIndex) = *(sourse->rowIndex);
    copy->totalElement = sourse->totalElement;
}

