#include <emscripten/emscripten.h>
#include <iostream>
#include <string>
#include <vector>

// Game state
std::string player_name;
std::vector<std::string> inventory;

// Forward declarations
extern "C" void process_input(const char* input);
void ask_input(const char* prompt_text);
void print(const std::string& text);

// Safe terminal printing
void print(const std::string& text) {
    std::cout << text << std::endl;

    EM_ASM({
        // Create terminal if it doesn't exist
        var term = document.getElementById('terminal');
        if (!term) {
            term = document.createElement('div');
            term.id = 'terminal';
            term.style.fontFamily = 'monospace';
            term.style.whiteSpace = 'pre';
            term.style.backgroundColor = '#000';
            term.style.color = '#0f0';
            term.style.padding = '10px';
            term.style.height = '400px';
            term.style.overflowY = 'auto';
            document.body.appendChild(term);
        }
        // Append text
        term.innerHTML += UTF8ToString($0) + "<br>";
        window.scrollTo(0, document.body.scrollHeight);
    }, text.c_str());
}

// Ask user input with prompt in page
void ask_input(const char* prompt_text) {
    EM_ASM({
        // Create terminal if missing
        var term = document.getElementById('terminal');
        if (!term) {
            term = document.createElement('div');
            term.id = 'terminal';
            term.style.fontFamily = 'monospace';
            term.style.whiteSpace = 'pre';
            term.style.backgroundColor = '#000';
            term.style.color = '#0f0';
            term.style.padding = '10px';
            term.style.height = '400px';
            term.style.overflowY = 'auto';
            document.body.appendChild(term);
        }

        // Create input box if missing
        var input = document.getElementById('user_input');
        if (!input) {
            input = document.createElement('input');
            input.id = 'user_input';
            input.type = 'text';
            input.style.width = '400px';
            document.body.appendChild(input);
        }

        // Create button if missing
        var button = document.getElementById('submit_button');
        if (!button) {
            button = document.createElement('button');
            button.id = 'submit_button';
            button.innerHTML = 'Enter';
            document.body.appendChild(button);
        }

        // Set onclick to send input back to C++
        button.onclick = function() {
            var val = input.value;
            input.value = "";
            Module.ccall('process_input', 'void', ['string'], [val]);
        };

        // Show prompt in terminal
        term.innerHTML += UTF8ToString($0) + "<br>";
        window.scrollTo(0, document.body.scrollHeight);

        // Focus input for convenience
        input.focus();
    }, prompt_text);
}

// Game logic
extern "C" void process_input(const char* input) {
    std::string text(input);

    if (player_name.empty()) {
        player_name = text;
        print("Hello " + player_name + "!");
        ask_input("You see two doors: left or right? Which do you choose?");
        return;
    }

    if (text == "left") {
        print(player_name + " goes through the left door and finds a sword!");
        inventory.push_back("sword");
        ask_input("Do you pick up the sword? yes/no");
        return;
    }

    if (text == "right") {
        print(player_name + " goes through the right door and encounters a monster!");
        if (std::find(inventory.begin(), inventory.end(), "sword") != inventory.end()) {
            print("Luckily, you have a sword! You defeat the monster!");
        } else {
            print("You are unarmed and the monster defeats you. Game over.");
        }
        print("The adventure ends here. Refresh the page to play again.");
        return;
    }

    if (text == "yes" && std::find(inventory.begin(), inventory.end(), "sword") == inventory.end()) {
        inventory.push_back("sword");
        print("You picked up the sword!");
        ask_input("Now you can choose: left or right?");
        return;
    }

    if (text == "no" && std::find(inventory.begin(), inventory.end(), "sword") == inventory.end()) {
        print("You leave the sword behind.");
        ask_input("Now you can choose: left or right?");
        return;
    }

    print("I don't understand that. Try again.");
}

// Start the game
int main() {
    ask_input("Welcome adventurer! What is your name?");
    return 0;
}