//created by Isaac Yates April 21

#ifndef __MOTOR_H__
#define __MOTOR_H_

struct NARmotor_properties
{
	int port;
	int diameter;//in mm
	int ticks_per_cycle;
}NARmotor_data[4];//only 4 motor ports on a link

typedef struct NARmotor_properties *NARmotor;
	
NARmotor create_motor(int port, int diameter, int ticks_per_cycle)
{
	NARmotor_data[port].port = port;
	NARmotor_data[port].diameter = diameter;
	NARmotor_data[port].ticks_per_cycle = ticks_per_cycle;
	return &NARmotor_data[port];
}

float motor_convert_ticks_mm(NARmotor motorName, int ticks)
{
	return (float)(ticks*PI*motorName->diameter)/(float)(motorName->ticks_per_cycle);
}

void motor_move_mm(NARmotor motorName, float mm, int ticks_per_second)
{
	clear_motor_position_counter(motorName->port);
	float current_position = motor_convert_ticks_mm(motorName, get_motor_position_counter(motorName->port));
	while(current_position != mm)
	{
		current_position = motor_convert_ticks_mm(motorName, get_motor_position_counter(motorName->port));
		
		if(current_position < mm)
			mav(motorName->port, ticks_per_second);
		
		if(current_position > mm)
			mav(motorName->port, ticks_per_second*-1);
		
		msleep(1);
	}
	off(motorName->port);
}
void motor_move_angle(NARmotor motorName, float angle, int ticks_per_second)
{
	float circumference = motorName->diameter*PI;
	float move_distance = circumference*(angle/360.00);
	motor_move_mm(motorName, move_distance, ticks_per_second);
}
	
#endif
