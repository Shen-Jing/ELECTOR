#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>



using namespace std;


void clean_msa( string& str1, string& str2, string& str3){
	string nstr1,nstr2,nstr3;
	uint pred(0);
	for(uint i(0);i<str2.size();++i){
		if(str2[i]=='n'){
			//~ cout<<"go"<<endl;
			nstr1+=str1.substr(pred,i-pred);
			nstr2+=str2.substr(pred,i-pred);
			nstr3+=str3.substr(pred,i-pred);
			pred=i+1;
		}
	}
	nstr1+=str1.substr(pred);
	nstr2+=str2.substr(pred);
	nstr3+=str3.substr(pred);
	str1=nstr1;
	str2=nstr2;
	str3=nstr3;
}


int main(int argc, char ** argv){
	if(argc<3){
		cout<<"[msa file in]  [msa file out]"<<endl;
		exit(0);
	}

	string input(argv[1]),output(argv[2]),ref, useless,acc1,acc2,acc3,header,cor,err;
	srand (time(NULL));
	ifstream in(input);

	if(not in.good() or in.eof()){
		//~ cout<<"Problem opening msa file to be compacted"<<endl;
		return 0;
	}
	ofstream out(output,ofstream::app);

	getline(in,useless);
	getline(in,ref);
	getline(in,useless);
	getline(in,err);
	getline(in,useless);
	getline(in,cor);
	acc1+=ref;
	acc2+=err;
	acc3+=cor;
	header=useless;

	while(not in.eof()){
		getline(in,useless);
		getline(in,ref);
		getline(in,useless);
		getline(in,err);
		getline(in,useless);
		getline(in,cor);
		if(header!=useless){
			if(acc1.size()>1){
				clean_msa(acc1,acc2,acc3);
				out<<header.substr(0, header.size()-11)<<" \n"<<acc1<<'\n';
				out<<header.substr(0, header.size()-11)<<" \n"<<acc2<<'\n';
				out<<header.substr(0, header.size()-11)<<" \n"<<acc3<<'\n';
				header=useless;
			}
			acc1=ref;
			acc2=err;
			acc3=cor;
		}else{
			acc1+=ref;
			acc2+=err;
			acc3+=cor;
		}
	}
	//~ if(acc1.size()>1){
		//~ out<<header<<'\n'<<acc1<<'\n';
		//~ out<<header<<'\n'<<acc2<<'\n';
		//~ out<<header<<'\n'<<acc3<<'\n';
		//~ header=useless;
		//~ acc1=acc2=acc3="";
	//~ }
	out.close();
}
