#include <Windows.h>
#include <iostream>

void CreateDirectory();
void CopyFile();
void MoveFile();
void CreateFile();

int main()
{
	CreateFile();

	system("PAUSE");
	return 0;
}

void CreateFile()
{
	HANDLE hFile;

	hFile = CreateFile(
		L"C:\\Users\\nhatv\\Work\\DialogBase\\WinSys\\TestFile.txt",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << "CreateFile Failed and Error No - " << GetLastError() << std::endl;
	}
	std::cout << "CreateFile Succeeded" << std::endl;

	CloseHandle(hFile);
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