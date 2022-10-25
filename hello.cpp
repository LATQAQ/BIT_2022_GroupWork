#include <iostream>
    #include<math.h>
    using namespace std;

    int arr[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    bool Leapyear(int i){
        return ((i%4 == 0 && i%100 !=0) || (i%400 == 0));
    }

    int main()
    {
        int y1,m1,d1,y2,m2,d2,n;
        int ans=0;
        cin>>y1>>m1>>d1>>n;
        while (n>0){
            d1++;
            n--;
            if(Leapyear(y1) && m1 == 2){
                if(d1 == arr[m1]+2){
                    m1++;
                    d1 = 1;
                }
            }
            else {
                if(d1 == arr[m1]+1){
                    m1++;
                    d1 = 1;
                }
            }
            if(m1 == 13){
                y1++;
                m1 = 1;
            }
        }   
        cout<<y1<<'.'<<m1<<'.'<<d1<<endl;;
        return 0;
    }