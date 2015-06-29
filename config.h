//created by Isaac Yates March 10 2015

//the order of the includes and defines in this file matter... et_drive, tophat_drive, and camera use functions in the driveTrain header.

/*when writing functions, first part of function name should be header, and parameters should go in this order: 
	(port, velocity, delta_x, delta_theta, shut_down_time) 

	ex. driveTrain_move_mm(int velocity, int millimeters);
	OR
	ex. servo_spin_angle(int velocity, int angle, int shut_down_in);
*/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define PI 3.14159265359

#include "servo.h"
#include "motor.h"
#include "et.h"

#include "create/create_config.h"
#include "create/create_drive.h"
#include "create/create_sensor.h"

#include "driveTrain.h"
#include "et_drive.h"
#include "tophat_drive.h"
#include "camera.h"

//#include "create_drive.h"



#endif


//Happy coding    ;)
