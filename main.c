// Jay Michael Carlos and Janica Megan Reyes - LBYARCH S14
#define _CRT_SECURE_NO_WARNINGS
#define VECTOR_N_1 1048576
#define VECTOR_N_2 16777216
#define VECTOR_N_3 536870912 // specs suggest 2^30 but you can lower if machine can't handle it. this is 2^29.
#define RAND_LIMIT 1000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// include the external assembly dot product function.
extern float asmDotProduct();

/*
 * cDotProduct() returns the dot product of two vectors.
 * @param n: Length of vector.
 * @param *a: Pointer to first vector a.
 * @param *b: Pointer to first vector b.
 * @return Dot product of two vectors.
 */
float cDotProduct(int n, float* a, float* b)
{
	int i;
	float intProduct; // store the intermediate products.
	float sdot; // store the final answer.
	sdot = 0.0;

	for (i = 0; i < n; i++) {
		intProduct = a[i] * b[i];
		sdot += intProduct;
	}

	return sdot;
}

/* 
 * generateVectorContents creates n random float values for
 * both vectors a and b.
 * @param n: Vector length.
 * @param *a: First vector.
 * @param *b: Second vector.
 */
void generateVectorContents(int n, float **a, float **b)
{
	int i;
	// allocate memory to a and b based on vector length.
	*a = (float *)malloc(n * sizeof(float));
	*b = (float *)malloc(n * sizeof(float));

	// generate vector contents.
	for (i = 0; i < n; i++) {
		(*a)[i] = (float)rand() / (float)(RAND_MAX) * RAND_LIMIT;
	}

	for (i = 0; i < n; i++) {
		(*b)[i] = (float)rand() / (float)(RAND_MAX) * RAND_LIMIT;
	}
}

/*
 * Perform a dot product between two vectors a and b.
 */
int main()
{
	int i;
	int n; // store the length of the vectors.
	float *a = NULL; // store the contents of the first vector.
	float *b = NULL; // store the contents of the second vector.

	float cOutput, asmOutput; // store outputs of each function. should be the same for all passes.

	// initialize clock for measuring time taken.
	clock_t start, end;
	double cTime, asmTime;

	srand(time(NULL));

	// 1. check time taken to process 2^20 values.
	n = VECTOR_N_1;
	generateVectorContents(n, &a, &b);

	// get average C execution time.
	printf("\n2^20 values:\n");
	cTime = 0.0;
	for (i = 0; i < 20; i++) {
		start = clock();
		cOutput = cDotProduct(n, a, b);
		end = clock();
		printf("C output: %f\n", cOutput);
		cTime += ((double)(end - start)) / CLOCKS_PER_SEC;
	}
	cTime /= 20;

	asmTime = 0.0;
	for (i = 0; i < 20; i++) {
		start = clock();
		asmOutput = asmDotProduct(); // TODO: update assembly function call.
		end = clock();
		printf("Assembly output: %f\n", asmOutput);
		asmTime += ((double)(end - start)) / CLOCKS_PER_SEC;
	}
	asmTime /= 20;

	printf("Average C execution time: %lf\n", cTime);
	printf("Average x86-64 assembly execution time: %lf\n", asmTime); // TODO: update with assembly function call.

	free(a);
	free(b);

	// 2. check time taken to process 2^24 values.
	n = VECTOR_N_2;
	generateVectorContents(n, &a, &b);

	// get average C execution time.
	printf("\n2^24 values:\n");
	cTime = 0.0;
	for (i = 0; i < 20; i++) {
		start = clock();
		cOutput = cDotProduct(n, a, b);
		end = clock();
		printf("C output: %f\n", cOutput);
		cTime += ((double)(end - start)) / CLOCKS_PER_SEC;
	}
	cTime /= 20;

	asmTime = 0.0;
	for (i = 0; i < 20; i++) {
		start = clock();
		asmOutput = asmDotProduct(); // TODO: update assembly function call.
		end = clock();
		printf("Assembly output: %f\n", asmOutput);
		asmTime += ((double)(end - start)) / CLOCKS_PER_SEC;
	}
	asmTime /= 20;

	printf("Average C execution time: %lf\n", cTime);
	printf("Average x86-64 assembly execution time: %lf\n", asmTime); // TODO: update with assembly function call.

	free(a);
	free(b);

	// 3. check time taken to process 2^30 values.
	// NOTE: it's normal for this part to appear to "hang" for a while.
	n = VECTOR_N_3;
	generateVectorContents(n, &a, &b);

	// get average C execution time.
	printf("\n2^29 values:\n");
	cTime = 0.0;
	for (i = 0; i < 20; i++) {
		start = clock();
		cOutput = cDotProduct(n, a, b);
		end = clock();
		printf("C output: %f\n", cOutput);
		cTime += ((double)(end - start)) / CLOCKS_PER_SEC;
	}
	cTime /= 20;

	asmTime = 0.0;
	for (i = 0; i < 20; i++) {
		start = clock();
		asmOutput = asmDotProduct(); // TODO: update assembly function call.
		end = clock();
		printf("Assembly output: %f\n", asmOutput);
		asmTime += ((double)(end - start)) / CLOCKS_PER_SEC;
	}
	asmTime /= 20;

	printf("Average C execution time: %lf\n", cTime);
	printf("Average x86-64 assembly execution time: %lf\n", asmTime); // TODO: update with assembly function call.

	free(a);
	free(b);

	return 0;
}