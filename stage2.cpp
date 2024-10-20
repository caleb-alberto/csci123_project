#include <vector>
#include <iostream>
#include <string>

int convToInt(std::string noun) {
    if (noun == "key") {
        return 1;
    }
    else if (noun == "sword") {
        return 2;
    }
    else {
        return 3;
    }
}

void lookWithObjects(int locIndex, std::vector<std::vector<bool> > mainArr) {
    if (mainArr[1][locIndex] == true) {
        std::cout << "there's a key on the ground " << std::endl;
    }
    if (mainArr[2][locIndex] == true) {
        std::cout << "there's a sword on the ground " << std::endl;
    }
    if (mainArr[3][locIndex] == true) {
        std::cout << "there's a telescope on the ground " << std::endl;
    }
}

void look(std::string noun, int locIndex, std::vector<std::vector<bool> > mainArr) {
    if (noun == "look") {
        if (locIndex == 0) {
            std::cout << "this is the brig, it's bared up so that prisoners can't get out " << std::endl;
            lookWithObjects(locIndex, mainArr);
        }
        else if (locIndex == 1) {
            std::cout << "this is the deck, there's cannons, the helm, and the mast " << std::endl;
            lookWithObjects(locIndex, mainArr);
        }
        else {
            std::cout << "this is the crow's nest, what surrounds you is the ocean blue " << std::endl;
            lookWithObjects(locIndex, mainArr);
        }
    }
    else if (noun == "key" && mainArr[1][locIndex] == true) {
        std::cout << "its a rusty old key, it seems to be for the brig" << std::endl;
    }
    else if (noun == "sword" && mainArr[2][locIndex] == true) {
        std::cout << "a pirate's sword, it's pretty dull and wouldn't do much damage" << std::endl;
    }
    else if (noun == "telescope" && mainArr[3][locIndex] == true) {
        std::cout << "an old telescope, it extends pretty far but is quite blurry" << std::endl;
    }
    else {
        std::cout << "you can't do that" << std::endl;
    }
}

std::vector<std::vector<bool> > get(std::string noun, int obj, int locIndex, std::vector<std::vector<bool> > mainArr) {
    if (mainArr[obj][locIndex] == true) {
        mainArr[obj][locIndex] = false;
        std::cout << "you picked up: " << noun << std::endl;
        return mainArr;
    }
    else {
        std::cout << "you can't do that" << std::endl;
        return mainArr;
    }
}

std::vector<std::vector<bool> > drop(std::string noun, int obj, std::vector<bool> inventory, int locIndex, std::vector<std::vector<bool> > mainArr) {
    if (mainArr[obj][locIndex] == false && inventory[obj-1] == true) {
        mainArr[obj][locIndex] = true;
        std::cout << "you dropped: " << noun << std::endl;
        return mainArr;
    }
    else {
        std::cout << "you can't do that" << std::endl;
        return mainArr;
    }
}

std::vector<bool> inventory(std::vector<std::vector<bool> > mainArr) {
    std::vector<bool> inventory(3, false);
    for (int i = 0; i < 3; i++) {
        if (mainArr[i+1][0] == true || mainArr[i+1][1] == true || mainArr[i+1][2] == true) {
            inventory[i] = false;
        }
        else  {
            inventory[i] = true;
        }
    }
    return inventory;
}

std::vector<std::vector<bool> > go(std::string noun, int locIndex, std::vector<std::vector<bool> > mainArr) {
    if (noun == "up" && locIndex != 2) {
        mainArr[0][locIndex] = false;
        mainArr[0][locIndex+1] = true;
        std::cout << "you went up" << std::endl;
    }
    else if (noun == "down" && locIndex != 0) {
        mainArr[0][locIndex] = false;
        mainArr[0][locIndex-1] = true;
        std::cout << "you went down" << std::endl;
    }
    else {
        std::cout << "you can't do that" << std::endl;
    }
    return mainArr;
}

std::vector<std::vector<bool> > parseinput(std::string verb, std::string noun, std::vector<std::vector<bool> > mainArr) {
    int locIndex;
    for (int i = 0; i < 3; i++) {
        if (mainArr[0][i] == true) {
            locIndex = i;
        }
    }

    if (verb == "look") {
        look(noun, locIndex, mainArr);
    }
    else if (verb == "get") {
        if (noun == "key" || noun ==  "sword" || noun == "telescope") {
            int obj = convToInt(noun);
            mainArr = get(noun, obj, locIndex, mainArr);
        } 
        else {
            std::cout << "you can't do that" << std::endl;
        }
    }
    else if (verb == "drop") {
        if (noun == "key" || noun ==  "sword" || noun == "telescope") {
            std::vector<bool> inventoryD = inventory(mainArr);
            int obj = convToInt(noun);
            mainArr = drop(noun, obj, inventoryD, locIndex, mainArr);
        }
        else {
            std::cout << "you can't do that" << std::endl;
        }
    }
    else if (verb == "inventory") {
        std::cout << "you have: " << std::endl;
        std::vector<bool> inventoryD = inventory(mainArr);
        if (inventoryD[0] == true) {
            std::cout << "key" << std::endl;
        }
        if (inventoryD[1] == true) {
            std::cout << "sword" << std::endl;
        }
        if (inventoryD[2] == true) {
            std::cout << "telescope" << std::endl;
        }
        if (inventoryD[0] == false && inventoryD[1] == false && inventoryD[2] == false) {
            std::cout << "nothing" << std::endl;
        }
    }
    else if (verb == "go") {
        mainArr = go(noun, locIndex, mainArr);
    }
    else {
        std::cout << "you can't do that" << std::endl;
    }
    return mainArr;
}

int main() {
    std::vector<std::vector<bool> > mainArr;
    std::vector<bool> loc(3, false);
    std::vector<bool> first(3, false);
    std::vector<bool> second(3, false);
    std::vector<bool> third(3, false);

    loc[1] = true;
    first[0] = true;
    second[1] = true;
    third[2] = true;
    
    mainArr.push_back(loc);
    mainArr.push_back(first);
    mainArr.push_back(second);
    mainArr.push_back(third);

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
            mainArr = parseinput(verb, noun, mainArr);
        }
    }
    while (std::cin);
}

