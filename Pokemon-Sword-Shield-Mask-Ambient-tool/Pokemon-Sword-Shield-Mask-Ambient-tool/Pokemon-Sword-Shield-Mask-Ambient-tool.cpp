#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace std;
using namespace Gdiplus;
wstring StringToWString(const string& str){
    int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wide = new wchar_t[num];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
    wstring w_str(wide);
    delete[] wide;
    return w_str;
}
//BOOL ImageFromIDResource(UINT nID, LPCTSTR sTR, Image*& pImg)
//{
//    HINSTANCE hInst = AfxGetResourceHandle();
//    HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nID), sTR); // type
//    if (!hRsrc)
//        return FALSE;
//    // load resource into memory
//    DWORD len = SizeofResource(hInst, hRsrc);
//    BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
//    if (!lpRsrc)
//        return FALSE;
//    // Allocate global memory on which to create stream
//    HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
//    BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
//    memcpy(pmem, lpRsrc, len);
//    IStream* pstm;
//    CreateStreamOnHGlobal(m_hMem, FALSE, &pstm);
//    // load from stream
//    pImg = Gdiplus::Image::FromStream(pstm);
//    // free/release stuff
//    GlobalUnlock(m_hMem);
//    pstm->Release();
//    FreeResource(lpRsrc);
//    return TRUE;
//}
int main(){
    char ar;
    string name;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;
    
    // Initialize GDI+.
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    cout << "File name?"<<endl;
    cin >> name;
    wstring infilename=StringToWString(name);
    Bitmap* bmp = new Bitmap(infilename.c_str());
    UINT height = bmp->GetHeight();
    UINT width = bmp->GetWidth();
    cout << "width " << width << ", height " << height << endl;
    if (!width || !height) {
        cout << "Please make sure the filename is correct."<<endl;
        return 0;
    }
    Gdiplus::Color color;
    Gdiplus::Bitmap bitmap(width, height, PixelFormat64bppPARGB),bmpg(width, height, PixelFormat64bppPARGB), bmpb(width, height, PixelFormat64bppPARGB);
    Gdiplus::Graphics graphics(&bitmap);
//sel:    cout << "msk or amb?(m/a)";
//    cin >> ar;
//    switch(ar){
//    case 'm': {
//        goto msk;
//    }
//    case 'a': {
//        goto amb;
//    }
//    default: {
//        goto sel;
//    }
//    }
    int isamb = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x <= width; x++) {
            bmp->GetPixel(x, y, &color);
            if ((int)color.GetBlue() < 100 || (int)color.GetBlue() > 150) {
                goto msk;
            }
        }
    }
    goto amb;
msk:    for (int y = 0; y < height; y++) {

        for (int x = 0; x < width; x++)

        {
            bmp->GetPixel(x, y, &color);
            Gdiplus::Color colorTemp;
            colorTemp.SetValue(color.MakeARGB((int)color.GetRed(), 255, 255, 255));
            bitmap.SetPixel(x, y, colorTemp);
            colorTemp.SetValue(color.MakeARGB((int)color.GetGreen(), 255, 255, 255));
            bmpg.SetPixel(x, y, colorTemp);
            colorTemp.SetValue(color.MakeARGB((int)color.GetBlue(), 255, 255, 255));
            bmpb.SetPixel(x, y, colorTemp);
        }
    }
goto end;
amb:for (int y = 0; y < height; y++) {

    for (int x = 0; x < width; x++)

    {
        bmp->GetPixel(x, y, &color);
        Gdiplus::Color colorTemp;
        int r = 255 - (int)color.GetRed(),g= 255 - (int)color.GetGreen(),b=(int)color.GetBlue();
        colorTemp.SetValue(color.MakeARGB(255, r, r, r));
        bitmap.SetPixel(x, y, colorTemp);
        colorTemp.SetValue(color.MakeARGB(255, g, g, g));
        bmpg.SetPixel(x, y, colorTemp);
        colorTemp.SetValue(color.MakeARGB(255, b, b, b));
        bmpb.SetPixel(x, y, colorTemp);
    }
}

end:    CLSID jpg_sid;
    CLSIDFromString(L"{557CF400-1A04-11D3-9A73-0000F81EF32E}", &jpg_sid);
    bitmap.Save(L"r.bmp", &jpg_sid, NULL);
    bmpg.Save(L"g.bmp", &jpg_sid, NULL);
    bmpb.Save(L"b.bmp", &jpg_sid, NULL);
}
