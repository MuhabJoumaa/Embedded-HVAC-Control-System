#include "p18f45k22.h"
#include "ext_ram.h"
#include "razconst.h"
#include <delays.h>


extern void Print_symb (unsigned char sim, unsigned char symbol);
void univup (unsigned int *),onlkont (void),Print_str();
void fconw (void),rconw (void),read_flag(void),koniop (void);	
void Pr_hex (void),Pr_des (void),Pr_temper (void),Pr_bd (void),
	uslper (void),Pr_napr(void),Pr_bd_e(void);





void univup (unsigned int *blozu)
{
b=*blozu;
On_st=1;
//;**********************************************************
 //;         Ќј„јЋќ ѕќƒ–ј«ƒ≈Ћј  ќЌ“–ќЋя
 //;**********************************************************
 for(;;)
	{
	 if (fl_end) {fl_end=0;return;}

	 read_tabwb(kom,adr);

	 if(kom==0xff) return;

	 if(!(kom&0xf0))
	  {
			On_st=0;
		   switch(kom)
				{
				 case 0x01: onlkont(); 
						    break;	
/*
				
				 case 0x02:read_flag();
						   read_tabw(adres);
						   if((op_b&INDF0)==0)b=adres;
						    break;
				 case 0x03:read_flag();
						   read_tabw(adres);
						   if(op_b&INDF0)b=adres;
					    	break;
				 case 0x04: //1-но байтное значение и провер.на рав-во
							op=adr;//константа
							 read_tabw(conb);//адрес переменной
							 rconb();//считываем слово
							 if(op_b==op) 
							 	{
								 read_tabw(adres);
							   	 b=adres;	
								}
							else {
									b=b+2;	
								 }								
						    break;
				 case 0x05: //2-х байтное значение означ.адрес в ќ«” 1-но
						     //байт.знач.и провер.на рав-во
							 conb=adr;//адрес константы
							 rconb();//считываем константу
							 op=op_b;
							 read_tabw(conb);//адрес переменной
							 rconb();//считываем слово
							 if(op_b==op)
							 	{
								 read_tabw(adres);
							   	 b=adres;	
								}
							else {
									b=b+2;	
								 }								
						    break;

				 case 0x06: //1-но байтное значение и провер.на рав-во
							op=adr;//константа
							 read_tabw(conb);//адрес переменной
							 rconb();//считываем слово
							 if(op_b!=op) 
							 	{
								 read_tabw(adres);
							   	 b=adres;	
								}
							else {
									b=b+2;	
								 }
						    break;

				 case 0x07: //2-х байтное значение означ.адрес в ќ«” 1-но
						     //байт.знач.и провер.на рав-во
							 conb=adr;//адрес константы
							 rconb();//считываем константу
							 op=op_b;
							 read_tabw(conb);//адрес переменной
							 rconb();//считываем слово
							 if(op_b!=op)
							 	{
								 read_tabw(adres);
							   	 b=adres;	
								}
							else {
									b=b+2;	
								 }								
						    break;
				 case 0x08: //1-но байтное значение и провер.на нерав-во
							op=adr;//константа
							 read_tabw(conb);//адрес переменной
							 rconb();//считываем слово
							 if(op_b>op) 
							 	{
								 read_tabw(adres);
							   	 b=adres;	
								}
							else {
									b=b+2;	
								 }								
						    break;
				 case 0x09: //2-х байтное значение означ.адрес в ќ«” 1-но
						     //байт.знач.и провер.на нерав-во
							 conb=adr;//адрес константы
							 rconb();//считываем константу
							 op=op_b;
							 read_tabw(conb);//адрес переменной
							 rconb();//считываем слово
							 if(op_b>op)
							 	{
								 read_tabw(adres);
							   	 b=adres;	
								}
							else {
									b=b+2;	
								 }								
						    break;						    
				 case 0x0a: //1-но байтное значение и провер.на нерав-во
							op=adr;//константа
							 read_tabw(conb);//адрес переменной
							 rconb();//считываем слово
							 if(op_b<op) 
							 	{
								 read_tabw(adres);
							   	 b=adres;	
								}
							else {
									b=b+2;	
								 }								
						    break;						    
				 case 0x0b://2-х байтное значение означ.адрес в ќ«” 1-но
						     //байт.знач.и провер.на нерав-во
							 conb=adr;//адрес константы
							 rconb();//считываем константу
							 op=op_b;
							 read_tabw(conb);//адрес переменной
							 rconb();//считываем слово
							 if(op_b<op)
							 	{
								 read_tabw(adres);
							   	 b=adres;	
								} 
							else {
									b=b+2;	
								 }								
						    break;	
*/
					    
				 case 0x0c: switch(adr)
				 				{
				 				 case 0:read_tabw(adres);//адресJUMP
										*blozu=adres;
										fl_end=1;
				 				 		break;
				 				 case 1:read_tabw(adres);//адресkJUMP
										b=adres;
				 				 		break;
								 case 2:(*blozu)=b;
				 				 		break;					 				 		
				 				 case 3://kNOP
				 				 		break;
			 				 		
				 				}
						    break;
				 case 0x0d: uslper();//клавиатура						    
						    break;	
			 		}
				}
			else {
				 koniop();	
				if(On_st)*blozu=b;
				On_st=0;	    
				}
	}
}
//;************************************************
//;ѕќƒѕ–ќ√–јћћј –≈∆»ћј Ћќ√»„≈— »’ ќѕ≈–ј÷»…
//;************************************************
void koniop (void)
{
while(fl==0)
	{
if(kom==0xfe)
	{
	 b=b-2;
	return;
	}	
if(kom==0xff)
	{
	 b=b-2;
	return;
	}	
if(!(kom&0xf0))
	{
	 b=b-2;
	return;
	}	

switch(kom)
	{

	 case 0x11://запись по адресу двухбайтового числа
		 conw=adr;
		 read_tabw(timer);//адрес числа
		 fconw();
		break;
/*
	case 0x14://заполнение буфера константой
			 conb=adr;//адрес буфера
			 read_tabwb(kol,op_b);//длина буфера 
			 while (kol!=0)
				{
				 fconb();
			     conb++;
				 kol--;
				}
			break;
	case 0x15://копирование буферов
			 conb=adr;//начало блока параметров
			 read_tabwb(conw,kol);//начало буфера,длина блока
			 while (kol!=0)
				{
				 rconb();//читаем первое число из блока
				 conb=conb+1;// адрес считывани€
				 adr=conb;
				 conb=conw;
				 fconb();//заносим в пам€ть
				 conw++; //увеличиваем адрес записи
				 conb=adr;
				 kol--;
				}
			break;			
	case 0x16://x+y=y
			  conb=adr;		
			  rconb();//читаем первое число	
			  oper=op_b;
			  read_tabw(conb);//
			  rconb();//читаем 2-е число
			  op_b+=oper;
			  fconb();
			  break;
*/
	case 0x17://пересылка 1 байта из одного адреса в другой
			 conb=adr;//адрес 1 €чейки
			 rconb();//считываем число по адресу
			 read_tabw(conb);//адрес 2 €чейки
			 fconb();//запись числа по адресу
			break;
	case 0x18: //sbros  bita v 0
				read_flag();
			   INDF0=(~op_b)&INDF0;
			   break;								  
	case 0x19: //ustanovka bita v 1
				read_flag();
			   INDF0=op_b|INDF0;
			   break;
/*	case 0x1a://v1=v1/v2
			  conb=adr;		
			  rconb();//читаем первое число	
			  oper=op_b;
			  read_tabw(conb);//
			  rconb();//читаем 2-е число
			  op_b=oper/op_b;
			  fconb();					
			  break;
*/
	case 0x1b://запись в ќ«” константы
			 conb=(unsigned int)adr;//адрес
			 read_tabwb(kol,op_b);
		 	fconb();//запись по адресу константы
			break;
	case 0x1c://inc €чейки ќ«”
			 conb=adr;//адрес
		 	rconb();//считываем значение
			 op_b++;//увеличиваем на 1
			 fconb();//заносим в пам€ть
		break;
	case 0x1d://декремент €чейки ќ«”
		 	 conb=adr;//адрес
			 rconb();//считываем значение
			 op_b--;//уменьшаем на 1
		 	 fconb();//заносим в пам€ть
		break;	
	case 0x1e://ADD CONST к байту
			 conb=adr;//адрес
			 rconb();//считываем байт
		 	 oper=op_b;
			 read_tabwb(kol,op_b)
			 oper=oper^op_b;
			op_b=oper;
		 	 fconb();//заносим в пам€ть
		break;
	case 0x1f://SUB CONST из байта
			 conb=adr;//адрес
			 rconb();//считываем значение
		 	 oper=op_b;
			 read_tabwb(kol,op_b)
			 oper=oper^op_b;
			op_b=oper;
		 	 fconb();//заносим в пам€ть
			break;
	case 0x20://	pSTOP
			 op_b=adr;
			if(op_b==1)
				{
				op_b=1;
				}
			else if(op_b==2)
				{
				op_b=2;
				}
			else if(op_b==3)
				{
				op_b=3;
				}
			 break;	
	case 0x21://BUZER ON
			 CCPR1L=64;//32
			 break;	
	case 0x22://BUZER OFF
			 CCPR1L=0;
			 break;	

	case 0x23://обнуление €чейки
			 conb=adr;
			 op_b=0;
			 fconb();
			 break; 
	case 0x24://подсчет секунд по 0,1 сек в -
			conb=adr;//адрес €чейки
			 rconb();//считываем значение в €чейке
			 if (!FCL1s) break;
			 if(!op_b) break;
			 op_b--;
			 fconb();
			 break;
	case 0x25://подсчет секунд по 0,1 сек в +
			 conb=adr;//адрес €чейки
			 rconb();//считываем значение в €чейке
			 if (!FCL1s) break;
			 op_b++;
			 fconb();
			 break;
	case 0x26://инверси€ €чейки
		 	 conb=adr;//адрес
		 	 rconb();//считываем значение
			 op_b=(!op_b)&0x01;
			 fconb();
	    	 break;
/*
	case 0x27://zoper=v1-v2
			  conb=adr;
			  rconb();
			  oper=op_b;
			  read_tabw(conb); 
			  rconb();
			  zOPER=oper-op_b;
			  break;
	case 0x28://подсчет секунд по 0,1 сек в -
			conb=adr;//адрес €чейки
			 rconb();//считываем значение в €чейке
			 if (!FCL1m) break;
			 if(!op_b) break;
			 op_b--;
			 fconb();
			 break;
*/
	case 0x29://подсчет секунд по 0,1 сек в +
			 conb=adr;//адрес €чейки
			 rconb();//считываем значение в €чейке
			 if (!FCL1m) break;
			 op_b++;
			 fconb();
			 break;	
//
/*
	case 0x2a://вывод  бита 
			read_flag();
			op_b=op_b&INDF0;
			f=0x30;
			if(op_b) f++;
			Print_symb (simvol,f);
			break;

	case 0x2b://запись указател€ чтени€ во внутреннюю EEPROM
			    eepromWriteByte(EE_AD_RD_L,w9.adr_ee_rd_l);
			    eepromWriteByte(EE_AD_RD_H,w9.adr_ee_rd_h);
				break;
	case 0x2c://чтение указателей из внутренней EEPROM
				// Ќј Ќј„јЋќ —≈јЌ—ј
			    eepromReadByte(EE_AD_RD_L);//считываем байт из EEPROM
				w9.adr_ee_rd_l=EEDATA;
			    eepromReadByte(EE_AD_RD_H);//считываем байт из EEPROM
				w9.adr_ee_rd_h=EEDATA;
			    eepromReadByte(EE_AD_WR_L);//считываем байт из EEPROM
				w8.adr_ee_wr_l=EEDATA;
			    eepromReadByte(EE_AD_WR_H);//считываем байт из EEPROM
				w8.adr_ee_wr_h=EEDATA;
				break;
	case 0x2d://увеличение указател€ чтени€ на „»—Ћќ
				w9.adrEEPROM_rd=w9.adrEEPROM_rd + adr;
				if(w9.adrEEPROM_rd >= 0x7c00)w9.adrEEPROM_rd=w9.adrEEPROM_rd-0x7c00;
				break;
	case 0x2e://уменьшение указател€ чтени€ на „»—Ћќ
				if(w9.adrEEPROM_rd >= adr) w9.adrEEPROM_rd = w9.adrEEPROM_rd - adr;
				else {w9.adr_ee_rd_h = 0x7b; 
						w9.adr_ee_rd_l = w9.adr_ee_rd_l - adr; }
				break;
	case 0x2f://присвоение битов
				read_flag();
				popa=op_b&INDF0;
				read_tabwb(kom,adr);
				read_flag();
				if(popa)INDF0=op_b|INDF0;//ustanovka bita v 1
				else INDF0=(~op_b)&INDF0;//sbros  bita v 0
				break;
*/
//
//
	case 0x30://установка курсора
			   simvol=adr;//адрес €чейки
			   break;	
	case 0x31://вывод строки с установкой курсора
				read_tabwb(stroka,simvol);
				read_tabw(conwt);
				Print_str();
				break;
	case 0x32://вывод символа с установкой курсора
				conb=adr;//read_tabw(conb);//адрес €чейки
				rconb();//считываем число
				adres=b;
				Print_symb(simvol,op_b);
				b=adres;
				break;
	case 0x33://вывод символа по текущему курсору
				op_b=adr;//read_tab(op_b);
				adres=b;
				Print_symb(simvol,op_b);
				b=adres;
				break;
/*
	case 0x34://вывод 1 байтового числа из ќ«” в hex виде по текущей позиции
				conb=adr;//read_tabw(conb);//адрес €чейки
				rconb();//считываем число
				adres=b;
				Pr_hex();
				b=adres;
				break;
*/

	case 0x34://вывод дельты температуры по текущей позиции
				conb=adr;//read_tabw(conb);//адрес €чейки
				rconb();//считываем число
				adres=b;
				op_b+=61;
				goto ddd;


	case 0x35://вывод 1 байтового числа из ќ«” в des виде по текущей позиции
				conb=adr;//read_tabw(conb);//адрес €чейки
				rconb();//считываем число
				adres=b;
				Pr_des();
				b=adres;
				break;

	case 0x36://вывод температуры по текущему положению курсора
				conb=adr;//read_tabw(conb);//адрес €чейки
				rconb();//считываем число
				adres=b;

ddd:			if(tTIMER2&&(blok_fl&0x40))
					{
					if(op_b<52){op_b=op_b*5;Pr_des();}
					else 
						{
						simvol=1;
						Print_symb(simvol,'-');
						Print_symb(simvol,'-');
						Print_symb(simvol,'-');
						}
					}
				else Pr_temper();

				b=adres;
				break;
	case 0x37://вывод знака-дес€тичного числа по текущей позиции
//			    conb=adr;//read_tabw(conb);//адрес €чейки
//				rconb();//считываем число
				if(F4&0x20)Pr_bd_e();
				else Pr_bd();
				break;

/*
	case 0x38://запись байта во внешную EEPROM из указател€ регистратора
				break;

	case 0x39://считывание байта из внешней EEPROM 
	  		    break;	

*/

		
	case 0x3a://считывание байта из внутренней EEPROM
				op=adr;//read_tab(op);//адрес в EEPROM внутренней
				read_tabw(conb);//адрес €чейки куда считывать
			    eepromReadByte(op);//считываем байт из EEPROM
				op_b=EEDATA;
				fconb();// записываеи число по адресу
				break;
	case 0x3b://запись байта во внутреннюю EEPROM
				op=adr;//read_tab(op);//адрес в EEPROM внутренней
				read_tabw(conb);//адрес €чейки откуда считывать
				rconb();//считываем число
			    eepromWriteByte(op,op_b);//записываем байт в EEPROM
				break;
//	case 0x3c://очистка всего экрана
//				Clr_disp ();
//				break;
//	case 0x3d://очистка строки (по номеру строки 1-3)
//				stroka=adr;//считали номер строки
//				simvol=1;
//				for(nt=0;nt<21;nt++)
//					{
//					 Print_symb(stroka,simvol,' ');
//					}
//				break;
//	case 0x3e://вывод на экран температуры большими цифрами
//				conb=adr;//read_tabw(conb);//адрес €чейки
//				rconb();//считываем число
//				Print_big();
//				break;
//	case 0x3f://вывод на экран специальных символов
//				op_b=adr-1;//номер символа
////				Print_spez();
//				break;
//	case 0x40://вывод на экран температуры средними цифрами
//				conb=adr;//read_tabw(conb);//адрес €чейки
//				rconb();//считываем число
//				Print_mid();
//				break;
//	case 0x41://вывод на экран часов большими цифрами
//				break;
//	case 0x42://очистка большой температуры
//				break;
//	case 0x43://вывод двоично-дес€тичного числа по текущей позиции
//			    conb=adr;//read_tabw(conb);//адрес €чейки
//				rconb();//считываем число
//				Pr_napr();
//				break;
/*
	case 0x44://выделение единиц минут
				tMIN5=MINUTE&0xf;
				break;
	case 0x45://увеличение указател€ записи на „»—Ћќ
				break;
	case 0x46://уменьшение указател€ записи на „»—Ћќ
				break;
*/
//	case 0x47://сравнение указат. чтени€ и записи на меньше
//	  		    break;	

//	case 0x48://pINC5MIN
//	  		    break;
//	case 0x49://pDEC5MIN
//	  		    break;
	case 0x4A://pREGTCOM
				if(tSECCOM==60)
					{
					tSECCOM=0;
				    eepromReadByte(EETCOM_M);
					op_b=EEDATA;op_b--;
					rtKMPm=~op_b;
					eepromWriteByte(EETCOM_M,op_b);
					if(op_b==195)
						{op_b=0xff;
						rtKMPm=~op_b;
						eepromWriteByte(EETCOM_M,op_b);
					    eepromReadByte(EETCOM_H);
						op_b=EEDATA;op_b--;
						rtKMPh_l=~op_b;
					    eepromWriteByte(EETCOM_H,op_b);
						if(op_b==155)
							{op_b=0xff;
							rtKMPh_l=~op_b;
							eepromWriteByte(EETCOM_H,op_b);
						    eepromReadByte(EETCOM_W);
							op_b=EEDATA;op_b--;
							rtKMPh_h=~op_b;
							eepromWriteByte(EETCOM_W,op_b);
							}
						}
					}

							if(rtKMPh_h < se_rtKMPh_h)
								{
								op=EETCOM_M;op_b_ee=~se_rtKMPm;
								eepromWriteByte(op,op_b_ee);//записываем байт в EEPROM
								op=EETCOM_H;op_b_ee=~se_rtKMPh_l;
								eepromWriteByte(op,op_b_ee);//записываем байт в EEPROM
								op=EETCOM_W;op_b_ee=~se_rtKMPh_h;
								eepromWriteByte(op,op_b_ee);//записываем байт в EEPROM
								rtKMPh_h = se_rtKMPh_h;
								rtKMPh_l = se_rtKMPh_l;
								rtKMPm = se_rtKMPm;
								}
							else if(rtKMPh_h == se_rtKMPh_h)
								{
								if(rtKMPh_l < se_rtKMPh_l)
									{
									op=EETCOM_M;op_b_ee=~se_rtKMPm;
									eepromWriteByte(op,op_b_ee);
									op=EETCOM_H;op_b_ee=~se_rtKMPh_l;
									eepromWriteByte(op,op_b_ee);
									rtKMPh_l = se_rtKMPh_l;
									rtKMPm = se_rtKMPm;
									}
								else if(rtKMPh_l == se_rtKMPh_l)
									{
									if(rtKMPm < se_rtKMPm)
										{
										op=EETCOM_M;op_b_ee=~se_rtKMPm;
										eepromWriteByte(op,op_b_ee);
										rtKMPm = se_rtKMPm;
										}
									}
								}


	  		    break;
	case 0x4B://pRDTCOM
			    eepromReadByte(EETCOM_M);
				op_b=EEDATA;rtKMPm=~op_b;
			    eepromReadByte(EETCOM_H);
				op_b=EEDATA;rtKMPh_l=~op_b;
			    eepromReadByte(EETCOM_W);
				op_b=EEDATA;rtKMPh_h=~op_b;
	  		    break;
/*

	case 0x4C://вывод 1 байтового числа из ќ«” в des виде по текущей позиции
				conb=adr;//read_tabw(conb);//адрес €чейки
				rconb();//считываем число
				op=op_b;
				f=(unsigned char)op/10;
				f+=0x30;
				Print_symb(simvol,f);
				f=op%10+0x30;
				Print_symb(simvol,f);
				break;
	case 0x4D://pEQWTIME	—–ј¬Ќ≈Ќ»≈ ¬–≈ћ≈Ќ» ¬ Ћё„≈Ќ»я
				break;
	case 0x4E://вывод 1 числа из ќ«” в HEX виде по текущей позиции
				conb=adr;//read_tabw(conb);//адрес €чейки
				rconb();//считываем число
				f=op_b;
				if(f<=9) f=f+0x30;
				else f=f+0x37;
				Print_symb(simvol,f);
				break;
	case 0x4F://»«ћ≈Ќ≈Ќ»≈  ќЌ“–ј—“Ќќ—“» ƒ»—ѕЋ≈я
//				Brightness (kontrast);
				break;
	case 0x50:// ‘ункци€ записи блока 128	
				break;
*/

		}//switch
	read_tabwb(kom,adr);
	}//while	
} //koniop

