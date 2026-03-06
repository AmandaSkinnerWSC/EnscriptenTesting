#include <emscripten/emscripten.h>
#include <iostream>
#include <string>

extern "C" void ask_user_input(const char* prompt_text);

// Utility to print to browser console AND flush output
void print(const std::string& text) {
    std::cout << text << std::endl;
    EM_ASM({
        var msg = UTF8ToString($0);
        var term = document.getElementById('terminal');
        if (!term) {
            term = document.createElement('div');
            term.id = 'terminal';
            document.body.appendChild(term);
        }
        term.innerHTML += msg + "<br>";
        window.scrollTo(0, document.body.scrollHeight);
    }, text.c_str());
}

// Game state
std::string player_name;

// Start the game
void start_game() {
    ask_user_input("Welcome adventurer! What is your name?");
}

// Called from JS after user input
extern "C" void process_input(const char* input) {
    std::string text(input);

    if (player_name.empty()) {
        player_name = text;
        print("Hello " + player_name + "!");
        ask_user_input("Do you go left or right?");
    } else {
        if (text == "left") {
            print(player_name + " goes left and finds a treasure!");
        } else if (text == "right") {
            print(player_name + " goes right and encounters a monster!");
        } else {
            print(player_name + ", I don't understand that choice.");
            ask_user_input("Do you go left or right?");
            return;
        }
        print("Game over. Refresh to play again!");
    }
}

// Ask user input via HTML prompt/input
void ask_user_input(const char* prompt_text) {
    EM_ASM({
        var existing = document.getElementById('user_input');
        if (!existing) {
            var input = document.createElement('input');
            input.id = 'user_input';
            input.type = 'text';
            input.style.width = '400px';
            document.body.appendChild(input);

            var button = document.createElement('button');
            button.innerHTML = 'Enter';
            document.body.appendChild(button);

            button.onclick = function() {
                var val = input.value;
                input.value = "";
                Module.ccall('process_input', 'void', ['string'], [val]);
            };
        }
        var term = document.getElementById('terminal');
        term.innerHTML += UTF8ToString($0) + "<br>";
    }, prompt_text);
}

int main() {
    start_game();
    return 0;
}