/*
    Copyright (c) 2013 250bpm s.r.o.  All rights reserved.
    Copyright (c) 2014 Wirebird Labs LLC.  All rights reserved.
    Copyright 2016 Garrett D'Amore <garrett@damore.org>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef NN_AWS_INCLUDED
#define NN_AWS_INCLUDED

#include "sws.h"

#include "../../transport.h"

#include "../../aio/fsm.h"
#include "../../aio/usock.h"

#include "../../utils/list.h"

/*  State machine handling accepted WS sockets. */

/*  In bws, some events are just *assumed* to come from a child aws object.
    By using non-trivial event codes, we can do more reliable sanity checking
    in such scenarios. */
#define NN_AWS_ACCEPTED 34231
#define NN_AWS_ERROR 34232
#define NN_AWS_STOPPED 34233

struct nn_aws {

    /*  The state machine. */
    struct nn_fsm fsm;
    int state;

    /*  Pointer to the associated endpoint. */
    struct nn_ep *ep;

    /*  Underlying socket. */
    struct nn_usock usock;

    /*  Listening socket. Valid only while accepting new connection. */
    struct nn_usock *listener;
    struct nn_fsm_owner listener_owner;

    /*  State machine that takes care of the connection in the active state. */
    struct nn_sws sws;

    /*  Events generated by aws state machine. */
    struct nn_fsm_event accepted;
    struct nn_fsm_event done;

    /*  This member can be used by owner to keep individual awss in a list. */
    struct nn_list_item item;
};

void nn_aws_init (struct nn_aws *self, int src,
    struct nn_ep *ep, struct nn_fsm *owner);
void nn_aws_term (struct nn_aws *self);

int nn_aws_isidle (struct nn_aws *self);
void nn_aws_start (struct nn_aws *self, struct nn_usock *listener);
void nn_aws_stop (struct nn_aws *self);

#endif
