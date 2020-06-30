#include<iostream>
#include<vector>
#include<stack>
#include<cstdio>

#define INT_MAX 99999

using namespace std;

void print_matrix(vector<vector<int> > matrix, int dimensions)
{
	int i=0, j=0;
	for(i=0; i<dimensions; i++)
	{
		for(j=0; j<dimensions; j++)
		{
			cout<<"\t"<<matrix[i][j];
		}
		cout<<"\n";
	}
}

vector<vector<int> > input_edge_matrix(vector<vector<int> > matrix, int dimension)
{
	int source, destination, weight;
	char more_edges='y';
	cout<<"Enter the edges of the graph:\n";
	cout<<"More Edges? (y/n): ";
	while(getchar()!='\n');
	cin>>more_edges;
	while(more_edges == 'y')
	{
		cout<<"Source: ";
		cin>>source;
		cout<<"Destination: ";
		cin>>destination;
		cout<<"Weight: ";
		cin>>weight;
		source--;
		destination--;
		matrix[source][destination] = weight;
		cout<<"More Edges? (y/n): ";
		while(getchar()!='\n');
		cin>>more_edges;
	}
	return matrix;
}

int mask_value(vector<int> mask, int count)
{
	int value=0, i=0;
	for(i=0; i<count; i++)
	{
		if(mask[count-i-1]==1)
			value+=1<<i;
	}
	return value;
}

int solve_TSP(vector<vector<int> > edge_matrix, vector<vector<int> > *dp_memory, vector<vector<int> > *dp_parent, int vertices, int *parent, vector<int> mask, int position, int source)
{
	vector<int> visited_all(vertices, 1);
	int ans=INT_MAX, new_ans=0, node=0, i=0, ans_node=0;
	cout<<"\nCurrent Mask is: ";
	for(i=0; i<vertices; i++)
		cout<<"\t"<<mask[i];
	if((*dp_memory)[mask_value(mask, vertices)][position]!=-1)
	{
		cout<<"\nMemorized value for mask found for source "<<position+1<<" value "<<(*dp_memory)[mask_value(mask, vertices)][position];
		return (*dp_memory)[mask_value(mask, vertices)][position];
	}
	if(visited_all==mask)
	{
		cout<<"\nReached base of recursion for "<<position+1;
		//parent[source]=0;
		cout<<" Returning value: "<<edge_matrix[position][source];
		(*dp_memory)[mask_value(mask, vertices)][position] = edge_matrix[position][source];
		return edge_matrix[position][source];
	}
	cout<<"\nSolving recursion";
	for(node=0; node<vertices; node++)
	{
		cout<<"\nChecking node: "<<node+1;
		if(mask[vertices-node-1]==0)
		{
			mask[vertices-node-1]=1;
			cout<<"\nNode considered "<< node+1;
			new_ans = edge_matrix[position][node] + solve_TSP(edge_matrix, dp_memory, dp_parent, vertices, parent, mask, node, source);
			cout<<"\nans for node "<<node+1<<" is "<<new_ans;
			if(new_ans<ans)
			{
				ans = new_ans;
				ans_node=node;
				//parent[position] = node;
			}
			mask[vertices-node-1]=0;
		}
	}
	(*dp_parent)[mask_value(mask, vertices)][position]=ans_node;
	(*dp_memory)[mask_value(mask, vertices)][position] = ans;
	cout<<"\nFinal selected answer at node "<< position+1 << " is"<<ans;
	//parent[position]=ans_node;
	return ans;
}

int main()
{
	int vertices=5, i=0, j=0, source=0, final_value=0;
	vector<int> path;
	cout<<"Enter the number of vertices in the graph: ";
	cin>>vertices;
	stack<int> s;
	int *parent = new int[vertices];
	for(i=0; i<vertices; i++)
		parent[i]=-1;
	vector<vector <int> > edge_matrix(vertices);
	for(i=0; i<vertices; i++)
		edge_matrix[i] = vector<int>(vertices, INT_MAX);
	edge_matrix = input_edge_matrix(edge_matrix, vertices);
	vector<vector<int> > dp_memory(1<<vertices);
	vector<vector<int> > dp_parent(1<<vertices);
	for(i=0; i<(1<<vertices); i++)
		dp_memory[i] = vector<int>(vertices, -1);
	for(i=0; i<(1<<vertices); i++)
		dp_parent[i] = vector<int>(vertices, -1);
	cout<<"Enter the source vertex: ";
	cin>>source;
	source--;
	vector<int> mask(vertices, 0);
	mask[vertices-source-1]=1;
	//cout<<vertices-source-1;
	//cout<<"\nCurrent Mask is: ";
	//for(i=0; i<vertices; i++)
		//cout<<"\t"<<mask[i];
	j = solve_TSP(edge_matrix, &dp_memory, &dp_parent, vertices, parent, mask, source, source);
	if(j!=INT_MAX)
	{
		cout<<"\nThe shortest hamiltonian cycle cost is: "<<j;
		//print_matrix(edge_matrix, vertices);
		i=0;
		j=source;
		final_value=1<<source;
		path.push_back(source+1);
		while(i<vertices-1)
		{
			j = dp_parent[final_value][j];
			if(j==-1)
			{
				cout<<"\nThe given graph does not have a hamiltonian cycle";
				break;
			}
			path.push_back(j+1);
			//cout<<"\t"<<j+1;
			final_value+=1<<j;
			i++;
		}
		path.push_back(source+1);
		if(i==vertices-1)
		{
			cout<<"\nPath: ";
			for(j=0; j<=vertices; j++)
				cout<<"\t"<<path[j];
		}
	}
	else
	{
		cout<<"\nThe given graph does not have a hamiltonian cycle";
	}
	/*cout<<"\nParent\n\t ";
	for(i=0; i<vertices; i++)
	{
		cout<<"\t"<<i;
	}
	cout<<"\n";
	for(i=0;i<(1<<vertices); i++)
	{
		cout<<"\t"<<i;
		for(j=0; j<vertices; j++)
		{
			cout<<"\t"<<dp_parent[i][j];
		}
		cout<<"\n";
	}
	cout<<"\nMemory\n\t ";
	for(i=0; i<vertices; i++)
	{
		cout<<"\t"<<i;
	}
	cout<<"\n";
	for(i=0;i<(1<<vertices); i++)
	{
		cout<<"\t"<<i;
		for(j=0; j<vertices; j++)
		{
			cout<<"\t"<<dp_memory[i][j];
		}
		cout<<"\n";
	}*/
	cout<<"\n";
	return 0;
}