#include "Configuration.h"

int main()
{
	Configuration config("ServerSettings.ini");

	//Create, then register
	auto ServerNameConf = StringProperty::create("Server Name", "Unknown", "Server to connect to.");
	config.registerProperty(ServerNameConf);

	//Create and register
	auto ServerPortConf = config.registerProperty<IntProperty>("Server Port", 12345, 1000, 65535, "Port of the server.");
	auto ConnectionLifetimeConf = config.registerProperty<FloatProperty>("Lifetime", 10.5f, "Lifetime of the connection in minutes.");
	ConnectionLifetimeConf->setMinValue(5.f);

	config.save();

	return 0;
}


