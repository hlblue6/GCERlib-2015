//created by Isaac Yates April 22

struct et_properties
{
	int port;
	int range_per_5mm;
}et_data[7];//only 7 ports for et to go into.

typedef struct et_properties *NARet;
	
NARet create_et(int port, int range_per_5mm)
{
	et_data[port].port = port;
	et_data[port].range_per_5mm = range_per_5mm;
	return &et_data[port];
}

float et_get_mm(NARet etName)
{
	return analog_et(etName->port)*5/etName->range_per_5mm;
}
