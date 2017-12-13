
#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <mcp3004.h>

#include "tempSensor.h"

using namespace std;

int main() {
	
	float (*fp) (int);

	fp = f;
	TempSensor ts = TempSensor(fp);
	cout << ts.getTemp();
	

}	
