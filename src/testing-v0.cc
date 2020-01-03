#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

#include "db.hh"
#include "software.hh"


int main(int argc, char *argv[])
{
    
	octetos::core::Artifact packinfo = octetos::software::getPackageInfo();
	octetos::core::Semver& ver = packinfo.version;
	int majorDevelop = 0;
	if(majorDevelop != ver.getMajor())
	{
		std::cerr << "Este conjunto de pruebas estan Deseñado para la version mayor '" << majorDevelop << "'\n";
		return EXIT_FAILURE;
	}
	
    octetos::software::Conector conn("/home/azael/develop/octetos-software/src/db-test");
	//octetos::software::Version ver;
	//ver.selectByArtifact(conn,1);
	//std::cout<< "Version : " << ver.toString() << std::endl;

	int iSecret, iGuess;
	/* initialize random seed: */
	srand (time(NULL));

	/* generate secret number between 1 and 10: */
	iSecret = rand() % 10000 + 1;

	
	octetos::software::Version ver1;
	std::string ver1str = "1.2.3-alpha" ;
	if(ver1.insert(conn,ver1str))
	{
		std::cout << "Artefacto inserted.\n";
	}
	else
	{
		std::cout << "Version not inserted.\n";
	}
	
	
	octetos::software::Package pack;
	std::string packname = "packtest" ;
	packname += std::to_string(iSecret);
	if(pack.insert(conn,packname,ver1))
	{
		//pack.selectByName(conn,packname);
		std::cout << "Pack inserted " << pack.getID() << ".\n";
	}
	else
	{
		std::cout << "Pack not inserted.\n";
	}
	
		
	octetos::software::Artifact arti;
	std::string artiname = "artitest" ;
	artiname += std::to_string(iSecret);
	std::string strpath = "pathtest" ;
	strpath += "-" + std::to_string(iSecret);
	if(arti.insert(conn,ver1,strpath,&pack))
	{
		//arti.selectByFullPath(conn,strpath);
		std::cout << "Artefacto inserted.\n";
	}
	else
	{
		std::cout << "Artefacto not inserted.\n";
	}
	
	/*
	octetos::software::Artifact artidel(2);
	if(artidel.remove(conn))
	{
		std::cout << "Artefacto delete.\n";
	}
	*/

	octetos::software::Package packdel;
	if(packdel.selectByName (conn,"packtest5625"))
	{
		int id = packdel.getID();
		std::cout << "Package id = " << packdel.getID() << ".\n";
		if(packdel.remove(conn))
		{
			std::cout << "Elimiando  = " << id << ".\n";
		}		
	}
	else
	{
		std::cout << "Not selected package.\n";
	}
	
	
    return 0;
}
