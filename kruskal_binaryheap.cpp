#include <bits/stdc++.h>

using namespace std;

// void create_wu(int**root,int**size,int vertex)
// {
//      *root=new int[vertex];
//      *size=new int[vertex];

//      for(int i=0;i<vertex;i++)
//      {
//         *(*root+i)=i;
//         *(*size+i)=1;

//      }

// }

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



int main()
{

// int *root,*size;
int l,r,root_l1,root_r1;
vector<int>root(5);
vector<int>size(5);
// create_wu(root,size);
// weighted_Union(0,1,root,size);
// weighted_Union(0,2,root,size);

// weighted_Union(3,4,root,size);
// weighted_Union(3,5,root,size);
// weighted_Union(6,5,root,size);

// weighted_Union(2,6,root,size);
// cout<<find(2,root)<<" "<<find(6,root);
// cout<<find(2,root)<<endl;
// cout<<root[3]<<endl;
vector<pair<int,int>> res;
map<int,vector<pair<int,int>>> m;
//vector<vector<int>> graph{{0,5,6,7},{5,0,5,18},{6,5,0,19},{7,18,19,0}};
vector<vector<int>> graph{{0,50,0,0,10},{50,0,15,40,100},{0,15,0,3,5},{0,40,3,0,30},{10,100,5,30,0}};

priority_queue<int,vector<int>,greater<int>> pq;   //min heap


for(int i=0;i<graph[0].size();i++)
{
  for(int j=0;j<graph[0].size();j++)
  {
    if(graph[i][j]!=0)
    {   
    	if(j>i)
    	{
           // cout<<graph[i][j]<<endl;
           pq.push(graph[i][j]);
    	   m[graph[i][j]].push_back(make_pair(i,j));

    	}
    	

    }

  }

}

clock_t start,end;
float calculated_time;
start=clock();
create_wu(root,size);
// krushkal's logic starts from here.

while(!pq.empty())
{

l=m[pq.top()][0].first;
r=m[pq.top()][0].second;

root_l1=find(l,root);
root_r1=find(r,root);

// cout<<root_l1<<" "<<root_r1<<endl;
if(root_r1!=root_l1)
{  
	// cout<<l<<" "<<r<<endl;
	weighted_Union(root_l1,root_r1,root,size);
	res.push_back(make_pair(l,r));
}


m[pq.top()].erase(m[pq.top()].begin());
pq.pop();
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
}








