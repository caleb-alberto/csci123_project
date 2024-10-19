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

bool parseinput(std::string verb, std::string noun, bool objInInventory) {
    std::string object = "OBJECT";
    
    if (verb == "look") {
        look(noun, object);
    }
    else if (verb == "get" && noun == object) {
        if (objInInventory == false) {
            std::cout << "you have picked up " << object << std::endl;
            objInInventory = true;
        }
        else {
            std::cout << "there is nothing to pick up" << std::endl;
        }
    }
    else if (verb == "drop" && noun == object) {
        if (objInInventory == true) {
            std::cout << "you have dropped " << object << std::endl;
            objInInventory = false;
        }
        else {
            std::cout << "you have nothing to drop" << std::endl;
        }
    }
    else if (verb == "inventory") {
        (objInInventory == true) ? std::cout << object << std::endl : std::cout << "nothing" << std::endl;
    }
    else if (verb == "go") {
        std::cout << "you can't go that way" << std::endl;
    }
    else {
        std::cout << "you can't do that" << std::endl;
    }
    return objInInventory;
}

int main() {
    bool objInInventory = false; 

    do {
        std::cout << "> ";
        std::string action;
        getline(std::cin, action);
        std::string verb = action.substr(0, action.find(' '));
        std::string noun = action.substr(action.find(' ')+1);

        if (verb == "quit") {
            break;
        } else {
            objInInventory = parseinput(verb, noun, objInInventory);
        }
    }
    while (std::cin);
}

