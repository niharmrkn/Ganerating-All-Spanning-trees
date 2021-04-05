#include<bits/stdc++.h>
using namespace std;

int brch[100][100];
int chrd[100][100];
int temp[100][100];
int temp1[100][100];

struct edge
{
	int src;
	int dest;
};

bool dfs(int vertex, set<int>&visited, int parent,int v,int arr[100][100])
{
   visited.insert(vertex);
   for(int i = 1; i<=v; i++)
   {
      if(arr[vertex][i])
	  {
         if(i == parent)    
            continue;
         if(visited.find(i) != visited.end())
            return true;
         if(dfs(i, visited, vertex,v,arr))
            return true;
      }
   }
   return false;
}
bool hasCycle(int v,int arr[100][100])
{
   set<int> visited;       
   for(int i = 1; i<=v; i++)
   {
      	if(visited.find(i) != visited.end()) 
        	continue;
      	if(dfs(i, visited, -1,v,arr))
	  	{
        	return true;
      	}
   }
   return false;
}


int comb[100][100]; 
int id=1;
void combinationUtil(int arr[], int data[],int start, int end,int index, int r)
{
    if (index == r)
    {
        for (int j = 0; j < r; j++)
        {
        	comb[id][j+1] = data[j];
		}
        id++;
        return;
    }
 
    for (int i = start; i <= end && end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1,end, index+1, r);
    }
}
void printCombination(int arr[], int n, int r)
{
	for(int i=1;i<=50;i++)
	{
		for(int j=1;j<=50;j++)
		{
			comb[i][j]=0;
		}
	}
	id= 1;
    int data[r];
    combinationUtil(arr, data, 1, n-1, 0, r);
}

int comb_b[100][100]; 
int id_b=1;
void combinationUtil_b(int arr[], int data[],int start, int end,int index, int r)
{
    if (index == r)
    {
        for (int j = 0; j < r; j++)
        {
        	comb_b[id_b][j+1] = data[j];
		}
        id_b++;
        return;
    }
 
    for (int i = start; i <= end && end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        combinationUtil_b(arr, data, i+1,end, index+1, r);
    }
}
void printCombination_b(int arr[], int n, int r)
{
	for(int i=1;i<=50;i++)
	{
		for(int j=1;j<=50;j++)
		{
			comb_b[i][j]=0;
		}
	}
	id_b= 1;
    int data[r];
    combinationUtil_b(arr, data, 1, n-1, 0, r);
}

initialTree(int ajm[100][100],int v)
{
	int parent[100];
	bool visited[100];
	
	for(int i=1;i<=v;i++)
	{
		visited[i]=false;	
	}
	parent[1]=-1;
	for(int i=1;i<=v-1;i++)
	{
		int u = i;
		visited[u]=true;
		
		for(int j=1;j<=v;j++)
		{
			if(ajm[u][j] && visited[j]==false)
			{
				parent[j]=u;
			}
		}
	}
	
	for(int i=1;i<=v;i++)
	{
		for(int j=1;j<=v;j++)
		{
			brch[i][j]=0;
			chrd[i][j]=0;
		}
	}
	int count = 1;
	cout<<"Spanning Tree " << count << " At distance = 1 \n";
	int k=1;
	edge br[100],ch[100];
	for (int i = 2; i <= v; i++)
	{
		printf("%d - %d\n", parent[i], i);
		
		brch[parent[i]][i]=1;
		brch[i][parent[i]]=1;
		
		br[k].src=parent[i];
		br[k].dest=i;
		k++;
	}

	
	int k1 = 1;	
	for(int i=1;i<=v;i++)
	{
		for(int j=1;j<=v;j++)
		{
			if(ajm[i][j]!=0 && brch[i][j]==0 && chrd[i][j]==0)
			{
				chrd[i][j]=1;
				chrd[j][i]=1;
				
				ch[k1].src = i;
				ch[k1].dest = j;
				k1++;	
			}	
		}	
	}
	
	int arr_c[100];
	for(int i=1;i<k1;i++)
	{
		arr_c[i] = i;
	}
	
	int arr_b[100];
	for(int i=1;i<k;i++)
	{
		arr_b[i] = i;
	}
	
	
	for(int d=1;d<k1;d++)
	{
		printCombination(arr_c, k1, d);
		//adding chords......
		for(int i=1;i<id;i++)
		{
			//copy branch matrix
			for(int l=1;l<=v;l++)
			{
				for(int m=1;m<=v;m++)
				{
					temp[l][m]	= brch[l][m];
				}	
			}

			for(int j=1;j<=d;j++)
			{
				int var = comb[i][j];
				temp[ch[var].src][ch[var].dest]=1;
				temp[ch[var].dest][ch[var].src]=1;
			}
			
			printCombination_b(arr_b, k, d);
			
			for(int l=1;l<id_b;l++)
			{
				//copy the  matrix...
				for(int l1=1;l1<=v;l1++)
				{
					for(int m1=1;m1<=v;m1++)
					{
						temp1[l1][m1]	= temp[l1][m1];
					}	
				}
				
				for(int m=1;m<=d;m++)
				{
					int var_b = comb_b[l][m];
					//remove branch
					temp1[br[var_b].src][br[var_b].dest]=0;	
					temp1[br[var_b].dest][br[var_b].src]=0;

					//call dfs for checking is there is a cycle or not
					bool cycle = hasCycle(v,temp1);
					if(!cycle)
					{
						count = count + 1;
						cout<<"Spanning Tree " << count << " At distance = "<< d <<" \n";
						for(int l2=1;l2<=v;l2++)
						{
							for(int m2=1;m2<=v;m2++)
							{
								if(temp1[l2][m2]!=0)
								{
									temp1[m2][l2]=0;
									cout << l2 <<" - " << m2 << endl;
								}
							}
						}
						
					}
					
					
				}
			}
		}
		
		

	}
	
	cout << "Total spanning tress = " << count << endl;	
		
}
int main()
{
	int ajm[100][100];
	int v,e;

	
	cout << "Enter the total number of vertices and edges : \n";
	cin >> v >> e;
	
	
	for(int i=1;i<=v;i++)
	{
		for(int j=1;j<=v;j++)
		{
			ajm[i][j]=0;
		}
	}
	
	for(int i=0;i<e;i++)
	{
		cout << "Enter the Egde " << i+1 << endl;
		cout << "Enter the source and Destination vertex : " << endl;
		int x,y;
		cin >> x >> y;
		ajm[x][y]=1;
		ajm[y][x]=1;	
	}
	
	cout << "\nAdjacency Matrix....\n";
	for(int i=1;i<=v;i++)
	{
		for(int j=1;j<=v;j++)
		{
			cout << ajm[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n";
	initialTree(ajm,v);
	
	return 0;
}
