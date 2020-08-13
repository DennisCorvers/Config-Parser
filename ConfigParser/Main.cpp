#include "Configuration.h"

int main()
{
	Configuration config("ServerSettings.ini");

	auto ServerNameConf = StringProperty::create("Server Name", "Unknown", "Server to connect to.");
	auto ServerPortConf = IntProperty::create("Server Port", 12345, 1000, 65535, "Port of the server.");
	auto ConnectionLifetimeConf = FloatProperty::create("Lifetime", 10.5f, "Lifetime of the connection in minutes.");
	ConnectionLifetimeConf->setMinValue(5.f);

	config.registerProperty(ServerNameConf);
	config.registerProperty(ServerPortConf);
	config.registerProperty(ConnectionLifetimeConf);

	config.save();

	return 0;
}


