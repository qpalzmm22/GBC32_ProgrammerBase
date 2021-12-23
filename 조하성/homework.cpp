#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string input;
    getline(cin, input);
    
    string temp;
    int check = 0;
    for(int i = 0; i < input.length(); i++)
    {
        if(input[i] == ' ')
        {
            if(check != 1)
            {
            reverse(temp.begin(), temp.end());
            cout << temp << " ";
            temp.clear();
            }
            else
                temp += input[i];
            
        }
        else if(input[i] == '<')
        {
            check = 1;
            reverse(temp.begin(), temp.end());
            cout << temp << input[i];
            temp.clear();
        }
        else if(input[i] == '>')
        {
            check = 0;
            cout << temp << input[i];
            temp.clear();
        }
        else
            temp += input[i];
    }
    reverse(temp.begin(), temp.end());
    cout << temp << endl;
    return 0;
}   
