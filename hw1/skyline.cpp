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
		 	x=x-1; // 0
		  	if (ss.fail() || skyline[x] != NULL) {
		  		cout << ss.fail() << endl;
		  		//cout << x << " " << y << " " << c << endl;  
			  	output << "Error - incorrect command" << endl;
		  	}
		  	else if(x<0 || x>=constructionspots || y<0){ // check if falls in limit
		  		output << "Error - incorrect command ha" << endl; 
		  	} 
		  	// else if(check if color is not wrong input)
		  	// else if(check if all numbers are integers)
		  	else {
		     	buildingheights[x] = y;  
				skyline[x] = new string[y]; 
		     	for(int i=0; i<y; i++){
		     		skyline[x][i] = c;
		     	} 
		  	}
	  	}
	  	else if (curr == "EXTEND") { //extending the height by 0???
	  	  	int x,y; 
	  	  	string c; 
	  	  	ss >> x; 
	  	  	ss >> y; 
		  	ss >> c; 
		  	x=x-1;
		  	if(ss.fail() || skyline[x] == NULL){
		  		output << "Error - incorrect command" << endl;
		  	}
		  	else{
		  		int currheight = buildingheights[x]; 
		  		int newheight = currheight + y; 

		  		string *temp;
		  		temp = new string[currheight]; 
		  		for(int i=0; i<currheight; i++){
		  			temp[i] = skyline[x][i]; 
		  		} 
				
				delete [] skyline[x];
				skyline[x] = NULL;  
				
				skyline[x] = new string[newheight]; 
		     	for(int i=0; i<currheight; i++){
		     		skyline[x][i] = temp[i];
		     	}
		     	
		     	delete [] temp; 
  			 	temp = NULL; 
  			 	  		 
		  		for(int i=currheight; i<newheight; i++){ 
		     		skyline[x][i] = c; 
		     	}	 
		     	buildingheights[x] = newheight; 
		  	}
	  	}
		else if (curr == "DEMOLISH") {
	  	  	int x; // spot
	  	  	ss >> x; 
	  	  	x=x-1; 
	  	  	if(ss.fail() || buildingheights[x] == 0){
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
	  	   if(ss.fail() || y<1){
	  	   	output << "Error - incorrect command" << endl; 
	  	   }
	  	   else { 
	  	  		for(int i=0; i<constructionspots; i++){
	  	  			if(buildingheights[i] >= y){ 
	  	        		output << skyline[i][y-1] << " ";
	  	        	}
	  	        	else{
	  	        		output << "SKY ";
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
