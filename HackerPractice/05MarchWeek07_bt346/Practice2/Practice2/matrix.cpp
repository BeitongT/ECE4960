//
//  matrix.cpp
//  homework4
//
//  Created by Beitong Tian on 3/2/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#include "matrix.hpp"

//the row & col numbers are from 0. i<j

int rowPermute(Matrix *A, Matrix *B, int i, int j) {
    if(B-> col !=1) {
        printf("The second input is not a vector!\n");
        return FAILED;
    }
    if(A->row != B->row) return FAILED;
    
    //    printf("Now permute line %d and line %d.\n",i,j);
    int state1 = rowPermuteSingle(A, i, j);
    int state2 = rowPermuteSingle(B, i, j);
    
    if (!(state1 || state2)) {
        return SUCCESS;
    }
    return FAILED;
}


int rowPermuteSingle(Matrix *A, int i, int j)
{
    
    if(A==NULL) return NULLERROR;
    //printf("detect %d.\n",A->row);
    if (i < 0 || j < 0 || i > ((A->row)-1) || j > ((A->row)- 1)){
        printf("Wrong Input Row Number!\n");
        return FAILED;
    }
    int rowElementA_1 = (A->rowIndex)[i+1] - (A->rowIndex)[i];
    int rowElementA_2 = (A->rowIndex)[j+1] - (A->rowIndex)[j];
    double tempA[A->totalElement];
    int tempColA[A->totalElement];
    
    memcpy(tempA,A->matrix,(A->totalElement)*sizeof(double));
    memcpy(tempColA,A->colIndex,(A->totalElement)*sizeof(int));
    
    int row_number = A->row;
    int rowIndexNumber = row_number + 1;
    
    double *tailA = A->matrix;
    int *tailColA = A->colIndex;
    
    for(int p = 0; p < row_number; p++)
    {
        if(p == i) {
            memcpy(tailA, &tempA[(A->rowIndex)[j]], rowElementA_2 * sizeof(double));
            tailA = tailA + rowElementA_2;
            memcpy(tailColA, &tempColA[(A->rowIndex)[j]], rowElementA_2 * sizeof(int));
            tailColA = tailColA + rowElementA_2;
        }
        else if(p==j) {
            memcpy(tailA, &tempA[(A->rowIndex)[i]], rowElementA_1 * sizeof(double));
            tailA = tailA + rowElementA_1;
            memcpy(tailColA, &tempColA[(A->rowIndex)[i]], rowElementA_1 * sizeof(int));
            tailColA = tailColA + rowElementA_1;
            
        }
        else {
            int tempCountA = (A->rowIndex)[p+1] - (A-> rowIndex)[p];
            memcpy(tailA, &tempA[(A->rowIndex)[p]], tempCountA * sizeof(double));
            tailA = tailA + tempCountA;
            int tempCountColA = (A->rowIndex)[p+1] - (A-> rowIndex)[p];
            memcpy(tailColA, &tempColA[(A->rowIndex)[p]], tempCountColA * sizeof(int));
            tailColA = tailColA + tempCountColA;
        }
    }
    
    int differenceA = rowElementA_2 - rowElementA_1;
    for (int p = 0; p< rowIndexNumber; p++) {
        if(p>i && p<=j) {
            A->rowIndex[p] += differenceA;
        }
    }
    
    return SUCCESS;
}


int rowScale(Matrix *A, Matrix *B, int i, int j, double a) {
    if(B-> col !=1) {
        printf("The second input is not a vector!\n");
        return FAILED;
    }
    if(A->row != B->row) return FAILED;
    if(A==NULL || B ==NULL) return NULLERROR;
    
    int state1 = rowScaleSingle(A, i, j, a);
    int state2 = rowScaleSingle(B, i, j, a);
    
    if (!(state1 || state2)) {
        return SUCCESS;
    }
    return FAILED;
    
}

