# A repository to learn System and GUI Programming in C++.

# Note on ANSI vs UNICODE:

- If you are compiling in ANSI (MBCS), use \_T(""). This will allow you to transition to UNICODE with the minimum amount of trouble.
- If you are compiling in UNICODE (and never need to compile in ANSI), use L"".

# Precompiled headers:

- stdafx.h
- pch.h
- Simply list all your big huge headers for your APIs in your stdafx.h file, in the appropriate order, and then start each of your CPP files at the very top with an #include "stdafx.h", before any meaningful content.
