
#include <iostream>

#include "db.hh"


int main(int argc, char *argv[])
{
    octetos::software::Conector conn("/home/azael/develop/octetos-software/src/db-test");
	octetos::software::Version ver;
	ver.selectByArtifact(conn,1);
	std::cout<< "Version : " << ver.toString() << std::endl;
	
    return 0;
}
