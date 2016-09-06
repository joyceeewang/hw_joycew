#include <iostream>
#include <fstream>
#include <string>

using namespace std; 

int main(int argc, char* argv[]){
	if(argc < 2){
		cerr << "Please provide filename." << endl;
    	return 1;
  	}

	ifstream inFile(argv[1]);   
   string *arr; 
   int n;
   
   inFile >> n;       
   arr = new string[n]; 
   while(!inFile.fail()){
      for(int i=0; i<n; i++) inFile >> arr[i]; 
   }
   
   inFile.close();
    
   for(int i=n-1; i>=0; i--) cout << arr[i]<< endl; 
   
   delete [] arr; 
   arr = NULL; 
} 

