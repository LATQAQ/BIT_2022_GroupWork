//版本号：Alpha_001

/*
1.面向对象的程度？
2.亟需沟通与协作 (●'◡'●)
*/



#include<iostream>
#include<vector>
#include<windows.h>
#include<conio.h>
#include<random>
#include<time.h>

using namespace std;

#define shape_L 0
#define shape_I 1
#define shape_Z 2
#define shape_O 3
#define shape_T 4
#define shape_R_Z 5
#define shape_R_L 6

int row=16,col=15;  //长row宽col


class Block{  //方块类
    private:
    vector<pair<int,int>> yx;//每一点坐标
    public:
    Block(int kind){  //构造函数
        switch (kind){    //新的形状实现方法
            case shape_R_Z:
                yx.push_back(make_pair(1,3));
                yx.push_back(make_pair(1,4));
                yx.push_back(make_pair(0,4));
                yx.push_back(make_pair(0,5));
            break;
            case shape_R_L:
                yx.push_back(make_pair(0,1));
                yx.push_back(make_pair(1,1));
                yx.push_back(make_pair(2,1));
                yx.push_back(make_pair(2,0));
            break;
            case shape_L:
                yx.push_back(make_pair(0,0));
                yx.push_back(make_pair(1,0));
                yx.push_back(make_pair(2,0));
                yx.push_back(make_pair(2,1));
            break;
            case shape_I:
                yx.push_back(make_pair(0,0));
                yx.push_back(make_pair(1,0));
                yx.push_back(make_pair(2,0));
                yx.push_back(make_pair(3,0));
            break;
            case shape_Z:
                yx.push_back(make_pair(0,0));
                yx.push_back(make_pair(0,1));
                yx.push_back(make_pair(1,1));
                yx.push_back(make_pair(1,2));
            break;
            case shape_O:
                yx.push_back(make_pair(0,0));
                yx.push_back(make_pair(0,1));
                yx.push_back(make_pair(1,0));
                yx.push_back(make_pair(1,1));
            break;
            case shape_T:
                yx.push_back(make_pair(0,0));
                yx.push_back(make_pair(0,1));
                yx.push_back(make_pair(0,2));
                yx.push_back(make_pair(1,1));
            break;

        }
    }    
    //形状的最下方 用于向下移动时触底判断
    int LowSpace(){
        int max=-1;
        for(auto &point:yx){
            if(point.first > max)max = point.first;
        }
        return max;
    }
    //形状的最左方
    int LeftSpace(){
        int min=1000;
        for(auto &point:yx){
            if(point.second < min)min = point.second;
        }
        return min;
    }
    //形状的最右方
    int RightSpace(){
        int max=-1;
        for(auto &point:yx){
            if(point.second > max)max = point.second;
        }
        return max;
    }
    //向下掉落speed个格
    bool Fall_Down(int speed,vector<vector<int>> &mp){
        bool flag=true;
        for(auto &point:yx){
            if(mp[point.first+speed][point.second] == 1)flag=false;
        } 
        if(flag && LowSpace()+speed < row)
        for(auto &point:yx){
            point.first+=speed;
        } 
        return flag;
    }
    //向左1格
    void Go_Left(vector<vector<int>> &mp){
        bool flag=true;
        for(auto &point:yx){
            if(mp[point.first][point.second-1] == 1)flag=false;
        } 
        if(flag && LeftSpace()>0)
        for(auto &point:yx){
            point.second--;
        } 
    }
    //向右1格
    void Go_Right(vector<vector<int>> &mp){
        bool flag=true;
        for(auto &point:yx){
            if(mp[point.first][point.second+1] == 1)flag=false;
        } 
        if(flag && RightSpace()<col-1)
        for(auto &point:yx){
            point.second++;
        } 
    }
    //改变方向，旋转
    void Change_dir(vector<vector<int>> &mp){
        bool flag = true;
        vector<pair<int,int>> ryx;
        for(int i=0;i<4;i++){
            int xx = yx[1].second-yx[i].first+yx[1].first;
            int yy = yx[1].first+yx[i].second-yx[1].second;
            ryx.push_back(make_pair(yy,xx));
        }
        for(auto &rpoint:ryx){
            if(mp[rpoint.first][rpoint.second] == 1 || rpoint.first > row-1 || rpoint.second > col-1 || rpoint.second < 0){
                flag = false;
            }
        }
        if(flag){
            for(int i=0;i<4;i++){
                yx[i].first = ryx[i].first;
                yx[i].second = ryx[i].second;
            }
        }
    }
    //打印地图和方块
    void Draw(vector<vector<int>> &mp){   
        bool flag = false;
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                for(auto &point:yx){
                    if(point.first == i && point.second == j || mp[i][j] == 1)flag = true;
                } 
                if(flag)cout<<1;
                else cout<<0;
                flag = false;
            }
            cout<<endl;
        }
    }
    //在Mapp上固定这个方块
    void Accomplished(vector<vector<int>> &mp){
        for(auto &point:yx){
            mp[point.first][point.second]=1;
        } 
    }
    bool Touch(int speed,vector<vector<int>> &mp){
        bool flag=true;
        for(auto &point:yx){
            if(mp[point.first+speed][point.second] == 1)flag=false;
        } 
        return flag;
    }
    bool ifEnd(vector<vector<int>> &mp){
        if(LowSpace()==row-1 || (Touch(1,mp) == false)){  
            Accomplished(mp);
            return false;
        }
        else return true;
    }
    //析构方块 暂时看来不用析构，vector会自己释放
    ~Block(){
    }

};

int main(){
    int key=0;  //键盘输入
    int tt=0;   //创建的第tt个方块
    vector<vector<int>> Mapp(row+10,vector<int>(col+10,0));  //存储地图
    vector<Block> blocks;    //存储多个方块对象
    srand(time(nullptr));    //设置随机数的种子，以时间为种子
    while(true){     //外层循环
        Block block1(rand()%7);  //创建新的方块对象
        blocks.push_back(block1);
        while(true){
            //控制运行速度
            Sleep(500);
            //清除屏幕，以实现整个画面的固定
            system("cls");  
            //判断是否触底或接触已固定方块
            if(blocks[tt].ifEnd(Mapp) == false)break;
            blocks[tt].Draw(Mapp);
            //接收键盘输入
            if(_kbhit()){
                key = _getch();
                switch(key)
                {
                    case 'a':
                        blocks[tt].Go_Left(Mapp);
                        break;
                    case 'd':
                        blocks[tt].Go_Right(Mapp);
                        break;
                    case 's':
                        blocks[tt].Fall_Down(3,Mapp);
                        break;
                    case 'w':
                        blocks[tt].Change_dir(Mapp);
                        break;
                    case 27:    //"esc" 直接结束
                        return 0;
                }
            }  
            blocks[tt].Fall_Down(1,Mapp);
        }
        tt++;
        int cnt = 0;
        for(int i=row-1;i>=0;){
            for(int j=0;j<col;j++){
                if(Mapp[i][j] == 1)cnt++;
            }
            if(cnt == col){
                for(int p=0;p<col;p++){
                    Mapp[i][p] = 0;
                }
                for(int ii = i;ii>=2;ii--){
                    for(int jj=0;jj<col;jj++){
                        Mapp[ii][jj] = Mapp[ii-1][jj];
                    }
                }
                continue;
            }
            else i--;
            cnt=0;
        }
    }
    return 0;
}
