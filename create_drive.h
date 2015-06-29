

/*

ATTENTION PROGRAMMER:

Although this header is still included in the lib, we are using the create lib cut and pasted from opencode, as it is still pretty good and I had trouble imporving upon it in a newer version.

Opencode's createlib is good because it bypasses the communication time between the kovan and the create and does its commands on board the create.

If you are curious as to how it works, look at the code, or try to find one of the many papers written by Jeremy Rand about create commands or talk to one of the members from the 2012 - 2013 years, such as Garret Sickles or Kevin Catrone... I think I spelled Catrone wrong.

You can also contact me (Isaac Yates), but I will not garentee that I can give a good explanation of the code.

*/

#ifndef __CREATE_DRIVE_H__
#define __CREATE_DRIVE_H__

#define DRIVE_TRAIN_DIA_MM 264

//returns charge as a percentage. This allows us to compensate for bad charge in other functions. Not implemented yet.
float create_get_charge()
{
	return (float)get_create_battery_charge()/(float)get_create_battery_capacity()*100.0;
}

void create_drive_segment(int speed, int distance_mm)
{
	set_create_distance(0);
	if(distance_mm > 0)
		create_drive_direct(speed, speed);//as of 2015, drive_direct is in millimeters per second
	
	else if(distance_mm < 0)
		create_drive_direct(-1*speed, -1*speed);
	
	while(abs(get_create_distance()) < distance_mm) msleep(1);
	
	/*msleep(abs(distance_mm)*1000/speed);//haha abs() is kinda nessecary. Almost a headache.*/
	create_stop();
}


//positive speed spins the create clockwise.
void create_spin(int velocity)
{
	create_drive_direct(velocity, -1*velocity);
}


//positive angle spins the create clockwise
void create_spin_angle(int speed, int angle)
{
	set_create_total_angle(0);
	if(angle > 0)
	{
		create_spin(speed);
	}
	if(angle < 0)
	{
		create_spin(-1*speed);
	}
	int beginTime = systime();
	while(abs(get_create_total_angle()) < abs(angle)) msleep(1);
	int totTime = systime() - beginTime;
	
	printf("\nms per current angle: %d", totTime);
	printf("\ncurrent angle: %d", get_create_total_angle());
	create_stop();
}

//waits for the create button sensor to be touched
void create_wait_for_bump(int velocity)
{
	while(get_create_lbump(0)!=1 || get_create_rbump(0)!=1)
	{
		if(get_create_lbump(0)==0 && get_create_rbump(0)==1)
		{
			create_drive(velocity,0);
			msleep(100);
		}
		if(get_create_lbump(0)==1 && get_create_rbump(0)==0)
		{
			create_drive(0,velocity);
			msleep(100);
		}
		if(get_create_lbump(0)!=1&& get_create_rbump(0)!=1)
		{
			create_drive_straight(velocity);
			msleep(100);
		}
	}
}


#endif
