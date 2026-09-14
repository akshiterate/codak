#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

int main(){
	std::ifstream file("image.shit",std::ios::binary);
	if(!file){
		std::cerr<<"whoops, file not found"<<std::endl;
		return 1;
	}
	struct header{
		int w;
		int h;
		int v;
		long yuvSize;
	};
	header h1;
	file.read(reinterpret_cast<char*>(&h1),sizeof(h1));
	std::vector<float> yuv(h1.yuvSize);
	file.read(reinterpret_cast<char*>(yuv.data()),h1.yuvSize*sizeof(float));
	std::vector<unsigned char> rgb;
	for(int i=0;i<yuv.size();i+=3){
		int r = (int)std::roundf(yuv[i] + 1.402f * (yuv[i+2] - 128.0f));
		int g = (int)std::roundf(yuv[i] - 0.344136f * (yuv[i+1] - 128.0f) - 0.714136f * (yuv[i+2] - 128.0f));
		int b = (int)std::roundf(yuv[i] + 1.772f * (yuv[i+1] - 128.0f));
		rgb.push_back(r);rgb.push_back(g);rgb.push_back(b);
	}
	std::ofstream ofile("output.ppm",std::ios::binary);
	if(!ofile){
		std::cerr<<"Sir, the output file doesnt exist"<<std::endl;
		return 1;
	}
	ofile<<"P6\n"<<h1.w<<" "<<h1.h<<"\n"<<h1.v<<"\n";
	ofile.write(reinterpret_cast<const char*>(rgb.data()),rgb.size());
	return 0;
	
	
}
