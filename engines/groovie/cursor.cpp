/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "groovie/cursor.h"
#include "groovie/groovie.h"

namespace Groovie {

// Cursor Manager

CursorMan::CursorMan(OSystem *system) :
	_syst(system), _lastTime(0), _cursor(NULL) {
}

CursorMan::~CursorMan() {
	// Delete the cursors
	for (uint cursor = 0; cursor < _cursors.size(); cursor++) {
		delete _cursors[cursor];
	}
}

uint8 CursorMan::getStyle() {
	return _current;
}

void CursorMan::setStyle(uint8 newStyle) {
	// Reset the animation
	_lastFrame = 254;
	_lastTime = 1;

	// Save the new cursor
	_current = newStyle;
	_cursor = _cursors[newStyle];

	// Show the first frame
	_cursor->enable();
	animate();
}

void CursorMan::animate() {
	if (_lastTime) {
		int newTime = _syst->getMillis();
		if (_lastTime - newTime >= 75) {
			_lastFrame++;
			_lastFrame %= _cursor->getFrames();
			_cursor->showFrame(_lastFrame);
			_lastTime = _syst->getMillis();
		}
	}
}


// t7g Cursor

class Cursor_t7g : public Cursor {
public:
	Cursor_t7g(OSystem *system, uint8 *img, uint8 *pal);

	void enable();
	void showFrame(uint16 frame);

private:
	OSystem *_syst;
	byte *_img;
	byte *_pal;
};

Cursor_t7g::Cursor_t7g(OSystem *system, uint8 *img, uint8 *pal) :
	_syst(system), _pal(pal) {

	_width = img[0];
	_height = img[1];
	_numFrames = img[2];
	uint8 elinor1 = img[3];
	uint8 elinor2 = img[4];

	_img = img + 5;

	debugC(1, kGroovieDebugCursor | kGroovieDebugAll, "Groovie::Cursor: width: %d, height: %d, frames:%d", _width, _height, _numFrames);
	debugC(1, kGroovieDebugCursor | kGroovieDebugUnknown | kGroovieDebugAll, "Groovie::Cursor: elinor: 0x%02X (%d), 0x%02X (%d)", elinor1, elinor1, elinor2, elinor2);
}

void Cursor_t7g::enable() {
	// Apply the palette
	_syst->setCursorPalette(_pal, 0, 32);
}

void Cursor_t7g::showFrame(uint16 frame) {
	// Set the mouse cursor
	int offset = _width * _height * frame;
	_syst->setMouseCursor((const byte *)_img + offset, _width, _height, _width >> 1, _height >> 1, 0);
}


// t7g Cursor Manager

#define NUM_IMGS 9
static const uint16 cursorDataOffsets[NUM_IMGS] = {
0x0000, 0x182f, 0x3b6d, 0x50cc, 0x6e79, 0x825d, 0x96d7, 0xa455, 0xa776
};

#define NUM_PALS 7
//Pals: 0xb794, 0xb7f4, 0xb854, 0xb8b4, 0xb914, 0xb974, 0xb9d4

#define NUM_STYLES 11
// pyramid is cursor 8, eyes are 9 & 10
const uint CursorMan_t7g::_cursorImg[NUM_STYLES] = {3, 5, 4, 3, 1, 0, 2, 6, 7, 8, 8};
const uint CursorMan_t7g::_cursorPal[NUM_STYLES] = {0, 0, 0, 0, 2, 0, 1, 3, 5, 4, 6};

CursorMan_t7g::CursorMan_t7g(OSystem *system) :
	CursorMan(system) {

	// Open the cursors file
	Common::File robgjd;
	if (!robgjd.open("rob.gjd")) {
		error("Groovie::Cursor: Couldn't open rob.gjd");
		return;
	}

	// Load the images
	for (uint imgnum = 0; imgnum < NUM_IMGS; imgnum++) {
		robgjd.seek(cursorDataOffsets[imgnum]);
		_images.push_back(loadImage(robgjd));
	}

	// Load the palettes
	robgjd.seek(-0x60 * NUM_PALS, SEEK_END);
	for (uint palnum = 0; palnum < NUM_PALS; palnum++) {
		_palettes.push_back(loadPalette(robgjd));
	}

	// Build the cursors
	for (uint cursor = 0; cursor < NUM_STYLES; cursor++) {
		Cursor *s = new Cursor_t7g(_syst, _images[_cursorImg[cursor]], _palettes[_cursorPal[cursor]]);
		_cursors.push_back(s);
	}

	robgjd.close();
}

CursorMan_t7g::~CursorMan_t7g() {
	// Delete the images
	for (uint img = 0; img < _images.size(); img++) {
		delete[] _images[img];
	}

	// Delete the palettes
	for (uint pal = 0; pal < _palettes.size(); pal++) {
		delete[] _palettes[pal];
	}
}

byte *CursorMan_t7g::loadImage(Common::File &file) {
	uint16 decompbytes = 0, offset, i, length;
	uint8 flagbyte, lengthmask = 0x0F, offsetlen, var_8;
	byte *cursorStorage = new byte[65536];
	uint8 *runningcursor = cursorStorage;

	bool finished = false;
	while (!(finished || file.eos())) {
		flagbyte = file.readByte();
		for (i = 1; i <= 8; i++) {
			if (!file.eos()) {
				if (flagbyte & 1) {
					*(runningcursor++) = file.readByte();
					decompbytes++;
				} else {
					var_8 = file.readByte();
					offsetlen = file.readByte();
					if (var_8 == 0 && offsetlen == 0) {
						finished = true;
						break;
					}
					length = (offsetlen & lengthmask) + 3;
					offsetlen >>= 4;
					offset = (offsetlen << 8) + var_8;
					decompbytes += length;

					for (; length > 0; length--, runningcursor++) {
						*(runningcursor) = *(runningcursor - offset);
					}
				}
				flagbyte = flagbyte >> 1;
			}
		}
	}

	return cursorStorage;
}

byte *CursorMan_t7g::loadPalette(Common::File &file) {
	byte *palette = new byte[4 * 32];
	for (uint8 colournum = 0; colournum < 32; colournum++) {
		palette[colournum * 4 + 0] = file.readByte();
		palette[colournum * 4 + 1] = file.readByte();
		palette[colournum * 4 + 2] = file.readByte();
		palette[colournum * 4 + 3] = 0;
	}
	return palette;
}


// v2 Cursor

class Cursor_v2 : public Cursor {
public:
	Cursor_v2(Common::File &file);

