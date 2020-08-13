# Config-Parser
Mainy available config parsers work on string conversion to, and from the desired type.
This project offers a more robust solution that is type-safe and also more easily extendable. The Config Parser class itself is thread-safe.


# Usage
Below is an example of normal usage.

```C++
Configuration config("ServerSettings.ini");

auto ServerNameConf = StringProperty::create("Server Name", "Unknown", "Server to connect to.");
auto ServerPortConf = IntProperty::create("Server Port", 12345, 1000, 65535, "Port of the server.");
auto ConnectionLifetimeConf = FloatProperty::create("Lifetime", 10.5f, "Lifetime of the connection in minutes.");
ConnectionLifetimeConf->setMinValue(5.f);

config.registerProperty(ServerNameConf);
config.registerProperty(ServerPortConf);
config.registerProperty(ConnectionLifetimeConf);
	
config.save();
```

First create and register all the configurations (A default value must be given).
Then either save, or load the config.

Configuration options registered will have their values overwritten when a load occurs. If the loaded value is invalid, it will default to the defaultvalue. If the loaded value is outside of the min/max range, it will be set to either the min/max value limit.

Recommended is a load followed by a save to synchronize any self-correcting changes that might occur during reading.

The resulting config file is as follows:
```
# Lifetime of the connection in minutes. [min: 5, default: 10.5]
Lifetime=10.500000

# Server to connect to. [default: Unknown]
Server Name=Unknown

# Port of the server. [range: 1000 ~ 65535, default: 12345]
Server Port=12345
```

## Formatting
All lines starting with a '#' (ignoring whitespace) will be ignored. Property names and values CAN contain '#', as long as it's not the first character.
Property names and values can contain '=' but it is assumed that everything following the first '=' is the value of the property. Therefor it is not recommended to put these characters in the property names.
Property names can be indented. White spaces are ignored up until the first character encountered.

Some examples of the above (that are valid) are:
```
   Lifetime=10.500000
Server Name=#unknown
Some String=abc=123
Some Other String="abc = 123"
```

Comments, default values and/or whitelines can be ignored.
```C++
Configuration config("ServerSettings.ini");
config.IncludeComments = false;
config.IncludeWhiteLine = false;
```
Results in:
```
Lifetime=10.500000
Server Name=Unknown
Server Port=12345
```

## "Advanced" usage
Since the properties are shared_ptr, the property objects registered change their value during a configuration load. It can be beneficial keeping these properties available in an object for further access. There is no performance penalty for accessing properties as there is no conversion taking place.

By extending from ConfigProperty, new types of properties can be easily added (such as RGBA values, collections, etc).

To re-obtain property objects from the Configuration, simply type the following (where "StringProperty" is to be replaced by the correct property type registered under that name"):
```C++
auto ServerNameConf = config.getType<StringProperty>("Server Name");
```
