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

#include "draci/draci.h"
#include "draci/animation.h"

namespace Draci {

void Animation::addAnimation(uint id, uint z, bool playing) {
	
	AnimObj *obj = new AnimObj();
	obj->_id = id;
	obj->_z = z;
	obj->_currentFrame = 0;
	obj->_playing = playing;

	insertAnimation(*obj);
}

void Animation::play(uint id) {

	AnimObj &obj = *getAnimation(id);

	obj._playing = true;
}

void Animation::stop(uint id) {

	AnimObj &obj = *getAnimation(id);

	obj._playing = false;
}

Common::List<AnimObj>::iterator Animation::getAnimation(uint id) {
	
	Common::List<AnimObj>::iterator it;

	for (it = _animObjects.begin(); it != _animObjects.end(); ++it) {
		if (it->_id == id) {
			return it;
		}
	}

	return _animObjects.end();
}

void Animation::insertAnimation(AnimObj &animObj) {
	
	Common::List<AnimObj>::iterator it;	

	for (it = _animObjects.begin(); it != _animObjects.end(); ++it) {
		if (animObj._z < it->_z) 
			break;
	}

	_animObjects.insert(it, animObj);
}

void Animation::addFrame(uint id, Drawable *frame) {
	
	Common::List<AnimObj>::iterator it = getAnimation(id);

	it->_frames.push_back(frame);	
}

void Animation::addOverlay(Drawable *overlay, uint z) {
	AnimObj *obj = new AnimObj();
	obj->_id = kOverlayImage;
	obj->_z = z;
	obj->_currentFrame = 0;
	obj->_playing = true;
	obj->_frames.push_back(overlay);

	insertAnimation(*obj);
}

void Animation::drawScene(Surface *surf) {
	
	Common::List<AnimObj>::iterator it;

	for (it = _animObjects.begin(); it != _animObjects.end(); ++it) {
		if (!it->_playing) {
			continue;
		}	
	
		if (it->_id == kOverlayImage) {			
			it->_frames[it->_currentFrame]->draw(surf, false);
		}
		else {
			it->_frames[it->_currentFrame]->draw(surf, true);
		}
	}
}

void Animation::deleteAnimation(uint id) {
	
	Common::List<AnimObj>::iterator it = getAnimation(id);

	for (uint i = 0; i < it->_frames.size(); ++i) {		
		delete it->_frames[i];
	}

	_animObjects.erase(it);
}
	
void Animation::deleteAll() {
	
	Common::List<AnimObj>::iterator it;

	for (it = _animObjects.begin(); it != _animObjects.end(); ++it) {
		for (uint i = 0; i < it->_frames.size(); ++i) {		
			delete it->_frames[i];
		}	
	}

	_animObjects.clear();
}

}
