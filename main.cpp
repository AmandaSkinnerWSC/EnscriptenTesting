#include <iostream>
#include <string>
#include "cashRegister.h"
#include "dispenserType.h"
#include <emscripten.h>

using namespace std;

cashRegister counter;
dispenserType orange(100, 50); 
dispenserType apple(100, 65);
dispenserType mango(75, 80);
dispenserType strawberryBanana(100, 85);

int choice = 0; // keeps track of user choice

// helper functions
string showSelection() {
    string output = "*** Welcome to Shelly's Juice Shop ***\n";
    output += "To select an item, enter:\n";
    output += "1 for orange juice (50 cents)\n";
    output += "2 for apple juice (65 cents)\n";
    output += "3 for mango juice (80 cents)\n";
    output += "4 for strawberry banana juice (85 cents)\n";
    output += "9 to exit\n";
    return output;
}

string sellProduct(dispenserType& product, cashRegister& pCounter, int amount) {
    string output = "";
    int amount2;
    if (product.getNoOfItems() > 0) {
        output += "Please deposit " + to_string(product.getCost()) + " cents\n";
        if (amount < product.getCost()) {
            amount2 = product.getCost() - amount;
            amount += amount2;
            output += "Please deposit another " + to_string(amount2) + " cents\n";
        }
        if (amount >= product.getCost()) {
            pCounter.acceptAmount(amount);
            product.makeSale();
            output += "Collect your item at the bottom and enjoy.\n";
        } else {
            output += "The amount is not enough. Collect what you deposited.\n";
        }
    } else {
        output += "Sorry, this item is sold out.\n";
    }
    output += "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";
    return output;
}

// Expose this to JS
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    const char* handleCommand(const char* cmd) {
        static string output; // must be static so pointer stays valid
        string command(cmd);

        // first, handle menu selection
        if (choice == 0) {
            choice = stoi(command);
            output = showSelection();
            return output.c_str();
        }

        string response = "";
        switch (choice) {
            case 1: response = sellProduct(orange, counter, stoi(command)); break;
            case 2: response = sellProduct(apple, counter, stoi(command)); break;
            case 3: response = sellProduct(mango, counter, stoi(command)); break;
            case 4: response = sellProduct(strawberryBanana, counter, stoi(command)); break;
            default: response = "Invalid selection.\n"; break;
        }

        output = response + showSelection();

        // reset choice so next input is menu selection
        choice = 0;

        return output.c_str();
    }
}