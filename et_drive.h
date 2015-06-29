//created by Isaac Yates March 10 2015

//this header requires a call to "void describe_driveTrain(...); before it can be used."

//head_port indicates the et at the front of the robot
//tail_port indicates the et at the back fo the robot
#ifndef __ET_DRIVE_H__
#define __ET_DRIVE_H__

struct et_drive
{
	int head_port;
	int tail_port;
	
	int head_per_5mm;
	int tail_per_5mm;
}et_drive;

void describe_et_drive(int head_port, int tail_port, int head_per_5mm, int tail_per_5mm)
{
	et_drive.head_port = head_port;
	et_drive.tail_port = tail_port;
	et_drive.head_per_5mm = head_per_5mm;
	et_drive.tail_per_5mm = tail_per_5mm;
}

void et_drive_follow(int ticks_per_second)
{
	
}

void et_drive_align(int ticks_per_second)
{
	
}
#endif
