


#include <iostream>

#include <fstream>

#include <string>

#include <windows.h>

#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")



using namespace std;

using namespace Gdiplus;

int main()

{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wstring infilename(L"in.png");
    Bitmap* bmp = new Bitmap(infilename.c_str());
    UINT height = bmp->GetHeight();
    UINT width = bmp->GetWidth();
    cout << "width " << width << ", height " << height << endl;
    if (!width || !height) {
        cout << "Rename your texture to 'in.png'!"<<endl;
        return 0;
    }
    Gdiplus::Color color;

    Gdiplus::Bitmap bitmap(width, height, PixelFormat64bppPARGB),bmpg(width, height, PixelFormat64bppPARGB), bmpb(width, height, PixelFormat64bppPARGB);
    Gdiplus::Graphics graphics(&bitmap);
    int white=0;
    char ch;
sel:    cout << "msk or amb?(m/a)";
    cin >> ch;
    switch(ch){
    case 'm': {
        goto msk;
    }
    case 'a': {
        goto amb;
    }
    default: {
        goto sel;
    }
    }
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