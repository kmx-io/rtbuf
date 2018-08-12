/*
 * Copyright 2018 Thomas de Grivel <thoxdg@gmail.com> +33614550127
 * Copyright 2018 Judy Najnudel <judy.najnudel@gmail.com>
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
#include <strings.h>
#include "rtbuf.h"
#include "rtbuf_synth.h"

static inline
double adsr (double attack, double decay, double sustain,
             double release, double start, double stop)
{
  double x;
  if (start < attack)
    x = start / attack;
  else if (start < attack + decay)
    x = 1.0 + (sustain - 1.0) * (start - attack);
  else
    x = sustain;
  if (stop < 0.0)
    return x;
  if (stop < release)
    return x * (1.0 - stop / release);
  return 0.0;
}

void rtbuf_synth_adsr_signal (s_rtbuf *rtb, double *signal,
                              double velocity, double start,
                              double stop, double r)
{
  double a =
    rtbuf_signal_sample(rtb, RTBUF_SYNTH_ADSR_VAR_ATTACK,  0.02);
  double d =
    rtbuf_signal_sample(rtb, RTBUF_SYNTH_ADSR_VAR_DECAY,   0.03);
  double s =
    rtbuf_signal_sample(rtb, RTBUF_SYNTH_ADSR_VAR_SUSTAIN, 0.5);
  unsigned int i = 0;
  (void) velocity;
  (void) start;
  (void) stop;
  while (i < RTBUF_SIGNAL_SAMPLES) {
    double dt = (double) i / RTBUF_SIGNAL_SAMPLERATE;
    double start_i = start + dt;
    double stop_i = stop < 0 ? stop : stop + dt;
    a = max(0.0, a);
    d = max(0.0, d);
    s = max(0.0, s);
    r = max(0.0, r);
    *signal = velocity * adsr(a, d, s, r, start_i, stop_i);
    signal++;
    i++;
  }
}

int rtbuf_synth_adsr (s_rtbuf *rtb)
{
  double vel;
  double start;
  s_rtbuf_synth_adsr_data *data;
  assert(rtb);
  assert(rtb->data);
  vel = rtbuf_signal_sample(rtb, RTBUF_SYNTH_ADSR_VAR_VELOCITY, 0.0);
  start = rtbuf_signal_sample(rtb, RTBUF_SYNTH_ADSR_VAR_START, -1.0);
  data = (s_rtbuf_synth_adsr_data*) rtb->data;
  if (data->state == RTBUF_SYNTH_ENVELOPE_STATE_NOT_STARTED) {
    if (vel > 0.0 && start >= 0.0)
      data->state = RTBUF_SYNTH_ENVELOPE_STATE_STARTED;
    else
      return 0;
  }
  if (data->state == RTBUF_SYNTH_ENVELOPE_STATE_ENDED)
    return 0;
  if (data->state == RTBUF_SYNTH_ENVELOPE_STATE_STARTED) {
    double stop =
      rtbuf_signal_sample(rtb, RTBUF_SYNTH_ADSR_VAR_STOP, -1.0);
    double rel =
      rtbuf_signal_sample(rtb, RTBUF_SYNTH_ADSR_VAR_RELEASE, 1.0);
    if (stop > rel) {
      rtbuf_signal_zero(data->signal);
      data->state = RTBUF_SYNTH_ENVELOPE_STATE_ENDED;
      return 0;
    }
    rtbuf_synth_adsr_signal(rtb, data->signal, vel, start, stop, rel);
    return 0;
  }
  assert(data->state != data->state);
  return 0;
}

int rtbuf_synth_adsr_start (s_rtbuf *rtb)
{
  s_rtbuf_synth_adsr_data *data;
  assert(rtb->data);
  assert(rtb->fun);
  assert(rtb->fun->out_bytes == sizeof(*data));
  data = (s_rtbuf_synth_adsr_data*) rtb->data;
  data->state = RTBUF_SYNTH_ENVELOPE_STATE_NOT_STARTED;
  bzero(data->signal, sizeof(t_rtbuf_signal));
  return 0;
}
