#ifndef SENSOR_H
#define SENSOR_H

#include<ctime>
#include<string>
#include<fstream>

struct sampleStructure{
	std::string time_stamp;
	double sampleValue;
};

class Sensor{
public:
	void setSampleTime(unsigned int);
	unsigned int getSampleTime();
	
	void setPrecisionBits(unsigned int);
	unsigned int getPrecisionBits();

	void initSensor();

	void generateSamples(unsigned int);
	void showInfo();

	Sensor(const char *name);
	Sensor(const char *name, unsigned int S, unsigned int B); 

	~Sensor();

private:
	std::ofstream sensorFile;

	std::string name;
	unsigned int sampleTime;
	unsigned int precisionBits;
	struct sampleStructure curSample;
};

#endif
