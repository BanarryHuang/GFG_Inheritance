#include <iostream>
#include <vector>

using namespace std;

class RP{
public:
    virtual ~RP()=0;
    virtual void getNextHop()=0;
};

RP::~RP(){}
void RP::getNextHop(){cout<<"ERROR: RP getNextHop()"<< endl;}

class FR: public RP{
public:
    ~FR(){};
    void getNextHop(){cout<<"FR getNextHop()"<< endl;}
};

class GFG: public FR{
public:
    ~GFG(){};
    void getNextHop(){cout<<"GFG getNextHop()"<< endl;}
};


class baseNode{
public:
    virtual ~baseNode()=0;
    virtual void active()=0;
};

baseNode::~baseNode(){}
void baseNode::active(){}

template <class T> 
class node: public baseNode{
    T routingProtocol;
public:
    void active(){routingProtocol.getNextHop();}
    ~node(){}
};

typedef node<FR> FRNode;
typedef node<GFG> GFGNode;

int main()
{
    vector<baseNode*> arr;
    baseNode* ptr = new FRNode;
    ptr->active();
    
    arr.push_back(ptr);
    arr[0]->active();
    
    ptr = new GFGNode;
    ptr->active();

    arr.push_back(ptr);
    arr[1]->active();
    
    return 0;
}

