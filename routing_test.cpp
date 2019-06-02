#include "FR.h"
int main(){
    ifstream inStream;
    ofstream outStream;
    inStream.open("request.txt");
    outStream.open("result.txt");
    int i,j,k,id,flag,tempj_id,tempk_id,routers,packets;
    double x,y,middle_x,middle_y,dist_ij;
    vector <node> router;
    cin >> routers;
    for(i=0;i<routers;i++){
        cin >> id >> x >> y;
        router.push_back(node(id,x,y));
        for(j=0;j<router.size()-1;j++){
        	dist_ij=dist(router[i].read_x(),router[i].read_y(),router[j].read_x(),router[j].read_y());
            if(dist_ij<=1||fabs(dist_ij-1)<=0.000001){
                router[i].neighbor.push_back(BN(router[j].read_id(),router[j].read_x(),router[j].read_y()));
                router[j].neighbor.push_back(BN(router[i].read_id(),router[i].read_x(),router[i].read_y()));
            }
        }
    }
    for(i=0;i<router.size();i++){
        for(j=0;j<router[i].neighbor.size();j++){
            flag=1;
            tempj_id=router[i].neighbor[j].read_id();
            middle_x=(router[i].read_x()+router[tempj_id].read_x())/2;
            middle_y=(router[i].read_y()+router[tempj_id].read_y())/2;
            dist_ij=dist(middle_x,middle_y,router[i].read_x(),router[i].read_y());

            for(k=0;k<router[i].neighbor.size();k++){
                tempk_id=router[i].neighbor[k].read_id();
                if(j!=k&&dist_ij>dist(middle_x,middle_y,router[tempk_id].read_x(),router[tempk_id].read_y())){
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                router[i].neighbor_planer.push_back(BN(router[tempj_id].read_id(),router[tempj_id].read_x(),router[tempj_id].read_y()));
            }
        }
    }
    cin >> packets;
    cout << packets << endl;
    for(i=0;i<packets;i++){
        cin >> j >> k;
        router[j].send_packets.push(GFGpacket(j,k,router[j].read_x(),router[j].read_y(),router[k].read_x(),router[k].read_y()));
        cout << router[j].send_packets.front().read_source() << ' ';
        while(1){
        	flag=0;
            for(j=0;j<router.size();j++){
                if(router[j].checkQueue()){
		    		router[j].send(router[j].send_packets.front(),router);
		    		if(router[j].send_packets.front().read_destination()==router[j].send_packets.front().read_next_hop()){
                        router[j].send_packets.pop();
                        flag=1;
                        break;
                    }
                }
            }
            if(flag==1)
                break;
            flag=1;
            for(j=0;j<router.size();j++){
                if(router[j].send_packets.empty()==false){
                    flag=0;
                    break;
                }
            }
            if(flag==1)
                break;
        }
        for(j=0;j<router.size();j++){
            if(router[j].send_packets.empty()==false)
                router[j].send_packets.pop();
        }
        cout << endl;
    }
    inStream.close();
    outStream.close();
}
