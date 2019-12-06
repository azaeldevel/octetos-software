#ifndef TOOLKIT_COMMON_DB_HPP
#define TOOLKIT_COMMON_DB_HPP

#include "version.hh"

namespace octetos
{
namespace software
{
    class Conector
    {
    private:
        void* serverConnector;
    public:
        Conector(const std::string&);
        ~Conector();
        bool query(const std::string&,int (*callback)(void*,int,char**,char**),void* obj);
        void* getServerConnector();
    };

	class Package
    {
	private:
        int id;  
		std::string name;
		std::string note;
      
        static int callbackByPackage(void *data, int argc, char **argv, char **azColName);
        static int callbackAll(void *data, int argc, char **argv, char **azColName);
			
    public:
        bool selectByPackage(Conector& conect, int artifact);
        static bool selectAll(Conector& conect, std::vector<Package*>& vec);
		bool insert(Conector& conn, const std::string& name);
    };
        
    class Version : public octetos::core::Version
    {
	private:
        int id;        
        static int callbackByArtifact(void *data, int argc, char **argv, char **azColName);
        static int callbackAll(void *data, int argc, char **argv, char **azColName);
			
    public:
        bool selectByArtifact(Conector& conect, int artifact);
        static bool selectAll(Conector& conect, std::vector<Version*>& vec);
		bool insert(Conector& conn, const std::string& sql);
    };    
    
}
}

#endif
