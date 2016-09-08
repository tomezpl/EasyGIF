#include "../sec/b64.hpp"
#include <string>
#include <iostream>
using namespace std;
int main(){
	string test="LOTSA STUFF IS GR8 4 U";
	cout<<"Full test string = "<<test<<endl;
	const char* steponu=test.c_str();
	int len=test.length();
	//cout<<"Test "<<i<<" = "<<EasyGIF::Conversion::Base64_Encode(steponu,6)<<endl;
	std::string stuff=EasyGIF::Conversion::Base64_Encode(test,false);
	cout<<"Base64 Encoded = "<<stuff<<endl;
	int syze;
	std::string decoded=EasyGIF::Conversion::Base64_DecodeString(stuff);
	cout<<"Base64 Decoded = "<<decoded<<endl;
	return 0;
}
