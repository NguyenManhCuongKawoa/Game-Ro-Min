#include"Ham.h"
#include "main.h"
#include"Console.h"



CauTrucBang CT_Bang;
CauTrucO** CT_O;

// Vi tri con tro hien tai.
COORD cViTriConTro;

//Su Dung Phim
bool bSuDungPhim = false;

//toa do x y ve bang
short sTaoDoX;
short sTaoDoY;

//cap nhat trang thai choi game
bool bTrangThaiChoiGame = false;



void TaoMangHaiChieu() {
	CT_O = new CauTrucO * [CT_Bang.sDong];
	for (int i = 0; i < CT_Bang.sDong; i++) {
		CT_O[i] =  new CauTrucO [CT_Bang.sCot];
	}
}

void XoaMangHaiChieu() {
	for (int i = 0; i < CT_Bang.sDong; i++) {
		delete[] CT_O[i];
	}
	delete[] CT_O;
} 

void LuuToaDoBang() {
	sTaoDoX = (ConsoleWidth / 2) - (CT_Bang.sDong );
	sTaoDoY = ((ConsoleHeight )/ 2 +3) - (CT_Bang.sCot / 2);
}

void KhoiTao(short sDong, short sCot, short sSoBom) {
	CT_Bang.sDong = sDong;
	CT_Bang.sCot = sCot;
	CT_Bang.sSoBom = sSoBom;
	CT_Bang.sSoODaMo = 0;
	CT_Bang.sSoCo = 0;

	TaoMangHaiChieu();

	LuuToaDoBang();

	cViTriConTro = { 0,0 };
	bTrangThaiChoiGame = true;

	VE_Bang();
	TaoBomNgauNhien();

	VeTrangthaichoigame(1,0,0);
	

	/*std::cout <<"\n";
	Xuat_Bom_Ngau_Nhien();*/

	

}
short ToaDoX(short x) { //Toa do x ve bang
	return (2*x)+ sTaoDoX;
}

short ToaDoY(short y) { //Toa do y ve bang
	return y + sTaoDoY;
}

