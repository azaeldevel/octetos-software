#include "software.hh"
#include "version.hh"
#include "db.hh"


namespace octetos
{
namespace software
{


int CmdVersion::indexDelete(int argc, char *argv[])
{
    std::string pakagename(argv[1]);
    if(pakagename.empty())
    {
		//std::cout << "Pkg: " << pakagename << "\n";
    	//return indexAdd(argc-1,argv+1); 
		return EXIT_FAILURE;
    }	
	std::string strver = argv[2];
	octetos::software::Version v;
	if(!v.set(strver))
	{
		return EXIT_FAILURE;
	}

	octetos::software::Conector conn(dirdb);

	octetos::software::Package packdel;
	if(packdel.selectByName (conn,pakagename))
	{
		//int id = packdel.getID();
		//std::cout << "Package id = " << packdel.getID() << ".\n";
		if(packdel.getVersion() == v)
		{
			if(packdel.remove(conn))
			{
				std::cout << "Se elímino '" << pakagename << "'.\n";
			}	
		}
		else
		{
			std::cout << "No hay coincidencia del paquete '" << pakagename << "' con la version especificada.\n";
		}
	}
	else
	{
		conn.close();
		return EXIT_FAILURE;
	}
	
	conn.close();
	return EXIT_SUCCESS;
}
int CmdVersion::versioncmd(int argc, char *argv[])
{   
    octetos::core::Artifact packinfo = octetos::software::getPackageInfo();
    std::string str = "v";
	str += packinfo.version.toString() + " " + packinfo.name + "\n" ;
	str += packinfo.licence.getBrief() + "\n" + packinfo.brief + "\tContac:" + packinfo.licence.contact + "\n";        
    std::cout << str ;    
	
   	return EXIT_SUCCESS;
}

int CmdVersion::help(int argc, char *argv[])
{
	//5.3.2 --get-numbers-only --minimal=3.2 --target='test program'
	std::cout << "Use :\n";
	std::cout << "\tversion vertext [--minimal=minver] [--maximal=verver] [--target='reference text']\n";
	std::cout << "\tversion vertext --get-numbers-only\n";
	std::cout << "\tversion vertext [--major] [--minor] [--patch]\n";
	std::cout << "\tversion index add pakagename vertext artifac1 [artifact2 [artifact3 [..]]]\n";
	std::cout << "\tversion index delete pakagename vertext\n";
	
    return EXIT_SUCCESS;
}
int CmdVersion::indexAdd(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "\tversion index delete pakagename vertext\n";
		return EXIT_FAILURE;
	}
	
    std::string pakagename(argv[1]);
    if(pakagename.empty())
    {
		//std::cout << "Pkg: " << pakagename << "\n";
    	//return indexAdd(argc-1,argv+1); 
		return EXIT_FAILURE;
    }	
	std::string strver = argv[2];
	octetos::software::Version v;
	if(!v.set(strver))
	{
		return EXIT_FAILURE;
	}
	std::vector<std::string> arts;
	for(int i = 3; i < argc; i++)
	{
		arts.push_back(argv[i]);
		//std::cout << "Artifacts: " << argv[i] << "\n";
	}

	octetos::software::Conector conn(dirdb);

	octetos::software::Version ver;
	if(!ver.insert(conn,strver))
	{
		std::cerr << "Version not inserted.\n";
		conn.close();
		return EXIT_FAILURE;
	}
	
	octetos::software::Package pack;
	if(pack.selectByName(conn,pakagename))
	{
		if(pack.insert(conn,pakagename,ver))
		{
			pack.selectByName(conn,pakagename);
			//std::cout << "Pack inserted.\n";
		}
		else
		{
			std::cerr << "Pack not inserted.\n";
			conn.close();
			return EXIT_FAILURE;
		}
	}

	octetos::software::Artifact artifact;
	for(std::string strart : arts)
	{
		if(artifact.insert(conn,ver,strart,&pack))
		{
			artifact.selectByFullPath(conn,strart);
		}
		else
		{
			std::cerr << "Artefacto not inserted.\n";
			conn.close();
			return EXIT_FAILURE;
		}
	}

