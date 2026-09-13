#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main(){
	std::string fpath = "../family_frames/output_0001.ppm";
	std::string opath = "output.ppm";

	std::ifstream file(fpath,std::ios::binary);
	if(!file){ 
		std::cerr<<"Oopsie Poopsie!! i cant read the file!!"<<std::endl;
		return 1;
	}

	std::string magicNumber;
	file>>magicNumber;
	if(magicNumber != "P6"){
		std::cerr<<"Oopsie Poopsie!! file format is gayyyyy"<<std::endl;
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
	
	return 0;

}
