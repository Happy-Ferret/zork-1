#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "entity.h"
#include "creature.h"
#include "world.h"
#include "item.h"
#include "exit.h"

World::World() {
	//GAME Entities...


	//ROOMS

	Room* living_room = new Room("Living Room", "The living room of the house.");
	Room* bath_room = new Room("Bath Room", "This is the bath room.");
	Room* storage_room = new Room("Storage Room", "Here you can see a lot of things.");
	Room* kitchen = new Room("Kitchen", "An Old Kitchen with some dishes.");
	Room* big_room = new Room("Big Room", "A very clean room, with a big bed.");
	Room* win_room = new Room("Win!", "You win the game, you scaped the room!");

	//ITEMS

	Item* book = new Item("Book", "Description of the game.");
	Item* letter = new Item("Letter", "Welcome to the game letter.");

	living_room->AddEntity(book);
	living_room->AddEntity(letter);

	// Add rooms to the game.
	rooms.push_back(living_room);


	//EXITS

	Exit* living_to_bathroom = new Exit("A wooden door.", "", living_room, bath_room, true, true, NULL);
	Exit* living_to_win = new Exit("A very heavy door.", "", living_room, win_room, true, true, NULL);
	Exit* living_to_bigroom = new Exit("A normal door.", "", living_room, big_room, true, false, NULL);
	Exit* living_to_kitchen = new Exit("It seams like a kitchen.", "", living_room, kitchen, false, false, NULL);

	living_room->AddExit(living_to_bathroom, "west");
	living_room->AddExit(living_to_win, "north");
	living_room->AddExit(living_to_bigroom, "south");
	living_room->AddExit(living_to_kitchen, "east");

	Exit* bathroom_to_livingroom = new Exit("To Living room", "", bath_room, living_room, true, false, NULL);
	Exit* kitchen_to_livingroom = new Exit("To Living room", "", kitchen, living_room, false, false, NULL);
	Exit* bigroom_to_livingroom = new Exit("To Living room", "", big_room, living_room, true, false, NULL);

	bath_room->AddExit(bathroom_to_livingroom, "east");
	kitchen->AddExit(kitchen_to_livingroom, "west");
	big_room->AddExit(bigroom_to_livingroom, "north");

	Exit* kitchen_to_storage = new Exit("To Storage room", "", kitchen, storage_room, true, true, NULL);
	Exit* storage_to_kitchen = new Exit("To Kitchen room", "", storage_room, kitchen, true, false, NULL);

	kitchen->AddExit(kitchen_to_storage, "east");
	storage_room->AddExit(storage_to_kitchen, "west");

	//TODO: Create Keys to open doors.
	

	//PLAYER
	player = new Creature("Player", "The person who is trapped inside the house.", living_room);

}

bool World::Interaction(const string& input) {

	bool response = true;

	vector<string> tokens;
	if (!input.empty()) {
		istringstream iss(input);
		copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(tokens));
	}

	if (tokens.size() == 1) {
		if (tokens[0] == "investigate") {
			player->Investigate();
		}
		else if (tokens[0] == "hi") {
			cout << "There is nobody here, you are alone... \n";
		}
		else if (tokens[0] == "north" || tokens[0] == "east" || tokens[0] == "west" || tokens[0] == "south") {
			if (player->Move(tokens[0])) {
				player->Investigate();
			}
			else {
				cout << "There is no way in that direction.";
			}
		}
		else {
			response = false;
		}
	}
	else {
		if (tokens.size() == 3) {

		}
	}

	return response;
}

World::~World() {

}