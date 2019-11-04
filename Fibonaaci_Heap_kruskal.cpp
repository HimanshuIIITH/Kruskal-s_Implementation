#include<bits/stdc++.h>
using namespace std;

int total_node=0;
int minimum=0;

void create_wu(vector<int>&root,vector<int>&size)
{
    

     for(int i=0;i<root.size();i++)
     {
        root[i]=i;
        size[i]=1;

     }

}


int find(int key,vector<int>&root)
{

while(key!=root[key])
{
key=root[key];
}

return key;
}


void weighted_Union( int l , int r , vector<int>&root , vector<int>&size )
{
int root_l,root_r;
root_l=find(l,root);
root_r=find(r,root);
 if(size[root_l]>size[root_r])
 {
     
     root[root_r]=root_l;
     size[root_l]=size[root_l]+size[root_r];
 }
 else 
 {   
 	// cout<<"here"<<endl;
     root[root_l]=root_r;
     size[root_r]=size[root_r]+size[root_l];
     // cout<<root_l<<" "<<size[root_l]<<endl;
 }



}
class Node
{
	public:
		int key;
		Node* left;
		Node* right;
		Node* parent;
		Node* child;
		int mark;
		int degree;


		Node()
		{
			
			left=NULL;
			right=NULL;
			parent=NULL;
			child=NULL;
			mark=0;
			degree=0;
		}
		Node(int y)
		{
			key=y;
			left=NULL;
			right=NULL;
			parent=NULL;
			child=NULL;
			mark=0;
			degree=0;
		}
};

Node *mini=NULL;
void insert(int val)
{
	//cout<<"enter inseert"<<endl;
	total_node++;
	Node* new_n=new Node(val);
	new_n->key=val;
	new_n->left=new_n;
	new_n->right=new_n;
	if(mini==NULL)
	{
		
		mini=new_n;
		
		return;
	}

		
	(mini->left)->right=new_n;
	new_n->left=mini->left;
	new_n->right=mini;
	mini->left=new_n;
	if(new_n->key<mini->key)
	{
		mini=new_n;

	}

}

void display()
{
	if(mini==NULL)
	{
		cout<<"empty"<<endl;
		return;
	}

	Node* p=mini->right;
	cout<<"roots are"<<endl;
	cout<<mini->key<<" ";
	while(p!=mini && p->right!=NULL)
	{
		//cout<<"enter "
		cout<<p->key<<" ";
		p=p->right;

	}

}
void swap_n(Node* trav,Node* p)
{
	//cout<<"inside swap"<<endl;
	Node* temp=NULL;
	temp=trav;
	trav=p;
	p=temp;
}

