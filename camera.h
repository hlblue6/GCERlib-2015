//created by Isaac Yates March 10 2015

//this header requires a call to "void describe_driveTrain(...)" before it may be used.

struct camera_scheme
{
	int channel;
	int object_count;
	int pixels_of_error;
	
	int desired_x_coordinate;
	int desired_y_coordinate;
	
}camera_data[10];//to use more camera channels, make number higher.

typedef struct camera_scheme *camera;


camera create_camera_scheme(int channel, int object_count, int pixels_of_error)
{
	camera_data[channel].channel = channel;
	camera_data[channel].object_count = object_count;
	camera_data[channel].pixels_of_error = pixels_of_error;
	
	camera_data[channel].desired_x_coordinate = 0;
	camera_data[channel].desired_y_coordinate = 0;
	
	return &camera_data[channel];
}

void camera_set_x(camera camera_properties, int x_coordinate)
{
	camera_properties->desired_x_coordinate = x_coordinate;
}

void camera_set_y(camera camera_properties, int y_coordinate)
{
	camera_properties->desired_y_coordinate = y_coordinate;
}

void camera_calibrate_position(camera camera_properties)
{
	camera_update();
	camera_properties->desired_x_coordinate = get_object_center(camera_properties->channel, camera_properties->object_count).x;
	camera_properties->desired_y_coordinate = get_object_center(camera_properties->channel, camera_properties->object_count).y;
	printf("\nnew desired positions...\nx: %d", camera_properties->desired_x_coordinate);
	printf("\n\ny: %d\n", camera_properties->desired_y_coordinate);
}

void camera_set_object_count(camera camera_properties, int object_count)
{
	camera_properties->object_count = object_count;
}

//waits for a specified square area to appear in the specified camera scheme. 1 = true, 0 = false
int camera_wait_area(camera camera_scheme, int bbox_area, int error_margin)
{
	camera_update();
	int current_area = get_object_bbox(camera_scheme->channel, camera_scheme->object_count).width * get_object_bbox(camera_scheme->channel, camera_scheme->object_count).height;
	if(current_area < bbox_area + error_margin && current_area > bbox_area - error_margin)
		return 1;
	else
		return 0;
}

//driveTrain camera functions
void camera_align_x(camera camera_properties, int x_coordinate, int velocity)
{
	camera_update();
	int current_position = get_object_center(camera_properties->channel, camera_properties->object_count).x;
	int distance_from_desired_position = abs(current_position - x_coordinate);
	while(current_position < x_coordinate - camera_properties->pixels_of_error || current_position > x_coordinate + camera_properties->pixels_of_error)
	{
		
		current_position = get_object_center(camera_properties->channel, camera_properties->object_count).x;
		distance_from_desired_position = abs(current_position - x_coordinate);
		
		if(current_position < x_coordinate)
		{
			mav(driveTrain.LEFTW->port, -1*velocity);
			mav(driveTrain.RIGHTW->port, velocity);
		}
			
		if(current_position > x_coordinate)
		{
			mav(driveTrain.LEFTW->port, velocity);
			mav(driveTrain.RIGHTW->port, -1*velocity);
		}
			
		camera_update();
		msleep(20);//im upping this in hope that the camera will have more time to update... idk if makes difference.
	}
	ao();
}

//this function does not drive straight as it could. I do not use any drift coefficients.
void camera_align_y(camera camera_properties, int y_coordinate, int velocity)
{
	camera_update();
	int current_position = get_object_center(camera_properties->channel, camera_properties->object_count).y;
	while(current_position < y_coordinate - camera_properties->pixels_of_error || current_position > y_coordinate + camera_properties->pixels_of_error)
	{

		current_position = get_object_center(camera_properties->channel, camera_properties->object_count).y;
		printf("\n\nobject center: %d", current_position);
		printf("\nupper limit: %d", y_coordinate - camera_properties->pixels_of_error);
		printf("\nlower limit: %d", y_coordinate + camera_properties->pixels_of_error);	
		printf("\npix err: %d", camera_properties->pixels_of_error);	
		if((current_position > y_coordinate - camera_properties->pixels_of_error && current_position < y_coordinate + camera_properties->pixels_of_error)|| current_position == -1)
		{
			off(driveTrain.LEFTW->port);
			off(driveTrain.RIGHTW->port);
		}
		
		if(current_position < y_coordinate - camera_properties->pixels_of_error  && current_position != -1)
		{
			mav(driveTrain.LEFTW->port, velocity);
			mav(driveTrain.RIGHTW->port, velocity);
		}
			
		if(current_position > y_coordinate + camera_properties->pixels_of_error)
		{
			mav(driveTrain.LEFTW->port, -1*velocity);
			mav(driveTrain.RIGHTW->port, -1*velocity);
		}
			
		camera_update();
		msleep(1);
	}
	ao();
}

void camera_align()
{
	
}

void camera_create_align_x(camera camera_properties, int x_coordinate, int velocity)
{
	camera_update();
	while(get_object_center(camera_properties->channel, camera_properties->object_count).x < x_coordinate - camera_properties->pixels_of_error || get_object_center(camera_properties->channel, camera_properties->object_count).x > x_coordinate + camera_properties->pixels_of_error)
	{
		camera_update();
		if(get_object_center(camera_properties->channel, camera_properties->object_count).x < x_coordinate - camera_properties->pixels_of_error)
			create_spin_b(velocity);
		
		if(get_object_center(camera_properties->channel, camera_properties->object_count).x > x_coordinate + camera_properties->pixels_of_error)
			create_spin_b(-1*velocity);
		
		msleep(10);
		printf("\nobject center: %d", get_object_center(camera_properties->channel, camera_properties->object_count).x);
		printf("\ndesired x: %d", x_coordinate);
	}
	create_stop();
}

//end of driveTrain camera functions