	void enable();
	void showFrame(uint16 frame);

private:
	//byte *_data;
};

Cursor_v2::Cursor_v2(Common::File &file) {
	_numFrames = file.readUint16LE();
	_width = file.readUint16LE();
	_height = file.readUint16LE();

	debugC(1, kGroovieDebugCursor | kGroovieDebugAll, "Groovie::Cursor: width: %d, height: %d, frames:%d", _width, _height, _numFrames);

	uint16 tmp16 = file.readUint16LE();
	debugC(5, kGroovieDebugCursor | kGroovieDebugAll, "hotspot x?: %d\n", tmp16);
	tmp16 = file.readUint16LE();
	debugC(5, kGroovieDebugCursor | kGroovieDebugAll, "hotspot y?: %d\n", tmp16);
	int loop2count = file.readUint16LE();
	debugC(5, kGroovieDebugCursor | kGroovieDebugAll, "loop2count?: %d\n", loop2count);
	for (int l = 0; l < loop2count; l++) {
		tmp16 = file.readUint16LE();
		debugC(5, kGroovieDebugCursor | kGroovieDebugAll, "loop2a: %d\n", tmp16);
		tmp16 = file.readUint16LE();
		debugC(5, kGroovieDebugCursor | kGroovieDebugAll, "loop2b: %d\n", tmp16);
	}

	file.seek(0x20 * 3, SEEK_CUR);

	for (int f = 0; f < _numFrames; f++) {
		uint32 tmp32 = file.readUint32LE();
		debugC(5, kGroovieDebugCursor | kGroovieDebugAll, "loop3: %d\n", tmp32);

		//file.seek(tmp32, SEEK_CUR);
		byte *data = new byte[tmp32];
		file.read(data, tmp32);
		//Common::hexdump(data, tmp32);
		delete[] data;
	}
}

void Cursor_v2::enable() {
}

void Cursor_v2::showFrame(uint16 frame) {
}


// v2 Cursor Manager

CursorMan_v2::CursorMan_v2(OSystem *system) :
	CursorMan(system) {

	// Open the icons file
	Common::File iconsFile;
	if (!iconsFile.open("icons.ph")) {
		error("Groovie::Cursor: Couldn't open icons.ph");
		return;
	}

	// Verify the signature
	uint32 tmp32 = iconsFile.readUint32LE();
	uint16 tmp16 = iconsFile.readUint16LE();
	if (tmp32 != 0x6e6f6369 || tmp16 != 1) {
		error("Groovie::Cursor: icons.ph signature failed: %04X %d", tmp32, tmp16);
		return;
	}

	// Read the number of icons
	uint16 nicons = iconsFile.readUint16LE();

	// Read the icons
	for (int i = 0; i < nicons; i++) {
		Cursor *s = new Cursor_v2(iconsFile);
		_cursors.push_back(s);
	}

	iconsFile.close();
}

CursorMan_v2::~CursorMan_v2() {
}

} // End of Groovie namespace
