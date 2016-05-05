#include "bcm2835.h"
#include "mfi.h"
#include "server.h"
#include "stdio.h"



char buf[]= {CDataLength, 0x77,0x55};

int main(int argc, char *argv[])
{
	if(!bcm2835_init())
	{return 1;}
	bcm2835_i2c_begin();
	mfi_init(50000);


	//mfi_show_device_info();
	//mfi_reg_write(buf,sizeof(buf));

	socket_server_buildup();



	bcm2835_i2c_end();
	bcm2835_close();	
	return 0;

}