#include <Windows.h>
#include <iostream>

void CreateDirectory();
void CopyFile();

int main()
{
	CopyFile();

	system("PAUSE");
	return 0;
}

void CopyFile()
{
	BOOL bFile;
	bFile = CopyFile(L"C:\\Users\\nhatv\\Work\\DialogBase\\WinSys\\OldFile.txt",
		L"C:\\Users\\nhatv\\Work\\DialogBase\\WinSys\\NewFile.txt",
		TRUE);
	if (bFile == FALSE)
	{
		std::cout << "CopyFile Failed and Error No - " << GetLastError() << std::endl;
	}
	std::cout << "CopyFile Succeeded" << std::endl;
}

void CreateDirectory()
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
}