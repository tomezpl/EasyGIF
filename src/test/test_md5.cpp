#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <crypto++/md5.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
std::string getFileMD5(const char *);
int main(int argc,char* argv[]){
	/*
	byte digest[ CryptoPP::Weak::MD5::DIGESTSIZE ];
	string message = "abcdefghijklmnopqrstuvwxyz";

	CryptoPP::Weak::MD5 hash;
	hash.CalculateDigest( digest, (const byte*)message.c_str(), message.length() );

	CryptoPP::HexEncoder encoder;
	string output;

	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();

	cout << output << endl;
	*/
	//getMD5File("./md5test.txt");
	for(int i=0;i<argc;i++){
		std::cout<<argv[i]<<std::endl;	
	}
	return 0;
}
std::string getFileMD5(const char *filename){
	std::string digest;
	CryptoPP::Weak::MD5 hash;
	CryptoPP::FileSource(filename,true,new CryptoPP::HashFilter(hash,new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
	return digest;
}
/*
DON'T YOU FORGET ABOUT ME
Fuk knows y dis don't work
std::string getMD5File(std::string filename){
	char * buffer =new char[1024];
	std::ifstream is("md5test.txt",std::ifstream::binary);
	CryptoPP::Weak::MD5 hash;
	byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];
	std::string output;
	if(is){
		is.seekg(0,is.end);
		unsigned long length=is.tellg();
		is.seekg(0,is.beg);
		std::cout<<"The file is "<<length<<" bytes long"<<std::endl;
		unsigned long pos=0;
		do{
			is.read(buffer,1024);
			std::cout<<"Read "<<is.gcount()<<" bytes"<<std::endl;
			hash.CalculateDigest(digest,(const byte*)buffer,is.gcount());
		}while(is.good());
		is.close();
		CryptoPP::HexEncoder encoder;
		encoder.Attach(new CryptoPP::StringSink(output));
		encoder.Put(digest,sizeof(digest));
		encoder.MessageEnd();
		std::cout<<"MD5 = "<<output<<std::endl;
		output="";
	}else{
		std::cout<<"PROBLEMS"<<std::endl;
		return "\0"; 
	}
	delete[] buffer;
	return "\0";
}
*/
