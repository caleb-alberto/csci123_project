#include <iostream>
#include <string>

void look(std::string noun, std::string object) {
    if (noun == object) {
        std::cout << "OBJECT DESCRIPTION" << std::endl;
    }
    else if (noun == "look") {
        std::cout << "DESCRIBE THE CURRENT SETTING" << std::endl;
    }
    else {
        std::cout << "you can't do that" << std::endl;
    }
}

bool parseinput(std::string action, bool objInInventory) {
    std::string verb = action.substr(0, action.find(' '));
    std::string noun = action.substr(action.find(' ')+1);
    std::string object = "OBJECT";
    
    if (verb == "look") {
        std::cout << "string noun:" << noun << std::endl;
        look(noun, object);
    }
    else if (verb == "get" && noun == object) {
        if (objInInventory == false) {
            std::cout << "you have picked up " << object << std::endl;
            return true;
        }
        else {
            std::cout << "there is nothing to pick up" << std::endl;
        }
    }
    else if (verb == "drop" && noun == object) {
        if (objInInventory == true) {
            std::cout << "you have dropped " << object << std::endl;
            return false;
        }
        else {
            std::cout << "you have nothing to drop" << std::endl;
        }
    }
    else if (verb == "go") {
        std::cout << "you can't go that way" << std::endl;
    }
    else {
        std::cout << "you can't do that" << std::endl;
    }
}

int main() {
    std::cout << "> ";
    std::string action;
    getline(std::cin, action);
    std::string verb = action.substr(0, action.find(' '));
    bool objInInventory = false; 

    if (verb == "quit") {
        return 0;
    } else {
        objInInventory = parseinput(action, objInInventory);
        parseinput(std::string action, bool objInInventory)
    }

    do {
        std::cout << "> ";
        std::string action;
        getline(std::cin, action);
        std::string verb = action.substr(0, action.find(' '));

        if (verb == "quit") {
            break;
        } else {
            parseinput(action, objInInventory);
        }
    }
    while (std::cin);
}