void fconw (void)
	{
	POSTINC0=*(char *)(&timer);
    POSTDEC0=*(char *)((char *)&timer+1);
	}

void rconw (void)
	{
	*(char *)(&timer) = POSTINC0;
    *(char *)((char *)&timer+1)=POSTDEC0;
	}
//;****************************************************
//;     ќЌ“–ќЋ№ ѕќ –ј«Ћ»„Ќџћ ѕј–јћ≈“–јћ
//;****************************************************
void onlkont (void)
{
fl_sovp=0;//флаг совпадени€ частей кода
kodusl=0;
kol_mask=1;//количество масок
for(i=0;i<8;i++) mask[i]=0;//буфер из 7 масок, нулевую игнорируем
kolpar=adr;

while(kolpar>0)
		{
		  read_tabwb(kom,adr);
		 if(kom!=3)
			{
			  kodusl=kodusl<<1;
			  for(i=1;i<=kol_mask;i++)
				{
				 mask[i]=mask[i]<<1;
				 if(i==kol_mask) mask[i]=mask[i]+1;
				}
			} 
	     switch(kom)
			{
			 case 0: //proverka flaga
					 read_flag();
			 		 op_b=op_b&INDF0;
					 if(op_b) kodusl++;
					 break;
			 case 1://значение 1-но байтное и провер.на рав-во
			 		 op=adr;//константa
					 read_tabw(conb);//адрес переменной
					 rconb();
					 if(!(op_b>op)) kodusl++;
					 break;
			 case 2://2-х байтное значение означ.адрес в ќ«” 1-но
				     //байт.знач.и провер.на рав-во
					 conb=adr;//адрес переменной
					 rconb();//считываем 
					 op=op_b;
					 read_tabw(conb);//адрес переменной
					 rconb();//считываем слово
					 if(!(op_b>op)) kodusl++;
					 break;
			 case 3: kol_mask++;
					 kolpar++;
					 break;
			 case 4: //значение 1-но байтное и провер.на рав-во
			 		 op=adr;//константa
					 read_tabw(conb);//адрес переменной
					 rconb();
					 if(op_b==op) kodusl++;
					 break;
			 case 5: //2-х байтное значение означ.адрес в ќ«” 1-но
				     //байт.знач.и провер.на рав-во
					 conb=adr;//адрес переменной
					 rconb();//считываем 
					 op=op_b;
					 read_tabw(conb);//адрес переменной
					 rconb();//считываем слово
					 if(op_b==op) kodusl++;
					 break;
			 case 6: //значение 1-но байтное и провер.на маску
			 		 op=adr;//константa
					 read_tabw(conb);//адрес переменной
					 rconb();
					 if(op_b&op) kodusl++;
					 break;
			}
	     kolpar--;
	    }
       read_tabw(etalon);//эталонный код услови€
       while (etalon!=0xffff)
	  	{
		 for(i=1;i<=kol_mask;i++)
				{
				 op=adr&mask[i];
				 j=kodusl&mask[i];
				 if(op==j)
					{
					 fl_sovp=1;
					 break;
					}
				}
			 if(fl_sovp==1)//ћј— ј —ќ¬ѕјЋј
				{
				 switch (kom)
				 	{
					 case 0:read_tabw(adres);
							*blozu=adres;
							 fl_end=1; 
							return;
					 case 1:read_tabw(adres);
							b=adres;
							return;
					 case 2:
							read_tabwb(kom,adr);
							koniop();//выполн€ем команду
		       				if(fl_end==1) return;
		       				fl_sovp=0;
				       		read_tabw(timer);
					       	if(timer==0xffff)
								{
								 read_tabw(adres);//адрес
								 *blozu=adres;
								 fl_end=1;
							return;
								}
					 		break;
					 case 3:
							read_tabwb(kom,adr);
							koniop();//выполн€ем команду
		       				if(fl_end==1) return;
					       fl_sovp=0;
		    			   read_tabw(timer);
					       if(timer==0xffff)
							{
							 read_tabw(adres);//адрес
							 b=adres;
							return;
							}
					 		break;	
					}
				}
			else {	//ћј— ј Ќ≈ —ќ¬ѕјЋј
				 if(kom>1)	
					{
					while(1)
						{
		     	    	read_tabw(timer);
						 if(timer==0xfefe)
							{
							break;
							}
						 if(timer==0xffff)
							{
							 b+=2;
						 	break;
							}
						}
					}else b=b+2;
	       	   }//else
		read_tabw(etalon);
	   }//while
}//onlkont

