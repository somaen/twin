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
 */

#include "engines/twin/lzss.h"

namespace Twin {


LzssReadStream::LzssReadStream(Common::ReadStream *indata, uint32 mode, uint32 realsize) {
	_outLzssBufData = (uint8 *)malloc(realsize);
	memset(_outLzssBufData, 0, realsize);
	decodeLZSS(indata, mode, realsize);
	_size = realsize;
	_pos = 0;
}

LzssReadStream::~LzssReadStream() {
	free(_outLzssBufData);
}

void LzssReadStream::decodeLZSS(Common::ReadStream *in, uint32 mode, uint32 size) {
	uint8 *dst = _outLzssBufData;

	do {
		uint8 b = in->readByte();
		for (int32 d = 0; d < 8; d++) {
			int32 length;
			if (!(b & (1 << d))) {
				uint16 offset = in->readUint16LE();
				length = (offset & 0x0F) + (mode + 1);
				uint8 *ptr = dst - (offset >> 4) - 1;
				for (int32 i = 0; i < length; i++)
					*(dst++) = *(ptr++);
			} else {
				length = 1;
				*(dst++) = in->readByte();
			}
			size -= length;
			if (size <= 0)
				return;
		}
	} while (size);
}

bool LzssReadStream::eos() const {
	return _pos >= _size;
}

uint32 LzssReadStream::read(void *buf, uint32 size) {
	if (size > _size - _pos)
		size = _size - _pos;

	memcpy(buf, &_outLzssBufData[_pos], size);
	_pos += size;

	return size;
}

bool LzssReadStream::seek(int32 offset, int whence) {
	if (whence == SEEK_SET) {
		_pos = offset;
	} else if (whence = SEEK_CUR) {
		_pos += offset;
	}
	return true;
}

} // End of Twin namespace
