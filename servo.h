//created by Isaac Yates March 10 2015

#ifndef __SERVO_H__
#define __SERVO_H__

//should be noted that the spin functions spin TO specified position; they do not add specified position to current position
//also, it is recomeded that you put the set the servo position using kipr functions before using these functions, because for some reason
//get_servo_position() will return randomly large numbers the first time it is called. idk why.

struct servo_properties
{
	int port;
	float ticks_per_millisecond;//is a float so that user can say "0.2" or "0.4" ticks per ms.
	
}servo_data[4]; // there is only 4 servo ports

typedef struct servo_properties *servo;

servo create_servo(int port, float ticks_per_millisecond)
{
	servo_data[port].port = port;
	servo_data[port].ticks_per_millisecond = ticks_per_millisecond;
	return &servo_data[port];
}


void servo_spin_ticks(servo servo_properties, int ticks)
{
	float current_position = get_servo_position(servo_properties->port);//i only get the position once for a reason, if I update it in the loop I can't use floating points numbers for tpms
	while((int)current_position < ticks || (int)current_position > ticks)
	{	
		//if the position of the servo is too high, lower the position
		if((int)current_position > ticks)
			current_position = current_position - servo_properties->ticks_per_millisecond;
		
		//if the position of the servo is too low, raise the position
		if((int)current_position < ticks)
			current_position = current_position + servo_properties->ticks_per_millisecond;
		
		//this is here to break the loop if the tpms is greater than 1.0. There is no reason to have a tpms greater than 2 as far as I can tell
		if(abs(ticks - (int)current_position) < 3)
			current_position = ticks;
		
		set_servo_position(servo_properties->port, (int)current_position);//relies on truncation to get the servo to the right position in the right time
		
		msleep(1);
	}
}

//assumes 2047 ticks per 180 degrees
void servo_spin_angle(servo servo_properties, int angle)
{
	int ticks = (angle*2047)/(180);
	servo_spin_ticks(servo_properties, ticks);
}

void servo_set_tpms(servo servo_properties, float tpms)
{
	servo_properties->ticks_per_millisecond = tpms;
}

//fun fact: if you set servo position before enabling the servo, the servo goes to that position upon enabling it.
void servo_initialize(int port0_position, int port1_position, int port2_position, int port3_position)
{
	set_servo_position(0, port0_position);
	set_servo_position(1, port1_position);
	set_servo_position(2, port2_position);
	set_servo_position(3, port3_position);
	enable_servos();
}

/*
EXAMPLE CODE

servo_intialize(0,0,0,0);

servo arm = create_servo(port#, tpms);
servo_spin_ticks(arm, 1500);
servo_set_tpms(arm, 0.5);
servo_spin_angle(arm, 75);

*/
#endif
