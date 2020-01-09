#include "FileDialog.h"

bool FileDialog::getPath(char* path)
{
    OPENFILENAMEA ofn;

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Ascii Stereolithography (.stl)\0*.stl";
    ofn.lpstrFile = path;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrTitle = "Privet, let me open your file...";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    return GetOpenFileNameA(&ofn);
}