void read_flag(void)
{
 FSR0=0x80+((adr&0xf0)>>4); 
 switch(adr&0x0f)//maska	
		{
	   	 case 0: op_b=0x01;
	   	 		 break;
	   	 case 1: op_b=0x02;
	   	 		 break;
	   	 case 2: op_b=0x04;
	   	 		 break;
	   	 case 3: op_b=0x08;
	   	 		 break;
	   	 case 4: op_b=0x10;
	   	 		 break;
	   	 case 5: op_b=0x20;
	   	 		 break;
	   	 case 6: op_b=0x40;
	   	 		 break;
	   	 case 7: op_b=0x80;
	   	 		 break;				   	 		 				   	 		 
   	}
}



//;**********************************************************
//;  п.п режима опроса клавиатуры
//;**********************************************************
//	DB 1XH
//;      DW ADR1  наличие адресов необ€зательно
//;      DW ADR2
//;      DW ADR4
//;      DW ADR8
//;  ¬  ќƒ≈ 10Ќ D3-D0 биты активных кнопок
void uslper (void)
{
 op=0;KP=0;

if((KNOPKA==0x9)||(KNOPKA==0x5))KNOPKA=0;
//if((KNOPKA==0x1)&&(t_kl>15)){KNOPKA=0;return;}

if(KNOPKA)
	{
 	KP=KNOPKA;
	KNOPKA=0;
	}
 op=adr&0x0f;

 if ((KP==0)||((KP&op)==0))
	{
	 kn=0;
	 for (kn1=4;kn1>0;kn1--)
		{
		 if((op&0x01)==1) kn++;
		 op=op>>1;
		}
	 b=b+2*kn;
	}
 else {
	 kn=KP&op;
	 switch(kn)
		{
		 case 1: break;
		 case 2: if((op&0x01)==1) b+=2;
				 break;
		 case 4: for(kn1=2;kn1>0;kn1--)
					{
					 if((op&0x01)==1) b+=2;
					 op=op>>1;
					}
				 break;
		 case 8: for (kn1=3;kn1>0;kn1--)
					{
					 if((op&0x01)==1) b+=2;
					 op=op>>1;
					}
				 break;
		 default:kn=0;
				 for (kn1=4;kn1>0;kn1--)
					{
					 if((op&0x01)==1) kn++;
					 op=op>>1;
					}
				 b=b+2*kn;
				 return;
		}
       read_tabw(conwt);
       b=conwt;
      }
}







