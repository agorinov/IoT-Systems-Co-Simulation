#include<map>
#include<string>
#include<iostream>
#include<iomanip>
#include<getopt.h> // getopt_long()
#include"Person.hpp"

using namespace std;

void printUsageExample(string programName);

void parseCommandLineOptions(int argc, char* argv[], map<string, string> &CLOpts);

void distributeSampleData(string sensorFile, Person person, map <string, int> &criticalCounts, map<string, int> &totalCounts);

void createAnalysisReport(string analysisFile, Person person, map <string, int> criticalCounts, map <string, int> totalCounts);