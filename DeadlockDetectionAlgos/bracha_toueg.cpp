#include <bits/stdc++.h>
using namespace std;

vector < pair <pair<int,int>,string> > messagess;
int ananya ;

class Node{

    public :
	int id;
	bool free = false;
	bool notified = false;
	bool initiator = false;
	int requests = 0;
	vector<int> out,in;

	void addOut(int u)
	{
		out.push_back(u);
		requests++;
	}

	void addIn(int u)
	{
		in.push_back(u);
	}

	void initiate()
	{
		initiator = true;
		notify(id);
	}

    bool allDone()
    {
    	for(int i=0;i<out.size();i++)
    	{
    		if(out[i]!=-1)
    			return false;
    	}
    	return true;
    }

    void handleMsg()
    {
    	if(messagess.size()==0)
    		return;
    	
    	cout<<"handle "<<messagess.size()<<endl;
    	pair<pair<int,int>,string> temp = messagess[0];
    	ananya++;
        messagess.erase(messagess.begin()+1);

        int sender = temp.first.first;
        int receiver = temp.first.second;
        string msg = temp.second;

        if(msg=="n")
        {
        	if(notified==true)
        	{
    			messagess.push_back(make_pair(make_pair(id,sender),"d"));
    			return;
        	}
        	if(notified==false)
        	{
        		notify(id);
        	}
        	while(allDone()==false)
        	{
        		handleMsg();
        	}
    	    messagess.push_back(make_pair(make_pair(id,sender),"d"));
        }

        if(msg=="g")
        {
        	if(requests>0)
        	{
        		requests--;
        		if(requests==0)
        		{
        			grant();
        		}
    	        messagess.push_back(make_pair(make_pair(receiver,sender),"a"));
        	}
        }

        if(msg=="d")
        {
        	for(int i=0;i<out.size();i++)
        	{
        		if(out[i]==sender)
        		{
        			out[i]=-1;
        			break;
        		}
        	}
        }

        if(msg=="a")
        {
        	for(int i=0;i<in.size();i++)
        	{
        		if(in[i]==sender)
        		{
        			in[i]=-1;
        			break;
        		}
        	}
        }

        if(msg=="t")
        {
        	exit(0);
        }

    }

    void notify(int k)
    {
    	//cout<<"notify"<<endl;
    	if(notified==false)
    	{

    		notified=true;
    		for(int i=0;i<out.size();i++)
    		{
    			if(out[i]!=-1)
    				messagess.push_back(make_pair(make_pair(id,out[i]),"n"));
    				
    		}

    	    if(requests==0)
    	    	grant();
    	}

    }

    void grant()
    {
    	free = true;
    	for(int i=0;i<in.size();i++)
    	{
    		if(in[i]!=-1)
    			messagess.push_back(make_pair(make_pair(id,in[i]),"g"));
    				
    	}
    }

    
};


int main()
{
	int numberOfNodes,initiator,n;
	cout<<"No of proc"<<endl;
    cin>>numberOfNodes;
    cout<<"Initiator"<<endl;
    cin>>initiator;
    cout<<"No of dependencies"<<endl;
    cin>>n;
    Node nodes[numberOfNodes];
    int u,v;
    
    for(int i=1;i<=n;i++) 
    {
   
    	nodes[i].id = i-1;
    	cin>>u>>v;
    	nodes[u].addOut(v);
    	nodes[v].addIn(u);

    }
    
    nodes[initiator].initiate();
   
    
    while(1)
    {
    	for(int i=0;i<numberOfNodes;i++)
    	{
    		nodes[i].handleMsg();
    		if(i==initiator && nodes[initiator].allDone())
    		{
    			if(nodes[initiator].free == true)
    			{
    				cout<<"Initiator is deadlock free"<<endl;
    			}
    			else if(nodes[initiator].requests>0)
    			{
    				cout<<"Deadlock at initiator"<<endl;
    			}

    			for(int i=0;i<numberOfNodes;i++)
    			{
    				messagess.push_back(make_pair(make_pair(initiator,i),"t"));
    			}
    			break;
    		}
    	}
    }
	
}
