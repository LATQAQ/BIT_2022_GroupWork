#include<iostream>
#include<vector>
#include<windows.h>
#include<conio.h>
#include <random>
#include<time.h>

using namespace std;

#define shape_L 0
#define shape_I 1
#define shape_Z 2
#define shape_O 3
#define shape_T 4
#define shape_R_Z 5
#define shape_R_L 6
int row=30,col=15;

class Block{
    private:
    int dir;
    int speed=1;
    public:
    int shape[4][4] = {0};
    int Right;
    int Bottom;
    Block(int kind,int dirr){
        Right = 3;
        Bottom = 3;
        dir = dirr;
        switch (kind){
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
    int LowSpace(int shape[4][4]){
        for(int i=3;i>=0;i--){
            for(int j=0;j<4;j++){
                if(shape[i][j]==1)return i;
            }
        }
    }
    int LeftSpace(int shape[4][4]){
        for(int i=0;i<4;i++){
            for(int j=3;j>=0;j--){
                if(shape[j][i]==1)return i;
            }
        }
    }
    int RightSpace(int shape[4][4]){
        for(int i=3;i>=0;i--){
            for(int j=0;j<4;j++){
                if(shape[j][i]==1)return i;
            }
        }
    }
    void Fall_Down(int speed){ 
        if(Bottom-LowSpace(shape)<row)
        Bottom++;
    }
    void Go_Left(){
        if(Right+LeftSpace(shape)>3)
        Right--;
    }
    void Go_Right(){
        if(Right-(3-RightSpace(shape))<col-1)
        Right++;
    }
    void Change_dir(){

    }
    void Draw(int i,int r){
        for(int j=0;j<=3;j++){
            cout<<shape[i][j];
        }
    }
    void Accomplished(vector<vector<int>> &mp){
        int q=0,p=0;
        for(int i=Bottom;i>=Bottom-3;i--){
            for(int j=Right-3;j<=Right;j++){
                if(shape[p][q] == 1)mp[i][j]=1;
                q++;
            }
        p++;
        }
    }
    ~Block(){
        delete shape;
    };
};

void gotoxy(int x, int y) {
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}


int main(){
    int key=0;
    vector<vector<int>> Mapp(row,vector<int>(col,0));
    vector<Block> blocks; 
    srand(time(nullptr));
    while(true)
    while(true){
        int cnt=0;
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(i >= block_test.Bottom-3 && i <= block_test.Bottom && j == block_test.Right-3 && block_test.Bottom-block_test.LowSpace(block_test.shape)+1<row){
                    block_test.Draw(cnt,col);
                    cnt++;
                    j+=3;
                }
                else cout<<Mapp[i][j];
            }
            cout<<endl;
        }
        if(_kbhit()){
            key = _getch();
            switch(key)
            {
                case 'a':
                    block_test.Go_Left();
                    break;
                case 'd':
                    block_test.Go_Right();
                    break;
                case 's':
                    block_test.Fall_Down(1);
                    break;
                case 'w':
                    block_test.Change_dir();
                    break;
                case 27:
                    return 0;
            }
        }  
        block_test.Fall_Down(1);
        if(block_test.Bottom-(4-block_test.LowSpace(block_test.shape))==row){
            block_test.Accomplished(Mapp);
            Block *p = &block_test;
            delete p ;
            p = nullptr;
            Block block_test(rand()%7,0);
        }
        Sleep(1000);
        system("cls");
    }
    return 0;
}