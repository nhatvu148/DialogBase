#include <Windows.h>
#include <iostream>

int main()
{
	BOOL bDir;
	bDir = CreateDirectory(L"C:\\Users\\nhatv\\Work\\DialogBase\\WinSys\\Dir1", NULL);

	if (bDir == FALSE)
	{
		std::cout << "CreateDirectory Failed and Error No - " << GetLastError() << std::endl;
	}

	std::cout << "CreateDirectory Succeeded" << std::endl;

	getchar();

	bDir = RemoveDirectory(L"C:\\Users\\nhatv\\Work\\DialogBase\\WinSys\\Dir1");

	std::cout << "RemoveDirectory Succeeded" << std::endl;

	system("PAUSE");
	return 0;
}