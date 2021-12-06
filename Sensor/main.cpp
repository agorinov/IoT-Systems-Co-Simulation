#include"Sensor.hpp"
#include<iostream>
#include<sstream>

using namespace std;

/* For Sensor-Person Co-Simulation you will need to process some arguments....*/
int main(int argc, char *argv[]){
    int sampleTime = 0, precisionBits = 0, numberOfSamples = 0;
	if (argc < 2) {
        	cerr << "Usage: " << argv[0] << " <sampleTime> <precisionBits> <numberOfSimulatedSamples>" << std::endl;
    	}
	else{
		cout << "You passed the following arguments: ";
		for(int argcount = 1; argcount < argc; argcount++){
			cout << argv[argcount] << "\t";
		}
		cout << endl;

		/* TODO: Process the first argument as sampleTime; second argument as precisionBits; and third argument as the number of samples to generate */
        stringstream string_stream;

        string_stream << argv[1];
        string_stream >> sampleTime;

        //Clearing the stringstream
        string_stream.clear();

        string_stream << argv[2];
        string_stream >> precisionBits;

        //Clearing the stringstream
        string_stream.clear();

        string_stream << argv[3];
        string_stream >> numberOfSamples;
	}

	Sensor A("A", sampleTime, precisionBits); /* TODO: The constructor parameters here should be input from the user through main arguments */
	A.showInfo();

	A.generateSamples(numberOfSamples); //TODO: 100 here should be replaced by the third argument you pass

	/* TODO: Declare the person objects here with different weights and ages */
	/* TODO: Read the sensed samples with timestamps and process sample information as directed in the Project info */
	/* TODO: Store analysed criticality info of the persons/samples in analysis.txt file */

	return 0;
}
