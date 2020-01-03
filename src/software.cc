

#include "config.h"
#include "software.hh"
	

namespace octetos
{
namespace software
{
	octetos::core::Semver getPakageVersion()
	{
		octetos::core::Semver v;
		v.set(PACKAGE_VERSION);
		return v;		
	}

	std::string getPakageName()
	{
		return PACKAGE_NAME;
	}
	
	octetos::core::Artifact getPackageInfo()
	{
		octetos::core::Artifact packinfo;
		
		packinfo.name = PACKAGE_NAME;
		packinfo.brief = "";
		packinfo.url = "";
		
		packinfo.version.set(PACKAGE_VERSION);
		
		packinfo.licence.type = octetos::core::Licence::Type::GPL;		
		packinfo.licence.name_public = packinfo.name;
		packinfo.licence.owner = "Azael Reyes";
		packinfo.licence.year = 2019;
        packinfo.licence.contact = "azael.devel@gmail.com";
		
		return packinfo;	
	}
}
}
