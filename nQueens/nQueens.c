#include<stdio.h>
#include<stdlib.h>

void print_solution(int dimension, int *queen_location)
{
	printf("\n\nSolution:");
	int i=0,j=0;
	printf("\n");
	for(i=0; i<dimension; i++)
	{
		printf("\n+");
		for(j=0;j<dimension;j++)
			printf("---+");
		printf("\n|");
		for(j=0; j<dimension; j++)
		{
			if(queen_location[i]==j)
				printf(" q |");
			else
				printf("   |");
		}
	}
	printf("\n+");
	for(j=0;j<dimension;j++)
		printf("---+");
}

int check_location(int dimension, int row, int col, int *queen_location, int *diagonal_1, int *diagonal_2)
{
	int i=0;
	for(i=0; i<dimension; i++)
	{
		if(queen_location[i]==col)
		{
			return 0;
		}
		if(diagonal_1[row+col]==1)
		{
			return 0;
		}
		if(diagonal_2[row-col+dimension-1]==1)
		{
			return 0;
		}
	}
	return 1;
}

int recursive_solve_queens(int dimension, int row, int *queen_location, int *diagonal_1, int *diagonal_2, float *solution_count)
{
	int i=0;
	if(row==dimension)
	{
		print_solution(dimension, queen_location);
		(*solution_count)++;
		printf("\nSolution %f generated",(*solution_count));
	}
	else
	{
		for(i=0; i<dimension; i++)
		{
			if(check_location(dimension, row, i, queen_location, diagonal_1, diagonal_2)==1)
			{
				queen_location[row]=i;
				diagonal_1[row+i]=1;
				diagonal_2[row-i+dimension-1]=1;
				if(recursive_solve_queens(dimension, row+1, queen_location, diagonal_1, diagonal_2, solution_count)==1)
					return 1;
				else
				{
					queen_location[row]=-1;
					diagonal_1[row+i]=0;
					diagonal_2[row-i+dimension-1]=0;
				}
			}
		}
	}	
}

int solve_queens(int dimension, int *queen_location)
{
	int i=0, *diagonal_1=NULL, *diagonal_2=NULL;
	float *solution_count=NULL;
	solution_count=(float *)malloc(sizeof(float));
	(*solution_count)=0;
	diagonal_1=(int *)malloc(2*dimension*sizeof(int)-1);
	diagonal_2=(int *)malloc(2*dimension*sizeof(int)-1);
	for(i=0; i<dimension; i++)
	{
		queen_location[i]=-1;
		diagonal_1[i]=0;
		diagonal_2[i]=0;
	}
	recursive_solve_queens(dimension, 0, queen_location, diagonal_1, diagonal_2, solution_count);
	return *solution_count;
}

int main()
{
	int dimension, *queen_location=NULL;
	float solution_count=0;
	printf("Enter dimensions of chessboard: ");
	scanf("%d", &dimension);
	queen_location = (int *)malloc(dimension*sizeof(int));
	solution_count=solve_queens(dimension, queen_location);
	printf("\n\nThe %d Queens problem has %f solutions\n",dimension,solution_count);
	//free(queen_location);
	return 0;
}