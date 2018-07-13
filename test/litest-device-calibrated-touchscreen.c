/*
 * Copyright © 2016 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "config.h"

#include "litest.h"
#include "litest-int.h"

static void litest_calibrated_touchscreen_setup(void)
{
	struct litest_device *d =
		litest_create_device(LITEST_CALIBRATED_TOUCHSCREEN);
	litest_set_current_device(d);
}

static struct input_event down[] = {
	{ .type = EV_ABS, .code = ABS_MT_SLOT, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_TRACKING_ID, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_X, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_Y, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_SYN, .code = SYN_REPORT, .value = 0 },
	{ .type = -1, .code = -1 },
};

static struct input_event move[] = {
	{ .type = EV_ABS, .code = ABS_MT_SLOT, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_X, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_Y, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_SYN, .code = SYN_REPORT, .value = 0 },
	{ .type = -1, .code = -1 },
};

static struct litest_device_interface interface = {
	.touch_down_events = down,
	.touch_move_events = move,
};

static struct input_absinfo absinfo[] = {
	{ ABS_X, 0, 1500, 0, 0, 0 },
	{ ABS_Y, 0, 2500, 0, 0, 0 },
	{ ABS_MT_SLOT, 0, 9, 0, 0, 0 },
	{ ABS_MT_POSITION_X, 0, 1500, 0, 0, 0 },
	{ ABS_MT_POSITION_Y, 0, 2500, 0, 0, 0 },
	{ ABS_MT_TRACKING_ID, 0, 65535, 0, 0, 0 },
	{ .value = -1 },
};

static struct input_id input_id = {
	.bustype = 0x11,
	.vendor = 0x22,
	.product = 0x33,
};

static int events[] = {
	EV_KEY, BTN_TOUCH,
	INPUT_PROP_MAX, INPUT_PROP_DIRECT,
	-1, -1
};

static const char udev_rule[] =
"ACTION==\"remove\", GOTO=\"calibrated_touchscreen_end\"\n"
"KERNEL!=\"event*\", GOTO=\"calibrated_touchscreen_end\"\n"
"\n"
"ATTRS{name}==\"litest Calibrated Touchscreen*\",\\\n"
"    ENV{LIBINPUT_CALIBRATION_MATRIX}=\"1.2 3.4 5.6 7.8 9.10 11.12\"\n"
"\n"
"LABEL=\"calibrated_touchscreen_end\"";

struct litest_test_device litest_calibrated_touchscreen_device = {
	.type = LITEST_CALIBRATED_TOUCHSCREEN,
	.features = LITEST_TOUCH,
	.shortname = "calibrated-touchscreen",
	.setup = litest_calibrated_touchscreen_setup,
	.interface = &interface,

	.name = "Calibrated Touchscreen",
	.id = &input_id,
	.events = events,
	.absinfo = absinfo,
	.udev_rule = udev_rule,
};
