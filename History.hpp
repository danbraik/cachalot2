#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <string>
#include <vector>

class History
{
	public:
		History(std::string filepath);
		~History();
		float getTime(std::string trackpath);
		void setTime(std::string trackpath, float value);
		std::string getLast();
	private:
		struct Track {
				std::string path;
				float value;
		};
		
		static const int MAX_TRACK = 1024;
		const std::string mFilepath;
		std::vector<Track> mData;
		std::vector<Track>::iterator it;
};

#endif // HISTORY_HPP
