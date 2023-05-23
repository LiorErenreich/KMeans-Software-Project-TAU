#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int i, j, counter, numberOfLines, cluster, line, row, column, r, max_iter, cord, d,cnt,dim;
float k , Max_iter;
const int K;
double tmp, norma, p;
char ch, c;
char fl[1000] = "";
char* oneFl;
double* x_i;
double* point;
int* Mio_count;
double** result;
double** N;
double** tmp_Mio;
double** mioSums;
double** mioAvr;
double min_j;

/* Getting the number of dimentions in a vector*/
int dem() {
    counter = 1;
    while ((ch = getchar()) != EOF) {
        if (ch == ',') {
            counter += 1;
        }
        if (ch == '\n') {
            break;
        }
    }
    return counter;
}

/*Getting the number of lines in the file, without the last empty one*/
int numbers_of_lines() {
    counter = 1;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            counter += 1;
        }
        if (ch == EOF) {
            break;
        }
    }
    return counter;
}

double** readlines(int numberOfLines, int d, double** N) {
    /*allocating memory for N*/
    /*N = (double**)malloc(numberOfLines * sizeof(double*));
    for (i = 0; i < numberOfLines; i++) {
        N[i] = (double*)calloc(d, sizeof(double));
    }*/
    /*filling N[Lines][Dimentions]:*/
    row = 0;
    column = 0;
    counter = 0;
    while ((c = getchar()) != EOF) {
        /*regular characters - add to char* fl and count*/
        if ((c != ',') && (c != '\n')) {
            fl[counter] = c;
            counter++;
        }
        /*
        * finished a dimention:
        * 1. save in the percise legth (oneFl)
        * 2. turn into flout (p) and free oneFl
        * 3. save in N[line][dim]
        * 4. reset counter and next dimention
         */
        else if (c == ',') {
            oneFl = calloc(counter, sizeof(char));
            for (i = 0; i < counter; i++) {
                oneFl[i] = fl[i];
            }
            p = atof(oneFl);
            /*printf("%f %d %d\n", p, row, column);*/
            if ((row <= numberOfLines) && (column < d)) {
                if (N[row]) {
                    N[row][column] = p;
                }
                else {
                    perror("N[row] is NULL");
                    exit(EXIT_FAILURE);
                }
            }
            column++;
            free(oneFl);
            counter = 0;
        }
        /*
        * finished a line:
        * 1. save in the percise legth (oneFl)
        * 2. turn into flout (p) and free oneFl
        * 3. save in N[line][dim]
        * 4. reset counter and dimention, next line
         */
        else if (c == '\n') {
            oneFl = calloc(counter, sizeof(char));
            for (i = 0; i < counter; i++) {
                oneFl[i] = fl[i];
            }
            p = atof(oneFl);
            /* printf("%f %d %d\n", p, row, column);*/
            if ((row <= numberOfLines) && (column < d)) {
                if (N[row]) {
                    N[row][column] = p;
                }
                else {
                    perror("N[row] is NULL");
                    exit(EXIT_FAILURE);
                }
            }
            counter = 0;
            column = 0;
            row++;
            free(oneFl);
        }
    }
    return N;
}

double Norma(double* x_i, double* Mio_j, int d) {
    norma = 0.0;
    for (i = 0; i < d; i++) {
        norma += (x_i[i] - Mio_j[i]) * (x_i[i] - Mio_j[i]);
    }
    return norma;
}

/*returns the K centroids after one iteration:
* given result which is the centroids as they are defined at the start of the iteration
* mioSums supposed to be initialized to zeros at the start of this function,
* mioAvr can be accepted with previous values,
*/
double** centroids(double** mioSums, double** mioAvr, double** result, double** N, int* Mio_count, int d, int K, int numberOfLines) {
    /*
    * iterating throghout lines:
    * given a line of doubles, stored as a point:
    * 1. calculates the norn from every centroid in result,
    * 2. updates the minimal norm (min_norm) and the matching closest centroid (min_centroid),
    * 3. addes to matching index in Mio_count and sums the value in every dimention to mioSums
    */
    point = calloc(d, sizeof(double));
    for (line = 0; line < numberOfLines; line++) {
        for (dim = 0; dim < d; dim++) {
            point[dim] = N[line][dim];
        }
        min_j = Norma(point, result[0], d);
        j = 0;

        for (cluster = 0; cluster < K; cluster++)
        {
            tmp = Norma(point, result[cluster], d);
            if (tmp < min_j) {
                min_j = tmp;
                j = cluster;
            }
        }
        Mio_count[j] += 1;

        for (row = 0; row < d; row++) {
            mioSums[j][row] = (mioSums[j][row]) + (point[row]);
        }
    }
    /*
    * recalculate the new centroids:
    * setting to mioAvr the averages of the clusters using the sums and counts,
    * they will be the updated centroids (tmpMio and then result)
     */
    for (cluster = 0; cluster < K; cluster++) {
        for (r = 0; r < d; r++) {
            if (Mio_count[cluster] != 0) {
                mioAvr[cluster][r] = mioSums[cluster][r] / Mio_count[cluster];
            }
            else {
                mioAvr[cluster][r] = result[cluster][r];
                printf("Mio_count[cluster] == 0");
            }
        }
    }
    free((void*) point);
    return (mioAvr);
}