// Add a*row[i] to row[j] for matrix A and vector x
//calculate the line and compare with the former one. Then use if else to redesign the struct
int rowScaleSingle(Matrix *A, int i, int j, double a) {
    if(A==NULL) return NULLERROR;
    if (i < 0 || j < 0 || i > (A->row)-1 || j > (A->row)- 1){
        printf("Wrong Input Row Number!\n");
        return FAILED;
        
    }
    int colNum = A-> col;
    int row_number = A->row;
    int rowIndexNumber = row_number + 1;
    int colNumStartI = (A -> rowIndex)[i];
    int colNumEndI = (A -> rowIndex)[i+1];
    int colNumStartJ = (A -> rowIndex)[j];
    int colNumEndJ = (A -> rowIndex)[j+1];
    int NumJ = colNumEndJ - colNumStartJ;
    int NumI = colNumEndI - colNumStartI;
    int NumJnew = 0;
    int startI = colNumStartI;
    int startJ = colNumStartJ;
    //define the temp array in the stack not in the heap
    double temp[colNum];
    for (int p = 0; p < colNum; p++) {
        temp[p] = 0.0;
        if(p == (A->colIndex)[startI])
        {
            temp[p] = temp[p] + a* (A->matrix)[startI];
            if(startI < colNumEndI-1) startI++;
            
        }
        if(p == (A->colIndex)[startJ])
        {
            temp[p] = temp[p] + (A->matrix)[startJ];
            if(startJ < colNumEndJ-1) startJ++;
        }
        
    }
    
    Matrix *matrixtemp = new Matrix(temp,1,A->col);
    //    printMatrixAll(matrixtemp);
    NumJnew =(matrixtemp->rowIndex)[1] - (matrixtemp->rowIndex)[0];
    //    printf("numJnew %d.\n",NumJnew);
    //    printf("numj %d.\n",NumJ);
    
    if(NumJnew == NumJ) {
        memcpy(&(A->matrix)[colNumStartJ], matrixtemp->matrix, NumJnew*sizeof(double));
        memcpy(&(A->colIndex)[colNumStartJ], matrixtemp->colIndex, NumJnew*sizeof(double));
    }
    
    else if(NumJnew < NumJ) {
        int total =A->totalElement;
        int difference =NumJnew -NumJ;
        A->totalElement =total + difference;
        if(j != (A->row) - 1)
        {
            memcpy(&(A->matrix)[colNumEndJ + difference], &(A->matrix)[colNumEndJ], (total - colNumEndJ)*sizeof(double));
        }
        
        memcpy( &(A->matrix)[colNumStartJ], matrixtemp->matrix,(NumJnew)*sizeof(double));
        A->matrix = (double*)realloc(A->matrix, (total + difference) * sizeof(double));
        
        if(j != (A->row) - 1)
        {
            memcpy(&(A->colIndex)[colNumEndJ + difference], &(A->colIndex)[colNumEndJ], (total - colNumEndJ)*sizeof(int));
        }
        memcpy( &(A->colIndex)[colNumStartJ], matrixtemp->colIndex,(NumJnew)*sizeof(int));
        A->colIndex= (int*)realloc(A->colIndex, ( total + difference) * sizeof(int));
        
        for(int p = j+1; p < rowIndexNumber;p++)
        {
            (A->rowIndex)[p] += difference;
        }
        
    }
    else if(NumJnew > NumJ){
        int total =A->totalElement;
        int difference =NumJnew -NumJ;
        A->totalElement =total + difference;
        A->matrix = (double*)realloc(A->matrix, (total + difference) * sizeof(double));
        if(j != (A->row) - 1)
        {
            memcpy(&(A->matrix)[colNumEndJ + difference], &(A->matrix)[colNumEndJ], (total - colNumEndJ)*sizeof(double));
        }
        
        memcpy( &(A->matrix)[colNumStartJ], matrixtemp->matrix,(NumJnew)*sizeof(double));
        
        A->colIndex= (int*)realloc(A->colIndex, ( total + difference) * sizeof(int));
        if(j != (A->row) - 1)
        {
            memcpy(&(A->colIndex)[colNumEndJ + difference], &(A->colIndex)[colNumEndJ], (total - colNumEndJ)*sizeof(int));
        }
        memcpy( &(A->colIndex)[colNumStartJ], matrixtemp->colIndex,(NumJnew)*sizeof(int));
        
        for(int p = j+1; p < rowIndexNumber;p++)
        {
            (A->rowIndex)[p] += difference;
        }
        
    }
    
    freeMemory(matrixtemp);
    //    printMatrixAll(A);
    return SUCCESS;
    //this is a method to find the maximum non zero number
    //    for (int p = colNumStartJ; p< colNumEndJ; p++) {
    //        while((A->colIndex)[p] > (A->colIndex)[start] && start < colNumEndI) {
    //            start++;
    //        }
    //        if(start == colNumEndI) break;
    //        else if ((A->colIndex)[p] == (A->colIndex)[start]){
    //            printf("the i is %d.", (A->colIndex)[p]);
    //            printf("the j is %d.", (A->colIndex)[start]);
    //            colNum -- ;
    //            start = start+1;
    //        }
    //    }
    //    newColNumber = colNum;
    //    printf("the total number is %d.\n",newColNumber);
    
}


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
    //    std::cout << r << std::endl;
    //    std::cout << c << std::endl;
    
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



