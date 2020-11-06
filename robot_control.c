/*
 * RC Robot Control C library implementation
 *
 * Copyright 2020 (C) Bartosz Meglicki <meglickib@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "robot_control.h"

// Minimal Latenecy Streaming Protocol library
#include "mlsp.h"

#include <stdio.h> //fprintf
#include <stdlib.h> //malloc, free

struct rc
{
	struct mlsp *network_streamer;
};

struct rc *rc_init(const struct rc_net_config *net_config)
{
	struct rc *r;

	if( ( r = (struct rc*)malloc(sizeof(struct rc))) == NULL )
	{
		fprintf(stderr, "rc: not enough memory for rc\n");
		return NULL;
	}

	struct mlsp_config streamer_config = {net_config->ip, net_config->port};

	if( !(r->network_streamer = mlsp_init_client(&streamer_config)) )
	{
		fprintf(stderr, "rc: failed to initalize MLSP network streamer\n");
		return NULL;
	}

	return r;
}

int rc_command(struct rc *r, int16_t command, int16_t left, int16_t right)
{
	struct mlsp_frame network_frame = {0};
	struct drive_command
	{
		int16_t command;
		int16_t left;
		int16_t right;
	} __attribute__((packed));

	struct drive_command cmd = {command, left, right};

	//ignoring big endian/little endian
	network_frame.data = (uint8_t*) &cmd;
	network_frame.size = sizeof(struct drive_command);

	if(mlsp_send(r->network_streamer, &network_frame, 0) != MLSP_OK)
		fprintf(stderr, "rc: failed to send robot command\n");

	return RC_OK;
}

void rc_close(struct rc *r)
{
	if(r == NULL)
		return;

	mlsp_close(r->network_streamer);

	free(r);
}
