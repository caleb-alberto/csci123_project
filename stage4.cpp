#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <fstream>

class object {
public:
    std::string name;
    std::string info;
    object(std::string name, std::string info): name(name), info(info) {}
};

class Key : public object {
public:
    Key(): object("key", "its a rusty old key, it seems to be for the brig") {}
};

class Sword : public object {
public:
    Sword(): object("sword", "a pirate's sword, it's pretty dull and wouldn't do much damage") {}
};

class Telescope : public object {
public:
    Telescope(): object("telescope", "an old telescope, it extends pretty far but is quite blurry") {}
};

class location {
public:
    std::string look;
    std::string go;
    std::vector<object*> objects;

    //constructor
    location(std::string look, std::string go) :
        look(look), go(go), objects() {}

    //methods
    void lookMethod() {
        std::cout << look << std::endl;
        for (object* obj : objects)
            std::cout << "on the ground is a " << obj->name << std::endl;
    }
    void goMethod() {
        std::cout << go << std::endl;
    }
};

int checkForObj(std::string noun, std::vector<location> room, int current) {
    std::vector<object*> vec = room[current].objects;
    for (int x=0; x!=vec.size(); x++) {
        if (vec[x]->name == noun) {return x;}
    }
    return -1;
}

void coutObj(std::string noun, std::vector<location> room, int current) {
    std::vector<object*> vec = room[current].objects;
    for (object* obj : vec) {
        if (obj->name == noun) {
            std::cout << obj->info << std::endl;
        }
    }
}

int checkInv(std::string noun, std::vector<object*> inv) {
    for (int x=0; x!=inv.size(); x++) {
        if (inv[x]->name == noun) { return x; }
    }
    return -1;
}

void get(std::vector<location>& rooms, std::vector<object*>& inv, int current, int index) {
    object* buffer = rooms[current].objects[index];
    rooms[current].objects.erase(rooms[current].objects.begin() + index);
    inv.push_back(buffer);
}

void drop(std::vector<location>& rooms, std::vector<object*>& inv, int current, int index) {
    object* buffer = inv[index];
    inv.erase(inv.begin() + index);
    rooms[current].objects.push_back(buffer);
}

void parseinput(std::string verb, std::string noun, std::vector<location>& rooms, std::vector<object*>& inventory, int& current) {
    if (verb == "look"){
        if (noun == "look") {
            rooms[current].lookMethod();
        }
        else if (checkForObj(noun, rooms, current) != -1) {
             coutObj(noun, rooms, current);
        }
        else {
            std::cout << "you cant do that\n";
        }
    }
    else if (verb == "get") {
        int index = checkForObj(noun, rooms, current);
        if (index != -1) {
            get(rooms, inventory, current, index);
            std::cout << "you picked up: \n" << noun << std::endl;
        }
        else {
            std::cout << "you cant do that\n";
        }
    }
    else if (verb == "drop") {
        int index = checkInv(noun, inventory);
        if (index != -1) {
            drop(rooms, inventory, current, index);
            std::cout << "you dropped:\n" << noun << std::endl;
        }
    }
    else if (verb == "inventory") {
        std::cout << "you have:\n";
        if (inventory.size()!=0) {
            for (object* obj : inventory) {
                std::cout << obj->name << std::endl;
            }
        }
        else {
            std::cout << "nothing\n";
        }
    }
    else if (verb == "go") {
        if (noun == "go") {
            rooms[current].goMethod();
        }
        else {
            if (noun == "up" && current != 2) {
                current++;
                std::cout << "you went up\n";
            }
            else if (noun == "down" && current != 0) {
                current--;
                std::cout << "you went down\n";
            }
            else {
                std::cout << "you cant do that\n";
            }
        }
    }
    else {
        std::cout << "you cant do that\n";
    }
}

void save(std::vector<location> rooms, std::vector<object*> inventory) {
    std::ofstream room1("room1.txt");
    std::ofstream room2("room2.txt");
    std::ofstream room3("room3.txt");
    std::ofstream inventorytxt("inventory.txt");

    for (object* obj : rooms[0].objects)
        room1 << obj->name << std::endl;
    for (object* obj : rooms[1].objects)
        room2 << obj->name << std::endl;
    for (object* obj : rooms[2].objects)
        room3 << obj->name << std::endl;
    for (object* obj : inventory)
        inventorytxt << obj->name << std::endl;
}

void pushFromFile(std::ifstream& file, std::vector<object*> obj_vec, std::vector<object*>& gamestate_vec) {
    std::string line;
    while (std::getline(file, line)) {
        for (object* obj : obj_vec) {
            if (line == obj->name)
                gamestate_vec.push_back(obj);
        }
    }
}

void load(std::vector<location>& rooms, std::vector<object*>& inventory, std::vector<object*> gameobjects) {
    for (int i = 0; i<3; i++)
        rooms[i].objects.clear();
    inventory.clear();
    std::ifstream room1("room1.txt");
    std::ifstream room2("room2.txt");
    std::ifstream room3("room3.txt");
    std::ifstream inventorytxt("inventory.txt");

    std::string line;
    pushFromFile(room1, gameobjects, rooms[0].objects);
    pushFromFile(room2, gameobjects, rooms[1].objects);
    pushFromFile(room3, gameobjects, rooms[2].objects);
    pushFromFile(inventorytxt, gameobjects, inventory);
}

int main() {
    location deck("this is the deck, there's cannons, the helm, and the mast ", "you can go down\nyou can go up");
    location brig("this is the brig, it's bared up so that prisoners can't get out ", "you can go up");
    location crow("this is the crow's nest, what surrounds you is the ocean blue ", "you can go down");
    object* telescope = new Telescope();
    object* sword = new Sword();
    object* key = new Key();
    deck.objects.push_back(sword);
    brig.objects.push_back(key);
    crow.objects.push_back(telescope);

    std::vector<location> rooms = { brig, deck, crow };
    std::vector<object*> inventory;
    std::vector<object*> gameobjects = { sword, key, telescope };
    int currentRoom = 1;

    std::cout << "this is the deck, there's cannons, the helm, and the mast \nthere's a sword on the ground" << std::endl;

    do {
        std::cout << "> ";
        std::string action;
        getline(std::cin, action);
        std::string verb = action.substr(0, action.find(' '));
        std::string noun = action.substr(action.rfind(' ')+1);

        if (verb == "quit") {
            for (location room : rooms) {
                for (object* obj : room.objects) {
                    delete obj;
                }
            }
            for (object* obj : inventory) {
                delete obj;
            }
            break;
        }
        else if (verb == "save") {
            save(rooms, inventory);
            std::cout << "Game saved\n";
        }
        else if (verb == "load") {
            load(rooms, inventory, gameobjects);
            std::cout << "Game loaded\n";
        }
        else {
            parseinput(verb, noun, rooms, inventory, currentRoom);
        }
    }
    while (std::cin);
}
