#ifndef COTETOS_SOFTWARE_HH
#define COTETOS_SOFTWARE_HH

#include <string>


#include <octetos/core/Version.hh>
#include <octetos/core/Artifact.hh>


namespace octetos
{
namespace software
{
	/**
	 * \brief retorna la version actual de componente
	 **/
	octetos::core::Version getPakageVersion();
	std::string getPakageName();
	
	/**
	 * \brief retorna la informacion del paquete usese ne lugar getPakageVersion y getPakageName
	 **/
	octetos::core::Artifact getPackageInfo();
	
}
}
#endif
