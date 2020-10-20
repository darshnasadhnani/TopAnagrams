
#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
  //read the dataset text file for preprocessing 
  // reading a text file
  string line;
  std::ifstream file("dataset.txt");
  ofstream out_file;
  out_file.open("dataset_processed.txt");

  if (file.is_open())
  {
    while ( std::getline(file,line) )
    {
      bool flag=true;
      for(int i=0;i<line.length();i++){
         
          if(!((line[i]<='Z' && line [i]>='A') || (line[i]<='z' && line[i]>='a'))){
            flag=false;
          }
          if(line[i]>='A' && line[i]<='Z')
            line[i]=char(line[i]+32);
    }
    if(flag==true){
        out_file << line << endl;
    }
  }
    file.close();
    out_file.close();
  }

  else cout << "Unable to open file"; 

}

