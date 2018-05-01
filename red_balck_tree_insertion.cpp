#include<bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	node *l, *r, *p;
	int c;	//c=1 for red && c=0 for black
};

node *newnode(int key)
{
	node *add=new node;
	add->data=key;
	add->c=1;
	add->l=add->r=add->p=NULL;
	
	node *lc=new node;
	lc->data=-1;
	lc->c=0;
	lc->p=add;
	add->l=lc;
	
	node *rc=new node;
	rc->data=-1;
	rc->c=0;
	rc->p=add;
	add->r=rc;
	
	return add;	
}

node *rr(node *root)
{
	node *par=root->p;
	node *x=root->l;
	node *y=x->r;
	
	x->r=root;
	root->l=y;
	
	x->p=par;
	root->p=x;
	
	return x;
}

node *lr(node *root)
{
	node *par=root->p;
	node *x=root->r;
	node *y=x->l;
	
	x->l=root;
	root->r=y;
	
	x->p=par;
	root->p=x;
	
	return x;
}

node *insert(node *root, int key)
{
	if(root==NULL || root->data==-1) return newnode(key);
	
	if(root->data > key)
		{
			root->l=insert(root->l, key);
			root->l->p=root;
		}
	else
		{
			root->r=insert(root->r, key);
			root->r->p=root;
		}
		
	return root;
}

node *balance(node *root, int key)
{
	node *x=root;
	while(x->data!=key)
	{
		if(x->data < key)
			x=x->r;
		else
			x=x->l;
	}
	
	node *par=x->p;
	if(par==NULL) return root;
	node *g=par->p;
	if(g==NULL) return root; 	
	node *u=((g->r==par)?g->l:g->r); 
	
	if(par->c==0) return root;
	
	else
	{
		if(u->c==1)
		{
			g->c=1-g->c;
			par->c=1-par->c;
			u->c=1-u->c;
			//cout<<"color changed\n";
			root=balance(root, g->data);
		}
		else
		{
			if(g->data>par->data  &&  par->data>key) 
			{
				g->c=1-g->c;
				par->c=1-par->c;
				
				node *pg=new node;
				pg=g->p;
				if(pg!=NULL) 
				{
					if(pg->r==g) pg->r=rr(g);
					else pg->l=rr(g);
				}
				else
				{
					root=rr(g);
				}
				
				//cout<<"rot r performed"<<endl;
			}
			if(g->data<par->data  &&  par->data<key)
			{
				g->c=1-g->c;
				par->c=1-par->c;
				
				node *pg=new node;
				pg=g->p;
				if(pg!=NULL) 
				{
					if(pg->r==g) pg->r=lr(g);
					else pg->l=lr(g);
				}
				else
				{
					root=lr(g);
				}
				
				//cout<<"rotn l performed "<<endl;
			}
			if(g->data>par->data  &&  par->data<key)
			{
				g->c=1-g->c;
				x->c=1-x->c;
				
				node *pg=new node;
				pg=g->p;
				if(pg!=NULL)
				{
					g->l=lr(par);
					if(pg->r==g) pg->r=rr(g);
					else pg->l=rr(g);
				}
				else
				{
					g->l=lr(par);
					root=rr(g);
				}
				
				//cout<<"l-r rotn performed "<<endl;
			}
			if(g->data<par->data  &&  par->data>key)
			{
				g->c=1-g->c;
				x->c=1-x->c;
				
				node *pg=new node;
				pg=g->p;
				if(pg!=NULL)
				{
					g->r=rr(par);
					if(pg->r==g) pg->r=lr(g);
					else pg->l=lr(g);
				}
				else
				{
					g->r=rr(par);
					root=lr(g);
				}
				
				//cout<<"r-l rotn performed "<<endl;
			}
		}
	}
	return root;
}
				
void preorder(node *root)
{
	if(root!=NULL)
	{
		if(root->data!=-1) cout<<root->data<<"("<<(root->c==1?"r":"b")<<")"<<" ";
		preorder(root->l);
		preorder(root->r);
	}
}

int main()
{
	node *root=NULL;
	cout<<"1.Insert 	2.Preorder"<<endl;
	int x;
	while(1)
	{
		cin>>x;
		if(x==1)
		{
			int t;
			cout<<"Enter value ";  cin>>t;
			root=insert(root, t); 
			root=balance(root, t);
			root->c=0; 
		}
		if(x==2) preorder(root);
	}
	
	return 0;
}
