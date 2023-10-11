/*
 * command.h
 *
 *  Created on: Oct 10, 2023
 *      Author: SkyNet
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#include <inttypes.h>
#include <stdbool.h>

typedef enum _cmd_id_t {
	CMD_ERROR = 0,
	CMD_SET_MEASURING_BEGIN = 1,
	CMD_SET_MEASURING_STOP = 2,
	CMD_SET_ACTIVATOR_UP = 3,
	CMD_SET_ACTIVATOR_DOWN = 4,
	CMD_SET_SOL_HIT = 5,
} cmd_id_t;

typedef struct _cmd_t
{
	cmd_id_t id;
	union
	{
		uint32_t param_i;
		float param_f;
	};
} cmd_t;

void command_run(cmd_t* cmd);
void command_copy_buf(uint8_t *data, uint16_t size);
void command_parse(cmd_t* cmd);

#endif /* INC_COMMAND_H_ */
