#include <iostream>
#include <string>
#include <strings.h>
#include <vector>

class object {
public:
    std::string name;
    std::string info;
    object(std::string name, std::string info): name(name), info(info) {}
};

class location {
public:
    std::string look;
    std::string go;
    std::vector<object> objects;
    
    //constructor
    location(std::string look, std::string go) :
        look(look), go(go) {}

    //methods
    void lookMethod() {
        std::cout << look << std::endl;
        for (object obj : objects)
            std::cout << "on the ground is a " << obj.name << std::endl;
    }
    void goMethod() {
        std::cout << go;
    }
};

int checkForObj(std::string noun, std::vector<location> room, int current) {
    std::vector<object> vec = room[current].objects;
    for (int x=0; x!=vec.size(); x++) {
        if (vec[x].name == noun) {return x;}
    }
    return -1;
}

void coutObj(std::string noun, std::vector<location> room, int current) {
    std::vector<object> vec = room[current].objects;
    for (object obj : vec) {
        if (obj.name == noun) {
            std::cout << obj.info << std::endl;
        }
    }
}

int checkInv(std::string noun, std::vector<object> inv) {
    for (int x=0; x!=inv.size(); x++) {
        if (inv[x].name == noun) { return x; }
    }
    return -1;
}

void get(std::vector<location>& rooms, std::vector<object>& inv, int current, int index) {
    object buffer = rooms[current].objects[index];
    rooms[current].objects.erase(rooms[current].objects.begin() + index);
    inv.push_back(buffer);
}

void drop(std::vector<location>& rooms, std::vector<object>& inv, int current, int index) {
    object buffer = inv[index];
    inv.erase(inv.begin() + index);
    rooms[current].objects.push_back(buffer);
}

void parseinput(std::string verb, std::string noun, std::vector<location>& rooms, std::vector<object>& inventory, int& current) {
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
        if (index != 0) {
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
    }
    else if (verb == "go") {
    }
    else {
    }
}

int main() {
    object key("key", "KEYINFO");
    object sword("sword", "SWORDINFO");
    object telescope("telescope", "TELESCOPE");
    location deck("LOOK", "GO");
    location brig("LOOK", "GO");
    location crow("LOOK", "GO");
    deck.objects = { sword };
    brig.objects = { key };
    crow.objects = { telescope };

    std::vector<location> rooms = { deck, brig, crow };
    std::vector<object> inventory;
    int currentRoom = 1;

    std::cout << "this is the deck, there's cannons, the helm, and the mast \nthere's a sword on the ground" << std::endl;

    do {
        std::cout << "> ";
        std::string action;
        getline(std::cin, action);
        std::string verb = action.substr(0, action.find(' '));
        std::string noun = action.substr(action.rfind(' ')+1);

        if (verb == "quit") {
            break;
        } else {
            parseinput(verb, noun, rooms, inventory, currentRoom);
        }
    }
    while (std::cin);
}
