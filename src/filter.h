/*
 * Copyright © 2012 Jonas Ådahl
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of the copyright holders not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.  The copyright holders make
 * no representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef FILTER_H
#define FILTER_H

#include "config.h"

#include <stdint.h>

struct motion_params {
	double dx, dy; /* in units/ms @ 400dpi */
};

struct motion_filter;

void
filter_dispatch(struct motion_filter *filter,
		struct motion_params *motion,
		void *data, uint64_t time);
void
filter_destroy(struct motion_filter *filter);


struct motion_filter_interface {
	void (*filter)(struct motion_filter *filter,
		       struct motion_params *motion,
		       void *data, uint64_t time);
	void (*destroy)(struct motion_filter *filter);
};

struct motion_filter {
	struct motion_filter_interface *interface;
};

struct motion_filter *
create_linear_acceleration_filter(double speed);

typedef double (*accel_profile_func_t)(struct motion_filter *filter,
				       void *data,
				       double velocity,
				       uint64_t time);

struct motion_filter *
create_pointer_accelator_filter(accel_profile_func_t filter);


/*
 * Pointer acceleration profiles.
 */

/*
 * Profile similar which is similar to nonaccelerated but with a smooth
 * transition between accelerated and non-accelerated.
 */
double
pointer_accel_profile_smooth_simple(struct motion_filter *filter,
				    void *data,
				    double velocity,
				    uint64_t time);

#endif /* FILTER_H */
