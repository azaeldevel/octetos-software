#ifndef COTETOS_SOFTWARE_VERSION_HH
#define COTETOS_SOFTWARE_VERSION_HH

#include <iostream>

#include <octetos/core/common.hh>


namespace octetos
{
namespace software
{
    
class CmdVersion
{
private:
    std::string dirdb;    
    std::string strOption;
    octetos::core::Version version;
    bool mininalOption;
    bool mininalOptionPass;
    bool mininalOptionEcho;
    std::string mininalOptionEchoStr;
    bool maximalOption;
    bool maximalOptionPass;
    bool maximalOptionEcho;
    std::string maximalOptionEchoStr;
    bool targetOption;
    std::string targetOptionStr;
    bool packCommand;
    bool indexCommand;
        
public:
    int base(int argc, char *argv[]); 
    int pack(int argc, char *argv[]);  
    int index(int argc, char *argv[]);
	int indexAdd(int argc, char *argv[]);
	int indexDelete(int argc, char *argv[]);
	int help(int argc, char *argv[]);
	int versioncmd(int argc, char *argv[]);
    CmdVersion();
};
    
}
}

#endif
