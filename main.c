// Jay Michael Carlos and Janica Megan Reyes - LBYARCH S14
#include <stdio.h>
#include <stdlib.h>

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
	float sdot;
	sdot = 0.0;

	return sdot;
}

/*
 * Perform a dot product between two vectors a and b.
 */
int main()
{
	float *a = NULL;
	float *b = NULL;
	printf("%f\n", cDotProduct(1, a, b));
	return 0;
}