void printMatrixAll(Matrix *A)
{
    
    printMatrix(A);
    printMatrixNumber(A);
    printMatrixValues(A);
    printMatrixRowIndex(A);
    printMatrixColIndex(A);
}

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
}

void printMatrixRowIndex(Matrix *A) {
    printf("Row Index:   ");
    for (int i = 0; i< (A -> row + 1); i++) {
        printf("%10d ", (A->rowIndex)[i]);
    }
    printf("\n");
    printf("\n");
}

void printMatrixColIndex(Matrix *A) {
    printf("Colum Index: ");
    for (int i = 0; i< A -> totalElement; i++) {
        printf("%10d ", (A->colIndex)[i]);
    }
    printf("\n");
    printf("\n");
}

void printMatrixValues(Matrix *A) {
    printf("Values:      ");
    for (int i = 0; i< A -> totalElement; i++) {
        printf("%e ", (A->matrix)[i]);
    }
    printf("\n");
    printf("\n");
}

void printMatrixNumber(Matrix *A) {
    printf("The total nonzero element number is:  ");
    printf("%d. \n", (A->totalElement));
    printf("\n");
}

void printFullMatrix(Eigen::MatrixXd A) {
    std::cout << "Eigen3 matrix is:"<<std::endl;
    std::cout << A <<std::endl;
    std::cout << std::endl;
}



// Instead of using the pointer to pointer, we can also use the reference of the pointer. The syntax is double *& VARIABLE_NAME
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


void freeMemory(Matrix *A) {
    delete [] A->matrix;
    delete [] A->rowIndex;
    delete [] A->colIndex;
    A->matrix = NULL;
    A->rowIndex = NULL;
    A->colIndex = NULL;
    
}

double testMatrix(Matrix *A,Eigen::MatrixXd B) {
    int count = 0;
    double sum = 0;
    int colNum = A->col;
    for (int i = 0; i< A -> row; i++) {
        for(int j = 0; j< A->col; j++) {
            if(j==A->colIndex[count] && count < A->rowIndex[i+1]) {
                sum += sqrt((A->matrix[count])*(A->matrix[count]) - B(i,j)*B(i,j));
                count ++;
            }
            else{
                sum += sqrt(0.0 * 0.0 - B(i,j)*B(i,j));
            }
        }
    }
    return sum;
}

double testMatrix2(Matrix *A,Matrix *B) {
    double sumA = 0;
    double sumB = 0;
    for (int i = 0; i< A->totalElement;i++) {
        sumA+=(A->matrix)[i];
    }
    //    printf("A is %e\n",sumA);
    
    
    for (int i = 0; i< B->row;i++) {
        sumB+=(B->matrix)[i];
    }
    //    printf("B is %d\n",sumB);
    
    double sum = abs(sumB - sumA);
    
    
    return sum;
}

