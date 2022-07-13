#include "Calculator.h"

Calculator::Calculator(){}

void debug(double& numOne, double& numTwo) {
    cout << numOne << endl;
    cout << numTwo << endl;
}

void displayScreen(double* activeNum, bool calc = false) {
    //system("cls");

    cout << "+----------+" << endl;
    cout << "|" << setw(10);
    if (calc) cout << fixed << setprecision(2);
    cout << *activeNum;
    cout << "|" << endl;
    cout << "+----------+" << endl;
}

double sumNumbers(double& numOne, double& numTwo) {
    return numOne + numTwo;
}

double subtractNumbers(double& numOne, double& numTwo) {
    return numOne - numTwo;
}

double multiplyNumbers(double& numOne, double& numTwo) {
    return numOne * numTwo;
}

double divideNumbers(double& numOne, double& numTwo) {
    return numOne / numTwo;
}

// This needed a pointer to a pointer to keep it all working - very confusing.
void calcFromChar(char& c, char& nextChar, string& activeNumStr, double** activeNum, double& numOne, double& numTwo, char& prevOperator, map<char, double>& calcMem) {
    // Clear Display

    if (c == 'k' || c == 'K') {
        activeNumStr.clear();
        **activeNum = 0;
        displayScreen(*activeNum);
    }

    // Clear All
    if (c == 'c' || c == 'C') {
        numOne = 0;
        numTwo = 0;
        activeNumStr.clear();
        *activeNum = &numOne;
        prevOperator = NULL;
        displayScreen(*activeNum);
    }

    // Enter value to mem
    if (c == 'm' || c == 'M') {
        if (prevOperator == NULL && *activeNum == &numTwo) *activeNum = &numOne;
        char tempChar;
        bool validSelection = false;
        while (!validSelection) {
            if (nextChar != NULL) {
                tempChar = nextChar;
            }
            else {
                tempChar = _getch();
            }
            if (isdigit(tempChar)) {
                validSelection = true;
                calcMem.insert(pair<char, double>(tempChar, **activeNum));
            }
        }
    }

    // Retrieve Value
    if (c == 'r' || c == 'R') {
        char tempChar;
        bool validSelection = false;
        while (!validSelection) {
            if (nextChar != NULL) {
                tempChar = nextChar;
            }
            else {
                tempChar = _getch();
            }
            if (isdigit(tempChar)) {
                validSelection = true;
                **activeNum = calcMem.at(tempChar);
                displayScreen(*activeNum);
            }
        }
    }

    // Add value to calculator
    if (isdigit(c) || c == '.') {
        //https://www.cplusplus.com/reference/string/string/find/
        size_t numOfDots = activeNumStr.find(".");
        if (c == '.' && numOfDots != string::npos) return;
        activeNumStr.push_back(c);
        **activeNum = stod(activeNumStr);
        displayScreen(*activeNum);
    }

    // Square Root value on screen
    if (c == 's') {
        if (prevOperator == NULL && *activeNum == &numTwo) *activeNum = &numOne;
        if (**activeNum > 0) {
            **activeNum = sqrt(**activeNum);
            prevOperator = NULL;
            displayScreen(*activeNum);
        }
    }

    // Convert between negative and positive
    if (c == '!') {
        if (prevOperator == NULL && *activeNum == &numTwo) *activeNum = &numOne;
        **activeNum = -**activeNum;
        displayScreen(*activeNum);
    }

    // Operation tasks
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '\r') {
        if (!prevOperator) prevOperator = c;

        if (numTwo != 0) {
            switch (prevOperator) {
            case '+':
                numOne = sumNumbers(numOne, numTwo);
                break;
            case '-':
                numOne = subtractNumbers(numOne, numTwo);
                break;
            case '*':
                numOne = multiplyNumbers(numOne, numTwo);
                break;
            case '/':
                numOne = divideNumbers(numOne, numTwo);
                break;
            }
        }
        prevOperator = c;
        activeNumStr.clear();
        if (*activeNum == &numTwo) displayScreen(&numOne, true);
        *activeNum = &numOne;
        if (c == '=' || c == '\r') prevOperator = NULL;
        numTwo = 0;
        *activeNum = &numTwo;
    }
}

void Calculator::calculate(string exp) {
    char c = 0;

    double numOne = 0.0;
    double numTwo = 0.0;

    string activeNumStr;
    double* activeNum;

    char prevOperator = NULL;


    map<char, double> calcMem = {};

    activeNum = &numOne;
    
    while (c != ';') {

        if (exp != "") {
            for (int i = 0; i < exp.length(); i++) {
                c = exp[i];
                char nextChar;
                if (i + 1 <= exp.length()) {
                    nextChar = exp[i + 1];
                }
                else {
                    nextChar = NULL;
                }
                if (c == 'm' || c == 'r') i++;
                calcFromChar(c, nextChar, activeNumStr, &activeNum, numOne, numTwo, prevOperator, calcMem);
            }
            c = ';';
        }
        else {
            c = _getch();
            char nextChar = NULL;
            calcFromChar(c, nextChar, activeNumStr, &activeNum, numOne, numTwo, prevOperator, calcMem);
        }


    }
}