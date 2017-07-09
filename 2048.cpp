#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>

//Software Engineering Assignment 3 Spring 2015
//Francine Tran 00953181


using namespace std;

bool shiftGrid(vector <int> &game,string move);
int coordtoidx(int x, int y);
bool checkforspaces(const vector <int> &game);	
void randomTwo(vector <int> &game);
bool gameover(const vector <int> &game);
void rotateGrid(vector <int> &game);	
bool shiftZeroes(vector <int> &game);
void writeGrid(const vector <int> &game);

int main(){
	
	srand(time(NULL));
	vector <int> game;
	string gamefile;
	ifstream infile;
	bool change = true;
	int temp;
	string move;

	cout<<"please enter configuration file."<<endl;
	cin>>gamefile;

	infile.open(gamefile.c_str());
	
	if(!infile.is_open()){
		
		cout<<"file not found, using default start configuration"<<endl;

		for(int i=0; i<16; i++){

			game.push_back(0);
		}
		game[15]=2;
	}
	
	else{
		while(infile >> temp){
		game.push_back(temp);
		}

	infile.close();
	}
	
	writeGrid(game);
	
	cout << "Your possible moves are w,s,a,d."<<endl;
	do{
		cin>>move;

		if(checkforspaces(game)){
			if(shiftGrid(game,move)){
				if(checkforspaces(game)){
				randomTwo(game);
				}
			writeGrid(game);
			}
		}
		else{
			if(gameover(game)){
				move ="stop";
			}
			else{
				if(shiftGrid(game,move)){
				writeGrid(game);
				}
			}
		}
	}while(move!="stop");

	cout <<"game over"<<endl;

return 0;
}

void writeGrid(const vector <int> &game){
	for(int i=1; i<17; i++){
			cout<< game[i-1] << "\t";
		if(i % 4 ==0){
			cout <<endl;
		}
	}
}

void rotateGrid(vector <int> &game){ //rotates the grid 90degrees clockwise
int temp;
	for(int x=0;x<2;x++){
		for(int y=x;y<3-x;y++){
			temp=game[coordtoidx(x,y)];
			game[coordtoidx(x,y)]=game[coordtoidx(y,3-x)];
			game[coordtoidx(y,3-x)]=game[coordtoidx(3-x,3-y)];
			game[coordtoidx(3-x,3-y)]=game[coordtoidx(3-y,x)];
			game[coordtoidx(3-y,x)]=temp;
		}
	}
}

int coordtoidx(int x, int y){ //converts the coordinates to an index

	return (4*y)+x;
}


bool shiftGrid(vector <int> &game,string move){
	bool change = false; //Initially there has been no change to the board
	int numberOfrot;
	if (move=="a"){
		numberOfrot=1;
	}
	else if(move=="s"){
		numberOfrot=2;	
	}
	else if(move=="d"){
		numberOfrot=3;	
	}
	else if(move=="w"){
		numberOfrot=0;	
	}
	else{
		return false; //if the user entry is not wasd then do not attempt to shift the grid.
	}
	for(int i=0;i<numberOfrot;i++){ //depending on the user entry the grid will rotate numberOfrot times
		rotateGrid(game);
	}

	change = shiftZeroes(game); //before merging, all the numbers are shifted where possible. If any numbers have moved then shiftzeroes returns true and change becomes true                            

		for(int x=0;x<4;x++)
		{
			for(int y=0;y<3;y++){
				if(game[coordtoidx(x,y)]==game[coordtoidx(x,y+1)] && game[coordtoidx(x,y)]!=0){ //iterates downwards along the grid and merges numbers if they are the same 
					game[coordtoidx(x,y)] +=  game[coordtoidx(x,y+1)];
					game[coordtoidx(x,y+1)] = 0;
					shiftZeroes(game);
					change =true;
				}
			}		
	}
						
	for(int i=0;i<4-numberOfrot;i++){ //finally the grid is reverted back to the correct orientation
		rotateGrid(game);
	}
			
	return change;
}

bool shiftZeroes(vector <int> &game){ //shifts all the non zero tiles into zero tiles
	bool shifted=false;
	for(int i=0;i<16;i++){
		for(int x=0;x<4;x++)
		{
			for(int y=3;y>0;y--){
				if(game[coordtoidx(x,y-1)]==0 && game[coordtoidx(x,y)]!=0){
					game[coordtoidx(x,y-1)] = game[coordtoidx(x,y)];
					game[coordtoidx(x,y)] = 0;
					shifted =true;		
				}
			}
		}
	}
	return shifted;
}

void randomTwo(vector <int> &game){ //generates a random two in a non zero tile
	int random;
	do{
		random = rand() % 16;
	}while(game[random]!=0);
	
	game[random] = 2;

}

bool checkforspaces(const vector <int> &game){ //checks to see if there are any zeroes in the grid
	bool spaceavailable=false;
	for(int i=0;i<game.size();i++){
		if(game[i]==0){
			spaceavailable=true;
		}
	}
	return spaceavailable;
}
	
bool gameover(const vector <int> &game){ //checks to see if there are any possible moves
	bool end=true;
	for(int x=0;x<3;x++){
		for(int y=0;y<4;y++){
			if(game[coordtoidx(x,y)]==game[coordtoidx(x+1,y)]){
				end = false;
			}
		}
	}
	for(int x=0;x<4;x++){
		for(int y=0;y<3;y++){
			if(game[coordtoidx(x,y)]==game[coordtoidx(x,y+1)]){
				end = false;
			}
		}
	}
	return end;
}







