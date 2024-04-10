#include <stdio.h> // printf
#include <stdint.h> // uint8_t
#include <fcntl.h> // open
#include <unistd.h> // read, write
#include <string.h> // memcpy, strcmp
#include <sys/ioctl.h> // ioctl
#include <linux/i2c-dev.h> // I2C_SLAVE

#include "icm.h"

#define I2C_BUS_1 "/dev/i2c-1"

#define I2C_ADDRESS_ICM 0x68

#define ICM_CONFIG							0
#define ICM_GYRO_CONFIG						1
#define ICM_TEMP_OUT						2
#define ICM_GYRO_XOUT   					3
#define ICM_GYRO_YOUT   					4
#define ICM_GYRO_ZOUT						5
#define ICM_PWR_MGMT_1						6
#define ICM_WHO_AM_I				        7
#define ICM_CMD_COUNT			  	  	  100

static int32_t i2c_fd_1;

static const uint8_t ICM_CMD_TBL[ICM_CMD_COUNT][2] = {
//	{/*	Name										*/		 reg, 	  len}
	{/*	ICM_TEMP_OUT    							*/		0x41,		2},
	{/*	ICM_GYRO_XOUT							    */		0x43,		2},
	{/*	ICM_GYRO_YOUT								*/		0x45,		2},
    {/*	ICM_GYRO_ZOUT								*/		0x47,		2},
	{/*	ICM_WHO_AM_I								*/		0x75,		1},
	{/*	ICM_CONFIG									*/		0x1A,		1},
    {/*	ICM_GYRO_CONFIG								*/		0x1B,		1},
    {/*	ICM_PWR_MGMT_1								*/		0x6B,		1},
};

int main(void)
{
	I2C_Init();
    Command();
}

void Command(void)
{
	char command[30];

	while (1)
	{
		scanf("%s", command);

        if (strcmp(command, "/ICM_Init") == 0)
		{
			ICM_Init();
		}

        else if (strcmp(command, "/ICM_GetTempOut") == 0)
		{
			ICM_GetTempOut();
		}
        else if (strcmp(command, "/ICM_GetGyroXout") == 0)
		{
			ICM_GetGyroXout();
		}
        else if (strcmp(command, "/ICM_GetGyroYout") == 0)
		{
			ICM_GetGyroYout();
		}
        else if (strcmp(command, "/ICM_GetGyroZout") == 0)
		{
			ICM_GetGyroZout();
		}
		else if (strcmp(command, "/ICM_GetWhoAmI") == 0)
		{
			ICM_GetWhoAmI();
		}
        
		else if (strcmp(command, "/ICM_SetConfig") == 0)
		{
			uint8_t Config;
			printf("Enter CONFIG : ");
            scanf("%hhd", &Config);
			ICM_SetConfig(Config);
		}
		else if (strcmp(command, "/ICM_SetGyroConfig") == 0)
		{
			uint8_t GyroConfig;
			printf("Enter GYRO_CONFIG : ");
            scanf("%hhd", &GyroConfig);
			ICM_SetGyroConfig(GyroConfig);
		}
		else if (strcmp(command, "/ICM_SetPwrMgmt1") == 0)
		{
			uint8_t PwrMgmt1;
			printf("Enter PWR_MGMT_1 : ");
            scanf("%hhd", &PwrMgmt1);
			ICM_SetPwrMgmt1(PwrMgmt1);
		}

        else if (strcmp(command, "/ICM_GetAll") == 0)
		{
			ICM_GetAll();
		}
        else if (strcmp(command, "/ICM_GetGyro") == 0)
		{
			ICM_GetGyro();
		}

		else
		{
			printf("Command Error!\n");
		}
	}
}

void ICM_Init(void)
{
    ICM_SetConfig(0);
    ICM_SetGyroConfig(0);
    ICM_SetPwrMgmt1(0);
}

