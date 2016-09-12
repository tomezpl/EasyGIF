#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <curl/curl.h>
#include <crypto++/md5.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
#include <iostream>
#include <fstream>
std::string getFileMD5(const char*);
long getFileLength(const char*);
//Can modify User-Agent
//Gyazo ID
//filename
//Input file
//Proxy settings
void attempt2(){
	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl=curl_easy_init();
	if(curl){
		curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
		curl_easy_setopt(curl,CURLOPT_URL,"https://gyazo.com/upload.cgi");
		//curl_easy_setopt(curl,CURLOPT_PROXY,"http://localhost:8000");
		struct curl_slist *list=NULL;
		list=curl_slist_append(list,"User-Agent: toooootaaalllygaaaygaaygaaaaaaaaaaaaay");
		list=curl_slist_append(list,"Expect: ");
		list=curl_slist_append(list,"Connection: Close");
		curl_easy_setopt(curl,CURLOPT_HTTPHEADER,list);
		//Forms
		struct curl_httppost* post=NULL;
		struct curl_httppost* last=NULL;
		char idbuffer[]="afbc8928213ceeafeb1a9a0ebfb1aec5";
		long idlength=strlen(idbuffer);
		curl_formadd(&post,&last,CURLFORM_COPYNAME,"id",CURLFORM_PTRCONTENTS,idbuffer,CURLFORM_END);
		curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,"idfk.gif",CURLFORM_CONTENTTYPE,"image/*",CURLFORM_FILENAME,"testfilename",CURLFORM_END);
		//Perform
		curl_easy_setopt(curl,CURLOPT_HTTPPOST,post);
		res=curl_easy_perform(curl);
		std::cout<<res<<std::endl;
		if(res!=CURLE_OK){
			curl_easy_strerror(res);
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

int main(int argc,char *argv[]){
	//std::cout<<"File Length: "<<getFileLength("dc.png")<<std::endl<<"File MD5: "<<getFileMD5("dc.png")<<std::endl;
	attempt2();
	return 0;
	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl=curl_easy_init();
	if(curl){
		struct curl_httppost* post=NULL;
		struct curl_httppost* last=NULL;

		char namebuffer[] = "name buffer";
		long namelength = strlen(namebuffer);
		char buffer[] = "test buffer";
		char htmlbuffer[] = "<HTML>test buffer</HTML>";
		long htmlbufferlength = strlen(htmlbuffer);
		struct curl_forms forms[3];
		char file1[] = "dc.png";
		char file2[] = "colin.png";
		/* add null character into htmlbuffer, to demonstrate that
		transfers of buffers containing null characters actually work
		*/
		htmlbuffer[8] = '\0';

		/* Add simple name/content section */
		//curl_formadd(&post, &last, CURLFORM_COPYNAME, "name",CURLFORM_COPYCONTENTS, "content", CURLFORM_END);
		/* Add simple name/content/contenttype section */
		//curl_formadd(&post, &last, CURLFORM_COPYNAME, "htmlcode",CURLFORM_COPYCONTENTS, "<HTML></HTML>",CURLFORM_CONTENTTYPE, "text/html", CURLFORM_END);
		/* Add name/ptrcontent section */
		//curl_formadd(&post, &last, CURLFORM_COPYNAME, "name_for_ptrcontent",CURLFORM_PTRCONTENTS, buffer, CURLFORM_END);
		/* Add ptrname/ptrcontent section */
		//curl_formadd(&post, &last, CURLFORM_PTRNAME, namebuffer,CURLFORM_PTRCONTENTS, buffer, CURLFORM_NAMELENGTH,namelength, CURLFORM_END);
		/* Add name/ptrcontent/contenttype section */
		//curl_formadd(&post, &last, CURLFORM_COPYNAME, "html_code_with_hole",CURLFORM_PTRCONTENTS, htmlbuffer,CURLFORM_CONTENTSLENGTH, htmlbufferlength,CURLFORM_CONTENTTYPE, "text/html", CURLFORM_END);

		/* Add simple file section */
		//curl_formadd(&post, &last, CURLFORM_COPYNAME, "picture", CURLFORM_FILE, "dc.png", CURLFORM_END);

		/* Add file/contenttype section */
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "picture",
				  CURLFORM_FILE, "dc.png",
				  CURLFORM_CONTENTTYPE, "image/png", CURLFORM_END);

		/* Add two file section */
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "pictures",
				  CURLFORM_FILE, "colin.png",
				  CURLFORM_FILE, "dc.png", CURLFORM_END);

		/* Add two file section using CURLFORM_ARRAY */
		forms[0].option = CURLFORM_FILE;
		forms[0].value  = file1;
		forms[1].option = CURLFORM_FILE;
		forms[1].value  = file2;
		forms[2].option  = CURLFORM_END;

		/*
		curl_formadd(&post, &last,
				  CURLFORM_COPYNAME, "name",
				  CURLFORM_BUFFER, "data",
				  CURLFORM_BUFFERPTR, record,
				  CURLFORM_BUFFERLENGTH, record_length,
				  CURLFORM_END);
		*/
		/* no option needed for the end marker */
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "pictures",
				  CURLFORM_ARRAY, forms, CURLFORM_END);
		/* Add the content of a file as a normal post text value */
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "filecontent",
				  CURLFORM_FILECONTENT, "md5test.txt", CURLFORM_END);
		/* Set the form info */
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
		curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
		curl_easy_setopt(curl,CURLOPT_URL,"http://gyazo.com/upload.cgi");
		curl_easy_setopt(curl,CURLOPT_PROXY,"http://localhost:8000");
		res=curl_easy_perform(curl);
		std::cout<<res<<std::endl;
		curl_easy_strerror(res);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return 0;
}

std::string getFileMD5(const char *filename){
	std::string digest;
	CryptoPP::Weak::MD5 hash;
	CryptoPP::FileSource(filename,true,new CryptoPP::HashFilter(hash,new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
	return digest;
}
long getFileLength(const char *filename){
	std::ifstream is(filename,std::ifstream::binary);
	if(is){
		is.seekg(0,is.end);
		long len=is.tellg();
		is.seekg(0,is.beg);
		is.close();
		return len;
	}
	return -1;
}
