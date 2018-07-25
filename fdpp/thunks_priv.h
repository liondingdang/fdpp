/*
 *  FDPP - freedos port to modern C++
 *  Copyright (C) 2018  Stas Sergeev (stsp)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef THUNKS_PRIV_H
#define THUNKS_PRIV_H

#ifdef __cplusplus
extern "C" {
#endif
void *resolve_segoff(struct far_s fa);
uint32_t thunk_call_void(struct far_s fa);
struct far_s lookup_far_st(const void *ptr);
void fdprintf(const char *format, ...) PRINTF(1);
void fdlogprintf(const char *format, ...) PRINTF(1);
void fdvprintf(const char *format, va_list vl);
void do_abort(const char *file, int line);
#ifdef __cplusplus
}
#endif

#endif