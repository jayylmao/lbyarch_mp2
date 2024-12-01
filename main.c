// Jay Michael Carlos and Janica Megan Reyes - LBYARCH S14
#define VECTOR_N_1 1048576
#define VECTOR_N_2 16777216
#define VECTOR_N_3 536870912 // specs suggest 2^30 but you can lower if machine can't handle it. this is 2^29.
#define RAND_LIMIT 1000.0f

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// include the external assembly dot product function.
extern float asmDotProduct(int n, float* a, float* b);

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
	float sdot = 0.0f; // store the final answer.

	for (i = 0; i < n; i++) {
		sdot += a[i] * b[i];
	}

	return sdot;
}

/* 
 * generateVectorContents creates n random float values for
 * both vectors a and b.
 * @param n: Vector length.
 * @param **a: First vector.
 * @param **b: Second vector.
 */
void generateVectorContents(int n, float **a, float **b)
{
	
	int i;
	// allocate memory to a and b based on vector length.
	*a = (float *)malloc(n * sizeof(float));
	*b = (float *)malloc(n * sizeof(float));
	
	if (*a == NULL || *b == NULL) {
		printf("[!] Memory failure: Failed to initialize memory. Program terminating.");
		exit(1);
	}

	// generate vector contents.
	for (i = 0; i < n; i++) {
		(*a)[i] = ((float)rand() / (float)RAND_MAX) * RAND_LIMIT;
	}

	for (i = 0; i < n; i++) {
		(*b)[i] = ((float)rand() / (float)RAND_MAX) * RAND_LIMIT;
	}
}

/* 
 * checkCorrectness() checks that the assembly output is the same as the C output.
 * @param cOutput: Output from C dot product function.
 * @param asmOutput: Output from assembly dot product function.
 */
void checkCorrectness(float cOutput, float asmOutput)
{
	if (fabs(cOutput - asmOutput) < 1e-6) {
		printf("[/] Correctness check passed: Assembly output is the same as the C output.\n\n");
	}
	else {
		printf("\n[X] Correctness check failed: Assembly output is different from the C output.\n");
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

	srand((unsigned int)time(NULL));

	// 1. check time taken to process 2^20 values.
	n = VECTOR_N_1;
	

	// get average execution time of both c and asm.
	printf("\n1. 2^20 values:\n");
	cTime = 0.0;
	asmTime = 0.0;
	printf("\n[*] Generating random vector values may take a while.\n");
	for (i = 0; i < 20; i++) {
		generateVectorContents(n, &a, &b);
		start = clock();
		cOutput = cDotProduct(n, a, b);
		end = clock();
		printf("\t\bC output: %f\n", cOutput);
		cTime += ((double)(end - start)) / CLOCKS_PER_SEC;
		start = clock();
		asmOutput = asmDotProduct(n, a, b);
		end = clock();
		printf("Assembly output: %f\n", asmOutput);
		asmTime += ((double)(end - start)) / CLOCKS_PER_SEC;
		checkCorrectness(cOutput, asmOutput);
		free(a);
		free(b);
	}
	cTime /= 20;
	asmTime /= 20;
	
	printf("Average C execution time: %lf\n", cTime);
	printf("Average x86-64 assembly execution time: %lf\n", asmTime);

	// 2. check time taken to process 2^24 values.
	n = VECTOR_N_2;
	generateVectorContents(n, &a, &b);

	// get average C execution time.
	printf("\n2. 2^24 values:\n");
	cTime = 0.0;
	asmTime = 0.0;
	printf("\n[*] Generating random vector values may take a while.\n");
	for (i = 0; i < 20; i++) {
		generateVectorContents(n, &a, &b);
		start = clock();
		cOutput = cDotProduct(n, a, b);
		end = clock();
		printf("\t\bC output: %f\n", cOutput);
		cTime += ((double)(end - start)) / CLOCKS_PER_SEC;
		start = clock();
		asmOutput = asmDotProduct(n, a, b);
		end = clock();
		printf("Assembly output: %f\n", asmOutput);
		asmTime += ((double)(end - start)) / CLOCKS_PER_SEC;
		checkCorrectness(cOutput, asmOutput);
		free(a);
		free(b);
	}
	cTime /= 20;
	asmTime /= 20;
	
	printf("Average C execution time: %lf\n", cTime);
	printf("Average x86-64 assembly execution time: %lf\n", asmTime);

	// 3. check time taken to process 2^29 values.
	// NOTE: it's normal for this part to appear to "hang" for a while.
	//       this process takes up 4GB of ram.
	n = VECTOR_N_3;
	
	// get average C execution time.
	printf("\n3. 2^29 values:\n");
	cTime = 0.0;
	asmTime = 0.0;
	printf("\n[*] Generating random vector values may take a while.\n");
	for (i = 0; i < 20; i++) {
		generateVectorContents(n, &a, &b);
		start = clock();
		cOutput = cDotProduct(n, a, b);
		end = clock();
		printf("\t\bC output: %f\n", cOutput);
		cTime += ((double)(end - start)) / CLOCKS_PER_SEC;
		start = clock();
		asmOutput = asmDotProduct(n, a, b);
		end = clock();
		printf("Assembly output: %f\n", asmOutput);
		asmTime += ((double)(end - start)) / CLOCKS_PER_SEC;
		checkCorrectness(cOutput, asmOutput);
		free(a);
		free(b);
	}
	cTime /= 20;
	asmTime /= 20;

	
	printf("Average C execution time: %lf\n", cTime);
	printf("Average x86-64 assembly execution time: %lf\n", asmTime);

	return 0;
}