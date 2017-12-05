// Aibek Smagulov 20142028 smagulovaybek@gmail.com

#include "hashmap.h"
#include <iostream>
#include <fstream>

using namespace std;

/** 
  * Assignment 4 for CSE221 Data Structures
  *
  * 2016. 11. 8
  *
  */
  
HashMap<MapElem<string, string> > hashmap(35000);

void spellcheck(std::string s)
{
    if(hashmap.find(s) != NULL){
        cout << "> " << s << " is in the dictionary" << endl;
    }
    else{
        cout << "> " << s << " is NOT in the dictionary" << endl;
        string temp = s;
        cout << "> " << s << " : ";
        bool found = 0;
        for(int i = 0; i < s.length(); i++){
            for(int j = 0; j < 26; j++){
                temp[i] = (char)('a' + j);
                MapElem<string, string>* ptr = hashmap.find(temp);
                if(ptr != NULL){
                   if(found == 1) cout << ", ";
                   cout << ptr->val;
                   found = 1;
                }
            }
            temp[i] = s[i];
        }
        if(found == 0) cout << "no suggestion";
        cout << endl;
    }
}


int main()
{
	// load dictionary
	char filename[] = "dictionary.txt";
	std::ifstream ifs(filename, std::ifstream::in);
	std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	std::transform(s.begin(), s.end(),
				   s.begin(), ::tolower);

	std::string token;	
	unsigned int len = s.length();
	
    int size = 0;

    //HashMap<MapElem<int, string> > hashmap();

    for(int i=0; i<len; i++)
	{
		int ascii = s[i];
		
		if(ascii < 97 || ascii > 127) 
		{
			if(token.length() > 0) 
			{
				// ToDo
				// Insert token to hash map
			//	cout << token << endl;
                //const char* c = token.c_str();
                //cout << c << endl;
                hashmap.insert(token, token);
                size ++;
				token.clear();
			}
			continue;
		}
		token.push_back(s[i]);
	}
	
	//cout << size << endl;
	//
	// infinite loop to accept user input word
	//
	while(1)
	{
		std::string s;
		std::cout << "> ";
        std::cin >> s;
		if(s == "q") break;
		spellcheck( s );
		
	}
	
	
	return 0;
}
