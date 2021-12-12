#include"Sensor.hpp"
#include<iostream>
#include<sstream>
#include<string>
#include<getopt.h>

using namespace std;

/* For Sensor-Person Co-Simulation you will need to process some arguments....*/
int main(int argc, char *argv[]){
    bool sMode = false;
    bool pMode = false;
    string sampleTime, precisionBits, numberOfSamples;

	if (argc < 2) { // no arguments provided
        	cerr << "Usage: " << argv[0] << " <sampleTime> <precisionBits> <numberOfSimulatedSamples>" << std::endl;
    	}
	else{
            static struct option longOptions[] = {
                    {"sensorMode",      no_argument,        0,  0 },
                    {"personMode",      no_argument,        0,  0 },
                    {"sampleTime",    required_argument,  0,  0 },
                    {"precisionBits",    required_argument,  0,  0 },
                    {"samples",         required_argument,  0,  0 },
                    {0,                 0,                  0,  0 }
            };

            int c;
            int digitOptind = 0;
            int optionIndex = 0;
            while ((c = getopt_long(argc, argv, "", longOptions, &optionIndex)) != -1) {

                switch (c) {
                    case 0: // valid option
                        cout << "option = " << longOptions[optionIndex].name;
                        if (optarg)
                            cout << " with arg " << optarg << endl;
                        break;
                    case '?': // invalid option
                        cerr << "Usage: " << argv[0] << " <sampleTime> <precisionBits> <numberOfSimulatedSamples>" << std::endl;
                        break;

                    default:
                        printf("?? getopt returned character code 0%o ??\n", c);
                }
            }

            if (optind < argc) {
                printf("non-option ARGV-elements: ");
                while (optind < argc)
                    printf("%s ", argv[optind++]);
                printf("\n");
            }

            cout << "argc = " << argc;
            cout << " optind = " << optind;
            cout << endl;

        cout << "You passed the following arguments: ";
        for(int argcount = 1; argcount < argc; argcount++){
            cout << argv[argcount] << "\t";
            string argString;
            argString = argv[argcount];

            if (argString == "--sensorMode"){
                sMode = true;
            } else if (argString == "--personMode"){
                pMode = true;
            } else if (argString == "--sampleTime" ){
                sampleTime = argv[argcount + 1];
            } else if (argString == "--precisionBits" ){
                precisionBits = argv[argcount + 1];
            } else if (argString == "--samples" ) {
                numberOfSamples = argv[argcount + 1];
            }
		}
		cout << endl;

//        cout << "sensorMode = " << sMode << endl;
//        cout << "personMode = " << pMode << endl;
//        cout << "sampleTime = " << sampleTime << endl;
//        cout << "precisionBits = " << precisionBits << endl;
//        cout << "numberOfSamples = " << numberOfSamples << endl;


        
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
	}

//	Sensor A("A", stoi(sampleTime), stoi(precisionBits)); /* TODO: The constructor parameters here should be input from the user through main arguments */
//	A.showInfo();
//
//	A.generateSamples(stoi(numberOfSamples)); //TODO: 100 here should be replaced by the third argument you pass

	/* TODO: Declare the person objects here with different weights and ages */
	/* TODO: Read the sensed samples with timestamps and process sample information as directed in the Project info */
	/* TODO: Store analysed criticality info of the persons/samples in analysis.txt file */

	return 0;
}
