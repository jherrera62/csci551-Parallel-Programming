#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
using namespace std;
namespace fs = std::filesystem;
class Picture
{
    public:
        string name;
        vector<vector<char>> bits;
};
int main()
{
    ifstream fin;
    vector<string>filename;//stores the names of the pgm card files
    int n=52;//number of cards
    vector<Picture> picture;//a vector to store each individual picture
    int rows=690,columns=920;//the resolution of each card
    //this loop will iterate through the entire directory mainly to save the name of each file
    for (const auto& entry : fs::directory_iterator("cards_3x4_pgm/"))
    {
        filename.push_back(entry.path());
    }
    for(int i=0; i<n; i++)
    {
        stringstream ss;
        string line= "";
        Picture curPicture;
        char bit;
        cout<<"opening file: "<<filename[i]<<endl;
        fin.open(filename[i]);//opening the current image file
        //Magic bytes
        getline(fin,line);
        cout<<"Version: "<<line<<endl;
        getline(fin,line);
        cout<<"Comment: "<<line<<endl;
        getline(fin,line);
        cout<<"Width and Height: "<<line<<endl;
        getline(fin,line);
        cout<<"Grey scale: "<<line<<endl;
        vector<vector<char>>hex_value;
        vector<char> buf;
        for(int j=0; j<rows; j++)
        {
            for(int p=0; p<columns; p++)
            {
                ss>>bit;
                buf.push_back(bit);
            }
            hex_value.push_back(buf);
        }
        fin.close();
        curPicture.name=filename[i];
        curPicture.bits=hex_value;
        picture.push_back(curPicture);
    }
}