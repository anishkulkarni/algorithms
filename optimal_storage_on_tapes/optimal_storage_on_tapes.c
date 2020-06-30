#include<stdio.h>
#include<stdlib.h>

typedef struct program
{
	int number;
	int size;
	int tape;
}program;

typedef struct tape
{
	int size;
	int avl_cap;
}tape;

void heapify(program *array, int root, int size) 
{
	int largest = root;
	int l = 2*root + 1;
	int r = 2*root + 2;
	program temp;
	if(l<size && array[l].size > array[largest].size)
		largest = l;
	if(r<size && array[r].size > array[largest].size)
		largest = r;
	if (largest != root) 
	{
		temp=array[root];
		array[root]=array[largest];
		array[largest]=temp;
		heapify(array, largest, size); 
	} 
} 

void heap_sort(program *array, int size) 
{
	int i=0;
	program temp;
	for(i=size/2-1; i>=0; i--) 
		heapify(array, i, size);
	for(int i=size-1; i>=0; i--) 
	{
		temp=array[0];
		array[0]=array[i];
		array[i]=temp;
		heapify(array, 0, i);
	}
}

void arrange_horizontally(program *programs, int program_count, tape *tapes, int tape_count)
{
	int i=0, j=0, count=0;
	double rt=0;
	int cur_tape = 0;
	for(i=0; i<program_count; i++)
	{
		if(tapes[cur_tape].avl_cap >= programs[i].size)
		{
			programs[i].tape = cur_tape;
			tapes[cur_tape].avl_cap -= programs[i].size;
		}
		else
		{
			cur_tape++;
			if(cur_tape == tape_count)
				break;
			if(tapes[cur_tape].avl_cap >= programs[i].size)
			{
				programs[i].tape = cur_tape;
				tapes[cur_tape].avl_cap -= programs[i].size;
			}
		}
	}
	printf("\nHorizontal Arrangement:");
	for(i=0; i<tape_count; i++)
	{
		count = 0;
		rt = 0;
		printf("\nPrograms on tape: %d size: %d", i+1, tapes[i].size);
		for(j=0; j<program_count; j++)
		{
			if(programs[j].tape == i)
			{
				printf("\nProgram: %d size: %d", programs[j].number, programs[j].size);
				rt = 2*rt + programs[j].size;
				count++;
			}
		}
		printf("\nMean response time = %f", rt);
	}
	printf("\n");
	for(i=0; i<program_count; i++)
	{
		if(programs[i].tape == -1)
			printf("Cannot store program: %d size: %d\n", programs[i].number, programs[i].size);
	}
}

void arrange_vertically(program *programs, int program_count, tape *tapes, int tape_count)
{
	int i=0, j=0, count=0, cur_tape = 0, temp=0;
	double rt=0;
	for(i=0; i<program_count; i++)
	{
		if(tapes[cur_tape].avl_cap >= programs[i].size)
		{
			programs[i].tape = cur_tape;
			tapes[cur_tape].avl_cap -= programs[i].size;
			cur_tape = (cur_tape + 1)%tape_count;
		}
		else
		{
			temp = cur_tape;
			do
			{
				temp = (temp + 1)%tape_count;
				if(tapes[temp].avl_cap >= programs[i].size)
				{
					programs[i].tape = temp;
					tapes[temp].avl_cap -= programs[i].size;
					break;
				}
			} while (temp!=cur_tape);
			
		}
		
	}
	printf("\nVertical Arrangement:");
	for(i=0; i<tape_count; i++)
	{
		count = 0;
		rt = 0;
		printf("\nPrograms on tape: %d size: %d", i+1, tapes[i].size);
		for(j=0; j<program_count; j++)
		{
			if(programs[j].tape == i)
			{
				printf("\nProgram: %d size: %d", programs[j].number, programs[j].size);
				rt = 2*rt + programs[j].size;
				count++;
			}
		}
		printf("\nMean response time = %f", rt);
	}
	printf("\n");
	for(i=0; i<program_count; i++)
	{
		if(programs[i].tape == -1)
			printf("Cannot store program: %d size: %d\n", programs[i].number, programs[i].size);
	}
}

int main()
{
	program *programs = NULL;
	tape *tapes = NULL;
	int program_count=0, i=0, tape_count;
	printf("Enter the number of tapes: ");
	scanf("%d", &tape_count);
	tapes = (tape *)malloc(tape_count * sizeof(tape));
	for(i=0; i < tape_count; i++)
	{
		printf("Enter the length of tape %d: ", i+1);
		scanf("%d", &tapes[i].size);
		tapes[i].avl_cap = tapes[i].size;
	}
	printf("Enter the number of programs: ");
	scanf("%d", &program_count);
	programs = (program *)malloc(program_count * sizeof(program));
	for(i=0; i < program_count; i++)
	{
		printf("Enter the length of program %d: ", i+1);
		scanf("%d", &programs[i].size);
		programs[i].number = i+1;
		programs[i].tape = -1;
	}
	heap_sort(programs, program_count);
	arrange_horizontally(programs, program_count, tapes, tape_count);
	arrange_vertically(programs, program_count, tapes, tape_count);
	printf("\n");
	return 0;
}