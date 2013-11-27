// This file is part of Notepad++ project
// Copyright (C)2003 Don HO <don.h@free.fr>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// Note that the GPL places important restrictions on "derived works", yet
// it does not provide a detailed definition of that term.  To avoid
// misunderstandings, we consider an application to constitute a
// "derivative work" for the purpose of this license if it does any of the
// following:
// 1. Integrates source code from Notepad++.
// 2. Integrates/includes/aggregates Notepad++ into a proprietary executable
//    installer, such as those produced by InstallShield.
// 3. Links to a library or executes a program that does any of the above.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


#ifndef COLORS_H
#define COLORS_H

#ifdef RGB
#undef RGB
#define RGB(r,g,b) ((uint32_t)(((uint8_t)(r)|((uint16_t)((uint8_t)(g))<<8))|(((uint32_t)(uint8_t)(b))<<16)))
#endif

const uint32_t red                      = RGB(0xFF,    0,    0);
const uint32_t darkRed                  = RGB(0x80,    0,    0);
const uint32_t offWhite                 = RGB(0xFF, 0xFB, 0xF0);
const uint32_t darkGreen                = RGB(0,    0x80,    0);
const uint32_t liteGreen                = RGB(0,    0xFF,    0);
const uint32_t blueGreen                = RGB(0,    0x80, 0x80);
const uint32_t liteRed                  = RGB(0xFF, 0xAA, 0xAA);
const uint32_t liteBlueGreen            = RGB(0xAA, 0xFF, 0xC8);

const uint32_t liteBlue                 = RGB(0xA6, 0xCA, 0xF0);
const uint32_t veryLiteBlue             = RGB(0xC4, 0xF9, 0xFD);
const uint32_t extremeLiteBlue          = RGB(0xF2, 0xF4, 0xFF);

const uint32_t darkBlue                 = RGB(0, 0, 0x80);
const uint32_t blue                     = RGB(0, 0, 0xFF);
const uint32_t black                    = RGB(0, 0, 0);
const uint32_t white                    = RGB(0xFF, 0xFF, 0xFF);
const uint32_t darkGrey                 = RGB(64,     64,   64);
const uint32_t grey                     = RGB(128,   128,  128);
const uint32_t liteGrey                 = RGB(192,   192,  192);
const uint32_t veryLiteGrey             = RGB(224,   224,  224);
const uint32_t brown                    = RGB(128,    64,    0);
//const uint32_t greenBlue                = RGB(192,   128,   64);
const uint32_t darkYellow               = RGB(0xFF, 0xC0,    0);
const uint32_t yellow                   = RGB(0xFF, 0xFF,    0);
const uint32_t lightYellow              = RGB(0xFF, 0xFF, 0xD5);
const uint32_t cyan                     = RGB(0,    0xFF, 0xFF);
const uint32_t orange                   = RGB(0xFF, 0x80, 0x00);
const uint32_t purple                   = RGB(0x80, 0x00, 0xFF);
const uint32_t deepPurple               = RGB(0x87, 0x13, 0x97);

const uint32_t extremeLitePurple        = RGB(0xF8, 0xE8, 0xFF);
const uint32_t veryLitePurple           = RGB(0xE7, 0xD8, 0xE9);
const uint32_t liteBerge                = RGB(0xFE, 0xFC, 0xF5);
const uint32_t berge                    = RGB(0xFD, 0xF8, 0xE3);
/*
#define RGB2int(color) 
    (((((long)color) & 0x0000FF) << 16) | ((((long)color) & 0x00FF00)) | ((((long)color) & 0xFF0000) >> 16))
*/
#endif //COLORS_H

