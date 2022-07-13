#include "FileHandler.h"

string selectDir() {
    string selectedDir;
    cout << "Enter Directory:";
    cin >> selectedDir;
    return selectedDir;
    //cout << "\nCurrent Directory:" << selectedDir << endl;
}

string selectFile() {
    string selectedFile;
    cout << "Enter Filename:";
    cin >> selectedFile;
    return selectedFile;
}

bool fileExists(string filename) {
    // https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
    cout << "Reading File: " + filename << endl;
    ifstream f(filename);
    return f.good();
}

void readTestFileAndRun(string selectedDir) {
    Calculator calc;
    if (selectedDir == "") {
        cout << "No Directory Selected." << endl;
        return;
    }

    cout << "Selected Directory is " + selectedDir << endl;

    fstream myFile;
    string selectedFile = selectFile();
    string fullFileLocation = selectedDir + selectedFile;
    vector<char> inputCalc;

    if (!fileExists(fullFileLocation)) {
        cout << "File Error" << endl;
        return;
    }

    try {
        char inputChar;
        ifstream inputFile(fullFileLocation);
        while (inputFile.get(inputChar)) {
            if (inputChar != '=' && !isspace(inputChar)) inputCalc.push_back(inputChar);
            if (inputChar == '=') {
                inputCalc.push_back(inputChar);
                string stringToCalc;
                for (auto& item : inputCalc) {
                    stringToCalc.push_back(item);
                }
                calc.calculate(stringToCalc);
                inputCalc.clear();
            }
        }
        inputFile.close();
    }
    catch (...) {
        cout << "Error Reading File" << endl;
        return;
    }
}