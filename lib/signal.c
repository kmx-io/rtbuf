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

#include <math.h>
#include <stdio.h>
#include <strings.h>
#include <rtbuf/rtbuf.h>
#include <rtbuf/lib.h>
#include <rtbuf/signal.h>
#include <rtbuf/signal_type.h>

const double g_rtbuf_signal_sample_zero       = 0.0;
const double g_rtbuf_signal_sample_half       = 0.5;
const double g_rtbuf_signal_sample_one        = 1.0;
const double g_rtbuf_signal_default_frequency = 220.0;

s_rtbuf_lib_proc_in g_rtbuf_signal_bandpass2_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 400.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { "qfactor",  RTBUF_SIGNAL_TYPE, 1.0, 0.0, 1000.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_bandpass2_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_delay_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "delay",    RTBUF_SIGNAL_TYPE, 0.4, 0.0, RTBUF_SIGNAL_DELAY_MAX },
  { "feedback", RTBUF_SIGNAL_TYPE, 0.5, 0.0, 1.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_delay_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "in", RTBUF_SIGNAL_DELAY_TYPE },
  { "pos", "unsigned int" },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_equalizer10_in[] = {
  { "signal", RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "amp32",  RTBUF_SIGNAL_TYPE, 1.0, 0.0, 2.0 },
  { "amp64",  RTBUF_SIGNAL_TYPE, 1.0, 0.0, 2.0 },
  { "amp128", RTBUF_SIGNAL_TYPE, 1.0, 0.0, 2.0 },
  { "amp256", RTBUF_SIGNAL_TYPE, 1.0, 0.0, 2.0 },
  { "amp512", RTBUF_SIGNAL_TYPE, 1.0, 0.0, 2.0 },
  { "amp1k",  RTBUF_SIGNAL_TYPE, 1.0, 0.0, 2.0 },
  { "amp2k",  RTBUF_SIGNAL_TYPE, 1.0, 0.0, 2.0 },
  { "amp4k",  RTBUF_SIGNAL_TYPE, 1.0, 0.0, 2.0 },
  { "amp8k",  RTBUF_SIGNAL_TYPE, 1.0, 0.0, 2.0 },
  { "amp16k", RTBUF_SIGNAL_TYPE, 1.0, 0.0, 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_equalizer10_out[] = {
  { "signal",    RTBUF_SIGNAL_TYPE },
  { "signal32",  RTBUF_SIGNAL_TYPE },
  { "signal64",  RTBUF_SIGNAL_TYPE },
  { "signal128", RTBUF_SIGNAL_TYPE },
  { "signal256", RTBUF_SIGNAL_TYPE },
  { "signal512", RTBUF_SIGNAL_TYPE },
  { "signal1k",  RTBUF_SIGNAL_TYPE },
  { "signal2k",  RTBUF_SIGNAL_TYPE },
  { "signal4k",  RTBUF_SIGNAL_TYPE },
  { "signal8k",  RTBUF_SIGNAL_TYPE },
  { "signal16k", RTBUF_SIGNAL_TYPE },
  { "x1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y0_1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y0_2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y0_3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y0_4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1_1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1_2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1_3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1_4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2_1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2_2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2_3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2_4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3_1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3_2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3_3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3_4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y4_1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y4_2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y4_3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y4_4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y5_1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y5_2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y5_3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y5_4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y6_1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y6_2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y6_3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y6_4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y7_1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y7_2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y7_3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y7_4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y8_1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y8_2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y8_3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y8_4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y9_1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y9_2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y9_3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y9_4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_flanger_in[] = {
  { "signal",    RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "frequency", RTBUF_SIGNAL_TYPE, 0.5, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { "amplitude", RTBUF_SIGNAL_TYPE, 0.02, 0.0, 1.0 },
  { "delay",     RTBUF_SIGNAL_TYPE, 0.0001, 0.0, 1.0 },
  { "feedback",  RTBUF_SIGNAL_TYPE, 0.01, 0.0, 1.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_flanger_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "phase", "double" },
  { "in", RTBUF_SIGNAL_FLANGER_TYPE },
  { "pos", "unsigned int" },
  { "ds", "unsigned int" },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_hipass_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 8000.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_hipass_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_hipass2_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 8000.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_hipass2_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_hipass3_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 8000.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_hipass3_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_hipass4_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 8000.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_hipass4_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_hipass5_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 400.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_hipass5_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x5", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y5", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_lowpass_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 400.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_lowpass_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_lowpass2_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 400.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_lowpass2_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_lowpass3_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 400.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_lowpass3_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_lowpass4_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 400.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_lowpass4_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_lowpass5_in[] = {
  { "signal",   RTBUF_SIGNAL_TYPE, 0.0, -1.0, 1.0 },
  { "cutoff",   RTBUF_SIGNAL_TYPE, 400.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_lowpass5_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "x1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "x5", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y1", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y2", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y3", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y4", RTBUF_SIGNAL_SAMPLE_TYPE },
  { "y5", RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_sawtooth_in[] = {
  { "frequency", RTBUF_SIGNAL_TYPE, 220.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { "amplitude", RTBUF_SIGNAL_TYPE, 1.0, 0.0, 1.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_sawtooth_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "phase", "double" },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_sinus_in[] = {
  { "frequency", RTBUF_SIGNAL_TYPE, 220.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { "amplitude", RTBUF_SIGNAL_TYPE, 1.0, 0.0, 1.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_sinus_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "phase", "double" },
  { 0, 0 } };

s_rtbuf_lib_proc_in g_rtbuf_signal_square_in[] = {
  { "frequency", RTBUF_SIGNAL_TYPE, 220.0, 0.0, RTBUF_SIGNAL_SAMPLERATE / 2.0 },
  { "amplitude", RTBUF_SIGNAL_TYPE, 1.0, 0.0, 1.0 },
  { "pulse",     RTBUF_SIGNAL_TYPE, 0.5, 0.0, 1.0 },
  { 0, 0, 0.0, 0.0, 0.0 } };

s_rtbuf_lib_proc_out g_rtbuf_signal_square_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "phase", "double" },
  { 0, 0 } };

const char     *rtbuf_lib_name = "signal";
unsigned long   rtbuf_lib_ver = RTBUF_LIB_VER;
s_rtbuf_lib_proc rtbuf_lib_proc[] = {
  { "bandpass2", rtbuf_signal_bandpass2, rtbuf_signal_bandpass2_start, 0,
    g_rtbuf_signal_bandpass2_in, g_rtbuf_signal_bandpass2_out },
  { "delay", rtbuf_signal_delay, rtbuf_signal_delay_start, 0,
    g_rtbuf_signal_delay_in, g_rtbuf_signal_delay_out },
  { "equalizer10", rtbuf_signal_equalizer10, rtbuf_signal_equalizer10_start, 0,
    g_rtbuf_signal_equalizer10_in, g_rtbuf_signal_equalizer10_out },
  { "flanger", rtbuf_signal_flanger, rtbuf_signal_flanger_start, 0,
    g_rtbuf_signal_flanger_in, g_rtbuf_signal_flanger_out },
  { "hipass", rtbuf_signal_hipass, rtbuf_signal_hipass_start, 0,
    g_rtbuf_signal_hipass_in, g_rtbuf_signal_hipass_out },
  { "hipass2", rtbuf_signal_hipass2, rtbuf_signal_hipass2_start, 0,
    g_rtbuf_signal_hipass2_in, g_rtbuf_signal_hipass2_out },
  { "hipass3", rtbuf_signal_hipass3, rtbuf_signal_hipass3_start, 0,
    g_rtbuf_signal_hipass3_in, g_rtbuf_signal_hipass3_out },
  { "hipass4", rtbuf_signal_hipass4, rtbuf_signal_hipass4_start, 0,
    g_rtbuf_signal_hipass4_in, g_rtbuf_signal_hipass4_out },
  { "hipass5", rtbuf_signal_hipass5, rtbuf_signal_hipass5_start, 0,
    g_rtbuf_signal_hipass5_in, g_rtbuf_signal_hipass5_out },
  { "lowpass", rtbuf_signal_lowpass, rtbuf_signal_lowpass_start, 0,
    g_rtbuf_signal_lowpass_in, g_rtbuf_signal_lowpass_out },
  { "lowpass2", rtbuf_signal_lowpass2, rtbuf_signal_lowpass2_start, 0,
    g_rtbuf_signal_lowpass2_in, g_rtbuf_signal_lowpass2_out },
  { "lowpass3", rtbuf_signal_lowpass3, rtbuf_signal_lowpass3_start, 0,
    g_rtbuf_signal_lowpass3_in, g_rtbuf_signal_lowpass3_out },
  { "lowpass4", rtbuf_signal_lowpass4, rtbuf_signal_lowpass4_start, 0,
    g_rtbuf_signal_lowpass4_in, g_rtbuf_signal_lowpass4_out },
  { "lowpass5", rtbuf_signal_lowpass5, rtbuf_signal_lowpass5_start, 0,
    g_rtbuf_signal_lowpass5_in, g_rtbuf_signal_lowpass5_out },
  { "sawtooth", rtbuf_signal_sawtooth, rtbuf_signal_sawtooth_start, 0,
    g_rtbuf_signal_sawtooth_in, g_rtbuf_signal_sawtooth_out },
  { "sinus", rtbuf_signal_sinus, rtbuf_signal_sinus_start, 0,
    g_rtbuf_signal_sinus_in, g_rtbuf_signal_sinus_out },
  { "square", rtbuf_signal_square, rtbuf_signal_square_start, 0,
    g_rtbuf_signal_square_in, g_rtbuf_signal_square_out },
  { 0, 0, 0, 0, 0, 0 } };

void rtbuf_signal_zero (t_rtbuf_signal_sample *signal)
{
  assert(signal);
  bzero(signal, sizeof(t_rtbuf_signal));
}

t_rtbuf_signal_sample
rtbuf_signal_sample (s_rtbuf *rtb,
                     unsigned int in,
                     t_rtbuf_signal_sample default_value)
{
  s_rtbuf_binding *v;
  assert(rtb);
  assert(rtb->proc);
  assert(in < rtb->proc->in_n);
  v = &rtb->in[in];
  if (v->rtb >= 0) {
    s_rtbuf *src;
    s_rtbuf_proc_out *out;
    assert(v->rtb < RTBUF_MAX);
    src = &g_rtbuf[v->rtb];
    assert(src->data);
    assert(src->proc);
    assert(v->out < src->proc->out_n);
    out = &src->proc->out[v->out];
    assert(out->type);
    if (out->type->t.bits >= sizeof(t_rtbuf_signal_sample) * 8) {
      t_rtbuf_signal_sample *sample = (t_rtbuf_signal_sample*)
        ((char*) src->data + out->offset);
      return *sample;
    }
  }
  return default_value;
}

double rtbuf_signal_sample_from_sample (const double *signal,
                                        unsigned int i)
{
  (void) i;
  assert(signal);
  return *signal;
}

double rtbuf_signal_sample_from_signal (const double *signal,
                                        unsigned int i)
{
  assert(signal);
  assert(i < RTBUF_SIGNAL_SAMPLES);
  return signal[i];
}

void rtbuf_signal_fun (s_rtbuf *rtb,
                       unsigned int in,
                       s_rtbuf_signal_fun *rsf)
{
  s_rtbuf_binding *v;
  const double *default_value;
  assert(rtb);
  assert(rtb->proc);
  assert(in < rtb->proc->in_n);
  assert(rsf);
  default_value = &rtb->proc->in[in].def;
  rsf->signal = default_value;
  rsf->sample_fun = rtbuf_signal_sample_from_sample;
  v = &rtb->in[in];
  if (v->rtb >= 0) {
    s_rtbuf *dest;
    s_rtbuf_proc_out *out;
    assert(v->rtb < RTBUF_MAX);
    dest = &g_rtbuf[v->rtb];
    assert(dest->data);
    assert(dest->proc);
    assert(v->out < dest->proc->out_n);
    out = &dest->proc->out[v->out];
    assert(out->type);
    if (out->type->t.bits >= sizeof(t_rtbuf_signal_sample) * 8)
      rsf->signal = (double*)((char*) dest->data + out->offset);
    if (out->type->t.bits >= sizeof(t_rtbuf_signal) * 8)
      rsf->sample_fun = rtbuf_signal_sample_from_signal;
  }
}

const double sqrt2_2 = M_SQRT2 * M_SQRT2;