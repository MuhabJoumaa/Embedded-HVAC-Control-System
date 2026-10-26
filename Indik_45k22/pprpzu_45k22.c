#include <p18f45k22.h>
#include "sysrm_25k22.h"
#include <delays.h>
#include "razconst.h"
#include <usart.h>


//25k22

#pragma	config	MCLRE=INTMCLR,WDTEN=ON,BOREN=ON,DEBUG=OFF//WORK
#pragma	config	CP0=ON,CP1=ON,CPB=ON,CPD=OFF	//WORK
#pragma	config	WRT0=ON,WRT1=ON,WRTB=ON,WRTC=OFF,WRTD=OFF
//
//#pragma	config	CP0=OFF,CP1=OFF,CPB=OFF,CPD=OFF  //DEBUG
//#pragma	config	MCLRE=EXTMCLR,WDTEN=OFF,BOREN=OFF,DEBUG=ON,WRTD=OFF  //DEBUG
//#pragma	config	WRT0=OFF,WRT1=OFF,WRTB=OFF,WRTC=OFF  //DEBUG
//
#pragma	config	CP2=OFF,CP3=OFF,WRT2=OFF,WRT3=OFF	//25k22
//
#pragma	config	PRICLKEN = OFF	//,PBADEN = OFF
//
#pragma	config 	PLLCFG=ON,FOSC=INTIO67
#pragma	config 	FCMEN=OFF,IESO=OFF
#pragma	config	BORV=285,WDTPS=512,PWRTEN=OFF
#pragma	config	PBADEN=OFF,CCP2MX=PORTC1
#pragma	config	LVP=OFF,XINST=OFF,STVREN=OFF
#pragma	config  EBTR0=OFF,EBTR1=OFF,EBTRB=OFF



//
#define T0_ON T0CONbits.TMR0ON = 1
#define T0_OFF T0CONbits.TMR0ON = 0
#define T1_ON T1CONbits.TMR1ON = 1
#define T1_OFF T1CONbits.TMR1ON = 0
#define T2_ON T2CONbits.TMR2ON = 1
#define T2_OFF T2CONbits.TMR2ON = 0
#define T3_ON T3CONbits.TMR3ON = 1
#define T3_OFF T3CONbits.TMR3ON = 0
//
#define Int_T0 INTCONbits.TMR0IF
#define Int_T0_EN INTCONbits.TMR0IF = 0; INTCONbits.TMR0IE = 1
#define Int_T0_DIS INTCONbits.TMR0IE = 0
//
#define Int_T1 PIR1bits.TMR1IF
#define Int_T1_EN PIR1bits.TMR1IF = 0; PIE1bits.TMR1IE = 1
#define Int_T1_DIS PIE1bits.TMR1IE = 0
//
#define Int_T2 PIR1bits.TMR2IF
#define Int_T2_EN PIR1bits.TMR2IF = 0; PIE1bits.TMR2IE = 1
#define Int_T2_DIS PIE1bits.TMR2IE = 1
//
#define Int_T3 PIR2bits.TMR3IF
#define Int_T3_EN PIR2bits.TMR3IF = 0; PIE2bits.TMR3IE = 1;
#define Int_T3_DIS PIE2bits.TMR3IE = 0;
//
#define Int_T4 PIR3bits.TMR4IF
#define Int_T4_EN PIR3bits.TMR4IF = 0; PIE3bits.TMR4IE = 1;
#define Int_T4_DIS PIE3bits.TMR4IE = 0;

//
#define Int_COM_RC PIR1bits.RCIF
#define Int_COM_TX PIR1bits.TXIF
#define On_COM_TX TXSTA1bits.TXEN = 1
#define Off_COM_TX TXSTA1bits.TXEN = 0

#define Int_COM_TX_EN PIE1bits.TX1IE = 1;
#define Int_COM_TX_DIS PIE1bits.TX1IE = 0;
#define Int_COM_RC_EN PIE1bits.RC1IE = 1; 
#define Int_COM_RC_DIS PIE1bits.RC1IE = 0; 

//COM2
#define Int_COM2_TX_EN   PIE3bits.TX2IE = 1
#define Int_COM2_TX_DIS   PIE3bits.TX2IE = 0
#define Int_COM2_RC_EN   PIE3bits.RC2IE = 1
#define Int_COM2_RC_DIS   PIE3bits.RC2IE = 0

#define Int_COM2_RC   PIR3bits.RC2IF
#define Int_COM2_TX    PIR3bits.TX2IF
//
#define On_COM2_TX TXSTA2bits.TXEN = 1
#define Off_COM2_TX TXSTA2bits.TXEN = 0


#define TMR1_res	TMR1H=0; TMR1L=0

/*
rom const char cmnd[]={
4,0x80,0x28,0xf0,0x81,0xff,0xff,0xff,//0  startCommunication
4,0x80,0x28,0xf0,0x82,0xff,0xff,0xff,//1  stopCommunication
6,0x80,0x28,0xf0,0x10,0x81,0x0a,0xff,//2  startDiagnosticSession 10400 	
4,0x80,0x28,0xf0,0x20,0xff,0xff,0xff,//3  stopDiagnosticSession	
5,0x80,0x28,0xf0,0x3e,0x01,0xff,0xff,//4  testerPresent 02-NO
5,0x80,0x28,0xf0,0x1a,0x80,0xff,0xff,//5  readECUIdentification
6,0x80,0x28,0xf0,0x14,0xff,0x00,0xff,//6  clearDiagnosticInformation
7,0x80,0x28,0xf0,0x18,0x00,0xff,0x00,//7  readDiagnosticTroubleCodesByStatus	
5,0x80,0x28,0xf0,0x21,0x01,0xff,0xff,//8  readDataByLocalIdentifier    	
4,0x80,0x28,0xf0,0x82,0xff,0xff,0xff,//9  
7,0x80,0x28,0xf0,0x82,0xff,0x00,0xff,//10 
0};// ������� ��� ������� ����� (��� ������)
*/

void Klav_read(void);
void Tr_COM(void);
void Obrabotka (void);
//void Tr_COM2_r(void);
void Tr_COM2(void);
void regist_avr (void);
unsigned char eepromReadByte( unsigned char Adr );
void eepromWriteByte( unsigned char Adr, unsigned char Data );


#pragma code
void high_isr(void);

#pragma code high_vector = 0x08
void intrpt_UART(void) { _asm GOTO high_isr _endasm }

#pragma code
void low_isr(void);

#pragma code low_vector = 0x18
void Interrupt (void)
	{
	 _asm
	 	 GOTO low_isr
	 _endasm
	}


#pragma code
#pragma interrupt high_isr
void high_isr(void)
	{
	if(PIR5bits.TMR4IF)
		{
		PIR5bits.TMR4IF=0;

if(stPORTA!=tPORTA){stPORTA=tPORTA;}
if(stPORTB!=tPORTB){stPORTB=tPORTB;}
if(stPORTC!=tPORTC){stPORTC=tPORTC;}
if(stPORTD!=tPORTD){stPORTD=tPORTD;}
if(stPORTE!=tPORTE){stPORTE=tPORTE;}

		if(znak==0)znak=1;
		else if(znak==1)znak=2;
		else if(znak==2)znak=3;
		else if(znak==3)znak=4;
		else if(znak==4)znak=0;
		else if(znak>4)znak=0;

if((znak+1)>(5-Bright))
	{
	PORTA=PORTB=PORTC=PORTD=PORTE=0xFF;
	}
else
	{
	PORTA=stPORTA;
	PORTB=stPORTB;
	PORTC=stPORTC;
	PORTD=stPORTD;
	PORTE=stPORTE;

	LATA=stPORTA;
	LATB=stPORTB;
	LATC=stPORTC;
	LATD=stPORTD;
	LATE=stPORTE;
	}

/*
		if(znak==0)
			{
			LATA = 0xff;
			LATBbits.LATB5=0;
			LATBbits.LATB2=1;
			znak=1;
			razr1=trazr1;

					if(!fSLEEP)LATA = razr1;
					else {
						if(tON_OFF<50)LATA = razr1;
						else LATA = 0xff;
						}
			}
		else if(znak==1)
			{
			LATA = 0xff;
			LATBbits.LATB2=0;
			LATBbits.LATB3=1;
			znak=2;
			razr2=trazr2;

		if(DAT_BIT&0x80)razr2&=0x7f;



					if(!fSLEEP) LATA = razr2;
					else {
						if(tON_OFF<50){if(rtKMPh_h>9)razr2&=0x7f;
										 LATA = razr2;}
						else LATA = 0x7f;
				}

			}
		else if(znak==2)
			{
			LATA = 0xff;
			LATBbits.LATB3=0;
			LATBbits.LATB4=1;
			znak=3;
			razr3=trazr3;

			if(!fSLEEP)
				{ 
				if(fIND_tC&&(F1&0x40)&&(F5&0x10)) razr3&=0x7f;//
				if(fIND_tC&&(!(F5&0x10))) razr3&=0x7f;//���� ��
				}
	
			if(!fSLEEP)LATA = razr3;
			else {
				if(tON_OFF<50)LATA = razr3;
				else LATA = 0xff;
				}
			}
		else if(znak==3)
			{
			LATA = 0xff;
			LATBbits.LATB4=0;
			LATBbits.LATB5=1;
			znak=0;
			razr4=trazr4;

			if(tblok_fl&0x40) razr4&=0xdf;  //fONDEFR


			if((!(F1&0x40))&&(F2&0x10)) razr4|=0x20;//

			if(tblok_fl&0x02) razr4&=0xfe;  //fCOLD

			if(tblok_fl&0x80) razr4&=0xef; // ������� .(HOT)

			if((!(F1&0x40))&&tENDHOT)razr4|=0x10;
			if((F1&0x40)&&tENDHOT)razr4=0xef;

			if((F5&0x20)&&(!(F1&0x40)))//fWAIT
				{razr4|=0x31;}

razr4&=0xdf;

			if(fSOS)razr4=0xce;

					if(!fSLEEP)LATA = razr4;
					else LATA = 0xff;
			}
*/
		}
	}

//razr4=0xfe; //* - ���� cool
//razr4=0xfd; //B - ���� segment
//razr4=0xfb; //C - ���� segment
//razr4=0xf7; //! � ������������ - �������������
//razr4=0xef; // ���������� - ������.
//razr4=0xdf; // ���������� - ������.
//razr4=0xbf; // - �����
//razr4=0x7f; // - evco

void Tr_COM(void) 
	{ 
	Int_COM_RC_DIS;
	yes_tr_com=0;
	com_trm=1;
	//
	buf_out[0]=buf_out[0]+ir-2;
	L_out=ir;
	summa_tr=0;
	for(ir=0; ir <= L_out; ir++ )
		{
		summa_tr = summa_tr + buf_out[ir];
		}
	L_out++;
	buf_out[L_out]=summa_tr;
	com_line=0;
	//
	p_out = 0;
	On_COM_TX;
	Int_COM_TX_EN;
	}	

void Tr_COM2(void) 
	{ 
	Int_COM2_RC_DIS;
	yes_tr_com2=0;
	com_trm2=1;
	//
	buf_out2[0]=buf_out2[0]+ip2-2;
	L_out2=ip2;
	summa_tr2=0;
	for(ip2=0; ip2 <= L_out2; ip2++ )
		{
		summa_tr2 = summa_tr2 + buf_out2[ip2];
		}
	L_out2++;
	buf_out2[L_out2]=summa_tr2;
//	com_line=0;
	//
	p_out2 = 0;
	On_COM2_TX;
	Int_COM2_TX_EN;
	}	
/*
void Tr_COM2_r(void) 
	{ 
	Int_COM2_RC_DIS;
	yes_tr_com2=0;
	com_trm2=1;
	//
	buf_out2[0]=buf_out2[0]+ir2-2;
	L_out2=ir2;
	summa_tr2=0;
	for(ir2=0; ir2 <= L_out2; ir2++ )
		{
		summa_tr2 = summa_tr2 + buf_out2[ir2];
		}
	L_out2++;
	buf_out2[L_out2]=summa_tr2;
//	com_line=0;
	//
	p_out2 = 0;
	On_COM2_TX;
	Int_COM2_TX_EN;
	}
*/	