void ICM_GetTempOut(void)
{
	int32_t status = HWLIB_SUCCESS;
	uint8_t cmd[2];
	memcpy(cmd, ICM_CMD_TBL[ICM_TEMP_OUT], sizeof(cmd));
	uint8_t rx_buffer[cmd[1]];

	if ((status = I2C_Read_ICM(I2C_ADDRESS_ICM, cmd[0], rx_buffer, cmd[1])) < 0)
	{
		printf("I2C Error (Error code : %d, Register : 0x%02X)\n", status, cmd[0]);
	}

	int16_t rx_output = (int16_t) ((rx_buffer[0] << 8) | rx_buffer[1]);
	float rx_convert = rx_output;
	rx_convert = (rx_convert / 326.8) + 25;

	printf("ICM - TEMP_OUT : %f\n", rx_convert);
}

void ICM_GetGyroXout(void)
{
	int32_t status = HWLIB_SUCCESS;
	uint8_t cmd[2];
	memcpy(cmd, ICM_CMD_TBL[ICM_GYRO_XOUT], sizeof(cmd));
	uint8_t rx_buffer[cmd[1]];

	if ((status = I2C_Read_ICM(I2C_ADDRESS_ICM, cmd[0], rx_buffer, cmd[1])) < 0)
	{
		printf("I2C Error (Error code : %d, Register : 0x%02X)\n", status, cmd[0]);
	}

	int16_t rx_output = (int16_t) ((rx_buffer[0] << 8) | rx_buffer[1]);
	float rx_convert = rx_output;
	rx_convert = rx_convert / 131;

	printf("ICM - GYRO_XOUT : %f\n", rx_convert);
}

void ICM_GetGyroYout(void)
{
	int32_t status = HWLIB_SUCCESS;
	uint8_t cmd[2];
	memcpy(cmd, ICM_CMD_TBL[ICM_GYRO_YOUT], sizeof(cmd));
	uint8_t rx_buffer[cmd[1]];

	if ((status = I2C_Read_ICM(I2C_ADDRESS_ICM, cmd[0], rx_buffer, cmd[1])) < 0)
	{
		printf("I2C Error (Error code : %d, Register : 0x%02X)\n", status, cmd[0]);
	}

	int16_t rx_output = (int16_t) ((rx_buffer[0] << 8) | rx_buffer[1]);
	float rx_convert = rx_output;
	rx_convert = rx_convert / 131;

	printf("ICM - GYRO_YOUT : %f\n", rx_convert);
}

void ICM_GetGyroZout(void)
{
	int32_t status = HWLIB_SUCCESS;
	uint8_t cmd[2];
	memcpy(cmd, ICM_CMD_TBL[ICM_GYRO_ZOUT], sizeof(cmd));
	uint8_t rx_buffer[cmd[1]];

	if ((status = I2C_Read_ICM(I2C_ADDRESS_ICM, cmd[0], rx_buffer, cmd[1])) < 0)
	{
		printf("I2C Error (Error code : %d, Register : 0x%02X)\n", status, cmd[0]);
	}

	int16_t rx_output = (int16_t) ((rx_buffer[0] << 8) | rx_buffer[1]);
	float rx_convert = rx_output;
	rx_convert = rx_convert / 131;

	printf("ICM - GYRO_ZOUT : %f\n", rx_convert);
}

void ICM_GetWhoAmI(void)
{
	int32_t status = HWLIB_SUCCESS;
	uint8_t cmd[2];
	memcpy(cmd, ICM_CMD_TBL[ICM_WHO_AM_I], sizeof(cmd));
	uint8_t rx_buffer[cmd[1]];

	if ((status = I2C_Read_ICM(I2C_ADDRESS_ICM, cmd[0], rx_buffer, cmd[1])) < 0)
	{
		printf("I2C Error (Error code : %d, Register : 0x%02X)\n", status, cmd[0]);
	}

	uint8_t rx_output = rx_buffer[0];

	printf("ICM - WHO_AM_I : 0x%02X\n", rx_output);
}

