#pragma once
#include<iostream>
#include<ctime>
#include <io.h> // hai thu vien nay de nhap xuat co dau
#include <fcntl.h>
using namespace std;


#define ClickTrai 0x5A
#define ClickPhai 0x58

#define ConsoleWidth 80
#define ConsoleHeight 35

struct CauTrucBang {
	short sDong = 0;
	short sCot = 0;
	short sSoBom = 0;
	short sSoODaMo = 0;
	short sSoCo = 0;
};

struct CauTrucO {
	bool bCoBom = false;
	bool bDaMo = false;
	bool bCamCo = false;
	short BomLanCan = 0;
};
//trang, vi tri dang chon, tong muc
extern short sTRang, sTongMuc, sVTDangChon;

