#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <sys/mman.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <cstdio>
#include <cerrno>
#include <streambuf>

using namespace std;

int read_by_ifstream(string filename){
	int start = clock();
	std::ifstream ifs(filename.c_str(), std::ios::binary);
	std::vector<char> buffer;
	buffer.resize(ifs.seekg(0, std::ios::end).tellg());
	ifs.seekg(0, std::ios::beg);
	ifs.read( &buffer[0], static_cast<std::streamsize>(buffer.size()) );
	ifs.close();

	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
	return 0;	
}

// int stl_stream_read(string filename){
// 	int start = clock();
// 	ifstream inputFile(filename.c_str());
// 	string fileData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

// 	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);

// 	return 0;
// }

void mmap_read(string filename)
{
	int MAXN = 10000000;
	int MAXS = 60*1024*1024;

	int numbers[MAXN];
	int start = clock();
	int fd = open(filename.c_str(),O_RDONLY);
	int len = lseek(fd,0,SEEK_END);
	char *mbuf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0);
	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
}

int read_fopen(string filename)
{
	int start = clock();
	std::FILE *fp = std::fopen(filename.c_str(), "rb");
	if (fp)
	{
	std::string contents;
	std::fseek(fp, 0, SEEK_END);
	contents.resize(std::ftell(fp));
	std::rewind(fp);
	std::fread(&contents[0], 1, contents.size(), fp);
	std::fclose(fp);
	}

	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);

	return 0;
}

int read_by_istreambuf_iterator(string filename)
{
	int start = clock();
	std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
	if (in)
	{
		std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	}

	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);

	return 0;
}

int read_by_ifstream_istreambuf_iterator_assign(string filename)
{
	int start = clock();
	std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
	if (in)
	{
	std::string contents;
	in.seekg(0, std::ios::end);
	contents.reserve(in.tellg());
	in.seekg(0, std::ios::beg);
	contents.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	in.close();
	}
	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}

int read_by_ifstream_istreambuf_iterator_copy(string filename)
{
	int start = clock();
	std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.reserve(in.tellg());
		in.seekg(0, std::ios::beg);
		std::copy((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>(), std::back_inserter(contents));
		in.close();
	}

	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);

	return 0;
}

int read_by_ifstream_rebuf(string filename)
{
	int start = clock();
	std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
	if (in)
	{
		std::ostringstream contents;
		contents << in.rdbuf();
		in.close();
	}
	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}

int main()
{
	string filename = "./data/bigfile.txt";

    read_by_ifstream(filename); 

    read_by_ifstream_rebuf(filename);

    read_by_ifstream_istreambuf_iterator_copy(filename);
}