void Pr_hex (void)
{
op=op_b;
f=(op&0xf0)>>4;
if (f<=9) f=f+0x30;
else f=f+0x37;
Print_symb (simvol,f);

f=op&0x0f;
if(f<=9) f=f+0x30;
else f=f+0x37;
Print_symb (simvol,f);
}
//
void Pr_des (void)
{
z=op_b;
f=((unsigned char)((z&0xf0)>>4))*16;
timer=z&0x0f;
z=timer+f;
f=(unsigned char)(z/100);
if (f==0) f=' ';
else f+=0x30;
Print_symb(simvol,f);

op=(unsigned char)(z%100);
f=(unsigned char)op/10;
if ((f==0)&&(z<100)) f=' ';
else f+=0x30;
Print_symb(simvol,f);

f=op%10+0x30;
Print_symb(simvol,f);
}


/*
void Pr_napr (void)
{
z=op_b;
f=(unsigned char)(z/100)+0x31;
Print_symb(simvol,f);

op=(unsigned char)(z%100);
f=((unsigned char)op/10)+0x30;

Print_symb(simvol,f);
f=',';
Print_symb(simvol,f);

f=op%10+0x30;
Print_symb(simvol,f);
}
*/

void Pr_bd (void)
{
 op=rtKMPh_l;

f=((unsigned char)op/10)+0x30;
rtKMPh_l_2=f;

f=op%10+0x30;
rtKMPh_l_1=f;

 op=rtKMPh_h;

if(rtKMPh_h<100)
	{
	f=((unsigned char)op/10)+0x30;
	rtKMPh_h_2=f;
	
	f=op%10+0x30;
	rtKMPh_h_1=f;
	}
else 
	{

	f=((unsigned char)op/100)+0x30;
	rtKMPh_h_3=f;

	op=(unsigned char)(rtKMPh_h%100);
	f=((unsigned char)op/10)+0x30;
	rtKMPh_h_2=f;
	
	f=op%10+0x30;
	rtKMPh_h_1=f;
	}
}

