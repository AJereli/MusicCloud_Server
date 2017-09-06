
#include <cstdlib>
#include "FilesController.h"
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using namespace std;

using boost::asio::ip::tcp;
namespace fs = boost::filesystem;
const int max_length = 2048;
void session(tcp::socket sock)
{
	try
	{
		std::cout << "new client\n";
		for (;;)
		{
			char data[max_length];

			boost::system::error_code error;
			size_t length = sock.read_some(boost::asio::buffer(data), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.
			std::cout.write(data, length);
			sock.write_some(boost::asio::buffer(data, length));
			boost::asio::write(sock, boost::asio::buffer(data, length));
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what()  << "\n";
	}
}

void sendSong(std::string name, tcp::socket & sock) {
	std::ifstream fin;
	std::ofstream fout("heh.mp3", std::ios_base::binary);
	fin.open(FilesController::getFilesController().dir + name, std::ios_base::binary);
	int currBits = 0;
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, fin.beg);
	while (currBits < length) {
		int currLen = 0;
		if (length - currBits < 2048)
			currLen = length - currBits;
		else
			currLen = 2048;
		std::unique_ptr<char[]> buffer(new char[currLen]);
		fin.read(buffer.get(), currLen);
		fout.write(buffer.get(), currLen);
		sock.write_some(boost::asio::buffer(buffer.get(), currLen));
		currBits += currLen;
		//std::cout << "Reading " << length << " characters... ";



	}

	fin.close();
}

void server(boost::asio::io_service& io_service, unsigned short port)
{
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
	std::cout << "Yep, server enable!\n";
	for (;;)
	{
		tcp::socket sock(io_service);
		a.accept(sock);
		std::thread(session, std::move(sock)).detach();
	}
}

int main()
{
	FilesController & lol = FilesController::getFilesController();
	thread([&lol]() { FilesController::getFilesController().work(); }).detach();
	try
	{
		

		boost::asio::io_service io_service;

		server(io_service, 2050);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}