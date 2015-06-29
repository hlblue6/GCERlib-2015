//created by Isaac Yates March 10 2015

//this header requires a call to "void describe_driveTrain(...)" before it may be used.

struct tophat_data
{
	int left_port;
	int left_white;
	int left_black;
	
	int right_port;
	int right_white;
	int right_black;
	
	int left_threshold;
	int right_threshold;
	
}tophat_data;

void tophat_calibrate(int right_port, int left_port)
{
	tophat_data.right_port = right_port;
	tophat_data.left_port = left_port;
	
	while(b_button() == 1)
	{
		console_clear();
		printf("\nHey hottie. Please place me so that my tophat sensors are centered over some well lit WHITE SPACE, then PRESS A");
		while(a_button() != 1){msleep(1);}
		tophat_data.left_white = analog(tophat_data.left_port);
		tophat_data.right_white = analog(tophat_data.right_port);
		msleep(700);
		printf("\nTHANKS BABE! ;) Now, can you do the same thing, but over BLACK SPACE?");
		while(a_button() != 1){msleep(1);}
		tophat_data.left_black = analog(tophat_data.left_port);
		tophat_data.right_black = analog(tophat_data.right_port);
		tophat_data.left_threshold = (tophat_data.left_black + tophat_data.left_white) / 2;
		tophat_data.right_threshold = (tophat_data.right_black + tophat_data.right_white) / 2;
		msleep(700);
		printf("\n\nleft threshold: %d", tophat_data.left_threshold);
		printf("\nright threshold: %d", tophat_data.right_threshold);
		printf("\n\nif you are not happy with the tophat thresholds, then PRESS B TO REPEAT THE CALIBRATION. Press 'a' to continue on ;)");
		while(b_button() != 1 || a_button() != 1){msleep(1);}
	}
	msleep(700);
}

void tophat_drive_follow_left()
{
	
}

void tophat_drive_follow_right()
{
	
}

void tophat_align_black(int velocity)
{
	mav(driveTrain.LEFTW->port, velocity);
	mav(driveTrain.RIGHTW->port, velocity);
	while(analog(tophat_data.left_port) < tophat_data.left_threshold || analog(tophat_data.right_port) < tophat_data.right_threshold)
	{
		if(analog(tophat_data.left_port) > tophat_data.left_threshold)
			freeze(driveTrain.LEFTW->port);
		
		if(analog(tophat_data.right_port) > tophat_data.right_threshold)
			freeze(driveTrain.RIGHTW->port);
		
		msleep(1);
	}
	
	off(driveTrain.LEFTW->port);
	off(driveTrain.RIGHTW->port);
}

void tophat_align_white(int velocity)
{
	mav(driveTrain.LEFTW->port, velocity);
	mav(driveTrain.RIGHTW->port, velocity);
	while(analog(tophat_data.left_port) > tophat_data.left_threshold || analog(tophat_data.right_port) > tophat_data.right_threshold)
	{
		if(analog(tophat_data.left_port) < tophat_data.left_threshold)
			freeze(driveTrain.LEFTW->port);
		
		if(analog(tophat_data.right_port) < tophat_data.right_threshold)
			freeze(driveTrain.RIGHTW->port);
		
		msleep(1);
	}
	
	off(driveTrain.LEFTW->port);
	off(driveTrain.RIGHTW->port);
}
