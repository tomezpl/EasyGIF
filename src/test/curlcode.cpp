//std::cout<<"File Length: "<<getFileLength("dc.png")<<std::endl<<"File MD5: "<<getFileMD5("dc.png")<<std::endl;
	const char filename[]="~/git/projects/EasyGIF/build/bin/dc.png\0";
	CURL *curl;
	int still_running;
	struct curl_httppost *formpost=NULL;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl=curl_easy_init();
	curl_off_t test_len=3;
	std::cout<<"Test len "<<test_len<<std::endl;
	if(curl){
		struct curl_httppost* post=NULL;
		struct curl_httppost* last=NULL;
		std::string ferlnem2="tmp498185126tmp";
		std::string content_type="image/*";
		char gyazoid[]="zfbc8928213ceeaeeb1a9a0ebfb1aec5";
		curl_formadd(&post,&last,CURLFORM_COPYNAME,"id",CURLFORM_PTRCONTENTS,gyazoid,CURLFORM_CONTENTLEN,0,CURLFORM_END);
		curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_CONTENTTYPE,"image/*",CURLFORM_CONTENTLEN,25,CURLFORM_FILE,"dc.png",CURLFORM_END);
		curl_off_t filelength=(curl_off_t)getFileLength("dc.png");
		//curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILENAME,"",CURLFORM_CONTENTTYPE,"image/*",CURLFORM_CONTENTSLENGTH,getFileLength("dc.png"),CURLFORM_FILECONTENT,"dc.png",CURLFORM_END);
		
		curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
		curl_easy_setopt(curl,CURLOPT_URL,"http://gyazo.com/upload.cgi");
		//curl_easy_setopt(curl,CURLOPT_PROXY,"http://localhost:8000");
		struct curl_slist *list=NULL;
		list=curl_slist_append(list,"User-Agent: meerikey");
		list=curl_slist_append(list,"Expect: ");
		list=curl_slist_append(list,"Connection: Keep-Alive");
		curl_easy_setopt(curl,CURLOPT_HTTPHEADER,list);
		curl_easy_setopt(curl,CURLOPT_HTTPPOST,post);
		/* Perform the request, res will get the return code */ 
		//res = curl_easy_perform(curl);
		/* Check for errors */ 
		/*if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		}

		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
