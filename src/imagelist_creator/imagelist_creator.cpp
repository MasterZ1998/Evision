// (sample) imagelist_creator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

using namespace cv;

static void help(char** av)
{
	cout << "\n创建记录文件列表的yaml或xml文件\n"
		"用法: 程序名 输出文件名 待序列化文件名1 待序列化文件名2 ..."
		"usage:\n./" << av[0] << " imagelist.yaml *.png\n"
		<< "可以使用多种扩展名(e.g. yaml yml xml xml.gz etc...)\n"
		<< "本程序可以使用OpenCV的FileStorage framework 序列化一组图片或者任何其他东西" << endl;
}

int main(int ac, char** av)
{
	cv::CommandLineParser parser(ac, av, "{help h||}{@output||}");
	if (parser.has("help"))
	{
		help(av);
		return 0;
	}
	string outputname = parser.get<string>("@output");

	if (outputname.empty())
	{
		help(av);
		return 1;
	}

	Mat m = imread(outputname); //check if the output is an image - prevent overwrites!
	if (!m.empty()) {
		std::cerr << "fail! Please specify an output file, don't want to overwrite you images!" << endl;
		help(av);
		return 1;
	}

	FileStorage fs(outputname, FileStorage::WRITE);
	fs << "images" << "[";
	for (int i = 2; i < ac; i++) {
		fs << string(av[i]);
	}
	fs << "]";
	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
