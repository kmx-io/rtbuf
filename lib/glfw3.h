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
#ifndef RTBUF_GLFW3_H
#define RTBUF_GLFW3_H

#include <GLFW/glfw3.h>
#include "../librtbuf/rtbuf.h"
#include "music.h"

typedef struct rtbuf_glfw3_keyboard_data {
  s_rtbuf_music_notes notes;
  GLFWwindow *window;
  unsigned int octave;
} s_rtbuf_glfw3_keyboard_data;

enum {
  RTBUF_GLFW3_OSCILLOSCOPE_IN_BLACK,
  RTBUF_GLFW3_OSCILLOSCOPE_IN_RED,
  RTBUF_GLFW3_OSCILLOSCOPE_IN_GREEN,
  RTBUF_GLFW3_OSCILLOSCOPE_IN_BLUE,
  RTBUF_GLFW3_OSCILLOSCOPE_INS
};

typedef struct rtbuf_glfw3_oscilloscope_data {
  GLFWwindow *window;
} s_rtbuf_glfw3_oscilloscope_data;

#endif