#pragma code
#pragma interruptlow low_isr
void low_isr (void)//���� ��� �������� ������
	{

 if(PIR2bits.TMR3IF)
		{
		 PIR2bits.TMR3IF=0;
		 TMR3H=0x3c;//3C
		 TMR3L=0x80;//

//		 TMR3H=0xcf;//3C
//		 TMR3L=0x22;//

		 ClrWdt();
			if((CLOC1s==20)||(CLOC1s==10))
				{if((tester_lin!=0xf1)&&(tester_lin!=0xf2)&&(!multi2))f_multi2_lin=1;}

//			if((CLOC1s==15)||(CLOC1s==5))
	//			{if((tester_lin!=0xf1)&&(tester_lin!=0xf2)&&(!multi2))f_otop_lin=1;}

//		if(!CLOC_04s){CLOC_04s=4;CLOC1s--;}	
	//		CLOC_04s--;

			CLOC1s--;
			if(!(CLOC1s&0x1))
				{
				 F_MEN=1;//10��� � �������
				 Klav_read();
				 if(!CLOC1s)
					{
					CLOC1s=20;FCL1s=1;
					CLOC1m--;
					if(!CLOC1m)
						{
						 CLOC1m=60;
						 FCL1m=1;//1 ������
						}
					}
				CLO30s--;
				if(!CLO30s)
					{
					 CLO30s=5;
					F1=F1^0x40;	//�������� fMIGAN
					}
				}
		}

if(com_trm&&Int_COM_RC)irr=RCREG1;
if(!com_trm&&Int_COM_TX){Off_COM_TX;Int_COM_TX=0;}


	 if(Int_COM_RC)
		{

		if(yes_tr_com)
			{
			irr=RCREG1;
			yes_tr_com=0;
			p_in=0;p_res=0;
			return;
			}

		TMR0L=1;T0_ON;
		Int_T0_EN;
//
		buf_in[p_in] = RCREG1; 
//
		if((buf_in[0]&0x80)&&(rs_mes_end)&&(!p_in))
			{
		if(buf_in[0]>0x9a)
			{p_res=0;p_in=0;rs_mes_end=1;buf_in[0]=0;return;}
			rs_mes_start=1;
			rs_mes_end=0;
			L_in=(buf_in[0]&0x3f)+2;//����� ���� ������
			summa=0;summa = buf_in[0];
			p_in++;p_res=0;
			}
		else if(rs_mes_start&&((buf_in[1]==0x31)||(buf_in[1]==0x32)))//�������
				{
				rs_mes_start=0;
				res[p_res] = buf_in[p_in];
				summa = summa + buf_in[p_in];
				p_in++;p_res++;
				}
			else if((!rs_mes_start)&&(!rs_mes_end))
					{
//					if(buf_in[2]!=0x28)
//						{p_res=0;p_in=0;rs_mes_end=1;return;}
					res[p_res] = buf_in[p_in];
					summa = summa + buf_in[p_in];

					 if((p_res==L_in)&&((buf_in[2]==0x28)||(buf_in[2]==0x29))&&(buf_in[0]&0x80))
						{
//						T4_OFF;TMR4=0;
//						Int_T4 = 0;Int_T4_DIS;	
						rs_mes_end=1;
						L_res=L_in;
						summa=summa-buf_in[p_in];
						if((summa==buf_in[p_in])&&(buf_in[0]&0x80))
							{
							rs_mes=1;

							schetcik2++;
							ver_mod=res[0];
							com_line=res[2];
							fl_Kline=1;
							if(buf_in[2]==0x29){multi2=1;pult_m=0x2b;}
							if(buf_in[2]==0x28){multi2=0;pult_m=0x2a;}
							}
						else schetcik3++;
		
//						p_res=0;p_in=0;
						rs_mes_end=1;rs_mes_start=0;
						return;
						}

//					else {rs_mes=0;p_in=0;rs_mes_end=1;rs_mes_start=0;return;}
					p_res++;p_in++;
					}
					if((!(buf_in[0]&0x80))&&((buf_in[0]&0x7f)>15)&&rs_mes_end&&(!p_in)) 
						{rs_mes=0;
p_in=0;rs_mes_end=1;rs_mes_start=0;return;}
					if(p_in>40){p_res=0;p_in=0;rs_mes_end=1;rs_mes_start=0;rs_mes=0;}
			}

	else if(Int_COM_TX&&com_trm)
		{
		Int_COM_TX=0;
		if(( p_out <= L_out+1 )&&(L_out>3))
			{
//			End_COM_TX;
			TXREG1=buf_out[p_out++];
			}
		else {
				Int_COM_TX_DIS;
//				End_COM_TX;
				com_trm=0;
				Int_COM_RC_EN;
				irr = RCREG1; 
				yes_tr_com=1;
				p_out=0;L_out=0;
//				Off_COM_TX;

//		TMR0L=1;T0_ON;
//		Int_T0_EN;
				
			 }
		}
	else if(Int_T0)
			{
			Int_T0=0;
			Int_T0_DIS;T0_OFF;
			p_in=0;p_res=0;
			rs_mes_end=1;rs_mes_start=0;
			op_b = RCREG1; 
			}


if(com_trm2&&Int_COM2_RC)ip2=RCREG2;
if(!com_trm2&&Int_COM2_TX){Off_COM2_TX;Int_COM2_TX=0;}


	 if(Int_COM2_RC&&(!com_trm2))
		{

		if(yes_tr_com2)
			{
			ipp=RCREG2;
			yes_tr_com2=0;
			p_in2=0;p_res2=0;
			return;
			}
//
		buf_in2[p_in2] = RCREG2; 
//
		TMR1H=0xf3;TMR1L=0x00;T1_ON;Int_T1_EN;

		if((buf_in2[0]&0x80)&&(rs_mes_end2)&&(!p_in2))
			{
		if(buf_in2[0]>0x96)//
			{p_res2=0;p_in2=0;rs_mes_end2=1;buf_in2[0]=0;return;}
			rs_mes_start2=1;
			rs_mes_end2=0;
			L_in2=(buf_in2[0]&0x3f)+2;//����� ���� ������
			summa2=0;summa2 = buf_in2[0];
			p_in2++;p_res2=0;
			}
		else if(rs_mes_start2&&((buf_in2[1]==0x2b)||(buf_in2[1]==0x2a)||(buf_in2[1]==0xf1)))//�������
				{
				rs_mes_start2=0;
				res2[p_res2] = buf_in2[p_in2];
				summa2 = summa2 + buf_in2[p_in2];
				p_in2++;p_res2++;
				}
			else if((!rs_mes_start2)&&(!rs_mes_end2))
					{
//					if(buf_in[2]!=0x28)
//						{p_res=0;p_in=0;rs_mes_end=1;return;}
					res2[p_res2] = buf_in2[p_in2];
//
					if(p_res2<=L_in2)
						{
					summa2 = summa2 + buf_in2[p_in2];
						p_res2++;p_in2++;
						}
//
						else
						{
						p_res2++;p_in2++;
						}
					}
					if((!(buf_in2[0]&0x80))&&((buf_in2[0]&0x7f)>15)&&rs_mes_end2&&(!p_in2)) 
						{rs_mes2=0;p_in2=0;rs_mes_end2=1;rs_mes_start2=0;return;}
					if(p_in2>40){p_res2=0;p_in2=0;rs_mes_end2=1;rs_mes_start2=0;rs_mes2=0;}
			}

	else if(Int_COM2_TX&&com_trm2)
		{
		Int_COM2_TX=0;
		if(( p_out2 <= L_out2+1 )&&(L_out2>3))
			{
//			End_COM_TX;
			TXREG2=buf_out2[p_out2++];
			}
//		if(( p_out2 <= L_out2 )&&(L_out2>3))
		else 
			{
				Int_COM2_TX_DIS;
//				End_COM_TX;
				com_trm2=0;
				Int_COM2_RC_EN;
				ip2 = RCREG2; 
				yes_tr_com2=1;
				p_out2=0;L_out2=0;
//				Off_COM_TX;
			
			 }
		}
	else if(Int_T1)
			{
			Int_T1=0;
			Int_T1_DIS;T1_OFF;
			rs_mes2=0;
			rs_mes_end2=1;rs_mes_start2=0;
			ip2 = RCREG2;
 			if((p_res2>5)&&(p_res2<40))
				{
				p_res2--;
				p_in2--;
				}
			L_res2=L_in2;
			summa2=summa2-res2[L_res2];
			tester_lin=buf_in2[2];
			com_line2=res2[2];

//���� �� ������. �����
					if((buf_in2[2]==0xf0)&&(buf_in2[1]==0xf1))
						{
						schetcik5=20;
						ip2=3;f_stend_hand=1;
		//
						mT_ISP=res2[ip2++];
						mT_AIR=res2[ip2++];
						utUPR_BT=res2[ip2++];
						uUPR_STEND=res2[ip2++];
						}




/*

			 if((p_res2>=L_in2)&&((buf_in2[2]==0xf1)||(buf_in2[2]==0xf2)))
				{
				if(summa2==res2[L_res2])
					{
					rs_mes_t=1;
					com_line2=res2[2];
//

					if(tmr<60000)tmr++;
//
					if(buf_in2[1]==0x2b)tmr=0;
 					if(tmr>20)pult_m=0x2a;

//
//���� �� ������� ������ �����
					if(((buf_in2[1]==pult_m)&&(pult_m==0x2a))||(buf_in2[2]==0xf2))
						{
						if(L_res2>0x14)
							{
							rs_mes2_yes=1;
							multi1=1;tmr1++;multi2=0;
							tester_lin=buf_in2[2];
							ip2=3;
							mT_ISP=res2[ip2++];
							mT_AIR=res2[ip2++];
							tUPR_BT=res2[ip2++];
							iSOST_UPR1=res2[ip2++];
							iSOST_UPR2=res2[ip2++];
							iSOST_UPR3=res2[ip2++];
							iDAT_BIT=res2[ip2++];
	//
							sSTATUS2=res2[ip2++];
							mSOST_UPR1=res2[ip2++];
							mSOST_UPR2=res2[ip2++];
							mSOST_UPR3=res2[ip2++];
							T_ISP2=res2[ip2++];
							T_AIR2=res2[ip2++];
							mDAT_BIT=res2[ip2++];
							mUPR_BT=res2[ip2++];
							sZADT2=res2[ip2++];
							mfAVR_IND2=res2[ip2];
							}
						else
							{
							ip2=3;
							rs_mes2_yes=1;
							tester_lin=buf_in2[2];
							mT_ISP=res2[ip2++];
							mT_AIR=res2[ip2++];
							tUPR_BT=res2[ip2++];
							iSOST_UPR1=res2[ip2++];
							iSOST_UPR2=res2[ip2++];
							iSOST_UPR3=res2[ip2++];
							if(res2[ip2++]==0xaa)
								{
								iSOST_UPR1=0;
								iSOST_UPR2=0;
								iSOST_UPR3=0;
								iSOST_UPR_dop=0;
								z_nom_err=0;
								z_rtKMPh_l=0;
								tUPR_BT_dop=0;
								}
							else
								{
								iSOST_UPR_dop=res2[ip2++];
								z_nom_err=res2[ip2++];
								z_rtKMPh_l=res2[ip2++];
								tUPR_BT_dop=res2[ip2];
								}
							}

						}
//
//���� �� ������� ������ �����
					else if((buf_in2[1]==pult_m)&&(pult_m==0x2b)&&(buf_in2[2]==0xf1))
						{
						if(L_res2>0x10)
							{
							rs_mes2_yes=1;
							multi2=1;multi1=0;
							tmr2++;
							tester_lin=buf_in2[2];
							ip2=3;
							mT_ISP=res2[ip2++];
							mT_AIR=res2[ip2++];
							tUPR_BT=res2[ip2++];
							iSOST_UPR1=res2[ip2++];
							iSOST_UPR2=res2[ip2++];
							iSOST_UPR3=res2[ip2++];
							iDAT_BIT=res2[ip2++];
	//
							sSTATUS1=res2[ip2++];
							mSOST_UPR1=res2[ip2++];
							mSOST_UPR2=res2[ip2++];
							mSOST_UPR3=res2[ip2++];
							T_ISP1=res2[ip2++];
							T_AIR1=res2[ip2++];
							mDAT_BIT=res2[ip2++];
							mUPR_BT=res2[ip2++];
							sZADT1=res2[ip2++];
							mfAVR_IND1=res2[ip2];
							}
						}
					}
				}
   */
//else
//������� ������ �� �������
			  if((p_res2>L_in2)&&(buf_in2[2]==0x2a)&&(buf_in2[1]==0x2b))
				{
				if(summa2==res2[L_res2])
					{
					rs_mes2_yes=1;
					rs_mes_t=1;
					ip2=4;
					com_line2=res2[2];
//new_t
	if(res2[3]==7)F4|=0x20;//ERR
	if(res2[3]==3)F5|=0x40;//UPR
					tester_lin=0x2a;
//
					sSTATUS1=res2[ip2++];
					mSOST_UPR1=res2[ip2++];
					mSOST_UPR2=res2[ip2++];
					mSOST_UPR3=res2[ip2++];
		//			T_ISP1=res2[ip2++];
		//			T_AIR1=res2[ip2++];
					ip2=ip2+2;
					mDAT_BIT=res2[ip2++];
					mUPR_BT=res2[ip2++]&0xef;
//					sZADT1=res2[ip2++];
//					mfAVR_IND1=res2[ip2];
					}
				}
//
//���� ������� ������ �� �������
			 else if((p_res2>L_in2)&&(buf_in2[2]==0x2b)&&(buf_in2[1]==0x2a))
				{
				if(summa2==res2[L_res2])
					{
					rs_mes2_yes=1;
					multi1=1;
					tester_lin=0;
					ip2=3;
					f_config_t2=res2[ip2++];
//
if(f_config_t2==7)F4|=0x20;//ERR
if(f_config_t2==3)F5|=0x40;//UPR
					sSTATUS2=res2[ip2++];
					mSOST_UPR1=res2[ip2++];
					mSOST_UPR2=res2[ip2++];
					mSOST_UPR3=res2[ip2++];
//					T_ISP2=res2[ip2++];
//					T_AIR2=res2[ip2++];
					ip2=ip2+2;
					mDAT_BIT=res2[ip2++];
					mUPR_BT=res2[ip2++]&0xef;
//					sZADT2=res2[ip2++];
//					mfAVR_IND2=res2[ip2];
					}
				}
//			else {p_res2=0;p_in2=0;return;}

				p_res2=0;p_in2=0;

			switch(com_line2)
					{
/*
					 case 0x81://startCommunication
//
							ip2=0;
							buf_out2[ip2++]=0x80;
							buf_out2[ip2++]=0xf1;
							buf_out2[ip2++]=pult_m;
							buf_out2[ip2++]=0xc1;
							buf_out2[ip2++]=0x6b;
							buf_out2[ip2]=0x8f;
//
							Tr_COM2();
//
						break;
	
					 case 0x82://stopCommunication
//
							ip2=0;
							buf_out2[ip2++]=0x80;
							buf_out2[ip2++]=0xf1;
							buf_out2[ip2++]=pult_m;
							buf_out2[ip2]=0xc2;
//
							Tr_COM2();
//
						break;	

					 case 0x10://startDiagnosticSession
//
							ip2=0;
							buf_out2[ip2++]=0x80;
							buf_out2[ip2++]=0xf1;
							buf_out2[ip2++]=pult_m;
							buf_out2[ip2++]=0x50;
							buf_out2[ip2]=0x81;
//
							Tr_COM2();
//
						break;	
					 case 0x20://stopDiagnosticSession
//
							ip2=0;
							buf_out2[ip2++]=0x80;
							buf_out2[ip2++]=0xf1;
							buf_out2[ip2++]=pult_m;
							buf_out2[ip2]=0x60;
//
							Tr_COM2();
//
						break;	
*/
					 case 0x21://readDataByLocalIdentifier

						if(L_res2==16){rs_mes2_yes=1;pult_m=0x2a;}
				//		else break;	
						rs_mes2_yes=0;

					if(pult_m==0x2a)
						if(f_stend_hand==0)tUPR_BT=res2[5];

						if(((tester_lin==0xf2)||(tester_lin==0xf0))&&(pult_m==0x2a))
							{
							buf_out2[0]=0x80;
							buf_out2[1]=0xf1;
							if(tester_lin==0xf1)buf_out2[2]=pult_m;
							if(tester_lin==0xf2)buf_out2[2]=0x2a;

							buf_out2[3]=0x61;

						if(f_stend_hand)buf_out2[4]=sf_config_t;
						else buf_out2[4]=f_config_t;
//
							ip2=5;tmr3++;
//
							buf_out2[ip2++]=iT_ISP;
							buf_out2[ip2++]=iT_AIR;
							buf_out2[ip2++]=U_nap;
							buf_out2[ip2++]=U_pr1;
							buf_out2[ip2++]=U_pr2;
//
							buf_out2[ip2++]=uSOST_UPR1|iSOST_UPR1;
							buf_out2[ip2++]=uSOST_UPR2|iSOST_UPR2;
							buf_out2[ip2++]=uSOST_UPR3|iSOST_UPR3;
//
						//	ip2+=8;
				//				
							buf_out2[ip2++]=I_CL_isp1;
							buf_out2[ip2++]=I_CL_isp2;
							buf_out2[ip2++]=I_CL_knd1;
							buf_out2[ip2++]=I_CL_knd2;
							buf_out2[ip2++]=U_CL_isp1;
							buf_out2[ip2++]=U_CL_isp2;
							buf_out2[ip2++]=U_CL_knd1;
							buf_out2[ip2++]=U_CL_knd2;
				//
//
						if(f_stend_hand)buf_out2[ip2++]=ssDAT_BIT;
						else buf_out2[ip2++]=sDAT_BIT;
//
							buf_out2[ip2++]=I_CL_DEF;

						
							if(multi1)buf_out2[ip2++]=I_KL_ISP;
							else buf_out2[ip2++]=I_CL_CON;

							buf_out2[ip2++]=I_CL_CMP;
					//
							buf_out2[ip2++]=uUPR_BT;
							buf_out2[ip2++]=sZADT;
							buf_out2[ip2++]=ifAVR_IND;
							buf_out2[ip2++]=sUPR_BT;
							buf_out2[ip2]=sSTATUS;
//
							if(f_config_t&0x10)
								{
								ip2++;
								buf_out2[ip2++]=I_CL_isp3;
								buf_out2[ip2]=U_CL_isp3;
								}
//
							Delay10KTCYx(3);
							//
							Tr_COM2();
							}
/*

						else if((tester_lin==0xf1)&&(pult_m==0x2a))
							{
							buf_out2[0]=0x80;
							buf_out2[1]=0xf1;
							if(tester_lin==0xf1)buf_out2[2]=pult_m;
							if(tester_lin==0xf2)buf_out2[2]=0x2a;

							buf_out2[3]=0x61;
							buf_out2[4]=f_config_t;
//
							ip2=5;tmr3++;
//
							buf_out2[ip2++]=iT_ISP;
							buf_out2[ip2++]=iT_AIR;
							buf_out2[ip2++]=U_nap;
							buf_out2[ip2++]=U_pr1;
							buf_out2[ip2++]=nom_err;
//
							buf_out2[ip2++]=uSOST_UPR1|iSOST_UPR1;
							buf_out2[ip2++]=uSOST_UPR2|iSOST_UPR2;
							buf_out2[ip2++]=uSOST_UPR3|iSOST_UPR3;
//
							buf_out2[ip2++]=uSOST_UPR_dop|iSOST_UPR_dop;
//							buf_out2[ip2++]=iuSOST_UPR_dop;
//
							buf_out2[ip2++]=U_CL_isp1;
							buf_out2[ip2++]=U_CL_isp2;
							buf_out2[ip2++]=U_CL_isp3;
							buf_out2[ip2++]=U_CL_knd1;
							buf_out2[ip2++]=U_CL_knd2;
//
							buf_out2[ip2++]=t_nom;
							buf_out2[ip2++]=t_l;
							buf_out2[ip2++]=t_h;
							buf_out2[ip2++]=t_sost1;
							buf_out2[ip2++]=t_sost2;
							buf_out2[ip2++]=t_sost3;
							buf_out2[ip2++]=t_sost_dop;
//
							buf_out2[ip2++]=sDAT_BIT;
					//
							if(F5&0x40)buf_out2[ip2++]=tech_upr;
							else buf_out2[ip2++]=uUPR_BT;
//
							buf_out2[ip2++]=sZADT;
							buf_out2[ip2++]=ifAVR_IND;
							buf_out2[ip2++]=sUPR_BT;
							buf_out2[ip2++]=sSTATUS;
//
							buf_out2[ip2++]=U_davl;
//
							f_config_dop&=0xfc;
							if(F5&0x40)f_config_dop=f_config_dop|(tech_upr_dop&0x03);
							else f_config_dop=f_config_dop|(uSOST_UPR_dop&0x03);
//
							buf_out2[ip2++]=f_config_dop;
							buf_out2[ip2++]=rtKMPm;
							buf_out2[ip2++]=rtKMPh_l;
							buf_out2[ip2++]=rtKMPh_h;

					//
							Delay10KTCYx(3);
							//
							Tr_COM2();

							}
						else if((tester_lin==0xf1)&&(pult_m==0x2b))
							{
							buf_out2[0]=0x80;
							buf_out2[1]=0xf1;
							buf_out2[2]=pult_m;
							buf_out2[3]=0x61;
							buf_out2[4]=f_config_t;
//
							ip2=5;tmr4++;
//
							buf_out2[ip2++]=iT_ISP;
							buf_out2[ip2++]=iT_AIR;
							buf_out2[ip2++]=U_nap;
							buf_out2[ip2++]=U_pr1;
//
							buf_out2[ip2++]=uSOST_UPR1|iSOST_UPR1;
							buf_out2[ip2++]=uSOST_UPR2|iSOST_UPR2;
							buf_out2[ip2++]=uSOST_UPR3|iSOST_UPR3;
//
							buf_out2[ip2++]=I_CL_isp3;
							buf_out2[ip2++]=I_CL_isp2;
							buf_out2[ip2++]=U_CL_isp3;
							buf_out2[ip2++]=U_CL_isp2;
//
							buf_out2[ip2++]=sDAT_BIT;
//
							buf_out2[ip2++]=I_CL_DEF;
							buf_out2[ip2++]=I_KL_ISP;
							buf_out2[ip2++]=I_CL_CON;
					//
					if(uUPR_BT&0x1)uUPR_BT|=0x10;
							buf_out2[ip2++]=uUPR_BT;
							buf_out2[ip2++]=sZADT;
							buf_out2[ip2++]=ifAVR_IND2;
							buf_out2[ip2++]=sUPR_BT;
							buf_out2[ip2]=sSTATUS;
//
							if(f_config_t&0x10)
								{
								ip2++;
								buf_out2[ip2++]=I_CL_isp3;
								buf_out2[ip2]=U_CL_isp3;
								}
					//
							Tr_COM2();
							}
*/

//����� ������� ������ �������
						if(tester_lin==0x2a)
							{
							buf_out2[0]=0x80;
							buf_out2[1]=0x2a;
							buf_out2[2]=pult_m;
							buf_out2[3]=0x61;
							buf_out2[4]=0x01;
//
if(F4&0x20)	buf_out2[4]=0x07;//ERR
if(F5&0x40)	buf_out2[4]=0x03;//UPR
//
							ip2=5;
//
							buf_out2[ip2++]=sSTATUS;
							buf_out2[ip2++]=tSOST_UPR1&0xf3;
							buf_out2[ip2++]=tSOST_UPR2;
							buf_out2[ip2++]=tSOST_UPR3&0x53;
							buf_out2[ip2++]=T_isp;
							buf_out2[ip2++]=T_air;
							buf_out2[ip2++]=DAT_BIT;
							buf_out2[ip2++]=sUPR_BT;
							buf_out2[ip2++]=sZADT;
							buf_out2[ip2]=ifAVR_IND;
//
//
							Tr_COM2();	
							}//
						break;	

// 
				}
	//		tester_lin = 0;	

			}

	}







