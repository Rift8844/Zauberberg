
#include "game.hpp"
#include "land_dat.hpp"
#include <iostream>
#include <algorithm>
#include <map>
#include <array>
#include <vector>

Game::Game(int numPlayers) {
	//players = std::vector<Player>(numPlayers)
	if (numPlayers < 1 || 6 < numPlayers)
		throw std::exception();

	territories = genLandData();

	
	//Initialize deck
	std::fill(deck.begin(), deck.begin()+13, Card::Horsemen);
	std::fill(deck.begin()+14, deck.begin()+27, Card::Cannon);
	std::fill(deck.begin()+28, deck.begin()+41, Card::Soldier);
	deck.push_back(Card::Joker);
	deck.push_back(Card::Joker);

	std::random_shuffle(deck.begin(), deck.end());

	std::vector<Territory*> terrPtrs;
	for (Territory& terr : territories)
		terrPtrs.push_back(&terr);

	std::random_shuffle(terrPtrs.begin(), terrPtrs.end());

	for (int i = 0; i < numPlayers; i++) {
		//Will initialize a Player whose color is
		//the n'th index of enum Color
		players.push_back(Player{ static_cast<Color>(i) });
	}

	auto plr = players.begin();

	//Note: implement card land association later
	//See "The Setup" section of Risk booklet
	while (!terrPtrs.empty()) {
		Territory* terr = terrPtrs.back();
		terr->armyCount = 1;
		terr->ownerColor = plr->color;

		plr->terrs.push_back(terr);
		terrPtrs.pop_back();

		plr++;
		if (plr == players.end())
			plr = players.begin();
	}

	
};


//THIS is where the fun begins!
void Game::doTurn() {
	/*
	int armyEntitlement = std::max(static_cast<int>(players[turnNum].terrs.size() / 3), 3);
	for (int i = 0; i < armyEntitlement; i++) {
		//std::pair<int, int> input = 
	}
	*/


	//End of turn code
	/*turnColor = static_cast<Color>(static_cast<int>(turnColor) + 1);
	if (static_cast<int>(turnColor) > players.size())
		turnColor = static_cast<Color>(0);*/
}




//Just try to ignore all this code because it's garbage
//If you're affiliated with a corporation and you're looking
//through this as a part of some hiring process, PLEASE IGNORE
//IT I SWEAR I'M BETTER THAN THERE'S A REASON WHY I DID THIS
std::vector<Territory> Game::genLandData() {
	std::vector<Territory> territories;

	std::map<std::string, Continent> const contNameMap {
		{"North America", NorthAmerica},
		{"South America", SouthAmerica},
		{"Africa", Africa},
		{"Asia", Asia},
		{"Europe", Europe},
		{"Australia", Australia}
	};

	std::array<int, 6> contNumOffs {{
		0, 9, 13, 20, 26, 38
	}};



	//You'll have to read land_dat.hpp to understand this
	for (auto cont : LandData::LandNames) {

		for (std::string terrName : cont.second) {
			territories.push_back(Territory(terrName, 
				contNameMap.at(cont.first)));
		}

		//continents.push_back(Continent(cont.first, territories));
	}
	
	//Unpack the neighbor data
	for (int cont = LandData::data.size() - 1; cont >= 0; cont--) {
		for (int terr = LandData::data.at(cont).size() - 1; terr >= 0; terr--) {
			for (auto nbCord : LandData::data.at(cont).at(terr)) {

				territories.at(contNumOffs.at(cont)+terr).neighbors.push_back(&territories.at(contNumOffs.at(nbCord.first)+nbCord.second));
				territories.at(contNumOffs.at(nbCord.first)+nbCord.second).neighbors.push_back(&territories.at(contNumOffs.at(cont)+terr));
			}
		}
	}

	return territories;
}
