#include <wx/string.h>
#include <wx/wxcrt.h>
#include <wx/wxchar.h>

int main(int argc, char** argv)
{
	wxPuts(wxT("A wxWidgets console application"));
	wxString str1 = wxT("Windows");
	wxString str2 = wxT("Operating");
	wxString str3 = wxT("System");
	wxString str = str1 + wxT(" ") + str2 + wxT(" ") + str3;
	wxPuts(str);
	wxPrintf(wxT("The string has %d characters\n"), str.Len());

	int flowers = 21;
	wxString str4;
	str4.Printf(wxT("There are %d red roses."), flowers);

	wxPuts(str4);

	if (str.Contains(wxT("Windows"))) {
		wxPuts(wxT("Contains!"));
	} if (!str.Contains(wxT("plain"))) {
		wxPuts(wxT("Does not contain!"));
	}

}