rom far const unsigned char NUM[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,\
									 0x82,0xf8,0x80,0x90,\
									0x88,0x83,0xc6,0xa1,0x86,0x8e};

rom far const unsigned char NUM_ZN[]={0xff,0x88,0x83,0xc6,0xa1,0x86,\
									 0x8e,0xf8,0x89,0xcf,\
									0x88,0x83,0xc7,0xa1,0x86,0x8e};

rom far const unsigned char NUM_ZN50[]={0x8c,0x88,0x83,0xc6,0xa1,0xc1,\
									 0x8e,0xf8,0x89,0x90,\
									0x88,0x83,0xc7,0xa1,0x86,0xf7};

//			if(symbol==0x74)f=0x87;//t


void Print_symb (unsigned char sim, unsigned char symbol)
	{
	if(symbol>0x4f)
		{
		if(symbol<0x60)
			{
			f=symbol&0x0f;
			if(symbol<0x50)tarrom=&NUM_ZN[0];
			else tarrom=&NUM_ZN50[0];
			tarrom=tarrom+f;
			if(sim==1)	trazr3=*(tarrom);
			else if(sim==2)	trazr2=*(tarrom);
			else if(sim==3)	trazr1=*(tarrom);
			else if(sim==5)	trazr2=*(tarrom);
			else if(sim==0xf)	trazr1=*(tarrom);
			}
		else
			{
//			if(symbol==0x55)f=0xe0;
//			if(symbol==0x5f)f=0xff;
			if(symbol==0x68)f=0x8b;
			if(symbol==0x63)f=0xa7;
			if(symbol==0x6e)f=0xab;//o
			if(symbol==0x6f)f=0xa3;//o
			if(symbol==0x72)f=0xaf;//r
			if(symbol==0x74)f=0x87;//t
			if(sim==1)	trazr3=f;
			else if(sim==2)	trazr2=f;
			else if(sim==3)	trazr1=f;
			}
		}
	else if(symbol>0x3f)
		{
		f=symbol&0x0f;
		tarrom=&NUM_ZN[0];
		tarrom=tarrom+f;
		if(sim==1)	trazr3=*(tarrom);
		else if(sim==2)	trazr2=*(tarrom);
		else if(sim==3)	trazr1=*(tarrom);
		}
	else if(symbol>0x2f)
		{
		f=symbol&0x0f;
		tarrom=&NUM[0];
		tarrom=tarrom+f;
		if(sim==1)	trazr3=*(tarrom);
		else if(sim==2)	trazr2=*(tarrom);
		else if(sim==3)	trazr1=*(tarrom);
		}
	else
		{
		if(symbol==0x20)f=0xff;
		if(symbol==0x2d)f=0xbf;
		if(sim==1)	trazr3=f;
		else if(sim==2)	trazr2=f;
		else if(sim==3)	trazr1=f;
		}
	if(simvol<3)simvol++;	
	}



