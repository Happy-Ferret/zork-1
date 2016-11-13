#include <iostream>
#include "room.h"
#include "exit.h"
#include "item.h"

Room::Room(const string& name, const string& description) :
	Entity(EntityType::ROOM, name, description) {}

Room::~Room() {

}

void Room::Investigate() {
	cout << name << " - ";
	cout << description << "\n";
	
	if (!contains.empty()) {
		cout << "\nHere you can find: \n";
		for (list<Entity*>::iterator it = contains.begin(); it != contains.cend(); ++it) {
			Entity* ent = *it;
			cout << "\t" << ent->name << ": ";
			cout << ent->description << "\n";
		}
	}
	
	if (!exits.empty()) {
		cout << "\nYou can see different directions from here:\n";
		for (map<string, Exit*>::const_iterator it = exits.begin(); it != exits.end(); ++it) {
			cout << "\t" << it->first << ": \t" << it->second->name << "\n";
		}
	}
}

void Room::AddExit(Exit* exit, const string& placement) {
	exits.insert(pair<string, Exit*>(placement, exit));
}

Exit* Room::GetExit(const string& direction) {
	Exit* ret = NULL;
	if (exits.find(direction) != exits.end()) {
		return exits[direction];
	}
	return ret;
}