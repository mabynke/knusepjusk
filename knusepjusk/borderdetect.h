#include <NewPing.h>
#include <NewServo.h>
#include <Pushbutton.h>
#include <PLab_ZumoMotors.h>
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1800 // 

int findBorder(int[] sensors, int num_sensors) {
	/*
	 * Tar inn verdiene fra de infrarøde sensorene i en array og antall sensorer (antall tall i arrayen).
	 * 
	 * Returnerer 0 dersom ingen kant blir funnet.
	 * Returnerer 1 dersom en kant blir funnet helt til venstre.
	 * Returnerer 3 dersom en kant blir funnet rett foran.
	 * Returnerer 5 dersom en kant blir funnet til høyre.
	 */

	bool left = sensors[0] < QTR_THRESHOLD;
	bool right = sensors[num_sensors] < QTR_THRESHOLD;
	if (left && right) return 2;
	if (left) return 1;
	if (right) return 3;
	return 0; 
}
