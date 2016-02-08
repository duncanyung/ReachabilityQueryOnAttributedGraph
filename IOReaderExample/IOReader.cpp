#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

using namespace std;

int main(int argc, char const * argv[]){
	ifstream inf("vSynopsis-roadNet-PA.txt");
 
    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        cerr << "Uh oh, Sample.dat could not be opened for reading!" << endl;
        exit(1);
    }
 
    string strData;
 	int c = (30+1)*10 + 30 + 1 + 1 + 1;//24;//7 + 5*2 + 5 + 1, 
    int row = atoi(argv[1]);
 	int addr = c * row;
    printf("addr=%d\n",addr);
    inf.seekg(addr); // move to 5th character
    // Get the rest of the line and print it
    getline(inf, strData);
    cout << strData << endl;
 
 	int row2 = atoi(argv[2]);
 	addr = c*row2;
 	inf.seekg(addr); // move to 5th character
    getline(inf, strData);
    cout << strData << endl;

/*    inf.seekg(8, ios::cur); // move 8 more bytes into file
    // Get rest of the line and print it
    getline(inf, strData);
    cout << strData << endl;
 
    inf.seekg(-15, ios::end); // move 15 bytes before end of file
    // Get rest of the line and print it
    getline(inf, strData);
    cout << strData << endl;
    */

    inf.close();
	return 0;	
}