
#include "game.hpp"

Game::Game() {

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
	for (unsigned cont = 0; cont < data.size(); cont++) {
		for (unsigned terr = 0; terr < data[cont].size(); terr++) {
			for (auto nbCord : data[cont][terr]) {
				continents.at(nbCord.first).at(nbCord.second).push_back(data.at(cont).at(terr));
				data.at(cont).at(terr).push_back(continents.at(nbCord.first).at(nbCord.second));
			}
		}
	}

}
