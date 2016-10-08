/*************************************************************************
    > File Name: depth_first_search.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Sat 08 Oct 2016 02:40:11 PM
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/* Roads Problem: POJ1724
 * how to prune? 
 * 1. if finding a path with length being L, during the following search, ignore the path which is greater than L
 * 2. when reaching a node v, which is visited before, if current cost is greater than that of the last time, then prune
*/

vector<bool> Visited;
int iBudget;
int iCityCount;
int iRoadCount;
int iMinLength = 1<<30;
int iCurCost=0;
int iCurLength=0;
vector<vector<int>> TempMinLen; //TempMInLen[i][j] represents from 0 to i, the lengh of the path with minimum cost

struct Road{
    int road_id;    //the identifier of this road
    int src_city; //source city of the road
    int dst_city; //destination city of the road
    int length; //how long is this road
    int cost;   //how much it costs to get through this road
};

void PruningDFS(int city_id, const vector<vector<Road>>& vecRoads){
    if(city_id==iCityCount-1){
        iMinLength = min(iMinLength, iCurLength);
        return;
    }

    for(int i=0;i<vecRoads[city_id].size();i++){
        int dst_city = vecRoads[city_id][i].dst_city;
        if(!Visited[dst_city]){
            //pruning when this path exceeds the budget
            if(iCurCost+vecRoads[city_id][i].cost>iBudget) continue;

            //pruning when curren path length is grater than currently global minimum path length 
            if(iCurLength+vecRoads[city_id][i].length>=iMinLength) continue;

            //pruning when visiting a city again, the length is longer
            if(iCurLength+vecRoads[city_id][i].length>=TempMinLen[dst_city][iCurCost+vecRoads[city_id][i].cost]) continue;
        
            iCurLength += vecRoads[city_id][i].length;
            iCurCost += vecRoads[city_id][i].cost;
            TempMinLen[dst_city][iCurCost] = iCurLength;
            Visited[dst_city] = true;
            PruningDFS(dst_city, vecRoads);
            Visited[dst_city] = false;
            iCurLength -= vecRoads[city_id][i].length;
            iCurCost -= vecRoads[city_id][i].cost;
        }
    }
}

int main(){
    cout<<"Please input city count, road count and total budget:"<<endl;
    cin>>iCityCount>>iRoadCount>>iBudget;

    vector<vector<Road>> vecRoads;
    vecRoads.resize(iCityCount);
    cout<<"Please input source city, destination city, road length, road cost:"<<endl;
    for(int i=0;i<iRoadCount;i++){
        int src_city, dst_city;
        Road road;
        cin>>src_city>>dst_city>>road.length>>road.cost;
        if(src_city==dst_city) continue;
        road.src_city = src_city;
        road.dst_city = dst_city;
        vecRoads[src_city].push_back(road);
    }

    for(int i=0;i<iCityCount;i++){
        vector<int> vecTemp;
        TempMinLen.push_back(vecTemp);
        Visited.push_back(false);
        for(int j=0;j<iBudget+1;j++) TempMinLen[i].push_back(1<<30);
    }

    PruningDFS(0, vecRoads);

    if(iMinLength==1<<30) cout<<"There is no feasible path from 0 to "<<iCityCount-1<<endl;
    else cout<<"It takes "<<iMinLength<<" from 0 to "<<iCityCount-1<<endl;
}


