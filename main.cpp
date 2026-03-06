#include <iostream>
#include <string>

using namespace std;

int main() {
    string name;

    // Ask the user for their name
    cout << "Please enter your name: ";
    getline(cin, name);  // Using getline to allow spaces in the name

    // Print hello message
    cout << "Hello " << name << "!" << std::endl;

    return 0;
}