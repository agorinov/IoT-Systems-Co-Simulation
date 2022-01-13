#include "Utility.hpp"
#include <regex>
#include <map>


// Display correct usage of arguments
void printUsageExample(string programName){
    cerr << "Usage: " << endl;
    cerr << programName << " --sensorMode --sampleTime <sampleTime> --precisionBits <precisionBits> --samples <numberOfSimulatedSamples>" << endl;
    cerr << "or" << endl;
    cerr << programName << " --personMode <numberOfPeople>" << endl;
}

// Process command line arguments using getopt library and validate inputs.
// Map containing arguments and corresponding values passed by reference.
void parseCommandLineOptions(int argc, char* argv[], map<string, string> &CLOpts) {

// checking parameters passed to the function
//    cout << "argc: " << argc << endl;
//    for(int argcount = 1; argcount < argc; argcount++) {
//        cout << argv[argcount] << "\t" << endl;
//    }
//    cout << "mode = " << CLOpts["mode"] << endl;
//    cout << "sampleTime = " << CLOpts["sampleTime"] << endl;
//    cout << "precisionBits = " << CLOpts["precisionBits"] << endl;
//    cout << "samples = " << CLOpts["samples"] << endl;
//    cout << "numberOfPersons = " << CLOpts["numberOfPersons"] << endl;


    if (argc < 2) {
        cerr << "Error: no arguments provided" << endl;
        printUsageExample(argv[0]);
        exit(1);
    } else {
        // Array of structs used by getopt, contains information about expected arguments
        static struct option longOptions[] = {
                {"sensorMode",    no_argument,       0, 0},
                {"personMode",    required_argument, 0, 0},
                {"sampleTime",    required_argument, 0, 0},
                {"precisionBits", required_argument, 0, 0},
                {"samples",       required_argument, 0, 0},
                {0,               0,                 0, 0}
        };

        int c;
        int digitOptind = 0;
        int optionIndex = 0;
        string argString;
        // Get command line arguments and determine if they match expected form as shown in  longOptions[]
        // If valid, stores corresponding value of each argument in map which was passed by reference
        while ((c = getopt_long(argc, argv, "", longOptions, &optionIndex)) != -1) {

            switch (c) {
                case 0: // valid option
//                    cout << "option = " << longOptions[optionIndex].name << endl;
                    argString = longOptions[optionIndex].name;
                    if(argString == "sensorMode" ){
                        CLOpts["sensorMode"] = "1";
                    }
                    if (optarg) {
//                        cout << " with arg " << optarg << endl;
                        CLOpts[argString] = optarg;
                    }
                    break;
                default:
//                    cerr << "Error: invalid command" << endl;
                    printUsageExample(argv[0]);
                    exit(1);
            }
        }

        // validating inputs
        if (CLOpts["sensorMode"].empty() and CLOpts["personMode"].empty()){
            cerr << "Error: no mode provided" << endl;
            printUsageExample(argv[0]);
            exit(1);
        }

        if (!CLOpts["sensorMode"].empty() and !CLOpts["personMode"].empty()){
            cerr << "Error: conflicting modes provided" << endl;
            printUsageExample(argv[0]);
            exit(1);
        }

        if (!CLOpts["sensorMode"].empty()){
            if (CLOpts["sampleTime"].empty() or CLOpts["precisionBits"].empty() or CLOpts["samples"].empty()){
                cerr << "Error: one or more arguments missing" << endl;
                printUsageExample(argv[0]);
            }
        }

        if (!CLOpts["personMode"].empty()){
            if (!CLOpts["sampleTime"].empty() or !CLOpts["precisionBits"].empty() or !CLOpts["samples"].empty()){
                cerr << "Error: incompatible arguments" << endl;
                printUsageExample(argv[0]);
            }
        }

        if (optind < argc) {
            cerr << "Error: Unrecognized arguments: " << endl;
            while (optind < argc) {
                cerr << argv[optind++] << endl;
            }
            exit(1);
        }

//        cout << "argc = " << argc;
//        cout << " optind = " << optind << endl;
//        cout << endl;

    }
}

void distributeSampleData(string sensorFilePath, Person p, map<string, int> &criticalCounts, map<string, int> &totalCounts){

    ifstream sensorFile(sensorFilePath);

//            cout << "sensor file path: " << sensorFilePath << endl;

    if(!sensorFile.is_open()) {
        cerr << "Sensor file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    string timeWindow;
    string timeStamp;
    float sensedData;

    while (getline(sensorFile, line)) {

        //cout << "in while loop" << endl;
        smatch m;
        regex sensRegExp(R"((^\S+)\s+(\S+))");
        if (regex_search(line, m, sensRegExp)) {

            timeStamp = m[1]; // first capturing group (entry in first column in sensor file)
            sensedData = stof(m[2]); // second capturing group (entry in second column in sensor file)

            timeWindow = p.getTimeWindow(timeStamp);
            // cout << "line number = " << lineTracker << ", " << m[1] << " corresponds to time window: " << timeWindow << endl;
            criticalCounts[timeWindow] += p.analyseSensedData(timeWindow, sensedData);
            totalCounts[timeWindow] += 1;
        }
    }

    sensorFile.close();

}

void createAnalysisReport(string analysisFilePath, Person p, map <string, int> criticalCounts, map <string, int> totalCounts){

    int personTracker = 1;

    ofstream analysisFile;
    analysisFile.open(analysisFilePath, ios_base::app);

    if(!analysisFile.is_open()) {
        cerr << "Analysis file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    analysisFile << "---------------------------------------------------------------------------------------------" << endl;
    analysisFile << "Person " << personTracker++ << " ";
    analysisFile << p.showPersonalInfo() << endl;
    analysisFile << "---------------------------------------------------------------------------------------------" << endl;

    string windowName[] = { "Night", "Morning", "Daytime", "Evening"};


    float criticalSamplesPercent;

    cout << fixed << setprecision(0);
    analysisFile << fixed << setprecision(0);

    for (const string& window : windowName) {

        int totalCount = totalCounts[window];

        if(totalCount > 0){
            int critCount = criticalCounts[window];

            criticalSamplesPercent = p.calculateCriticalSamplesPercent(critCount, totalCount);
            cout << left << setw(7) << window << right << setw(37) << criticalSamplesPercent << "% critical samples" << endl;
            analysisFile << left << setw(7) << window << right << setw(37) << criticalSamplesPercent << "% critical samples" << endl;
        } else {
            cout << setw(7) << window << setw(55) << "No samples detected" << endl;
            analysisFile << setw(7) << window << setw(55) << "No samples detected" << endl;
        }
    }

    analysisFile.close();

}