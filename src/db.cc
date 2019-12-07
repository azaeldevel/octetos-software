#include "db.hh"

#include <stdio.h>
#include <sqlite3.h> 

#include "db.hh"


namespace octetos
{
namespace software
{
	int Artifact::getID()const
	{
		return id;
	}
	bool Artifact::insert(Conector& conn, const Version& version,const std::string& path, Package* package)
	{
		std::string sql = "INSERT INTO artifact(version,package,fullpath) values (";
		sql += "'" + std::to_string(version.getID()) + "','" + std::to_string(package->getID())+ "','" + path + "')";
		//std::cout << "SQL : " << sql << "\n";
		if(conn.query(sql,callbackByArtifact,this))
        {
			id = sqlite3_last_insert_rowid((sqlite3*)conn.getServerConnector());
            return true;
        }
			
        return false;
	}	
	bool Artifact::selectAll(Conector& conect, std::vector<Artifact*>& vec)
    {
        std::string sql = "SELECT id,fullpath,version,package FROM version";
        if(conect.query(sql,callbackAll,&vec))
        {
            return true;
        }
			
        return false;
    }			
    int Artifact::callbackAll(void *obj, int argc, char **argv, char **azColName)
    {
        std::vector<Artifact*>* lst = (std::vector<Artifact*>*)obj;
        Artifact* p = new Artifact();
        p->id = std::atoi(argv[0]);
        lst->push_back(p);
        return 0;
    }
    int Artifact::callbackByArtifact(void *obj, int argc, char **argv, char **azColName)
    {
        Artifact* p = (Artifact*)obj;	
        p->id = std::atoi(argv[0]);
        
        return 0;
    }
    bool Artifact::selectByArtifact(Conector& connect, const std::string& path)
    {
        std::string sql = "SELECT id FROM artifact WHERE fullpath = '";
        sql = sql + path + "'";
		//std::cout << "SQL : " << sql << "\n";
        if(connect.query(sql,callbackByArtifact,this))
        {
            return true;
        }
			
        return false;
    }




	



	
	int Package::getID()const
	{
		return id;
	}
	bool Package::insert(Conector& conn, const std::string& name,const Version& version)
	{
		std::string sql = "INSERT INTO package(name,version) values (";
		sql += "'" + name + "','" + std::to_string(version.getID()) + "')";
		//std::cout << "SQL : " << sql << "\n";
		if(conn.query(sql,callbackByPackage,this))
        {
			id = sqlite3_last_insert_rowid((sqlite3*)conn.getServerConnector());
            return true;
        }
		
		id = -1;
        return false;
	}	
	bool Package::selectAll(Conector& conect, std::vector<Package*>& vec)
    {
        std::string sql = "SELECT id,name,version FROM version";
        if(conect.query(sql,callbackAll,&vec))
        {
            return true;
        }
			
        return false;
    }			
    int Package::callbackAll(void *obj, int argc, char **argv, char **azColName)
    {
        std::vector<Package*>* lst = (std::vector<Package*>*)obj;
        Package* p = new Package();
        p->id = std::atoi(argv[0]);
        p->name = argv[1];
		p->version = std::atoi(argv[2]);
		
        lst->push_back(p);
        return 0;
    }
    int Package::callbackByPackage(void *obj, int argc, char **argv, char **azColName)
    {
        Package* p = (Package*)obj;	
        p->id = std::atoi(argv[0]);
        p->name = argv[1];
		p->version = std::atoi(argv[2]);	
        
        return 0;
    }
    bool Package::selectByName(Conector& connect, const std::string name)
    {
        std::string sql = "SELECT id,name,version FROM package WHERE name = '";
        sql = sql + name + "' ORDER BY id DESC LIMIT 1 ";
        if(connect.query(sql,callbackByPackage,this))
        {
            return true;
        }
			
        return false;
    }




	