/*prints the desired result properly*/
void cosmetic(double** result, int K, int d) {
    for (cluster = 0; cluster < K; cluster++) {
        for (cord = 0; cord < d; cord++) {
            if (result[cluster][cord]) {
                printf("%.4f", result[cluster][cord]);
            }
            else {
                perror("result[cluster][cord] is NULL");
                exit(EXIT_FAILURE);
            }
            if ((cord + 1) < d) {
                printf("%c", ',');
            }
        }
        printf("\n");
    }
}

void free_data_2D(double** data, int K)
{
    for (i = 0; i < K; ++i) {
        free((void *)data[i]);
    }
    free((void *)data);
}


int main(int argc, char* argv[]) {
    int K = atoi(argv[1]);
    float k = atof(argv[1]);
    if (k != K) {
        printf("K must be int");
    }
    assert(k == K);
    if (K < 0) {
    	printf("K must be positive");
    }
    assert(K >= 0);
    if (argc == 2) {
        max_iter = 200;
    }
    else {
        max_iter = atoi(argv[2]);
        Max_iter = atof(argv[2]);
        if (max_iter != Max_iter) {
            printf("max_iter must be int");
        }
        assert(Max_iter == max_iter);
    }
    d = dem();
    numberOfLines = numbers_of_lines();
    if (max_iter < 0) {
    	printf("max_iter must be positive");
    }
    assert(max_iter >= 0);
    if (K >= numberOfLines) {
    	printf("K >= N is invalid");
    }
    assert(K < numberOfLines);
    rewind(stdin);
    N = (double**)malloc(numberOfLines * sizeof(double*));
    for (i = 0; i < numberOfLines; i++) {
        N[i] = (double*)calloc(d, sizeof(double));
    }
    N = readlines(numberOfLines, d, N);
    Mio_count = calloc(K, sizeof(int));
    for (i = 0; i < K; i++) {
        Mio_count[i] = 1;
    }
    result = (double**)malloc(K * sizeof(double*));
    for (i = 0; i < K; i++) {
        result[i] = (double*)calloc(d, sizeof(double));
    }
    mioSums = (double**)malloc(K * sizeof(double*));
    mioAvr = (double**)malloc(K * sizeof(double*));
    for (cluster = 0; cluster < K; cluster++) {
        mioSums[cluster] = (double*)calloc(d, sizeof(double));
        mioAvr[cluster] = (double*)calloc(d, sizeof(double));
    }
    /* sets the first K lines in N to be the first K centroids*/
    for (i = 0; i < K; i++) {
        if (result) {
            for (j = 0; j < d; j++) {
                if (result[i]) {
                    result[i][j] = N[i][j];
                }
                else {
                    perror("result[i] is NULL when setting the first K clusters");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else {
            perror("result is NULL");
            exit(EXIT_FAILURE);
        }
    }
    counter = 0;
    while (counter < max_iter) {
        free((void *) Mio_count);
        Mio_count = (int *) calloc(K, sizeof(int));
        counter += 1;
        tmp_Mio = centroids(mioSums, mioAvr, result, N, Mio_count, d, K, numberOfLines);
        free_data_2D(mioSums, K);
        mioSums = (double**)malloc(K * sizeof(double*));
        for (cluster = 0; cluster < K; cluster++) {
            mioSums[cluster] = (double*)calloc(d, sizeof(double));
        }
        cnt = 0;
        for (cluster = 0; cluster < K; cluster++) {
            for (row = 0; row < d; row++) {
                if (result[cluster][row] != tmp_Mio[cluster][row]) {
                    cnt++;
                    break;
                }
            }
        }
        if (cnt==0) {
            break;
        }
        else if(cnt !=0) {
            for (cluster = 0; cluster < K; cluster++) {
                for (row = 0; row < d; row++) {
                    result[cluster][row] = tmp_Mio[cluster][row];
                }
            }
        }
    }

    if (Mio_count) {
        free(Mio_count);
    }
    else {
        perror("Mio_count is NULL");
        exit(EXIT_FAILURE);
    }
    cosmetic(result, K, d);
    free_data_2D(N, numberOfLines);
    free_data_2D(mioAvr, K);
    free_data_2D(result, K);
    return 0;
}
