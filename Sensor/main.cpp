#include"Sensor.hpp"
#include"Utility.hpp" // to avoid making main function busy
#include<iostream>
#include<string>
#include<map>
#include<vector> // to store person objects


using namespace std;

int main(int argc, char *argv[]){

    string sensorName = "A";
    // Directory where analysis file is stored (laptop path)
    string analysisFilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - Computer Systems and Microprocessors\\projects\\IoT Laptop\\Sensor\\Analysis.txt";
    string sensorFilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - Computer Systems and Microprocessors\\projects\\IoT Laptop\\Sensor\\sensor" + sensorName + ".dat";

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

    if (!commandLineOptions["sensorMode"].empty()) {

        //validate sensorMode arguments for negative/zero values
        if(stoi(commandLineOptions["precisionBits"]) >= 0 and
        stoi(commandLineOptions["sampleTime"]) > 0 and
        stoi(commandLineOptions["samples"]) > 0 ) {

            Sensor A(sensorName, stoi(commandLineOptions["sampleTime"]), stoi(commandLineOptions["precisionBits"]));
            A.showInfo();

            A.generateSamples(stoi(commandLineOptions["samples"]));

        } else {
            cerr << "Invalid value for precisionBits, sampleTime, or samples" << endl;
            cerr << "sampleTime and samples cannot be negative" << endl;
            cerr << "precisionBits cannot be negative or zero" << endl;
            exit(0);
        }
    }

	/* TODO: Declare the person objects here with different weights and ages */

    if (!commandLineOptions["personMode"].empty()) {

        vector<Person> People;
        int personCounter;
        for (personCounter = 0; personCounter < stoi(commandLineOptions["personMode"]); personCounter++) {
            Person person = Person();
            People.push_back(person);
        }

//        cout << "Size of People vector = " << People.size() << endl;

        for (Person p: People) {

            // Read the sensed samples with timestamps and process sample information as directed in the Project info

            // stores number of critical sensed values corresponding to each time window
            // populated by distributeSampleData()
            // used by createAnalysisReport()
            map<string, int> criticalSensedValues{
                    {"Night",   0},
                    {"Morning", 0},
                    {"Daytime", 0},
                    {"Evening", 0}
            };

            // stores number of total sensed values corresponding to each time window
            // populated by distributeSampleData()
            // used by createAnalysisReport()
            map<string, int> totalSensedValues{
                    {"Night",   0},
                    {"Morning", 0},
                    {"Daytime", 0},
                    {"Evening", 0}
            };

            distributeSampleData(sensorFilePath, p, criticalSensedValues, totalSensedValues);

            //Store analysed criticality info of the persons/samples in analysis.txt file

            createAnalysisReport(analysisFilePath, p, criticalSensedValues, totalSensedValues);

            }

    }

	return 0;
}

