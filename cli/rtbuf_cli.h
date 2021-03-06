/*
 * Copyright 2020-2021 Thomas de Grivel <thoxdg@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef RTBUF_CLI_H
#define RTBUF_CLI_H

#include <pthread.h>

typedef void (*f_rtbuf_position) (s_rtbuf *rtb, short x, short y);

extern f_rtbuf_position g_rtbuf_position_cb;
extern pthread_t g_rtbuf_cli_run_thread;

int rtbuf_cli_exit (int argc, const char *argv[]);
void repl_init ();
int load (const char *path);
int repl ();
void rtbuf_cli_args (int argc, char *argv[]);

int rtbuf_cli_start ();
int rtbuf_cli_stop ();

int rtbuf_cli_do_event ();

#endif /* RTBUF_CLI_H */
