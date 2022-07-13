#include <iostream>
#include <conio.h>
#include <string>
#include <iomanip>
#include "Calculator.h"
#include "FileHandler.h"

using namespace std;

void outputMenuOption(string menuSelectionKey, string menuText) {
    cout << menuSelectionKey + " - " + menuText << endl;
}

int main()
{
    Calculator calc;

    string input;
    string currentFile;
    string selectedDir = "";
    bool programRunning = true;
    bool invalidSelection = false;

    while (programRunning) {
        cout << "Calculator\n " << endl;

        cout << "Select an option:" << endl;
         
        // R and D combined as Memory is working
        outputMenuOption("E", "Exit");
        outputMenuOption("S", "Set Directory");
        outputMenuOption("4", "Run 4 function calculator from keyboard");
        outputMenuOption("R", "Read single test file and run");

        if (invalidSelection) {
            cout << "Not a valid selection. ";
            invalidSelection = false;
        }
        cout << "\nEnter your selection: "; cin >> input;

        system("cls");
        char selection = input[0];

        switch (selection) {
        case 'E': case 'e':
            programRunning = false;
            break;
        case 'S': case 's':
            selectedDir = selectDir();
            break;
        case '4':
            calc.calculate();
            break;
        case 'R': case 'r':
            readTestFileAndRun(selectedDir);
            break;
        default:
            invalidSelection = true;
            system("cls");
            break;
        }
    }
    return 0;
}