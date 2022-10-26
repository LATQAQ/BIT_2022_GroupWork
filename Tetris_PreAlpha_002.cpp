//版本号：PreAlpha_002

/*
1.消除功能未完成
2.运动方块 与 已固定方块 产生冲突，未解决
3.旋转方向未实现
4.面向对象的程度？
5.右侧出框问题未解决
6.亟需沟通与协作 (●'◡'●)
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

int row=30,col=15;  //长row宽col


class Block{  //方块类
    private:
    int dir;  //方向
    int speed=1;  //下落速度
    public:
    int shape[4][4] = {0};  //形状
    int Right;  //最右坐标
    int Bottom;  //最下坐标
    Block(int kind,int dirr){  //构造函数
        Right = 3;  //初始化为（3，3）
        Bottom = 3;
        dir = dirr;    //方向及旋转还没实现
        switch (kind){    //暂时的形状实现方法
            case shape_R_Z:
                shape[1][0]=1;
                shape[1][1]=1;
                shape[0][1]=1;
                shape[0][2]=1;
            break;
            case shape_R_L:
                shape[0][1]=1;
                shape[1][1]=1;
                shape[2][1]=1;
                shape[2][0]=1;
            break;
            case shape_L:
                shape[0][0]=1;
                shape[1][0]=1;
                shape[2][0]=1;
                shape[2][1]=1;
            break;
            case shape_I:
                shape[0][0]=1;
                shape[1][0]=1;
                shape[2][0]=1;
                shape[3][0]=1;
            break;
            case shape_Z:
                shape[0][0]=1;
                shape[0][1]=1;
                shape[1][1]=1;
                shape[1][2]=1;
            break;
            case shape_O:
                shape[0][0]=1;
                shape[0][1]=1;
                shape[1][0]=1;
                shape[1][1]=1;
            break;
            case shape_T:
                shape[0][0]=1;
                shape[0][1]=1;
                shape[0][2]=1;
                shape[1][1]=1;
            break;

        }
    }    
    //形状的最下方 用于向下移动时触底判断
    int LowSpace(int shape[4][4]){
        for(int i=3;i>=0;i--){
            for(int j=0;j<4;j++){
                if(shape[i][j]==1)return i;
            }
        }
    }
    //形状的最左方
    int LeftSpace(int shape[4][4]){
        for(int i=0;i<4;i++){
            for(int j=3;j>=0;j--){
                if(shape[j][i]==1)return i;
            }
        }
    }
    //形状的最右方
    int RightSpace(int shape[4][4]){
        for(int i=3;i>=0;i--){
            for(int j=0;j<4;j++){
                if(shape[j][i]==1)return i;
            }
        }
    }
    //向下掉落speed个格
    void Fall_Down(int speed){ 
        if(Bottom-(3-LowSpace(shape)) + speed < row)
        Bottom+=speed;
    }
    //向左1格
    void Go_Left(){
        if(Right+LeftSpace(shape)>3)
        Right--;
    }
    //向右1格
    void Go_Right(){
        if(Right-(3-RightSpace(shape))<col-1)
        Right++;
    }
    //改变方向，旋转
    void Change_dir(){

    }
    //打印出形状
    void Draw(int i,int r){
        for(int j=0;j<=3;j++){
            cout<<shape[i][j];
        }
    }
    //在Mapp上固定这个方块
    void Accomplished(vector<vector<int>> &mp){
        int q=0,p=0;
        for(int i=Bottom-3;i<=Bottom;i++){
            for(int j=Right-3;j<=Right;j++){
                if(shape[p][q] == 1)mp[i][j]=1;
                q++;
            }
        q=0;
        p++;
        }
    }
    //找到方块最下方的接触点
    vector<vector<int>> TouchPoint(){
        vector<vector<int>> arr(4,vector<int>(2,-1));
        int cnt=0;
        for(int i=3;i>=0;i--){
            for(int j=0;j<=3;j++){
                if(i==3&&shape[i][j]==1){
                    arr[cnt][0]=i;
                    arr[cnt][1]=j;
                    cnt++;
                }
                else if(i!=3 && shape[i][j]==1 && shape[i][j+1]==0){
                    arr[cnt][0]=i;
                    arr[cnt][1]=j;
                    cnt++;
                }
            }
        }
        return arr;
    }
    //接触下方的已固定方块
    bool Touch(vector<vector<int>> &mp){
        vector<vector<int>> arr = TouchPoint();
        bool flag = true;
        for(auto i:arr){
            if(i[0]!=-1)
                if(mp[Bottom-(3-i[0])+1][Right-3+i[1]] == 1){
                    flag = false;
                }
        }
        return flag;
    }
    //析构方块
    ~Block(){
        delete shape;
    }

};

int main(){
    int key=0;  //键盘输入
    int tt=0;   //创建的第tt个方块
    bool flag = true;  //用于结束内层循环的bool
    vector<vector<int>> Mapp(row,vector<int>(col,0));  //存储地图
    vector<Block> blocks;    //存储多个方块对象
    srand(time(nullptr));    //设置随机数的种子，以时间为种子
    while(true){     //外层循环
        flag = true;
        Block block1(rand()%7,0);  //创建新的方块对象
        blocks.push_back(block1);
        while(flag){
            //判断是否触底或接触已固定方块
            if(blocks[tt].Bottom-(3-blocks[tt].LowSpace(blocks[tt].shape))==row-1 || blocks[tt].Touch(Mapp) == false){  
                blocks[tt].Accomplished(Mapp);
                flag = false;
                break;
            }
            system("cls");  //清除屏幕，以实现整个画面的固定
            int cnt=0;    //打印地图和方块
            for(int i=0; i<row; i++){
                for(int j=0; j<col; j++){
                    if(i >= blocks[tt].Bottom-3 && i <= blocks[tt].Bottom && j == blocks[tt].Right-3 && blocks[tt].Bottom-(3-blocks[tt].LowSpace(blocks[tt].shape))-1<row){
                        blocks[tt].Draw(cnt,col);
                        cnt++;
                        j+=3;
                    }
                    else cout<<Mapp[i][j];
                }
                cout<<endl;
            }
            //接收键盘输入
            if(_kbhit()){
                key = _getch();
                switch(key)
                {
                    case 'a':
                        blocks[tt].Go_Left();
                        break;
                    case 'd':
                        blocks[tt].Go_Right();
                        break;
                    case 's':
                        blocks[tt].Fall_Down(3);
                        break;
                    case 'w':
                        blocks[tt].Change_dir();
                        break;
                    case 27:    //"esc" 直接结束
                        return 0;
                }
            }  
            blocks[tt].Fall_Down(1);
            //控制运行速度
            Sleep(500);
        }
        tt++;
    }
    return 0;
}
