/* -*- c-basic-offset: 8 -*-
 * Copyright (c) 2019 National Technology & Engineering Solutions
 * of Sandia, LLC (NTESS). Under the terms of Contract DE-NA0003525 with
 * NTESS, the U.S. Government retains certain rights in this software.
 * Copyright (c) 2019,2025 Open Grid Computing, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the BSD-type
 * license below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *      Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *      Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 *      Neither the name of Sandia nor the names of any contributors may
 *      be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 *      Neither the name of Open Grid Computing nor the names of any
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *      Modified source versions must be plainly marked as such, and
 *      must not be misrepresented as being the original software.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#define _GNU_SOURCE
#include <inttypes.h>
#include <unistd.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/inotify.h>
#include <time.h>
#include <pthread.h>
#include <strings.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <ovis_json/ovis_json.h>
#include <assert.h>
#include <sched.h>
#include "ldms.h"
#include "ldmsd.h"
#include "ldmsd_plug_api.h"

ldms_msg_client_t mc;
static ovis_log_t mylog;
static char *match;

static const char *usage(ldmsd_plug_handle_t handle)
{
	return  "config name=hello_ldms_msg producer=<producer_name> instance=<instance_name>\n"
		"         [match=<match>] [component_id=<component_id>] [perm=<permissions>]\n"
                "         [uid=<user_name>] [gid=<group_name>] [job_count=<job_length>]\n"
                "         [task_count=<task_length>]\n"
		"     producer      A unique name for the host providing the data\n"
		"     instance      A unique name for the metric set\n"
		"     match         A regex to subscribe the ldms_msg_sampler to.\n"
		"                   Defaults to '.*'\n";
}

static int sample(ldmsd_plug_handle_t handle)
{
	return 0;
}

static int ldms_msg_recv_cb(ldms_msg_event_t ev, void *cb_arg)
{
	int rc = 0;
	switch (ev->type) {
	case LDMS_MSG_EVENT_RECV:
		ovis_log(mylog, OVIS_LCRITICAL, "%s\n", ev->recv.data);
	case LDMS_MSG_EVENT_CLIENT_CLOSE:
		break;
	case LDMS_MSG_EVENT_SUBSCRIBE_STATUS:
		break;
	case LDMS_MSG_EVENT_UNSUBSCRIBE_STATUS:
		if (cb_arg)
			free(cb_arg);
		break;
	}
	return rc;
}

static int config(ldmsd_plug_handle_t handle, struct attr_value_list *kwl,
		  struct attr_value_list *avl)
{
	char *value;
	int rc = 0;
	char *app_ctxt = malloc(4096);
	if (!app_ctxt)
		return ENOMEM;

	value = av_value(avl, "name");
	if (value)
		match = strdup(value);
	else
		match = strdup(".*");
	mc = ldms_msg_subscribe(match, 1, ldms_msg_recv_cb,
				app_ctxt, "ldms_msg client");

	return rc;
}

static int constructor(ldmsd_plug_handle_t handle)
{
	mylog = ldmsd_plug_log_get(handle);

        return 0;
}

static void destructor(ldmsd_plug_handle_t handle)
{
	ldms_msg_client_close(mc);
}

struct ldmsd_sampler ldmsd_plugin_interface = {
	.base = {
		.type = LDMSD_PLUGIN_SAMPLER,
		.config = config,
		.usage = usage,
		.constructor = constructor,
		.destructor = destructor,
	},
	.sample = sample
};
