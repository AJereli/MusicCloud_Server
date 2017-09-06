#include "FilesController.h"

 void FilesController::work()
{
	std::cout << "FilesController thread is work!;\n";
	fs::path dir_path(dir);

	try {
		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(20));
			unsigned int tmpMusicCnt = 0;
			for (fs::directory_iterator it(dir_path), end; it != end; ++it) {
				if (it->path().extension() == ".mp3")
					tmpMusicCnt++;
				if (tmpMusicCnt > currMusicCnt) {
					std::ifstream fin;
					//fin.open(it->path().filename().string());
					currMusicList.push_front(it->path().filename().string());
				std::cout << it->path().filename().string() + "\n";
				}
			}
			currMusicCnt = tmpMusicCnt;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
	std::cout << "FilesController thread off!;\n";

}

FilesController::FilesController()
{
	setlocale(LC_ALL, "Russian");
	dir = "./dir";
	fs::path dir_path(dir);
	fs::ifstream fin;
	for (fs::directory_iterator it(dir_path), end; it != end; ++it) {
		if (it->path().extension() == ".mp3") {
			currMusicCnt++;
			currMusicList.push_front(it->path().filename().string());
			
			currMusicList.push_front(it->path().filename().string());
			std::cout << it->path().filename().string() + "\n";
		}
	}
	
	
	std::cout << "Files controller enable, music file cnt: " << currMusicCnt << std::endl;
}

FilesController & FilesController::getFilesController()
{
	static FilesController fc;
	return fc;
}


FilesController::~FilesController()
{
}
