#include"Sensor.hpp"
#include"Person.hpp"
#include<iostream>
#include<sstream>
#include<string>
#include<getopt.h> // getopt_long()
#include<map>
#include<vector>

using namespace std;

void printUsageExample(string programName);

void parseCommandLineOptions(int argc, char* argv[], map<string, string> &CLOpts);

/* For Sensor-Person Co-Simulation you will need to process some arguments....*/
int main(int argc, char *argv[]){
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

    parseCommandLineOptions(argc, argv, commandLineOptions);

    cout << "sensorMode = " << commandLineOptions["sensorMode"] << endl;
    cout << "number of persons = " << commandLineOptions["personMode"] << endl;
    cout << "sampleTime = " << commandLineOptions["sampleTime"] << endl;
    cout << "precisionBits = " << commandLineOptions["precisionBits"] << endl;
    cout << "numberOfSamples = " << commandLineOptions["samples"] << endl;


//	Sensor A("A", stoi(commandLineOptions["sampleTime"]), stoi(commandLineOptions["precisionBits"]));
//	A.showInfo();
//
//	A.generateSamples(stoi(commandLineOptions["samples"]));

	/* TODO: Declare the person objects here with different weights and ages */

    vector<Person> People;
    int personCounter;
    for (personCounter = 0; personCounter < stoi(commandLineOptions["personMode"]); personCounter++){
        Person person = Person();
        People.push_back(person);
    }

    cout << "Size of People vector = " << People.size() << endl;

    // Print total number of objects.
    cout << "Total people: " << Person::personCount << endl;

    for (Person p : People){
        p.showPersonalInfo();
    }

	/* TODO: Read the sensed samples with timestamps and process sample information as directed in the Project info */
	/* TODO: Store analysed criticality info of the persons/samples in analysis.txt file */

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

        cout << "optind = " << optind << endl;

        if (optind < argc) {
            cerr << "Error: Unrecognized arguments: " << endl;
            while (optind < argc) {
                cerr << argv[optind++] << endl;
            }
            exit(1);
        }

//        cout << "argc = " << argc;
//        cout << " optind = " << optind;
//        cout << endl;

    }
}

