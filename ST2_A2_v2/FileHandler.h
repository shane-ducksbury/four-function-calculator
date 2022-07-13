#include <fstream>
#include <vector>
#include "Calculator.h"

using namespace std;

#pragma once
class FileHandler
{
	FileHandler();
};

string selectDir();
string selectFile();
bool fileExists(string filename);
void readTestFileAndRun(string selectedDir);
