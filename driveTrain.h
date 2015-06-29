//created by Isaac Yates March 10 2015

//because I am awesome, this lib doesnt have to use drift coefficients. Get pwned.

#ifndef __DRIVETRAIN_H__
#define __DRIVETRAIN_H__

struct driveTrain
{
	
	NARmotor LEFTW;
	NARmotor RIGHTW;
	
	int diameter;
	
}driveTrain;

//describes the driveTrain for the kovan, must call this function before using any other functions in the driveTrain, et_drive, tophat_drive, camera lib.
//for best results, when creating the motors measure the diameter to the inside edges of the wheels where they just barely touch the ground.
void describe_driveTrain(NARmotor leftw, NARmotor rightw, int diameter)
{
	driveTrain.LEFTW = leftw;
	driveTrain.RIGHTW = rightw;
	driveTrain.diameter=diameter;
}

//drives the drivetrain forward at the given velocity for a given tick amount of millimeters, 
//correcting whenever one wheel falls behind the other using the tick counter.
void driveTrain_move_mm(int velocity, float millimeters)
{
	clear_motor_position_counter(driveTrain.LEFTW->port);
	clear_motor_position_counter(driveTrain.RIGHTW->port);
	float left_mm = motor_convert_ticks_mm(driveTrain.LEFTW, get_motor_position_counter(driveTrain.LEFTW->port));
	float right_mm = motor_convert_ticks_mm(driveTrain.RIGHTW, get_motor_position_counter(driveTrain.RIGHTW->port));
	
	float leftCo = 1.0;
	float rightCo = 1.0;
	float increment = 0.009*fabs((float)velocity)/1100.0;
	
	while(left_mm < millimeters && right_mm < millimeters)
	{	
		left_mm = fabs(motor_convert_ticks_mm(driveTrain.LEFTW, get_motor_position_counter(driveTrain.LEFTW->port)));
		right_mm = fabs(motor_convert_ticks_mm(driveTrain.RIGHTW, get_motor_position_counter(driveTrain.RIGHTW->port)));
		printf("\n\n\nleft_mm: %f", fabs(motor_convert_ticks_mm(driveTrain.LEFTW, get_motor_position_counter(driveTrain.LEFTW->port))));
		printf("\nright_mm: %f", fabs(motor_convert_ticks_mm(driveTrain.RIGHTW, get_motor_position_counter(driveTrain.RIGHTW->port))));
		printf("\nleftCo: %f", leftCo);
		printf("\nrightCo: %f", rightCo);
		
		//goes straight if the wheels are caught up with one another.
		if(left_mm == right_mm)
		{
			leftCo = 1.0;
			rightCo = 1.0;
		}
		//corrects if one wheel falls behind the other.
		else if(left_mm < right_mm)
		{
			rightCo = rightCo - increment;
			leftCo = 1.0;
		}
		else if(left_mm > right_mm)
		{
			rightCo = 1.0;
			leftCo = leftCo - increment;
		}
		
		//powering or freezing motors
		if(left_mm < fabs(millimeters))
			mav(driveTrain.LEFTW->port, velocity*leftCo);
		
		if(left_mm > fabs(millimeters)){
			freeze(driveTrain.LEFTW->port);
			printf("\nLEFT FREEZE");
		}
		
		if(right_mm < fabs(millimeters))
			mav(driveTrain.RIGHTW->port, velocity*rightCo);
		
		if(right_mm > fabs(millimeters)){
			freeze(driveTrain.RIGHTW->port);
			printf("\nRIGHT FREEZE");
		}
		
		msleep(1);
	}
	ao();
}

//we were having trouble with the older versions of function after the June updates, so this one assumes 1300 ticks_cycle for each wheel
void driveTrain_spin_angle(int velocity, int angle)
{
	mrp(driveTrain.LEFTW->port, velocity, (-angle*PI*driveTrain.diameter*driveTrain.LEFTW->ticks_per_cycle)/(360*PI*driveTrain.LEFTW->diameter));
	mrp(driveTrain.RIGHTW->port, velocity, (angle*PI*driveTrain.diameter*driveTrain.RIGHTW->ticks_per_cycle)/(360*PI*driveTrain.RIGHTW->diameter));
	bmd(driveTrain.LEFTW->port);
	bmd(driveTrain.RIGHTW->port);
	off(driveTrain.LEFTW->port);
	off(driveTrain.RIGHTW->port);
}

#endif
