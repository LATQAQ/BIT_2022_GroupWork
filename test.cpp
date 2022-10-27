#include<iostream>
#include<vector>
#include<windows.h>
#include<conio.h>
#include <random>
#include<time.h>

using namespace std;

int main(){
    vector<pair<int,int>> yx;
    
    yx.push_back(make_pair(0,0));
    yx.push_back(make_pair(0,1));
    yx.push_back(make_pair(0,2));
    yx.push_back(make_pair(1,1));
    

    for(int i=0;i<4;i++){
        cout<<yx[i].first<<yx[i].second<<endl;
    }
}