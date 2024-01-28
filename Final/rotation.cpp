#include <iostream>
#include <fstream>
#include <string>
#include <vector>//this is for the data structure we need to hold
#include <experimental/filesystem>//so we can traverse the file system and access our cards
#include <time.h>//this is to time the program
using namespace std;
namespace fs = std::experimental::filesystem;

//this vector will hold the paths of each card
vector<string> cardPath;
//this vector will hold all the pixel data from each card in the specified directory
vector<vector<vector<uint8_t>>> imageVector;
//this data structure will be used to hold all of the pixel data from the images once they are rotated
vector<vector<vector<uint8_t>>> rImageVector;
int rows=920;
int columns=690;
struct timespec start,stop;
//resizeRIV is resizing the rImageVector
void resizeRIV(int index,int rows, int columns)
{
    rImageVector[index].resize(rows);//we are populating the number of rows in the imageVector
    for(int i=0; i<rows;i++)
    {
        rImageVector[index][i].resize(columns);//this is populating the amount of columns we need
    }

}
//resizeIV is resizing the ImageVector
void resizeIV(int index,int rows, int columns)
{
    imageVector[index].resize(rows);//we are populating the number of rows in the imageVector
    for(int i=0; i<rows;i++)
    {
        imageVector[index][i].resize(columns);//this is populating the amount of columns we need
    }

}
void rotateCards(int i, string direction, int rows, int columns)
{
    //resize rimagevector to be 690*920
    resizeRIV(i,690, 920);
    if(direction=="right")
    {
        for(int j=0; j<920; j++)
        {
            for (int k=0; k<690; k++)
            {
                rImageVector[i][k][rows - j -1]=imageVector[i][j][k];
            }
        }

    }
    else if (direction=="left")
    {
        for(int j=0; j<920; j++)
        {
            for (int k=0; k<690; k++)
            {
                rImageVector[i][columns - k -1][j]=imageVector[i][j][k];
            }
        }
    }
}
void cardPixelInput(int index, string direction, int rows, int columns)
{
    
    //this will open the card given the path of the card on my system
    string image = cardPath[index];
    ifstream fin(image);
    string str;
    //This is where we will store the pixel data for each card
    char pixelData[1];
    //these getlines will get the first for lines of information from the cards
    //1. Type
    getline(fin,str);
    //2. Comment
    getline(fin,str);
    //3. Resolution
    getline(fin,str);
    //4. Color Value
    getline(fin,str);
    //this will populate the vector image vector with the required amount of elements to store pixel data
    resizeIV(index,rows,columns);
    for(int row = 0; row<920;row++)
    {
        for(int col=0; col<690;col++)
        {
            fin.read(pixelData,1);
            imageVector[index][row][col]=pixelData[0];
        }
    }
    fin.close();
}

int main(int argc, char* argv[])
{
    int rows=920;
    int columns=690;
    string direction=argv[1];//determines which way the cards will be rotated
    ifstream fin;
    vector<string>filename;//stores the names of the pgm card files
    int n=52;//number of cards
    struct timespec start,end;
    double fstart = 0.0, fend = 0.0;
    for (const auto& entry : fs::directory_iterator("cards_3x4_pgm/"))
    {
        cardPath.push_back(entry.path());
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    imageVector.resize(cardPath.size());
    rImageVector.resize(cardPath.size());
    //this for loop will output all the rotated images into a file
    for(int i =0; i<cardPath.size();i++)
    {
        //This function will store the pixel data for each card
        fstream fout;
        cardPixelInput(i, direction,rows,columns);
        rotateCards(i, direction,rows,columns);
        string outputFile = "rotatedImages/"+cardPath[i];
        fout.open(outputFile, fstream::out);
        if (!fout)
        {
            cout<<"Error opening file"<<endl;
        }
        fout<<"P5"<<endl;
        fout<<"# comment"<<endl;
        fout<<rows<<" "<<columns<<endl;
        fout<<255<<endl;
        for(int j=0; j<columns; j++)
        {
            for(int k=0;k<rows;k++)
            {
                fout<<rImageVector[i][j][k];
            }
        }
        fout.close();
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    fstart = start.tv_sec + (start.tv_nsec / 1000000000.0);
    fend = end.tv_sec + (end.tv_nsec / 1000000000.0);
    cout<<"Time program took after File I/O: "<<fend-fstart<<"s"<<endl;
}