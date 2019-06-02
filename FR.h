#include <bits/stdc++.h>
using namespace std;
class BN{
private:
    int id;
    double x;
    double y;
public:
    BN(int newID, double newX, double newY);
    int read_id(){return id;}
    double read_x(){return x;}
    double read_y(){return y;}
};
BN::BN(int newID, double newX, double newY){
    id=newID;
    x=newX;
    y=newY;
}
double dist(double x1,double y1,double x2,double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double LorR(double x1,double y1,double x2,double y2,double x3,double y3){
    return (x3-x1)/(x2-x1)-(y3-y1)/(y2-y1);
}
class packet{
protected:
    int source;
    int destination;
    int dead;
    double source_x;
    double source_y;
    double destination_x;
    double destination_y;
    double dead_x;
    double dead_y;
    double line_dis;
    int last_hop;
    int next_hop;
    int previous_intersection_point;
public:
    int read_source(){return source;}
    int read_destination(){return destination;}
    int read_dead(){return dead;}
    int read_last_hop(){return last_hop;}
    int read_next_hop(){return next_hop;}
    int read_previous_intersection_point(){return previous_intersection_point;}
    double read_source_x(){return source_x;}
    double read_source_y(){return source_y;}
    double read_destination_x(){return destination_x;}
    double read_destination_y(){return destination_y;}
    double read_dead_x(){return dead_x;}
    double read_dead_y(){return dead_y;}
    double read_line_dis(){return line_dis;}
    void change_dead(int d){dead=d;}
    void change_dead_x(double x){dead_x=x;}
    void change_dead_y(double y){dead_y=y;}
    void change_last_hop(int prehop){last_hop=prehop;}
    void change_next_hop(int newhop){next_hop=newhop;}
    void change_previous_intersection_point(int closer){previous_intersection_point=closer;}
    void change_line_dis(double dis){line_dis=dis;}
};
class GFGpacket:public packet{
    bool mode;
public:
    GFGpacket(int new_source,int new_destination,double new_s_x,double new_s_y,double new_d_x,double new_d_y);
    bool read_mode(){return mode;}
    void change_mode(bool m){mode=m;}
};
GFGpacket::GFGpacket(int new_source,int new_destination,double new_s_x,double new_s_y,double new_d_x,double new_d_y){
    source=new_source;
    destination=new_destination;
    source_x=new_s_x;
    line_dis=dist(new_s_x,new_s_y,new_d_x,new_d_x);
    source_y=new_s_y;
    destination_x=new_d_x;
    destination_y=new_d_y;
    last_hop=new_source;
    next_hop=new_source;
    previous_intersection_point=new_source;
}
class RP{
public:
    friend class node;
    virtual int getNextHop(int id,double x,double y,vector<BN> neighbor,vector<BN> neighbor_planer,queue<GFGpacket> &send_packets)=0;
};
class FR: public RP{
public:
    friend class node;
    int getNextHop(int id,double x,double y,vector<BN> neighbor,vector<BN> neighbor_planer,queue<GFGpacket> &send_packets);
};
class GFG: public FR{
public:
    friend class node;
    int getNextHop(int id,double x,double y,vector<BN> neighbor,vector<BN> neighbor_planer,queue<GFGpacket> &send_packets);
};
int FR::getNextHop(int id,double x,double y,vector<BN> neighbor,vector<BN> neighbor_planer,queue<GFGpacket> &send_packets){
    double LorR(double x1,double y1,double x2,double y2,double x3,double y3);

    int i,j,s,d,sel_next,flag=1;
    double s_x,s_y,d_x,d_y,v1_x,v1_y,v2_x,v2_y,mid_x,mid_y,inn,angle,min_angle,m1,m2;
    vector <bool> sting;
    for(i=0;i<neighbor_planer.size();i++)
    	sting.push_back(true);

    s=send_packets.front().read_dead();
    d=send_packets.front().read_destination();
    s_x=send_packets.front().read_dead_x();
    s_y=send_packets.front().read_dead_y();
    d_x=send_packets.front().read_destination_x();
    d_y=send_packets.front().read_destination_y();

    if(id==send_packets.front().read_dead()){
        v1_x=d_x-s_x;
        v1_y=d_y-s_y;
    }
    else{
        for(i=0;i<neighbor_planer.size();i++){
            if(send_packets.front().read_last_hop()==neighbor_planer[i].read_id())
                break;
        }
        v1_x=neighbor_planer[i].read_x()-x;
        v1_y=neighbor_planer[i].read_y()-y;
    }
    for(j=0;j<neighbor_planer.size();j++)
        sting.push_back(true);
    while(flag){
        min_angle=10*M_PI;
        for(j=0;j<neighbor_planer.size();j++){
            v2_x=neighbor_planer[j].read_x()-x;
            v2_y=neighbor_planer[j].read_y()-y;
            inn=v1_x*v2_x+v1_y*v2_y;
            if(send_packets.front().read_last_hop()==neighbor_planer[j].read_id())
				angle=2*M_PI;
			else{
				angle=acos(inn/(sqrt(v1_x*v1_x+v1_y*v1_y)*sqrt(v2_x*v2_x+v2_y*v2_y)));
                if((v1_x*v2_y-v1_y*v2_x)>0)
                    angle=2*M_PI-angle;
			}
			//cout << angle << ' ' << neighbor_planer[j].read_id() << endl;
            if(angle<min_angle&&sting[j]==true){
                min_angle=angle;
                sel_next=j;
            }
        }
        m1=(d_y-s_y)/(d_x-s_x);
        m2=(neighbor_planer[sel_next].read_y()-y)/(neighbor_planer[sel_next].read_x()-x);
        mid_x=(y-m2*x-(s_y-m1*s_x))/(m1-m2);
        mid_y=m1*mid_x+(s_y-m1*s_x);
        if((fabs(mid_x-s_x)<fabs(d_x-s_x)||fabs(mid_y-s_y)<fabs(d_y-s_y))&&LorR(s_x,s_y,d_x,d_y,x,y)*LorR(s_x,s_y,d_x,d_y,neighbor_planer[sel_next].read_x(),neighbor_planer[sel_next].read_y())<0&&dist(mid_x,mid_y,d_x,d_y)<send_packets.front().read_line_dis()){
            send_packets.front().change_previous_intersection_point(neighbor_planer[sel_next].read_id());
            send_packets.front().change_line_dis(dist(mid_x,mid_y,d_x,d_y));
            if(LorR(s_x,s_y,d_x,d_y,neighbor_planer[sel_next].read_x(),neighbor_planer[sel_next].read_y())<0){
                v1_x=x-neighbor_planer[sel_next].read_x();
                v1_y=y-neighbor_planer[sel_next].read_y();
                sting[sel_next]=false;
            }
            else{
                flag=0;
                break;
            }
        }
        else
            flag=0;
    }
    return neighbor_planer[sel_next].read_id();
};
int GFG::getNextHop(int id,double x,double y,vector<BN> neighbor,vector<BN> neighbor_planer,queue<GFGpacket> &send_packets){
    double dist(double x1,double y1,double x2,double y2);

    int i,j,d,sel_next;
    double d_x,d_y,d_min;

    d=send_packets.front().read_destination();
    d_x=send_packets.front().read_destination_x();
    d_y=send_packets.front().read_destination_y();

    d_min=dist(x,y,d_x,d_y);
    sel_next=-1;

    for(i=0;i<neighbor.size();i++){
        if(dist(neighbor[i].read_x(),neighbor[i].read_y(),d_x,d_y)<d_min){
            d_min=dist(neighbor[i].read_x(),neighbor[i].read_y(),d_x,d_y);
            sel_next=i;
        }
    }

    if(sel_next==-1)
        return -1;
    else
        return neighbor[sel_next].read_id();
}
class node{
private:
    RP *routingProtocol;
    int id;
    double x;
    double y;
public:
    friend class GFGpacket;
    friend class RP;
    friend class FR;
    friend class GFG;
    vector<BN> neighbor;
    vector<BN> neighbor_planer;
    queue<GFGpacket> send_packets;
    node(int newID, double newX, double newY);
    int read_id(){return id;}
    double read_x(){return x;}
    double read_y(){return y;}
    bool checkQueue();
    void send(GFGpacket P,vector <node> &R);
    void change_routingProtocol(bool x);
    int active(int id,double x,double y,vector<BN> neighbor,vector<BN> neighbor_planer,queue<GFGpacket> &send_packets){return routingProtocol->getNextHop(id,x,y,neighbor,neighbor_planer,send_packets);}
};
node::node(int newID, double newX, double newY){
    id=newID;
    x=newX;
    y=newY;
    routingProtocol= new GFG;
}
void node::change_routingProtocol(bool x){
    delete routingProtocol;
    if(x==true)
        routingProtocol= new GFG;
    else
        routingProtocol= new FR;
}
bool node::checkQueue(){
    double dist(double x1,double y1,double x2,double y2);
    int i;
    if(send_packets.empty()==false){
        if(send_packets.front().read_next_hop()==id){
            if(send_packets.front().read_mode()==false&&dist(x,y,send_packets.front().read_destination_x(),send_packets.front().read_destination_y())<dist(send_packets.front().read_dead_x(),send_packets.front().read_dead_y(),send_packets.front().read_destination_x(),send_packets.front().read_destination_y()))
                send_packets.front().change_mode(true);
            change_routingProtocol(send_packets.front().read_mode());
            i=active(id,x,y,neighbor,neighbor_planer,send_packets);

            if(i!=-1){
                send_packets.front().change_next_hop(i);
                send_packets.front().change_last_hop(id);
            }
            else{
                send_packets.front().change_mode(false);
                change_routingProtocol(send_packets.front().read_mode());
                send_packets.front().change_dead(id);
                send_packets.front().change_dead_x(x);
                send_packets.front().change_dead_y(y);
                i=active(id,x,y,neighbor,neighbor_planer,send_packets);
                send_packets.front().change_next_hop(i);
                send_packets.front().change_last_hop(id);
            }
            //cout << '*' << send_packets.front().read_next_hop() << endl;

            /*if(send_packets.front().read_next_hop()==send_packets.front().read_destination())
            	cout << send_packets.front().read_destination();
            else
            	cout << send_packets.front().read_next_hop() << ' ';*/
            return true;
        }
        else{
            send_packets.pop();
            return false;
        }
    }
    else
    	return false;
}
void node::send(GFGpacket P,vector <node> &R){
    int k;
    for(k=0;k<neighbor.size();k++){
        R[neighbor[k].read_id()].send_packets.push(P);
    }
}
