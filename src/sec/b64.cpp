	#include "b64.hpp"
#include <iostream>
namespace EasyGIF{
	namespace Conversion{
		const char base64_alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
		//Gets the length of the B64 string from input data length
		int Base64_StringLength(int byte_size){int count=byte_size/3;if(byte_size%3>0){count++;}return count*4;}
		int Base64_PaddingLength(int byte_size){
			int b=byte_size%3;
			if(b==0 || b==3){return 0;}
			else if(b==1){return 2;}
			else{return 1;}
		}
		int Base64_DataLength(int b64_stringlen,int padding_length){return ((b64_stringlen*3)/4) - padding_length;}
		//Gets the length of the Binary Data from the B64 string
		int Base64_StringLength(std::string b64_string){
			if(b64_string.length()%4!=0){return -1;}
			int len=(b64_string.length()*3)/4;
			len-=b64_string.find("=")>0?(b64_string.length()-b64_string.find("=")):0;
			return len;
		}
		int Base64_ConvertCharToInt(char c){
			switch(c){
				case 'A':return 0;
				case 'B':return 1;
				case 'C':return 2;
				case 'D':return 3;
				case 'E':return 4;
				case 'F':return 5;
				case 'G':return 6;
				case 'H':return 7;
				case 'I':return 8;
				case 'J':return 9;
				case 'K':return 10;
				case 'L':return 11;
				case 'M':return 12;
				case 'N':return 13;
				case 'O':return 14;
				case 'P':return 15;
				case 'Q':return 16;
				case 'R':return 17;
				case 'S':return 18;
				case 'T':return 19;
				case 'U':return 20;
				case 'V':return 21;
				case 'W':return 22;
				case 'X':return 23;
				case 'Y':return 24;
				case 'Z':return 25;
				case 'a':return 26;
				case 'b':return 27;
				case 'c':return 28;
				case 'd':return 29;
				case 'e':return 30;
				case 'f':return 31;
				case 'g':return 32;
				case 'h':return 33;
				case 'i':return 34;
				case 'j':return 35;
				case 'k':return 36;
				case 'l':return 37;
				case 'm':return 38;
				case 'n':return 39;
				case 'o':return 40;
				case 'p':return 41;
				case 'q':return 42;
				case 'r':return 43;
				case 's':return 44;
				case 't':return 45;
				case 'u':return 46;
				case 'v':return 47;
				case 'w':return 48;
				case 'x':return 49;
				case 'y':return 50;
				case 'z':return 51;
				case '0':return 52;
				case '1':return 53;
				case '2':return 54;
				case '3':return 55;
				case '4':return 56;
				case '5':return 57;
				case '6':return 58;
				case '7':return 59;
				case '8':return 60;
				case '9':return 61;
				case '+':return 62;
				case '/':return 63;
				default:return 64;
			}
		}
		//Nicked from the Base64 Wikipedia page
		std::string Base64_Encode(const char* in,int length){
			int b64len=Base64_StringLength(length);
			std::string b64_encoded (b64len,'=');
			int b;
			int spos=0;
			for(int i=0;i<length;i+=3){
				b=(in[i]&0xFC)>>2;
				b64_encoded[spos++]=base64_alphabet[b];
				b=(in[i]&0x03)<<4;
				if(i+1<length){
					b|=(in[i+1]&0xF0)>>4;
					b64_encoded[spos++]=base64_alphabet[b];
					b=(in[i+1]&0x0F)<<2;
					if(i+2<length){
						b|=(in[i+2]&0xC0)>>6;
						b64_encoded[spos++]=base64_alphabet[b];
						b=in[i+2]&0x3F;
						b64_encoded[spos++]=base64_alphabet[b];
					}else{b64_encoded[spos++]=base64_alphabet[b];}
				}else{b64_encoded[spos++]=base64_alphabet[b];}
			}
			return b64_encoded;
		}
		std::string Base64_Encode(std::string str,bool include_null){return Base64_Encode(str.c_str(),str.length()+include_null);}
		std::string Base64_Encode(std::string str){return Base64_Encode(str.c_str(),str.length());}
		char* Base64_Decode(std::string b64_string,int* b64_size,bool add_null){
			int b64len=b64_string.length();
			int len=Base64_StringLength(b64_string)+add_null;
			*b64_size=len;
			char* data=new char[len];
			int i=0;
			int b[4];
			for(int i2=0;i2<b64len;i2+=4){			
				b[0]=Base64_ConvertCharToInt(b64_string[i2]);
				b[1]=Base64_ConvertCharToInt(b64_string[i2+1]);
				b[2]=Base64_ConvertCharToInt(b64_string[i2+2]);
				b[3]=Base64_ConvertCharToInt(b64_string[i2+3]);
				data[i++]=(char)((b[0]<<2)|(b[1]>>4));
				if(b[2]<64){
					data[i++]=(char)((b[1]<<4)|(b[2]>>2));
					if(b[3]<64){data[i++]=(char)((b[2]<<6)|b[3]);}
				}
			}
			if(add_null){data[i]='\0';}
			return data;
		}
		char* Base64_Decode(std::string b64_string,int* b64_size){return Base64_Decode(b64_string,b64_size,false);}
		std::string Base64_DecodeString(std::string b64_string){
			int len;
			char* decoded=Base64_Decode(b64_string,&len,false);
			std::string dec ((const char*)decoded,len);
			delete[] decoded;
			return dec;
		}
	}
}
