variables=[("upload_id","id"),"title","description","datetime","type","animated","width","height","size","views","bandwidth","vote",("favourite","favorite"),"nsfw","section","account_url","account_id","is_ad","in_gallery",("delete_hash","deletehash"),"name","link"]
def getVarString(vars,newline="\r\n",data_variable="d",uploaded_variable="comp"):return newline.join(["if({0}.count(\"{1}\")>0&&!{0}[\"{1}\"].is_null()){{{2}->{3}={0}[\"{1}\"];}}".format(data_variable,v if type(v)==str else v[1],uploaded_variable,v if type(v)==str else v[0]) for v in vars])
with open("gen.txt",'w')as out:
	out.write(getVarString(variables))
