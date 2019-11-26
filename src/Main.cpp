#include <iostream>
#include "../include/Session.h"

using namespace std;

int main(int argc, char** argv){
	if(argc!=2)
	{
 		cout << "usage splflix input_file" << endl;
		return 0;
	}
	Session s(argv[1]);
	s.start();
    Session s2(argv[1]);
    s2 = s;
    s2.start();
//    Session s3 (s);
//    s3.start();
	return 0;
}
