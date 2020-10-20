
#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> 
#include <cassert>
#include <cmath> 
using namespace std;

template<typename K, typename V>
void print_map(std::unordered_map<K,V> const &m)
{
	for (auto const& pair: m) {
		std::cout << "{" << pair.first << ": " << pair.second << "}\n";
	}
}

int main()
{
    //unigram calculation is complete 
    int unigram[26] = {};
    for(int i=0;i<26;i++)
        unigram[i]=0;
    double sum=0.0;
    double sum_bi=0.0;
    ofstream myfile;
    myfile.open("counts.txt");
    
  // reading a text file 
    string line;
    std::ifstream file("dataset_processed.txt");
    unordered_map<string, double> umap; 
    if (file.is_open())
  {
      while (getline(file,line))
    {
        for(int i=0;i<line.length();i++){
          string str="";
          str.push_back(line[i]);
          umap[str] = umap[str]+1;
          sum=sum+1;
        }
        if(line.length()>=2){
        
          for(int i=0;i<line.length()-1;i++){
            string substr = line.substr(i,2);
            umap[substr]=umap[substr]+1;
            sum_bi=sum_bi+1;
          }
        }
    }
  }
    else cout << "Unable to open file"; 

    double total=0.0;
   for (auto const& pair: umap) {
		std::cout << "{" << pair.first << ": " << (pair.second) << "}\n";
    myfile << pair.first << " " << pair.second << endl;
	}
  myfile << "sum_of_unigram "<< sum << endl;
  myfile.close();

  string example = "tatopo" ;
  string str="";
  str.push_back(example[0]);
  double value=-1*log2(umap[str]/sum); 
  for(int i=0;i<example.length()-1;i++){
    string next="";
    string prev="";

    prev.push_back(example[i]);
    next.push_back(example[i]);
    next=next+example[i+1];
    cout<<"prev "<<prev<<" "<< umap[prev] << endl;
    cout<<"next "<<next<< umap[next] << endl;
    value = value + -1*log2(umap[next]/umap[prev]);
  }
  cout<<value<<endl;

}


