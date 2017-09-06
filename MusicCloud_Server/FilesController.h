#pragma once
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <list>
#include <thread>
#include <chrono>
#include <fstream>

namespace fs = boost::filesystem;

class FilesController
{

private:  unsigned int currMusicCnt;
		  std::list<std::string> currMusicList;
		  std::unique_ptr<std::thread> work_thread;
		  
		 


		  FilesController();
		  FilesController(FilesController const&);
		  FilesController & operator=(FilesController&) = delete;

public:
	static FilesController & getFilesController();
	void work();
	std::string dir;
	~FilesController();

};