void Ve_O(short x, short y, short kieu) {
	char a[3]="\0";
	switch (kieu) {
	    case 0: //rong la mau xanh la
			strcpy(a, "  ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 0, 10, a);
		    break;
	    case 1: // so 1 chu mau xanh duong. 1->8 co nen la mau trang
			strcpy(a, "1 ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 9, 15, a);
			break;
		case 2: //So 2 xanh la
			strcpy(a, "2 ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 2, 15, a);
			break;
		case 3: //So 3 do
			strcpy(a, "3 ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 12, 15, a);
			break;
		case 4: // so 4 xanh duong dam
			strcpy(a, "4 ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 1, 15, a); 
			break;
		case 5: //so 5 do dam
			strcpy(a, "5 ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 4, 15, a);
			break;
		case 6:  //so 6 cam dam
			strcpy(a, "6 ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 3, 15, a);
			break;
		case 7: // so 7 den
			strcpy(a, "7 ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 0, 15, a);
			break;
		case 8: // so 8 hong
			strcpy(a, "8 ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 13, 15, a);
			break;
		case 9: //bom
			strcpy(a, "B ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 0, 12, a);
			break;
		case 10: // o chan
			strcpy(a, "  ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 0, 8, a);
			break;
		case 11: // o le
			strcpy(a, "  ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 0, 7, a);
			break;
		case 12: //con tro
			strcpy(a, " ");
			setColorBGTextXY(ToaDoX(x) + 1, ToaDoY(y), 0, 13, a);
			break;
		case 13: // cam co
			strcpy(a, "P ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 12, 14, a);
			break;
		case 14: // cam co khong co bom->cam co sai
			strcpy(a, "Px");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 15, 6, a);
			break;
		case 15: // cam co co bom-> cam co dung
			strcpy(a, "B ");
			setColorBGTextXY(ToaDoX(x), ToaDoY(y), 12, 14, a);
			break;
	}
}
void VE_Bang() {
	for (int i = 0; i < CT_Bang.sDong; i++) {
		for (int j = 0; j < CT_Bang.sCot; j++) {

			if(CT_O[i][j].bCamCo) {
				Ve_O(j, i, 13); 
			}
			else if(CT_O[i][j].BomLanCan) {
				Ve_O(j, i, CT_O[i][j].BomLanCan);
			}
			else if (CT_O[i][j].bDaMo) {
				Ve_O(j, i, 0);
			}
			else if ((i + j) % 2 == 0) {
				Ve_O(j, i, 10);
			}  
			else Ve_O(j, i, 11);

			if (bSuDungPhim) {
				Ve_O(cViTriConTro.X, cViTriConTro.Y, 12);
			}
		}
	}
}

void TaoBomNgauNhien() {
	short sSoBom = CT_Bang.sSoBom;
	short sI, sJ; // sI la vi tri dong sJ la vi tri cot	
	srand(time(NULL));
	while (sSoBom != 0) {
		sI = rand() % CT_Bang.sDong;
		sJ = rand() % CT_Bang.sCot;
		if (CT_O[sI][sJ].bCoBom) {
			continue;
		}
		CT_O[sI][sJ].bCoBom = true;
		sSoBom--;
	}
}
void Xuat_Bom_Ngau_Nhien() {
	for (int i = 0; i < CT_Bang.sDong; i++) {
		for (int j = 0; j < CT_Bang.sCot; j++) {
			wcout << CT_O[i][j].bCoBom<<" ";
		}
		wcout << endl;
	}
}

bool KT_Game_Thang() {
	for (int i = 0; i < CT_Bang.sDong; i++) {
		for (int j = 0; j < CT_Bang.sCot; j++) {
			if ((CT_O[i][j].bCamCo==1 && CT_O[i][j].bCoBom!=1) || (CT_O[i][j].bCamCo != 1 && CT_O[i][j].bCoBom == 1)) return false;
		}
	}
	return true;
	/*if ((CT_Bang.sSoODaMo + CT_Bang.sSoBom ) == (CT_Bang.sCot * CT_Bang.sDong)) return true;
	else return false;*/
}

void click_Phai(short sX, short sY) { // cam co chu x
	if (!CT_O[sX][sY].bDaMo) { 
		if (CT_O[sX][sY].bCamCo) {
			CT_O[sX][sY].bCamCo = false;
			CT_Bang.sSoCo--;
			deleteRow(5, 1);
			VeTrangthaichoigame(1, 0, 0);
		}
		else {
			if (CT_Bang.sSoCo < CT_Bang.sSoBom) {
				CT_O[sX][sY].bCamCo = true;
				CT_Bang.sSoCo++;
				deleteRow(5, 1);
				VeTrangthaichoigame(1, 0, 0);
			}
		}
		VE_Bang();
		if (KT_Game_Thang())
			Thang();
	}
}
short Dem_Bom_Lan_Can(short sX, short sY) {
	short count = 0;
	for (int i = sX - 1; i <= sX + 1; i++) {
		for (int j = sY - 1; j <= sY + 1; j++) {
			//cac vi tri k hop le
			if (i < 0 || i >= CT_Bang.sDong || j < 0 || j >= CT_Bang.sCot || (i==sX && j==sY)) {
				continue;
			}
			//neu co bom thi dem tang them 1
			if (CT_O[i][j].bCoBom) {
				count++;
			}
		}
	}
	return count;
}

void mo_O(short sX, short sY) {
	if (!CT_O[sX][sY].bDaMo && !CT_O[sX][sY].bCamCo) {
		CT_O[sX][sY].bDaMo = true;
		CT_Bang.sSoODaMo++;
		if (CT_O[sX][sY].bCoBom) {  // co bom
			Thua(); // => thua
		}
		else {  // k co bom
			short sSo_Bom_Lan_Can = Dem_Bom_Lan_Can(sX, sY);
			if (sSo_Bom_Lan_Can > 0) {  // co bom lan can
				CT_O[sX][sY].BomLanCan = sSo_Bom_Lan_Can;
			}
			else { // o rong
				// duyet cac o lan can va goi de quy
				for (int i = sX - 1; i <= sX + 1; i++) {
					for (int j = sY - 1; j <= sY + 1; j++) {
						//cac vi tri k hop le
						if (i < 0 || i >= CT_Bang.sDong || j < 0 || j >= CT_Bang.sCot || (i == sX && j == sY)) {
							continue;
						}
						// goi de quy
						mo_O(i, j);
						}
					}
				}
			}
		}
	}

void click_Trai(short sX, short sY) { // mo o
	if (!CT_O[sX][sY].bDaMo && !CT_O[sX][sY].bCamCo) {
		mo_O(sX, sY);
		if (bTrangThaiChoiGame) {
			VE_Bang();
		}
	}
}

void Thang() {
	bTrangThaiChoiGame = false;
	XoaMangHaiChieu();
	sTRang = 5;
	deleteRow(4, 1);
	VeTrangthaichoigame(2,2,1); // cap nhat lai trang thai la thang
}

void Thua() {
	// Hien bom an va kiem tra cam co dung hay sai.
	for (int i = 0; i < CT_Bang.sDong; i++) {
		for (int j = 0; j< CT_Bang.sCot; j++) {
			if (CT_O[i][j].bCamCo) { // co cam co
				if (CT_O[i][j].bCoBom) {
					Ve_O(j, i, 15);// cam co dung(cam co co bom)
				}
				else Ve_O(j, i, 14); //cam co sai(cam co k co bom)
			}
			else { // k co cam co
				if (CT_O[i][j].bCoBom) { // co bom +> hien bom
					Ve_O(j, i, 9);//hien bom
				}
			}
		}
	}

	bTrangThaiChoiGame = false;
	XoaMangHaiChieu();
	sTRang= 4;
	deleteRow(4, 1);
	VeTrangthaichoigame(3,3,1); // cap nhat lai  trang thai la thua
}

/*Y Tuong
1) Trang Menu Chinh.
2) Trang Menu chon cap do.
3) Trang Choi Game.
4) Trang Thua.
5) Trang Thang.
6) Trang Luu Game.
7) Trang Thong Tin Ve Game.
*/

void Xu_Li_Phim(KEY_EVENT_RECORD key) {
	if (key.bKeyDown) { //co nhan phim
		switch (key.wVirtualKeyCode) {
		     case VK_UP: //MUI TEN LEN
				 switch (sTRang) {
				 case 1: // Menu chinh
					 if (sTongMuc == 4) {
						 if (sVTDangChon == 0) {
							 sVTDangChon = sTongMuc - 1;
						 }
						 else sVTDangChon--;
						 VeMenuChinh(sVTDangChon);
					 }
					 break;
				 case 2: // chon cap do
					 if (sTongMuc == 4) {
						 if (sVTDangChon == 0) {
							 sVTDangChon = sTongMuc - 1;
						 }
						 else sVTDangChon--;
						 VeMenuCapDo(sVTDangChon);
					 }
					 break;
				 case 3: // trang choi game
					 if (bTrangThaiChoiGame) {
						 bSuDungPhim = true;
						 cViTriConTro.Y = ((cViTriConTro.Y == 0) ? CT_Bang.sDong - 1 : cViTriConTro.Y - 1);
						 VE_Bang();
					 }

					 break;
				 case 4: // trang thua
					 VeTrangthaichoigame(3, 3, (sVTDangChon == 1) ? 2 : 1);
					 break;
				 case 5: // trang thang
					 VeTrangthaichoigame(2, 2, (sVTDangChon == 1) ? 2 : 1);
					 break;
				 case 6: // trang luu diem
					 if (sTongMuc == 3) {
						 if (sVTDangChon == 0) {
							 sVTDangChon = sTongMuc - 1;
						 }
						 else sVTDangChon--;
						 VeTrangthaichoigame(1, 1, sVTDangChon);
					 }
					 break;
				 case 7: // trang thong tin (mui ten len)
					 /*cViTriConTro.Y = ((cViTriConTro.Y == 0) ? ConsoleHeight - 1 : cViTriConTro.Y - 1);
					 Trang_Thong_Tin();*/
					 break;
				 }
				 break;
			 case VK_DOWN: //MUI TEN XUONG
				 switch (sTRang) {
				 case 1: // Menu chinh
					 if (sTongMuc == 4) {
						 if (sVTDangChon == sTongMuc - 1) {
							 sVTDangChon = 0;
						 }
						 else sVTDangChon++;
						 VeMenuChinh(sVTDangChon);
					 }

					 break;
				 case 2: // chon cap do
					 if (sTongMuc == 4) {
						 if (sVTDangChon == sTongMuc - 1) {
							 sVTDangChon = 0;
						 }
						 else sVTDangChon++;
						 VeMenuCapDo(sVTDangChon);
					 }
					 break;
				 case 3: // trang choi game
					 if (bTrangThaiChoiGame) {
						 bSuDungPhim = true;
						 cViTriConTro.Y = ((cViTriConTro.Y == CT_Bang.sDong - 1) ? 0 : cViTriConTro.Y + 1);
						 VE_Bang();
					 }

					 break;
				 case 4: // trang thua
					 VeTrangthaichoigame(3, 3, (sVTDangChon == 1) ? 2 : 1);
					 break;
				 case 5: // trang thang
					 VeTrangthaichoigame(2, 2, (sVTDangChon == 1) ? 2 : 1);
					 break;
				 case 6: // trang luu diem
					 if (sTongMuc == 3) {
						 if (sVTDangChon == sTongMuc - 1) {
							 sVTDangChon = 0;
						 }
						 else sVTDangChon++;
						 VeTrangthaichoigame(1, 1, sVTDangChon);
					 }
					 break;
				 case 7: // trang thong tin (mui ten xuong)

					 break;
				 }
				 break;
			 case VK_LEFT: //MUI TEN TRAI
				 if (bTrangThaiChoiGame) {
					 bSuDungPhim = true;
					 cViTriConTro.X = ((cViTriConTro.X == 0) ? CT_Bang.sCot - 1 : cViTriConTro.X - 1);
					 VE_Bang();
				 }
				 if (sTRang == 7) { // trang thong tin ( mui ten trai)

				 }
				 break;
			 case VK_RIGHT: //mui ten phai
				 if (bTrangThaiChoiGame) {
					 bSuDungPhim = true;
					 cViTriConTro.X = ((cViTriConTro.X == CT_Bang.sCot - 1) ? 0 : cViTriConTro.X + 1);
					 VE_Bang();
				 }
				 if (sTRang == 7) { //trang thong tin mui ten phai

				 }
				 break;
			 case VK_RETURN: // phim enter
				 switch (sTRang) {
				 case 1: // Menu chinh
					 if (sVTDangChon == 0) {
						 sTRang = 2;
						 deleteRow(4, 7);
						 VeMenuCapDo(0);
					 }
					 else if (sVTDangChon == 1) { // trang bang diem

					 }
					 else if (sVTDangChon == 2) { // trang thong tin
						 Trang_Thong_Tin();
					 }
					 else exit(0);// thoat chuong trinh
					 break;
				 case 2: // chon cap do
					 if (sVTDangChon == 0) { //  chon muc do de
						 sTRang = 3; // cap nhat trang dang choi
						 deleteRow(4, 10);
						 KhoiTao(9, 9, 10);
					 }
					 else if (sVTDangChon == 1) { // chon muc do trung binh
						 sTRang = 3; // cap nhat trang dang choi
						 deleteRow(5, 12);
						 KhoiTao(16, 16, 40);
					 }
					 else if (sVTDangChon == 2) { // chon muc do kho
						 sTRang = 3; // cap nhat trang dang choi
						 deleteRow(5, 12);
						 KhoiTao(24, 24, 99);
					 }
					 else {
						 sTRang = 1;
						 deleteRow(4, 12);
						 VeMenuChinh(0);
					 }
					 break;
				 case 4: // trang thua
					 if (sVTDangChon == 2) { //  thoat game
						 sTRang = 1;
						 deleteRow(3, ConsoleHeight - 3);
						 VeMenuChinh(0);
					 }
					 else { // choi lai
						 deleteRow(3, ConsoleHeight - 3);
						 sTRang = 3; // cap nhat trang dang choi game
						 VeTrangthaichoigame(1, 0, 0);
						 KhoiTao(CT_Bang.sDong, CT_Bang.sCot, CT_Bang.sSoBom);
					 }
					 break;
				 case 5: // trang thang
					 if (sVTDangChon == 2) { //  thoat game
						 sTRang = 1;
						 deleteRow(3, ConsoleHeight - 3);
						 VeMenuChinh(0);
					 }
					 else { // luu khi thang
						 
					 }
					 break;
				 case 6: // trang luu game
					 if (sVTDangChon == 0) {
						 sTRang = 3;// cap nhat trang thai choi game 
						 deleteRow(3, 3);
						 VeTrangthaichoigame(1, 0, 0);
						 bTrangThaiChoiGame = true;
					 }
					 else if(sVTDangChon == 1) { // luu game su ly file
						 
					 }
					 else  { //  thoat game
						 sTRang = 1;
						 deleteRow(3, ConsoleHeight - 3);
						 VeMenuChinh(0);
					 }
					 
					 break;
				 }
				 break;
			 case VK_ESCAPE: // phim ESC(thoat)
				 switch (sTRang) {
				 case 1: // Menu chinh
					  exit(0);// thoat chuong trinh
					 break;
				 case 2: // chon cap do
					 sTRang = 1; // cap nhat lai trang menu chinh
					 deleteRow(3, 12);
					 VeMenuChinh(0);

					 break;
				 case 3: // trang choi game
					 sTRang = 6;
					 sTongMuc = 3;
					 bTrangThaiChoiGame = false;
					 //deleteRow(3, ConsoleHeight - 3);
					 VeTrangthaichoigame(1, 1, 0);
					 break;
				 case 4: // trang thua
					 sTRang = 1;
					 deleteRow(3, ConsoleHeight - 3);
					 VeMenuChinh(0);
					 break;
				 case 5: // trang thang
					 sTRang = 2;
					 deleteRow(3, ConsoleHeight - 3);
					 VeMenuCapDo(0);
					 break;
				 case 7: // trang thong tin (nut esc)
					 sTRang = 1;// ve menu chinh
					 deleteRow(0, ConsoleHeight); // xoa dong
					 
					 /*Ve_Tieu_De_Gam();
					 VeMenuChinh(0);*/
					 break;
				 }
				 break;
			 case ClickTrai: // phim Z( mo o)
				 if (bTrangThaiChoiGame) {
					 click_Trai(cViTriConTro.Y, cViTriConTro.X);
				 }
				 break;
			 case ClickPhai: // phim x(cam co)
				 if (bTrangThaiChoiGame) {
					 click_Phai(cViTriConTro.Y, cViTriConTro.X);
				 }
				 break;
		}
	}
}
void Xu_Li_Su_Kien() {
	while(true) {
		DWORD DW_Number_OF_Enents = 0; //luu lai su kien hien tai
		DWORD DW_Number_OF_Enents_Read = 0; // luu lai su kien da dc lap

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);//THIET BI DAU VAO
		GetNumberOfConsoleInputEvents(HConsoleInput, &DW_Number_OF_Enents);//dat su kien dau vao cua gia dien cho bien DW_Number_OF_Enents

		if (DW_Number_OF_Enents) {
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DW_Number_OF_Enents]; //khai bao con tro EventBuffer.
			ReadConsoleInput(HConsoleInput, IREventBuffer, DW_Number_OF_Enents, &DW_Number_OF_Enents_Read); // dat cac su kien dc luu vao con tro EventBuffe.

			//chay vong lap de doc du kien
			for (DWORD i = 0; i < DW_Number_OF_Enents; i++) {
				if (IREventBuffer[i].EventType == KEY_EVENT) { //NEU LA SU KIEN PHIM
					Xu_Li_Phim(IREventBuffer[i].Event.KeyEvent);
				}
				//else if (IREventBuffer[i].EventType == MOUSE_EVENT) { //NEU LA SU KIEN CHUOT

				//}
			}
		}
	}
}


// design 
void Ve_Tieu_De_Gam() {
	short i;
	for (i = 0; i < ConsoleWidth; i++) {
		cout << "-";
	}
	char c[20];
	strcpy(c, "Game Do Min");
	setColorBGTextXY((ConsoleWidth / 2)-5, 1, 11, 0, c);
	cout << "\n";
	for (i = 0; i < ConsoleWidth; i++) {
		cout << "-";
	}
}
void VeTrangthaichoigame(short sTrangThai,short sCheDo,short sIndex) {

	sVTDangChon = sIndex;

	char c[30];
	strcpy(c, "BAN DO: ");
	setColorBGTextXY(1, 3, 15, 0, c); cout << CT_Bang.sDong << "x" << CT_Bang.sCot<<"\n";
	strcpy(c, "SO BOM: ");
	setColorBGTextXY(1, 4, 15, 0, c); cout << CT_Bang.sSoBom<< "\n";
	strcpy(c, "So Co Da Cam: ");
	setColorBGTextXY(1, 5, 15, 0, c); cout << CT_Bang.sSoCo << "\n";

	// ve Menu thang thua 
	if (sCheDo == 1) {
		strcpy(c, "  =>Luu Lai<=  "); // luu lai khi chua choi xong
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(c) / 2), 4, 15, ((sIndex == 1) ? 2 : 0), c);
	}
	if (sCheDo == 2) {
		strcpy(c, "  =>Luu Diem<=  "); // luu diem khi thang
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(c) / 2), 4, 15, ((sIndex == 1) ? 2 : 0), c);
	} 
	if (sCheDo == 3) {
		strcpy(c, "  =>Choi Lai<=  "); 
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(c) / 2), 4, 15, ((sIndex == 1) ? 2 : 0), c);
	}
	if (sCheDo == 1) { // tiep tuc game khi chua choi xong
		strcpy(c, "  =>Continue<=  ");
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(c) / 2), 3, 15, ((sIndex == 0) ? 2 : 0), c);
	}
	if (sCheDo >= 1) {
		strcpy(c, "  =>EXIT<=  ");// thoatgame
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(c) / 2), 5, 15, ((sIndex == 2) ? 2 : 0), c);
	}

	if (sTrangThai == 1) {
		strcpy(c, "TRANG THAI : DANG CHOI\n");
		setColorBGTextXY(ConsoleWidth-22, 4, 15, 0, c);
	}
	if (sTrangThai == 2) {
		strcpy(c, "TRANG THAI : THANG\n");
		setColorBGTextXY(ConsoleWidth - 22, 4, 9, 0, c);
	}
	if (sTrangThai == 3) {
		strcpy(c, "TRANG THAI : THUA\n");
		setColorBGTextXY(ConsoleWidth - 22, 4, 12, 0, c);
	}
	cout << "\n";
	for (short i = 0; i < ConsoleWidth; i++) {
		cout << "-";
	}
}
void VeMenuChinh(short sIndex) {
	//cap nhat lai vi tri dang chon va tong muc cua menu
	sVTDangChon = sIndex;
	sTongMuc = 4;
	

	// Ve menu
	char sTextMenuChinh[50];
	strcpy(sTextMenuChinh , "  =>NEW GAME<=  ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(sTextMenuChinh) / 2), 7, 15,((sIndex==0) ? 2 : 0), sTextMenuChinh);
	strcpy(sTextMenuChinh, "  =>POINT<=  ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(sTextMenuChinh) / 2), 8, 15, ((sIndex == 1) ? 2 : 0), sTextMenuChinh);
	strcpy(sTextMenuChinh, "  =>INFORMATION<=  ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(sTextMenuChinh) / 2), 9, 15, ((sIndex == 2) ? 2 : 0), sTextMenuChinh);
	strcpy(sTextMenuChinh, "  =>EXIT<=  ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(sTextMenuChinh) / 2), 10, 15, ((sIndex == 3) ? 2 : 0), sTextMenuChinh);

}
void VeMenuCapDo(short sIndex) {
	//cap nhat lai vi tri dang chon va tong muc cua menu cap do
	sVTDangChon = sIndex;
	sTongMuc = 4;

	// Ve menu
	char sTextMenuCapDo[50];
	strcpy(sTextMenuCapDo, "  =>Chon Cap Do<=  ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(sTextMenuCapDo) / 2), 7, 15, 1, sTextMenuCapDo);

	strcpy(sTextMenuCapDo, "  De (9 x 9 && 10 Bom)  ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(sTextMenuCapDo) / 2), 10, 15, ((sIndex == 0) ? 2 : 0), sTextMenuCapDo);
	strcpy(sTextMenuCapDo, "  Trung binh (16 x 16 && 40 Bom)  ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(sTextMenuCapDo) / 2), 11, 15, ((sIndex == 1) ? 2 : 0), sTextMenuCapDo);
	strcpy(sTextMenuCapDo, "  Kho (24 x 24 && 99 Bom)  ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(sTextMenuCapDo) / 2), 12, 15, ((sIndex == 2) ? 2 : 0), sTextMenuCapDo);
	strcpy(sTextMenuCapDo, "  =>EXIT<=  ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(sTextMenuCapDo) / 2), 13, 15, ((sIndex == 3) ? 2 : 0), sTextMenuCapDo);
}

//trang thong tin
void Trang_Thong_Tin() {
	//_setmode(_fileno(stdin), _O_U16TEXT);   // nhập có dấu
	_setmode(_fileno(stdout), _O_U16TEXT);  // xuất có dấu

	//cViTriConTro = { 0,0 }; // vị trí con trỏ.
	//Cursor(true);//an hien con tro;
	sTRang = 7;
	deleteRow(1, ConsoleHeight - 2);

	setColor(9); // màu xanh
	wcout << L"                               ==>( GAME DÒ MÌN )<==                \n" << endl;
	setColor(15); // màu trắng
	for (int i = 0; i < ConsoleWidth; i++) {
		wcout << "-";
	}
	setColor(12); // màu đỏ
	wcout << endl;
	wcout << L"             PHẦN 1: CÁCH CHƠI GAME.                \n"<<endl;
	setColor(15); // chữ màu trắng
	wcout << L"1: Người chơi khởi đầu với một bảng ô vuông trống thể hiện :bãi mìn."<<endl;
	wcout << L"2: Chọn một ô trong bảng: \n";
	wcout << L"        +) Nếu không may chọn vào ô có min . Thì trò chơi kết thúc.\n";
	wcout << L"        +) Trường hợp thường sảy ra hơn là ô đó không có mìn,và 1 vùng các ô sẽ được mở ra cùng với các con số.";
	wcout << L"Số trên 1 ô là chỉ số mìn có trong 8 ô lân cận.\n";
	wcout << L"3) Nếu chắc chắn là ô đó có mìn. Thì người chơi có thể cắm cờ vào ô đó bằng cách nhấn nút x trên bàn phím.\n";
	wcout << L"4) Khi 8 ô lân cận của 1 ô số đã có đủ số mìn thì các ô còn lại sẽ không có mìn.\n";
	wcout << L"5) Trò chơi kết thúc và phần thắng dành cho người chơi khi người chơi tìm được  tất cả các ô có mìn.\n\n";
	setColor(12);
	wcout << L"             PHẦN 2: CÁC PHÍM ĐỂ CHƠI GAME.                \n" << endl;
	setColor(15);
	wcout << L"1) Các phím mũi tên: \n";
	wcout << L"         +) Để di chuyển lên, xuống, trái, phải con trỏ trong bảng ô để dò mìn.\n";
	wcout << L"         +) Để di chuyển chọn chức năng.\n";
	wcout << L"2) Phím x: Cắm cờ.\n";
	wcout << L"3) Phím z: Mở ô.\n";
	wcout << L"4) Phím ENTER: Chọn Chức Năng.\n";
	wcout << L"5) Phím ESC: Thoát trò chơi.\n\n";
	setColor(12);
	wcout << L"             PHẦN 3: MỨC ĐỘ GAME.                \n" << endl;
	setColor(15);
	wcout << L"1) Mức Dễ (beginner): Bảng có 9x9 ô vuông, có 10 bom.\n";
	wcout << L"2) Mức Trung Bình (intermediate): Bảng có 16x16 ô vuông, có 40 bom.\n";
	wcout << L"3) Mức Khó (expert): Bảng có 24x24 ô vuông, có 99 bom.\n\n";
	setColor(2);
	wcout << L"             CHÚC NGƯỜI CHƠI CHƠI VUI VẺ!!!!!!!        \n";
}