void ICM_SetConfig(uint8_t Config)
{
	int32_t status = HWLIB_SUCCESS;
	uint8_t cmd[2];
	memcpy(cmd, ICM_CMD_TBL[ICM_CONFIG], sizeof(cmd));
	uint8_t tx_buffer[cmd[1]];
    tx_buffer[0] = Config;

	if ((status = I2C_Write_ICM(I2C_ADDRESS_ICM, cmd[0], tx_buffer, cmd[1])) < 0)
	{
		printf("I2C Error (Error code : %d, Register : 0x%02X)\n", status, cmd[0]);
	}
}

void ICM_SetGyroConfig(uint8_t GyroConfig)
{
	int32_t status = HWLIB_SUCCESS;
	uint8_t cmd[2];
	memcpy(cmd, ICM_CMD_TBL[ICM_GYRO_CONFIG], sizeof(cmd));
	uint8_t tx_buffer[cmd[1]];
    tx_buffer[0] = GyroConfig;

	if ((status = I2C_Write_ICM(I2C_ADDRESS_ICM, cmd[0], tx_buffer, cmd[1])) < 0)
	{
		printf("I2C Error (Error code : %d, Register : 0x%02X)\n", status, cmd[0]);
	}
}

void ICM_SetPwrMgmt1(uint8_t PwrMgmt1)
{
	int32_t status = HWLIB_SUCCESS;
	uint8_t cmd[2];
	memcpy(cmd, ICM_CMD_TBL[ICM_PWR_MGMT_1], sizeof(cmd));
	uint8_t tx_buffer[cmd[1]];
    tx_buffer[0] = PwrMgmt1;

	if ((status = I2C_Write_ICM(I2C_ADDRESS_ICM, cmd[0], tx_buffer, cmd[1])) < 0)
	{
		printf("I2C Error (Error code : %d, Register : 0x%02X)\n", status, cmd[0]);
	}
}

void ICM_GetAll(void)
{
    ICM_GetTempOut();
    ICM_GetWhoAmI();
    ICM_GetGyroXout();
    ICM_GetGyroYout();
    ICM_GetGyroZout();
}

void ICM_GetGyro(void)
{
	while (1)
	{
		ICM_GetGyroXout();
		ICM_GetGyroYout();
		ICM_GetGyroZout();
		printf("\n");
		usleep(500000);
	}
}

int32_t I2C_Init(void)
{
    int32_t status = IO_I2C_SUCCESS;

	if ((i2c_fd_1 = open(I2C_BUS_1, O_RDWR)) < 0)
    {
        status |= IO_I2C_ERROR_OPEN;
    }

	return status;
}

int32_t I2C_Read_ICM(uint8_t address, uint8_t reg, void *rx_buffer, uint8_t len)
{
    uint8_t reg_buffer[2] = {reg};

	if (i2c_fd_1 < 0)
    {
        return IO_I2C_ERROR_INIT;
    }
    if (ioctl(i2c_fd_1, I2C_SLAVE, address) < 0)
    {
        return IO_I2C_ERROR_IOCTL;
    }
    if (write(i2c_fd_1, reg_buffer, 1) < 0)
    {
        return IO_I2C_ERROR_WRITE;
    }
    if (read(i2c_fd_1, rx_buffer, len) < 0)
    {
        return IO_I2C_ERROR_READ;
    }

    return IO_I2C_SUCCESS;
}

int32_t I2C_Write_ICM(uint8_t address, uint8_t reg, void *tx_buffer, uint8_t len)
{
    uint8_t reg_buffer[1+len];
    reg_buffer[0] = reg;
    memcpy(reg_buffer+1, tx_buffer, len);

	if (i2c_fd_1 < 0)
    {
        return IO_I2C_ERROR_INIT;
    }
    if (ioctl(i2c_fd_1, I2C_SLAVE, address) < 0)
    {
        return IO_I2C_ERROR_IOCTL;
    }
    if (write(i2c_fd_1, reg_buffer, 1+len) < 0)
    {
        return IO_I2C_ERROR_WRITE;
    }

    return IO_I2C_SUCCESS;
}
