#include"Sensor.hpp"
#include<iostream>
#include<sstream>
#include<string>
#include<getopt.h>
#include<map>

using namespace std;

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
        cerr << "Usage: " << argv[0] << " <sampleTime> <precisionBits> <numberOfSimulatedSamples>" << std::endl;
        exit(1);
    } else {
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
        while ((c = getopt_long(argc, argv, "", longOptions, &optionIndex)) != -1) {

            switch (c) {
                case 0: // valid option
                    cout << "option = " << longOptions[optionIndex].name << endl;
                    argString = longOptions[optionIndex].name;
                    if(argString == "sensorMode" ){
                        CLOpts["sensorMode"] = "1";
                    }
                    if (optarg) {
                        cout << " with arg " << optarg << endl;
                        CLOpts[argString] = optarg;
                    }
                    break;
                default:
//                    cerr << "Error: invalid command" << endl;
                    cerr << "Usage: " << argv[0] << " <sampleTime> <precisionBits> <numberOfSimulatedSamples>"
                         << std::endl;
                    exit(1);
            }
        }

        if (CLOpts["sensorMode"].empty() and CLOpts["personMode"].empty()){
            cerr << "Error: no mode provided" << endl;
            cerr << "Usage: " << argv[0] << " <sampleTime> <precisionBits> <numberOfSimulatedSamples>" << endl;
        }

        cout << "optind = " << optind << endl;

        if (optind < argc) {
            cerr << "Error: Unrecognized arguments: " << endl;
            while (optind < argc) {
                cerr << argv[optind++] << endl;
            }
            exit(1);
        }

        cout << "argc = " << argc;
        cout << " optind = " << optind;
        cout << endl;

    }

}
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

        argString = argv[argcount];


        cout << endl;
    }
    parseCommandLineOptions(argc, argv, commandLineOptions);



        cout << "sensorMode = " << commandLineOptions["sensorMode"] << endl;
        cout << "number of persons = " << commandLineOptions["personMode"] << endl;
        cout << "sampleTime = " << commandLineOptions["sampleTime"] << endl;
        cout << "precisionBits = " << commandLineOptions["precisionBits"] << endl;
        cout << "numberOfSamples = " << commandLineOptions["samples"] << endl;



    /* TODO: Process the first argument as sampleTime; second argument as precisionBits; and third argument as the number of samples to generate */
//        stringstream string_stream;
//
//        string_stream << argv[1];
//        string_stream >> sampleTime;
//
//        //Clearing the stringstream
//        string_stream.clear();
//
//        string_stream << argv[2];
//        string_stream >> precisionBits;
//
//        //Clearing the stringstream
//        string_stream.clear();
//
//        string_stream << argv[3];
//        string_stream >> numberOfSamples;


//	Sensor A("A", stoi(sampleTime), stoi(precisionBits)); /* TODO: The constructor parameters here should be input from the user through main arguments */
//	A.showInfo();
//
//	A.generateSamples(stoi(numberOfSamples)); //TODO: 100 here should be replaced by the third argument you pass

	/* TODO: Declare the person objects here with different weights and ages */
	/* TODO: Read the sensed samples with timestamps and process sample information as directed in the Project info */
	/* TODO: Store analysed criticality info of the persons/samples in analysis.txt file */

	return 0;
}

