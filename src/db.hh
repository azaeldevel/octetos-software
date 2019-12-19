#ifndef TOOLKIT_COMMON_DB_HPP
#define TOOLKIT_COMMON_DB_HPP

#include <vector>


#include "version.hh"

namespace octetos
{
namespace software
{
	class Artifact;


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

    class Version : public octetos::core::Version
    {
	private:
        int id;        
        static int callbackByArtifact(void *data, int argc, char **argv, char **azColName);
        //static int callbackAll(void *data, int argc, char **argv, char **azColName);
        static int callbackFull(void *data, int argc, char **argv, char **azColName);
		
    public:
        bool selectByArtifact(Conector& conect, int artifact);
		//static bool selectAll(Conector& conect, std::vector<Version*>& vec);
		bool insert(Conector& conn,const std::string& strver);
		int getID()const;
		Version();
		Version(int);
		Version& operator=(int id);
        bool remove(Conector& conect);
        bool download(Conector& conect);
    }; 

	class Package
    {
	private:
        int id;  
		std::string name;
		std::string note;
		Version version;
      
        static int callbackByFullLine(void *data, int argc, char **argv, char **azColName);
        //static int callbackAll(void *data, int argc, char **argv, char **azColName);
		
    public:
        bool selectByName(Conector& conect, const std::string& name);
        //static bool selectAll(Conector& conect, std::vector<Package*>& vec);
		bool insert(Conector& conn, const std::string& name,const Version& version);
		int getID()const;
		bool deleteByName(Conector& conn, const std::string& name);
        bool remove(Conector& conect);
    };

        
	class Artifact
    {
	private:
        int id;  
		std::string name;
		std::string fullpath;
		Package* package;
		Version* version;
		
        static int callbackByArtifact(void *data, int argc, char **argv, char **azColName);
        //static int callbackAll(void *data, int argc, char **argv, char **azColName);
        static int callbackMultiline(void *data, int argc, char **argv, char **azColName);
		
    public:
        bool selectByFullPath(Conector& conect, const std::string& path);
        //static bool selectAll(Conector& conect, std::vector<Artifact*>& vec);
		bool insert(Conector& conn, const Version& version,const std::string& path, Package* package);
		int getID()const;
		bool deleteByPackage(Conector& conn, const Package& package);
        bool remove(Conector& conect);
		Artifact(int id);
		Artifact();
		bool getArtifacts(Conector& conect, std::vector<Artifact*>* artifacts);
    };   
    
}
}

#endif
