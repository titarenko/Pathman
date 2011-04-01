#include "Config.h"
#include "VirtualXmlReader.h"

using namespace irr;
using namespace core;
using namespace io;

Config::Config(Game* game, const path& filename)
	: _game(game)
	, _reader(new VirtualXmlReader(game->getDevice(
		)->getFileSystem()->createXMLReader(filename)))
{
}

Config::Config(Game* game, IConfigReader* reader)
	: _game(game)
	, _reader(reader)
{
}

Config::~Config(void)
{
	delete _reader;
}

bool Config::next()
{
	bool result = _reader->next();
	if (result)
		OnNode(_reader->getNodeName());
	return result;
}