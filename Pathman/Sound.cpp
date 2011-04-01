#include "Sound.h"
#include "Game.h"

using namespace irr;
using namespace io;

Sound::Sound(Game* game, const path& filename, bool looped, bool stopped)
	: _game(game)
	, _filename(filename)
	, _looped(looped)
	, _stopped(stopped)
	, _sound(NULL)
{
	IReadFile* read = _game->getDevice(
		)->getFileSystem()->createAndOpenFile(filename);

	void* buffer = new u8[read->getSize()];
	read->read(buffer, read->getSize());

	_game->getSoundEngine()->addSoundSourceFromMemory(
		buffer, read->getSize(), filename.c_str());

	read->drop();
	delete[] buffer;

	if (!_stopped)
		_game->getSoundEngine()->play2D(
			_filename.c_str(), _looped, _stopped);
}

Sound::~Sound(void)
{
	stop();
}

void Sound::play(bool stoppable)
{
	if (!stoppable) {

		_game->getSoundEngine()->play2D(
			_filename.c_str(), _looped);

	} else if (_stopped) {

		stop();
		_sound = _game->getSoundEngine()->play2D(
			_filename.c_str(), _looped, _stopped);
		_sound->setIsPaused(false);

	}
}

void Sound::stop()
{
	if (_sound) {
		_sound->stop();
		_sound->drop();
		_sound = NULL;
	}
}