#include"Sensor.hpp"
#include"Person.hpp"
#include<iostream>
#include<string>
#include<getopt.h> // getopt_long()
#include<map>
#include<vector> // to store person objects
#include<regex>
#include<iomanip>


using namespace std;

void printUsageExample(string programName);

void parseCommandLineOptions(int argc, char* argv[], map<string, string> &CLOpts);

/* For Sensor-Person Co-Simulation you will need to process some arguments....*/
int main(int argc, char *argv[]){

    // Directory where analysis file is stored (laptop path)
    string analysisFilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - Computer Systems and Microprocessors\\projects\\IoT Laptop\\Sensor\\Analysis.txt";
    string sensorFilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - Computer Systems and Microprocessors\\projects\\IoT Laptop\\Sensor\\sensorA.dat";

    // Directory where analysis file is stored (desktop path)
//    string analysisFilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - Computer Systems and Microprocessors\\projects\\IoT Desktop\\Sensor\\Analysis.txt";
//    string sensorFilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - Computer Systems and Microprocessors\\projects\\IoT Desktop\\Sensor\\sensorA.dat";



    map<string, string> commandLineOptions = {
            {"sensorMode", ""},
            {"personMode", ""},
            {"sampleTime", ""},
            {"precisionBits", ""},
            {"samples", ""},
    };

    cout << "You passed the following arguments:" << endl;
    string argString;
    for(int argcount = 1; argcount < argc; argcount++){
        cout << argv[argcount] << "\t";
    }
    cout << endl;

    parseCommandLineOptions(argc, argv, commandLineOptions);

//    cout << "sensorMode = " << commandLineOptions["sensorMode"] << endl;
//    cout << "number of persons = " << commandLineOptions["personMode"] << endl;
//    cout << "sampleTime = " << commandLineOptions["sampleTime"] << endl;
//    cout << "precisionBits = " << commandLineOptions["precisionBits"] << endl;
//    cout << "numberOfSamples = " << commandLineOptions["samples"] << endl;

    if (commandLineOptions["sensorMode"] != "") {

        //validate sensorMode arguments for negative/zero values
        if(stoi(commandLineOptions["precisionBits"]) >= 0 and
        stoi(commandLineOptions["sampleTime"]) > 0 and
        stoi(commandLineOptions["samples"]) > 0 ) {

            Sensor A("A", stoi(commandLineOptions["sampleTime"]), stoi(commandLineOptions["precisionBits"]));
            A.showInfo();

            A.generateSamples(stoi(commandLineOptions["samples"]));

        } else {
            cerr << "Invalid value for precisionBits, sampleTime, or samples" << endl;
            cerr << "sampleTime and samples cannot be negative" << endl;
            cerr << "precisionBits cannot be negative or zero" << endl;
        }
    }

	/* TODO: Declare the person objects here with different weights and ages */

    if (commandLineOptions["personMode"] != ""){

        vector<Person> People;
        int personCounter;
        for (personCounter = 0; personCounter < stoi(commandLineOptions["personMode"]); personCounter++){
            Person person = Person();
            People.push_back(person);
        }

//        cout << "Size of People vector = " << People.size() << endl;

        ofstream analysisFile;
        analysisFile.open(analysisFilePath, ios_base::app);

        if(!analysisFile.is_open()) {
            cerr << "Analysis file could not be opened -- exiting." << endl;
            exit(EXIT_FAILURE);
        }

        int personTracker = 1;

        for (Person p : People){


            analysisFile << "---------------------------------------------------------------------------------------------" << endl;
            analysisFile << "Person " << personTracker++ << " ";
            analysisFile << p.showPersonalInfo() << endl;
            analysisFile << "---------------------------------------------------------------------------------------------" << endl;

            /* TODO: Read the sensed samples with timestamps and process sample information as directed in the Project info */

            ifstream sensorFile(sensorFilePath);

//            cout << "sensor file path: " << sensorFilePath << endl;

            if(!sensorFile.is_open()) {
                cerr << "Sensor file could not be opened -- exiting." << endl;
                exit(EXIT_FAILURE);
            }

    //        int lineTracker = 0;
            string line;
            string timeWindow;
            string timeStamp;
            float sensedData;
            int result;
            map<string, int> criticalSensedValues{
                    {"Night", 0},
                    {"Morning", 0},
                    {"Daytime", 0},
                    {"Evening", 0}
            };

            map<string, int> totalSensedValues{
                    {"Night", 0},
                    {"Morning", 0},
                    {"Daytime", 0},
                    {"Evening", 0}
            };

            string windowName[] = { "Night", "Morning", "Daytime", "Evening"};

    //        map <string, int>::iterator it; // iterator for looping through map

            while (getline(sensorFile, line)) {

    //            cout << "in while loop" << endl;
                smatch m;
    //            regex sensRegExp(R"((^\d+\-\d+\-\d+\.\d+\:\d+\:\d+)\s+(\d+\.{0,1}\d+))");
                regex sensRegExp(R"((^\S+)\s+(\S+))");
                if (regex_search(line, m, sensRegExp)) {

    //                lineTracker++;
                    timeStamp = m[1]; // first capturing group (entry in first column in sensor file)
                    sensedData = stof(m[2]); // second capturing group (entry in second column in sensor file)

                    timeWindow = p.getTimeWindow(timeStamp);
    //                cout << "line number = " << lineTracker << ", " << m[1] << " corresponds to time window: " << timeWindow << endl;
                    criticalSensedValues[timeWindow] += p.analyseSensedData(timeWindow, sensedData);
                    totalSensedValues[timeWindow] += 1;
                }
            }

            /* TODO: Store analysed criticality info of the persons/samples in analysis.txt file */


            float criticalSamplesPercent;

            cout << fixed << setprecision(0);
            analysisFile << fixed << setprecision(0);

            for (const string& window : windowName) {

                int totalCount = totalSensedValues[window];

                if(totalCount > 0){
                    int critCount = criticalSensedValues[window];

                    criticalSamplesPercent = p.calculateCriticalSamplesPercent(critCount, totalCount);
                    cout << left << setw(7) << window << right << setw(37) << criticalSamplesPercent << "% critical samples" << endl;
                    analysisFile << left << setw(7) << window << right << setw(37) << criticalSamplesPercent << "% critical samples" << endl;
                } else {
                    cout << setw(7) << window << setw(55) << "No samples detected" << endl;
                    analysisFile << setw(7) << window << setw(55) << "No samples detected" << endl;
                }
            }

            sensorFile.close();

        }

        analysisFile.close();
        }



	return 0;
}

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

