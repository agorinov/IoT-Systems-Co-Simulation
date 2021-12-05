#include"Sensor.hpp"
#include<iostream>

using namespace std;

/* For Sensor-Person Co-Simulation you will need to process some arguments....*/
int main(int argc, char *argv[]){
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
	}

	Sensor A("A", 1000, 2); /* TODO: The constructor parameters here should be input from the user through main arguments */
	A.showInfo();

	A.generateSamples(50); //TODO: 100 here should be replaced by the third argument you pass

	/* TODO: Declare the person objects here with different weights and ages */
	/* TODO: Read the sensed samples with timestamps and process sample information as directed in the Project info */
	/* TODO: Store analysed criticality info of the persons/samples in analysis.txt file */

	return 0;
}
