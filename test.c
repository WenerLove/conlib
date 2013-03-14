/*
 * Author: Wener
 * E-mail: wenermail@gmail.com
 * Site: http://blog.wener.me
 */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "conlib.h"

#define T(c,description) puts(#c);c;puts(description "  �����������");getch();



int main(int argc, char *argv[])
{
	puts("conlib���Գ���:");
	T(conlib_init(),"��ʼ������̨��");
	 
	T(gotoxy(5,5),"���ڹ����������");
	T(hide_cursor(),"��겻����"); 
	T(show_cursor(50),"��ʾһ����"); 
	T(show_cursor(100),"��ʾ�������"); 
	T(settitle("conlib test program"),"���ñ���");
	T(set_text_color(ConRed),"����������ɫ");
	T(set_background_color(ConWhite),"���ñ�����ɫ");
	
	clrscr();
	
	const ConKey* ck;
	const ConMouse* cm;
	const ConControlKeyState *cks; 

	char spaceLine[80] = {[0 ... 78] = ' ',[79] = '\0'};

	

	puts("��������:");
	hide_cursor();
#define Tand(v,t)	if(v & t)printf(#t "  ");
#define Teq(v,t)	if(v == t)printf(#t "  ");
	while(1)
	{
		gotoxy(12,0);
		printf("clock: %d\t", (int)clock()); 
		
		ck = getkey();
		cm = getmouse();
		cks = NULL; 
		gotoxy(0,1);
		printf("key value: %p", ck);
		gotoxy(0,2);
		printf("mouse value: %p", cm);
		
		gotoxy(0,3);
		if(ck != NULL)
		{
			cks = ck->ctrl_key_state;
			printf("key code: %d is %s", ck->key, ck->state? "����": "�ͷ�");			
		}
			
		gotoxy(0,4);
		if(cm != NULL)
		{
			cks = cm->ctrl_key_state;
			printf("mouse position: %2d, %2d\n", cm->x, cm->y);
			printf(spaceLine);
			printf(spaceLine);
			printf(spaceLine);
			printf(spaceLine);
			gotoxy(0,5);
			if(cm->event != ConMOUSE_WHEELED && cm->event != ConMOUSE_HWHEELED)
			{
				Tand(cm->button,ConMOUSE_1ST_BUTTON);
				Tand(cm->button,ConMOUSE_2ND_BUTTON);
				Tand(cm->button,ConMOUSE_3RD_BUTTON);
				Tand(cm->button,ConMOUSE_4TH_BUTTON);
				Tand(cm->button,ConMOUSE_RIGHT_BUTTON);
				printf(" �� ������\n");
			}else
				printf("����� [%s] ��\n", cm->button > 0? "ǰ":"��");
			Teq(cm->event,ConMOUSE_CLICK);
			Teq(cm->event,ConMOUSE_DBCLICK);
			Teq(cm->event,ConMOUSE_MOVED);
			Teq(cm->event,ConMOUSE_WHEELED);
			Teq(cm->event,ConMOUSE_HWHEELED);
			printf(" �� ������\n");
		}

		gotoxy(0,10);
#define S(c)	(c? "ON": "OFF")

		if(cks != NULL)
			printf("NUM[%3s]  SCROLL[%3s]  CAPS[%3s]\n"
					"LCTRL[%3s]  LALT[%3s]  RALT[%3s]  RCTRL[%3s]\n"
					"SHIFT[%3s]  ENHANCED[%3s]"
					, S(cks->numlock), S(cks->scrolllock), S(cks->capslock)
					, S(cks->left_ctrl), S(cks->left_alt), S(cks->right_alt), S(cks->right_ctrl)
					, S(cks->shift), S(cks->enhanced));
		console_test();
	}	
	
return EXIT_SUCCESS;
}