	conn.close();
    return EXIT_SUCCESS;
}
int CmdVersion::index(int argc, char *argv[])
{    
   	strOption = argv[1];
    //std::cout << "O: " << strOption << "\n";
    std::string addPrefix("add");
    int addPrefixIndex = strOption.compare(0, addPrefix.size(), addPrefix);
    if(!addPrefixIndex)
    {
    	return indexAdd(argc-1,argv+1);            
    }

    std::string deletePrefix("delete");
    int deletePrefixIndex = strOption.compare(0, deletePrefix.size(), deletePrefix);
    if(!deletePrefixIndex)
    {
    	return indexDelete(argc-1,argv+1);            
    }
	
	
    return EXIT_FAILURE;
}

int CmdVersion::pack(int argc, char *argv[])
{
    bool packcreateOption = false;
    std::string packcreateOptinVal;
    std::cout << "p: " << argv << "\n";
    std::cout << "str: " << argv[0] << "\n";
    for(int i = 0; i< argc; i++)
    {
        strOption = argv[i];
        //std::cout << "O: " << strOption << "\n";
        std::string packcreatePrefix("--create=");
        int createPrefixIndex = strOption.compare(0, packcreatePrefix.size(), packcreatePrefix);
        if(!createPrefixIndex)
        {
            packcreateOption = true;
            packcreateOptinVal = strOption.substr(packcreatePrefix.size());
            std::cout << "File:" << packcreateOptinVal << "\n";
        }
    }
    
    return EXIT_SUCCESS;
}

CmdVersion::CmdVersion()
{
    mininalOption = false;
    mininalOptionPass = false;
    mininalOptionEcho = false;
    maximalOption = false;
    maximalOptionPass = false;
    maximalOptionEcho = false;
    targetOption = false;
    packCommand = false;

	octetos::core::Artifact artifact = getPackageInfo();
	if(artifact.version.getStage() <= octetos_version_Stage::snapshot)
	{
		dirdb = "/etc/octetos/version/db";
	}
	else
	{
    	dirdb = "/home/azael/develop/octetos-software/src/db-test";
	}
}
int CmdVersion::base(int argc, char *argv[])
{
    int i = 1;    
    strOption = argv[i];  
    
    //es una operacion con version
    if(version.set(strOption))
    {
        for(i = 2; i< argc; i++)
        {
            strOption = argv[i];
			
			if(strOption.compare("--get-numbers-only") == 0)
			{
				std::cout <<  version.toString(octetos::core::Semver::Format::ONLY_NUMBERS) << "\n";
				return EXIT_SUCCESS;
			}
            
            if(strOption.compare("--major") == 0 or  strOption.compare("-M")==0)
            {
                std::cout <<  version.getMajor() << "\n";
            }
            if(strOption.compare("--minor") == 0 or  strOption.compare("-m")==0)
            {
                std::cout <<  version.getMinor() << "\n";
            }
            if(strOption.compare("--patch") == 0 or  strOption.compare("-p")==0)
            {
                std::cout <<  version.getPatch() << "\n";
            }
            
            std::string minimalOptionPrefix("--minimal=");
            int minmalIndex = strOption.compare(0, minimalOptionPrefix.size(), minimalOptionPrefix);
            if(!minmalIndex)
            {
                mininalOption = true;
                std::string strMin = strOption.substr(minimalOptionPrefix.size());
                //std::cout << "Minimal: " << strMin << "\n";
                octetos::core::Semver minversion;
                if(minversion.set(strMin))
                {                
                    if(minversion.getMajor() < 0 or minversion.getMinor() < 0 or minversion.getPatch() < 0)
                    {
                        std::cout<<"Advertencia: Especifique version con los tres componetes x.y.z, la falta de algun componete tiene un efecto sematico.\nhttps://semver.org/lang/es/";
                    }
                }
                else
                {
                    std::cerr << "Falló la lectura de la version '" << strMin << "\n";
                }
                if(minversion <= version)
                {
                    mininalOptionPass = true;
                    //std::cout << "true\n";
                }
                else
                {
                    mininalOptionPass = false;
                    //std::cout << "false\n";
                }
            }        
            std::string minimalOptionEchoPrefix("--minimal-echo=");
            int minmalEchoIndex = strOption.compare(0, minimalOptionEchoPrefix.size(), minimalOptionEchoPrefix);
            if(!minmalEchoIndex)
            {
                mininalOptionEcho = true;
                mininalOptionEchoStr = strOption.substr(minimalOptionEchoPrefix.size());
            }
            
            //std::cout << "step 1\n";
            std::string maximalOptionPrefix("--maximal=");
            int maximalIndex = strOption.compare(0, maximalOptionPrefix.size(), maximalOptionPrefix);
            if(!maximalIndex)
            {
                maximalOption = true;
                std::string strMax = strOption.substr(maximalOptionPrefix.size());
                //std::cout << "Maximal: " << strMin << "\n";
                octetos::core::Semver maxversion;
                if(maxversion.set(strMax))
                {   
                    if(maxversion.getMajor() < 0 or maxversion.getMinor() < 0 or maxversion.getPatch() < 0)
                    {
                        std::cout<<"Advertencia: Especifique version con los tres componetes x.y.z, la falta de algun componete tiene un efecto sematico.\nhttps://semver.org/lang/es/";
                    }
                }
                else
                {
                    std::cerr << "Falló la lectura de la version '" << strMax << "\n";
                }
                if(maxversion >= version)
                {
                    //std::cout << "true\n";
                    maximalOptionPass = true;
                }
                else
                {
                    //std::cout << "false\n";
                    maximalOptionPass = true;
                }
            }
            //std::cout << "step 2\n";
            std::string maximalOptionEchoPrefix("--maximal-echo=");
            int maximalEchoIndex = strOption.compare(0, maximalOptionEchoPrefix.size(), maximalOptionEchoPrefix);
            if(!maximalEchoIndex)
            {
                maximalOptionEcho = true;
                maximalOptionEchoStr = strOption.substr(maximalOptionEchoPrefix.size());
            }
            
            std::string targetOptionPrefix("--target=");
            int targetOptionIndex = strOption.compare(0, targetOptionPrefix.size(), targetOptionPrefix);
            if(!targetOptionIndex)
            {
                targetOption = true;
                targetOptionStr = strOption.substr(targetOptionPrefix.size());
            }
            
        }
    
        //std::cout << "step 3\n";
        if(mininalOption and mininalOptionEcho)
        {
            if(mininalOptionEcho && mininalOptionPass) 
            {
                std::cout << mininalOptionEchoStr << "\n";    
            }
            else if(mininalOptionPass) 
            {
                std::cout << "true\n";
            }
            else
            {
                std::cout << "false\n";
            }
            
            return EXIT_SUCCESS;
        }
        
        //std::cout << "step 4\n";
        if(maximalOption and maximalOptionEcho)
        {
            if(maximalOptionEcho && maximalOptionPass) 
            {
                std::cout << maximalOptionEchoStr << "\n";    
            }
            else if(maximalOptionPass) 
            {
                std::cout << "true\n";
            }
            else
            {
                std::cout << "false\n";
            }
            
            return EXIT_SUCCESS;
        }
        
        if(targetOption)
        {
            if(maximalOption and maximalOption)
            {
                if(mininalOptionPass and maximalOptionPass)
                {
                    std::cout << targetOptionStr << " " << version.toString() << " : pass\n";
                }
                else
                {
                    std::cout << targetOptionStr << " " << version.toString() << " : fail\n";
                }
            }
            else 
            {
                if(mininalOption)
                {
                    if(mininalOptionPass)
                    {
                        std::cout << targetOptionStr << " " << version.toString() << " : pass\n";
                    }
                    else
                    {
                        std::cout << targetOptionStr << " " << version.toString() << " : fail\n";
                    }
                }            
                
                if(maximalOption)
                {
                    if(maximalOptionPass)
                    {
                        std::cout << targetOptionStr << " " << version.toString() << " : pass\n";
                    }
                    else
                    {
                        std::cout << targetOptionStr << " " << version.toString() << " : fail\n";
                    }
                }
            } 
            
            return EXIT_SUCCESS;
        }
        
        strOption = argv[i]; 
        std::string packCommandStr("pack");
        int packCommandStrIndex = strOption.compare(0, packCommandStr.size(), packCommandStr);
        if(!packCommandStrIndex)
        {
            ///std::cout << "str:" << strOption << "\n";
            //std::cout << "pstr:" << strOption << "\n";
            packCommand = true;
            //std::cout << "p0:" << argv << "\n";
            //std::cout << "pi:" << argv + i << "\n";
            //std::cout << "argc:" << argc << "\n";
            //std::cout << "argc-i:" << argc-i << "\n";
            return pack(argc-i,argv+i);
        }
        
        
        strOption = argv[i]; 
        std::string indexCommandStr("index");
        int indexCommandStrIndex = strOption.compare(0, indexCommandStr.size(), indexCommandStr);
        if(!indexCommandStrIndex)
        {
            //std::cout << "str:" << strOption << "\n";
            //std::cout << "pstr:" << strOption << "\n";
            indexCommand = true;
            //std::cout << "p0:" << argv << "\n";
            //std::cout << "pi:" << argv + i << "\n";
            //std::cout << "argc:" << argc << "\n";
            //std::cout << "argc-i:" << argc-i << "\n";
            return index(argc-i,argv+i);
        }
        
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}




}
}


int main(int argc, char *argv[])
{	
    //int i = 1;    
	//std::cout << "argc = " << argc << "\n";
	std::string strOption = "";
	octetos::software::CmdVersion cmd;	
	if(argc == 1)
	{
		return cmd.versioncmd(argc,argv);
	}
	
	strOption = argv[1];
	if(strOption.compare("--version") == 0)
	{
		return cmd.versioncmd(argc,argv);
	}
	else if(strOption.compare("--help") == 0)
	{
		return cmd.help(argc,argv);
	}
	else if(strOption.compare("index") == 0)
	{
		return cmd.index(argc-1,argv+1);
	}
	else
	{		    
		return cmd.base(argc,argv);
	}
}
