#include"main.h"
#include"Console.h"
#include"Ham.h"


//trang, vi tri dang chon, tong muc
short sTRang, sTongMuc, sVTDangChon;

int main() {

	resizeConsole(ConsoleWidth, ConsoleHeight); // thay doi kich thuoc cua man hinh console
	SetConsoleTitle(TEXT("Game Do Min")); //  thay doi ten cua man hinh console(tieu de game)

	
	Ve_Tieu_De_Gam();
	VeMenuChinh(0);
	sTRang = 1;
	Cursor(false);//an hien con tro;
	Xu_Li_Su_Kien();
	

	return 0;
}