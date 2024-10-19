#include <vector>
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

std::vector<std::vector<bool>> parseinput(std::string verb, std::string noun, std::vector<std::vector<bool>> mainArr) {
    
    if (verb == "look") {
        look(noun, object);
    }
    else if (verb == "get") {
        if (condition) {
        
        } 
        else {
            std::cout << "there is nothing to pick up" << std::endl;
        }
    }
    else if (verb == "drop") {
        if (condition) {
        
        }
        else {
            std::cout << "you have nothing to drop" << std::endl;
        }
    }
    else if (verb == "inventory") {
        
    }
    else if (verb == "go") {
        
    }
    else {
        std::cout << "you can't do that" << std::endl;
    }
    return mainArr;
}

int main() {
    std::vector<std::vector<bool>> mainArr = {
        { false, true, false },
        { true, false, false },
        { false, true, false },
        { false, false, true },
    };
    do {
        std::cout << "> ";
        std::string action;
        getline(std::cin, action);
        std::string verb = action.substr(0, action.find(' '));
        std::string noun = action.substr(action.rfind(' ')+1);

        if (verb == "quit") {
            break;
        } else {
            mainArr = parseinput(verb, noun, mainArr);
        }
    }
    while (std::cin);
}

