/*
 * command.c
 *
 *  Created on: Oct 10, 2023
 *      Author: SkyNet
 */

#include "command.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#define CMD_BUF_SIZE 10

volatile bool cmd_recive_flg = false;

static uint8_t cmd_buf[CMD_BUF_SIZE];
static uint8_t cmd_buf_count = 0;

void command_copy_buf(uint8_t *data, uint16_t size){
	if(cmd_buf_count < sizeof(cmd_buf)){
		for(int i = 0; i < size; i++){
			cmd_buf[cmd_buf_count] = data[i];
			cmd_buf_count++;
			if(data[i] == '>'){
				cmd_buf_count = 0;
				cmd_recive_flg = true;
				return;
			}
		}
	}else
		cmd_buf_count = 0;
}

void command_parse(cmd_t* cmd){
	char op, id, var;

	sscanf((char*)cmd_buf, "<%c%c%c", &op, &id, &var);

	if(op == 'S' && id == 'M' && var == 'B')
		cmd->id = CMD_SET_MEASURING_BEGIN;
	else if(op == 'S' && id == 'M' && var == 'S')
		cmd->id = CMD_SET_MEASURING_STOP;
	else if(op == 'S' && id == 'A' && var == 'U')
		cmd->id = CMD_SET_ACTIVATOR_UP;
	else if(op == 'S' && id == 'A' && var == 'D')
		cmd->id = CMD_SET_ACTIVATOR_DOWN;
	else if(op == 'S' && id == 'S' && var == 'H')
		cmd->id = CMD_SET_SOL_HIT;
	else
		cmd->id = CMD_ERROR;
}

void command_run(cmd_t* cmd){
	char data[30];
	uint16_t data_len;

	command_parse(cmd);

	switch (cmd->id) {
		case CMD_ERROR:
			data_len = sprintf(data, "<CMD_ERROR>");
			CDC_Transmit_FS((uint8_t*)data, data_len);
			break;

		case CMD_SET_MEASURING_BEGIN:
			data_len = sprintf(data, "<CMD_SET_MEASURING_BEGIN>");
			CDC_Transmit_FS((uint8_t*)data, data_len);
			break;

		case CMD_SET_MEASURING_STOP:
			data_len = sprintf(data, "<CMD_SET_MEASURING_STOP>");
			CDC_Transmit_FS((uint8_t*)data, data_len);
			break;

		case CMD_SET_ACTIVATOR_UP:
			data_len = sprintf(data, "<CMD_SET_ACTIVATOR_UP>");
			CDC_Transmit_FS((uint8_t*)data, data_len);
			break;

		case CMD_SET_ACTIVATOR_DOWN:
			data_len = sprintf(data, "<CMD_SET_ACTIVATOR_DOWN>");
			CDC_Transmit_FS((uint8_t*)data, data_len);
			break;

		case CMD_SET_SOL_HIT:
			data_len = sprintf(data, "<CMD_SET_SOL_HIT>");
			CDC_Transmit_FS((uint8_t*)data, data_len);
			break;
	}

	cmd_recive_flg = false;
}