void make_parent(Node* childn,Node* parentn)
{
	// if(childn==parentn)
	// {
	// 	return;
	// }
//	cout<<"inside make_parent"<<endl;
//	cout<<"make parent "<<parentn->key<<endl;
//	cout<<"make child "<<childn->key<<endl;
	//delete child from rootlist
	(childn->left)->right=childn->right;
	(childn->right)->left=childn->left;

	if(parentn->right==parentn)
	{
		//cout<<"here\n";
		mini=parentn;

	}
	childn->left=childn;
	childn->right=childn;
	childn->parent=parentn;
	if(parentn->child==NULL)
	{
		parentn->child=childn;
	}
	childn->right=parentn->child;
	childn->left=(parentn->child)->left;
	((parentn->child)->left)->right=childn;
	(parentn->child)->left=childn;
	if(childn->key<(parentn->child)->key)
	{
		parentn->child=childn;
	}
	parentn->degree++;
	//cout<<"going out of parent "<<endl;

}
void merge_degree()
{
	int max_d=(log(total_node)/log(2));
	Node* deg[max_d+1]={NULL};

	Node *trav=mini;
	int deg_i;
	//cout<<" "<<trav->key<<endl;
	do
	{
		//cout<<"inside do 1"<<endl;
		deg_i=trav->degree;
		while(deg_i<=max_d && deg[deg_i]!=NULL && trav!=mini)
		{
			//cout<<"inside while "<<endl;
			Node *p=deg[deg_i];
			//cout<<"deg_i is "<<deg_i<<endl;
			//cout<<"key deg_i is "<<deg[deg_i]->key<<endl;
			//cout<<"before swap p is "<<p->key<<endl;
			//make mini one trav
			if(trav->key>p->key)
			{
				Node* ptr3=trav;
				trav=p;
				p=ptr3;
				//swap_n(p,trav);
			}

			if(p==mini)
			{
				mini=trav;
			}
			//cout<<"p is "<<p->key<<endl;
			//cout<<"trav is "<<trav->key<<endl;
			//cout<<"mini is "<<mini->key<<endl;
			//cout<<"trav is mini "<<trav->key<<endl;
			//cout<<"p is mini "<<p->key<<endl;
			if(p==trav)
			{
				break;
			}
			make_parent(p,trav);
			if(trav->right==trav)
			{
				mini=trav;
			}

			deg[deg_i]=NULL;
			deg_i++;

		}
		deg[deg_i]=trav;
		//cout<<"deg_i "<<deg_i<<" "<<deg[deg_i]->key<<"\n";
		trav=trav->right;
	}while(trav!=mini);

	mini=NULL;
	for(int i=0;i<=max_d;i++)
	{
		if(deg[i]!=NULL)
		{
			deg[i]->left=deg[i];
			deg[i]->right=deg[i];
			if(mini!=NULL)
			{
				(mini->left)->right=deg[i];
				deg[i]->right=mini;
				deg[i]->left=mini->left;
				mini->left=deg[i];
				if(deg[i]->key<mini->key)
				{
					mini=deg[i];
				}
			}

			else
			{
				mini=deg[i];
			}
			if(mini==NULL)
				mini=deg[i];
			else if(deg[i]->key<mini->key)
				{
					mini=deg[i];
				}
		}
	}
	// for(int i=0;i<=max_d;i++)
	// {
	// 	if(deg[i]==NULL)
	// 	{
	// 		cout<<"hi "<<endl;
	// 	}
	// }

	//cout<<max_d<<" d \n";

}
void extract_min()
{
	if(mini==NULL)
	{
		cout<<"empty "<<endl;
		return;
	}
	Node* temp=mini;
	Node* x=NULL;
	Node* xr=temp;
	minimum=temp->key;

	//bringing the heap of mini above
	if(temp->child!=NULL)
	{
		x=temp->child;
		
		do
		{
			xr=x->right;
			x->left=mini->left;
			x->right=mini;
			(mini->left)->right=x;
			mini->left=x;
			
			if(x->key<mini->key)
			{
				mini=x;
			}
			x->parent=NULL;
			x=xr;
		}while(xr!=temp->child);


	}

	(temp->left)->right=temp->right;
	(temp->right)->left=temp->left;
	mini=temp->right;
	// cout<<"**********"<<endl;
	// 	display();
	// 	cout<<"\n*********"<<endl;
		if(temp->right==temp && temp->child==NULL)
	{
		mini=NULL;
		//return;
	}


	else
	{
		mini=temp->right;
		merge_degree();

		}

		total_node--;

		// mini=temp->right;
		
		// merge_degree();






}
int main()
{

	int l,r,root_l1,root_r1;
	vector<int>root(6);
	vector<int>size(6);
	vector<pair<int,int>> res;
map<int,vector<pair<int,int>>> m;
    clock_t start,end;
vector<vector<int>> graph{{0,15,14,13,12,11},{15,0,10,9,8,7},{14,10,0,6,5,4},{13,9,6,0,3,2},{12,8,5,3,0,1},{11,7,4,2,1,0}};
vector<int>edges;
for(int i=0;i<graph[0].size();i++)
{
  for(int j=0;j<graph[0].size();j++)
  {
    if(graph[i][j]!=0)
    {   
    	if(j>i)
    	{
    		//cout<<"gra "<<graph[i][j]<<endl;
    		edges.push_back(graph[i][j]);
    		//insert(graph[i][j]);
           // cout<<graph[i][j]<<endl;
          // pq.push(graph[i][j]);
    	   m[graph[i][j]].push_back(make_pair(i,j));

    	}
    	

    }

  }

}
//clock_t start,end;


for(int i=0;i<edges.size();i++)
	{
		insert(edges[i]);
		//cout<<"mini "<<mini<<endl;
	}
	
start=clock();
//display();

float calculated_time;

create_wu(root,size);

for(int i=0;i<edges.size();i++)
{
		minimum=-1;
	 	extract_min();
	 	int min_n=minimum;
	 	//cout<<"min edges "<<min_n<<endl;
	 	l=m[min_n][0].first;
		r=m[min_n][0].second;

		root_l1=find(l,root);
		root_r1=find(r,root);

		if(root_r1!=root_l1)
		{  
			// cout<<l<<" "<<r<<endl;
			weighted_Union(root_l1,root_r1,root,size);
			res.push_back(make_pair(l,r));
		}

		m[min_n].erase(m[min_n].begin());
}
	
	end=clock();
calculated_time=(float)(end-start)/CLOCKS_PER_SEC;
calculated_time=calculated_time*1000000;


		cout<<"TIME TAKEN USING MIN HEAP :"<<calculated_time<<" microseconds\n";
		// printing minimum spanning tree.

		cout<<"SPANIING TREE EDGES\n";
		for(int i=0;i<res.size();i++)
		{


			cout<<res[i].first<<" "<<res[i].second<<endl;
		}


		return 0;

	//pq.pop();




	 	//cout<<"min is "<<minimum<<endl;
}








	// vector<int> a{50,40,12,32,11,5,6,90,12,2,1,8,7,128,80};
	// //cout<<"mini "<<mini<<endl;
	// for(int i=0;i<a.size();i++)
	// {
	// 	insert(a[i]);
	// 	//cout<<"mini "<<mini<<endl;
	// }
	
	// //display();
	// //cout<<endl;
	// vector<int>mink;
	// for(int i=0;i<a.size();i++)
	// {
	// 	//cout<<"/////////////////\n";
	// 	minimum=-1;
	// 	extract_min();
	// 	//display();
	// 	//cout<<endl;
	// 	mink.push_back(minimum);
	// 	//cout<<"min is "<<minimum<<endl;
	// }
	// cout<<"------------------------------\n";
	// for(int i=0;i<mink.size();i++)
	// {
	// 	cout<<mink[i]<<endl;
	// }
	// display();
	// // cout<<endl;
	// cout<<"total "<<total_node<<endl;

	// extract_min();
	// display();
	// cout<<"min is "<<minimum<<endl;
	// cout<<endl;
	// cout<<"total "<<total_node<<endl;
	// cout<<"------------------"<<endl;
	// extract_min();
	// display();
	// cout<<"min is "<<minimum<<endl;
	// // cout<<endl;
	// cout<<"total "<<total_node<<endl;
	// //
	