void Displ(void)
	{
			razr1=trazr1;
		if(DAT_BIT&0x80)razr1&=0x7f; //fSTANB

//		if(F4&0x10) razr1&=0x7f;//fON_CND
		if(F5&0x04) razr1&=0x7f;//fON_CND

			if(fSLEEP) 
				{
				if(tON_OFF<50){if(rtKMPh_h>9)razr1&=0x7f;}
				else razr1 = 0x7f;
				}
//����� � ��� ��� ��� ���������
			if((F5&0x40)&&tech_upr)razr1&=0x7f; 
			if((F5&0x40)&&tech_upr_dop)razr1&=0x7f; 
			if((F4&0x40)&&(ver_mod==0x32))razr1&=0x7f; 

//
			razr2=trazr2;
//
			razr3=trazr3;
//
			razr4=0xf;

			if(!fSLEEP)
				{ 
				if(fIND_tC&&(F1&0x40)&&(F5&0x10)) razr4&=0xe;//
				if(fIND_tC&&(!(F5&0x10))) razr4&=0xe;//���� ��
				}

			if(tblok_fl&0x40) razr4&=0xb;  //fONDEFR
			if((!(F1&0x40))&&(F2&0x10)) razr4|=0x4;//

if(oT_air==85)razr4&=0xb; 

			if(((F1&0x40))&&(fTECH_DLT)) razr4&=0xb;//

			if(F5&0x08) razr4&=0xb;  //IND_DAVL
			if((!(F1&0x40))&&(F5&0x08)) razr4|=0x4;//



//
			if((tblok_fl&0x02)&&(!(F2&0x08))) razr4&=0xd;  //fCOLD
			if((tblok_fl&0x02)&&(!(F1&0x02))) razr4&=0xd;  //fCOLD
			if((tblok_fl&0x02)&&(F2&0x08)&&uCOMP) razr4&=0xd;  //fCOLD

//����� ����� � ��� ������
			if((F5&0x40)&&(tech_upr&0x80))razr4&=0xd; 
			


//�������� ���������� ����� �� ������
		if((!(F1&0x40))&&(F5&0x01)&&(F5&0x02)&&(!(DAT_BIT&0x80))) razr4|=0x2;//

			if((F5&0x40)&&multi2) razr4|=0x2;//

			if(F2&0x08)
				{
				if(F2&0x40)razr4&=0x7; // �������.(HOT)
				}
			else
				{
				if(tblok_fl&0x80) razr4&=0x7; // �������.(HOT)
	
				if((!(F1&0x40))&&tENDHOT)razr4|=0x8;
				if((F1&0x40)&&tENDHOT)razr4=0x7;
				}

			if(F5&0x40) razr4|=0x8;//


			if((F5&0x20)&&(!(F1&0x40)))razr4|=0xe; //fWAIT

			if(fSLEEP)
				{
				if(tON_OFF>50)razr2=razr3=0xff;
				if(F2&0x40)razr4=0x7; // �������.(HOT)
				else razr4=0xf;
				}
//�������� ���������� ����� �� ������
			if((!(F1&0x40))&&(F5&0x01)&&(F5&0x02)&&(!(DAT_BIT&0x80))) razr4|=0x8;//�������.(HOT)

//
if(sONOFF&&(!(F1&0x02))&&(tblok_fl&0x80)&&(F2&0x80))razr4&=0x7;//�������.(HOT)

if(fSYN_V_ISP && (!fONDEFR)) 
	{
	razr4&=0xb;//�������.(HOT)
	if((F1&0x40)&&(F1&0x02)&&(!uCOMP))razr4|=0x4;
	}

//����� ����� � ������ � ��� ������
		if(multi1)
			if((F5&0x40)&&((tech_upr&0x60)==0x60))razr4&=0x9; 
		if(multi2)
			if((F5&0x40)&&((tech_upr&0xa0)==0xa0))razr4&=0x9; 

	if(F5&0x40)
		{
		if((tech_upr&0x20)&&(t_nom_upr==1))razr4&=0xb;
		if((tech_upr&0x40)&&(t_nom_upr==2))razr4&=0xb;
		if((tech_upr&0x80)&&(t_nom_upr==3))razr4&=0xb;
		if((tech_upr&0xe0)==0xc0)razr4|=0x2;
		if((tech_upr&0x01)&&(t_nom_upr==4))razr4&=0xb;
		if((tech_upr&0x02)&&(t_nom_upr==5))razr4&=0xb;
		if((tech_upr&0x04)&&(t_nom_upr==6))razr4&=0xb;
		if((tech_upr&0x08)&&(t_nom_upr==7))razr4&=0xb;
		if((tech_upr&0x10)&&(t_nom_upr==8))razr4&=0xb;
		if((tech_upr&0x10)&&(t_nom_upr==4))razr4&=0xb;
		if((tech_upr_dop&0x01)&&(t_nom_upr==9))razr4&=0xb;
		if((tech_upr_dop&0x02)&&(t_nom_upr==10))razr4&=0xb;
		}



razr1=razr1^0xff;
razr2=razr2^0xff;
razr3=razr3^0xff;
razr4=razr4^0xff;


tPORTA=tPORTB=tPORTC=tPORTD=0xff;
tPORTE=0x7;

if(razr3&0x01)tPORTD&=0xfb; //A1*
if(razr3&0x02)tPORTD&=0xf7; //B1*
if(razr3&0x04)tPORTA&=0xbf; //C1*
if(razr3&0x08)tPORTC&=0xfe; //D1*
if(razr3&0x10)tPORTC&=0xfd; //E1*
if(razr3&0x20)tPORTD&=0xfd; //F1*
if(razr3&0x40)tPORTD&=0xfe; //G1*

if(razr2&0x01)tPORTD&=0xef; //A2*
if(razr2&0x02)tPORTD&=0xdf; //B2*
if(razr2&0x04)tPORTE&=0xfd; //C2*
if(razr2&0x08)tPORTE&=0xfb; //D2*
if(razr2&0x10)tPORTA&=0x7f; //E2*
if(razr2&0x20)tPORTC&=0xdf; //F2*
if(razr2&0x40)tPORTC&=0xef; //G2*


if(razr1&0x01)tPORTB&=0xfb; //A3*
if(razr1&0x02)tPORTB&=0xf7; //B3*
if(razr1&0x04)tPORTA&=0xef; //C3*
if(razr1&0x08)tPORTA&=0xdf; //D3*
if(razr1&0x10)tPORTE&=0xfe; //E3*
if(razr1&0x20)tPORTB&=0xfd; //F3*
if(razr1&0x40)tPORTB&=0xfe; //G3*
if(razr1&0x80)tPORTA&=0xf7; //H3*

if(razr4&0x01)tPORTB&=0xef; //A4*
if(razr4&0x02)tPORTB&=0xdf; //B4*
if(razr4&0x04)tPORTA&=0xfe; //C4*
if(razr4&0x08)tPORTA&=0xfd; //D4*

/*
if(stPORTA!=tPORTA){stPORTA=tPORTA;PORTA=stPORTA;}
if(stPORTB!=tPORTB){stPORTB=tPORTB;PORTB=stPORTB;}
if(stPORTC!=tPORTC){stPORTC=tPORTC;PORTC=stPORTC;}
if(stPORTD!=tPORTD){stPORTD=tPORTD;PORTD=stPORTD;}
if(stPORTE!=tPORTE){stPORTE=tPORTE;PORTE=stPORTE;}
*/

		}





#pragma code progrm=0x2a

