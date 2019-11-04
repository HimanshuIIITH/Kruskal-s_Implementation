#include <bits/stdc++.h>

using namespace std;


#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

struct veb
{
   int u;
   int max;
   int min;
   veb*summery;
   vector<veb*> cluster;

};

int heigh (int x,int size)
{
  int u=ceil(sqrt(size));
  return x/u;
}

int low(int x,int size)
{
     int u=ceil(sqrt(size));
     return x%u;

}
int maximum(veb*v)
{
  return v->max;
}

int minimum(veb*v)
{
  return v->min;
}


void insert(veb*v,int key)
{

  if(v->min==-1)
  {
       v->min=key;
       v->max=key;

  }
  else
  {

         if(key<v->min)
         {

          int temp;
          temp=v->min;
          v->min=key;
          key=temp;

         }
         if(v->u>2)
         {
              if(v->cluster[heigh(key,v->u)]->min==-1)
              {
                  insert(v->summery,heigh(key,v->u));
                  v->cluster[heigh(key,v->u)]->min=low(key,v->u);
                  v->cluster[heigh(key,v->u)]->max=low(key,v->u);

              }
              else
              {

                 insert(v->cluster[heigh(key,v->u)],low(key,v->u));
              }


         }

         if (key > v->max) 
         { 
            v->max= key; 
         } 




  }



}

veb*initialize(int size)
{

     veb*temp;
     temp= new veb ;
     temp->u=size;
     temp->min=-1;
     temp->max=-1;
     // temp.summery=NULL;
    int  size_child=ceil(sqrt(size));

     if(size<=2)
     {
       temp->summery=nullptr;
       temp->cluster=vector<veb*>(0, nullptr);;

     }
     else
     {
       temp->summery=initialize(size_child);
       for(int i=0;i<size_child;i++)
       {

        temp->cluster.push_back(initialize(size_child));
       }

     }
     return temp;

}

int get_index(int u,int i,int j)
{
    int temp=ceil(sqrt(u));
    int index=i*temp+j;
    return index;

}

void veb_delete(veb*v,int key)
{
   if(v->max==v->min)
   {
    v->max=-1;
    v->min=-1;
   }
   else if(v->u==2)
   {
      if(key==0)
      {
        v->min=1;
      }
      else
      {
       v->min=1;
      }
      // v->min=v->max;
      v->max=v->min;

   }
   else
   {
        
        if(key==v->min)
        {
           int first_cluster=minimum(v->summery);
           int new_min=get_index(v->u,first_cluster,v->cluster[first_cluster]->min);
           v->min=new_min;
           key=new_min;

        }
        veb_delete(v->cluster[heigh(key,v->u)],low(key,v->u));
        if(v->cluster[heigh(key,v->u)]->min==-1)
        {

           veb_delete(v->summery,heigh(key,v->u));
           if(key==v->max)
           {
              int max_cluster=v->summery->max;

              if(max_cluster==-1)
              {
                  v->max=v->min;
                  
              }
              else
              {

                v->max=get_index(v->u,max_cluster,v->cluster[max_cluster]->max);
              }


           }


        }
        else if(v->max==key)
        {
             v->max=get_index(v->u,heigh(key,v->u),v->cluster[heigh(key,v->u)]->max);
        }

   }


}



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
    veb*v;
    vector<int>root(5);
    vector<int>size(5);

    vector<pair<int,int>> res;
    map<int,vector<pair<int,int>>> m;
    vector<vector<int>> graph{{0,50,0,0,10},{50,0,15,40,100},{0,15,0,3,5},{0,40,3,0,30},{10,100,5,30,0}};
    clock_t start,end;
    start=clock();
    float calculated_time;
    v=initialize(128);
    // priority_queue<int,vector<int>,greater<int>> pq;   //min heap


    for(int i=0;i<graph[0].size();i++)
    {
      for(int j=0;j<graph[0].size();j++)
      {
        if(graph[i][j]!=0)
        {   
        	if(j>i)
        	{
               // cout<<graph[i][j]<<endl;
               // pq.push(graph[i][j]);
               insert(v,graph[i][j]);
        	   m[graph[i][j]].push_back(make_pair(i,j));

        	}
        	

        }

      }

    }
    create_wu(root,size);
    // krushkal's logic starts from here.
    // while(!pq.empty())
    while(v->min!=-1)
    {

        // l=m[pq.top()][0].first;
        // r=m[pq.top()][0].second;

         l=m[v->min][0].first;
        r=m[v->min][0].second;

        root_l1=find(l,root);
        root_r1=find(r,root);

        // cout<<root_l1<<" "<<root_r1<<endl;
        if(root_r1!=root_l1)
        {  
        	// cout<<l<<" "<<r<<endl;
        	weighted_Union(root_l1,root_r1,root,size);
        	res.push_back(make_pair(l,r));
        }


        // m[pq.top()].erase(m[pq.top()].begin());
        // pq.pop();

         m[v->min].erase(m[v->min].begin());
         int min_ele=v->min;
        veb_delete(v,min_ele);

    }

    // end=clock();
    end=clock();
    calculated_time=(float)(end-start)/CLOCKS_PER_SEC;
    calculated_time=calculated_time*1000000;


    cout<<"TIME TAKEN USING MIN HEAP :"<<calculated_time<<" microseconds\n";
    // printing minimum spanning tree.

    cout<<"SPANIING TREE EDGES\n";


    // printing minimum spanning tree.

    for(int i=0;i<res.size();i++)
    {
    	cout<<res[i].first<<" "<<res[i].second<<endl;
    }

    return 0;
}








