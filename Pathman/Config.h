#pragma once

#include <irrlicht.h>
#include "IConfigReader.h"
#include "Game.h"
#include "InitializationException.h"
#include "NotImplementedException.h"

/*!
	Represents base class for any config.
	Derive any config class from it and implement OnNode.
	Use family of template methods to obtain data.
*/
class Config
{
public:
	/*!
		Creates config from file using Irrlicht's filesystem.
	*/
	Config(Game* game, const irr::io::path& filename);

	/*!
		Creates config using provided reader.
	*/
	Config(Game* game, IConfigReader* reader);

	/*!
		Frees allocated resources.
	*/
	~Config(void);

protected:
	/*!
		Should be called to move to the next node.
		Returns false if no more nodes left.
	*/
	bool next();

	/*!
		Should be implemented by the descendants 
		to process values of attributes of the node.
	*/
	virtual void OnNode(const irr::core::stringw& name) = 0;

	template <class T> T read(
		const irr::core::stringw& attributeName)
	{
		throw NotImplementedException();
	}

	/*!
		Reads stringw from node's attribute with provided name.
	*/
	template <> irr::core::stringw read<irr::core::stringw>(
		const irr::core::stringw& attributeName)
	{
		irr::core::stringw result = 
			_reader->getAttributeValue(attributeName.c_str());
		if (!result.size())
			throw InitializationException(attributeName);
		return result;
	}

	/*!
		Reads bool from node's attribute with provided name.
	*/
	template <> bool read<bool>(
		const irr::core::stringw& attributeName)
	{
		irr::core::stringw value = 
			read<irr::core::stringw>(attributeName);
		value.make_lower();
		return value == "true" || value == "1";
	}

	/*!
		Reads s32 from node's attribute with provided name.
	*/
	template <> irr::s32 read<irr::s32>(
		const irr::core::stringw& attributeName)
	{
		return (irr::s32) _reader->getAttributeValueAsInt(
			attributeName.c_str());
	}

	/*!
		Reads u32 from node's attribute with provided name.
		Warning! Result is equivalent of "(u32) read<s32>"!
	*/
	template <> irr::u32 read<irr::u32>(
		const irr::core::stringw& attributeName)
	{
		return (irr::u32) _reader->getAttributeValueAsInt(
			attributeName.c_str());
	}

	/*!
		Reads f32 from node's attribute with provided name.
	*/
	template <> irr::f32 read<irr::f32>(
		const irr::core::stringw& attributeName)
	{
		return (irr::f32) _reader->getAttributeValueAsFloat(
			attributeName.c_str());
	}

	/*!
		Reads path from node's attribute with provided name.
		Path is checked to be correct.
	*/
	template <> irr::io::path read<irr::io::path>(
		const irr::core::stringw& attributeName)
	{
		irr::core::stringw result = 
			read<irr::core::stringw>(attributeName);
		if (!_game->getDevice()->getFileSystem()->existFile(result))
			throw InitializationException(attributeName);
		return result;
	}

	/*!
		Reads ITexture from node's attribute with provided name.
		(Considers node's attribure value as path to the texture file.)
	*/
	template <> irr::video::ITexture* read<irr::video::ITexture*>(
		const irr::core::stringw& attributeName)
	{
		irr::video::ITexture* result = 
			_game->getDevice()->getVideoDriver()->getTexture(
			read<irr::io::path>(attributeName));
		if (!result)
			throw InitializationException(attributeName);
		return result;
	}

	/*!
		Reads IGUIFont from node's attribute with provided name.
		(Considers node's attribure value as path to the font file.)
	*/
	template <> irr::gui::IGUIFont* read<irr::gui::IGUIFont*>(
		const irr::core::stringw& attributeName)
	{
		irr::gui::IGUIFont* result = 
			_game->getDevice()->getGUIEnvironment()->getFont(
			read<irr::io::path>(attributeName));
		if (!result)
			throw InitializationException(attributeName);
		return result;
	}

	/*!
		Reads SColor from node's attribute with provided name.
	*/
	template <> irr::video::SColor read<irr::video::SColor>(
		const irr::core::stringw& attributeName)
	{
		irr::video::SColor color(0xFF000000);

		color.setRed(read<irr::u32>(attributeName + "Red"));
		color.setGreen(read<irr::u32>(attributeName + "Green"));
		color.setBlue(read<irr::u32>(attributeName + "Blue"));

		return color;
	}

	/*!
		Reads IAnimatedMesh from node's attribute with provided name.
		(Considers node's attribure value as path to the mesh file.)
	*/
	template <> irr::scene::IAnimatedMesh* read<irr::scene::IAnimatedMesh*>(
		const irr::core::stringw& attributeName)
	{
		irr::scene::IAnimatedMesh* result = 
			_game->getDevice()->getSceneManager()->getMesh(
			read<irr::io::path>(attributeName));
		if (!result)
			throw InitializationException(attributeName);
		return result;
	}

	Game* _game;

private:
	IConfigReader* _reader;
};