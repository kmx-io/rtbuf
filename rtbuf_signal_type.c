/*
 * Copyright 2018 Thomas de Grivel <thoxdg@gmail.com> +33614550127
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

#include <stdio.h>
#include "rtbuf.h"
#include "rtbuf_signal.h"

int main ()
{
  printf("/* file generated by rtbuf_signal_type */\n");
  printf("#ifndef RTBUF_SIGNAL_TYPE_H\n"
         "#define RTBUF_SIGNAL_TYPE_H\n"
         "\n");
  printf("#define RTBUF_SIGNAL_TYPE"
         " RTBUF_SIGNAL_SAMPLE_TYPE \"[%u]\"\n",
         RTBUF_SIGNAL_SAMPLES);
  printf("#define RTBUF_SIGNAL_DELAY_TYPE"
         " RTBUF_SIGNAL_SAMPLE_TYPE \"[%u]\"\n",
         RTBUF_SIGNAL_DELAY_SAMPLES_MAX);
  printf("\n"
         "#endif\n");
  return 0;
}
