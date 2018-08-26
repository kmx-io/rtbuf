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

#include "rtbuf.h"
#include "rtbuf_lib.h"
#include "rtbuf_signal.h"
#include "rtbuf_signal_type.h"
#include "rtbuf_dynamic.h"

s_rtbuf_lib_fun_var g_rtbuf_dynamic_limiter_var[] = {
  { "signal"  , RTBUF_SIGNAL_TYPE },
  { "gain"    , RTBUF_SIGNAL_TYPE },
  { "treshold", RTBUF_SIGNAL_TYPE },
  { "limit"   , RTBUF_SIGNAL_TYPE },
  { "attack"  , RTBUF_SIGNAL_TYPE },
  { "release" , RTBUF_SIGNAL_TYPE },
  { 0, 0 } };

s_rtbuf_lib_fun_out g_rtbuf_dynamic_limiter_out[] = {
  { "signal", RTBUF_SIGNAL_TYPE },
  { "gain"  , RTBUF_SIGNAL_SAMPLE_TYPE },
  { 0, 0 } };

const char     *rtbuf_lib_name = "dynamic";
unsigned long   rtbuf_lib_ver = RTBUF_LIB_VER;
s_rtbuf_lib_fun rtbuf_lib_fun[] = {
  { "limiter", rtbuf_dynamic_limiter, rtbuf_dynamic_limiter_start, 0,
    g_rtbuf_dynamic_limiter_var, g_rtbuf_dynamic_limiter_out },
  { 0, 0, 0, 0, 0, 0 } };