int Jacobi(Matrix *A, Matrix *B, Matrix *C) {
    
    double maxnum = 0;
    double resultHis[5] = {-0.25,0,0,0,0};

    
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
            maxnum = std::max(maxnum,std::abs((C->matrix)[i] - resultHis[i]));
        }
        for(int p = 0; p<C->row;p++) {
            resultHis[p] = (C->matrix)[p];
        }
        count ++;
    } while (abs(maxnum)>1e-7);
    return count;
}



void Jacobi2(float *a,float *b,int row)
{
    
    int i,j;
    int times=0;
    float data=0;
    
    //row代表二维数组a的行数，col代表列数，col应比row大1
    float *x=(float*)malloc(sizeof(float)*row);
    float *y=(float*)malloc(sizeof(float)*row);
    
    for(i=0;i<row;i++)
        x[i]=0;
    
    //迭代过程，MAX为最大迭代次数。
    while(times<=10000)
    {
        times++;
        //        printf("%d\\n",times);
        for(i=0;i<row;i++)
        {
            data=0;
            
            for(j=0;j<row;j++)
            {
                if(j!=i)
                    data=data+a[i*row+j]*x[j];
            }
            
            y[i]=(b[i]-data)/a[i*row+i];
            std::cout <<"result "<< i<< " = "<<y[i]<<std::endl;
            //            printf("%f\\n",y[i]);
        }
        std::cout<<std::endl;
        
        
        for(i=0;i<row;i++)
            x[i]=y[i];
        
    }
}

//int retrieveElement(double *matrix, double **outmatrix, int **rowId, int **colId, int row, int col) {
int retrieveElementOut(Matrix *fullmatrix) {
    
    double * matrix = new double[fullmatrix->totalElement]();
    memcpy(matrix, fullmatrix->matrix, (fullmatrix->totalElement)*sizeof(double));
    int totalElement = 0;
    double *outmatrix = fullmatrix->matrix;
    int *colId = fullmatrix->colIndex;
    int *rowId = fullmatrix->rowIndex;
    int row = fullmatrix -> row;
    int col = fullmatrix -> col;
    if(outmatrix == NULL || colId == NULL || rowId == NULL)
        return FAILED;
    
    rowId[0] = 0;
    for (int i = 0; i< row; i++) {
        for (int j = 0; j< col; j++) {
            //printf("%f\n",matrix[i*col+j]);
            if(matrix[i*col+j] != 0) {
                (outmatrix)[totalElement] = matrix[i*col+j];
                (colId)[totalElement] = j;
                totalElement ++;
            }
        }
        (rowId)[i+1] = totalElement;
        
    }
    colId = (int*)realloc(colId, totalElement*sizeof(int));
    outmatrix = (double*)realloc(outmatrix, totalElement*sizeof(double));
    
    delete [] matrix;
    fullmatrix->totalElement =totalElement;
    return SUCCESS;
}

double * returnToFull(Matrix *A) {
    double * array = new double[(A->row)*(A->col)];
    int numCol = A->col;
    int count = 0;
    printf("My matrix is:\n");
    for (int i = 0; i< A -> row; i++) {
        for(int j = 0; j< A->col; j++) {
            if(j==A->colIndex[count] && count < A->rowIndex[i+1]) {
                array[i*numCol + j] =A->matrix[count];
                count ++;
            }
            else
                array[i*numCol + j] =0;
        }
    }
    return array;
}

double* twoArraySub(double *A, double*B, int length) {
    double *result = new double[length]();
    for (int i = 0; i< length; i++) {
        result[i] = A[i] - B[i];
    }
    return result;
}

double second_Norm(double *A, int length) {
    double sum = 0;
    for (int i = 0; i< length; i++) {
        sum+=A[i]*A[i];
    }
    return sqrt(sum);
}

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