	Version::Version()
	{
		id = -1;
	}
	Version::Version(int id)
	{
		this->id = id;
	}
	int Version::getID()const
	{
		return id;
	}
	bool Version::insert(Conector& conn,const std::string& strver)
	{
		if(!from(strver))
		{
			std::cout << "Error. " << strver << "\n"  ;
			return false;
		}
		std::string sql = "INSERT INTO version(major,minor,patch,stage,string) values (";
		sql += "'" + std::to_string(getMajor()) + "','" + std::to_string(getMinor()) + "','" + std::to_string(getPatch()) + "','";
		sql += "unknown" ;
		sql += "','" + strver + "')";
		//std::cout << "SQL : " << sql << "\n";
		if(conn.query(sql,callbackByArtifact,this))
        {
			id = sqlite3_last_insert_rowid((sqlite3*)conn.getServerConnector());
            return true;
        }
		
		id = -1;
        return false;
	}
    /**
    ***
    **/
    bool Version::selectAll(Conector& conect, std::vector<Version*>& vec)
    {
        std::string sql = "SELECT id,major,minor,patch,stage,build FROM version";
        if(conect.query(sql,callbackAll,&vec))
        {
            return true;
        }
			
        return false;
    }
			
    int Version::callbackAll(void *obj, int argc, char **argv, char **azColName)
    {
        std::vector<Version*>* lst = (std::vector<Version*>*)obj;
        Version* p = new Version();
        p->id = std::atoi(argv[0]);
        p->setNumbers(std::atoi(argv[1]),std::atoi(argv[2]),std::atoi(argv[3]));
        lst->push_back(p);
        return 0;
    }
    int Version::callbackByArtifact(void *obj, int argc, char **argv, char **azColName)
    {
        Version* p = (Version*)obj;	
        p->id = std::atoi(argv[0]);
        p->setNumbers(std::atoi(argv[1]),std::atoi(argv[2]),std::atoi(argv[3]));	
        
        return 0;
    }
    bool Version::selectByArtifact(Conector& connect, int artifact)
    {
        std::string sql = "SELECT id,major,minor,patch,stage,build,string FROM version WHERE artifact = '";
        sql = sql + std::to_string(artifact) + "'";
        if(connect.query(sql,callbackByArtifact,this))
        {
            return true;
        }
			
        return false;
    }









	
    /**
    ***
    **/
    bool Conector::query(const std::string& str, int (*callback)(void*,int,char**,char**),void* obj)
    {
        char *zErrMsg = 0;
        int rc = sqlite3_exec((sqlite3*)serverConnector, str.c_str(), callback, obj, &zErrMsg);
        if( rc == SQLITE_OK )
		{
			return true;
		}
		else if( rc == SQLITE_NOTADB ) 
        {
            fprintf(stderr, "SQL error(%i): La base de datos tiene mal formato: %s\n",rc, zErrMsg);
            sqlite3_free(zErrMsg);
            return false;				
        }
        else if( rc == SQLITE_ABORT ) 
        {
            fprintf(stderr, "SQL error(%i) : %s\n Quiza la callback retorn no-zero valor.",rc, zErrMsg);
            sqlite3_free(zErrMsg);
            return false;				
        }
        else if( rc != SQLITE_OK ) 			
        {
            fprintf(stderr, "SQL error(%i): %s\n",rc, zErrMsg);
            sqlite3_free(zErrMsg);
            return false;			
        }			
    }
    void* Conector::getServerConnector()
    {
        return serverConnector;
    }
    Conector::~Conector()
    {
        if(serverConnector != NULL) 
        {
            sqlite3_close((sqlite3*)serverConnector);
            serverConnector = NULL;
        }
    }		
    Conector::Conector(const std::string& dbname)
    {
        serverConnector = NULL;
        int rc = sqlite3_open(dbname.c_str(), (sqlite3**)&serverConnector);
        if( rc ) {
				fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg((sqlite3*)serverConnector));
				//return(0);
        } else {
				//fprintf(stderr, "Opened database(%s) successfully\n",dbname.c_str());
        }
    }

}
}
