#include"Sensor.hpp" // because I am implementing Sensor.hpp

#include<iostream>
#include<time.h>
#include<unistd.h>
#include<fstream>
#include<cstdlib>
#include <iomanip> // to control precision

using namespace std;

void Sensor::setSampleTime(unsigned int S){
	sampleTime = S;
}
unsigned int Sensor::getSampleTime(){
	return sampleTime;
}
	
void Sensor::setPrecisionBits(unsigned int P){
	precisionBits = P;
}

unsigned int Sensor::getPrecisionBits(){
	return precisionBits;
}

void Sensor::initSensor(){
	cout << "Sensor " << name << " is initialising:" << endl;
	float progress = 0.0;
	while (progress <= 1.0) {
		int barWidth = 70;

		cout << "[";
	    	int pos = barWidth * progress;
	    	for (int i = 0; i < barWidth; ++i) {
	        	if (i < pos) std::cout << "=";
	        	else if (i == pos) std::cout << ">";
	        	else std::cout << " ";
			usleep(50);
	    	}
	    	cout << "] " << (int(progress * 100.0) == 99 ? 100 : int(progress * 100.0)) << " %\r";
	    	cout.flush();
	
	    progress += 0.01; // for progress demonstration only
	}
	string filename = "sensor" + name + ".dat";
	sensorFile.open(filename.c_str(), ios::app); /* Data gets appended here -- so make sure you clear your file before you start to set up experiments */
	cout << endl;

	if(!sensorFile.good()){
		cerr << "Error opening sensor recording file" << endl;
		exit(EXIT_FAILURE);
	}
}

void Sensor::showInfo(){
	cout << "Sensor " << name << " has sampling time: " << sampleTime << ", Floating precision: " << precisionBits << endl;
}

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}


void Sensor::generateSamples(unsigned int totalSamples){
	double prev_sample, correlation;
	srand(time(NULL));

	if(sampleTime <= 10)
		correlation = 0.9;
	else if(sampleTime <= 50)
		correlation = 0.8;
	else if(sampleTime <= 100)
		correlation = 0.7;
	else if(sampleTime <= 200)
		correlation = 0.6;
	else if(sampleTime <= 300)
		correlation = 0.5;
	else if(sampleTime <= 400)
		correlation = 0.4;
	else if(sampleTime <= 500)
		correlation = 0.3;
	else if(sampleTime <= 600)
		correlation = 0.25;
	else if(sampleTime <= 700)
		correlation = 0.2;
	else if(sampleTime <= 800)
		correlation = 0.15;
	else if(sampleTime <= 900)
		correlation = 0.1;
	else
		correlation = 0;

	unsigned int countSamples;

	cout <<  "Generating simulated samples....." << endl;
	
	for(countSamples = 0; countSamples < totalSamples; countSamples++){
		curSample.time_stamp = currentDateTime();
		if(countSamples == 0)
			curSample.sampleValue = ((double)(rand() % 6200000)/100000.00);
		else	
			curSample.sampleValue = (correlation * prev_sample) + (1-correlation) * ((double)(rand() % 6200000)/100000.00);

		sensorFile << curSample.time_stamp;
		sensorFile << fixed;
		sensorFile << "\t" << std::setprecision(precisionBits) << "\t" << curSample.sampleValue << "\t" << sampleTime << endl;

		usleep(sampleTime*1000);

		prev_sample = curSample.sampleValue;
	}
}

Sensor::Sensor(const char *name): name(name){
	sampleTime = 100;
	precisionBits = 2;
	initSensor();
}

Sensor::Sensor(const char *name, unsigned int S, unsigned int B): name(name), sampleTime(S), precisionBits(B){
	initSensor();
}

Sensor::~Sensor(){
	if(sensorFile.is_open())	
		sensorFile.close();
}