void Pr_bd_e (void)
{
 op=t_l;

f=((unsigned char)op/10)+0x30;
rtKMPh_l_2=f;

f=op%10+0x30;
rtKMPh_l_1=f;

if(t_h)
	{
	 op=t_h;
	
	if(t_h<100)
		{
		rtKMPh_h_3=0x30;

		f=((unsigned char)op/10)+0x30;
		rtKMPh_h_2=f;
		
		f=op%10+0x30;
		rtKMPh_h_1=f;
		}
	else 
		{
	
		f=((unsigned char)op/100)+0x30;
		rtKMPh_h_3=f;
	
		op=(unsigned char)(t_h%100);
		f=((unsigned char)op/10)+0x30;
		rtKMPh_h_2=f;
		
		f=op%10+0x30;
		rtKMPh_h_1=f;
		}
	}
else
	{
	rtKMPh_h_1=rtKMPh_h_2=rtKMPh_h_3=0x30;
	}

/*
op=op_b;
f=(op&0xf0)>>4;
//if(f==0) f=' ';
//else 
f=f+0x30;

Print_symb (simvol,f);

f=op&0x0f;
f=f+0x30;
Print_symb (simvol,f);
*/
}


//
void Pr_temper (void)
{
 op=op_b;

 if(op<60)
	{
	if(op>50)
		{
		Print_symb(simvol,' ');
		Print_symb(simvol,'-');
		f=(60-op)+0x30;
		Print_symb(simvol,f);
		}
	else 
		{
		Print_symb(simvol,'-');
		op=60-op;
		op_b=op;
	  	f=op/10;
	  	if (f){f+=0x30;Print_symb(simvol,f);}

		f=op%10+0x30;
		Print_symb(simvol,f);
		}	
	}

  else {
		op=op-60;
		popa1=op;
		f=op/100;
		if ((f==0)&&(op<100)) f=' ';
		else f+=0x30;
		Print_symb(simvol,f);
		op=op%100;
		f=op/10;
	  	if (f) f+=0x30;
		 else  if (popa1>99) 
					{
					f=0x30;
					}
		 		else  f=' ';
		Print_symb(simvol,f);
//
		f=op%10+0x30;
		Print_symb(simvol,f);
//
       }
}

void Print_str(void)
	{
    ptd=b;
	 b=conwt++;
	 read_tab(op_b);
	 while(op_b!=0)
			{
			 Print_symb (simvol,op_b);
			 b=conwt++;		
			 read_tab(op_b);
			}
	 b=ptd;
	}


