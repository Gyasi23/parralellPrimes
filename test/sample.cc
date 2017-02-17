#include <vector>
#include <string>
#include<fstream>
#include <algorithm>
#include <iostream>
using namespace std;

class CircleTheWordWCSolver {
 public:
    
    ifstream input;
    void get_word(){
        char puzzle;
        input.open("datain.txt");
        int x;
        int y;
        cin>>x>>y;
	char myArray[x][y];
        input.get(puzzle);
        while(!input.eof())
        {
            for(int i = 0; i < x; i++)
            {
                for(int j = 0; j < y; ++j)
                {
                    myArray[i][j] = puzzle;
                }
            }
            input.get(puzzle);
        }
        
        for(int i = 0; i < x; ++i)
        {
            for(int j = 0; j < y; ++j)
            {
                cout<< myArray[i][j];
            }
        }
    }
    
};


    int main()
    {
        CircleTheWordWCSolver a;
        a.get_word();
        
        return 0;
    }
