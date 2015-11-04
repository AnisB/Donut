/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/
#include "sceneloader.h"
#include "tools/fileloader.h"
#include "resource/common.h"
#include "base/common.h"
#include "picojson.h"
#include "rapidxml.hpp"

#include <fstream>

namespace Donut
{
	#define JSON_EXTENSION "json"
	#define XML_EXTENSION "xml"
	TSceneLoader::TSceneLoader()
	{

	}

	TSceneLoader::~TSceneLoader()
	{
		
	}
	TSceneFile::Type GetExtensionType(const std::string& _extension)
	{
		if(_extension == JSON_EXTENSION)
		{
			return TSceneFile::JSon;
		}
		else if(_extension == XML_EXTENSION)
		{
			return TSceneFile::Xml;
		}
		return TSceneFile::UNKNOWN;
	}

	TNode* HandleJsonFile(const std::string& _sceneFileName)
	{
		// Reading json file
		std::string jsonFile;
		ReadFile(_sceneFileName.c_str(), jsonFile);
		picojson::value v;
		std::string err = picojson::parse(v, jsonFile);
		ASSERT_MSG (err.empty(), "Failed reading json file "<<err); 

		return nullptr;
	}

	TNode* HandleXmlFile(const std::string& _sceneFileName)
	{
		// Reading json file
		std::vector<char> buffer;
		ReadFile(_sceneFileName.c_str(), buffer);
	    rapidxml::xml_document<> doc;
		doc.parse<0>(&buffer[0]);
		return nullptr;
	}

	TNode* TSceneLoader::LoadScene(const std::string& _sceneFileName)
	{
 		size_t stringLength = _sceneFileName.size();
 		const std::string& extension = _sceneFileName.substr(_sceneFileName.find_last_of(".") + 1, stringLength - 1);
 		TSceneFile::Type type = GetExtensionType(extension);
 		TNode* result = nullptr;
 		switch (type)
 		{
 			case TSceneFile::JSon:
 			{
 				RESOURCE_INFO("Opening json file "<<_sceneFileName);
 				result =  HandleJsonFile(_sceneFileName);
 			}
 			break;
  			case TSceneFile::Xml:
 			{
 				RESOURCE_INFO("Opening xml file "<<_sceneFileName);
 				result =  HandleXmlFile(_sceneFileName);
 			}
 			break;
 			default:
 				ASSERT_FAIL_MSG("Unsupported file type "<<extension);
 		}
		return result;
	}

}