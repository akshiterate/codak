#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main(){
	std::string fpath = "../family_frames/output_0001.ppm";
	std::string opath = "image.shit";

	std::ifstream file(fpath,std::ios::binary);
	if(!file){ 
		std::cerr<<"Oops!! i cant read the file!!"<<std::endl;
		return 1;
	}

	std::string magicNumber;
	file>>magicNumber;
	if(magicNumber != "P6"){
		std::cerr<<"Oops!! file format does not match"<<std::endl;
		return 1;
	}
	int w,h,v;
	file>>w>>h>>v;
	std::cout<<w<<" "<<h<<" "<<v<<std::endl;

	file.get(); // skips single channel whitespace adter max val
	std::vector<unsigned char> pixels(w*h*3);
	file.read(reinterpret_cast<char*>(pixels.data()),pixels.size());
	file.close();
	
	std::vector<float> yuv;
	for(size_t i=0;i<pixels.size();i+=3){
		float y = 0.299f * pixels[i] + 0.587f * pixels[i+1] + 0.114f *pixels[i+2];
 		float u = -0.168736f * pixels[i] - 0.331264f * pixels[i+1] + 0.500f * pixels[i+2] + 128.0f;
 		float v =  0.500f * pixels[i] - 0.418688f * pixels[i+1] - 0.081312f * pixels[i+2] + 128.0f;
		yuv.push_back(y);yuv.push_back(u);yuv.push_back(v);

	}
	
	std::ofstream ofile(opath,std::ios::binary);
	if(!ofile){
		std::cerr<<"Oops! there is no output file here!!"<<std::endl;
		return 1;
	}
	struct header{
		int w;
		int h;
		int v;
		long yuvSize;

	};
	header h1 = {w,h,v,yuv.size()*sizeof(float)};
	ofile.write(reinterpret_cast<char*>(&h1),sizeof(h1));
	ofile.write(reinterpret_cast<char*>(yuv.data()),yuv.size()*sizeof(float));
	std::cout<<"File has been written yayayay"<<std::endl;

	return 0;

}
