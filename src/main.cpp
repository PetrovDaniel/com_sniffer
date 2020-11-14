#include "sniffer.h"

int main()
{
	try
	{
		std::string port_name = "COM6";
		PortHandler sp(port_name, 19200);
		port_name = "COM4";
		PortHandler sp2(port_name, 19200);

		for (;;)
		{
			sp.Run();
			sp2.Run();
		}
	}
	catch (const std::exception &ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
		system("pause");
	}

	return 0;
}