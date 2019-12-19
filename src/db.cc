#include "db.hh"

#include <stdio.h>
#include <sqlite3.h> 

#include "db.hh"


namespace octetos
{
namespace software
{
	
    int Artifact::callbackMultiline(void *obj, int argc, char **argv, char **azColName)
    {
		std::vector<Artifact*>* ls = (std::vector<Artifact*>*)obj;
		for (int i = 0; i < argc; i++) 
		{			
		    Artifact* p = new Artifact(std::atoi(argv[0]));	

			ls->push_back(p);
		}
        return 0;
    }
	bool Artifact::getArtifacts(Conector& connect, std::vector<Artifact*>* artifacts)
	{
        std::string sql = "SELECT id FROM artifact WHERE fullpath = '";
        //sql = sql + path + "'";
		//std::cout << "SQL : " << sql << "\n";
        if(connect.query(sql,callbackMultiline,artifacts))
        {
            return true;
        }
			
        return false;		
	}
	Artifact::Artifact()
	{
	}
	Artifact::Artifact(int id)
	{
		this->id = id;
	}
    bool Artifact::remove(Conector& conect)
	{
        std::string sql = "DELETE FROM artifact WHERE id = ";
        sql = sql + std::to_string(id);
        if(conect.query(sql,NULL,this))
        {
            return true;
        }
		
        return false;
	}
	bool Artifact::deleteByPackage(Conector& conn, const Package& package)
	{
		std::string sql = "DELETE from artifact WHERE package = " + std::to_string(package.getID());
		//std::cout << "SQL : " << sql << "\n";
		if(conn.query(sql,NULL,this))
        {
			id = -1;
            return true;
        }
		
		id = -1;
        return false;
	}
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
	/*bool Artifact::selectAll(Conector& conect, std::vector<Artifact*>& vec)
    {
        std::string sql = "SELECT id,fullpath,version,package FROM version";
        if(conect.query(sql,callbackAll,&vec))
        {
            return true;
        }
			
        return false;
    }*/			
    /*int Artifact::callbackAll(void *obj, int argc, char **argv, char **azColName)
    {
        std::vector<Artifact*>* lst = (std::vector<Artifact*>*)obj;
        Artifact* p = new Artifact();
        p->id = std::atoi(argv[0]);
        lst->push_back(p);
        return 0;
    }*/
    int Artifact::callbackByArtifact(void *obj, int argc, char **argv, char **azColName)
    {
        Artifact* p = (Artifact*)obj;	
        p->id = std::atoi(argv[0]);
        
        return 0;
    }
    bool Artifact::selectByFullPath(Conector& connect, const std::string& path)
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




	


    bool Package::remove(Conector& conect)
	{
        std::string sql = "DELETE FROM artifact WHERE id = ";
        sql = sql + std::to_string(id);
        if(conect.query(sql,NULL,this))
        {
            return true;
        }
		
        return false;
	}
	bool Package::deleteByName(Conector& conn, const std::string& name)
	{
		std::string sql = "DELETE from package WHERE name = " + name;
		//std::cout << "SQL : " << sql << "\n";
		if(conn.query(sql,NULL,this))
        {
			id = -1;
            return true;
        }
		
		id = -1;
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
		if(conn.query(sql,callbackByFullLine,this))
        {
			id = sqlite3_last_insert_rowid((sqlite3*)conn.getServerConnector());
            return true;
        }
		
		id = -1;
        return false;
	}	
	/*bool Package::selectAll(Conector& conect, std::vector<Package*>& vec)
    {
        std::string sql = "SELECT id,name,version,note FROM version";
        if(conect.query(sql,callbackAll,&vec))
        {
            return true;
        }
			
        return false;
    }*/			
    /*int Package::callbackAll(void *obj, int argc, char **argv, char **azColName)
    {
        std::vector<Package*>* lst = (std::vector<Package*>*)obj;
        Package* p = new Package();
        p->id = std::atoi(argv[0]);
        p->name = argv[1];
		p->version = std::atoi(argv[2]);
		p->note = argv[3];
		
        lst->push_back(p);
        return 0;
    }*/
    int Package::callbackByFullLine(void *obj, int argc, char **argv, char **azColName)
    {
		//std::cout << "argc " << argc << "\n";
		Package* p = (Package*)obj;
		if(argc > 0)
		{
			//std::cout << "step : " << 1 << "\n";
			p->id = std::atoi(argv[0]);
			//std::cout << "step : " << 2 << "\n";
			p->name = argv[1];
			//std::cout << "step : " << 3 << "\n";
			p->version = std::atoi(argv[2]);
			//std::cout << "step : " << 4 << "\n";
			p->note = (argv[3] == NULL? "" : argv[3]);
			//std::cout << "step : " << 5 << "\n";
		}
		else
		{
			p->id = -1;
		}
		
		//std::cout << "step : " << 6 << "\n";
        return 0;
    }
    bool Package::selectByName(Conector& connect, const std::string& name)
    {
        std::string sql = "SELECT id,name,version,note FROM package WHERE name = '";
        sql = sql + name + "' ORDER BY id DESC LIMIT 1 ";
		//std::cout << "SQL : " << sql << "\n";
        if(connect.query(sql,callbackByFullLine,this))
        {
			//std::cout << "id : " << id << "\n";
			if(id == -1) return false;
			
			version.download(connect);
            return true;
        }
		
        return false;
    }






	
	
    int Version::callbackFull(void *obj, int argc, char **argv, char **azColName)
    {
        Version* p = (Version*)obj;	
        p->id = std::atoi(argv[0]);
        //p->setNumbers(std::atoi(argv[1]),std::atoi(argv[2]),std::atoi(argv[3]));	
        p->from(argv[4]);
		
        return 0;
    }
    bool Version::download(Conector& connect)
    {
        std::string sql = "SELECT id,major,minor,patch,stage,build,string FROM version WHERE id = '";
        sql = sql + std::to_string(id) + "'";
        if(connect.query(sql,callbackByArtifact,this))
        {
            return true;
        }
		
        return false;
    }
    bool Version::remove(Conector& conect)
	{
        std::string sql = "DELETE FROM version WHERE id = ";
        sql = sql + std::to_string(id);
        if(conect.query(sql,NULL,this))
        {
            return true;
        }
		
        return false;
	}
	Version& Version::operator=(int id)
	{
		this->id = id;
		return *this;
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
    /*bool Version::selectAll(Conector& conect, std::vector<Version*>& vec)
    {
        std::string sql = "SELECT id,major,minor,patch,stage,build FROM version";
        if(conect.query(sql,callbackAll,&vec))
        {
            return true;
        }
			
        return false;
    }	*/		
    /*int Version::callbackAll(void *obj, int argc, char **argv, char **azColName)
    {
        std::vector<Version*>* lst = (std::vector<Version*>*)obj;
        Version* p = new Version();
        p->id = std::atoi(argv[0]);
        p->setNumbers(std::atoi(argv[1]),std::atoi(argv[2]),std::atoi(argv[3]));
        lst->push_back(p);
        return 0;
    }*/
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

		return false;
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
