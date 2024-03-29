
#include "game.hpp"
#include "command.hpp"
#include "player.hpp"
#include "card.hpp"

Territory* terrFromStr(Game& game, std::string const& name);

std::unique_ptr<Command> User::getCommand(Game& game) {

	endTurn = false;

	std::cout << "\n";

	if (commandStatus != CmdStatus::Success) {
		std::cout << "The previous command yielded" << 
			" an error; try again." << std::endl;
		commandStatus = CmdStatus::Success;
	}

	switch (game.getTurnState()) {

		case (TurnPhase::PlacingArmies): {
			return promptPlaceArmies(game);
		}

		case (TurnPhase::FreeMove): {
			return promptFreeMove(game);
		}

		case (TurnPhase::AttackInit): {
			return promptAttack(game);
		}

		case (TurnPhase::DefendInit): {
			return promptDefend(game);
		}

		case (TurnPhase::VictoryArmyMove): {
			return promptVictoryMove(game);
		}

		case (TurnPhase::PlayCards): {
			return promptPlayCards(game);
		}

		default: {
			throw std::exception();
		}
	}
}


std::unique_ptr<Command> User::promptPlaceArmies(Game& game) {
	std::cout << name << "'s turn:\n" <<
	"Where would you like to place your armies?" << std::endl;

	std::string terrName;
	std::cin >> terrName;

	std::cout << "How many armies would you like to place?" 
		"\t(" << armies << " armies left)" << std::endl;

	unsigned numArmies;
	std::cin >> numArmies;

	Territory& terr = *terrFromStr(game, terrName);

	return std::unique_ptr<Command>(new PlaceArmy(*this, terr, numArmies));
}


std::unique_ptr<Command> User::promptFreeMove(Game& game) {
	std::cout << "\nWould you like to use a free move? (y/n)" <<
		std::endl;

	char choice;
	std::cin >> choice;

	if (choice == 'n') {
		return std::unique_ptr<Command>(new EndTurn(*this));

	} else if (choice != 'y') {
		commandStatus = CmdStatus::IOError;

		return getCommand(game);
	}

	std::cout << "\nWhat territory would you like to " <<
		"move armies from?" << std::endl;

	std::string origin;
	std::cin >> origin;

	std::cout << "\nWhat territory do you want " <<
		"to move them to?" << std::endl;

	std::string dest;
	std::cin >> dest;

	std::cout << "\nHow many armies do you want " <<
		"to move?" << std::endl;

	unsigned numArmies;
	std::cin >> numArmies;


	Territory* originPtr = terrFromStr(game, origin);
	Territory* destPtr = terrFromStr(game, dest);


	return std::unique_ptr<Command>(new FreeMove(*this, *originPtr, *destPtr, numArmies));
}

std::unique_ptr<Command> User::promptAttack(Game& game) {
	std::cout << "Would you like attack? (y/n)" <<
		std::endl;

	char choice;
	std::cin >> choice;

	if (choice == 'n') {
		return std::unique_ptr<Command>(new EndTurn(*this));

	} else if (choice != 'y') {
		commandStatus = CmdStatus::IOError;

		return getCommand(game);
	}

	std::cout << "\nWhat territory would you like to " <<
		"attack from?" << std::endl;

	std::string origin;
	std::cin >> origin;

	std::cout << "\nWhat territory do you want to attack?"
		 << std::endl;

	std::string target;
	std::cin >> target;

	std::cout << "\nHow many die would you like to " <<
		"attack with?" << std::endl;

	unsigned numDie;
	std::cin >> numDie;


	Territory* originPtr = terrFromStr(game, origin);
	Territory* targetPtr = terrFromStr(game, target);

	return std::unique_ptr<Command>(new AttackInit(*this, *originPtr, *targetPtr, numDie));
}


std::unique_ptr<Command> User::promptDefend(Game& game) {

	std::cout << "\nHow many die would you like to " <<
	"defend with?" << std::endl;

	unsigned numDie;
	std::cin >> numDie;

	return std::unique_ptr<Command>(new DefendInit(*this, numDie));
}


std::unique_ptr<Command> User::promptVictoryMove(Game& game) {
	std::cout << "\nVICTORY! How many armies " <<
		"do you want to move from " << game.attackState.origin->name <<
		" to " << game.attackState.target->name << 
		" (" << game.attackState.attackDie << " - " <<
		game.attackState.origin->armies - 1 << ")?" << std ::endl;

	unsigned numArmies;
	std::cin >> numArmies;

	return std::unique_ptr<Command>(new VictoryArmyMove(*this, numArmies));
};


Territory* User::terrFromStr(Game& game, std::string const& name) {
	//Post C++20
	/*
	Territory* terr = std::ranges::find(terrs, terrName,
		{}, &Territory::name);
	*/

	//Pre C++20
    Territory* terr = &(*std::find_if(
    	game.getTerritories().begin(), 
    	game.getTerritories().end(), 

        [&name](Territory& currentTerr) {
        	return currentTerr.name == name; 
        }));

    if (terr == &(*game.getTerritories().end()))
    	throw std::exception();

    return terr;
}

std::unique_ptr<Command> User::promptPlayCards(Game& game) {
	
	std::cout << "Would you like to play any cards?" <<
		" You must play cards if you have 5 cards. (y/n)" <<
		"\nYour cards:\n";

	std::string out;

	if (cards.size() > 0) {
		for (Card card : cards) {
			out += cardToStr(card) + ",\n";
		}
	} else {
		out = "(None)";
	}

	//Remove last comma and newline
	out.pop_back();
	out.pop_back();

	out += "\n";

	std::cout << out << std::endl;

	std::string in;

	std::cin >> in;

	if (in == "n") {
		return std::unique_ptr<Command>(new EndTurn(*this));
	} else if (in != "y") {
		commandStatus = CmdStatus::IOError;

		return getCommand(game);
	}

	std::cout << "Which cards would you like to play?"
		<< std::endl;

	std::array<std::string, 3> cardNames;

	for (std::string& name : cardNames) {
		std::cin >> name;
	}

	return std::unique_ptr<Command>(new PlayCards(*this, cardNames));
}

