    #include <iostream>
    #include <vector>

    using namespace std;

    int main() 
    {
        
        vector<int> vasl = {0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30, 15, 31, 0, 16};

        // for(int v : vasl){
        //     cout<< v + 8 << ", ";
        // }
        // cout<<"\n";
        // for(int x=0; x<72; x++){
        //     cout<< x << ", ";
        // }
        // for(int x=0; x<=16; x++){
        //     cout<< x << ", " << x+16 <<", ";
        // }
        for(int x=8; x<=16; x++){
            for(int v : vasl){
                cout<< v + 16*x << ", ";
            }
             cout<<"\n";
        }
        return 0;
    }