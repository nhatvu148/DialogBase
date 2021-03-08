#include <Windows.h>
#include <iostream>

void CreateDirectory();
void CopyFile();
void MoveFile();

int main()
{
	MoveFile();

	system("PAUSE");
	return 0;
}

void MoveFile()
{
	BOOL bFile;
	bFile = MoveFile(L"C:\\Users\\nhatv\\Work\\DialogBase\\WinSys\\OldFile.txt",
		L"C:\\Users\\nhatv\\Work\\DialogBase\\WinSys\\New.txt"
	);
	if (bFile == FALSE)
	{
		std::cout << "MoveFile Failed and Error No - " << GetLastError() << std::endl;
	}
	std::cout << "MoveFile Succeeded" << std::endl;
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