void main(void)
{

PORTA = 0x00;
ANSELA = 0x0;	//0-analog
LATA = 0x00;
TRISA = 0x04; 

PORTB = 0x00; 
ANSELB = 0x00;
LATB = 0x00;
TRISB = 0x00;

PORTC = 0x40;
ANSELC = 0x08;
LATC =0x40;
TRISC = 0x88;  

PORTD = 0x40;
ANSELD = 0x00;
LATD =0x40;
TRISD = 0x80;  
//
PORTE = 0x00;
ANSELE = 0x00;
LATE =0x00;
TRISE = 0x00;  
 
ADCON0 = 0x0;
ADCON1 = 0x00;
ADCON2 = 0x26;

CM1CON0 = 0x0;
CM2CON0 = 0x0;

HLVDCON = 0x0;

OSCCON=0xe0;	//8MG
OSCCON2=0x00;

OSCTUNE=0x40;


T0CON = 0x47;//8MGZ 4*50000=200000(1:4):(1:16 TO 0X83)
T1CON = 0x31;
T3CON = 0x31;


RCONbits.IPEN=1;// 2 ������ ����������
INTCON=0xc0;//��������� 2 ������ ����������

//		��������� COM
		Open1USART( USART_TX_INT_OFF  &
				   USART_RX_INT_OFF    &
				   USART_ASYNCH_MODE  &
				   USART_EIGHT_BIT    &
				   USART_CONT_RX      &
				   USART_BRGH_HIGH, 188 ); // 10400 ??? ,191

TXSTA2 = 0x04; // Reset USART registers to POR state
RCSTA2 = 0x90;
SPBRG2 = 188;// Write baudrate to SPBRG1


TBLPTRU=0;
CLOC1s=20;//1 sek
CLO30s=5;//0,5 sek
CLOC1m=60;//1 min


ptrindex=0x100;

prer1[0]=&S1OZSPV;
prer1[1]=&S1OZREJ;
prer1[2]=&S1OZUPR;
prer1[3]=&S1OZOTOP;

S1OZSPV=0x4140;

//lin();

Obrabotka ();

op=0;

PR2=0xff;		//Tpwm = 64 x 4 x Tosc
T2CON=0x0E;		//PRESCALER /16
CCP1CON=0x0C;
CCPR1L=0;

IPR1bits.RC1IP = 0;  
IPR1bits.TX1IP = 0;
PIE1bits.TX1IE = 0; 

IPR3bits.RC2IP = 0;  
IPR3bits.TX2IP = 0;
PIE3bits.TX2IE = 0; 

//rs_mes_end=1;
//Int_COM_RC_EN;

INTCONbits.TMR0IE=0;//
INTCON2bits.TMR0IP=0;//������� ������� ���������� �� ������� 0

IPR1bits.TMR1IP=0;

TMR3H=0x3c;TMR3L=0x80;//

// TMR3H=0xcf;//3C
// TMR3L=0x22;//


IPR2bits.TMR3IP=0;
PIE2bits.TMR3IE=1;


T4CON = 0x7e;
PR4 = 110 ;  //156;
PIR5bits.TMR4IF=0;
IPR5bits.TMR4IP=1;
PIE5bits.TMR4IE=1;

Delay10KTCYx(250);
Delay10KTCYx(250);
Delay10KTCYx(250);
//Delay10KTCYx(250);
//Delay10KTCYx(250);


razr1=0xff;
razr2=0xff;
razr3=0xff;
razr4=0xff;

rs_mes_end2=1;
Int_COM2_RC_EN;

t_blk_isp1_c=10;t_blk_isp2_c=11;
t_blk_isp3_c=12;
t_blk_knd1_c=14;t_blk_knd2_c=16;

t_zmk_isp1_c=10;t_zmk_isp2_c=11;
t_zmk_isp3_c=12;
t_zmk_knd1_c=14;t_zmk_knd2_c=16;

f_str_mtch=1;
eepromReadByte(EETCOM_M);
op_b=EEDATA;rtKMPm=~op_b;
eepromReadByte(EETCOM_H);
op_b=EEDATA;rtKMPh_l=~op_b;
eepromReadByte(EETCOM_W);
op_b=EEDATA;rtKMPh_h=~op_b;

//
if((rtKMPm==0xff)||(rtKMPh_l==0xff)||(rtKMPh_h==0xff))
	{
	op=EETCOM_M;op_b_ee=0xff;
	eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM						
	op=EETCOM_H;						
	eepromWriteByte(op,op_b_ee);
	op=EETCOM_W;				
	eepromWriteByte(op,op_b_ee);

rtKMPm=rtKMPh_l=rtKMPh_h=0;
	}


//fAVR_LIN=1; 
U_nap = 125;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
for(;;)
	{
	if(RCSTA1bits.FERR)
		{
		p_in=0; op_b = RCREG1; 
		rs_mes_start=0;
		rs_mes_end=1;
		}
	if(RCSTA1bits.OERR)
		{
		RCSTA1bits.CREN=0;
		Nop();
		RCSTA1bits.CREN=1;
		rs_mes_start=0;
		rs_mes_end=1;
		}		

	if(RCSTA2bits.FERR)
		{
		p_in2=0; op_b = RCREG2; 
		rs_mes_start2=0;
		rs_mes_end2=1;
		}
	if(RCSTA2bits.OERR)
		{
		RCSTA2bits.CREN=0;
		Nop();
		RCSTA2bits.CREN=1;
		rs_mes_start2=0;
		rs_mes_end2=1;
		}		
/*	
	simvol=1;op_b=0x3d;
	Print_symb(simvol,op_b);
	simvol=2;op_b=0x3e;
	Print_symb(simvol,op_b);
	simvol=3;op_b=0x3f;
	Print_symb(simvol,op_b);
	simvol=4;op_b=0x31;
	Print_symb(simvol,op_b);
*/


//test
//tester_lin=0xf2;




//O������� ������� ������ �� �������

if(f_stend_hand == 0)
if((!com_trm)&&f_multi2_lin)
	{
	f_multi2_lin=0;

	buf_out2[0]=0x80;
	buf_out2[1]=0x2b;
	buf_out2[2]=0x2a;
	buf_out2[3]=0x21;
	buf_out2[4]=0x01;
//
if(F4&0x20)	buf_out2[4]=0x07;//ERR
if(F5&0x40)	buf_out2[4]=0x03;//UPR
//
	ip2=5;
	buf_out2[ip2++]=sSTATUS;
	buf_out2[ip2++]=tSOST_UPR1;
	buf_out2[ip2++]=tSOST_UPR2;
	buf_out2[ip2++]=tSOST_UPR3;
	buf_out2[ip2++]=T_isp;
	buf_out2[ip2++]=T_air;
	buf_out2[ip2++]=DAT_BIT;
	buf_out2[ip2++]=sUPR_BT;
	buf_out2[ip2++]=sZADT;
	buf_out2[ip2]=ifAVR_IND;
//
	Tr_COM2();
	}	
	

if(F_MEN)//||rs_mes)
	{
if(schetcik5)schetcik5--;
else f_stend_hand = 0;


	tAVR_LIN++;
	if(tAVR_LIN>20){fAVR_LIN=1;tAVR_LIN=0;}

//		 TMR3H=0x3c;//3C
//		 TMR3L=0x80;//


	if(rs_mes&&(!multi2))
		{
		s_com_line=com_line;
		tAVR_LIN=0;fAVR_LIN=0;
		rs_mes=0;
		ver_sil=res[0];	
		ip=3;
//
		f_config_t=res[ip++];
if((ver_sil==0x31)&&(f_config_t&0x10))F5|=0x80; //f_T_isp3

	sf_config_t=f_config_t;
if(f_stend_hand)f_config_t&0x0f;

		iT_ISP=res[ip++]+dTp;
		iT_AIR=res[ip++]+dTp;
		U_nap=res[ip++];
		U_pr1=res[ip++];
		U_pr2=res[ip++];
		uSOST_UPR1=res[ip++];
		uSOST_UPR2=res[ip++];
		uSOST_UPR3=res[ip++];
//
		I_CL_isp1=res[ip++];
		I_CL_isp2=res[ip++];
		I_CL_knd1=res[ip++];
		I_CL_knd2=res[ip++];

		U_CL_isp1=res[ip++];
		U_CL_isp2=res[ip++];
		U_CL_knd1=res[ip++];//
		U_CL_knd2=res[ip++];
//
		sDAT_BIT=res[ip++];

// sDAT_BIT|=0x80; //

//	if(ver_sil==0x31)sDAT_BIT^=0x4;

	if(f_stend_hand)ssDAT_BIT=sDAT_BIT;
//
		if(!(sDAT_BIT&0x20))//������ ���������
			{
			I_CL_DEF=res[ip++];
	//	
			if(multi1)I_KL_ISP=res[ip++];
			else I_CL_CON=res[ip++];
	//
			I_CL_CMP=res[ip];
			}
		else
			{
			sDAT_BIT&=0xdf;
			se_rtKMPm=res[ip++];
			se_rtKMPh_l=res[ip++];
			se_rtKMPh_h=res[ip];
//			sDAT_BIT&=0xbf;
			f_new_mtch=1;
//
			if((se_rtKMPm==0xff)||(se_rtKMPh_l==0xff)||(se_rtKMPh_h==0xff))
				{
				se_rtKMPm=se_rtKMPh_l=se_rtKMPh_h=0;f_new_mtch=0;
				}
			}
//
		if((f_config_t&0x10)&&(ver_sil==0x31))
			{
			ip++;F5|=0x80;
			I_CL_isp3=res[ip++];
			U_CL_isp3=res[ip];
			}
		else F5&=0x7f;

		if((f_config_t&0x10)&&(ver_sil==0x32))//���� ���. ����
			{
			ip++;F1|=0x04;
			T_cmp=res[ip++];
			if(sDAT_BIT&0x8)F1|=0x8;  //fZMK_Tcmp
			else F1&=0xf7;
			if(sDAT_BIT&0x10)F1|=0x10;  //fZMK_Tcmp
			else F1&=0xef;
			sDAT_BIT&=0xe7;
			}
		else 
			{
			F1&=0xe3;
			if(ver_sil==0x32)sDAT_BIT&=0xe7;
			}

		if((res[2]&0x02)&&(f_stend_hand==0))//���������� ������
			{
			ip++;F4|=0x2;
			U_davl=res[ip];
			if((U_davl&0xc0)==0x80){F3|=0x1;U_davl&=0x3f;}// fAD2
			else {
				  if(U_davl==0xff)F3|=0x1;
				  else	F3&=0xfe;
				 }
			}
		else {F4&=0xfd;U_davl=0;}
	//

	if((com_line&0x4)||(com_line&0x8)||((f_config_t&0x10)&&(ver_sil==0x32)))
		{ip++;uSOST_UPR_dop=res[ip];}
		if(com_line&0x8)//������� ������� �������
			{
			f_H_def=1;
			}
		if(com_line&0x4)//������� ��� ����� � �������
			{
			sDAT_BIT|=0x04;
			f_config_dop|=0x0c; //������� ����
			}
		else {f_config_dop=0;}

		if((f_config_t&0x10)&&(ver_sil==0x32))//���� ���. ����
			{
			uSOST_UPR_dop=res[ip]&0x3f;
			f_config_dop|=0x01; //������� ����
			}

		if((com_line&0x20)&&(ver_mod==0x32))//������� ������� �� ���. ����
			{
			F5|=0x4;
			f_config_dop|=0x10;
			}
		else {F5&=0xfb;f_config_dop&=0xef;}

	//
	
		if(com_line&0x10)F5|=0x1;//fDO_CMP
		else F5&=0xfe;
		if(com_line&0x80)F5|=0x2;//fDO_CMP
		else F5&=0xfd;

//U_davl=29;


//////////////////////////////////////
//TECH
//f_config_t|=0x80;
//F2|=0x80;
			F2&=0x3f;
			F2=F2|(f_config_t&0xc0);
//
		if(f_config_t&0x80)//OTOP_YES
			{
			if(POWER_OTOP>1)f_config_t|=0x20;//���� Otop_MAX
			else f_config_t&=0xdf;
			}

//f_config_t|=0x20;
//
		rs_mes_t=1;
//		tUPR_BT=0;

		if(com_line&0x4)//fON_CND ���� ��� ����.
			{
			if((sDAT_BIT&0x4)&&(tester_lin!=0xf2))
				{
				F4|=0x10;
//				sDAT_BIT&=0xfb;
				}
			else F4&=0xef;
			}
		else {F4&=0xef;}

		}		

	if(rs_mes&&multi2)
		{
		tAVR_LIN=0;fAVR_LIN=0;
		rs_mes=0;	
		ver_sil=res[0];	
		ip=3;
//
		f_config_t=res[ip++];

//if((ver_sil==0x31)&&(f_config_t&0x10))F5|=0x80; //f_T_isp3

		iT_ISP=res[ip++]+dTp;
		iT_AIR=res[ip++]+dTp;

//		iT_ISP=45;
//		iT_AIR=46;

		U_nap=res[ip++];
		U_pr1=res[ip++];
		U_pr2=res[ip++];
		uSOST_UPR1=res[ip++];

		uSOST_UPR2=res[ip++];
		uSOST_UPR3=res[ip++];

		ip+=8;
/*
		I_CL_isp1=res[ip++];
		I_CL_isp2=res[ip++];
		I_CL_knd1=res[ip++];
		I_CL_knd2=res[ip++];
		U_CL_isp1=res[ip++];
		U_CL_isp2=res[ip++];
		U_CL_knd1=res[ip++];
		U_CL_knd2=res[ip++];
*/
		sDAT_BIT=res[ip++];

		ip+=3;

/*
		I_CL_DEF=res[ip++];
//	
		I_CL_CON=res[ip++];
//
		I_KL_ISP=res[ip++];
		I_CL_CMP=I_KL_ISP;
*/
//
/*	if((f_config_t&0x10)&&(ver_sil==0x31))
		{
		I_CL_isp3=res[ip++];
		U_CL_isp3=res[ip];
		}
*/
	if(ver_sil==0x32)sDAT_BIT&=0xc7;

//////////////////////////////////////
//TECH
//f_config_t|=0x80;
//F2|=0x80;
			F2&=0x3f;
			F2=F2|(f_config_t&0xc0);
//
		if(f_config_t&0x80)//OTOP_YES
			{
			if(POWER_OTOP>1)f_config_t|=0x20;//���� Otop_MAX
			else f_config_t&=0xdf;
			}

		if(com_line&0x8)//������� ������� �������
			{
			f_H_def=1;
			}
//
		rs_mes_t=1;
//		tUPR_BT=0;
		}


	if(U_nap<40)
		{
		uSOST_UPR1=0;
		uSOST_UPR2=0;
		uSOST_UPR3=0;
		uSOST_UPR_dop=0;
		}

if(iSOST_UPR_dop&0x07)
	{
	if(iSOST_UPR_dop&0x01)sDAT_BIT|=0x08;
	if(iSOST_UPR_dop&0x02)sDAT_BIT|=0x10;
	if(iSOST_UPR_dop&0x04)sDAT_BIT|=0x20;
	}

f_config_dop=f_config_dop|(uSOST_UPR_dop&0x03);

//f_config_dop=0x0f;

						if((f_str_mtch==0)&&(f_yes_mtch==0))
							{
							if(rtKMPh_h < se_rtKMPh_h)
								{
								op=EETCOM_M;op_b_ee=~se_rtKMPm;
								eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM
								op=EETCOM_H;op_b_ee=~se_rtKMPh_l;
								eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM
								op=EETCOM_W;op_b_ee=~se_rtKMPh_h;
								eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM
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
							f_yes_mtch = 1;
							}

		
	Obrabotka();




		if(iDAT_BIT)
			{
			if(multi1)
				{
				DAT_BIT=iDAT_BIT;
				sDAT_BIT=DAT_BIT^0x2;
				}
			if(multi2)
				{
				DAT_BIT=iDAT_BIT&0xc3;
				if(iDAT_BIT&0x8)DAT_BIT|=0x4;
				sDAT_BIT=DAT_BIT;
				}
			}

if(tester_lin!=0xf2)
	{
	if(multi2)
		{
		if(zmk_COMP)fzmk_C_isp2=1;
		else fzmk_C_isp2=0;
		if(obr_COMP)fobr_C_isp2=1;
		else fobr_C_isp2=0;

		if(zmk_COMP)zmk_C2_isp=1;
		else zmk_C2_isp=0;
		if(obr_COMP)obr_C2_isp=1;
		else obr_C2_isp=0;


		uSOST_UPR2&=0xfc;

		if(mSOST_UPR2&0x1)zmk_COMP=1;
		if(mSOST_UPR2&0x2)obr_COMP=1;
	
	if(!f_H_def)
		{
		if(mSOST_UPR1&0x4)zmk_V_knd1=1;
		if(mSOST_UPR1&0x8)obr_V_knd1=1;
		if(mSOST_UPR3&0x4)zmk_V_knd2=1;
		if(mSOST_UPR3&0x8)obr_V_knd2=1;
		}
		if(mSOST_UPR3&0x20)blk_V_knd1=1;
		if(mSOST_UPR3&0x80)blk_V_knd2=1;

		}
	if(multi1)
		{
		if(zmk_C_con)fzmk_C_isp1=1;
		else fzmk_C_isp1=0;
		if(obr_C_con)fobr_C_isp1=1;
		else fobr_C_isp1=0;

		if(zmk_C_con)zmk_C1_isp=1;
		else zmk_C1_isp=0;
		if(obr_C_con)obr_C1_isp=1;
		else obr_C1_isp=0;

		if((mSOST_UPR2&0x1)&&(!zmk_COMP))fzmk_C_isp2=1;
		else fzmk_C_isp2=0;
		if((mSOST_UPR2&0x2)&&(!obr_COMP))fobr_C_isp2=1;
		else fobr_C_isp2=0;

		uSOST_UPR1&=0x3f;
		
		if(mSOST_UPR1&0x40)zmk_C_con=1;
		if(mSOST_UPR1&0x80)obr_C_con=1;
//


		}
	}

		tSOST_UPR4=sDAT_BIT&0x38;

		tSOST_UPR4=(fSOST_UPR4&0xc3)+(tSOST_UPR4&0x38);


	if(ver_mod==0x31)ct_st_up=30;
	if(ver_mod==0x32)ct_st_up=5;

//��������� ������ ��������� ������������

	if(tSOST_UPR1&&(t_st_up1<ct_st_up)){t_st_up1++;fSOST_UPR1=0;}
	if(!tSOST_UPR1){t_st_up1=0;fSOST_UPR1=0;}
	if(tSOST_UPR1&&(t_st_up1==ct_st_up))fSOST_UPR1=tSOST_UPR1;

	if(tSOST_UPR2&&(t_st_up2<ct_st_up)){t_st_up2++;fSOST_UPR2=0;}
	if(!tSOST_UPR2){t_st_up2=0;fSOST_UPR2=0;}
	if(tSOST_UPR2&&(t_st_up2==ct_st_up))fSOST_UPR2=tSOST_UPR2;

	if(tSOST_UPR3&&(t_st_up3<ct_st_up)){t_st_up3++;fSOST_UPR3=0;}
	if(!tSOST_UPR3){t_st_up3=0;fSOST_UPR3=0;}
	if(tSOST_UPR3&&(t_st_up3==ct_st_up))fSOST_UPR3=tSOST_UPR3;

	if(tSOST_UPR4&&(t_st_up4<ct_st_up)){t_st_up4++;fSOST_UPR4=0;}
	if(!tSOST_UPR4){t_st_up4=0;fSOST_UPR4=0;}
	if(tSOST_UPR4&&(t_st_up4==ct_st_up))
		{
		fSOST_UPR4=tSOST_UPR4;
		}
	if(tSOST_UPR_dop&&(t_st_up_dop<5)){t_st_up_dop++;fSOST_UPR_dop=0;}
	if(!tSOST_UPR_dop){t_st_up_dop=0;fSOST_UPR_dop=0;}
	if(tSOST_UPR_dop&&(t_st_up_dop==5))fSOST_UPR_dop=tSOST_UPR_dop;



// � ������������ ���������� ���� �������� ��� ��������????????????
// ���������� ������ �� ���� �� ����� ������

//fSOST_UPR1&=0xf7;
//fSOST_UPR3&=0xf7;


// 1. ���� ������� ��������� ���������  f_no_work
	ifAVR_IND&=0x80;

	if(fAVR_LIN){f_no_work=1;}


//������������� ���������������
	if(fSOST_UPR2&0x0c)
		{
f_no_work=1;
	//	if(DAT_BIT&0x80)f_stop=1;
	//	else f_no_work=1;
		}

//������������� �����������
//	if(fSOST_UPR2&0x02){f_no_work=1;}


//������������� ���� ������������
//	if((fSOST_UPR1&0x03)&&(fSOST_UPR3&0x03))f_no_work=1;
//	if((fSOST_UPR1&0x0c)&&(fSOST_UPR3&0x0c))f_no_work=1;

f_stop = 0;

// 2. ���� ���������� ���������� ���������  f_stop

//�������������  ��������
	if((fSOST_UPR1&0xf0)&&(!multi1)&&(!multi2))
		{
		f_no_klap=1;
		if(fSOST_UPR1&0x30){if(!(DAT_BIT&0x80)){f_stop=1;rbit|=0x10;}} //1;
		}

	if(multi1||multi2)
		{
		if((fSOST_UPR1&0xf0)||(fSOST_UPR4&0xc3))
			{
			f_no_klap=1;
			if((fSOST_UPR4&0xc3)&&(sSTATUS)&&(sSTATUS<4)){f_stop=1;rbit|=0x10;}
			if(fSOST_UPR1&0x30){f_stop=1;rbit|=0x10;}
			}
		}

//�������������  �������� ��������. �����
	if(fSOST_UPR_dop&0x30)
		{
		f_no_klap=1;
		f_stop=1;
		}

//������������� �����������
	if(fSOST_UPR2&0x03){f_no_comp=1;}    //if(!(DAT_BIT&0x80))f_stop=1;}



//������������� ���������������
	if(fSOST_UPR2&0x0c)f_stop=1;

//������������� ������������ ����� �� ����� 2
if((f_config_t==6)&&(fSOST_UPR3&0x43))f_stop=1;
if((f_config_t==6)&&(fSOST_UPR1&0x0c))f_stop=1;
if((f_config_t==6)&&(fSOST_UPR3&0x40))f_stop=1;

if((f_config_t==9)&&(fSOST_UPR1&0x03))f_stop=1;
if((f_config_t==9)&&(fSOST_UPR3&0x10))f_stop=1;
if((f_config_t==9)&&(fSOST_UPR3&0x8c))f_stop=1;


//������������� ���� ������������
//  if((DAT_BIT&0x80)==0) // no fSTANB
//	{

	if((fSOST_UPR1&0x01)&&(fSOST_UPR3&0x01)){rbit|=0x10;f_stop=1;}

if(!multi2)
	{
	if((fSOST_UPR1&0x04)&&(fSOST_UPR3&0x04)){rbit|=0x10;f_stop=1;}
	if((fSOST_UPR1&0x0c)&&(fSOST_UPR3&0x8c))f_stop=1;
	}
//	if((fSOST_UPR1&0x02)&&(fSOST_UPR3&0x02)){rbit|=0x10;f_stop=1;}//

/////////////////////
	if((fSOST_UPR1&0x03)&&(fSOST_UPR3&0x43))f_stop=1;
	if((fSOST_UPR3&0x10)&&(fSOST_UPR3&0x43))f_stop=1;
	if((fSOST_UPR3&0x43)&&(fSOST_UPR4&0x38))f_stop=1;
	if((fSOST_UPR3&0x20)&&(fSOST_UPR3&0x8c))f_stop=1;

//	if((fSOST_UPR1&0x0c)&&(fSOST_UPR3&0x8c))f_stop=1;

//
	if((mSOST_UPR1&0x0c)&&(mSOST_UPR3&0x0c))f_stop=1;
//
//	}

//���������a ���� ������������
	if((mSOST_UPR3&0xa0)==0xa0){f_blk_vnt=1;f_stop=1;}
	if((fSOST_UPR3&0x50)==0x50){f_blk_vnt=1;f_stop=1;}
	if(fSOST_UPR3&0x50){f_blk_vnt=1;}
	if(fSOST_UPR3&0xa0){f_blk_vnt=1;}


	if((fSOST_UPR3&0x40)&&(fSOST_UPR4&0x20)){f_stop=1;f_blk_vnt=1;}



// ���������� ������ ������������ ��� ����������
//isp

	if(!(uUPR_BT&0x03)){if(t_tst_obr_i<60)t_tst_obr_i++;}
	else t_tst_obr_i=0;
	if(t_tst_obr_i<60)
		{
		if((fSOST_UPR1&0x02)&&(fSOST_UPR3&0x02)&&(!(uUPR_BT&0x03)))f_stop=0;
		}

	if(!(uUPR_BT&0x0c)){if(t_tst_obr_c<60)t_tst_obr_c++;}
	else t_tst_obr_c=0;
	if(t_tst_obr_c<60)
		{
		if((fSOST_UPR1&0x08)&&(fSOST_UPR3&0x08)&&(!(uUPR_BT&0x0c)))f_stop=0;
		}

//������������� �������� �����������
	if(fSOST_UPR2&0xf0){f_stop=1;f_no_temp=1;}
	else {f_no_temp=0;}

	if((fSOST_UPR2&0xc0)&&((tblok_fl&0x24)==0x4)&&(F2&0x80)){f_stop=0;}
	if((fSOST_UPR2&0x30)&&((tblok_fl&0x24)==0x4)&&(F2&0x80))
		{f_stop=0;f_no_temp=0;}

// 3. ���� ���������� ������������

	if((fSOST_UPR3&0xf0)||(sDAT_BIT&0x20))f_blk_vnt=1;

//  ���������� ������ ��� ������ ���������
//  ���� �������� ������ ��� ������


///////////////////////////////////////////////////////////

if(oT_air==85)T_air=85;//��� ��������������� ����� ��
if(sZADT!=90)oT_air=0;

///////////////////////////////////////////////////////////
if(sZADT>T_air)zOPER_MN=sZADT-T_air;
else zOPER_MN=0;
if(T_air>sZADT)zOPER_PL=T_air-sZADT;
else zOPER_PL=0;
///////////////////////////////////////////////////////////


	if(U_nap>80)
		{
		tON_OFF_2h=0;tON_OFF=0;fSLEEP=0;

		if(U_nap<91)
			{
			t_U_91++;t_U_92=0;
			fSOST_UPR1=0;
			fSOST_UPR2&=0xfc;
			fSOST_UPR3=0;
			fSOST_UPR_dop=0;
			DAT_BIT&=0x80;
			mSOST_UPR1=0;
			mSOST_UPR2=0;
			mSOST_UPR3=0;
			mDAT_BIT=0;

			if(t_U_91>20)
				{
				F4&=0xf7;
				t_U_91=20;
			  if(!(DAT_BIT&=0x80))	
				F4|=0x8;//fACC_LOW=1
				}
			else {F4&=0xf7;}
			}
		else 
			{
			F4&=0xf7;t_U_91=0;
			t_U_92++;
			if(t_U_92>20)
				{
				if(!(F5&0x40))regist_avr();
				
				t_U_92=20;
				}
			}

		if(t_U_napr<100){t_U_napr++;}
		if(t_U_napr<50)
			{
			fSOST_UPR1=0;
			fSOST_UPR2=0;
			fSOST_UPR3=0;
			fSOST_UPR_dop=0;
			DAT_BIT=0;
			mSOST_UPR1=0;
			mSOST_UPR2=0;
			mSOST_UPR3=0;
			mDAT_BIT=0;
			}

		//
		if(t_blk_isp1){fblk_V_isp1=1;f_blk_vnt=1;}
		if(t_zmk_isp1){fzmk_V_isp1=1;}
		if(t_blk_isp2){fblk_V_isp2=1;f_blk_vnt=1;}
		if(t_zmk_isp2){fzmk_V_isp2=1;}

//		if(t_blk_isp3){fblk_V_isp3=1;f_blk_vnt=1;}
//		if(t_zmk_isp3){fzmk_V_isp3=1;}

		if(t_blk_knd1){fblk_V_knd1=1;f_blk_vnt=1;}
		if(t_zmk_knd1){fzmk_V_knd1=1;}
		if(t_blk_knd2){fblk_V_knd2=1;f_blk_vnt=1;}
		if(t_zmk_knd2){fzmk_V_knd2=1;}


		if(!(F1&0x02)&&(tester_lin!=0xf1))
			{
			t_blk_isp1_c=10;t_blk_isp2_c=11;
		//	t_blk_isp3_c=12;
			
			t_zmk_isp1_c=10;t_zmk_isp2_c=11;
		//	t_zmk_isp3_c=12;
			}
		if((sSTATUS == 0)&&(sSTATUS2 == 0))
			{
			t_blk_knd1_c=14;t_blk_knd2_c=16;
			t_zmk_knd1_c=14;t_zmk_knd2_c=16;
			}

if(fAVR_LIN) U_nap = 125;

///////////////////////////
if((ver_sil==0x31)&&(F2&0x80))//���� ��� ����
	{
	DAT_BIT&=0xbb;
	}
if((ver_sil==0x31)&&(!(F2&0x80)))//��� ��� ����
	{
	DAT_BIT&=0xbf;
	if(DAT_BIT&0x4){DAT_BIT&=0xfb;DAT_BIT|=0x40;}
	}
///////////////////////////
if(ver_sil==0x32)DAT_BIT&=0xbf;


		for(ij=0;ij<4;ij++)//
			{
		 	blozu=prer1[ij];
		 	if (*blozu!=0)
				{
			  	univup (blozu);
				}
			}
		}   //  if(U_nap>80)
	else
		{
			F4|=0x8;//fACC_LOW=1
			t_U_91=0;t_U_92=0;
			fSOST_UPR1=0;
			fSOST_UPR2=0;
			fSOST_UPR3=0;
			fSOST_UPR_dop=0;
			DAT_BIT=0;
			mSOST_UPR1=0;
			mSOST_UPR2=0;
			mSOST_UPR3=0;
			mDAT_BIT=0;

			F4&=0xf7;//fACC_LOW=0
			t_U_napr=0;

			for(ij=0;ij<4;ij++)//
				{
			 	blozu=prer1[ij];
			 	if (*blozu!=0)
					{
				  	univup (blozu);
					}
				}
		}	

	if(knop)CCPR1L=64;	

Displ();


//*****************************************************
//****  ���������� ������� � �����. ����. �������.
//*****************************************************

sUPR_BT=UPR_BT;
  
if(!multi2)  
if(F4&0x02) // f_davl_an = 1
	{					//fWAIT
	if(((sSTATUS > 2)&&(!(F5&0x20)))||((sSTATUS > 1)&&(sSTATUS2 > 1))\\
		||((sSTATUS == 0)&&(sSTATUS2 > 1))) //(multi1)
		{
		if(((UPR_BT&0x20)||(mUPR_BT&0x20))&&((UPR_BT&0x40)||(mUPR_BT&0x40)))
			{
			if(U_davl>25)
				{
				sUPR_BT&=0xbf; //uC_con=0;
				fuC_con=1;
				UPR_BT|=0x4;   //uV_CON
				sUPR_BT|=0x4;   //uV_CON
				}//max, D_davl>28 ���
			}

	if(((UPR_BT&0x20)||(mUPR_BT&0x20))&&((UPR_BT&0x40)||(mUPR_BT&0x40))&&fuC_con)
			{
			if(U_davl>=23)
				{
				sUPR_BT&=0xbf; //uC_con=0;
				UPR_BT|=0x4;   //uV_CON
				sUPR_BT|=0x4;   //uV_CON
				}//max, D_davl>25 ���

			else
				{
				fuC_con=0;
				UPR_BT&=0xfb;   //uV_CON
				sUPR_BT&=0xfb;   //uV_CON
				}//max, D_davl<25 ���
			}
		}
	else //sSTATUS < 3
		{
		if((!(UPR_BT&0x40))&&((UPR_BT&0x80)||(mUPR_BT&0x80)||((DAT_BIT&0x03)==3)))
			{
			if(DAT_BIT & 0x01)          
				UPR_BT|=0x4;   //uV_CON}//mid, D_davl > 17 ���
			else UPR_BT&=0xfb;
			}
		}
//new
	if(((sSTATUS == 1)||(sSTATUS2 == 1))&&((UPR_BT&0x80)||(mUPR_BT&0x80)))
			{
			if(DAT_BIT & 0x01)          
				UPR_BT|=0x4;   //uV_CON}//mid, D_davl > 17 ���
			else UPR_BT&=0xfb;
			}

	} // f_davl_an = 1

if(!multi2)  
if(!(F4&0x02)) // f_davl_an = 0
	{				    // fWAIT
	if(((sSTATUS > 2)&&(!(F5&0x20)))||((sSTATUS > 1)&&(sSTATUS2 > 1))\\
		||((sSTATUS == 0)&&(sSTATUS2 > 1))) //(multi1)
		{
		if((DAT_BIT & 0x03) == 3)         
			UPR_BT|=0x4;   //uV_CON}//mid
		else UPR_BT&=0xfb;
		}
	else //sSTATUS < 3
		{
		if((!(UPR_BT&0x40))&&((UPR_BT&0x80)||(mUPR_BT&0x80)||((DAT_BIT&0x03)==3)))
			{
			if(DAT_BIT & 0x01)          
				UPR_BT|=0x4;   //uV_CON}//mid
			else UPR_BT&=0xfb;
			}
		if((sSTATUS == 0)&&(sSTATUS2 == 0)) UPR_BT&=0xfb;
		}

	}  // f_davl_an = 0


	if(multi2)
		{
		if((UPR_BT&0x20)&&(UPR_BT&0x40)&&(mUPR_BT&0x04))
			{
			UPR_BT&=0xbf;
			}
		}
//		if((UPR_BT&0x20)&&(UPR_BT&0x40)&&(!(mUPR_BT&0x40)))
//			{
//			UPR_BT&=0xbf;
//			}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



	//��������� ����� ����������
	if(rs_mes_t)
		{
		 T_ISP=mT_ISP;
		 T_AIR=mT_AIR;

		t_rs_mes=10;

		if(utUPR_BT)uUPR_BT=utUPR_BT;

		else if(tUPR_BT)uUPR_BT=tUPR_BT;
		else 
			{
			uUPR_BT=0;
			if(UPR_BT&0x1)
				{
				if(f_config_t&0x01)uV_isp1=1;
				else uV_isp2=1;
				}
			else {t_up_isp2=0;t_up_isp3=0;}

		if(f_config_t&0x01)
			{
			if(uV_isp1&&(t_up_isp2<10))t_up_isp2++;
			if(uV_isp1&&(t_up_isp2==10))uV_isp2=1;
			else uV_isp2=0;
			}
	/*  new_b
		if(f_config_t&0x10)
			{
			if(f_config_t&0x01)
				{
				if(uV_isp1&&(t_up_isp3<30))t_up_isp3++;
				if(uV_isp1&&(t_up_isp3==30))uV_isp3=1;
				else uV_isp3=0;
				}
			else
				{
				if(uV_isp2&&(t_up_isp3<30))t_up_isp3++;
				if(uV_isp2&&(t_up_isp3==30))uV_isp3=1;
				else uV_isp3=0;
				}
			}		
	*/

		if((!multi1)&&(!multi2))
			{
			if(UPR_BT&0x4)uV_knd1=1;
			else t_up_knd2=0;
			}
		else if(multi1)
				{
				if((UPR_BT&0x4)||(mUPR_BT&0x4))uV_knd1=1;
				else t_up_knd2=0;
				}


			if(uV_knd1&&(t_up_knd2<20))t_up_knd2++;
			if(uV_knd1&&(t_up_knd2==20))uV_knd2=1;
			else uV_knd2=0;
//	

		if(UPR_BT&0x10)uH_def=1;

	
		if((!multi1)&&(!multi2))
			{
			if(UPR_BT&0x20)uC_def=1;
			if(UPR_BT&0x40)uC_con=1;
			if(UPR_BT&0x80)uCOMP=1;
//new
			if(U_davl==0xff)uCOMP=0;
			}
		else if(multi1)
				{
				if(UPR_BT&0x20)uC_def=1;
				if(UPR_BT&0x02)uC_isp1=1;

//new
				if((UPR_BT&0x80)||(mUPR_BT&0x80))
					{
					uCOMP=1;

					//��� ������ ��������
					if((UPR_BT&0x80)&&(mUPR_BT&0x80))
						{if(F3&0x1)uCOMP=0;} //  fAD2 = 1

					else //���� ������ ��������
						{
						switch(n_AD2)
							{
							case 0:
								t_AD2=0;
								if(F3&0x1){uCOMP=0;n_AD2=1;}
							break;	

							case 1:
								uCOMP=0;
								if(!(F3&0x1)){if(FCL1s)t_AD2++;}

								if(U_davl > 15){if(t_AD2 > 30)n_AD2=0;}
								else {if(t_AD2 > 60)n_AD2=0;}
							break;	
							}
						}
					}
				}
		else if(multi2)
				{
				if(UPR_BT&0x20)uC_def=1;
				if((UPR_BT&0x40)||(mUPR_BT&0x40))uC_con=1;
				if(UPR_BT&0x02)uC_isp2=1;
				}

			}

	
		if(iSOST_UPR1)tSOST_UPR1=iSOST_UPR1|uSOST_UPR1;
		else tSOST_UPR1=uSOST_UPR1;

//������������ ������ ��. �������
		if(uSOST_UPR1&0x80){F4|=0x80;}//tSOST_UPR1&=0x7f;
		else {F4&=0x7f;}
	
		if(iSOST_UPR2)tSOST_UPR2=iSOST_UPR2|uSOST_UPR2;
		else tSOST_UPR2=uSOST_UPR2;
	
		if(iSOST_UPR3)tSOST_UPR3=iSOST_UPR3|uSOST_UPR3;
		else tSOST_UPR3=uSOST_UPR3;

		if(iSOST_UPR_dop)tSOST_UPR_dop=iSOST_UPR_dop|uSOST_UPR_dop;
		else tSOST_UPR_dop=uSOST_UPR_dop;

//�������� ���������� ��� ��������� ������������
// � �� ���������� 
		if(fblk_V_isp1||fzmk_V_isp1)//||fobr_V_isp1)
			{
			if(FCL1s&&fblk_V_isp1)t_blk_isp1++;
			if(FCL1s&&fzmk_V_isp1)t_zmk_isp1++;

			if(t_blk_isp1<t_blk_isp1_c)uV_isp1=0;
			else 
				{
				t_st_up3=0;t_blk_isp1=0;
				uUPR_BT&=0xfe;
				if(t_blk_isp1_c<240)t_blk_isp1_c=t_blk_isp1_c+15;
				}

			if(t_zmk_isp1<t_zmk_isp1_c)uV_isp1=0;
			else 
				{
				t_st_up1=0;t_zmk_isp1=0;
				uUPR_BT&=0xfe;
				if(t_zmk_isp1_c<240)t_zmk_isp1_c=t_zmk_isp1_c+15;
				}
			}
		else 
			{
			if(t_blk_isp1&&(t_blk_isp1<t_blk_isp1_c))
				{
				uV_isp1=0;
				if(FCL1s)t_blk_isp1++;
				fblk_V_isp1=1;
				}
			if(t_blk_isp1==t_blk_isp1_c)
				{
				t_blk_isp1=0;
				if(t_blk_isp1_c<240)
				t_blk_isp1_c=t_blk_isp1_c+15;
				}
//
			if(t_zmk_isp1&&(t_zmk_isp1<t_zmk_isp1_c))
				{
				uV_isp1=0;
				if(FCL1s)t_zmk_isp1++;
				fzmk_V_isp1=1;
				}
			if(t_zmk_isp1==t_zmk_isp1_c)
				{
				t_zmk_isp1=0;
				if(t_zmk_isp1_c<240)
				t_zmk_isp1_c=t_zmk_isp1_c+15;
				}
			}
//		
		if(fblk_V_isp2||fzmk_V_isp2)//||fobr_V_isp2)
			{
			if(FCL1s&&fblk_V_isp2)t_blk_isp2++;
			if(FCL1s&&fzmk_V_isp2)t_zmk_isp2++;

			if(t_blk_isp2<t_blk_isp2_c)uV_isp2=0;
			else 
				{
				t_st_up3=0;t_blk_isp2=0;
				uUPR_BT&=0xfd;
				if(t_blk_isp2_c<240)t_blk_isp2_c=t_blk_isp2_c+15;
				}

			if(t_zmk_isp2<t_zmk_isp2_c)uV_isp2=0;
			else 
				{
				t_st_up3=0;t_zmk_isp2=0;
				uUPR_BT&=0xfd;
				if(t_zmk_isp2_c<240)t_zmk_isp2_c=t_zmk_isp2_c+15;
				}
			}
		else 
			{
			if(t_blk_isp2&&(t_blk_isp2<t_blk_isp2_c))
				{
				uV_isp2=0;
				if(FCL1s)t_blk_isp2++;
				fblk_V_isp2=1;
				}
			if(t_blk_isp2==t_blk_isp2_c)
				{
				t_blk_isp2=0;
				if(t_blk_isp2_c<240)
				t_blk_isp2_c=t_blk_isp2_c+15;
				}
//
			if(t_zmk_isp2&&(t_zmk_isp2<t_zmk_isp2_c))
				{
				uV_isp2=0;
				if(FCL1s)t_zmk_isp2++;
				fzmk_V_isp2=1;
				}
			if(t_zmk_isp2==t_zmk_isp2_c)
				{
				t_zmk_isp2=0;
				if(t_zmk_isp2_c<240)
				t_zmk_isp2_c=t_zmk_isp2_c+15;
				}
			}
/* new_b
		if(fblk_V_isp3||fzmk_V_isp3)//||fobr_V_isp2)
			{
			if(FCL1s&&fblk_V_isp3)t_blk_isp3++;
			if(FCL1s&&fzmk_V_isp3)t_zmk_isp3++;

			if(t_blk_isp3<t_blk_isp3_c)uV_isp3=0;
			else 
				{
				t_st_up4=0;t_blk_isp3=0;
				uUPR_BT&=0xef;
				if(t_blk_isp3_c<240)t_blk_isp3_c=t_blk_isp3_c+15;
				}

			if(t_zmk_isp3<t_zmk_isp3_c)uV_isp3=0;
			else 
				{
				t_st_up4=0;t_zmk_isp3=0;
				uUPR_BT&=0xef;
				if(t_zmk_isp3_c<240)t_zmk_isp3_c=t_zmk_isp3_c+15;
				}
			}
		else 
			{
			if(t_blk_isp3&&(t_blk_isp3<t_blk_isp3_c))
				{
				uV_isp3=0;
				if(FCL1s)t_blk_isp3++;
				fblk_V_isp3=1;
				}
			if(t_blk_isp3==t_blk_isp3_c)
				{
				t_blk_isp3=0;
				if(t_blk_isp3_c<240)
				t_blk_isp3_c=t_blk_isp3_c+15;
				}
//
			if(t_zmk_isp3&&(t_zmk_isp3<t_zmk_isp3_c))
				{
				uV_isp3=0;
				if(FCL1s)t_zmk_isp3++;
				fzmk_V_isp3=1;
				}
			if(t_zmk_isp3==t_zmk_isp3_c)
				{
				t_zmk_isp3=0;
				if(t_zmk_isp3_c<240)
				t_zmk_isp3_c=t_zmk_isp3_c+15;
				}
			}
*/
		if(fblk_V_knd1||fzmk_V_knd1)//||fobr_V_knd1)
			{
			if(FCL1s)
				{
				if(fzmk_V_knd1)t_zmk_knd1++;
				if(fblk_V_knd1)t_blk_knd1++;
				}

			if(t_blk_knd1<t_blk_knd1_c)uV_knd1=0;
			else 
				{
				t_st_up3=0;t_blk_knd1=0;
				uUPR_BT&=0xfb;
				if(t_blk_knd1_c<240)t_blk_knd1_c=t_blk_knd1_c+15;
				}

			if(t_zmk_knd1<t_zmk_knd1_c)uV_knd1=0;
			else 
				{
				t_st_up1=0;t_zmk_knd1=0;
				uUPR_BT&=0xfb;
				if(t_zmk_knd1_c<240)t_zmk_knd1_c=t_zmk_knd1_c+15;
				}
			}
		else 
			{
			if(t_blk_knd1&&(t_blk_knd1<t_blk_knd1_c))
				{
				uV_knd1=0;
				if(FCL1s)t_blk_knd1++;
				fblk_V_knd1=1;
				}
			if(t_blk_knd1==t_blk_knd1_c)
				{
				t_blk_knd1=0;
				if(t_blk_knd1_c<240)
				t_blk_knd1_c=t_blk_knd1_c+15;
				}
//
			if(t_zmk_knd1&&(t_zmk_knd1<t_zmk_knd1_c))
				{
				uV_knd1=0;
				if(FCL1s)t_zmk_knd1++;
				fzmk_V_knd1=1;
				}
			if(t_zmk_knd1==t_zmk_knd1_c)
				{
				t_zmk_knd1=0;
				if(t_zmk_knd1_c<240)
				t_zmk_knd1_c=t_zmk_knd1_c+15;
				}
			}
//
		if(fblk_V_knd2||fzmk_V_knd2)//||fobr_V_knd2)
			{
			if(FCL1s)
				{
				if(fzmk_V_knd2)t_zmk_knd2++;
				if(fblk_V_knd2)t_blk_knd2++;
				}

			if(t_blk_knd2<t_blk_knd2_c)uV_knd2=0;
			else 
				{
				t_st_up3=0;t_blk_knd2=0;
				uUPR_BT&=0xf7;
				if(t_blk_knd2_c<240)t_blk_knd2_c=t_blk_knd2_c+15;
				}

			if(t_zmk_knd2<t_zmk_knd2_c)uV_knd2=0;
			else 
				{
				t_st_up3=0;t_zmk_knd2=0;
				uUPR_BT&=0xf7;
				if(t_zmk_knd2_c<240)t_zmk_knd2_c=t_zmk_knd2_c+15;
				}
			}
		else 
			{
			if(t_blk_knd2&&(t_blk_knd2<t_blk_knd2_c))
				{
				uV_knd2=0;
				if(FCL1s)t_blk_knd2++;
				fblk_V_knd2=1;
				}
			if(t_blk_knd2==t_blk_knd2_c)
				{
				t_blk_knd2=0;
				if(t_blk_knd2_c<240)
				t_blk_knd2_c=t_blk_knd2_c+15;
				}
//
			if(t_zmk_knd2&&(t_zmk_knd2<t_zmk_knd2_c))
				{
				uV_knd2=0;
				if(FCL1s)t_zmk_knd2++;
				fzmk_V_knd2=1;
				}
			if(t_zmk_knd2==t_zmk_knd2_c)
				{
				t_zmk_knd2=0;
				if(t_zmk_knd2_c<240)
				t_zmk_knd2_c=t_zmk_knd2_c+15;
				}
			}

// ������������� ������ ������������ ����������

			if((sSTATUS > 4)||(sSTATUS2 > 4))
				{
				if(uV_knd1 == 0)
				  {
				  if(FCL1s)t_knd1_rot++;
				  if(t_knd1_rot > 240)	
					{
					uUPR_BT |= 0x04;
					if(t_knd1_rot > 243)t_knd1_rot=0;
					}
				  }
				else t_knd1_rot=0;

				if(uV_knd2 == 0)
				  {
				  if(FCL1s)t_knd2_rot++;
				  if(t_knd2_rot > 248)	
					{
					uUPR_BT |= 0x08;
					if(t_knd2_rot > 251){t_knd1_rot=0;t_knd2_rot=0;}
					}
				  }
				else t_knd2_rot=0;
				}
			else {t_knd1_rot=t_knd2_rot=0;}

// ������ ������������ ���������� ��� ��������� �� STANDBY

			if(((sSTATUS > 0)||(sSTATUS2 > 0))&&(DAT_BIT&0x80))
				{
				if(uV_knd1 == 0)
				  {
				  if((FCL1s)&&(t_knd_rot < 20))t_knd_rot++;
				  if((t_knd_rot > 0)&&(t_knd_rot < 7))
					{
					uUPR_BT |= 0x04;
					}
				  if((t_knd_rot > 6)&&(t_knd_rot < 13))	
					{
					uUPR_BT |= 0x08;
					}
				  }
				}





//�������� ��������� �����������
// � ���������� ���
		if(fzmk_COMP)
			{
			t_zmk_Comp++;
			if(t_zmk_Comp<150)uCOMP=0;
			else {t_st_up2=0;t_zmk_Comp=0;uUPR_BT&=0x7f;}
			}
		else t_zmk_Comp=0;
/*
		if(fzmk_C_def)
			{
			t_zmk_def++;
			if(t_zmk_def<100)uC_def=0;
			else {t_st_up1=0;t_zmk_def=0;uUPR_BT&=0xdf;}
			}
		else t_zmk_def=0;

		if(fzmk_C_con)
			{
			t_zmk_con++;
			if(t_zmk_con<100)uC_con=0;
			else {t_st_up1=0;t_zmk_con=0;uUPR_BT&=0xbf;}
			}
		else t_zmk_con=0;
*/



		}
	else 
		{
		if(t_rs_mes)t_rs_mes--;
		else 
			{
			mT_ISP=0;
			mT_AIR=0;
			tUPR_BT=0;
			iSOST_UPR1=0;
			iSOST_UPR2=0;
			iSOST_UPR3=0;
			}
		}		


//	if(U_nap>50) regist_avr();


		buf_out[0]=0x80;
		buf_out[1]=0x28;
		buf_out[2]=0x31;
		buf_out[3]=0x21;
		buf_out[4]=0x81;//����� �����
if(tester_lin==0xf2){buf_out[4]=0xf2;}
if(F5&0x40)buf_out[4]=0xf3;

if(f_stend_hand)
	{
	buf_out[4]=0xf0;
	ir=5;
	buf_out[ir++]=uUPR_BT;
	buf_out[ir]=uUPR_STEND;
	}
else
	{
		ir=5;
	//
//		if((uUPR_BT&0x10)||(mUPR_BT&0x10))buf_out[ir++]=0;
//		else 

//		buf_out[ir++]=0;
		if(F5&0x40)buf_out[ir++]=tech_upr;
		else buf_out[ir++]=uUPR_BT;  //&0xf0;  //new_h
//
//		F1|=0x20;  ������

		if(F1&0x20)buf_out[ir++]=0x1;//���� ��� ����
		else 
			{
			if(F5&0x40)buf_out[ir++]=tech_upr_dop;
			else buf_out[ir++]=tUPR_BT_dop;
			}
		buf_out[ir++]=0;
//
//sSTATUS = 3;

//
	if(tester_lin==0xf2)buf_out[ir++]=0x0f;//�����
	else buf_out[ir++]=sSTATUS;
	//
		buf_out[ir++]=ifAVR_IND;
	//
		if(multi1)buf_out[ir++]=0x01;
		else if(multi2)buf_out[ir++]=0x02;
		else buf_out[ir++]=0x55;
	//
		buf_out[ir]=POWER_OTOP;
	//
	if((rtKMPm!=s_rtKMPm)||((f_str_mtch)&&(CLOC1m > 30)&&(CLOC1m < 55)))
		{
		ir++;
		if(CLOC1m < 50){f_str_mtch=0;}
		s_rtKMPm = rtKMPm;
		buf_out[ir++]=rtKMPm;
		buf_out[ir++]=rtKMPh_l;
		buf_out[ir]=rtKMPh_h;
		}
	}

	//
		schetcik1++;
	//
		Tr_COM();
	//
	
		F_MEN=0;
		FCL1s=0;
		FCL1m=0;
		F1m=0;
	
	
		 }//F_MEN

	}//for

}//main



void Klav_read (void)
	{

	//���������� RC3 AN15
	ADCON2bits.ADFM=0;	//>>
	
	op_b=15;
	op_b=op_b<<2;
	ADCON0 = 0x01+op_b;	//AN15
	
	op_b=40;
	while(op_b) op_b--;
	ADCON0bits.GO = 1;
	while(ADCON0bits.GO);
	popa=ADRESH;

if(popa<67)op_b=0x6;
else if(popa<90)op_b=0x2;
else if(popa<140)op_b=0x4;

		if(!PORTAbits.RA2)op_b+=0x1;
		
		popa=0;
		if(op_b&0x1)popa=popa+0x8;
		if(op_b&0x2)popa=popa+0x4;
		if(op_b&0x4)popa=popa+0x1;

		if(popa)t_kl++; //else t_kl=0;	
	
		switch(TIMKN)
			{
				case 0: if(!popa) return;
				TIMKN++; knop = popa;
				t_kl=0;
				kn_schet=0;no_repit=0;	
				break;

				case 1: if(popa)knop = popa;
						if(popa==0)
							{
							 if(!fknop48) KNOPKA=knop;
							TIMKN=0;knop=0;fknop48=0;
							 if(t_kl>10)
							 	{
									t_kl=0;
								 	KNOPKA=0;
								 }	
							 kn_schet=0;
							 return;
							}
//						else t_kl++;

						if(t_kl>10)	tREPIT=3; else 	tREPIT=4;

						if((popa==4)||(popa==8))
							{
							if(!no_repit)
								{
							     kn_schet++;	
							     if(kn_schet>=tREPIT)
									{
									 fknop48=1;
									 KNOPKA=knop; 
									 kn_schet=0;
									}
								}	
							}
						else no_repit=1;
				



				break;
			}
	}

void Write_buf(unsigned char dan)
{
  FSR0=ptrindex;
  INDF0=dan;
  ptrindex++;

}
unsigned char Read_buf(void)
{
 FSR0=ptrindex;
 op_b=INDF0;

 return op_b;	
}

//
unsigned char eepromReadByte( unsigned char Adr )
	{

		while( EECON1bits.WR );
		EEADR =Adr;
		EECON1bits.EEPGD = 0; 
		EECON1bits.CFGS = 0;
		EECON1bits.RD = 1;
		while( EECON1bits.RD );

		return EEDATA;
	}
void eepromWriteByte( unsigned char Adr, unsigned char Data )
	{

		while( EECON1bits.WR );
		EEADR = Adr;//ee.by[0];
		EEDATA = Data;
		EECON1bits.EEPGD = 0; 
		EECON1bits.CFGS = 0;
		EECON1bits.WREN = 1;
		INTCONbits.GIEH = 1;
		EECON2 = 0x55; 
		EECON2 = 0xaa; 
		EECON1bits.WR = 1;
		while( EECON1bits.WR );
		INTCONbits.GIEH = 1;
		EECON1bits.WREN = 0;

	}
 


void Obrabotka (void)
	{
	#define Tperiod 15
	
	if(mT_AIR)T_air=mT_AIR;
	else T_air=iT_AIR;
	
	//
	T_air_dpl=T_air;   //+1;
	T_air_dmn=T_air-dT_GIST+1;
	//
	T_air_dpl_o=T_air+dT_GIST;
	//
	T_air_dpl_a = T_air+2;
	T_air_dmn_a = T_air-3;
	
	//
	if(mT_ISP)T_isp=mT_ISP;
	else T_isp=iT_ISP;
	//
	
	if(multi2)
		{
		DAT_BIT=sDAT_BIT&0xfc;
		DAT_BIT|=mDAT_BIT&0x3;
		}	//~ P_AVR
	else
		{
		DAT_BIT=sDAT_BIT;
		DAT_BIT=DAT_BIT^0x2;	//~ P_AVR
		}
	
	if(fAVR_LIN){DAT_BIT=0;uSOST_UPR1=0;uSOST_UPR2=0;uSOST_UPR3=0;}
	
	}




void live_avr (void)
	{
	//eSOST_UPR1
	if(fobr_V_isp1||fobr_V_isp2||fobr_V_isp3)eobr_V_isp=1;
	if(fblk_V_isp1||fblk_V_isp2||fblk_V_isp3)eblk_V_isp=1;
	
	if(fobr_V_knd1||fobr_V_knd2)eobr_V_knd=1;
	if(fblk_V_knd1||fblk_V_knd2)eblk_V_knd=1;
	
	if(fzmk_C_def)ezmk_C_def=1;
	if(fobr_C_def)eobr_C_def=1;
	if(fzmk_C_con)ezmk_C_con=1;
	if(fobr_C_con)eobr_C_con=1;
	
	//eSOST_UPR2
	if(fzmk_COMP)ezmk_COMP=1;
	if(fobr_COMP)eobr_COMP=1;
	if(fzmk_V_isp1||fzmk_V_isp2||fzmk_V_isp3){ezmk_V_isp=1;}
	if(fzmk_V_knd1||fzmk_V_knd2){ezmk_V_knd=1;}
	if(fzmk_T_isp)ezmk_T_isp=1;
	if(fobr_T_isp)eobr_T_isp=1;
	if(fzmk_T_air)ezmk_T_air=1;
	if(fobr_T_air)eobr_T_air=1;
	
	//eSOST_UPR3
	if(DAT_BIT&0x2)eAVR_AD=1;
	if(F3&0x1)eAVR_AD2=1;
	if(U_davl==0xfe)ezmk_AD=1;
	if(U_davl==0xfd)eobr_AD=1;
	if(fno_U_pr1||fno_U_pr2)eno_U_pr=1;
	if(u1.tfAVR_LIN)eAVR_LIN=1;
/*
	if(fAVR_IND.tf_stop)ef_stop=1;
	if(DAT_BIT&0x80)
		{
		if(eSOST_UPR1||eSOST_UPR2||(eSOST_UPR3&0x3))ef_STANB=1;
		}
*/	
	//eSOST_UPR_dop
//	if(fzmk_C_isp1)ezmk_C_isp1=1;
//	if(fobr_C_isp1)eobr_C_isp1=1;
//	if(fzmk_C_isp2)ezmk_C_isp2=1;
//	if(fobr_C_isp2)eobr_C_isp2=1;
	if(fzmk_C1_isp)ezmk_C1_isp=1;
	if(fobr_C1_isp)eobr_C1_isp=1;
	if(fzmk_C2_isp)ezmk_C2_isp=1;
	if(fobr_C2_isp)eobr_C2_isp=1;

//
	if(eSOST_UPR1>s_eSOST_UPR1){f_wr_err=1;s_eSOST_UPR1|=eSOST_UPR1;}
	if(eSOST_UPR2>s_eSOST_UPR2){f_wr_err=1;s_eSOST_UPR2|=eSOST_UPR2;}
	if(eSOST_UPR3>s_eSOST_UPR3){f_wr_err=1;s_eSOST_UPR3|=eSOST_UPR3;}
	if(eSOST_UPR_dop>s_eSOST_UPR_dop){f_wr_err=1;s_eSOST_UPR_dop|=eSOST_UPR_dop;}
	
	if((rtKMPh_l!=s_rtKMPh_l)&&nom_err)
		{
		s_rtKMPh_l=rtKMPh_l;f_chng_n_err=1;
		eSOST_UPR1=eSOST_UPR2=eSOST_UPR3=eSOST_UPR_dop=0;
		s_eSOST_UPR1=s_eSOST_UPR2=s_eSOST_UPR3=s_eSOST_UPR_dop=0;
		}



	}


void regist_avr (void)
{
switch(state_reg)
	{
	case 0:
			if(nom_err)
				{
				op=(((nom_err-1)&0x0f)*8)+0x81;
				eepromReadByte(op);//��������� �� EEPROM
				s_rtKMPh_l=EEDATA;
				op++;op++;
				eepromReadByte(op);//��������� �� EEPROM
				s_eSOST_UPR1=EEDATA;op++;
				eSOST_UPR1=s_eSOST_UPR1;
//
				eepromReadByte(op);//��������� �� EEPROM
				s_eSOST_UPR2=EEDATA;op++;
				eSOST_UPR2=s_eSOST_UPR2;
//
				eepromReadByte(op);//��������� �� EEPROM
				s_eSOST_UPR3=EEDATA;op++;
				eSOST_UPR3=s_eSOST_UPR3;
//
				eepromReadByte(op);//��������� �� EEPROM
				s_eSOST_UPR_dop=EEDATA;op++;
				eSOST_UPR_dop=s_eSOST_UPR_dop;
				}
			else {f_chng_n_err=1;s_rtKMPh_l=rtKMPh_l;}



			op=0x80;

			for(ij=0;ij<128;ij++)
				{
				eepromReadByte(op);//��������� �� EEPROM
				buf_err[ij]=EEDATA;
				op++;
				}
				state_reg++;
				break;

	case 1:
			if(rbit&0x08)// �������� ������
				{
				rbit&=0xf7;

				op=0x80;
	
				for(ij=0;ij<128;ij++)
					{
					eepromReadByte(op);//��������� �� EEPROM
					op_b=EEDATA;
					if(op_b!=0xff)op_b=0xff;
					eepromWriteByte(op,op_b);//���������� � EEPROM
					op++;
					}
				op=0xf;op_b=0;
				eepromWriteByte(op,op_b);//���������� � EEPROM

				state_reg=0;
				break;
				}
				
			live_avr();

				if(z_rtKMPh_l&&(z_rtKMPh_l!=rtKMPh_l))
					{
					rtKMPh_l=z_rtKMPh_l;
					op_b=~rtKMPh_l;
					eepromWriteByte(EETCOM_H,op_b);
					}

if(t_U_napr<100){f_wr_err=0;s_eSOST_UPR_dop=0;
				s_eSOST_UPR1=s_eSOST_UPR2=s_eSOST_UPR3=0;}

			if(f_wr_err)
				{
				f_wr_err=0;
				if(f_chng_n_err)
					{
					f_chng_n_err=0;
					nom_err++;

					op=0xf;op_b=nom_err;
					eepromWriteByte(op,op_b);//���������� � EEPROM

					ij=((nom_err-1)&0x0f)*8;
					op=ij+0x80;

					op_b=nom_err;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM

					op++;ij++;
					op_b=rtKMPh_l;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM
					op++;ij++;
					op_b=rtKMPh_h;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM

					op++;ij++;
					op_b=eSOST_UPR1;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM
					op++;ij++;
					op_b=eSOST_UPR2;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM
					op++;ij++;
					op_b=eSOST_UPR3;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM
					op++;ij++;
					op_b=eSOST_UPR_dop;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM

					}
				else
					{
					ij=(((nom_err-1)&0x0f)*8)+3;
					op=ij+0x80;

					op_b=eSOST_UPR1;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM
					op++;ij++;
					op_b=eSOST_UPR2;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM
					op++;ij++;
					op_b=eSOST_UPR3;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM
					op++;ij++;
					op_b=eSOST_UPR_dop;
					buf_err[ij]=op_b;
					eepromWriteByte(op,op_b);//���������� � EEPROM
					}
				}

			if((z_nom_err<=nom_err)&&nom_err)
				{
				if(!z_nom_err)z_nom_err=nom_err;

				if((nom_err-z_nom_err)>15)z_nom_err=nom_err;

				ij=((z_nom_err-1)&0x0f)*8;
				t_nom=buf_err[ij++];
				t_l=buf_err[ij++];
				t_h=buf_err[ij++];
				t_sost1=buf_err[ij++];
				t_sost2=buf_err[ij++];
				t_sost3=buf_err[ij++];
				t_sost_dop=buf_err[ij++];


				if((!n_err_txt)||(rbit&0x04))
					{
					if(rbit&0x04)
						{
rep_txt:				n_err_txt++;yes_err=0;

					     switch(n_err_txt)
							{
							 case 1: //proverka flaga
									if(t_sost1&0x01)yes_err=1;
									 break;
							 case 2: //proverka flaga
									if(t_sost1&0x02)yes_err=1;
									 break;
							 case 3: //proverka flaga
									if(t_sost1&0x04)yes_err=1;
									 break;
							 case 4: //proverka flaga
									if(t_sost1&0x08)yes_err=1;
									 break;
							 case 5: //proverka flaga
									if(t_sost1&0x10)yes_err=1;
									 break;
							 case 6: //proverka flaga
									if(t_sost1&0x20)yes_err=1;
									 break;
							 case 7: //proverka flaga
									if(t_sost1&0x40)yes_err=1;
									 break;
							 case 8: //proverka flaga
									if(t_sost1&0x80)yes_err=1;
									 break;
				
							 case 9: //proverka flaga
									if(t_sost2&0x01)yes_err=1;
									 break;
							 case 10: //proverka flaga
									if(t_sost2&0x02)yes_err=1;
									 break;
							 case 11: //proverka flaga
									if(t_sost2&0x04)yes_err=1;
									 break;
							 case 12: //proverka flaga
									if(t_sost2&0x08)yes_err=1;
									 break;
							 case 13: //proverka flaga
									if(t_sost2&0x10)yes_err=1;
									 break;
							 case 14: //proverka flaga
									if(t_sost2&0x20)yes_err=1;
									 break;
							 case 15: //proverka flaga
									if(t_sost2&0x40)yes_err=1;
									 break;
							 case 16: //proverka flaga
									if(t_sost2&0x80)yes_err=1;
									 break;
					
							 case 17: //proverka flaga
									if(t_sost3&0x01)yes_err=1;
									 break;
							 case 18: //proverka flaga
									if(t_sost3&0x02)yes_err=1;
									 break;
							 case 19: //proverka flaga
									if(t_sost3&0x04)yes_err=1;
									 break;
							 case 20: //proverka flaga
									if(t_sost3&0x08)yes_err=1;
									 break;
							 case 21: //proverka flaga
									if(t_sost3&0x10)yes_err=1;
									 break;
							 case 22: //proverka flaga
									if(t_sost3&0x20)yes_err=1;
									 break;
							 case 23: //proverka flaga
									if(t_sost_dop&0x10)yes_err=1;
									 break;
							 case 24: //proverka flaga
									if(t_sost_dop&0x20)yes_err=1;
									 break;
							 case 25: //proverka flaga
									if(t_sost_dop&0x40)yes_err=1;
									 break;
							 case 26: //proverka flaga
									if(t_sost_dop&0x80)yes_err=1;
									 break;
							 case 27: //proverka flaga
									n_err_txt=0;n_err_bt=1;yes_err=1;
									 break;
							}
						if(!yes_err)goto rep_txt;
						goto indik_txt;
						}		
					
					}

indik_txt:	rbit&=0xfb;yes_err=0;				

				}
			else 
				{
				t_nom=t_l=t_h=0;
				t_sost1=t_sost2=t_sost3=t_sost_dop=0;
				}


			break;
	}//switch

}//regist_avr
