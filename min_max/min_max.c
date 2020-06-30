#include<stdio.h>
#include<stdlib.h>

typedef struct min_max_pair
{
	int min;
	int max;
}min_max_pair;

min_max_pair get_min_max(int *array, int start, int end)
{
	int mid;
	min_max_pair min_max, min_max_left, min_max_right;
	if(start == end)
	{
		min_max.min = array[start];
		min_max.max = array[start];
		return min_max;
	}
	else if(start == end-1)
	{
		if(array[start] > array[end])
		{
			min_max.min = array[end];
			min_max.max = array[start];
		}
		else
		{
			min_max.min = array[start];
			min_max.max = array[end];
		}
		return min_max;
	}
	else
	{
		mid = (start + end)/2;
		min_max_left = get_min_max(array, start, mid);
		min_max_right = get_min_max(array, mid+1, end);
		if(min_max_left.min < min_max_right.min)
		{
			min_max.min = min_max_left.min;
		}
		else
		{
			min_max.min = min_max_right.min;
		}
		if(min_max_left.max > min_max_right.max)
		{
			min_max.max = min_max_left.max;
		}
		else
		{
			min_max.max = min_max_right.max;
		}
		return min_max;
	}
}

int main()
{
	int *array=NULL;
	int count=0, i=0;
	printf("\nEnter the number of elements: ");
	scanf("%d", &count);
	array=(int *)malloc(count*sizeof(int));
	for(i=0; i<count; i++)
	{
		printf("Enter element %d: ", i+1);
		scanf("%d", &array[i]);
	}
	min_max_pair min_max = get_min_max(array, 0, count-1);
	printf("Minimum element of the given array is: %d", min_max.min);
	printf("\nMaximum element of the given array is: %d\n", min_max.max);
	return 0;
}