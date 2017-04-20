/*
This is program that written by 11510426 林震屹.
This program is to open a .txt file(in this lab it is Demo.text),
generate 500000 random numbers, write this numbers into the Demo.text and
read these numbers and find the max array in these numbers by using divide and
conquer algorithms and dymanic programming separately, comparing the running time
of this two method. At last, this program will write these numbers into different files.
*/


#pragma warning( disable : 4996) 
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define N 100000 // To sort 10000 numbers

/*
	the function to find the max subarray sum
	by using divide and conquer algorithms
*/
int maxSubarraySum_DAC(int arr[], int left, int right)
{
	int k, sum = 0;
	if (left == right)
		return arr[left] >= 0 ? arr[left] : 0;
	else
	{
		int center = (left + right )/ 2;
		int left_sum = maxSubarraySum_DAC(arr, left, center); // max subarray sum presents at the left
//		printf("ok");
		int right_sum = maxSubarraySum_DAC(arr, center + 1, right); // max subarray sum presents at the left
		int sum_1 = 0;
		int new_left = 0;
/*
	the case that the max subarray sum contains the center element
*/	
		for (k = center; k >= left; --k)
		{
			new_left += arr[k];
			if (new_left > sum_1)
				sum_1 = new_left;
		}
		int sum_2 = 0;
		int new_right = 0;
		for (k = center + 1; k <= right; ++k)
		{
			new_right += arr[k];
			if (new_right > sum_2)
				sum_2 = new_right;
		}
		sum = sum_1 + sum_2;
		if (sum < left_sum)
			sum = left_sum;
		if (sum < right_sum)
			sum = right_sum;
	}
	return sum;
} // end maxSubarraySum_DAC

  /*
  the function to find the max subarray sum
  by using dymatic programming
  */
int maxSubarraySum_DP(int arr[], int n)
{
	int sum = 0, arr_b = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr_b>0)
			arr_b += arr[i];
		else
			arr_b = arr[i];
		if (arr_b>sum)
			sum = arr_b;
	}
	return sum;
} // end maxSubarraySum_DP

int main()
{
	FILE* fstream;
	int sum_DAC, sum_DP;   // initialize the sum by using the method "divide and conquer algorithms" and "dymanic programming"
	long start, end;   // clock
	int arr[N];   // the generated random array.
	int arr2[N]; // the arr2[] is the array read from the file.
    int size = sizeof(int);
	srand(time(NULL)); // Set random number seeds
	for (int i = 0; i < N; i++) // Run 100000 times
	{
		arr[i] = (rand() % N) - (rand() % N); // generate the random values range from -N to N
	}

	fstream = fopen("Demo.txt", "wb+");
	if (fstream == NULL)
	{
		printf("ERROR OPEN!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("opne file Demo.text succeed\n");
	}

	fwrite(arr, size, N, fstream); // write the random numbers into Demo.text

	rewind(fstream);
	fread(arr2, size, N, fstream);
//	printf("The numbers that be written in the Demo.txt is : \n");
//	for (int j = 0; j < N; j++)
//	{
//		printf("%d\t", arr2[j]);
//	}
	printf("\n");
	start = clock();
	sum_DAC = maxSubarraySum_DAC(arr2, 0, N-1);
	end = clock();
	printf("the max sum by using divide and conquer algorithms is : %d\n", sum_DAC);
	printf("The running time of divide and conquer algorithms is : %ld ms\n", end - start);
	start = clock();
	sum_DP = maxSubarraySum_DP(arr2, N);
	end = clock();
	printf("the max sum by using dymanic programming is : %d\n", sum_DP);
	printf("The running time of dymanic programming algorithms is : %ld ms\n", end - start);
	fclose(fstream); // close the file 
	return 0;

} // end main