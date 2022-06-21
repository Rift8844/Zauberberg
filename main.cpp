
#define VERSION "0.0.1"

#include <iostream>
#include "game.hpp"

#include <fstream>

void genData();

int main() {

	std::cout << "Zauberberg - Rift84\n" << 
	"Version " << VERSION << std::endl;

	std::ofstream dataOut("dat.txt");
	dataOut << "Test";
	
	Game game;
}




void genData() {

	//This is gonna be a shitshow by the next commit
	std::array<std::pair<std::string, std::vector<std::string>>, 6> continents {{
		{"North America", { 	

			"Alaska", 				//0 0
			"Northwest Territory", 	//0 1
			"Greenland",				//0 2
			"Alberta",				//0 3
			"Ontario",				//0 4
			"Quebec",					//0 5
			"Western United States",	//0 6
			"Eastern United States",	//0 7
			"Central America"			//0 8
		}},

		{"South America", {		
			"Venezuala",				//1 0
			"Peru",					//1 1			
			"Brazil",					//1 2
			"Argentina"				//1 3
		}},

		{"Europe", {			
			"Iceland",				//2 0
			"Scandanavia",			//2 1
			"Ukraine",				//2 2
			"Great Britain",			//2 3		
			"Northern Europe",		//2 4
			"Western Europe",			//2 5
			"Southern Europe"			//2 6
		}},

		{"Africa", {			
			"Egypt",					//3 0
			"North Africa",			//3 1
			"East Africa",			//3 2
			"Congo",					//3 3
			"South Africa",			//3 4
			"Madagasgar"				//3 5
		}},

		{"Asia", {
			"Ural",					//4 0
			"Siberia",				//4 1
			"Yaktusk",				//4 2
			"Kamchatka",				//4 3
			"Irkutsk",				//4 4
			"Mongolia",				//4 5
			"Japan",					//4 6
			"Afghanistam",			//4 7
			"China",					//4 8
			"Middle East",			//4 9
			"India",					//4 10
			"Siam",					//4 11
		}},

		{"Australia", {
			"Indonesia",				//5 0
			"New Guinea",				//5 1
			"Western Australia",		//5 2
			"Eastern Australia",		//5 3
		}}
	}};

	//If you're thinking "this is unbearably messy",
	//that's because it was never meant to be readable lmao

	//Good luck reading this; you'll need it!
	std::array<std::vector<std::vector<std::pair<unsigned, unsigned>>>, 6> data {{

		//North America
		{
			//0 0
			{
				{0, 2},
				{0, 4},
				{4, 3}
			},
			//0 1
			{
				{0, 3},
				{0, 2}
			},
			//0 2
			{
				{0, 4},
				{0, 5},
				{2, 0}
			},
			//0 3
			{
				{0, 4},
				{0, 6},
				{0, 7}
			},
			//0 4
			{
				{0, 5},
				{0, 6},
				{0, 7}
			},
			//0 5
			{
				{0, 6},
				{0, 7}
			},
			//0 6
			{
				{0, 7},
				{0, 8}
			},
			//0 7
			{
				{0, 8},
				{1, 0}
			},
			//0 8
			{}
		},

		//South America
		{
			//1 0
			{
				{0, 8},
				{1, 1},
				{1, 2}
			},
			//1 1
			{
				{1, 2},
				{1, 3},
			},
			//1 2
			{
				{3, 1},
				{1, 3}
			},
			//1 3
			{}
		},

		//Europe
		{
			//2 0
			{
				{2, 1},
				{2, 3}
			},
			//2 1
			{
				{2, 2},
				{2, 3},
				{2, 4}	
			},
			//2 2
			{
				{2, 4},
				{2, 6},
				{4, 0},
				{4, 7},
				{4, 9}
			},
			//2 3
			{
				{2, 4},
				{2, 5}
			},
			//2 4
			{
				{2, 5},
				{2, 6}
			},
			//2 5
			{
				{2, 6},
				{3, 0}
			},
			//2 6
			{
				{3, 0},
				{3, 1},
				{4, 9},
			}
		},

		//Africa
		{	
			//3 0
			{
				{3, 1}
			},
			//3 1
			{
				{4, 9},
				{3, 2}
			},
			//3 2
			{
				{4, 9},
				{3, 3},
				{3, 4},
				{3, 5}
			},
			//3 3
			{
				{3, 4},
				{3, 5}
			},
			//3 4
			{
				{3, 5}
			},
			//3 5
			{}
		},

		//Asia
		{
			//4 0
			{
				{4, 1},
				{4, 7},
				{4, 8}
			},
			//4 1
			{
				{4, 2},
				{4, 4},
				{4, 5},
				{4, 8}
			},
			//4 2
			{
				{4, 4},
				{4, 3}
			},
			//4 3
			{
				{4, 4},
				{4, 5},
				{4, 6}
			},
			//4 4
			{
				{4, 5}
			},
			//4 5
			{
				{4, 6},
				{4, 8}
			},
			//4 6
			{},
			//4 7
			{
				{4, 9},
				{4, 10},
				{4, 8}
			},
			//4 8
			{
				{4, 10},
				{4, 11}
			},
			//4 9
			{
				{4, 10}
			},
			//4 10
			{
				{4, 11}
			},
			//4 11
			{
				{5, 0}
			},
		},

		//Australia
		{
			//5 0
			{
				{5, 1},
				{5, 2}
			},
			//5 1
			{
				{5, 2},
				{5, 3}
			},
			//5 2
			{
				{5, 3}
			},
			//5 3
			{}
		}
	}};


	
	//Unpack the values
	for (unsigned cont = data.size(); cont >= 0; cont--) {
		for (unsigned terr = data.size(); terr >= 0; terr--) {
			for (auto nbCord : data[cont][terr]) {
				//continents.at(nbCord.first).at(nbCord.second).push_back(data.at(cont).at(terr));
				data.at(cont).at(terr).push_back(continents.at(nbCord.first).second.at(nbCord.second));
			}
		}
	}
	
}