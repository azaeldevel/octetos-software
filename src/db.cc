#include "db.hh"

#include <stdio.h>
#include <sqlite3.h> 

namespace octetos
{
namespace software
{
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
        std::string sql = "SELECT id,major,minor,patch,stage,build FROM version WHERE artifact = '";
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
        if( rc == SQLITE_NOTADB ) 
        {
            fprintf(stderr, "SQL error(%i): La base de datso tiene mal formato: %s\n",rc, zErrMsg);
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
        else 
        {
            //fprintf(stdout, "Operation done successfully\n");
            return true;			
        }
        return true;			
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
