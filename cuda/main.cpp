// Copyright (c) 2016 Nicolas Weber and Sandra C. Amend / GCC / TU-Darmstadt. All rights reserved. 
// Use of this source code is governed by the BSD 3-Clause license that can be
// found in the LICENSE file.
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdint>

//-------------------------------------------------------------------
// SHARED
//-------------------------------------------------------------------
struct Params {
	uint32_t oWidth;
	uint32_t oHeight;
	uint32_t iWidth;
	uint32_t iHeight;
	float pWidth;
	float pHeight;
	float lambda;
};

//-------------------------------------------------------------------
// HOST
//-------------------------------------------------------------------
void run(const Params& i, const void* hInput, void* hOutput);

//-------------------------------------------------------------------
int main(int argc, char** argv) {
	// check if there are enough arguments
	if(argc != 5) {
		std::cout << "usage: dpid <image> <width> <height> <lambda>" << std::endl;
		exit(1);
	}
		
	// read params
	Params i = {0};
	i.oWidth			= (uint32_t)std::atoi(argv[2]);
	i.oHeight			= (uint32_t)std::atoi(argv[3]);
	i.lambda			= (float)	std::atof(argv[4]);
	const char* iName	= argv[1];

	// check params
	if(i.oWidth == 0 && i.oHeight == 0) {
		std::cerr << "only one dimension (width or height) can be 0!" << std::endl;
		exit(1);
	}

	// load image
	cv::Mat iImage	= cv::imread(iName);
	
	if(!iImage.data)  {
		std::cerr << "unable to read image" << std::endl;
		exit(1);
	}

	i.iWidth		= iImage.cols;
	i.iHeight		= iImage.rows;
	
	// calc width/height according to aspect ratio
	if(i.oWidth == 0)
		i.oWidth = (uint32_t)std::round((i.oHeight / (double)i.iHeight) * i.iWidth);

	if(i.oHeight == 0)
		i.oHeight = (uint32_t)std::round((i.oWidth / (double)i.iWidth) * i.iHeight);
	
	// alloc output
	cv::Mat oImage(i.oHeight, i.oWidth, CV_8UC3);

	// calc patch size
	i.pWidth	= i.iWidth  / (float)i.oWidth;
	i.pHeight	= i.iHeight / (float)i.oHeight;

	// run cuda
	run(i, iImage.data, oImage.data);
	
	// write image
	cv::imwrite("output.png", oImage);
	
	return 0;
}
