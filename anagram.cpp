
#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> 
#include <cassert>
#include <cmath> 
#include <vector> 
#include <algorithm>
#include <chrono> 
#include <sstream>

#include <array>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <queue>
#include <utility>
using namespace std;
using namespace std::chrono;

#define possible_nodes 26

unordered_map<string, double> initialize_map(){
    ifstream file("counts.txt"); 
    string line="";
    unordered_map<string, double> umap;
     if (file.is_open())
  {
      while (getline(file,line))
    {
        string s = line;
        string delimiter = " ";
        string str = s.substr(0, s.find(delimiter));
        string val = s.substr(s.find(delimiter)+1,s.length()-s.find(delimiter));
        umap[str] = stod(val); 
    }
  }
   return umap;  
}

unordered_map<string,double> permutations;

//this function was not used finally as it was part of the brute force method I did initially. 
void permute(string a, int l, int r)  
{    
    if (l == r)  
        permutations[a]=0.0; 
    else
    {    
        for (int i = l; i <= r; i++)  
        {  
            swap(a[l], a[i]);  
            permute(a, l+1, r);  
            swap(a[l], a[i]);  
        }  
    }  
}  
  
//this function was not used finally as it was part of the brute force method I did initially. 
double word_probability(string s, unordered_map<string, double> umap){
  string str="";
  str.push_back(s[0]);

  double value=-1*log2(umap[str]/umap["sum_of_unigram"]); 
  for(int i=0;i<s.length()-1;i++){
    string next="";
    string prev="";

    prev.push_back(s[i]);
    next.push_back(s[i]);
    next=next+s[i+1];
    value = value + -1*log2(umap[next]/umap[prev]);
  }
  return value;
}

//this function was not used finally as it was part of the brute force method I did initially. 
void print_k_minimum(unordered_map<string, double> result, int k){

    vector<std::pair<double, string>> results;
    results.reserve(result.size());

    for(auto kv : result) {
        results.push_back({kv.second,kv.first}); 
    }
   sort(results.begin(), results.end());
   int i=0;
   for(auto kv : results){
       cout << kv.second << " " << kv.first << endl; 
        if( i == (k-1))
            break;
        i++;
   }
}
//function used to sort the hashmap of the results (Referenced from geeks for geeks)

bool compare_function(pair<string, double> one,
         pair<string, double> two)
{
    return one.second < two.second;
}

//(Referenced from geeks for geeks)

void sort(unordered_map<string, double>& map) 
{ 
  
    // Declare vector of pairs 
    vector<pair<string, double>> A; 
  
    // Copy key-value pair from Map 
    // to vector of pairs 
    for (auto& it : map) { 
        A.push_back(it); 
    } 
  
    // Sort using comparator function. 
    sort(A.begin(), A.end(), compare_function); 
  
    // Print the sorted value 
    for (auto& it : A) { 
  
        cout << it.first << ' ';
        cout<<setprecision(20)<< it.second << endl; 
    } 
} 

void dijkstra(string s, unordered_map<string, double> umap,int k){

    // a set to store all the nodes that have not been looked at yet. 
    array<char, possible_nodes> not_visited;

    //we store the results in a hashmap so that we dont get any repeating anagrams 
    unordered_map<string,double> results;

    // needed to create a new one since it didnt exist for pairs, only other data types. 
        struct Greater {
            bool operator()(const pair<string,double>& x, const pair<string,double>& y) const {
                return x.second > y.second;
            }
        };

    //needed for implementing dijkstra's algorithm to get the shortest next path 
    priority_queue<pair<string,double>, vector<pair<string,double>>, Greater> proccess_nodes;
 
    // initialize array of not_visited to 0 which means that it is empty and consists of no node.
        for(int i=0;i<possible_nodes;i++)
            not_visited[i]=0;

    // we add all the letters in the word into the node set and is marked as not visited 
    for(int i=0;i<s.length();i++){
        int index = s[i] - 'a';
        not_visited[index] = not_visited[index]+1; 
    }

        //since all the different letters are the different nodes in the graph, we add them all to the priority queue 
        //they are marked as not visited
        for(int i=0;i<possible_nodes;++i){
            if(not_visited[i]>0){
            string str="";
            char a = (char)(i + 'a');
            str.push_back(a);
            pair<string,double> letter; 
            letter.first = str;
            letter.second= -1*log2(umap[str]/umap["sum_of_unigram"]);
            proccess_nodes.push(letter);
        }
    }

        // condition stops once we have collected k anagrams 
        while(!proccess_nodes.empty() && results.size()<k ){
            pair<string,double> u = proccess_nodes.top(); 
            proccess_nodes.pop();

            if(u.first.length()==s.length()){ //this is the condition to check if the word is an anagram 
                results[u.first]=u.second; //store in hashmap
            }
            else { 

                //we create an array of the visited nodes so far that was popped from the stack. 
                array<char, possible_nodes> visited = not_visited;
                for(char i : u.first){
                    visited[i-'a'] = visited[i-'a'] -1;
                }

                //iterate through the adjacency list. Since this is a two way directed graph, 
                //all the remaining letters in the word is in the adjacency list 
                //they should not be repeated back to back otherwise it will cause duplicates
                for (int i = 0; i < possible_nodes; ++i) {
                    if (visited[i] > 0) {
                    string latest = u.first + char(i + 'a');
                    string next="";
                    string prev="";
                    int length = latest.length();
                    next.push_back(latest[length-2]);
                    next.push_back(char(i + 'a'));
                    prev.push_back(latest[length-2]);
                    double value = u.second + -1*log2(umap[next]/umap[prev]); //calculate the probability score
                    pair<string,double> latest_pair; 
                    latest_pair.first=latest; 
                    latest_pair.second=value;
                    proccess_nodes.push(latest_pair); //add a new node to the priority queue to continue with dijkstra's algorithm 
                }
            }
        }
    }

    //print results from hashmap 
    sort(results);

}


int main(int argc, char** argv)
{
   unordered_map<string, double> umap = initialize_map();

   string s = {argv[1]};
   int k=0;

   if (argc >= 3)
    {
        std::istringstream iss( argv[2] );
        

        if (iss >> k)
        {
            // Conversion successful
            cout << "Initialization Successful"<<endl;
        }
    }


   auto start = high_resolution_clock::now(); 
   dijkstra(argv[1],umap,k);
   auto stop = high_resolution_clock::now(); 
   auto duration = duration_cast<microseconds>(stop - start);
   cout <<"Total time taken: "<< duration.count()<< " microseconds"<<endl;

}






