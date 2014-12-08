#include <iostream>
#include <queue>
using namespace std;
#define NIL 100
#define WHITE 0
#define GRAY 1
#define BLACK 2
struct Node
{
	int key;
	int a;
	int b;
	int former;
	int color;
};
void initial_edge(int matrix[][24], Node *state)//二维数组形参必须指明第二维（列）大小
{
	for (int i = 0; i<24; i++)
	for (int j = 0; j<24; j++)
	{
		int a1 = state[i].a;
		int b1 = state[i].b;
		int a2 = state[j].a;
		int b2 = state[j].b;
		if (((a2 == 3 || a2 == 0) && (b2 == b1 || a1 + b1 == a2 + b2)) || ((b2 == 5 || b2 == 0) && (a2 == a1 || a1 + b1 == a2 + b2)))//make a pot full or empty is ok!
			matrix[i][j] = 1;
		else
			matrix[i][j] = 0;
	}
}
void BFS(int matrix[][24], Node* state, int s)
{
	for (int i = 0; i<24; i++)
	{
		state[i].color = WHITE;
		state[i].former = NIL;
	}
	state[s].color = GRAY;
	queue<int> q1;
	q1.push(s);
	while (!q1.empty())
	{
		int u = q1.front();
		q1.pop();
		for (int i = 0; i < 24; i++)
		{
			if (matrix[u][i] == 1 && state[i].color == WHITE)
			{
				state[i].color = GRAY;
				state[i].former = u;
				q1.push(i);
			}
		}
		state[u].color = BLACK;
	}
}
void print_path(Node* state, int s, int d)
{
	if (s == d)
		cout << "(" << state[s].a << "," << state[s].b << ")";
	else if (state[d].former == NIL)
		cout << "No path";
	else
	{
		print_path(state, s, state[d].former);
		cout << "->(" << state[d].a<<","<<state[d].b << ")";
	}
	return;
}

int main()
{
	Node state[24];
	for (int i = 0; i<24; i++)
	{
		state[i].key = i;
		state[i].a = i / 6;
		state[i].b = i % 6;
		state[i].former = 100;
	}
	int matrix[24][24];
	int source, destination;
	source = 0;
	initial_edge(matrix, state);
	BFS(matrix, state, source);
	for (int i = 0; i < 24; i++)
	{
		if (state[i].a == 1 || state[i].b == 1)
		{
			print_path(state, source, i);
			cout << endl;
		}
	}
	return 0;
}