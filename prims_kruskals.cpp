#include <iostream>
#include <stdio.h>
#include <stdlib.h>


struct node
{
	int value;
	struct node* parent;
};

struct edgenode
{
	int vertex1;
	int vertex2;
	int edgevalue;
};

//Prims variables
int* gparent;
int* gkey;
bool* gmstset;

//Kruskal's variables
node* gkruskalsnode;
edgenode* gedgenode;

int minKey(int v)
{
	int min = INT_MAX, min_index = 0;

	for (int i = 0; i < v; i++)
		if (gmstset[i] == false && gkey[i] < min)
			min = gkey[i], min_index = i;

	return min_index;
}

void printMST(int* ptr, int v)
{
	std::cout << "Edge \tWeight\n";
	for (int i = 1; i < v; i++)
		std::cout << gparent[i] << " - " << i << " \t" << ptr[i*v + gparent[i]]<< " \n";
}


void primsMST(int* ptr,int v)
 
{
	for (int i = 0; i < v; i++)
		gkey[i] = INT_MAX, gmstset[i] = false;

	gkey[0] = 0;
	gparent[0] = -1;

	for (int count = 0; count < v - 1; count++)
	{
		int u = minKey(v);

		gmstset[u] = true;

		for (int j = 0; j < v; j++)
			if (ptr[(v*u)+j] && gmstset[j] == false && ptr[(v*u) + j] < gkey[j])
				gparent[j] = u, gkey[j] = ptr[(v*u) + j];
	}

	printMST(ptr, v);
}

void sort(int n, edgenode* ptr)
{
	int i, j;
	edgenode tempedgenode;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (ptr[j].edgevalue < ptr[i].edgevalue)
			{
				tempedgenode = ptr[i];
				ptr[i] = ptr[j];
				ptr[j] = tempedgenode;
			}
		}
	}

	std::cout << "all the edge values in ascending order" << std::endl;
	for (i = 0; i < n; i++)
	{
		if (ptr[i].edgevalue != 0)
			std::cout << ptr[i].vertex1 << " " << ptr[i].vertex2 << " " << ptr[i].edgevalue << std::endl;		
	}
}

node* find(node* node)
{
	while (node->parent != node)
		node = node->parent;

	return node;
}

void unionK(node* first, node* second, int weight)
{
	if (find(first)->value > find(second)->value)
		find(first)->parent = find(second)->parent;
	else
		find(second)->parent = find(first)->parent;

	std::cout << first->value << " - " << second->value << "   " << weight << std::endl;
}

void kruskalsMST(int* ptr, int v)
{
	gkruskalsnode = (node*)malloc(v * sizeof(node));
	gedgenode = (edgenode*)malloc(v*v*sizeof(edgenode));

	for (int i = 0; i < v; i++)
		gkruskalsnode[i].value = i, gkruskalsnode[i].parent = &gkruskalsnode[i];

	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			gedgenode[i*v + j].vertex1 = i;
			gedgenode[i*v + j].vertex2 = j;
			gedgenode[i*v + j].edgevalue = ptr[i*v + j];
		}
	}

	//sort gedgenode based on value
	sort(v*v, gedgenode);

	std::cout << "Edge \tWeight\n";
	for (int i = 0; i < (v*v); i++)
	{
		if (gedgenode[i].edgevalue != 0)
			if (find(gkruskalsnode + (gedgenode[i].vertex1)) != find(gkruskalsnode + (gedgenode[i].vertex2)))
					unionK(gkruskalsnode + gedgenode[i].vertex1, gkruskalsnode + gedgenode[i].vertex2, gedgenode[i].edgevalue);
	}
}

int main()
{
	/* Graph looks like this
	    1   7
	(0)--(1)--(2)
	|    / \   | 
   3|  6/   \7 |9
	|  /     \ |
	(3)-------(4)
	      9	 */
	while (true)
	{
		int v;

		printf("Enter the number of vertices ");
		scanf_s("%d", &v);

		int* ptr = (int*)malloc((v * v) * sizeof(int));
		gparent = (int*)malloc(v * sizeof(int));
		gkey = (int*)malloc(v * sizeof(int));
		gmstset = (bool*)malloc(v * sizeof(bool));

		for (int i = 0; i < v*v; i++)
		{
			ptr[i] = 0;
		}

		char is_node_present;
		int from, to, weight;
		while (true)
		{
			std::cout << "Is there a new edge?\nPress Y to enter new node or N to stop the input for algorithm." << std::endl;
			std::cin >> is_node_present;
			if (is_node_present == 'Y')
			{
				std::cout << "from  to  weight" << std::endl;
				std::cin >> from;
				std::cin >> to;
				std::cin >> weight;
				ptr[(from * v) + to] = weight;
				ptr[(to * v) + from] = weight;
			}
			else if (is_node_present == 'N')
				break;
		}

		while (true)
		{
			std::cout << "Press P to run prim's algorithm or press K to run kruskal's algorithm." << std::endl;
			char algo;
			std::cin >> algo;

			if (algo == 'P')
			{
				primsMST(ptr, v);
				break;
			}
			else if (algo == 'K')
			{
				kruskalsMST(ptr, v);
				break;
			}
			else
			{
				std::cout << "You pressed wrong key" << std::endl;
				continue;
			}
		}

		std::cout << "\nPress q to exit or any other key to repeat the alogorithms" << std::endl;
		char wait;
		std::cin >> wait;
		if (wait == 'q')
			break;
		else
			continue;
	}

	return 0;
}
