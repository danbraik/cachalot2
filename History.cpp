#include <fstream>
#include <stdlib.h>
#include <iostream>

#include "History.hpp"



History::History(std::string filepath)
	: mFilepath(filepath), mData()
{
	std::ifstream file(mFilepath.c_str());
	
	if (file) {
		std::string line;
		
		while (getline(file, line)) {
			if (line.size() == 0)
				continue;
			
			char trackpath[2048];
			float value;
			const char * cstring = line.c_str();
			
			sscanf(cstring, "%f", &value);
			
			int i = 0;
			while (cstring[i] != ' ' && cstring[i] != '\0')
				++i;
			
			if (cstring[i] == ' ')
				++i;
			
			sprintf(trackpath, "%s", &(cstring[i]));
			
			
			Track track;
			track.path = std::string(trackpath);
			track.value = value;
			
			mData.push_back(track);
		}
	} else {
		std::cerr << "Warning : can't open file in reading mode '" << mFilepath << "'." << std::endl;
	}
	
}

History::~History()
{
	std::ofstream file(mFilepath.c_str());
	
	if (file) {
		for(it = mData.begin(); it != mData.end() ; ++it)
			file << (*it).value << " " << (*it).path << std::endl;
		
	} else {
		std::cerr << "Error : can't write file : '" << mFilepath << "'." << std::endl;
	}
}

float History::getTime(std::string trackpath)
{
	for(it = mData.begin(); it != mData.end() ; ++it)
		if ((*it).path == trackpath)
			return (*it).value;
	
	return 0.0f;
}

void History::setTime(std::string trackpath, float value)
{
	for(it = mData.begin(); it != mData.end() ; ++it) {
		if ((*it).path == trackpath) {
			//(*it).value = value;
			it=mData.erase(it);
			break;
		}
	}
	
	if (mData.size() >= MAX_TRACK)
		mData.erase(mData.begin());
	
	Track track;
	track.path = trackpath;
	track.value = value;
	
	mData.push_back(track);
}

std::string History::getLast()
{
	if (mData.size() == 0)
		return std::string();
	
	return mData.at(mData.size()-1).path;
}
