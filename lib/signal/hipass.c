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

#include <math.h>
#include "../../librtbuf/rtbuf.h"
#include "../../librtbuf/lib.h"
#include "../signal.h"
#include "../signal_type.h"

s_rtbuf_lib_proc_in rtbuf_signal_hipass_in[] =
  {{ "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0, 1.0 },
   { "cutoff",   RTBUF_SIGNAL_TYPE, 8000.0, 1.0, RTBUF_SIGNAL_SAMPLERATE / 2.0, 2.0 },
   { 0, 0, 0.0, 0.0, 0.0, 0.0 }};

s_rtbuf_lib_proc_out rtbuf_signal_hipass_out[] =
  {{ "signal", RTBUF_SIGNAL_TYPE },
   { "x", RTBUF_SIGNAL_SAMPLE_TYPE },
   { "y", RTBUF_SIGNAL_SAMPLE_TYPE },
   { 0, 0 }};

int rtbuf_signal_hipass_start (s_rtbuf *rtb)
{
  s_rtbuf_signal_hipass_data *data;
  assert(rtb->proc->out_bytes == sizeof(*data));
  data = (s_rtbuf_signal_hipass_data*) rtb->data;
  data->x1 = 0;
  data->y1 = 0;
  return 0;
}

int rtbuf_signal_hipass (s_rtbuf *rtb)
{
  s_rtbuf_signal_fun in;
  s_rtbuf_signal_fun cutoff;
  s_rtbuf_signal_hipass_data *data;
  unsigned int i = 0;
  double k = 2.0 * RTBUF_SIGNAL_SAMPLERATE;
  rtbuf_signal_fun(rtb, RTBUF_SIGNAL_HIPASS_IN_SIGNAL, &in);
  rtbuf_signal_fun(rtb, RTBUF_SIGNAL_HIPASS_IN_CUTOFF, &cutoff);
  data = (s_rtbuf_signal_hipass_data*) rtb->data;
  while (i < RTBUF_SIGNAL_SAMPLES) {
    double x = in.sample_fun(in.signal, i);
    double fc = cutoff.sample_fun(cutoff.signal, i);
    double wc = 2.0 * M_PI * fc;
    data->signal[i] = (k * (x - data->x1) + (k - wc) * data->y1) / (k + wc);
    data->x1 = x;
    data->y1 = data->signal[i];
    i++;
  }
  return 0;
}

s_rtbuf_lib_proc rtbuf_lib_proc =
  { "hipass",
    rtbuf_signal_hipass,
    rtbuf_signal_hipass_start,
    0,
    rtbuf_signal_hipass_in,
    rtbuf_signal_hipass_out };

unsigned long rtbuf_lib_ver = RTBUF_LIB_VER;
