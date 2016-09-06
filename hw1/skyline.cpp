#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
   if(argc < 3){
  		cerr << "Please provide an input and output file." << endl;
   	return 1;
   }
	ifstream input(argv[1]);
	ofstream output(argv[2]);
	
	int constructionspots;
	int *buildingheights;
	string **skyline;
	string curr;

	input >> constructionspots;
	getline(input, curr); //consume the newline character for the first line.
	skyline = new string*[constructionspots];

	//you will need to keep track of the height of each building
	buildingheights = new int[constructionspots];

	for (int i = 0; i < constructionspots; i++) {
		buildingheights[i] = 0;
		skyline[i] = NULL;
	}	
	
	while(getline(input, curr)) {
		stringstream ss;
		ss << curr;
		ss >> curr;
	  	if (curr == "BUILD") {
		  	int x,y;
		  	string c;
		  	ss >> x; 
		  	ss >> y; 
		 	ss >> c; 
		  	if (ss.fail() || skyline[x] != NULL) {
		  		cout << ss.fail() << endl;
		  		cout << x << " " << y << " " << c << endl;  
			  	output << "Error - incorrect command" << endl;
		  	}
		  	else if(x<0 || x>=constructionspots || y<0){
		  		output << "Error - incorrect command ha" << endl; // check if falls in limit
		  	} 
		  	else {
		     	buildingheights[x] = y;  
				skyline[x] = new string[y]; 
		     	for(int i=0; i<y; i++){
		     		skyline[x][i] = c;
		     	} 
		  	}
	  	}
	  	else if (curr == "EXTEND") {
	  	  	int x,y; 
	  	  	string c; 
	  	  	ss >> x; 
	  	  	ss >> y; 
		  	ss >> c; 
		  	if(skyline[x] == NULL){
		  		output << "Error - incorrect command" << endl;
		  	}
		  	else{
		  		int currheight = buildingheights[x];
		  		int newheight = currheight + y; //9+6=15 

		  		string *temp;
		  		temp = new string[currheight]; 
		  		for(int i=0; i<currheight; i++){
		  			temp[i] = skyline[x][i]; 
		  		} 
				
				skyline[x] = new string[newheight]; 
		     	for(int i=0; i<currheight; i++){
		     		skyline[x][i] = temp[i];
		     	}
		     	
		     	// delete temp
		     		  		 
		  		for(int i=buildingheights[x]; i<newheight; i++){
		     		skyline[x][i] = c; //=blue
		     	}	 
		     	
		     	/*for(int i=0; i<newheight; i++){ //printing out
		     		cout << skyline[x][i] << " "; 
		     	}
		     	cout << endl; */
		     	
		     	buildingheights[x] = newheight; //=15
		  	}
	  	}
		else if (curr == "DEMOLISH") {
	  	  	int x; // spot
	  	  	ss >> x; 
	  	  	if(buildingheights[x] == 0){
	  	  	   output << "Error - incorrect command" << endl;
	  	  	}
	  	   else{ 
	  	   	delete [] skyline[x];
	  	   	skyline[x] = NULL; 
	  	   	buildingheights[x] = 0;
	  	   }
	  	}
	  	else if (curr == "SKYLINE") {
	  		int y; 
	   	ss >> y; // height
	  	   if(y<1){
	  	   	output << "Error - incorrect command" << endl; 
	  	   }
	  	   else {
	  	  		for(int i=1; i<=constructionspots; i++){
	  	  			if(buildingheights[i] >= y){ 
	  	        		output << skyline[i][y] << " " << endl;
	  	        	}
	  	        	else{
	  	        		output << "SKY " << endl;
	  	        	}
		   	}
		   	output << "\n" << endl;  
	  	   }
	  	}
	  	else {
			output << "Error - incorrect command" << endl;  
		}
  	}
  	
  	input.close(); 
  	
  	delete [] buildingheights; 
   buildingheights = NULL; 
   
   for(int i=0; i<constructionspots; i++) delete [] skyline[i];  
   delete [] skyline;
   skyline = NULL;  
  	
	return 0;
}
