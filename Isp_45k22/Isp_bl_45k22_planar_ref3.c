#include <p18f45k22.h>
#include "sysrm_25k22_planar.h"
#include "razconst.h"
#include <delays.h>
#include <usart.h>

//45k22

#pragma	config	MCLRE=INTMCLR,WDTEN=ON,BOREN=ON,DEBUG=OFF	//WORK
#pragma	config	CP0=ON,CP1=ON,CPB=ON,CPD=OFF	//WORK
#pragma	config	WRT0=ON,WRT1=ON,WRTB=ON,WRTC=OFF,WRTD=OFF
#pragma	config	CP2=ON,CP3=ON,WRT2=ON,WRT3=ON	//25k22
//
//#pragma	config	CP0=OFF,CP1=OFF,CPB=OFF,CPD=OFF  //DEBUG
//#pragma	config	MCLRE=EXTMCLR,WDTEN=OFF,BOREN=OFF,DEBUG=ON,WRTD=OFF  //DEBUG
//#pragma	config	WRT0=OFF,WRT1=OFF,WRTB=OFF,WRTC=OFF  //DEBUG
//#pragma	config	CP2=OFF,CP3=OFF,WRT2=OFF,WRT3=OFF	//25k22
//
#pragma	config	PRICLKEN = OFF	//,PBADEN = OFF
//
#pragma	config 	PLLCFG=ON,FOSC=INTIO67
#pragma	config 	FCMEN=OFF,IESO=OFF
#pragma	config	BORV=285,WDTPS=512,PWRTEN=OFF
#pragma	config	PBADEN=OFF,CCP2MX=PORTB3
#pragma	config	LVP=OFF,XINST=OFF,STVREN=OFF
#pragma	config  EBTR0=OFF,EBTR1=OFF,EBTRB=OFF


void lin (void),TRANB(void),LINSTR(void),INTERPOL(void);
void PAUSE1(void);	
char RECVB(void);

#define H_def_12  0

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
#define Int_COM_RC PIR1bits.RCIF
#define Int_COM_TX PIR1bits.TXIF
#define On_COM_TX TXSTA1bits.TXEN = 1
#define Off_COM_TX TXSTA1bits.TXEN = 0
#define Int_COM_TX_EN PIE1bits.TX1IE = 1;
#define Int_COM_TX_DIS PIE1bits.TX1IE = 0;
#define Int_COM_RC_EN PIE1bits.RC1IE = 1; 
#define Int_COM_RC_DIS PIE1bits.RC1IE = 0; 
//
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

//
////////////////////////////////////////////////////////////////

#define	cConfig_t4 0

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


void Klav_read (void);	
void Obrabotka (void);

unsigned char eepromReadByte( unsigned char Adr ) ;
void eepromWriteByte( unsigned char Adr, unsigned char Data );

void INTERPOL(void);
void Config_T(void);
void Config_T_stb(void);

void SPROGN (void);
void Test_start(void);
void Tr_COM(void);
void Tr_COM2(void);
void regist_avr (void);

void tst_U_pr1 (void);
void tst_AN_X_h (void);
void tst_AN_X_l (void);
void tst_pr_stanby(void);
void tst_pr_stanby_rot(void);

void silov_kl(void);
void silov_kl_dop(void);

void silov_vent(void);
void silov_vent_st24(void);
void tst_V_cond (void);


rom far const unsigned char D_temp1[20]={0x00, 29, 0x01, 29,0x02, 30,0x10, 38,0x17, 40,0x49, 66,\
										 0x6A, 80,0x85, 95,0xF0,155,0xFF,165};
rom far const unsigned char D_temp2[20]={0x01, 165,0x10, 175,0x20, 185,0x30, 195,0x40, 205,0x50,215,\
										 0x60,225,0x70,235,0xFF,250};


rom far const unsigned char D_napr1[]={0x00, 00, 0x53, 100,0x7D, 150, 0xA8,200,0xD3,250,0xff, 254};

//���������� �������
rom far const unsigned char D_davl[]={0x00,00, 19,1, 30,3, 107,15, 224,34, 250,38};
//���������  �����
//rom far const unsigned char D_davl[]={0x00,00, 18,2,  118,15, 249,34, 255,35};// 5V

//

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
if(com_trm&&Int_COM_RC)ir=RCREG1;


	 if(Int_COM_RC)
		{
		if(yes_tr_com)
			{
			ir=RCREG1;
			yes_tr_com=0;
			return;
			}


		TMR0L=10;T0_ON;
		Int_T0_EN;
//
		buf_in[p_in] = RCREG1; 
//		TMR4=0;T4_ON;Int_T4_EN;
		if((buf_in[0]&0x80)&&(rs_mes_end)&&(!p_in))
			{
			rs_mes_start=1;
			rs_mes_end=0;
			L_in=(buf_in[0]&0x3f)+2;//����� ���� ������
			summa=0;summa = buf_in[0];
			p_in++;p_res=0;
			}
		else if(rs_mes_start&&(buf_in[1]==0x28))//�������
				{
				rs_mes_start=0;
				res[p_res] = buf_in[p_in];
				summa = summa + buf_in[p_in];
				p_in++;p_res++;
				}
			else if((!rs_mes_start)&&(!rs_mes_end))
					{
//					if(buf_in[2]!=0x31)
//						{p_res=0;p_in=0;rs_mes_end=1;return;}
					res[p_res] = buf_in[p_in];
					summa = summa + buf_in[p_in];

					 if(p_res==L_in)
						{
//						T4_OFF;TMR4=0;
//						Int_T4 = 0;Int_T4_DIS;	
						rs_mes_end=1;
						L_res=L_in;
						summa=summa-buf_in[p_in];

			if(summa==buf_in[p_in])
				{
					if(buf_in[2]!=0x31)
						{p_res=0;p_in=0;rs_mes_end=1;rs_mes_start=0;return;}
				rs_mes=1;
	//			cikl_int++;
				com_line=res[2];
				fl_Kline=1;
				}
		else 
			{
	//		cikl_err++;

			}
						}

//					else {rs_mes=0;p_in=0;rs_mes_end=1;rs_mes_start=0;return;}
					p_res++;p_in++;
					}
					if((!(buf_in[0]&0x80))&&((buf_in[0]&0x7f)>15)&&rs_mes_end&&(!p_in)) 
						{rs_mes=0;p_in=0;rs_mes_end=1;rs_mes_start=0;return;}
//					if(p_in>18){p_res=0;p_in=0;rs_mes_end=1;rs_mes_start=0;rs_mes=0;}
			}

	else if(Int_COM_TX&&com_trm)
		{
		Int_COM_TX=0;
		if(( p_out <= L_out+1 )&&(L_out>3))
			{
//			End_COM_TX;
			TXREG=buf_out[p_out++];
			}
		else {
				Int_COM_TX_DIS;
//				End_COM_TX;
				com_trm=0;
				Int_COM_RC_EN;
				ir = RCREG1; 
				yes_tr_com=1;
				p_out=0;L_out=0;
//				Off_COM_TX;
				
			 }
		}
	else if(Int_T0)
			{
			Int_T0=0;
			Int_T0_DIS;T0_OFF;
			p_res=0;p_in=0;
			rs_mes_end=1;rs_mes_start=0;

			op_b = RCREG1; 

			if(rs_mes)
				{
				rs_mes=0;
				t_F_MEN=0;
				switch(com_line)
					{

					 case 0x21://readDataByLocalIdentifier

		//					chetchik++;

		 				ClrWdt();
//
						tester_rej=res[3];
	//
					if(tester_rej != 0xf0)
						{
						uUPR_BT=res[4];
						uUPR_BT=uUPR_BT&cUPR_BT;

						uUPR_BT_dop&=0xf8;
						uUPR_BT_dop=uUPR_BT_dop|res[5];


						sSTATUS=res[7];
						fAVR_IND=res[8];
	
						multi=res[9];
  						if(tester_rej == 0xf2)
						multi=0x55;

						POWER_OTOP=res[10];
						}
					else
						{
						f_stend_hand=1;
						uUPR_BT=res[4];
						uUPR_STEND=res[5];
						}
					if(L_in == 14)if(t_mot_l_14 < 5)t_mot_l_14++;
			
					if((L_in == 14)&&(t_mot_l_14 > 2))
						{
						f_new_mtch =1;
						rtKMPm=res[11];
						rtKMPh_l=res[12];
						rtKMPh_h=res[13];
//op=0;//read_tab(op);//����� � EEPROM ����������
//op_b_ee=0xff;//
//eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM
						
						op=0;eepromReadByte(op);
						se_rtKMPm=EEDATA;
						op=1;eepromReadByte(op);	
						se_rtKMPh_l=EEDATA;
						op=2;eepromReadByte(op);
						se_rtKMPh_h=EEDATA;
//
if((se_rtKMPm==0xff)||(se_rtKMPh_l==0xff)||(se_rtKMPh_h==0xff))
	{
	op=0;op_b_ee=0;
	eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM						
	op=1;						
	eepromWriteByte(op,op_b_ee);
	op=2;				
	eepromWriteByte(op,op_b_ee);

se_rtKMPm=se_rtKMPh_l=se_rtKMPh_h=0;

	}

if((rtKMPm==0xff)||(rtKMPh_l==0xff)||(rtKMPh_h==0xff))
	{
	rtKMPm=rtKMPh_l=rtKMPh_h=0;f_new_mtch =0;
	}
						if(f_new_mtch)
							{
							if(rtKMPh_h > se_rtKMPh_h)
								{
								op=0;op_b_ee=rtKMPm;
								eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM
								op=1;op_b_ee=rtKMPh_l;
								eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM
								op=2;op_b_ee=rtKMPh_h;
								eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM
								}
							else if(rtKMPh_h == se_rtKMPh_h)
								{
								if(rtKMPh_l > se_rtKMPh_l)
									{
									op=0;op_b_ee=rtKMPm;
									eepromWriteByte(op,op_b_ee);
									op=1;op_b_ee=rtKMPh_l;
									eepromWriteByte(op,op_b_ee);
									}
								else if(rtKMPh_l == se_rtKMPh_l)
									{
									if(rtKMPm > se_rtKMPm)
										{
										op=0;op_b_ee=rtKMPm;
										eepromWriteByte(op,op_b_ee);
										}
									}
								}
							op=0;eepromReadByte(op);
							se_rtKMPm=EEDATA;
							op=1;eepromReadByte(op);	
							se_rtKMPh_l=EEDATA;
							op=2;eepromReadByte(op);
							se_rtKMPh_h=EEDATA;
							}
						}
							
		//		if(sDAT_BIT&0x80)
		//			{
		//			TRISDbits.TRISD7=0;
		//			LATDbits.LATD7=1;
		//			}

				if(f_yes_Tcmp&&(f_klp_cmp==0))fConfig_t|0x10;

							buf_out[0]=0x80;
							buf_out[1]=0x32;
							buf_out[2]=k_line_adr;
							buf_out[3]=0x41;
							buf_out[4]=fConfig_t;
							ip=5;
//
							buf_out[ip++]=T_ISP;
							buf_out[ip++]=T_AIR;
							buf_out[ip++]=U_nap;
							buf_out[ip++]=U_pr1;
							buf_out[ip++]=U_pr2;
//SOST_UPR1=0;
							buf_out[ip++]=SOST_UPR1&cSOST_UPR1;
//SOST_UPR2=0;
							buf_out[ip++]=SOST_UPR2&cSOST_UPR2;
//SOST_UPR3=0;
							buf_out[ip++]=SOST_UPR3&cSOST_UPR3;
//
						if(YES_OTOP2)
							{
							buf_out[ip++]=adc_ch_1_4;
							buf_out[ip++]=adc_ch_5_8;
							buf_out[ip++]=drivers;
							buf_out[ip++]=ctrl;
							}
						else
							{
							buf_out[ip++]=I_CL_isp1;
							buf_out[ip++]=I_CL_isp2;
							buf_out[ip++]=I_CL_knd1;
							buf_out[ip++]=I_CL_knd2;
							}

						if((tester_rej==0xf2)&&(U_CL_isp1>50))U_CL_isp1=100;
							if(fConfig_t&0x01)buf_out[ip++]=U_CL_isp1;
							else buf_out[ip++]=0;

						if((tester_rej==0xf2)&&(U_CL_isp2>50))U_CL_isp2=100;
							if(fConfig_t&0x02)buf_out[ip++]=U_CL_isp2;
							else buf_out[ip++]=0;

						if((tester_rej==0xf2)&&(U_CL_knd1>50))U_CL_knd1=100;
							if(fConfig_t&0x04)buf_out[ip++]=U_CL_knd1;
							else buf_out[ip++]=0;

						if((tester_rej==0xf2)&&(U_CL_knd2>50))U_CL_knd2=100;
							if(fConfig_t&0x08)buf_out[ip++]=U_CL_knd2;
							else buf_out[ip++]=0;
//
	if((tester_rej==0xf2)&&(sDAT_DAT==0x7)&&(sDAT_BIT==0x3)&&(multi==0x55))
		sDAT_BIT|=0x04;
//		if((tester_rej==0xf2)&&(sDAT_DAT==0x7)&&(multi==0x55))sDAT_BIT&=0xfb;
			if((tester_rej==0xf2)&&(multi==0x55))DOP_MODUL=0;

//
						if(YES_OTOP2)sDAT_BIT|=0x08;

						if(f_new_mtch==0)
							{
							if(f_stend_hand)buf_out[ip++]=ssDAT_BIT;
							else buf_out[ip++]=sDAT_BIT&0xdf;

						if(YES_OTOP2)
							{
							buf_out[ip++]=ctrl2;
							buf_out[ip++]=warning;
							buf_out[ip]=err_plan;
							}
						else
							{
							buf_out[ip++]=I_C_def;
							buf_out[ip++]=I_C_con;
							buf_out[ip]=I_Comp;
							}

							sDAT_BIT&=0xdf;
							}
						else
							{
							buf_out[ip++]=sDAT_BIT|0x20;
							buf_out[ip++]=se_rtKMPm;
							buf_out[ip++]=se_rtKMPh_l;
							buf_out[ip]=se_rtKMPh_h;
							f_new_mtch=0;
							}
//
						if(fConfig_t&0x10)// ������ ����������
							{			  //�����������		
							ip++;
							buf_out[ip++]=T_CMP;
							buf_out[ip]=0;
							}
//
							if(f_davl_an)
								{
								buf_out[3]|=0x02;
								ip++;
								buf_out[ip]=U_davl;
								}
							else buf_out[3]&=0xfd;
//
							if(DOP_MODUL)  //&&(multi==0x55))
								{
								ip++;
								if(uC_isp1)SOST_UPR_dop|=0x01;
								else SOST_UPR_dop&=0xfe;
								if(uC_isp2)SOST_UPR_dop|=0x02;
								else SOST_UPR_dop&=0xfd;

								if(fH_def)
									{
									buf_out[3]|=0x08;//���� ������ �������
									}
								buf_out[ip]=SOST_UPR_dop;
								buf_out[3]|=0x04;//���� ��� �����
								if(on_cndl)buf_out[3]|=0x20;//���� ������
								}

//							if(fH_def&&(multi==0x55)&&(DOP_MODUL==0)&&(f_klp_cmp==0))
							if((fH_def||fH_def_12)&&(DOP_MODUL==0)&&(f_klp_cmp==0))
								{
								ip++;
								SOST_UPR_dop&=0x0c;
								buf_out[3]|=0x08;//���� ������ �������
								buf_out[ip]=SOST_UPR_dop;
								}

							if(f_klp_cmp)  //&&(multi==0x55))
								{
								ip++;
								if(uC_isp1)SOST_UPR_dop|=0x01;
								else SOST_UPR_dop&=0xfe;

								if(fH_def)
									{
									buf_out[3]|=0x08;//���� ������ �������
									}

								buf_out[ip]=SOST_UPR_dop;
								}

							if((!DOP_MODUL)&&(multi==0x55))
							 	{buf_out[3]&=0xfb;}//��� ��� �����

							if(bl_up_dvg)buf_out[3]|=0x10;
							if(fDO_CMP)buf_out[3]|=0x80;
//
							Tr_COM();



//
						break;	
//


					}
				}
			else {if(t_F_MEN<12)t_F_MEN++;}

		}

}

void Tr_COM(void) 
	{ 
	Int_COM_RC_DIS;
	yes_tr_com=0;

	pult_yes=0;

	com_trm=1;
	//
	buf_out[0]=buf_out[0]+ip-2;
	summa_tr=0;
	L_out=ip;
	for(ip=0; ip <= L_out; ip++ )
		{
		summa_tr = summa_tr + buf_out[ip];
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
	L_out2=ip2-1;
	
	p_out2 = 0;
	On_COM2_TX;
	Int_COM2_TX_EN;
	
	timer1++;
	}	


#pragma code
#pragma interruptlow low_isr
void low_isr (void)//���� ��� �������� ������
	{
PIR2bits.TMR3IF=0;
	 TMR3H=0x3c;	//3C
	 TMR3L=0x80;//
//

	 CLOC1s--;

	 ClrWdt();
  	 
	 if((CLOC1s==5)||(CLOC1s==10)||(CLOC1s==15))
		{   
		Nop();F_MEN=1;//10��� � �������
		}

	 if(!CLOC1s)
		{
		CLOC1s=20;FCL1s=1;
		}

if(com_trm2&&Int_COM2_RC)ip2=RCREG2;
if(!com_trm2&&Int_COM2_TX){Off_COM2_TX;Int_COM2_TX=0;}


	 if(Int_COM2_RC&&(!com_trm2))
		{
/*
		if(yes_tr_com2)
			{
			ipp=RCREG2;
			yes_tr_com2=0;
			p_in2=0;p_res2=0;
			return;
			}
*/
		buf_in2[p_in2] = RCREG2; 
//
		TMR1H=0x30;TMR1L=0x00;T1_ON;Int_T1_EN;

		if((rs_mes_end2)&&(!p_res2))
			{
			if(buf_in2[p_in2]!=0xAA)//
				{p_res2=0;rs_mes_end2=1;res2[0]=0;return;}
			rs_mes_start2=1;
			rs_mes_end2=0;
			L_in2=(buf_in2[0]&0x3f)+2;//����� ���� ������

			p_in2++;p_res2=0;
			}
		else if(rs_mes_start2)//&&((buf_in2[1]==0x2b)||(buf_in2[1]==0x2a)||(buf_in2[1]==0xf1)))//�������
				{
				rs_mes_start2=0;
				res2[p_res2] = buf_in2[p_in2];
				summa2 = summa2 + buf_in2[p_in2];
				p_in2++;p_res2++;
				}
			else if((!rs_mes_start2)&&(!rs_mes_end2))
					{
					res2[p_res2] = buf_in2[p_in2];
//
					p_res2++;p_in2++;
					}
		//			if((!(buf_in2[0]&0x80))&&((buf_in2[0]&0x7f)>15)&&rs_mes_end2&&(!p_in2)) 
		//				{rs_mes2=0;p_in2=0;rs_mes_end2=1;rs_mes_start2=0;return;}
	//				if(p_in2>40){p_res2=0;rs_mes_end2=1;rs_mes_start2=0;rs_mes2=0;}
			}//p_in2=0;

	else if(Int_COM2_TX&&com_trm2)
		{
		Int_COM2_TX=0;
		if(( p_out2 <= L_out2+1 )&&(L_out2>3))
			{
//			End_COM_TX;
			TXREG2=buf_out2[p_out2++];
			}
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

			L_res2=p_res2;

 			if((res2[0]==3)&&(res2[3]==6))// �����������
				{
				rs_mes2_diag=1;
				timer2 ++;
				res2[0]=0xee;
				cikl_plan = 0;

				adc_ch_1_4 = res2[4];
				adc_ch_5_8 = res2[5];
				drivers = res2[6];
				ctrl = res2[7];
				ctrl2 = res2[8];
				warning = res2[9];
				}
 			if((res2[0]==3)&&(res2[3]==0x1a))// ���������
				{
				rs_mes2_sost=1;
				timer2 ++;
				res2[0]=0xee;
				cikl_plan = 0;

				Power_Level = res2[11];
				Phase = res2[12];
				ErrorCode = res2[15];
				Script = res2[20];
				}

//Script	Phase	�������� ������
//2		0	��������
//2		1	�������� ��� ������ �������
//2		2	�������� ����� ��������
//2		10	������
//2		14	�������
//2		25	���������� � ������ ��������
//2		20	������
//2		30	��������
//2		31	�������� ��� �����
//2		32	�������� ��� ���������
//2		33	�������� ��� �������������

 			if((res2[0]==8)&&(res2[3]==7))// ������ ������
				{
				rs_mes2_data=1;
				timer3 ++;
				res2[0]=0xee;
				cikl_plan = 0;
				}

			tester_lin=buf_in2[2];
			com_line2=res2[2];

			p_res2=0;
			buf_in2[p_in2++]=0xdd;
			buf_in2[p_in2++]=0xdd;

/*
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
*/

			}


	}

#pragma code progrm=0x2a

void main(void)
{
PORTA = 0x40;
ANSELA = 0x03;	//1-analog
LATA = 0x40;
TRISA = 0x00; 

PORTB = 0x00; 
ANSELB = 0x20;
LATB = 0x00;
TRISB = 0x30;

CCP1CON=0x00;

PORTC = 0x40;
ANSELC = 0x38;
LATC =0x40;
TRISC = 0xa0;  

//===================
PORTD = 0xc0; 
ANSELD = 0x3f;
LATD =0xc0;
TRISD = 0xb2;

PORTE = 0x04; 
ANSELE = 0x00;
LATE =0x04;
TRISE = 0x00;
//===================
//

if(H_def_12)fH_def_12 = 1;
 
ADCON0 = 0x0;
ADCON1 = 0x00;
ADCON2 = 0x26;

CM1CON0 = 0x0;
CM2CON0 = 0x0;

HLVDCON = 0x0;

OSCCON=0xe0;	//8MG
//OSCCON=0xb0;	//1MG
OSCCON2=0x00;

OSCTUNE=0x40;

//T0CON = 0x48;//115200
T0CON = 0x47;//10400
T1CON = 0x31;
T3CON = 0x31;

Delay10KTCYx(250);ClrWdt();
Delay10KTCYx(250);ClrWdt();
Delay10KTCYx(250);ClrWdt();
Delay10KTCYx(250);ClrWdt();
Delay10KTCYx(250);ClrWdt();
Delay10KTCYx(250);ClrWdt();
Obrabotka();

TBLPTRU=0;
CLOC01=10;//
CLOC1s=10;//1 sek

RCONbits.IPEN=1;// 2 ������ ����������
INTCON=0xc0;//��������� 2 ������ ����������

INTCON2bits.TMR0IP=1;//������� ������� ���������� �� ������� 0

//ptrindex=0x100;
INTCONbits.TMR0IE=0;//��������� ���������� �� ������� 0

//		��������� COM
		Open1USART( USART_TX_INT_OFF	  &
				   USART_RX_INT_ON    &
				   USART_ASYNCH_MODE  &
				   USART_EIGHT_BIT    &
				   USART_CONT_RX      &
				   USART_BRGH_HIGH, 188 ); // 10400 ??? ,191

/*
		Open2USART( USART_TX_INT_OFF	  &
				   USART_RX_INT_ON    &
				   USART_ASYNCH_MODE  &
				   USART_EIGHT_BIT    &
				   USART_CONT_RX      &
				   USART_BRGH_HIGH, 800 ); // 10400 ??? ,191
*/

//
TXSTA2 = 0x00; // Reset USART registers to POR state
RCSTA2 = 0x90;
BAUDCON2 = 0x08;
SPBRG2 = 32;// Write baudrate to SPBRG1  832 - 2400
SPBRGH2 = 3;


//

CCP1CON=0x00;
//CCP2CON=0x0C;
T2CON=0x05;		//PRESCALER /16
//PR2=0x7f;		//Tpwm = 128 x 4 x (1/32) x 4 = 48 ���
//Tpwm = (PR2+1) x 4 x (Tosc) x PRStmr2
//CCPR1L=0;
//CCPR2L=60;



//TMR0L=100;


IPR1bits.RC1IP = 1;  
IPR1bits.TX1IP = 1;
PIE1bits.TX1IE = 0; 

IPR3bits.RC2IP = 0;  
IPR3bits.TX2IP = 0;
PIE3bits.TX2IE = 0; 


rs_mes_end=1;
Int_COM_RC_EN;

IPR2bits.TMR3IP=0;
PIE2bits.TMR3IE=1;

IPR1bits.TMR1IP=0;

rs_mes_end2=1;
Int_COM2_RC_EN;


//op=0;//read_tab(op);//����� � EEPROM ����������
//op_b_ee=0xff;//
//eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM

	trON_AD=0;ON_AD=1;Nop();Nop();
	trON_AD=1;Nop();Nop();
	if(ON_ADp)
		{
		f_davl_an=0;//��� ������ ���������� (��������� ���)
		ANSELB &= 0xfd; //RB1
		}
	else 
		{
		f_davl_an=1;// ����������
		ANSELB |= 0x02; //RB1
		}
	trON_AD=0;ON_AD=0;

op=0;eepromReadByte(op);
se_rtKMPm=EEDATA;
op=1;eepromReadByte(op);
se_rtKMPh_l=EEDATA;
op=2;eepromReadByte(op);
se_rtKMPh_h=EEDATA;

//
if((se_rtKMPm==0xff)||(se_rtKMPh_l==0xff)||(se_rtKMPh_h==0xff))
	{
	op=0;op_b_ee=0;
	eepromWriteByte(op,op_b_ee);//���������� ���� � EEPROM						
	op=1;						
	eepromWriteByte(op,op_b_ee);
	op=2;				
	eepromWriteByte(op,op_b_ee);

se_rtKMPm=se_rtKMPh_l=se_rtKMPh_h=0;

	}


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
		RCSTAbits.CREN=0;
		Nop();
		RCSTAbits.CREN=1;
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
		
	 ClrWdt();

//f_davl_an=0;

	if(f_ACC)
		{
		if((L_out==0)&&(p_in==0))
			{
			tst_V_cond();
			}

		}
else
	t_stanby=0;






//if(f_ACC)
//	t_stanby=20;

/*
Nop();
Nop();
tst_pr_stanby();



Nop();
Nop();
tst_pr_stanby();
Nop();
Nop();
tst_pr_stanby();
Nop();
Nop();
tst_pr_stanby();
Nop();
Nop();
*/
if(L_out==0)
	if(yes_tr_com&&(!pult_yes))
		{
		t_cl_1s++;
		if((t_cl_1s==5)||(t_cl_1s==10))FCL05s=1;
		if(t_cl_1s>9)
			{
			t_cl_1s=0;
			FCL1s=1;
			t_cl_1m++;
			if(t_cl_1m>3)t_cl_1m=0;
			}


		F_MEN=0;pult_yes=1;
//		t_F_MEN=0;

		 TMR3H=0x3c;	//3C
		 TMR3L=0x80;//

		CLOC1s=20;

/*
	trON_AD=0;ON_AD=1;Nop();Nop();
	trON_AD=1;Nop();Nop();
	if(ON_ADp)
		{
		f_davl_an=0;//��� ������ ���������� (��������� ���)
		ANSELB &= 0xfd; //RB1
		}
	else 
		{
		f_davl_an=1;// ����������
		ANSELB |= 0x02; //RB1
		}
	trON_AD=0;ON_AD=0;
*/

//f_davl_an=0;


	if(tester_rej==0xf2){f_davl_an=0;ANSELB &= 0xfd;} //RB1

		Obrabotka();

//if(f_ACC)
//	tst_V_cond();


		if(U_nap>70)
			{
//			if(tON_OFF==20)
//				{
//				TRISAbits.TRISA7=0;
//				LATAbits.LATA7=1;
//				Delay10KTCYx(5);
//				}
/*
			if((tON_OFF<20)&&tON_OFF)
				{
				TRISAbits.TRISA7=0;
				LATAbits.LATA7=0;
				uUPR_BT=0;f_ACC=0;
				Delay10KTCYx(100);
				tON_OFF--;
				}
*/
//			tON_OFF=20;
			if(!f_ACC)
				{
				t_stanby = 0;
				f_ACC=1;
				Config_T();

				TRISAbits.TRISA7=0;
				LATAbits.LATA7=1;

				}
			}
	
		if(U_nap<=40)
			{
			f_ACC=0;
			if(tON_OFF)tON_OFF--;
			else 
				{
				if(fAVR_IND&0x80)
					{
					if(!fSTANBY)
						{
						TRISAbits.TRISA7=0;
						LATAbits.LATA7=0;
						uUPR_BT=0;f_ACC=0;
						Delay10KTCYx(100);
						}
					}
				if(multi==0xaa)
					{
					TRISAbits.TRISA7=0;
					LATAbits.LATA7=0;
					uUPR_BT=0;f_ACC=0;
					Delay10KTCYx(100);
					}

				}
			}	

//		if(uR_err)
//			{
//			SOST_UPR1=SOST_UPR2=SOST_UPR3=0;
//
//			t_avr_comp=t_avr_con=t_avr_def=0;
//			t_avr_isp1=t_avr_isp2=t_avr_knd1=t_avr_knd2=0;
//			tRAZG_isp1=tRAZG_isp2=tRAZG_knd1=tRAZG_knd2=tRAZG_isp3=0;
//			}

	if(multi==0x55){if((!uC_def)&&uC_con&&uCOMP)uCOMP=0;}


//tester_rej=0xf2;

		if((tester_rej==0xf2)&&(multi==0x55)&&(fConfig_t&0x0e))//&&(f_standart)
			{
			sDAT_DAT=0;	
			trON_OTOP=0;ON_OTOP=0;
			trREZIST=0;REZIST=0;Nop();Nop();
			trREZIST=1;
			trSVD_OTOP=0;SVD_OTOP=1;
			ANSELE |= 0x04;
			Nop();Nop();Nop();Nop();
			op_bp=7;tst_AN_X_h();//AN10
			vREZIST=ADRESH;
			ANSELE &= 0xfb;

//			if((vREZIST>50)&&(vREZIST<90))sDAT_DAT++;
			if(vREZIST>50)sDAT_DAT++;

			trSVD_OTOP=0;SVD_OTOP=0;
			Delay100TCYx(50);
			trSVD_OTOP=1;Nop();Nop();
			trREZIST=0;REZIST=1;
			Delay100TCYx(50);
			if(SVD_OTOPp){stSVD_OTOP=1;sDAT_DAT|=0x02;}
			else stSVD_OTOP=0;

			trREZIST=0;REZIST=1;
			trSVD_OTOP=0;SVD_OTOP=1;
			Delay100TCYx(50);
			trSVD_OTOP=1;
			trREZIST=1;
			trON_OTOP=0;ON_OTOP=1;
//			Nop();Nop();Nop();Nop();
			Delay100TCYx(50);
			if(!SVD_OTOPp)sDAT_DAT|=0x04;

			CCPR1L=60;

//sDAT_DAT = 0x7;

			}

//if(f_ACC)
//	tst_V_cond();


	//**************************************************
	// cool

	if((multi==0x55)||(multi==0x01))
		{

		if(DOP_MODUL&&(U_nap>40)&&(tester_rej!=0xf2))
			{
			if(sSTATUS>2)on_cndl=0;
			if(uCOMP&&(!uC_def))
				{
				uC_isp1=1;

				if((!on_cndl)&&zmk_C_isp1)uCOMP=0;
				if((!on_cndl)&&obr_C_isp1)uCOMP=0;

				if(zmk_C_isp1)uC_isp1=0;
				}
			if(!uCOMP){uC_isp1=0;}
	
			if(on_cndl&&uCOMP){uC_isp2=1;}
			if(on_cndl&&(!uCOMP)&&(!uC_def))
				{
				uC_isp2=1;uCOMP=1;
				if(zmk_C_isp2||obr_C_isp2)uCOMP=0;
				if(zmk_COMP)uCOMP=0;
				}
			if(on_cndl&&uCOMP)
				{
				uC_isp2=1;
				if(zmk_C_isp2)uC_isp2=0;
				}
	
			if(!on_cndl){uC_isp2=0;}
	
			if(uCOMP&&uC_def){uC_isp1=0;uC_isp2=0;}
	
			if(!uCOMP){uC_isp1=0;uC_isp2=0;}

			if((SOST_UPR_dop&0x23)==0x21)uCOMP=0;
			if((SOST_UPR_dop&0x13)==0x11)uCOMP=0;
			if((SOST_UPR_dop&0x43)==0x42)uCOMP=0;
			if((SOST_UPR_dop&0x83)==0x82)uCOMP=0;

			if(!(sDAT_BIT&0x2)&&(!uC_def)){uC_isp1=0;uC_isp2=0;uCOMP=0;}

//new_s			if((sDAT_BIT&0x1)&&(on_cndl)){uV_knd1=1;uV_knd2=1;}
//			else {uV_knd1=0;uV_knd2=0;}
			}
		else {on_cndl=0;}

		if(DOP_MODUL&&(U_nap<40))
			{
			uCOMP=0;uC_isp1=0;uC_isp2=0;
			}



// cool

//if(f_ACC)
//	tst_V_cond();

  if(tester_rej != 0xf2)
	if(f_stend_hand==1)
		{
		if(uUPR_STEND&0x80){ON_OTOP=1;}
		else {ON_OTOP=0;}

		trSVD_OTOP=0;SVD_OTOP=0;
		Delay100TCYx(30);
		trSVD_OTOP=1;
		if(SVD_OTOPp)fConfig_t |=0x40;//���� ��������� �����.
		else fConfig_t &=0xbf;

		trREZIST=1;
		Delay100TCYx(5);
		if(ON_OTOP_TSTp)fConfig_t |=0x80;
		else fConfig_t &=0x7f;
		trREZIST=0;REZIST=0;

		}

  if(tester_rej == 0xf2)
	{
	 fConfig_t &=0x7f;
	multi=0x55;
	}

	if(f_stend_hand==1)
		{
		ssDAT_BIT=0;
		ANSELB &= 0xfc; //RB1
		ANSELD &= 0xdf; //RB1

		trK1=0;K1=1;
		trK2=0;K2=1;
		trK3=1;

		Delay100TCYx(50);

		trK1=1;trK2=1; 

		Delay100TCYx(50);

		if(!K1p)ssDAT_BIT|=0x1;//mid
	//
		if(!K2p)ssDAT_BIT|=0x2;//max,min

		if(!K3p)ssDAT_BIT|=0x4;//max,min

	trON_AD=0;ON_AD=1;Nop();Nop();
	trON_AD=1;Nop();Nop();
	if(ON_ADp)ssDAT_BIT=0;

		}

	if(f_stend_hand==1)
		{
		if(uV_isp3){OUT_BUD=1;trOUT_BUD=0;}
		else {OUT_BUD=0;trOUT_BUD=0;}

			trDO_CMP=0;DO_CMP=1;
			Delay100TCYx(40);
			trDO_CMP=1;
			Delay100TCYx(40);
			if(!DO_CMPp){fDO_CMP=1;fConfig_t |=0x20;}
			else {fDO_CMP=0;fConfig_t &=0xdf;}

		}
	else if(uCOMP&&(!fSTANBY))
			{
			OUT_BUD=1;trOUT_BUD=0;

			trDO_CMP=0;DO_CMP=1;
			Delay100TCYx(100);
			trDO_CMP=1;
			Delay100TCYx(100);

			if(tester_rej==0xf2)
				{
				if(!DO_CMPp)
					{
					bl_up_dvg=1;fDO_CMP=0;
					}
				else fDO_CMP=1;
	
		//		if(DO_CMPp&&bl_up_dvg&&(tester_rej!=0xf2))uCOMP=0;
				if(DO_CMPp&&(fConfig_t&0x0c))uCOMP=0;
				}
			else
				{
				//���������� ACC
				op_bp=21;tst_AN_X_h();//AN21
				op_b=ADRESH+4;
				tarrom=&D_napr1[0];
				INTERPOL();
				sU_nap=op_b;
				if(sU_nap>90)
					{
					ANSELE|=0x1;
					op_bp=5;  //AN5  RE0
					tst_AN_X_h();//
								
					op_bp=ADRESH;
					ANSELE&=0x6;
		
					if(op_bp<120)
						{
						if(t_bl_dvg < 5)t_bl_dvg++;
						else {bl_up_dvg=1;fDO_CMP=0;}
						}
					else {fDO_CMP=1;t_bl_dvg = 0;}
		
					if((op_bp>120)&&bl_up_dvg&&(tester_rej!=0xf2))uCOMP=0;
					}
				}
			trDO_CMP=0;DO_CMP=0;
			}
		else 
			{
			OUT_BUD=0;
			trOUT_BUD=0;
			trDO_CMP=0;DO_CMP=0;
			}

		}

//if(f_ACC)
//	tst_V_cond();


//if(f_ACC)
//	tst_V_cond();
		

//		if(f_davl_an)
//			{
//			trK2=0;K2=1;// ������� ���. ����.
//			trK1=0;K1=0;
//			}

		if(multi==0x55)
			{
//new_s			if(on_cndl&&(sDAT_BIT&0x1)&&(!uV_knd1))
//				{uV_knd1=1;uV_knd2=1;}
			}

	if(f_ACC&&(t_ACC<12)){if(FCL1s)t_ACC++;t_ST_VENT=0;}
	if(!f_ACC){t_ACC=0;t_ST_VENT=0;}


	if(U_nap>75)
		{
		tst_ON=0;tr_tst_ON=1;

		if(t_ACC<10)
			{
			if(fSTANBY)uUPR_BT&=0x60;
			else uUPR_BT=0;
			}

		silov_kl();

			//���������� ACC
			op_bp=21;tst_AN_X_h();//AN21
			op_b=ADRESH+4;
			tarrom=&D_napr1[0];
			INTERPOL();
			sU_nap=op_b;
			if(sU_nap<85)
				{
				SOST_UPR1=0;
				SOST_UPR2&=0xfc;
				SOST_UPR3=0;
				SOST_UPR_dop=0;
				}


//			if(f_ACC)
//				tst_V_cond();
			
				if(f_klp_cmp==0)
					{	
					if(uUPR_BT_dop&0x01)uC_isp1=1;
			//		else uC_isp1=0;
					if(uUPR_BT_dop&0x02)uC_isp2=1;
			//		else uC_isp2=0;
					if(uUPR_BT_dop&0x04)uH_def=1;
					}
				else
					{	
					if(uUPR_BT_dop&0x01)uC_isp1=1;
					else uC_isp1=0;
					}
			
			if((tester_rej!=0xf2)&&(DOP_MODUL||f_klp_cmp))silov_kl_dop();
	//		else SOST_UPR_dop=0;
			
				
			
//		if(f_ACC)
//			tst_V_cond();

		uUPR_BT=uUPR_BT&fConfig_t;

//
//uUPR_BT &= 0xfc;

		if(fSTANBY&&fU_24)silov_vent_st24();
		else silov_vent();

			//���������� ACC
			op_bp=21;tst_AN_X_h();//AN21
			op_b=ADRESH+4;
			tarrom=&D_napr1[0];
			INTERPOL();
			sU_nap=op_b;
			if(sU_nap<70)
				{
				uUPR_BT=0;
				tst_ON=1;tr_tst_ON=0;
				silov_kl();
		if(fSTANBY&&fU_24)silov_vent_st24();
		else silov_vent();
				uUPR_BT_dop=0;
			if((tester_rej!=0xf2)&&(DOP_MODUL||f_klp_cmp))silov_kl_dop();
		
				SOST_UPR1=0;
				SOST_UPR2&=0xfc;
				SOST_UPR3=0;
				SOST_UPR_dop=0;
				t_mot_l_14=0;
				}
			if(sU_nap<90)
				{
				SOST_UPR1=0;
				SOST_UPR2&=0xfc;
				SOST_UPR3=0;
				SOST_UPR_dop=0;
				}
			}

			if(U_nap<51)
				{
				uUPR_BT=0;
				tst_ON=1;tr_tst_ON=0;
				silov_kl();
		if(fSTANBY&&fU_24)silov_vent_st24();
		else silov_vent();
				uUPR_BT_dop=0;
			if((tester_rej!=0xf2)&&(DOP_MODUL||f_klp_cmp))silov_kl_dop();
		
				SOST_UPR1=0;
				SOST_UPR2&=0xfc;
				SOST_UPR3=0;
				SOST_UPR_dop=0;
				}

		if((tester_rej!=0xf2)&&(YES_OTOP2==0))
			{
			if(!POWER_OTOP)
				{
				trREZIST=1;
				if(YES_OTOP){ON_OTOP=0;}
				if(ON_OTOP_TSTp){fConfig_t|=0x80;YES_OTOP=1;}
// 15_10_20	else fConfig_t&=0x7f;
				}
			else 
				{
				if(YES_OTOP){ON_OTOP=1;}
	//
				if(POWER_OTOP==1){trREZIST=0;REZIST=0;}
				else {trREZIST=1;}
				}
			}

//tech
//fConfig_t|=0x80;YES_OTOP=1;

		if(!YES_OTOP)
			{
			op_d++;

		if((timer1 > 10)&&(!(rs_mes2_diag+rs_mes2_sost)))NO_YES_OTOP2=1;

//		if()  
		  if(NO_YES_OTOP2 == 0)
			if(op_d==0x04)
				{
				op_d=0;
				op_d1++;
				
				if(YES_OTOP2)
					{
			// ��������� � ����������� ���������
			if(err_plan != 8)
				if((s_POWER_OTOP != POWER_OTOP)&&(s_POWER_OTOP==0))	
					if((com_planar == 0)&&(POWER_OTOP > 0))
						com_planar = 1;

			// ���������� � ����������� ���������
				if((s_POWER_OTOP != POWER_OTOP)&&(s_POWER_OTOP > 0))	
					if((com_planar == 0)&&(POWER_OTOP == 0))
						com_planar = 4;

			// ����������� ��������
				if((s_POWER_OTOP != POWER_OTOP)&&(s_POWER_OTOP==2))	
					if((com_planar == 0)&&(POWER_OTOP == 1))
						com_planar = 7;

			// ���������� ��������
				if((s_POWER_OTOP == POWER_OTOP)&&(s_POWER_OTOP==2))	
				  if((com_planar == 0)&&(Power_Level == 0))
					if(Phase == 20)
					  if(t_max_power == 0)	
						{s_POWER_OTOP = 1;}

				if((s_POWER_OTOP != POWER_OTOP)&&(s_POWER_OTOP==1))	
					if((com_planar == 0)&&(POWER_OTOP == 2))
						com_planar = 10;

					}
				else com_planar = 0;

				buf_out2[0]=0xaa;
				buf_out2[1]=0x09;
				buf_out2[2]=0xe8;
				buf_out2[3]=0x03;
				buf_out2[4]=0x07;
				buf_out2[6]=0xff;
				buf_out2[7]=0xff;
				buf_out2[8]=0x04;// ������ �� ��������.
				ip2=12;

				switch(com_planar)
					{
					 case 0://������ �����������
						fl_comnd++;
					if(fl_comnd&0x01)
						{
						buf_out2[0]=0xaa;
						buf_out2[1]=0x02; 
						buf_out2[2]=0xd0; //2000
						buf_out2[3]=0x07;
						buf_out2[4]=0x06;
						buf_out2[5]=0x54;
						}
					else
						{
						buf_out2[0]=0xaa;
						buf_out2[1]=0x02;
						buf_out2[2]=0xf4; //500
						buf_out2[3]=0x01;
						buf_out2[4]=0x1a;
						buf_out2[5]=0x96;
						}

						ip2=5;
						s_POWER_OTOP = POWER_OTOP;

						if(t_max_power)t_max_power--;

					break;

		//////////////////////////
				// ��������� � ����������� ���������
					 case 1:// ������ ����������
						s_POWER_OTOP = POWER_OTOP;
					 case 2:// ������ ����������

						buf_out2[5]=0x01;// 1 - ���,  2 - ����
						buf_out2[9]=0x01;
						buf_out2[10]=0x01;
						buf_out2[11]=0x00;
						buf_out2[12]=0x5d;
						com_planar++;
					break;
					 case 3:// ������ ����������
						com_planar = 0;	
						break;

		//////////////////////////
				// ���������� � ����������� ���������
					 case 4:// ������ ����������
						s_POWER_OTOP = POWER_OTOP;
					 case 5:// ������ ����������
						buf_out2[5]=0x02;// 1 - ���,  2 - ����
						buf_out2[9]=0x01;
						buf_out2[10]=0x01;
						buf_out2[11]=0x00;
						buf_out2[12]=0x3b;

						com_planar++;
					break;

					 case 6:// ������ ����������
						com_planar = 0;	
						break;

		//////////////////////////
				// ����������� ��������
					 case 7:// ������ ����������
						s_POWER_OTOP = POWER_OTOP;
					 case 8:// ������ ����������

						buf_out2[5]=0x00;// 1 - ���,  2 - ����
						buf_out2[9]=0x01;
						buf_out2[10]=0x01;
						buf_out2[11]=0x00;
						buf_out2[12]=0x82;
						com_planar++;
					break;

					 case 9:// ������ ����������
						com_planar = 0;	
						break;

		//////////////////////////
				// ���������� ��������
					 case 10:// ������ ����������
						s_POWER_OTOP = POWER_OTOP;
					 case 11:// ������ ����������
						buf_out2[5]=0x00;// 1 - ���,  2 - ����
						buf_out2[9]=0x0d;
						buf_out2[10]=0x01;
						buf_out2[11]=0x04;
						buf_out2[12]=0x64;
						com_planar++;
					break;

					 case 12:// ������ ����������
						com_planar = 0;	
						t_max_power = 20;
						break;
					}
				Tr_COM2();
				cikl_plan++;
				} //op_d==0x04

			 } // if(!YES_OTOP)
//
//
			if(rs_mes2_diag == 1)
				{
				YES_OTOP2=1;
				trREZIST=0;REZIST=1;
				}
			if(YES_OTOP2 == 1)
				{
				fConfig_t|=0x80;
				trREZIST=0;REZIST=1;

				if((Phase > 0)||(POWER_OTOP > 0))
					fConfig_t|=0x40;//���� ��������� �����.
				else fConfig_t&=0xbf;

				if(cikl_plan > 5)
					{
					if(cikl_plan == 6)com_planar = 4;
					cikl_plan = 7;
					fConfig_t&=0xbf;
					err_plan = 8;
					}
				else {err_plan = 0;err_mig = 0;}

//adc_ch_1_4
//0x01	�������� ��������� ������� ����������� ��������� ������� //6
//0x02	����� ������� ����������� ��������� ������� //6
//0x04	�������� ��������� ������� ����������� ��������� ----
//0x08	����� ������� ����������� ��������� ---
//0x10	�������� ��������� ������� ����������� ������� //17
//0x20	����� ������� ����������� �������  //17
//0x40	�������� ��������� ������� ����������� ������� //5
//0x80	����� ������� ����������� ������� //5

				if(adc_ch_1_4&0x01)err_plan = 6;
				if(adc_ch_1_4&0x02)err_plan = 6;
		//		if(adc_ch_1_4&0x04)err_plan =  ;
		//		if(adc_ch_1_4&0x08)err_plan =  ;
				if(adc_ch_1_4&0x10)err_plan = 17;
				if(adc_ch_1_4&0x20)err_plan = 17;
				if(adc_ch_1_4&0x40)err_plan = 5;
				if(adc_ch_1_4&0x80)err_plan = 5;


//adc_ch_5_8
//0x04	�������� ��������� ������� ����������� ���������� ������� //15
//0x08	����� ������� ����������� ���������� ������� //15

				if(adc_ch_5_8&0x04)err_plan = 15;
				if(adc_ch_5_8&0x08)err_plan = 15;


//drivers
//0x01	����� ���� ���������� ������ //7
//0x02	�� �������� ������� �� ��������� ����� //7
//0x04	����� ���� ����� //4
//0x08	�� �������� ������� �� ����� //4
//0x10	����������� ������� �� ��������� //11
//0x20	������������ ����������� ������� //11
//0x40	�� ��������� ������� ����������� ������� //11

				if(drivers&0x01)err_plan = 7;
				if(drivers&0x02)err_plan = 7;
				if(drivers&0x04)err_plan = 4;
				if(drivers&0x08)err_plan = 4;
				if(drivers&0x10)err_plan = 11;
				if(drivers&0x20)err_plan = 11;
				if(drivers&0x40)err_plan = 11;


//ctrl
//0x01	���������� ���� ����������� ������� //11
//0x02	���������� ���� ���������� ������ //7
//0x04	���������� ���� �����    //4
//0x08	���������� ���� (����������� � ����� ����) //22
//0x10	�� ��������� ����� (���� �������) //5
//0x20	�� ������� ������� �� 2 ������� //2

				if(ctrl&0x01)err_plan = 11;
				if(ctrl&0x02)err_plan = 7;
				if(ctrl&0x04)err_plan = 4;
				if(ctrl&0x08)err_plan = 22;
				if(ctrl&0x10)err_plan = 5;
				if(ctrl&0x20)err_plan = 2;

//ctrl2
//0x01	�������� ������� ����������� ������� //12
//0x02	�������� ������� ����������� ������� //15
//0x04	�������� ����. ��. ����. //12
//0x08	������ ����� � �������  //8
//0x10	��������� ����� ����������

				if(ctrl2&0x01)err_plan = 12;
				if(ctrl2&0x02)err_plan = 15;
				if(ctrl2&0x04)err_plan = 12;
				if(ctrl2&0x08)err_plan = 8;
	//			if(ctrl2&0x10)err_plan =  ;

				if(ErrorCode)err_plan = ErrorCode;

				if(err_plan > 0)// ����� ������
					{
					if(FCL05s)
						{
						svd_mig_1s++;
						if(!(svd_mig_1s & 0x01))err_mig++;
						}
	
					if(svd_mig_1s & 0x01)
						fConfig_t|=0x40;
					else fConfig_t&=0xbf;

				// ����� � ��������
					if(err_mig >= err_plan)
					//	if(!(svd_mig_1s & 0x01))
						{
						fConfig_t&=0xbf;
					if((err_mig - err_plan)>2)
						err_mig=0;
						}
					}

				} // YES_OTOP2 == 1


		FCL1s=0;FCL05s=0;
		}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

	 if(F_MEN||(t_F_MEN>10))
		{
		F_MEN=0;pult_yes=0;

		 ClrWdt();


//		if(multi!=0xaa)
//			{
//			CCP1CON=0x0;trSHIM=0;
//			}


		if(t_F_MEN<8)t_F_MEN++;

		if(t_F_MEN>6)
			{
//			TRISAbits.TRISA7=0;
//			LATAbits.LATA7=0;
//			Delay10KTCYx(40);

			POWER_OTOP=0;

		if(YES_OTOP2==0)
			if(YES_OTOP){ON_OTOP=0;trREZIST=1;}

			uUPR_BT=0;
			silov_kl();

		if(fSTANBY&&fU_24)silov_vent_st24();
		else silov_vent();

			SOST_UPR1=SOST_UPR3=0;
			SOST_UPR2&=0xfc;
			t_avr_isp1=t_avr_isp2=t_avr_knd1=t_avr_knd2=0;
			tRAZG_isp1=tRAZG_isp2=tRAZG_knd1=tRAZG_knd2=0;

			t_avr_comp=t_avr_con=t_avr_def=0;
			}

		Obrabotka();

//		trK2=0;K2=0;// ������� ���. ����.


		if(U_nap>70)
			{
			TRISAbits.TRISA7=0;
			LATAbits.LATA7=1;
			Delay10KTCYx(40);

			if(!f_ACC)
				{
				t_stanby = 0;
				f_ACC=1;
				Config_T();
				}
			tON_OFF=20;
			}	
		else if(t_F_MEN>6)	
			{
			uUPR_BT=0;f_ACC=0;
			TRISAbits.TRISA7=0;
			LATAbits.LATA7=0;
			Delay10KTCYx(40);
			}	

		}//F_MEN


  }//for

}//main



#define Tperiod 5

//**********************************************************
//**********************************************************
void Obrabotka (void)
{

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(f_davl_an)//�������� �� ����� � ��
	{
	ANSELB &= 0xfd; //RB1
	trK1=0;K1=1;
	Delay100TCYx(100);
	trK1=1;
	ANSELB |= 0x02; //RB1
	Delay100TCYx(100);

	op_bp=10;tst_AN_X_h();//AN10
	U_davl=ADRESH;

	if(U_davl<1)
		{
		op_bp=10;tst_AN_X_l();//AN10
		if(ADRESL<1)
			{fAD2_kz=1;fAD2_obr=0;}
		}
	else 
		{
		U_davl=1;
		fAD2_kz=0;
	
		ANSELB &= 0xfd; //RB1
		trK1=0;K1=0;
		Delay100TCYx(100);
		trK1=1;
		ANSELB |= 0x02; //RB1
		Delay100TCYx(100);
	
		op_bp=10;tst_AN_X_h();//AN10
		U_davl=ADRESH;
	
		if(U_davl<2)fAD2_obr=1;
		else fAD2_obr=0;
		}

	}// ������� ���. ����.


U_pr1=0;U_pr2=0;

for(iu=0;iu<20;iu++)
	{

//���������� ACC
	op_bp=21;tst_AN_X_h();//AN21

	op_b=ADRESH;
	if(op_b < 251)op_b+=4;

	tarrom=&D_napr1[0];
	INTERPOL();

	sU_nap=op_b;


	//���������� PR1
	op_bp=13;tst_AN_X_h();//AN13

	op_b=ADRESH;
	if(op_b < 242)op_b+=4;

	U_acp = op_b;
	
	tarrom=&D_napr1[0];
	INTERPOL();
	
	sU_pr1=op_b;



	if(iu==0)
		{
		max_U_acp=U_acp/2;
		sU_pr1_min=sU_pr1;sU_pr1_max=sU_pr1/2;
		sU_pr2_min=sU_nap;sU_pr2_max=sU_nap;
		}
	else 
		{
		if(max_U_acp < U_acp)max_U_acp=U_acp;
		if(sU_pr1_min>sU_pr1){sU_pr1_min=sU_pr1;}
		if(sU_pr1_max<sU_pr1){sU_pr1_max=sU_pr1;}
		
		if(sU_pr2_min>sU_nap){sU_pr2_min=sU_nap;}
		if(sU_pr2_max<sU_nap){sU_pr2_max=sU_nap;}
		}
	Delay100TCYx(20);
	}

//if(sSTATUS == 0)


if((t_stanby < 70)||(sSTATUS == 0))
	{
	if(t_stanby < 70)t_stanby++;
	if(t_stanby < 4)fSTANBY=0;
	if((sU_pr1_max-sU_pr1_min)>55)
		{
		fSTANBY=1;
//		TRISDbits.TRISD6=0;
//		LATDbits.LATD6=1;
		
		}
	if((sU_pr1_max-sU_pr1_min)<20)
		{
		fSTANBY=0;
//		TRISDbits.TRISD6=0;
//		LATDbits.LATD6=1;
		
		}

	}

//	else fSTANBY=0;
	
	U_pr1=sU_pr1_max;
	
	if((fSTANBY)&&(sU_pr1_max > 80))	U_pr1=sU_pr1_max-30;

	U_nap=sU_pr2_max;


//fU_24=0;

//if(U_pr1>200)fU_24=1;  //

//if(U_nap>210)fU_24=1;  //

if((t_stanby > 5)&&(t_stanby < 50))
	{
	if((st_stanby == 0)&&(fSTANBY))st_stanby=t_stanby;

	if(fSTANBY&&(st_stanby > 0))
		{
		uC_def=1;uC_con=1;
		if((t_stanby - st_stanby)  > 9)
			{uC_def=0;uC_con=0;}
		}

	if(st_stanby)	
	if((t_stanby - st_stanby)  > 7)
		{
 		if(U_nap>210)fU_24=1;  //
 		if(U_pr1>210)fU_24=1;  //
		}

	if(st_stanby==0)	
	if((t_stanby - st_stanby)  > 20)
		{
 		if(U_nap>210)fU_24=1;  //
 		if(U_pr1>210)fU_24=1;  //
		}
	}




if(U_nap>80)
	{ssU_nap=U_nap;t_s_U_nap=10;}
else 
	{
	if(t_s_U_nap){t_s_U_nap--;U_nap=ssU_nap;}

	if(fSTANBY&&t_s_U_nap)
		{U_nap=120;if(fU_24)U_nap=240;}
	}


if(!fSTANBY)
	{
	if((U_nap-30)<U_pr1) U_pr2=U_pr1;

	if((U_pr1>80)&&(!fU_24)) {U_pr2=U_pr1;no_U_pr2=0;}
	if((U_pr1<81)&&(!fU_24)) no_U_pr2=1;
	if((U_pr1>200)&&fU_24) {U_pr2=U_pr1;no_U_pr2=0;}
	if((U_pr1<201)&&fU_24) no_U_pr2=1;
	}
else 
	{
//	if((U_pr1>110)&&(!fU_24)) {U_pr2=U_pr1;no_U_pr2=0;}
//	if((U_pr1<111)&&(!fU_24)) no_U_pr2=1;

	if((U_pr1>90)&&(!fU_24)) {U_pr2=U_pr1;no_U_pr2=0;}
	if((U_pr1<91)&&(!fU_24)) no_U_pr2=1;

	if((U_pr1>220)&&fU_24) {U_pr2=U_pr1;no_U_pr2=0;}
	if((U_pr1<221)&&fU_24) no_U_pr2=1;

	
	if(fU_24)U_stnb = max_U_acp;
	else U_stnb = sU_pr1_max;

	 if(ii<32)
		{
		mU_stnb[ii]=U_stnb;
		if(iit < 35)iit++;
		ii++;
		if(ii==32)ii=0;
		}

	if(iit > 33)
		{
		Sum_acp = 0;
		 for(iis=0;iis<32;iis++)
			{
			Sum_acp += mU_stnb[iis];
			}
		Sredn_U_stnb = Sum_acp/32;
		}

	if(uUPR_BT&0x0f)
		{
		if(fU_24)
			{
			if(Sredn_U_stnb > 253)t_stb = 2;
			else if(Sredn_U_stnb > 245)t_stb = 1;
			else t_stb = 0;
			}
		else
			{
			if(Sredn_U_stnb > 170)t_stb = 2;
			else if(Sredn_U_stnb > 155)t_stb = 1;
			else t_stb = 0;
			}
		}
	else t_stb = 0;

	}



//if((U_pr1>200)&&fSTANBY&&(stU_nap>50))U_nap=255;//new1

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


if((f_davl_an)&&(U_nap>50))
	{
//	trK2=0;K2=1;// ������� ���. ����.
	ANSELB |= 0x02; //RB1

	trK1=1;K1=1;

	}
else
	{
	trK2=0;K2=0;// ������� ���. ����.
	ANSELB &= 0xfd; //RB1
	}




//����������� ����������
//
	op_bp=17;tst_AN_X_l();//AN17


if(ADRESH<3)
	{
	zmk_T_isp=0;
	obr_T_isp=0;

	if(ADRESH==1)
		{
		if(ADRESL>0x90)op_b=ADRESL-0x90;
		else op_b=0;
		if(op_b>0)
			{
			tarrom=&D_temp1[0];
			INTERPOL();
			}
		else op_b = 29;
		}
	if(ADRESH==2)
		{
		if(ADRESL<143)
			{
			op_b=ADRESL+0x70;
			tarrom=&D_temp1[0];
			INTERPOL();
			}
		else
			{
			op_b=ADRESL-142;
			tarrom=&D_temp2[0];
			INTERPOL();
			}
		}

	
		sT_ISP=op_b;
		
		if((sT_ISP)&&(iT_ISP==0)) iT_ISP=sT_ISP;
		if(iT_ISP==sT_ISP) tT_ISP=Tperiod;
		else if(tT_ISP) tT_ISP--;
			 else {iT_ISP=sT_ISP;tT_ISP=Tperiod;}


	if(ADRESH==0)
		{
		obr_T_isp=0;T_ISP=0;
		zmk_T_isp=1;iT_ISP=0;
		}
	}
else 
	{
	obr_T_isp=1;T_ISP=0;
	zmk_T_isp=0;iT_ISP=0;
	}

if(mT_ISP)T_ISP=mT_ISP;
else T_ISP=iT_ISP;

//
//����������� ��������� 
//
	op_bp=24;tst_AN_X_l();//AN24
	

if(ADRESH<3)
	{

zmk_T_air=0;
obr_T_air=0;

	if(ADRESH==1)
		{
		if(ADRESL>0x90)op_b=ADRESL-0x90;
		else op_b=0;
		if(op_b>0)
			{
			tarrom=&D_temp1[0];
			INTERPOL();
			}
		else op_b = 29;
		}
	if(ADRESH==2)
		{
		if(ADRESL<143)
			{
			op_b=ADRESL+0x70;
			tarrom=&D_temp1[0];
			INTERPOL();
			}
		else
			{
			op_b=ADRESL-142;
			tarrom=&D_temp2[0];
			INTERPOL();
			}
		}

	if(op_b>0)
		{
		sT_AIR=op_b;
		
		if((sT_AIR)&&(iT_AIR==0)) iT_AIR=sT_AIR;
		if(iT_AIR==sT_AIR) tT_AIR=Tperiod;
		else if(tT_AIR) tT_AIR--;
			 else {iT_AIR=sT_AIR;tT_AIR=Tperiod;}

		}

	if(ADRESH==0)
		{
		obr_T_air=0;T_AIR=0;
		zmk_T_air=1;iT_AIR=0;
		}
	}
else 
	{
	obr_T_air=1;T_AIR=0;
	zmk_T_air=0;iT_AIR=0;
	}

	if(mT_AIR)T_AIR=mT_AIR;
	else T_AIR=iT_AIR;


		//
		//������� ����������� �����������
		//
			op_bp=25;tst_AN_X_l();//AN25
		
		if(ADRESH<3)
			{
		
			zmk_T_cmp=0;
			obr_T_cmp=0;
		
			if(ADRESH==1)
				{
				if(ADRESL>0x90)op_b=ADRESL-0x90;
				else op_b=0;
				if(op_b>0)
					{
					tarrom=&D_temp1[0];
					INTERPOL();
					}
				else op_b = 29;
				}
			if(ADRESH==2)
				{
				if(ADRESL<143)
					{
					op_b=ADRESL+0x70;
					tarrom=&D_temp1[0];
					INTERPOL();
					}
				else
					{
					op_b=ADRESL-142;
					tarrom=&D_temp2[0];
					INTERPOL();
					}
				}
		
			if(op_b>0)
				{
				sT_CMP=op_b;
				
				if((sT_CMP)&&(iT_CMP==0)) iT_CMP=sT_CMP;
				if(iT_CMP==sT_CMP) tT_CMP=Tperiod;
				else if(tT_CMP) tT_CMP--;
					 else {iT_CMP=sT_CMP;tT_CMP=Tperiod;}
				}
		
		
			if(ADRESH==0)
				{
				obr_T_cmp=0;T_CMP=0;
				zmk_T_cmp=1;iT_CMP=0;
				}
			}
		else 
			{
			obr_T_cmp=1;T_CMP=0;
			zmk_T_cmp=0;iT_CMP=0;
			}
		
		if(mT_CMP)T_CMP=mT_CMP;
		else T_CMP=iT_CMP;

	if(f_klp_cmp==0){obr_T_cmp=0;zmk_T_cmp=0;}
	
	if(obr_T_cmp||zmk_T_cmp){f_yes_Tcmp=0;fAVR_TCMP=0;}
	else 
		{
		f_yes_Tcmp=1;t_tcmp=0;
		
		if(fAVR_TCMP)t_tcmp+=0x4;
		if(T_CMP<175)t_tcmp+=0x2;   //114
		if(T_CMP<155)t_tcmp+=0x1;   // 94

	//	if(t_tcmp==b'100')

		if(t_tcmp==0)fAVR_TCMP=1; //b'000'
		if(t_tcmp==6)fAVR_TCMP=1; //b'110'
		if(t_tcmp==7)fAVR_TCMP=0; //b'111'
		}

	if(multi==0x55)
		{
		if(!DOP_MODUL){on_cndl=0;k_door=0;}
		}
//	if(multi==0xaa)
//		{
//		if(!K3p){DOP_KLAPS=1;k_door=1;}
//		else {DOP_KLAPS=0;on_cndl=0;k_door=0;}
//		}

////////////////////////////////////////////////////////////
//DOP_MODUL=1;
////////////////////////////////////////////////////////////


if(U_nap>50)
	{

	if(DOP_MODUL&&(multi==0x55))
		{
//		trON_CNDL=0;ON_CNDL=0;
//		Nop();
		trON_CNDL=1;
//		Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
//		Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
//		Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();

		if(ON_CNDLp)on_cndl=1;
		else on_cndl=0;
		}
	if((!DOP_MODUL)&&(multi==0x55))on_cndl=0;
	 

	if((!DOP_KLAPS)&&(multi==0xaa))on_cndl=0;



//�� �� �����

	if(!f_davl_an)
		{

		trK1=0;K1=1;
		trK2=0;K2=1;
		trK3=1;

	if(YES_OTOP2==0)
		if(YES_OTOP){trSVD_OTOP=0;SVD_OTOP=0;}

		if(multi==0xaa){trDO_CMP=0;DO_CMP=0;}
		
		Delay100TCYx(100);
		
		trK1=1;trK2=1; 

	if(YES_OTOP2==0)
	 	if(YES_OTOP)trSVD_OTOP=1;

		if(multi==0xaa)trDO_CMP=1;

		Delay100TCYx(100);

//	
		if(tester_rej==0xf2)sDAT_BIT&=0xfc;    //
		else sDAT_BIT&=0xf8;    //

		if(!K1p)sDAT_BIT|=0x1;//mid
	//
		if(!K2p)sDAT_BIT|=0x2;//max,min

//		if(tester_rej==0xf2)sDAT_BIT|=0x4;//door

		if(on_cndl&&(multi==0x55))sDAT_BIT|=0x4;//�����. ��� ������.

//sDAT_BIT&=0xfe;

		//
	if(YES_OTOP2==0)
		if(YES_OTOP)
			{
			if(SVD_OTOPp)fConfig_t|=0x40;//���� ��������� �����.
			else fConfig_t&=0xbf;
			}

		if(multi==0xaa)
			{
			if(DO_CMPp)sDAT_BIT|=0x4;
			trDO_CMP=0;DO_CMP=0;
			}
			//
		trK1=0;K1=1;
		trK2=0;K2=1;

//		
		if((sDAT_BIT&0x3)==0x1)
			{
			uC_con=0;
//new_s			uV_knd1=1;uV_knd2=1;   //
			}

		}
//fConfig_t|=0x40;

	if(f_davl_an)
		{

		trK1=1;trK3=1;
		trK2=0;K2=1;//AD2

	if(YES_OTOP2==0)
		if(YES_OTOP){trSVD_OTOP=0;SVD_OTOP=0;}
		
		Delay100TCYx(50);

	if(YES_OTOP2==0)
	 	trSVD_OTOP=1;

		trK2=1; 
		Delay100TCYx(50);	

//������ AD2
//		if(!K2p)fAD2=0;//
//		else fAD2=1;

//��������� AD2
		if(!K2p)fAD2=1;//
		else fAD2=0;

		trK2=0;K2=0;


		op_bp=10;tst_AN_X_h();//AN10
		U_davl=ADRESH;

//	U_davl=195;

	sDAT_BIT&=0xf8;

	if(YES_OTOP2==0)
		if(YES_OTOP)
			{
			if(SVD_OTOPp)fConfig_t|=0x40;//���� ��������� �����.
			else fConfig_t&=0xbf;
			}

//		if(!K3p)sDAT_BIT|=0x4;//door
		if(on_cndl&&(multi==0x55))sDAT_BIT|=0x4;//�����. ��� ������.

//			trK1=0;
	//		trK2=0;K2=1;// ������� ���. ����.

		
	//200 - 30 ���
	//��������� ����� ��������� � ������ ��������?
	//21,5 - 121
	//32   - 
	//17   - 

		if(U_davl==255)U_davl=254;


		if((!uC_con)||((multi==0x01)&&uC_con))
			{
			if(U_davl>P_mid_c_17)               //   //123
				{sDAT_BIT|=0x1;f_d_mid=1;}//mid, D_davl > 17 ���
			if((U_davl>=P_mid_c_14)&&f_d_mid)   //   //110
				{sDAT_BIT|=0x1;}//mid, D_davl > 14 ���
			if(U_davl<P_mid_c_14)              //   //110
				{sDAT_BIT&=0xfe;f_d_mid=0;}//mid, D_davl < 14 ���
			}
		
//sDAT_BIT|=0x1;
//sDAT_BIT&=0xfe;
//
		if(uC_def&&uC_con)
			{
			if(U_davl>P_mid_h_26)        //   //181   
				{
				uC_con=0;		  //213	26 ���
				fuC_con=1;
//new_s				uV_knd1=1;uV_knd2=1;   //
				sDAT_BIT|=0x1;
				}//max, D_davl>25 ���
			}
		if(uC_def&&uC_con&&fuC_con)
			{
			if(U_davl>=P_mid_h_23)       //   //167
				{
				uC_con=0;			//190  23 ���
//new_s				uV_knd1=1;uV_knd2=1;   //
				sDAT_BIT|=0x1;
				}//max, D_davl>23 ���
			}

		if(uC_def&&uC_con&&fuC_con)
			{
			if(U_davl<P_mid_h_23)         //   //167
				{
				uC_con=1;fuC_con=0;
//new_s				uV_knd1=0;uV_knd2=0;   //
				sDAT_BIT&=0xfe;
				}//max, D_davl<23 ���
			}

//
		if(U_davl>P_max_32) //D_davl>32 ���          //   //200
			{
			sDAT_BIT|=0x2;
			f_d_max=1;
			uComp=0;   //
			}//max, 

		if((U_davl>=P_max_28)&&f_d_max)   //   //171
			{sDAT_BIT|=0x2;}//max, D_davl>24 ���

		if(U_davl<P_max_28)                //   //171
			{sDAT_BIT&=0xfd;f_d_max=0;}//max, D_davl<24 ���

		if(U_davl<P_min_01)               //   //21
			sDAT_BIT|=0x2;//min, D_davl < 1 ��� 


		op_b=U_davl;
		
		tarrom=&D_davl[0];
		INTERPOL();
		
		U_davl=op_b;

		if(fAD2)U_davl|=0x80;		

		if(fAD2_kz)U_davl=0xfe;
		if(fAD2_obr)U_davl=0xfd;

		sDAT_BIT^=0x2;

//new
//	if(tester_rej!=0xf3)
//		if(fAD2)uComp=0;

		if(fAVR_TCMP&&(f_klp_cmp==0))uComp=0;

		}

	}
else   //if(U_nap<50)
	{
	if(YES_OTOP2==0)
	  if(YES_OTOP)
		{
		trSVD_OTOP=0;SVD_OTOP=0;
		Delay100TCYx(100);
		trSVD_OTOP=1;
		Delay100TCYx(100);
		if(SVD_OTOPp)fConfig_t|=0x40;//���� ��������� �����.
		else fConfig_t&=0xbf;
//		trSVD_OTOP=0;SVD_OTOP=0;
		on_cndl=0;
		}
	}

}

//#####################################################
//***********************************************
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void tst_V_cond (void)
	{

	if(uV_knd1&&(fConfig_t&0x4)&&(tRAZG_knd1>=v_knd_razg))
		{
		//U_CL_knd1  ����������
		op_bp=U_V_knd1;
		tst_AN_X_h();//
					
		U_CL_knd1=ADRESH;

		if(U_CL_knd1>maxU_CL_knd1) maxU_CL_knd1=U_CL_knd1;
		if(U_CL_knd1<minU_CL_knd1) minU_CL_knd1=U_CL_knd1;
		}
	else 
		{
		minU_CL_knd1 = 250;
		maxU_CL_knd1 = 0;
		}

	if(uV_knd2&&(fConfig_t&0x8)&&(tRAZG_knd2>=v_knd_razg))
		{
		//U_CL_knd2  ����������
		op_bp=U_V_knd2;
		tst_AN_X_h();//
					
		U_CL_knd2=ADRESH;
	
		if(U_CL_knd2>maxU_CL_knd2) maxU_CL_knd2=U_CL_knd2;
		if(U_CL_knd2<minU_CL_knd2) minU_CL_knd2=U_CL_knd2;
		}
	else 
		{
		minU_CL_knd2 = 250;
		maxU_CL_knd2 = 0;
		}

	if(uV_isp1&&(fConfig_t&0x1)&&(tRAZG_isp1>=v_isp_razg))
		{
		anV_isp1=1;
		//U_CL_isp1  ����������
		op_bp=U_V_isp1;
		tst_AN_X_h();//

		U_CL_isp1=ADRESH;

		if(U_CL_isp1>maxU_CL_isp1) maxU_CL_isp1=U_CL_isp1;
		if(U_CL_isp1<minU_CL_isp1) minU_CL_isp1=U_CL_isp1;
		}
	else 
		{
		minU_CL_isp1 = 250;
		maxU_CL_isp1 = 0;
		}

	if(uV_isp2&&(fConfig_t&0x2)&&(tRAZG_isp2>=v_isp_razg))
		{
		//U_CL_isp2  ����������
		op_bp=U_V_isp2;
		tst_AN_X_h();//

		U_CL_isp2=ADRESH;

		if(U_CL_isp2>maxU_CL_isp2) maxU_CL_isp2=U_CL_isp2;
		if(U_CL_isp2<minU_CL_isp2) minU_CL_isp2=U_CL_isp2;
		}
	else 
		{
		minU_CL_isp2 = 250;
		maxU_CL_isp2 = 0;
		}

	}

//#####################################################
//***********************************************
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



void tst_U_pr1 (void)
	{
	//���������� PR1
	ADCON2bits.ADFM=0;	//>>
	
op_bp=13; //	op_bp=20;
	op_bp=op_bp<<2;
	ADCON0 = 0x01+op_bp;	//AN20
	
	op_b=40;
	while(op_b) op_b--;
	ADCON0bits.GO = 1;
	while(ADCON0bits.GO);
	if(ADRESH < 252)op_b=ADRESH+4;
	else op_b = 255;
	
	tarrom=&D_napr1[0];
	INTERPOL();
	
	sU_pr1=op_b;
	}

void tst_AN_X_h (void)
	{
	ADCON2bits.ADFM=0;	//>>
	
	op_bp=op_bp<<2;
	ADCON0 = 0x01+op_bp;
	
	op_b=40;
	while(op_b) op_b--;
	ADCON0bits.GO = 1;
	while(ADCON0bits.GO);
	}

void tst_AN_X_l (void)
	{
	ADCON2bits.ADFM=1;	//>>
	
	op_bp=op_bp<<2;
	ADCON0 = 0x01+op_bp;
	
	op_b=40;
	while(op_b) op_b--;
	ADCON0bits.GO = 1;
	while(ADCON0bits.GO);
	}





/*
void SPROGN (void)
{
 unsigned char ii;
 unsigned char s;
 unsigned char *tar1;

 u.w=0;
 tar1=tar;
 s=op_b;
 tar+=2;
 op_b=*tar;;
 if(op_b==0)//
	{
	 op_b=1;
	 *tar=op_b;
	 op_b=s;
		 for(ii=0;ii<10;ii++)
			{
			 tar++;
			 *tar=op_b;//
			}
	timer=10;		
	u.w=op_b*timer;
	*tar1=u.by[1];//
	*(tar1+1)=u.by[0];

	return;
	}
 op_b++;//
 if(op_b==0x0b) op_b=1;
 *tar=op_b;
 tar=tar+op_b;
 op_b=*tar;//
 ii=op_b;
 op_b=s;
 *tar=op_b;//
 u.by[1]=*tar1;//
 u.by[0]=*(tar1+1);
 timer=u.w;
 timer=timer+op_b-ii;
 u.w=timer;
 *tar1=u.by[1];//
 *(tar1+1)=u.by[0];
 op_b=(unsigned char)(timer/10);
}
*/

//��������� ������������
void INTERPOL(void)
{
 unsigned char x1,x2,y1,y2;
 
 x2=*(tarrom);//X1

 while(op_b>x2)
	{
	 x1=x2;
	 tarrom=tarrom+2;
	 x2=*(tarrom);//������� ��������� �������� X2
	}
 if(x2==x1) return;
 tarrom=tarrom+1;
 y2=*(tarrom);//Y2
 tarrom=tarrom-2;
 y1=*(tarrom);//������� ��������� �������� Y1
 timer=(unsigned int)(op_b-x1)*(y2-y1);
 op_b=(unsigned char)(timer/(x2-x1)+y1);//������������� ��������
}
/*
		while( EECON1bits.WR );
		EEADR =Adr;
		EECON1bits.EEPGD = 0; 
		EECON1bits.CFGS = 0;
		EECON1bits.RD = 1;
		while( EECON1bits.RD );
*/
//
unsigned char eepromReadByte( unsigned char Adr )
	{
		while( EECON1bits.WR );
		EEADR =Adr;
		EECON1bits.EEPGD = 0; 
		EECON1bits.CFGS = 0;
		EECON1bits.RD = 1;
		while( EECON1bits.RD );
	}
void eepromWriteByte( unsigned char Adr, unsigned char Data )
	{
		while( EECON1bits.WR );
		EEADR = Adr;//ee.by[0];
		EEDATA = Data;
		EECON1bits.EEPGD = 0; 
		EECON1bits.CFGS = 0;
		EECON1bits.WREN = 1;
		INTCONbits.GIE = 0;
		EECON2 = 0x55; 
		EECON2 = 0xaa; 
		EECON1bits.WR = 1;
		while( EECON1bits.WR );
		INTCONbits.GIE = 1;
		EECON1bits.WREN = 0;
	}







//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



void silov_vent_st24(void)
	{
		
//t_stb=1;

//tst_pr_stanby();


//fSTANBY=1;//

if(fU_24)vU_vent_kz=cU_vent_kz_24;
else {vU_vent_kz=cU_vent_kz;
			vU_vent_obr=cU_vent_kz;}

if(fU_24)vU_knd_kz=cU_knd_kz_24;
else {vU_knd_kz=cU_knd_kz;
			vU_knd_obr=cU_knd_kz;}

if(fU_24)v_isp_razg=cRAZG_isp_24;
else v_isp_razg=cRAZG_isp;

if(fU_24)v_knd_razg=cRAZG_knd_24;
else v_knd_razg=cRAZG_knd;

if(fSTANBY)
	{
	if(fU_24)vU_knd_kz=cU_knd_kz_st_24;
	else {vU_knd_kz=cU_knd_kz_st;
			vU_knd_obr=cU_knd_kz_st;}
	
	if(fU_24)vU_vent_kz=cU_vent_kz_st_24;
	else {vU_vent_kz=cU_vent_kz_st;
			vU_vent_obr=cU_vent_kz_st;}
	}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

if(U_nap>80)
	{
	TSTL=1;

	if(!(fConfig_t&0x1))
		{
		obr_V_isp1=0;blk_V_isp1=0;zmk_V_isp1=0;
		goto no_isp1;
		}


	if(uV_isp1) //��������� 1 ����������� ���������� 
		{
		if(!suV_isp1)
			{
			tRAZG_isp1=0;obr_V_isp1=0;blk_V_isp1=0;zmk_V_isp1=0;
			t_avr_isp1_o=0;t_avr_isp1=0;
			tOST_isp1=150;

			for(iu=0;iu<50;iu++)
				{
				buf_Upr_kz[iu]=0;
				}

			suV_isp1=uV_isp1;

			}// end  (!suV_isp1)

			if(zmk_V_isp1||blk_V_isp1)
					{
					if(FCL1s&&(tAVR_isp1<12))tAVR_isp1++;					
					if(tAVR_isp1>10)
						{
						tAVR_isp1=0;
				  		zmk_V_isp1=0;
						blk_V_isp1=0;
						}
					anV_isp1=0;
					trV_isp1=0; kV_isp1=0;
					obr_V_isp1=0;
					}

			if((!zmk_V_isp1)&&(!blk_V_isp1))
				{
				if(tRAZG_isp1<=30)tRAZG_isp1++;

			if(tRAZG_isp1<v_isp_razg)
				{
				if(tRAZG_isp1 < 10)
					{
					anV_isp1=0;

					TSTL=0;
					anV_isp1=0;
					kV_isp1=0;trV_isp1=0;	
					Delay10KTCYx(2);


					trV_isp1=1;Nop();Nop();
					anV_isp1=1;
					Delay10KTCYx(1);
					//U_CL_isp1  ����������
					op_bp=U_V_isp1;
					tst_AN_X_h();//

					U_CL_isp1=ADRESH;
					buf_Upr_rot[tRAZG_isp1]=U_CL_isp1;

/////////////
					tst_pr_stanby();

					kV_isp1=1;trV_isp1=0;kV_isp1=1;
					Delay100TCYx(10);

					trV_isp1=1;
					anV_isp1=1;

					for(iu=0;iu<40;iu++)
						{
						Delay100TCYx(20);
						//U_CL_isp1  ����������
						op_bp=U_V_isp1;
						tst_AN_X_h();//
						sU_CL_isp1=ADRESH;
						buf_Upr_start_i1[iu]=sU_CL_isp1;

						if(iu==0)
							{
							buf_Upr_kz[tRAZG_isp1]=sU_CL_isp1;
							U_CL_isp1=sU_CL_isp1; 
							}
						}
					Sum_U_rot=0;
					for(iu=30;iu<40;iu++)
						{
						Sum_U_rot+=buf_Upr_start_i1[iu];
						}

						Oper_int=vU_vent_kz;

					if(Sum_U_rot>Oper_int) //����� ��������
						{
						kV_isp1=1;trV_isp1=0;kV_isp1=1;
						}
					else //����� �� ��������
						{
						Sum_U_rot=0;
						for(iu=0;iu<30;iu++)
							{
							Sum_U_rot+=buf_Upr_start_i1[iu];
							}
						if(Sum_U_rot>4500) //��� ���������
							{
							kV_isp1=1;trV_isp1=0;kV_isp1=1;
							}
						}
					}
				else  // (tRAZG_isp1 > 9)
					{
					Sum_U_rot=0;
					for(iu=30;iu<40;iu++)
						{
						Sum_U_rot+=buf_Upr_start_i1[iu];
						}
						Oper_int=vU_vent_kz;
					if(Sum_U_rot<Oper_int)  //||(U_CL_isp1<vU_vent_kz))
						{
						Sum_U_rot=0;
						for(iu=0;iu<30;iu++)
							{
							Sum_U_rot+=buf_Upr_start_i1[iu];
							}
						if(Sum_U_rot>4500) //��� ���������
							{
							kV_isp1=1;trV_isp1=0;kV_isp1=1;
							}
						else
							{
							zmk_V_isp1=1;
							obr_V_isp1=0;
							blk_V_isp1=0;
							anV_isp1=0;
					//		kV_isp1=0;
							}
						}
					else
						{
						kV_isp1=1;trV_isp1=0;kV_isp1=1;
						}
					}

				} //if(tRAZG_isp1<v_isp_razg)
			else 
				{//����� �������

					if(minU_CL_isp1<vU_vent_kz)
						{
						TSTL=1;
							
						op_bp=U_V_isp1;
						trV_isp1=1;Nop();Nop();
						anV_isp1=1;
						Delay10KTCYx(1);
						//U_CL_isp1  ����������
						tst_AN_X_h();//
			
						U_CL_isp1=ADRESH;
						trV_isp1=0;
						anV_isp1=0;
			 			if(U_CL_isp1>20){obr_V_isp1=1;zmk_V_isp1=0;
										t_avr_isp1=0;blk_V_isp1=0;}	
						else {blk_V_isp1=1;obr_V_isp1=0;}
						}
					else
						{
						obr_V_isp1=0;
						blk_V_isp1=0;

					tst_pr_stanby_rot();

					TSTL=0;
					anV_isp1=0;
					kV_isp1=0;trV_isp1=0;	
					Delay10KTCYx(1);

					trV_isp1=1;Nop();Nop();
					anV_isp1=1;
					Delay10KTCYx(1);
					//U_CL_isp1  ����������
					op_bp=U_V_isp1;
					tst_AN_X_h();//

					U_CL_isp1=ADRESH;

					buf_Upr_rot[tRAZG_isp1]=U_CL_isp1;

			 		if(U_CL_isp1>20){obr_V_isp1=0;zmk_V_isp1=0;
						t_avr_isp1=0;blk_V_isp1=0;}	
					else {obr_V_isp1=0;blk_V_isp1=1;}


						if(minU_CL_isp1<(vU_vent_kz+20))
							{
							tst_pr_stanby();

							kV_isp1=1;trV_isp1=0;kV_isp1=1;
							Delay100TCYx(100);
							}
						trV_isp1=1;
						}
					minU_CL_isp1 = 250;
					maxU_CL_isp1 = 0;
					}

				I_CL_isp1=15;


/*
		if((!zmk_V_isp1)&&(!blk_V_isp1)&&(!obr_V_isp1))
				if((tRAZG_isp1>v_isp_razg)&&((t_cl_1s==0)||(t_cl_1s==5)))
					{
					if(t_stb==1)
						{
						if((t_cl_1s==0)){trV_isp1=0;kV_isp1=0;}	
						}
					if(t_stb==2)
						{
						if((t_cl_1s==0)||(t_cl_1s==5))
								{trV_isp1=0;kV_isp1=0;}	
						}
					}
*/

				if(obr_V_isp1){t_avr_isp1_o++;obr_V_isp1=0;}
				if(t_avr_isp1_o>=5){obr_V_isp1=1;t_avr_isp1_o=5;}

				if((!zmk_V_isp1)&&(!blk_V_isp1)){t_avr_isp1=0;}
				if(zmk_V_isp1||blk_V_isp1){t_avr_isp1++;}
				if(t_avr_isp1>4)
					{
					t_avr_isp1=5;
					t_avr_isp1_o=0;
					anV_isp1=0;
					trV_isp1=0; kV_isp1=0;
					obr_V_isp1=0;
					}
				else {blk_V_isp1=zmk_V_isp1=0;}



				}//end !zmk_V_isp1&&!blk_V_isp1	

			Nop();
			Nop();
			}
		else 			//���������� 1 ����������� ���������� 
			{

			if(suV_isp1){suV_isp1=0;obr_V_isp1=0;tOST_isp1=150;}

			suV_isp1=uV_isp1;
			tRAZG_isp1=0;

			//��� 1 ����������� ���������� 
			I_CL_isp1=0;

			if(blk_V_isp1)
				{
				if(FCL1s)t_blk_res_isp1++;
				if(t_blk_res_isp1>5){t_blk_res_isp1=0;blk_V_isp1=0;}
				}
			if(zmk_V_isp1)
				{
				if(FCL1s)t_blk_res_isp1++;
				if(t_blk_res_isp1>5)
					{
					t_blk_res_isp1=0;
					zmk_V_isp1=0;
					}
				}
			t_avr_isp1=0;

			if(tOST_isp1){tOST_isp1--;U_CL_isp1=0;}

			anV_isp1=0;
			trV_isp1=0; kV_isp1=0;

	//		if((tOST_isp1==0)&&FCL1s)
			
			if(FCL1s)
				{
				TSTL=0;
				op_bp=U_V_isp1;
				Delay10KTCYx(1);
	
				trV_isp1=1;anV_isp1=1;
				Delay10KTCYx(2);
				//U_CL_isp1  ����������
				tst_AN_X_h();//
				U_CL_isp1=ADRESH;
	
	 			if(U_CL_isp1>5)
					{
					obr_V_isp1=0;zmk_V_isp1=0;
					blk_V_isp1=0;
					anV_isp1=0;
					trV_isp1=0;
					}	
				else 
					{
					TSTL=1;
						
					op_bp=U_V_isp1;
					trV_isp1=1;Nop();Nop();
					anV_isp1=1;
					Delay10KTCYx(1);
					//U_CL_isp1  ����������
					tst_AN_X_h();//
		
					U_CL_isp1=ADRESH;
					trV_isp1=0;
					anV_isp1=0;
		 			if(U_CL_isp1>20){obr_V_isp1=1;zmk_V_isp1=0;
									t_avr_isp1=0;blk_V_isp1=0;}	
					else obr_V_isp1=0;
	
					if(zmk_V_isp1)obr_V_isp1=0;
					}
			if(obr_V_isp1){t_avr_isp1_o++;obr_V_isp1=0;}
			else t_avr_isp1_o=0;
			if(t_avr_isp1_o>=4){obr_V_isp1=1;t_avr_isp1_o=4;}
				}

			TSTL=1;
			}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  _12

no_isp1:

	if(!(fConfig_t&0x2))
		{
		obr_V_isp2=0;blk_V_isp2=0;zmk_V_isp2=0;
		goto no_isp2;
		}

	if(uV_isp2) //��������� 1 ����������� ���������� 
		{
		if(!suV_isp2)
			{
			tRAZG_isp2=0;obr_V_isp2=0;blk_V_isp2=0;zmk_V_isp2=0;
			t_avr_isp2_o=0;t_avr_isp2=0;
			tOST_isp2=150;

			for(iu=0;iu<50;iu++)
				{
				buf_Upr_kz[iu]=0;
				}

			suV_isp2=uV_isp2;

			}// end  (!suV_isp2)

			if(zmk_V_isp2||blk_V_isp2)
					{
					if(FCL1s&&(tAVR_isp2<12))tAVR_isp2++;					
					if(tAVR_isp2>10)
						{
						tAVR_isp2=0;
				  		zmk_V_isp2=0;
						blk_V_isp2=0;
						}
					anV_isp2=0;
					trV_isp2=0; kV_isp2=0;
					obr_V_isp2=0;
					}

			if((!zmk_V_isp2)&&(!blk_V_isp2))
				{
				if(tRAZG_isp2<=30)tRAZG_isp2++;

			if(tRAZG_isp2<v_isp_razg)
				{
				if(tRAZG_isp2 < 10)
					{
					anV_isp2=0;

					TSTL=0;
					anV_isp2=0;
					kV_isp2=0;trV_isp2=0;	
					Delay10KTCYx(2);


					trV_isp2=1;Nop();Nop();
					anV_isp2=1;
					Delay10KTCYx(1);
					//U_CL_isp2  ����������
					op_bp=U_V_isp2;
					tst_AN_X_h();//

					U_CL_isp2=ADRESH;
					buf_Upr_rot[tRAZG_isp2]=U_CL_isp2;

/////////////
					tst_pr_stanby();

					kV_isp2=1;trV_isp2=0;kV_isp2=1;
					Delay100TCYx(10);

					trV_isp2=1;
					anV_isp2=1;

					for(iu=0;iu<40;iu++)
						{
						Delay100TCYx(20);
						//U_CL_isp2  ����������
						op_bp=U_V_isp2;
						tst_AN_X_h();//
						sU_CL_isp2=ADRESH;
						buf_Upr_start_i2[iu]=sU_CL_isp2;

						if(iu==0)
							{
							buf_Upr_kz[tRAZG_isp2]=sU_CL_isp2;
							U_CL_isp2=sU_CL_isp2; 
							}
						}
					Sum_U_rot=0;
					for(iu=30;iu<40;iu++)
						{
						Sum_U_rot+=buf_Upr_start_i2[iu];
						}

						Oper_int=vU_vent_kz;

					if(Sum_U_rot>Oper_int)  //||(U_CL_isp2<vU_vent_kz))
						{
						kV_isp2=1;trV_isp2=0;kV_isp2=1;
						}
					else //����� �� ��������
						{
						Sum_U_rot=0;
						for(iu=0;iu<30;iu++)
							{
							Sum_U_rot+=buf_Upr_start_i2[iu];
							}
						if(Sum_U_rot>4500) //��� ���������
							{
							kV_isp2=1;trV_isp2=0;kV_isp2=1;
							}
						}

					}
				else  // (tRAZG_isp2 > 9)
					{
					Sum_U_rot=0;
					for(iu=30;iu<40;iu++)
						{
						Sum_U_rot+=buf_Upr_start_i2[iu];
						}
						Oper_int=vU_vent_kz;
					if(Sum_U_rot<Oper_int)  //||(U_CL_isp2<vU_vent_kz))
						{
						Sum_U_rot=0;
						for(iu=0;iu<30;iu++)
							{
							Sum_U_rot+=buf_Upr_start_i2[iu];
							}
						if(Sum_U_rot>4500) //��� ���������
							{
							kV_isp2=1;trV_isp2=0;kV_isp2=1;
							}
						else
							{
							zmk_V_isp2=1;
							obr_V_isp2=0;
							blk_V_isp2=0;
							anV_isp2=0;
					//		kV_isp2=0;
							}
						}
					else
						{
						kV_isp2=1;trV_isp2=0;kV_isp2=1;
						}
					}

				} //if(tRAZG_isp2<v_isp_razg)
			else 
				{//����� �������

					if(minU_CL_isp2<vU_vent_kz)
						{
						TSTL=1;
							
						op_bp=U_V_isp2;
						trV_isp2=1;Nop();Nop();
						anV_isp2=1;
						Delay10KTCYx(1);
						//U_CL_isp2  ����������
						tst_AN_X_h();//
			
						U_CL_isp2=ADRESH;
						trV_isp2=0;
						anV_isp2=0;
			 			if(U_CL_isp2>20){obr_V_isp2=1;zmk_V_isp2=0;
										t_avr_isp2=0;blk_V_isp2=0;}	
						else {blk_V_isp2=1;obr_V_isp2=0;}
						}
					else
						{
						obr_V_isp2=0;
						blk_V_isp2=0;

					tst_pr_stanby_rot();

					TSTL=0;
					anV_isp2=0;
					kV_isp2=0;trV_isp2=0;	
					Delay10KTCYx(1);

					trV_isp2=1;Nop();Nop();
					anV_isp2=1;
					Delay10KTCYx(1);
					//U_CL_isp2  ����������
					op_bp=U_V_isp2;
					tst_AN_X_h();//

					U_CL_isp2=ADRESH;

					buf_Upr_rot[tRAZG_isp2]=U_CL_isp2;

			 		if(U_CL_isp2>20){obr_V_isp2=0;zmk_V_isp2=0;
						t_avr_isp2=0;blk_V_isp2=0;}	
					else {obr_V_isp2=0;blk_V_isp2=1;}	


						if(minU_CL_isp2<(vU_vent_kz+20))
							{
							tst_pr_stanby();

							kV_isp2=1;trV_isp2=0;kV_isp2=1;
							Delay100TCYx(100);
							}
						trV_isp2=1;
						}
					minU_CL_isp2 = 250;
					maxU_CL_isp2 = 0;
					}

				I_CL_isp2=15;


/*
		if((!zmk_V_isp2)&&(!blk_V_isp2)&&(!obr_V_isp2))
				if((tRAZG_isp2>v_isp_razg)&&((t_cl_1s==1)||(t_cl_1s==6)))
					{
					if(t_stb==1)
						{
						if((t_cl_1s==1)){trV_isp2=0;kV_isp2=0;}	
						}
					if(t_stb==2)
						{
						if((t_cl_1s==1)||(t_cl_1s==6))
								{trV_isp2=0;kV_isp2=0;}	
						}
					}
*/

				if(obr_V_isp2){t_avr_isp2_o++;obr_V_isp2=0;}
				if(t_avr_isp2_o>=5){obr_V_isp2=1;t_avr_isp2_o=5;}

				if((!zmk_V_isp2)&&(!blk_V_isp2)){t_avr_isp2=0;}
				if(zmk_V_isp2||blk_V_isp2){t_avr_isp2++;}
				if(t_avr_isp2>4)
					{
					t_avr_isp2=5;
					t_avr_isp2_o=0;
					anV_isp2=0;
					trV_isp2=0; kV_isp2=0;
					obr_V_isp2=0;
					}
				else {blk_V_isp2=zmk_V_isp2=0;}



				}//end !zmk_V_isp2&&!blk_V_isp2	

			Nop();
			Nop();
			}
		else 			//���������� 1 ����������� ���������� 
			{

			if(suV_isp2){suV_isp2=0;obr_V_isp2=0;tOST_isp2=150;}

			suV_isp2=uV_isp2;
			tRAZG_isp2=0;

			//��� 1 ����������� ���������� 
			I_CL_isp2=0;

			if(blk_V_isp2)
				{
				if(FCL1s)t_blk_res_isp2++;
				if(t_blk_res_isp2>5){t_blk_res_isp2=0;blk_V_isp2=0;}
				}
			if(zmk_V_isp2)
				{
				if(FCL1s)t_blk_res_isp2++;
				if(t_blk_res_isp2>5)
					{
					t_blk_res_isp2=0;
					zmk_V_isp2=0;
					}
				}
			t_avr_isp2=0;

			if(tOST_isp2){tOST_isp2--;U_CL_isp2=0;}

			anV_isp2=0;
			trV_isp2=0; kV_isp2=0;

	//		if((tOST_isp2==0)&&FCL1s)
			
			if(FCL1s)
				{
				TSTL=0;
				op_bp=U_V_isp2;
				Delay10KTCYx(1);
	
				trV_isp2=1;anV_isp2=1;
				Delay10KTCYx(2);
				//U_CL_isp2  ����������
				tst_AN_X_h();//
				U_CL_isp2=ADRESH;
	
	 			if(U_CL_isp2>5)
					{
					obr_V_isp2=0;zmk_V_isp2=0;
					blk_V_isp2=0;
					anV_isp2=0;
					trV_isp2=0;
					}	
				else 
					{
					TSTL=1;
						
					op_bp=U_V_isp2;
					trV_isp2=1;Nop();Nop();
					anV_isp2=1;
					Delay10KTCYx(1);
					//U_CL_isp2  ����������
					tst_AN_X_h();//
		
					U_CL_isp2=ADRESH;
					trV_isp2=0;
					anV_isp2=0;
		 			if(U_CL_isp2>20){obr_V_isp2=1;zmk_V_isp2=0;
									t_avr_isp2=0;blk_V_isp2=0;}	
					else obr_V_isp2=0;
	
					if(zmk_V_isp2)obr_V_isp2=0;
					}
			if(obr_V_isp2){t_avr_isp2_o++;obr_V_isp2=0;}
			else t_avr_isp2_o=0;
			if(t_avr_isp2_o>=4){obr_V_isp2=1;t_avr_isp2_o=4;}
				}

			TSTL=1;
			}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  _12

no_isp2:

	if(!(fConfig_t&0x4))
		{
		obr_V_knd1=0;blk_V_knd1=0;zmk_V_knd1=0;
		goto no_knd1;
		}

	if(uV_knd1) //��������� 1 ����������  
		{
		if(!suV_knd1)
			{
			tRAZG_knd1=0;obr_V_knd1=0;blk_V_knd1=0;zmk_V_knd1=0;
			t_avr_knd1_o=0;t_avr_knd1=0;
			tOST_knd1=150;

			for(iu=0;iu<50;iu++)
				{
				buf_Upr_kz[iu]=0;
				}

			suV_knd1=uV_knd1;

			}// end  (!suV_knd1)

			if(zmk_V_knd1||blk_V_knd1)
					{
					if(FCL1s&&(tAVR_knd1<12))tAVR_knd1++;					
					if(tAVR_knd1>10)
						{
						tAVR_knd1=0;
				  		zmk_V_knd1=0;
						blk_V_knd1=0;
						}
					anV_knd1=0;
					trV_knd1=0; kV_knd1=0;
					obr_V_knd1=0;
					}

			if((!zmk_V_knd1)&&(!blk_V_knd1))
				{
				if(tRAZG_knd1<=30)tRAZG_knd1++;

			if(tRAZG_knd1<v_knd_razg)
				{
				if(tRAZG_knd1 < 7)
					{
					anV_knd1=0;

					TSTL=0;
					anV_knd1=0;
					kV_knd1=0;trV_knd1=0;	
					Delay10KTCYx(2);


					trV_knd1=1;Nop();Nop();
					anV_knd1=1;
					Delay10KTCYx(1);
					//U_CL_knd1  ����������
					op_bp=U_V_knd1;
					tst_AN_X_h();//

					U_CL_knd1=ADRESH;
					buf_Upr_rot[tRAZG_knd1]=U_CL_knd1;

/////////////
					tst_pr_stanby();

					kV_knd1=1;trV_knd1=0;kV_knd1=1;
					Delay100TCYx(10);

					trV_knd1=1;
					anV_knd1=1;

					for(iu=0;iu<40;iu++)
						{
						Delay100TCYx(20);
						//U_CL_knd1  ����������
						op_bp=U_V_knd1;
						tst_AN_X_h();//
						sU_CL_knd1=ADRESH;
						buf_Upr_start_k1[iu]=sU_CL_knd1;

						if(iu==0)
							{
							buf_Upr_kz[tRAZG_knd1]=sU_CL_knd1;
							U_CL_knd1=sU_CL_knd1; 
							}
						}
					Sum_U_rot=0;
					for(iu=30;iu<40;iu++)
						{
						Sum_U_rot+=buf_Upr_start_k1[iu];
						}

						Oper_int=vU_knd_kz;

					if(Sum_U_rot>Oper_int)  //����� ��������
						{
						kV_knd1=1;trV_knd1=0;kV_knd1=1;
						}
					else //����� �� ��������
						{
						Sum_U_rot=0;
						for(iu=0;iu<30;iu++)
							{
							Sum_U_rot+=buf_Upr_start_k1[iu];
							}
						if(Sum_U_rot>4500) //��� ���������
							{
							kV_knd1=1;trV_knd1=0;kV_knd1=1;
							}
						}

					}
				else  // (tRAZG_knd1 > 6)
					{
					Sum_U_rot=0;
					for(iu=30;iu<40;iu++)
						{
						Sum_U_rot+=buf_Upr_start_k1[iu];
						}
						Oper_int=vU_knd_kz;
					if(Sum_U_rot<Oper_int) //����� �� ��������
						{
						Sum_U_rot=0;
						for(iu=0;iu<30;iu++)
							{
							Sum_U_rot+=buf_Upr_start_k1[iu];
							}
						if(Sum_U_rot>4500) //��� ���������
							{
							kV_knd1=1;trV_knd1=0;kV_knd1=1;
							}
						else
							{
							zmk_V_knd1=1;
							obr_V_knd1=0;
							blk_V_knd1=0;
							anV_knd1=0;
			//				kV_knd1=0;
							}
						}
					else
						{
						kV_knd1=1;trV_knd1=0;kV_knd1=1;
						}
					  }

					} //if(tRAZG_knd1<v_knd_razg)
				else 
					{//����� �������

					if(minU_CL_knd1<vU_knd_kz)
						{
						TSTL=1;
							
						op_bp=U_V_knd1;
						trV_knd1=1;Nop();Nop();
						anV_knd1=1;
						Delay10KTCYx(1);
						//U_CL_knd1  ����������
						tst_AN_X_h();//
			
						U_CL_knd1=ADRESH;
						trV_knd1=0;
						anV_knd1=0;
			 			if(U_CL_knd1>20){obr_V_knd1=1;zmk_V_knd1=0;
										t_avr_knd1=0;blk_V_knd1=0;}	
						else {blk_V_knd1=1;obr_V_knd1=0;}
						}
					else
						{
						obr_V_knd1=0;
						blk_V_knd1=0;

					tst_pr_stanby_rot();

					TSTL=0;
					anV_knd1=0;
					kV_knd1=0;trV_knd1=0;	
					Delay10KTCYx(1);

					trV_knd1=1;Nop();Nop();
					anV_knd1=1;
					Delay10KTCYx(1);
					//U_CL_knd1  ����������
					op_bp=U_V_knd1;
					tst_AN_X_h();//

					U_CL_knd1=ADRESH;

					buf_Upr_rot[tRAZG_knd1]=U_CL_knd1;

			 		if(U_CL_knd1>20){obr_V_knd1=0;zmk_V_knd1=0;
						t_avr_knd1=0;blk_V_knd1=0;}	
					else  {blk_V_knd1=1;obr_V_knd1=0;}


						if(minU_CL_knd1<(vU_knd_kz+20))
							{
							tst_pr_stanby();

							kV_knd1=1;trV_knd1=0;kV_knd1=1;
							Delay100TCYx(100);
							}
						trV_knd1=1;
						}
					minU_CL_knd1 = 250;
					maxU_CL_knd1 = 0;

					}

				I_CL_knd1=15;


/*
		if((!zmk_V_knd1)&&(!blk_V_knd1)&&(!obr_V_knd1))
				if((tRAZG_knd1>v_knd_razg)&&((t_cl_1s==2)||(t_cl_1s==7)))
					{
					if(t_stb==1)
						{
						if((t_cl_1s==2)){trV_knd1=0;kV_knd1=0;}	
						}
					if(t_stb==2)
						{
						if((t_cl_1s==2)||(t_cl_1s==7))
								{trV_knd1=0;kV_knd1=0;}	
						}
					}
*/
				if(obr_V_knd1){t_avr_knd1_o++;obr_V_knd1=0;}
				else t_avr_knd1_o=0;

				if(t_avr_knd1_o>=5){obr_V_knd1=1;t_avr_knd1_o=5;}

				if((!zmk_V_knd1)&&(!blk_V_knd1)){t_avr_knd1=0;}
				if(zmk_V_knd1||blk_V_knd1){t_avr_knd1++;}
				if(t_avr_knd1>4)
					{
					t_avr_knd1=5;
					t_avr_knd1_o=0;
					anV_knd1=0;
					trV_knd1=0; kV_knd1=0;
					obr_V_knd1=0;
					}
				else {blk_V_knd1=zmk_V_knd1=0;}

				}//end !zmk_V_knd1&&!blk_V_knd1	

			Nop();
			Nop();
			}
		else 			//���������� 1 �����������  
			{

			if(suV_knd1){suV_knd1=0;obr_V_knd1=0;tOST_knd1=150;}

			suV_knd1=uV_knd1;
			tRAZG_knd1=0;

			//��� 1 ����������� ���������� 
			I_CL_knd1=0;

			if(blk_V_knd1)
				{
				if(FCL1s)t_blk_res_knd1++;
				if(t_blk_res_knd1>5){t_blk_res_knd1=0;blk_V_knd1=0;}
				}
			if(zmk_V_knd1)
				{
				if(FCL1s)t_blk_res_knd1++;
				if(t_blk_res_knd1>5)
					{
					t_blk_res_knd1=0;
					zmk_V_knd1=0;
					}
				}
			t_avr_knd1=0;

			if(tOST_knd1){tOST_knd1--;U_CL_knd1=0;}

			anV_knd1=0;
			trV_knd1=0; kV_knd1=0;

			
//			if(FCL1s)
			if((tOST_knd1==0)&&FCL1s)
				{
				TSTL=0;
				op_bp=U_V_knd1;
				Delay10KTCYx(1);
	
				trV_knd1=1;anV_knd1=1;
				Delay10KTCYx(2);
				//U_CL_knd1  ����������
				tst_AN_X_h();//
				U_CL_knd1=ADRESH;
	
	 			if(U_CL_knd1>5)
					{
					obr_V_knd1=0;zmk_V_knd1=0;
					blk_V_knd1=0;
					anV_knd1=0;
					trV_knd1=0;
					}	
				else 
					{
					TSTL=1;
						
					op_bp=U_V_knd1;
					trV_knd1=1;Nop();Nop();
					anV_knd1=1;
					Delay10KTCYx(1);
					//U_CL_knd1  ����������
					tst_AN_X_h();//
		
					U_CL_knd1=ADRESH;
					trV_knd1=0;
					anV_knd1=0;
		 			if(U_CL_knd1>20){obr_V_knd1=1;zmk_V_knd1=0;
									t_avr_knd1=0;blk_V_knd1=0;}	
					else obr_V_knd1=0;
	
					if(zmk_V_knd1)obr_V_knd1=0;
					}
				if(obr_V_knd1){t_avr_knd1_o++;obr_V_knd1=0;}
				else t_avr_knd1_o=0;
	
				if(t_avr_knd1_o>=4){obr_V_knd1=1;t_avr_knd1_o=4;}
				}

			TSTL=1;
			}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  _12

no_knd1:

	if(!(fConfig_t&0x8))
		{
		obr_V_knd2=0;blk_V_knd2=0;zmk_V_knd2=0;
		goto no_knd2;
		}

	if(uV_knd2) //��������� 2 ����������  
		{
		if(!suV_knd2)
			{
			tRAZG_knd2=0;obr_V_knd2=0;blk_V_knd2=0;zmk_V_knd2=0;
			t_avr_knd2_o=0;t_avr_knd2=0;
			tOST_knd2=150;

			for(iu=0;iu<50;iu++)
				{
				buf_Upr_kz[iu]=0;
				}

			suV_knd2=uV_knd2;

			}// end  (!suV_knd2)

			if(zmk_V_knd2||blk_V_knd2)
					{
					if(FCL1s&&(tAVR_knd2<12))tAVR_knd2++;					
					if(tAVR_knd2>10)
						{
						tAVR_knd2=0;
				  		zmk_V_knd2=0;
						blk_V_knd2=0;
						}
					anV_knd2=0;
					trV_knd2=0; kV_knd2=0;
					obr_V_knd2=0;
					}

			if((!zmk_V_knd2)&&(!blk_V_knd2))
				{
				if(tRAZG_knd2<=30)tRAZG_knd2++;

				if(tRAZG_knd2<v_knd_razg)
					{
				if(tRAZG_knd2 < 7)
					{
					anV_knd2=0;

					TSTL=0;
					anV_knd2=0;
					kV_knd2=0;trV_knd2=0;	
					Delay10KTCYx(2);


					trV_knd2=1;Nop();Nop();
					anV_knd2=1;
					Delay10KTCYx(1);
					//U_CL_knd2  ����������
					op_bp=U_V_knd2;
					tst_AN_X_h();//

					U_CL_knd2=ADRESH;
					buf_Upr_rot[tRAZG_knd2]=U_CL_knd2;

/////////////
					tst_pr_stanby();

					kV_knd2=1;trV_knd2=0;kV_knd2=1;
					Delay100TCYx(10);

					trV_knd2=1;
					anV_knd2=1;

					for(iu=0;iu<40;iu++)
						{
						Delay100TCYx(20);
						//U_CL_knd1  
						op_bp=U_V_knd2;
						tst_AN_X_h();//
						sU_CL_knd2=ADRESH;
						buf_Upr_start_k2[iu]=sU_CL_knd2;

						if(iu==0)
							{
							buf_Upr_kz[tRAZG_knd2]=sU_CL_knd2;
							U_CL_knd2=sU_CL_knd2; 
							}
						}
					Sum_U_rot=0;
					for(iu=30;iu<40;iu++)
						{
						Sum_U_rot+=buf_Upr_start_k2[iu];
						}

						Oper_int=vU_knd_kz;

					if(Sum_U_rot>Oper_int)  //����� ��������
						{
						kV_knd2=1;trV_knd2=0;kV_knd2=1;
						}
					else //����� �� ��������
						{
						Sum_U_rot=0;
						for(iu=0;iu<30;iu++)
							{
							Sum_U_rot+=buf_Upr_start_k2[iu];
							}
						if(Sum_U_rot>4500) //��� ���������
							{
							kV_knd2=1;trV_knd2=0;kV_knd2=1;
							}
						}

					}
				else  // (tRAZG_knd2 > 6)
					{
					Sum_U_rot=0;
					for(iu=30;iu<40;iu++)
						{
						Sum_U_rot+=buf_Upr_start_k2[iu];
						}
						Oper_int=vU_knd_kz;
					if(Sum_U_rot<Oper_int) //����� �� ��������
						{
						Sum_U_rot=0;
						for(iu=0;iu<30;iu++)
							{
							Sum_U_rot+=buf_Upr_start_k2[iu];
							}
						if(Sum_U_rot>4500) //��� ���������
							{
							kV_knd2=1;trV_knd2=0;kV_knd2=1;
							}
						else
							{
							zmk_V_knd2=1;
							obr_V_knd2=0;
							blk_V_knd2=0;
							anV_knd2=0;
				//			kV_knd2=0;
							}
						}
					else
						{
						kV_knd2=1;trV_knd2=0;kV_knd2=1;
						}
					  }

					} //if(tRAZG_knd2<v_knd_razg)
				else 
					{//����� �������

					if(minU_CL_knd2<vU_knd_kz)
						{
						TSTL=1;
							
						op_bp=U_V_knd2;
						trV_knd2=1;Nop();Nop();
						anV_knd2=1;
						Delay10KTCYx(1);
						//U_CL_knd2  ����������
						tst_AN_X_h();//
			
						U_CL_knd2=ADRESH;
						trV_knd2=0;
						anV_knd2=0;
			 			if(U_CL_knd2>20){obr_V_knd2=1;zmk_V_knd2=0;
										t_avr_knd2=0;blk_V_knd2=0;}	
						else {blk_V_knd2=1;obr_V_knd2=0;}
						}
					else
						{
						obr_V_knd2=0;
						blk_V_knd2=0;

					tst_pr_stanby_rot();

					TSTL=0;
					anV_knd2=0;
					kV_knd2=0;trV_knd2=0;	
					Delay10KTCYx(1);

					trV_knd2=1;Nop();Nop();
					anV_knd2=1;
					Delay10KTCYx(1);
					//U_CL_knd2  
					op_bp=U_V_knd2;
					tst_AN_X_h();//

					U_CL_knd2=ADRESH;

					buf_Upr_rot[tRAZG_knd2]=U_CL_knd2;

			 		if(U_CL_knd2>20){obr_V_knd2=0;zmk_V_knd2=0;
						t_avr_knd2=0;blk_V_knd2=0;}	
					else {obr_V_knd2=0;blk_V_knd2=1;}

						if(minU_CL_knd2<(vU_knd_kz+20))
							{
							tst_pr_stanby();

							kV_knd2=1;trV_knd2=0;kV_knd2=1;
							Delay100TCYx(100);
							}
						trV_knd2=1;
						}
					minU_CL_knd2 = 250;
					maxU_CL_knd2 = 0;
					}

				I_CL_knd2=15;


/*
		if((!zmk_V_knd2)&&(!blk_V_knd2)&&(!obr_V_knd2))
				if((tRAZG_knd2>v_knd_razg)&&((t_cl_1s==3)||(t_cl_1s==8)))
					{
					if(t_stb==1)
						{
						if((t_cl_1s==3)){trV_knd2=0;kV_knd2=0;}	
						}
					if(t_stb==2)
						{
						if((t_cl_1s==3)||(t_cl_1s==8))
								{trV_knd2=0;kV_knd2=0;}	
						}
					}
*/
				if(obr_V_knd2){t_avr_knd2_o++;obr_V_knd2=0;}
				else t_avr_knd2_o=0;

				if(t_avr_knd2_o>=5){obr_V_knd2=1;t_avr_knd2_o=5;}

				if((!zmk_V_knd2)&&(!blk_V_knd2)){t_avr_knd2=0;}
				if(zmk_V_knd2||blk_V_knd2){t_avr_knd2++;}
				if(t_avr_knd2>4)
					{
					t_avr_knd2=5;
					t_avr_knd2_o=0;
					anV_knd2=0;
					trV_knd2=0; kV_knd2=0;
					obr_V_knd2=0;
					}
				else {blk_V_knd2=zmk_V_knd2=0;}

				}//end !zmk_V_knd2&&!blk_V_knd2	

			Nop();
			Nop();
			}
		else 			//���������� 2 �����������  
			{

			if(suV_knd2){suV_knd2=0;obr_V_knd2=0;tOST_knd2=150;}

			suV_knd2=uV_knd2;
			tRAZG_knd2=0;

			//��� 2 ����������� ���������� 
			I_CL_knd2=0;

			if(blk_V_knd2)
				{
				if(FCL1s)t_blk_res_knd2++;
				if(t_blk_res_knd2>5){t_blk_res_knd2=0;blk_V_knd2=0;}
				}
			if(zmk_V_knd2)
				{
				if(FCL1s)t_blk_res_knd2++;
				if(t_blk_res_knd2>5)
					{
					t_blk_res_knd2=0;
					zmk_V_knd2=0;
					}
				}
			t_avr_knd2=0;

			if(tOST_knd2){tOST_knd2--;U_CL_knd2=0;}

			anV_knd2=0;
			trV_knd2=0; kV_knd2=0;

			
	//		if(FCL1s)
			if((tOST_knd2==0)&&FCL1s)
				{
				TSTL=0;
				op_bp=U_V_knd2;
				Delay10KTCYx(1);
	
				trV_knd2=1;anV_knd2=1;
				Delay10KTCYx(2);
				//U_CL_knd2  ����������
				tst_AN_X_h();//
				U_CL_knd2=ADRESH;
	
	 			if(U_CL_knd2>5)
					{
					obr_V_knd2=0;zmk_V_knd2=0;
					blk_V_knd2=0;
					anV_knd2=0;
					trV_knd2=0;
					}	
				else 
					{
					TSTL=1;
						
					op_bp=U_V_knd2;
					trV_knd2=1;Nop();Nop();
					anV_knd2=1;
					Delay10KTCYx(1);
					//U_CL_knd2 ����������
					tst_AN_X_h();//
		
					U_CL_knd2=ADRESH;
					trV_knd2=0;
					anV_knd2=0;
		 			if(U_CL_knd2>20){obr_V_knd2=1;zmk_V_knd2=0;
									t_avr_knd2=0;blk_V_knd2=0;}	
					else obr_V_knd2=0;
	
					if(zmk_V_knd2)obr_V_knd2=0;
					}
				if(obr_V_knd2){t_avr_knd2_o++;obr_V_knd2=0;}
				else t_avr_knd2_o=0;
	
				if(t_avr_knd2_o>=4){obr_V_knd2=1;t_avr_knd2_o=4;}

				}

			}

no_knd2:
	TSTL=0;
	}
	else
		{
		trV_knd1=0; kV_knd1=0;
		trV_knd2=0; kV_knd2=0;
		trV_isp1=0; kV_isp1=0;
		trV_isp2=0; kV_isp2=0;	
	
		obr_V_knd1=0;zmk_V_knd1=0;blk_V_knd1=0;	
		obr_V_knd2=0;zmk_V_knd2=0;blk_V_knd2=0;	
		obr_V_isp1=0;zmk_V_isp1=0;blk_V_isp1=0;
		obr_V_isp2=0;zmk_V_isp2=0;blk_V_isp2=0;

		SOST_UPR1=SOST_UPR3=0;
		SOST_UPR2&=0xfc;
		t_avr_isp1=t_avr_isp2=t_avr_knd1=t_avr_knd2=0;
		t_avr_isp1_o=t_avr_isp2_o=t_avr_knd1_o=t_avr_knd2_o=0;
		tRAZG_isp1=tRAZG_isp2=tRAZG_knd1=tRAZG_knd2=0;

		}


	if(t_stanby < 65)
		{
		SOST_UPR1=SOST_UPR3=0;
		SOST_UPR2&=0xfc;
		t_avr_isp1=t_avr_isp2=t_avr_knd1=t_avr_knd2=0;
		t_avr_isp1_o=t_avr_isp2_o=t_avr_knd1_o=t_avr_knd2_o=0;
		tRAZG_isp1=tRAZG_isp2=tRAZG_knd1=tRAZG_knd2=0;
		}
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void silov_vent(void)
	{
		
//t_stb=1;

//fSTANBY=1;//

if(fU_24)vU_vent_kz=cU_vent_kz_24;
else {vU_vent_kz=cU_vent_kz;
			vU_vent_obr=cU_vent_kz-15;}

if(fU_24)vU_knd_kz=cU_knd_kz_24;
else {vU_knd_kz=cU_knd_kz;
			vU_knd_obr=cU_knd_kz-15;}

if(fU_24)v_isp_razg=cRAZG_isp_24;
else v_isp_razg=cRAZG_isp;

if(fU_24)v_knd_razg=cRAZG_knd_24;
else v_knd_razg=cRAZG_knd;

if(fSTANBY)
	{
	if(fU_24)vU_knd_kz=cU_knd_kz_st_24;
	else {vU_knd_kz=cU_knd_kz_st;
			vU_knd_obr=cU_knd_kz_st-15;}
	
	if(fU_24)vU_vent_kz=cU_vent_kz_st_24;
	else {vU_vent_kz=cU_vent_kz_st;
			vU_vent_obr=cU_vent_kz_st-15;}
	}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

if(U_nap>80)
	{
	TSTL=1;

	if(!(fConfig_t&0x1))
		{
		obr_V_isp1=0;blk_V_isp1=0;zmk_V_isp1=0;
		goto no_isp1;
		}


	if(uV_isp1) //��������� 1 ����������� ���������� 
		{
		if(!suV_isp1)
			{
			tRAZG_isp1=0;obr_V_isp1=0;blk_V_isp1=0;zmk_V_isp1=0;
			t_avr_isp1_o=0;t_avr_isp1=0;tRAZG_isp1=0;

			suV_isp1=uV_isp1;

			}// end  (!suV_isp1)

			if(zmk_V_isp1||blk_V_isp1)
					{
					if(FCL1s&&(tAVR_isp1<12))tAVR_isp1++;					
					if(tAVR_isp1>11)
						{
						tAVR_isp1=0;
						zmk_V_isp1=0;
						blk_V_isp1=0;
						}
					anV_isp1=0;
					trV_isp1=0; kV_isp1=0;
					tRAZG_isp1=0;
					obr_V_isp1=0;
					}

			if((!zmk_V_isp1)&&(!blk_V_isp1))
				{
				if(tRAZG_isp1<=100)tRAZG_isp1++;

				if(tRAZG_isp1<v_isp_razg)
					{
					anV_isp1=0;
					if(!fSTANBY)
						{
						kV_isp1=1;trV_isp1=0;kV_isp1=1;
						Delay100TCYx(100);
						trV_isp1=1;
						anV_isp1=1;
					Delay100TCYx(100);

						//U_CL_isp1  ����������
						op_bp=U_V_isp1;
						tst_AN_X_h();//
		
						U_CL_isp1=ADRESH;

						if(U_CL_isp1<vU_vent_kz)
							{
							zmk_V_isp1=1;
							obr_V_isp1=0;
							blk_V_isp1=0;
							anV_isp1=0;
							kV_isp1=0;trV_isp1=0;
							}
						}
					else // if(fSTANBY)
						{
						tst_pr_stanby();
						kV_isp1=1;trV_isp1=0;kV_isp1=1;
						Delay100TCYx(50);

						if(tRAZG_isp1<v_isp_razg/2)
							{
							trV_isp1=1;
							anV_isp1=1;
							Delay100TCYx(50);
							//U_CL_isp1  ����������
							op_bp=U_V_isp1;
							tst_AN_X_h();//
			
							U_CL_isp1=ADRESH;
	
							if(U_CL_isp1<vU_vent_kz)
								{
								zmk_V_isp1=1;
								obr_V_isp1=0;
								blk_V_isp1=0;
								anV_isp1=0;
								kV_isp1=0;trV_isp1=0;
								}
							else
								{
							  	kV_isp1=1;trV_isp1=0;kV_isp1=1;
								}
							}
						else
							{
						  	kV_isp1=1;trV_isp1=0;kV_isp1=1;
							}

						}// if(fSTANBY)
					} //if(tRAZG_isp1<v_isp_razg)
				else 
					{
					if((!fSTANBY)||(fU_24))
						{  //����� �������
						
						trV_isp1=1;
						anV_isp1=1;
						Delay100TCYx(100);
	
						//U_CL_isp1  ����������
						op_bp=U_V_isp1;
						tst_AN_X_h();//
		
						U_CL_isp1=ADRESH;
		
						if(U_CL_isp1<vU_vent_kz)
							{
							obr_V_isp1=0;
							if(fSTANBY)tst_pr_stanby();
							
							kV_isp1=1;trV_isp1=0;kV_isp1=1;
							Delay100TCYx(100);
							trV_isp1=1;
							anV_isp1=1;
							Delay100TCYx(100);
	
							//U_CL_isp1  ����������
							op_bp=U_V_isp1;
							tst_AN_X_h();//
			
							U_CL_isp1=ADRESH;
	
							if(U_CL_isp1<vU_vent_kz)
								{
								zmk_V_isp1=1;
								tRAZG_isp1=0;
								}
							else
								{
								blk_V_isp1=1;
								}
							anV_isp1=0;
							kV_isp1=0;trV_isp1=0;
							t_avr_isp1++;
							}
						}
					else  //if ((fSTANBY)||(fU_12))
						{
					  	kV_isp1=1;trV_isp1=0;kV_isp1=1;
						}
					}

				I_CL_isp1=15;

		if((tRAZG_isp1>v_isp_razg)&&((t_cl_1s==0)||(t_cl_1s==5)))
					{
					TSTL=0;
					anV_isp1=0;
					kV_isp1=0;trV_isp1=0;	
					Delay10KTCYx(2);

					op_bp=U_V_isp1;

					trV_isp1=1;Nop();Nop();
					anV_isp1=1;
					Delay10KTCYx(1);
					//U_CL_isp1  ����������
					tst_AN_X_h();//

					U_CL_isp1=ADRESH;

					TSTL=1;

				//���� ����. ������ � ��������.

					if(U_CL_isp1>vU_vent_obr)
						{
						blk_V_isp1=0;
						obr_V_isp1=0;
						t_avr_isp1_o=0;
						anV_isp1=0;
						kV_isp1=1;trV_isp1=0;kV_isp1=1;	

						if((!fSTANBY)||(fU_24))
							{
							Delay10KTCYx(1);
							trV_isp1=1;	
							}

			if(t_stb==1)
				{
				if((t_cl_1s==0)){trV_isp1=0;kV_isp1=0;}	
				}
			if(t_stb==2)
				{
				if((t_cl_1s==0)||(t_cl_1s==5))
						{trV_isp1=0;kV_isp1=0;}	
				}


						}
					else 
						{
						Delay10KTCYx(1);
						anV_isp1=1;
						op_bp=U_V_isp1;
						//U_CL_isp1  ����������
						tst_AN_X_h();//
						U_CL_isp1=ADRESH;

						if(U_CL_isp1<vU_vent_obr)
							{
							blk_V_isp1=1;
							obr_V_isp1=0;
							t_avr_isp1=4;
							}
						else 
							{
							blk_V_isp1=0;
							obr_V_isp1=1;
							t_avr_isp1_o++;
							}
				if(!obr_V_isp1){t_avr_isp1_o=0;}//
				obr_V_isp1=0;
				if(fSTANBY)
					{
					if(t_avr_isp1_o>=10){obr_V_isp1=1;t_avr_isp1_o=10;}
					}
				else
					{
					if(t_avr_isp1_o>=2){obr_V_isp1=1;t_avr_isp1_o=2;}
					}
						}
					}


				if((!zmk_V_isp1)&&(!blk_V_isp1)){t_avr_isp1=0;}
				if((t_avr_isp1<3)&&blk_V_isp1){t_avr_isp1++;blk_V_isp1=0;}
				if((t_avr_isp1<3)&&zmk_V_isp1){t_avr_isp1++;zmk_V_isp1=0;}
				if(t_avr_isp1>=3)
					{
					tRAZG_isp1=0;t_avr_isp1_o=0;
					anV_isp1=0;
					trV_isp1=0; kV_isp1=0;
					obr_V_isp1=0;
					}

				}//end !zmk_V_isp1&&!blk_V_isp1	

			Nop();
			Nop();
			}
		else 			//���������� 1 ����������� ���������� 
			{

			if(suV_isp1){suV_isp1=0;obr_V_isp1=0;tRAZG_isp1=150;}

			suV_isp1=uV_isp1;


			//��� 1 ����������� ���������� 
			I_CL_isp1=0;

			if(blk_V_isp1)
				{
				if(FCL1s)t_blk_res_isp1++;
				if(t_blk_res_isp1>5){t_blk_res_isp1=0;blk_V_isp1=0;}
				}
			if(zmk_V_isp1)
				{
				if(FCL1s)t_blk_res_isp1++;
				if(t_blk_res_isp1>5)
					{
					t_blk_res_isp1=0;
					zmk_V_isp1=0;
					}
				}
			t_avr_isp1=0;
			t_avr_isp1_o=0;

			if(tRAZG_isp1){tRAZG_isp1--;U_CL_isp1=0;}

			anV_isp1=0;
			trV_isp1=0; kV_isp1=0;

			if((tRAZG_isp1==0)&&FCL1s)
				{
				TSTL=0;
				op_bp=U_V_isp1;
				Delay10KTCYx(1);
	
				trV_isp1=1;anV_isp1=1;
				Delay10KTCYx(2);
				//U_CL_isp1  ����������
				tst_AN_X_h();//
				U_CL_isp1=ADRESH;
	
	 			if(U_CL_isp1>10)
					{
					obr_V_isp1=0;zmk_V_isp1=0;
					blk_V_isp1=0;
					anV_isp1=0;
					trV_isp1=0;
					}	
				else 
					{
					TSTL=1;
						
					op_bp=U_V_isp1;
					trV_isp1=1;Nop();Nop();
					anV_isp1=1;
					Delay10KTCYx(1);
					//U_CL_isp1  ����������
					tst_AN_X_h();//
		
					U_CL_isp1=ADRESH;
					trV_isp1=0;
					anV_isp1=0;
		 			if(U_CL_isp1>20){obr_V_isp1=1;zmk_V_isp1=0;blk_V_isp1=0;}	
					else obr_V_isp1=0;
	
					if(zmk_V_isp1)obr_V_isp1=0;
					}
				}

			TSTL=1;
			}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  _12

no_isp1:

	if(!(fConfig_t&0x2))
		{
		obr_V_isp2=0;blk_V_isp2=0;zmk_V_isp2=0;
		goto no_isp2;
		}

	if(uV_isp2) //��������� 2 ����������� ���������� 
		{
		if(!suV_isp2)
			{
			tRAZG_isp2=0;obr_V_isp2=0;blk_V_isp2=0;zmk_V_isp2=0;
			t_avr_isp2_o=0;t_avr_isp2=0;

			suV_isp2=uV_isp2;


			}// end  (!suV_isp2)

			if(zmk_V_isp2||blk_V_isp2)
					{
					if(FCL1s&&(tAVR_isp2<12))tAVR_isp2++;					
					if(tAVR_isp2>11)
						{
						tAVR_isp2=0;
						zmk_V_isp2=0;
						blk_V_isp2=0;
						}
					anV_isp2=0;
					trV_isp2=0; kV_isp2=0;
					tRAZG_isp2=0;
					obr_V_isp2=0;
					}

			if((!zmk_V_isp2)&&(!blk_V_isp2))
				{
				if(tRAZG_isp2<=100)tRAZG_isp2++;

				if(tRAZG_isp2<v_isp_razg)
					{
					anV_isp2=0;
					if(!fSTANBY)
						{
						kV_isp2=1;trV_isp2=0;kV_isp2=1;
						Delay100TCYx(100);
						trV_isp2=1;
						anV_isp2=1;
					Delay100TCYx(100);

						//U_CL_isp2  ����������
						op_bp=U_V_isp2;
						tst_AN_X_h();//
		
						U_CL_isp2=ADRESH;
						if(U_CL_isp2<vU_vent_kz)
							{
							zmk_V_isp2=1;
							obr_V_isp2=0;
							blk_V_isp2=0;
							anV_isp2=0;
							kV_isp2=0;trV_isp2=0;
							}
						}
					else  // if(fSTANBY)
						{
						tst_pr_stanby();
						kV_isp2=1;trV_isp2=0;kV_isp2=1;
						Delay100TCYx(50);

						if(tRAZG_isp2<v_isp_razg/2)
							{
							trV_isp2=1;
							anV_isp2=1;
							Delay100TCYx(50);
							//U_CL_isp2  ����������
							op_bp=U_V_isp2;
							tst_AN_X_h();//
			
							U_CL_isp2=ADRESH;
	
							if(U_CL_isp2<vU_vent_kz)
								{
								zmk_V_isp2=1;
								obr_V_isp2=0;
								blk_V_isp2=0;
								anV_isp2=0;
								kV_isp2=0;trV_isp2=0;
								}
							else
								{
							  kV_isp2=1;trV_isp2=0;kV_isp2=1;
								}
							}
						else
							{
						  	kV_isp2=1;trV_isp2=0;kV_isp2=1;
							}
						}// if(fSTANBY)
					}//if(tRAZG_isp2<v_isp_razg)
				else 
					{
					if((!fSTANBY)||(fU_24))
						{  //����� �������
						trV_isp2=1;anV_isp2=1;
						Delay100TCYx(100);
	
						//U_CL_isp2  ����������
						op_bp=U_V_isp2;
						tst_AN_X_h();//
		
						U_CL_isp2=ADRESH;
		
						if(U_CL_isp2<vU_vent_kz)
							{
							obr_V_isp2=0;
							if(fSTANBY)tst_pr_stanby();
							
							kV_isp2=1;trV_isp2=0;kV_isp2=1;
							Delay100TCYx(100);
							trV_isp2=1;
							anV_isp2=1;
							Delay100TCYx(100);
	
							//U_CL_isp2  ����������
							op_bp=U_V_isp2;
							tst_AN_X_h();//
			
							U_CL_isp2=ADRESH;
	
							if(U_CL_isp2<vU_vent_kz)
								{
								zmk_V_isp2=1;
								tRAZG_isp2=0;
								}
							else
								{
								blk_V_isp2=1;
								}
							anV_isp2=0;
							kV_isp2=0;trV_isp2=0;
							t_avr_isp2++;
							}
						}
					else  //if !((!fSTANBY)||(fU_24))
						{
					  	kV_isp2=1;trV_isp2=0;kV_isp2=1;
						}
					}

					I_CL_isp2=15;

		if((tRAZG_isp2>v_isp_razg)&&((t_cl_1s==1)||(t_cl_1s==6)))
					{
					TSTL=0;
					anV_isp2=0;
					kV_isp2=0;trV_isp2=0;	
					Delay10KTCYx(2);

					op_bp=U_V_isp2;

					trV_isp2=1;Nop();Nop();
					anV_isp2=1;
					Delay10KTCYx(1);
					//U_CL_isp2  ����������
					tst_AN_X_h();//

					U_CL_isp2=ADRESH;

					TSTL=1;

				//���� ����. ������ � ��������.

					if(U_CL_isp2>vU_vent_obr)
						{
						blk_V_isp2=0;
						obr_V_isp2=0;
						t_avr_isp2_o=0;
						anV_isp2=0;
						kV_isp2=1;trV_isp2=0;kV_isp2=1;	

						if((!fSTANBY)||(fU_24))
							{
							Delay10KTCYx(1);
							trV_isp2=1;	
							}
			if(t_stb==1)
				{
				if((t_cl_1s==1)){trV_isp2=0;kV_isp2=0;}	
				}
			if(t_stb==2)
				{
				if((t_cl_1s==1)||(t_cl_1s==6))
					{trV_isp2=0;kV_isp2=0;}	
				}

						}
					else 
						{
						Delay10KTCYx(1);
						anV_isp2=1;

						op_bp=U_V_isp2;
						//U_CL_isp2  ����������
						tst_AN_X_h();//
						U_CL_isp2=ADRESH;

						if(U_CL_isp2<vU_vent_obr)
							{
							blk_V_isp2=1;
							obr_V_isp2=0;
							t_avr_isp2=4;
							}
						else 
							{
							blk_V_isp2=0;
							obr_V_isp2=1;
							t_avr_isp2_o++;
							}
						if(!obr_V_isp2){t_avr_isp2_o=0;}//
						obr_V_isp2=0;
		
						if(fSTANBY)
							{
							if(t_avr_isp2_o>=10){obr_V_isp2=1;t_avr_isp2_o=10;}
							}
						else
							{
							if(t_avr_isp2_o>=2){obr_V_isp2=1;t_avr_isp2_o=2;}
							}
						}
					}


				if((!zmk_V_isp2)&&(!blk_V_isp2)){t_avr_isp2=0;}
				if((t_avr_isp2<3)&&blk_V_isp2){t_avr_isp2++;blk_V_isp2=0;}
				if((t_avr_isp2<3)&&zmk_V_isp2){t_avr_isp2++;zmk_V_isp2=0;}
				if(t_avr_isp2>=3)
					{
					tRAZG_isp2=0;t_avr_isp2_o=0;
					anV_isp2=0;
					trV_isp2=0; kV_isp2=0;
					obr_V_isp2=0;
					}
				}//end !blk_V_isp2&&!blk_V_isp2	
				Nop();
				Nop();
			}
		else 			//���������� 2 ����������� ���������� 
			{

			if(suV_isp2){suV_isp2=0;obr_V_isp2=0;tRAZG_isp2=150;}

			suV_isp2=uV_isp2;

			//��� 2 ����������� ���������� 
			I_CL_isp2=0;

			if(blk_V_isp2)
				{
				if(FCL1s)t_blk_res_isp2++;
				if(t_blk_res_isp2>5){t_blk_res_isp2=0;blk_V_isp2=0;}
				}
			if(zmk_V_isp2)
				{
				if(FCL1s)t_blk_res_isp2++;
				if(t_blk_res_isp2>5){t_blk_res_isp2=0;zmk_V_isp2=0;}
				}
			t_avr_isp2=0;
			t_avr_isp2_o=0;

			if(tRAZG_isp2){tRAZG_isp2--;U_CL_isp2=0;}

			trV_isp2=0; kV_isp2=0;

			if((tRAZG_isp2==0)&&FCL1s)
				{
				TSTL=0;
				op_bp=U_V_isp2;
				Delay10KTCYx(1);
	
				trV_isp2=1;anV_isp2=1;
				Delay10KTCYx(2);
				//U_CL_isp2  ����������
				tst_AN_X_h();//
				U_CL_isp2=ADRESH;
	
	 			if(U_CL_isp2>10)
					{
					obr_V_isp2=0;zmk_V_isp2=0;
					blk_V_isp2=0;
					anV_isp2=0;
					trV_isp2=0;
					}	
				else 
					{
					TSTL=1;
					anV_isp2=1;	
					op_bp=U_V_isp2;
					trV_isp2=1;Nop();Nop();
					Delay10KTCYx(1);
					//U_CL_isp2  ����������
					tst_AN_X_h();//
					trV_isp2=0;
					anV_isp2=0;
					U_CL_isp2=ADRESH;
		 			if(U_CL_isp2>20){obr_V_isp2=1;zmk_V_isp2=0;blk_V_isp2=0;}	
					else obr_V_isp2=0;
	
					if(zmk_V_isp2)obr_V_isp2=0;
					}
				}

			TSTL=1;
			}




//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  _12

no_isp2:

if(fH_def_12) goto no_knd2;

	if(!(fConfig_t&0x4))
		{
		obr_V_knd1=0;blk_V_knd1=0;zmk_V_knd1=0;
		goto no_knd1;
		}

	if(uV_knd1) //��������� 1 �����������  
		{
		if(!suV_knd1)
			{
			tRAZG_knd1=0;obr_V_knd1=0;blk_V_knd1=0;zmk_V_knd1=0;
			t_avr_knd1_o=0;t_avr_knd1=0;

			suV_knd1=uV_knd1;

			}// end  (!suV_knd1)

			if(zmk_V_knd1||blk_V_knd1)
					{
					if(FCL1s&&(tAVR_knd1<12))tAVR_knd1++;					
					if(tAVR_knd1>11)
						{
						tAVR_knd1=0;
						zmk_V_knd1=0;
						blk_V_knd1=0;
						}
					anV_knd1=0;
					trV_knd1=0; kV_knd1=0;
					tRAZG_knd1=0;
					obr_V_knd1=0;
					}

			if((!zmk_V_knd1)&&(!blk_V_knd1))
				{
				if(tRAZG_knd1<=100)tRAZG_knd1++;

				if(tRAZG_knd1<v_knd_razg)
					{
					anV_knd1=0;
					if(!fSTANBY)
						{
						kV_knd1=1;trV_knd1=0;kV_knd1=1;
						Delay100TCYx(100);
						trV_knd1=1;
						anV_knd1=1;
						Delay100TCYx(100);

						//U_CL_knd1  
						op_bp=U_V_knd1;
						tst_AN_X_h();//
		
						U_CL_knd1=ADRESH;
						if(U_CL_knd1<vU_knd_kz)
							{
							zmk_V_knd1=1;
							obr_V_knd1=0;
							blk_V_knd1=0;
							anV_knd1=0;
							kV_knd1=0;trV_knd1=0;
							}
						}
					else // if(fSTANBY)
						{
						tst_pr_stanby();
						kV_knd1=1;trV_knd1=0;kV_knd1=1;
						Delay100TCYx(50);

						if(tRAZG_knd1<v_knd_razg/2)
							{
							trV_knd1=1;
							anV_knd1=1;
							Delay100TCYx(50);

							//U_CL_knd1  
							op_bp=U_V_knd1;
							tst_AN_X_h();//
			
							U_CL_knd1=ADRESH;
							if(U_CL_knd1<vU_knd_kz)
								{
								zmk_V_knd1=1;
								obr_V_knd1=0;
								blk_V_knd1=0;
								anV_knd1=0;
								kV_knd1=0;trV_knd1=0;
								}
							else
								{
								kV_knd1=1;trV_knd1=0;kV_knd1=1;
								}
							}
						else
							{
							kV_knd1=1;trV_knd1=0;kV_knd1=1;
							}
						}// if(fSTANBY)
					}//if(tRAZG_knd1<v_knd_razg)
				else 
					{
					if((!fSTANBY)||(fU_24))
						{  //����� �������
						trV_knd1=1;
						anV_knd1=1;
						Delay100TCYx(100);
	
						//U_CL_knd1  
						op_bp=U_V_knd1;
						tst_AN_X_h();//
			
						U_CL_knd1=ADRESH;
			
						if(U_CL_knd1<(vU_knd_kz))
							{
							obr_V_knd1=0;
							if(fSTANBY)tst_pr_stanby();
	
							kV_knd1=1;trV_knd1=0;kV_knd1=1;
							Delay100TCYx(50);
							trV_knd1=1;
							anV_knd1=1;
							Delay100TCYx(20);
	
							//U_CL_knd1  
							op_bp=U_V_knd1;
							tst_AN_X_h();//
			
							U_CL_knd1=ADRESH;
							if(U_CL_knd1<vU_knd_kz)
								{
								zmk_V_knd1=1;
								tRAZG_knd1=0;
								}
							else
								{
								blk_V_knd1=1;
								}
							anV_knd1=0;
							kV_knd1=0;trV_knd1=0;
							t_avr_knd1++;
							}
						}
					else  //if !((!fSTANBY)||(fU_24))
						{
						kV_knd1=1;trV_knd1=0;kV_knd1=1;
						}
					}
				//��� 1 ����������� ���������� 
					I_CL_knd1=35;

		if((tRAZG_knd1>v_knd_razg)&&((t_cl_1s==2)||(t_cl_1s==7)))
					{
						TSTL=0;
						anV_knd1=0;
						kV_knd1=0;trV_knd1=0;	
						Delay10KTCYx(2);

						op_bp=U_V_knd1;
						trV_knd1=1;Nop();Nop();
						anV_knd1=1;
						Delay10KTCYx(1);
						//U_CL_knd1  ����������
						tst_AN_X_h();//
					
						U_CL_knd1=ADRESH;

						TSTL=1;

				//���� ����. ������ � ��������.

					if(U_CL_knd1>vU_knd_obr)
						{
						blk_V_knd1=0;
						obr_V_knd1=0;
						t_avr_knd1_o=0;
						anV_knd1=0;
						kV_knd1=1;trV_knd1=0;kV_knd1=1;

						if((!fSTANBY)||(fU_24))
							{
							Delay10KTCYx(1);
							trV_knd1=1;
							}
			if(t_stb==1)
				{
				if((t_cl_1s==2)){trV_knd1=0;kV_knd1=0;}	
				}
			if(t_stb==2)
				{
				if((t_cl_1s==2)||(t_cl_1s==7))
					{trV_knd1=0;kV_knd1=0;}	
				}

						}
					else 
						{
						Delay10KTCYx(1);
						anV_knd1=1;

						op_bp=U_V_knd1;
						//U_CL_knd1  
						tst_AN_X_h();//
						U_CL_knd1=ADRESH;

						if(U_CL_knd1<vU_knd_obr)
							{
							blk_V_knd1=1;
							obr_V_knd1=0;
							t_avr_knd1=4;
							}
						else 
							{
							blk_V_knd1=0;
							obr_V_knd1=1;
							t_avr_knd1_o++;
							}

						if(!obr_V_knd1){t_avr_knd1_o=0;}//
							obr_V_knd1=0;

		
						if(fSTANBY)
							{
							if(t_avr_knd1_o>=10){obr_V_knd1=1;t_avr_knd1_o=10;}
							}
						else
							{
							if(t_avr_knd1_o>=2){obr_V_knd1=1;t_avr_knd1_o=2;}
							}
						}
					}


				if((!zmk_V_knd1)&&(!blk_V_knd1)){t_avr_knd1=0;}
				if((t_avr_knd1<3)&&blk_V_knd1){t_avr_knd1++;blk_V_knd1=0;}
				if((t_avr_knd1<3)&&zmk_V_knd1){t_avr_knd1++;zmk_V_knd1=0;}
				if(t_avr_knd1>=3)
					{
					tRAZG_knd1=0;t_avr_knd1_o=0;
					anV_knd1=0;
					trV_knd1=0; kV_knd1=0;
					obr_V_knd1=0;
					}
				}//end !blk_V_knd1 && blk_V_knd1
				Nop();
				Nop();
			}	
		else 			//���������� 1 ����������� ���������� 
			{

			if(suV_knd1){suV_knd1=0;obr_V_knd1=0;tRAZG_knd1=150;}

			suV_knd1=uV_knd1;


			//��� 1 ����������� ���������� 
			I_CL_knd1=0;

			if(blk_V_knd1)
				{
				if(FCL1s)t_blk_res_knd1++;
				if(t_blk_res_knd1>5){t_blk_res_knd1=0;blk_V_knd1=0;}
				}
			if(zmk_V_knd1)
				{
				if(FCL1s)t_blk_res_knd1++;
				if(t_blk_res_knd1>5){t_blk_res_knd1=0;zmk_V_knd1=0;}
				}

			t_avr_knd1=0;
			t_avr_knd1_o=0;

			if(tRAZG_knd1){tRAZG_knd1--;U_CL_knd1=0;}

			anV_knd1=0;
			 kV_knd1=0;trV_knd1=0; kV_knd1=0;

			if((tRAZG_knd1==0)&&FCL1s)
				{
				TSTL=0;
				
				op_bp=U_V_knd1;
				Delay10KTCYx(1);
	
				trV_knd1=1;anV_knd1=1;
				Delay10KTCYx(2);
				//U_CL_knd1  
				tst_AN_X_h();//
				U_CL_knd1=ADRESH;
	
	 			if(U_CL_knd1>5)
					{
					obr_V_knd1=0;zmk_V_knd1=0;
					blk_V_knd1=0;
					anV_knd1=0;
					trV_knd1=0;
					kV_knd1=0;
					}	
				else 
					{
					TSTL=1;
						
					op_bp=U_V_knd1;
					trV_knd1=1;Nop();Nop();
					anV_knd1=1;
					Delay10KTCYx(1);
					//U_CL_knd1  
					tst_AN_X_h();//
					anV_knd1=0;
					trV_knd1=0;
					kV_knd1=0;

					U_CL_knd1=ADRESH;
		 			if(U_CL_knd1>60){obr_V_knd1=1;zmk_V_knd1=0;blk_V_knd1=0;}	
					else obr_V_knd1=0;
	
					if(zmk_V_knd1)obr_V_knd1=0;
					}
				}

			TSTL=1;
			}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  _12

no_knd1:

	if(!(fConfig_t&0x8))
		{
		obr_V_knd2=0;blk_V_knd2=0;zmk_V_knd2=0;
		goto no_knd2;
		}

	if(uV_knd2) //��������� 1 ����������� ���������� 
		{
		if(!suV_knd2)
			{tRAZG_knd2=0;obr_V_knd2=0;blk_V_knd2=0;zmk_V_knd2=0;
			t_avr_knd2_o=0;t_avr_knd2=0;tRAZG_knd2=0;

			suV_knd2=uV_knd2;

			}// end  (!suV_knd2)

			if(zmk_V_knd2||blk_V_knd2)
					{
					if(FCL1s&&(tAVR_knd2<12))tAVR_knd2++;					
					if(tAVR_knd2>11)
						{
						tAVR_knd2=0;
						zmk_V_knd2=0;
						blk_V_knd2=0;
						}
					anV_knd2=0;
					trV_knd2=0; kV_knd2=0;
					tRAZG_knd2=0;
					obr_V_knd2=0;
					}

			if((!zmk_V_knd2)&&(!blk_V_knd2))
				{
				if(tRAZG_knd2<=100)tRAZG_knd2++;

				if(tRAZG_knd2<v_knd_razg)
					{
					anV_knd2=0;
					if(!fSTANBY)
						{
						kV_knd2=1;trV_knd2=0;kV_knd2=1;
						Delay100TCYx(100);

						trV_knd2=1;
						anV_knd2=1;
						Delay100TCYx(100);

						//U_CL_knd2  
						op_bp=U_V_knd2;
						tst_AN_X_h();//
		
						U_CL_knd2=ADRESH;
						if(U_CL_knd2<vU_knd_kz)
							{
							zmk_V_knd2=1;
							obr_V_knd2=0;
							blk_V_knd2=0;
							anV_knd2=0;
							kV_knd2=0;trV_knd2=0;
							}
						}
					else // if(fSTANBY)
						{
						tst_pr_stanby();
						kV_knd2=1;trV_knd2=0;kV_knd2=1;
						Delay100TCYx(50);

						if(tRAZG_knd2<v_knd_razg/2)
							{
							trV_knd2=1;
							anV_knd2=1;
							Delay100TCYx(50);
	
							//U_CL_knd2  
							op_bp=U_V_knd2;
							tst_AN_X_h();//
			
							U_CL_knd2=ADRESH;
							if(U_CL_knd2<vU_knd_kz)
								{
								zmk_V_knd2=1;
								obr_V_knd2=0;
								blk_V_knd2=0;
								anV_knd2=0;
								kV_knd2=0;trV_knd2=0;
								}
							else
								{
								kV_knd2=1;trV_knd2=0;kV_knd2=1;
								}
							}
						else
							{
							kV_knd2=1;trV_knd2=0;kV_knd2=1;
							}
						}// if(fSTANBY)
					} //if(tRAZG_knd2<v_knd_razg)
				else 
					{
					if((!fSTANBY)||(fU_24))
						{  //����� �������
						trV_knd2=1;
						anV_knd2=1;
						Delay100TCYx(100);
	
						//U_CL_knd2  ����������
						op_bp=U_V_knd2;
						tst_AN_X_h();//
	
						U_CL_knd2=ADRESH;
			
						if(U_CL_knd2<(vU_knd_kz))
							{
							obr_V_knd2=0;
							if(fSTANBY)tst_pr_stanby();
	
							kV_knd2=1;trV_knd2=0;kV_knd2=1;
							Delay100TCYx(100);
							trV_knd2=1;
							anV_knd2=1;
							Delay100TCYx(100);
	
							//U_CL_knd1  
							op_bp=U_V_knd2;
							tst_AN_X_h();//
			
							U_CL_knd2=ADRESH;
							if(U_CL_knd2<vU_knd_kz)
								{
								zmk_V_knd2=1;
								tRAZG_knd2=0;
								}
							else
								{
								blk_V_knd2=1;
								}
							anV_knd2=0;
							kV_knd2=0;trV_knd2=0;
							t_avr_knd2++;
							}
						}
					else  //if !((!fSTANBY)||(fU_24))
						{
						kV_knd2=1;trV_knd2=0;kV_knd2=1;
						}
					}

				//��� 2 ����������� ����������  
				I_CL_knd2=35;

			if((tRAZG_knd2>v_knd_razg)&&((t_cl_1s==3)||(t_cl_1s==8)))
						{
						TSTL=0;
						anV_knd2=0;
						kV_knd2=0;trV_knd2=0;	
						Delay10KTCYx(2);

						op_bp=U_V_knd2;
						trV_knd2=1;Nop();Nop();
						anV_knd2=1;
					Delay10KTCYx(1);
						//U_CL_knd2  
						tst_AN_X_h();//
					
						U_CL_knd2=ADRESH;

						TSTL=1;

				//���� ����. ������ � ��������.

					if(U_CL_knd2>vU_knd_obr)
						{
						blk_V_knd2=0;
						obr_V_knd2=0;
						t_avr_knd2_o=0;
						anV_knd2=0;
						kV_knd2=1;trV_knd2=0;kV_knd2=1;

						if((!fSTANBY)||(fU_24))
							{
							Delay10KTCYx(1);
							trV_knd2=1;
							}
			if(t_stb==1)
				{
				if((t_cl_1s==3)){trV_knd2=0;kV_knd2=0;}	
				}
			if(t_stb==2)
				{
				if((t_cl_1s==3)||(t_cl_1s==8))
						{trV_knd2=0;kV_knd2=0;}	
				}

						}
					else 
						{
						anV_knd2=1;
						Delay10KTCYx(1);

						op_bp=U_V_knd2;
						//U_CL_knd2  
						tst_AN_X_h();//
						U_CL_knd2=ADRESH;

						if(U_CL_knd2<vU_knd_obr)
							{
							blk_V_knd2=1;
							obr_V_knd2=0;
							t_avr_knd2=4;
							}
						else 
							{
							blk_V_knd2=0;
							obr_V_knd2=1;
							t_avr_knd2_o++;
							}
						if(!obr_V_knd2){t_avr_knd2_o=0;}//
							obr_V_knd2=0;
		
						if(fSTANBY)
							{
							if(t_avr_knd2_o>=10){obr_V_knd2=1;t_avr_knd2_o=10;}
							}
						else
							{
							if(t_avr_knd2_o>=2){obr_V_knd2=1;t_avr_knd2_o=2;}
							}
						}
					}


				if((!zmk_V_knd2)&&(!blk_V_knd2)){t_avr_knd2=0;}
				if((t_avr_knd2<3)&&blk_V_knd2){t_avr_knd2++;blk_V_knd2=0;}
				if((t_avr_knd2<3)&&zmk_V_knd2){t_avr_knd2++;zmk_V_knd2=0;}
				if(t_avr_knd2>=3)
					{
					tRAZG_knd2=0;t_avr_knd2_o=0;
					anV_knd2=0;
					trV_knd2=0; kV_knd2=0;
					obr_V_knd2=0;
					}
				}//end !blk_V_knd2	&& blk_V_knd2
				Nop();
				Nop();
			}
		else 			//���������� 2 ����������� ���������� 
			{

			if(suV_knd2){suV_knd2=0;obr_V_knd2=0;tRAZG_knd2=150;}

			suV_knd2=uV_knd2;

			//��� 2 ����������� ���������� 
			I_CL_knd2=0;

			if(blk_V_knd2)
				{
				if(FCL1s)t_blk_res_knd2++;
				if(t_blk_res_knd2>5){t_blk_res_knd2=0;blk_V_knd2=0;}
				}
			if(zmk_V_knd2)
				{
				if(FCL1s)t_blk_res_knd2++;
				if(t_blk_res_knd2>5){t_blk_res_knd2=0;zmk_V_knd2=0;}
				}

			t_avr_knd2=0;
			t_avr_knd2_o=0;

			if(tRAZG_knd2){tRAZG_knd2--;U_CL_knd2=0;}

			TSTL=0;
			anV_knd2=0;
			kV_knd2=0;trV_knd2=0; kV_knd2=0;

			if((tRAZG_knd2==0)&&FCL1s)
				{
				TSTL=0;
				op_bp=U_V_knd2;
				Delay10KTCYx(1);
	
				trV_knd2=1;anV_knd2=1;
				Delay10KTCYx(2);
				//U_CL_knd2
				tst_AN_X_h();//
				U_CL_knd2=ADRESH;
	
	 			if(U_CL_knd2>5)
					{
					obr_V_knd2=0;zmk_V_knd2=0;
					blk_V_knd2=0;
					anV_knd2=0;
					trV_knd2=0; kV_knd2=0;
					}	
				else 
					{
					TSTL=1;
						
					op_bp=U_V_knd2;
					trV_knd2=1;Nop();Nop();
					anV_knd2=1;
					Delay10KTCYx(1);
					//U_CL_knd2  
					tst_AN_X_h();//
					trV_knd2=0;
					anV_knd2=0;
					kV_knd2=0;
					U_CL_knd2=ADRESH;
		 			if(U_CL_knd2>60){obr_V_knd2=1;zmk_V_knd2=0;blk_V_knd2=0;}	
					else obr_V_knd2=0;
	
					if(zmk_V_knd2)obr_V_knd2=0;
					}
				}
			}
no_knd2:
	TSTL=0;
	}
	else
		{
		trV_knd1=0; kV_knd1=0;
		trV_knd2=0; kV_knd2=0;
		trV_isp1=0; kV_isp1=0;
		trV_isp2=0; kV_isp2=0;	
	
		obr_V_knd1=0;zmk_V_knd1=0;blk_V_knd1=0;	
		obr_V_knd2=0;zmk_V_knd2=0;blk_V_knd2=0;	
		obr_V_isp1=0;zmk_V_isp1=0;blk_V_isp1=0;
		obr_V_isp2=0;zmk_V_isp2=0;blk_V_isp2=0;

		SOST_UPR1=SOST_UPR3=0;
		SOST_UPR2&=0xfc;
		t_avr_isp1=t_avr_isp2=t_avr_knd1=t_avr_knd2=0;
		t_avr_isp1_o=t_avr_isp2_o=t_avr_knd1_o=t_avr_knd2_o=0;
		tRAZG_isp1=tRAZG_isp2=tRAZG_knd1=tRAZG_knd2=0;

		}


	if(t_stanby < 65)
		{
		SOST_UPR1=SOST_UPR3=0;
		SOST_UPR2&=0xfc;
		t_avr_isp1=t_avr_isp2=t_avr_knd1=t_avr_knd2=0;
		t_avr_isp1_o=t_avr_isp2_o=t_avr_knd1_o=t_avr_knd2_o=0;
		tRAZG_isp1=tRAZG_isp2=tRAZG_knd1=tRAZG_knd2=0;
		}
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void silov_kl(void)
	{

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  12

	
		if(U_nap>80)
		{
	TSTL=1;
		if(t_zad_def&&uC_def)
			{
			t_zad_def--;
			anC_def=0;
			kC_def=0;trC_def=0;
			}
		if(uC_def&&(!t_zad_def)) //��������� ������� ����������
			{
			if(t_avr_def==0){zmk_C_def=0;}
			if(!zmk_C_def)
				{
				if(t_vkl_def<8)
					{
					t_vkl_def++;
					anC_def=0;
					trC_def=0;	kC_def=1;trC_def=0;	
					Delay100TCYx(70);
					trC_def=1;	
					Delay100TCYx(100);
					}
				else 
					{
					trC_def=1;	
					}
		//���������� ������� ����������
				anC_def=1;
				op_bp=U_def;tst_AN_X_h();//AN4
				U_C_def=ADRESH;

				anC_def=0;
				if(U_C_def>100)
					{
					zmk_C_def=0;

					if(FCL1s)
						{
						anC_def=0;
						kC_def=0;trC_def=0;	
						Delay100TCYx(100);
						trC_def=1;	
						anC_def=1;
				//���������� ������� ����������
						Delay100TCYx(100);
						op_bp=U_def;tst_AN_X_h();//AN4
						sU_C_def=ADRESH;
						anC_def=0;

						if(sU_C_def>20)
							{
							obr_C_def=1;zmk_C_def=0;
							if((t_avr_def_o<3)&&(!obr_C_def)){t_avr_def_o=0;}

							if((t_avr_def_o<3)&&obr_C_def&&(!DOP_MODUL)&&(multi!=0xaa))
								{
								t_avr_def_o++;
								if(!uC_con)obr_C_def=0;
								}
							if((t_avr_def_o<3)&&obr_C_def&&(multi==0xaa))
								{
								t_avr_def_o++;
								}

							if((t_avr_def_o>=3)&&obr_C_def)
								{
								obr_C_def=1;
								}
							}	
						else {obr_C_def=0;}

						anC_def=0;
						trC_def=0;	kC_def=1;
						Delay100TCYx(70);
						trC_def=1;	
						}	

					if(!obr_C_def)I_C_def=25;
					else I_C_def=0;
					}
				else
					{
					zmk_C_def=1;
					I_C_def=0;
					}

			if((t_avr_def<5)&&(!zmk_C_def)){t_avr_def=0;}
			if((t_avr_def<5)&&zmk_C_def){t_avr_def++;zmk_C_def=0;}
			if((t_avr_def>=5)&&zmk_C_def)
				{
				obr_C_def=0;
				I_C_def=0;
				if(uC_con&&uCOMP)uCOMP=0;
				t_zad_def=100;
				anC_def=0;
				kC_def=0;trC_def=0;	
				}
			}
		else 
			{//zmk_C_def=1	
			t_avr_def=0;
			t_vkl_def=0;
if(t_zad_def)t_zad_def--;
			if(uC_con&&uCOMP)uCOMP=0;
				
				anC_def=0;
				kC_def=0;trC_def=0;	
				Delay10KTCYx(2);
				trC_def=1;	
		//���������� ������� ����������
				Delay100TCYx(10);
				op_bp=U_def;tst_AN_X_h();//AN4
				U_C_def=ADRESH;
				trC_def=0;	
				anC_def=0;
				if(U_C_def>20)
					{
					obr_C_def=1;
					zmk_C_def=0;
					t_avr_def=0;

					if(uC_con&&uCOMP)uCOMP=0;

					}	
				else obr_C_def=0;
			}
		}
	else 			//���������� ������� ����������
		{
			t_avr_def=0;t_avr_def_o=0;
			t_vkl_def=0;
if(t_zad_def)t_zad_def--;

			anC_def=0;
			trC_def=0; kC_def=0;
			Delay100TCYx(100);
			trC_def=1;	
			anC_def=1;
			Delay100TCYx(100);
			//���������� �� ������� ����������
			op_bp=U_def;tst_AN_X_h();//AN4
			U_C_def=ADRESH;
			trC_def=0;	
			anC_def=0;
			if(U_C_def>20){obr_C_def=1;zmk_C_def=0;}	
			else obr_C_def=0;

			if(zmk_C_def)obr_C_def=0;

			//��� ������� ����������

			I_C_def=0;

			if(zmk_C_def)
				{
				if(FCL1s)t_res_def++;
				if(t_res_def>10){t_res_def=0;zmk_C_def=0;}
				}
			}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  12

if(((!YES_OTOP)&&(YES_OTOP2==0))||(tester_rej == 0xf2))
	{
		if(t_zad_con&&uC_con)
			{
			t_zad_con--;
			kC_con=0;trC_con=0;
			}
		if(uC_con&&(!t_zad_con)) //��������� ������� �������
			{
			if(t_avr_con==0){zmk_C_con=0;}
			if(!zmk_C_con)
				{
				if(t_vkl_con<8)
					{
					t_vkl_con++;
					kC_con=1;trC_con=0;	
					Delay100TCYx(70);		
					trC_con=1;	
					Delay100TCYx(100);
					}		
				else 
					{
					trC_con=1;	
					}

		//���������� ������� �������
				op_bp=U_con;tst_AN_X_h();//AN25
				U_C_con=ADRESH;

				if(U_C_con>100)
					{
					zmk_C_con=0;

					if(FCL1s)
						{
						kC_con=0;trC_con=0;	
						Delay100TCYx(100);		
						trC_con=1;	
						anC_con=1;
		//���������� ������� �������
						Delay100TCYx(100);
						op_bp=U_con;tst_AN_X_h();//AN25
						sU_C_con=ADRESH;
						anC_con=0;
		
						if(sU_C_con>20)
							{
							obr_C_con=1;zmk_C_con=0;
							if((t_avr_con_o<3)&&(!obr_C_con)){t_avr_con_o=0;}

							if((t_avr_con_o<3)&&obr_C_con)
									{t_avr_con_o++;
									if(multi!=0xaa)obr_C_con=0;}

							if((t_avr_con_o>=3)&&obr_C_con)
									{obr_C_con=1;zmk_C_con=0;}
		
							}	
						else {obr_C_con=0;}

						kC_con=1;trC_con=0;	
						Delay100TCYx(70);		
						trC_con=1;	
						}	

					if(!obr_C_con)I_C_con=25;
					else I_C_con=0;
					}	
				else 
					{
					zmk_C_con=1;
					obr_C_con=0;
					I_C_con=0;
					}

				if((t_avr_con<5)&&(!zmk_C_con)){t_avr_con=0;}
				if((t_avr_con<5)&&zmk_C_con){t_avr_con++;zmk_C_con=0;}
				if((t_avr_con>=5)&&zmk_C_con)
					{
					obr_C_con=0;I_C_con=0;
					t_zad_con=100;
					kC_con=0;trC_con=0;	
					}

				}
		else 
			{//zmk_C_con=1	
			t_avr_con=0;
			t_vkl_con=0;

if(t_zad_con)t_zad_con--;

				kC_con=0;trC_con=0;	
				Delay10KTCYx(2);
				trC_con=1;	
				anC_con=1;
		//���������� ������� �������
				Delay100TCYx(10);
				op_bp=U_con;tst_AN_X_h();//AN25
				U_C_con=ADRESH;
				trC_con=0;anC_con=0;	
	
				if(U_C_con>20)
					{
					obr_C_con=1;
					zmk_C_con=0;
					t_avr_con=0;
					}	
				else obr_C_con=0;
			}
		}
	else 			//���������� ������� �������
		{
		t_avr_con=0;t_avr_con_o=0;
		t_vkl_con=0;
if(t_zad_con)t_zad_con--;

		trC_con=0; kC_con=0;
		Delay100TCYx(100);
		trC_con=1;	anC_con=1;
		Delay100TCYx(100);

		//���������� �� ������� �������
		op_bp=U_con;tst_AN_X_h();//AN25
		U_C_con=ADRESH;
		trC_con=0;	anC_con=0;

		if(U_C_con>20){obr_C_con=1;zmk_C_con=0;}	
		else obr_C_con=0;

		if(zmk_C_con)obr_C_con=0;

				//��� ������� �������

					I_C_con=0;

			if(zmk_C_con)
				{
				if(FCL1s)t_res_con++;
				if(t_res_con>10){t_res_con=0;zmk_C_con=0;}
				}

		}
	}
	else   // yes YES_OTOP
		{obr_C_con = 0;zmk_C_con=0;}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 12

if(uCOMP&&uC_con&&uC_def&&obr_C_def)uCOMP=0;
if(uCOMP&&(!uC_con)&&uC_def&&obr_C_def&&DOP_MODUL)uCOMP=0;

//uCOMP=1;
		if(tZAD_CND&&uCOMP)
			{
			tZAD_CND=0;
			kCOMP=0;trCOMP=0;
			}
if(t_pau_comp){t_pau_comp--;}

if((tester_rej==0xf3)||(tester_rej==0xf2)){t_pau_comp=0;tZAD_CND=0;}
		if(uCOMP&&(!tZAD_CND)&&(!t_pau_comp)) //��������� �����������
			{
			f_pau_comp=1;
//			if(t_avr_comp==0){zmk_COMP=0;}
			if(!zmk_COMP)
				{
				if(t_vkl_comp<8)
					{
					t_vkl_comp++;
					kCOMP=1;trCOMP=0;	
					Delay100TCYx(250);	
					trComp=1;	
					Delay100TCYx(100);		
					}	
				else 
					{
					trComp=1;	
					}
				anComp=1;
		//���������� �� �����������
				op_bp=U_comp;tst_AN_X_h();//
				U_Comp=ADRESH;
				anComp=0;
	
				if(U_Comp>40)
					{
					zmk_Comp=0;

					if(FCL1s)
						{
						kCOMP=0;trCOMP=0;	
						Delay100TCYx(100);		
						trComp=1;	
						anComp=1;
						//���������� �� �����������
						Delay100TCYx(100);		
						op_bp=U_comp;tst_AN_X_h();//AN22
						U_Comp=ADRESH;
						anComp=0;
			
						if(U_Comp>20)
							{
							obr_COMP=1;zmk_COMP=0;
							if(t_avr_comp_o<5)
								{t_avr_comp_o++;obr_COMP=0;}
							else
								{
								zmk_COMP=0;
								}
							}	
						else {obr_COMP=0;t_avr_comp_o=0;}


						kCOMP=1;trCOMP=0;	
						Delay100TCYx(250);		
						trComp=1;	

						}
					if(!obr_COMP)I_Comp=40;
					else I_Comp=0;
					}	
				else 
					{
					zmk_Comp=1;
					I_Comp=0;
					}
	
				if((t_avr_comp<5)&&(!zmk_Comp)){t_avr_comp=0;}
				if((t_avr_comp<5)&&zmk_Comp){t_avr_comp++;zmk_Comp=0;}
				if((t_avr_comp>=5)&&zmk_Comp)
					{
					obr_COMP=0;
					I_Comp=0;
					tZAD_CND=100;
					kCOMP=0;trCOMP=0;	
					}

//zmk_COMP=1;t_avr_comp=5;

				}
			else 
				{//zmk_COMP=1	

				t_avr_comp=0;
				t_vkl_comp=0;

				kCOMP=0;trCOMP=0;	
				Delay10KTCYx(2);
				trCOMP=1;anComp=1;	
		//���������� �� �����������
				Delay100TCYx(10);
				op_bp=U_comp;tst_AN_X_h();//
				U_Comp=ADRESH;
				trCOMP=0; anComp=0;	
	
				if(U_Comp>20)
					{
					obr_COMP=1;
					zmk_COMP=0;
					t_avr_comp=0;
					}	
				else obr_COMP=0;
			}
		}
		else 			//���������� �����������
			{
			if(f_pau_comp){t_pau_comp=100;f_pau_comp=0;}

			t_avr_comp=0;
			t_vkl_comp=0;

			trCOMP=0; kCOMP=0;
			Delay100TCYx(100);
			anComp=1;  trCOMP=1;
			Delay100TCYx(100);
			//���������� �� �����������
			op_bp=U_comp;tst_AN_X_h();//AN24
			U_Comp=ADRESH;
			trCOMP=0;anComp=0;
			kCOMP=0;	

			if(U_Comp>20)
				{
				obr_COMP=1;zmk_COMP=0;
				if(t_avr_comp_o<10)
					{t_avr_comp_o++;obr_COMP=0;}
				else
					{
					zmk_COMP=0;
					}
				}	
			else {obr_COMP=0;t_avr_comp_o=0;}


			if(zmk_COMP)obr_COMP=0;

				//��� �����������
			I_Comp=0;


			if(zmk_COMP)
				{
				if(FCL1s)t_res_comp++;
				if(t_res_comp>10){t_res_comp=0;zmk_COMP=0;}
				}
			}
//obr_COMP=0;

///////////////////////////////////////

	if(fH_def || fH_def_12)
		{
		if(uV_isp3){uH_def=1;uH_def1=1;uH_def2=1;}
		else {uH_def=0;uH_def1=0;uH_def2=0;}
		}
	else {uH_def=0;uH_def1=0;uH_def2=0;}

//if(uH_def){kH_def=1;trH_def=0;}
//else {kH_def=0;trH_def=0;}

//
if(fH_def_12) goto no_H_def;	

	if(fH_def)
		{
		if(t_zad_h_def&&uH_def)
			{
			t_zad_h_def--;
			kH_def=0;trH_def=0;
			}

		if(uH_def&&(!t_zad_h_def)) //��������� ����������� ������� �����.
			{
			if(t_avr_h_def==0){zmk_H_def=0;}
			if(!zmk_H_def)
				{
				if(t_vkl_h_def<4)
					{
					t_vkl_h_def++;
					trH_def=0;	kH_def=1;trH_def=0;	
					Delay100TCYx(60);
					trH_def=1;	
					Delay100TCYx(100);
					}
				else 
					{
					trH_def=1;	
					}

		//���������� ����������� ������� �����.
				op_bp=U_h_def;tst_AN_X_h();//AN4
				U_H_def=ADRESH;

				if(U_H_def>80)
					{
					zmk_H_def=0;

					if(FCL1s)
						{
						trH_def=0;kH_def=0;trH_def=0;	
						Delay100TCYx(100);
						trH_def=1;	
						anH_def=1;
				//���������� ����������� ������� �����.
						Delay100TCYx(100);
						op_bp=U_h_def;tst_AN_X_h();//AN4
						U_H_def=ADRESH;
						anH_def=0;
						if(U_H_def>20)
							{
							obr_H_def=1;zmk_H_def=0;
							}	
						else {obr_H_def=0;}

						trH_def=0;	kH_def=1;
						Delay100TCYx(100);
						trH_def=1;	
						}	

					}
				else {zmk_H_def=1;}

			if((t_avr_h_def<3)&&(!zmk_H_def)){t_avr_h_def=0;}
			if((t_avr_h_def<3)&&zmk_H_def){t_avr_h_def++;zmk_H_def=0;}
			if((t_avr_h_def>=3)&&zmk_H_def)
				{
				obr_H_def=0;
				t_zad_h_def=100;
				kH_def=0;trH_def=0;	
				}
			}
		else 
			{//zmk_h_def=1	
			t_avr_h_def=0;
			t_vkl_h_def=0;

				kH_def=0;trH_def=0;	
				Delay10KTCYx(2);
				trH_def=1;	
		//���������� ����������� ������� �����.
				Delay100TCYx(10);
				op_bp=U_h_def;tst_AN_X_h();//AN4
				U_H_def=ADRESH;
				trH_def=0;	
	
				if(U_H_def>20)
					{
					obr_H_def=1;
					zmk_H_def=0;
					t_avr_h_def=0;

					}	
				else obr_H_def=0;
			}

		}
	else 			//���������� ����������� ������� �����.
		{
			t_avr_h_def=0;
			t_vkl_h_def=0;
if(t_zad_h_def)t_zad_h_def--;

			trH_def=0; kH_def=0;
			Delay100TCYx(100);
			trH_def=1;	
			Delay100TCYx(100);
			//���������� ����������� ������� �����.
			op_bp=U_h_def;tst_AN_X_h();//AN4
			U_H_def=ADRESH;
			trH_def=0;	

			if(U_H_def>20){obr_H_def=1;zmk_H_def=0;}	
			else obr_H_def=0;

			if(zmk_H_def)obr_H_def=0;

			if(zmk_H_def)
				{
				if(FCL1s)t_res_h_def++;
				if(t_res_h_def>5){t_res_h_def=0;zmk_H_def=0;}
				}
			}
		}
//	
//
no_H_def:

	if(fH_def_12)
		{
		if(t_zad_h_def1&&uH_def1)
			{
			t_zad_h_def1--;
			kH_def1=0;trH_def1=0;
			}

		if(uH_def1&&(!t_zad_h_def1)) //��������� ����������� 1 ������� �����.
			{
			if(t_avr_h_def1==0){zmk_H_def1=0;}
			if(!zmk_H_def1)
				{
				if(t_vkl_h_def1<4)
					{
					t_vkl_h_def1++;
					trH_def1=0;	kH_def1=1;trH_def1=0;	
					Delay100TCYx(60);
					trH_def1=1;	
					Delay100TCYx(100);
					}
				else 
					{
					trH_def=1;	
					}

		//���������� ����������� ������� �����.
				op_bp=U_h_def1;tst_AN_X_h();//AN4
				U_H_def1=ADRESH;

				if(U_H_def1>80)
					{
					zmk_H_def1=0;

					if(FCL1s)
						{
						trH_def1=0;kH_def1=0;trH_def1=0;	
						Delay100TCYx(100);
						trH_def1=1;	
						anH_def1=1;
				//���������� ����������� ������� �����.
						Delay100TCYx(100);
						op_bp=U_h_def1;tst_AN_X_h();//AN4
						U_H_def1=ADRESH;
						anH_def1=0;
						if(U_H_def1>20)
							{
							obr_H_def1=1;zmk_H_def1=0;
							}	
						else {obr_H_def1=0;}

						trH_def1=0;	kH_def1=1;
						Delay100TCYx(100);
						trH_def1=1;	
						}	

					}
				else {zmk_H_def1=1;}

			if((t_avr_h_def1<3)&&(!zmk_H_def1)){t_avr_h_def1=0;}
			if((t_avr_h_def1<3)&&zmk_H_def1){t_avr_h_def1++;zmk_H_def1=0;}
			if((t_avr_h_def1>=3)&&zmk_H_def1)
				{
				obr_H_def1=0;
				t_zad_h_def1=100;
				kH_def1=0;trH_def1=0;	
				}
			}
		else 
			{//zmk_h_def1=1	
			t_avr_h_def1=0;
			t_vkl_h_def1=0;

				kH_def1=0;trH_def1=0;	
				Delay10KTCYx(2);
				trH_def1=1;	
		//���������� ����������� ������� �����.
				Delay100TCYx(10);
				op_bp=U_h_def1;tst_AN_X_h();//AN4
				U_H_def1=ADRESH;
				trH_def1=0;	
	
				if(U_H_def1>20)
					{
					obr_H_def1=1;
					zmk_H_def1=0;
					t_avr_h_def1=0;

					}	
				else obr_H_def1=0;
			}

		}
	else 			//���������� ����������� 1 ������� �����.
		{
			t_avr_h_def1=0;
			t_vkl_h_def1=0;
if(t_zad_h_def1)t_zad_h_def1--;

			trH_def1=0; kH_def1=0;
			Delay100TCYx(100);
			trH_def1=1;	
			Delay100TCYx(100);
			//���������� ����������� ������� �����.
			op_bp=U_h_def1;tst_AN_X_h();//AN4
			U_H_def1=ADRESH;
			trH_def1=0;	

			if(U_H_def1>20){obr_H_def1=1;zmk_H_def1=0;}	
			else obr_H_def1=0;

			if(zmk_H_def1)obr_H_def1=0;

			if(zmk_H_def1)
				{
				if(FCL1s)t_res_h_def1++;
				if(t_res_h_def1>5){t_res_h_def1=0;zmk_H_def1=0;}
				}
			}
		}

//
	if(fH_def_12)
		{
		if(t_zad_h_def2&&uH_def2)
			{
			t_zad_h_def2--;
			kH_def2=0;trH_def2=0;
			}

		if(uH_def2&&(!t_zad_h_def2)) //��������� ����������� 2 ������� �����.
			{
			if(t_avr_h_def2==0){zmk_H_def2=0;}
			if(!zmk_H_def2)
				{
				if(t_vkl_h_def2<4)
					{
					t_vkl_h_def2++;
					trH_def2=0;	kH_def2=1;trH_def2=0;	
					Delay100TCYx(60);
					trH_def2=1;	
					Delay100TCYx(100);
					}
				else 
					{
					trH_def2=1;	
					}

		//���������� ����������� ������� �����.
				op_bp=U_h_def2;tst_AN_X_h();//AN4
				U_H_def2=ADRESH;

				if(U_H_def2>80)
					{
					zmk_H_def2=0;

					if(FCL1s)
						{
						trH_def2=0;kH_def2=0;trH_def2=0;	
						Delay100TCYx(100);
						trH_def2=1;	
						anH_def2=1;
				//���������� ����������� ������� �����.
						Delay100TCYx(100);
						op_bp=U_h_def2;tst_AN_X_h();//AN4
						U_H_def2=ADRESH;
						anH_def2=0;
						if(U_H_def2>20)
							{
							obr_H_def2=1;zmk_H_def2=0;
							}	
						else {obr_H_def2=0;}

						trH_def2=0;	kH_def2=1;
						Delay100TCYx(100);
						trH_def2=1;	
						}	

					}
				else {zmk_H_def2=1;}

			if((t_avr_h_def2<3)&&(!zmk_H_def2)){t_avr_h_def2=0;}
			if((t_avr_h_def2<3)&&zmk_H_def2){t_avr_h_def2++;zmk_H_def2=0;}
			if((t_avr_h_def2>=3)&&zmk_H_def2)
				{
				obr_H_def2=0;
				t_zad_h_def2=100;
				kH_def2=0;trH_def2=0;	
				}
			}
		else 
			{//zmk_h_def2=1	
			t_avr_h_def2=0;
			t_vkl_h_def2=0;

				kH_def2=0;trH_def2=0;	
				Delay10KTCYx(2);
				trH_def2=1;	
		//���������� ����������� ������� �����.
				Delay100TCYx(10);
				op_bp=U_h_def2;tst_AN_X_h();//AN4
				U_H_def2=ADRESH;
				trH_def2=0;	
	
				if(U_H_def2>20)
					{
					obr_H_def2=1;
					zmk_H_def2=0;
					t_avr_h_def2=0;

					}	
				else obr_H_def2=0;
			}

		}
	else 			//���������� ����������� 2 ������� �����.
		{
			t_avr_h_def2=0;
			t_vkl_h_def2=0;
if(t_zad_h_def2)t_zad_h_def2--;

			trH_def2=0; kH_def2=0;
			Delay100TCYx(100);
			trH_def2=1;	
			Delay100TCYx(100);
			//���������� ����������� ������� �����.
			op_bp=U_h_def2;tst_AN_X_h();//AN4
			U_H_def2=ADRESH;
			trH_def2=0;	

			if(U_H_def2>20){obr_H_def2=1;zmk_H_def2=0;}	
			else obr_H_def2=0;

			if(zmk_H_def2)obr_H_def2=0;

			if(zmk_H_def2)
				{
				if(FCL1s)t_res_h_def2++;
				if(t_res_h_def2>5){t_res_h_def2=0;zmk_H_def2=0;}
				}
			}
		}




	TSTL=0;		 
	}
else
	{
	trC_con=0; kC_con=0;
	trCOMP=0; kCOMP=0;
	trC_def=0; kC_def=0;
	trH_def=0; kH_def=0;
	trH_def1=0; kH_def1=0;
	trH_def2=0; kH_def2=0;

	obr_COMP=0;zmk_COMP=0;
	obr_C_def=0;zmk_C_def=0;
	obr_C_con=0;zmk_C_con=0;
	obr_H_def=0;zmk_H_def=0;
	}	
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void silov_kl_dop(void)
	{

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  12

	
		if(U_nap>80)	TSTL=1;
	
		if(t_zad_isp1&&uC_isp1)
			{
			t_zad_isp1--;
			kC_isp1=0;trC_isp1=0;
			}
		if(uC_isp1&&(!t_zad_isp1)) //��������� ������� ���������� 1
			{
			if(t_avr_C_isp1==0){zmk_C_isp1=0;}
			if(!zmk_C_isp1)
				{
				if(t_vkl_isp1<4)
					{
					t_vkl_isp1++;
					trC_isp1=0;	kC_isp1=1;trC_isp1=0;	
					Delay100TCYx(60);
					trC_isp1=1;	
					Delay100TCYx(100);
					}
				else 
					{
					trC_isp1=1;	
					}

		//���������� ������� ���������� 1
				op_bp=U_isp1;tst_AN_X_h();//AN4
				U_C_isp1=ADRESH;

				if(U_C_isp1>100)
					{
					zmk_C_isp1=0;

					if(FCL1s)
						{
						kC_isp1=0;trC_isp1=0;	
						Delay100TCYx(100);
						trC_isp1=1;	

				//���������� ������� ���������� 1
						Delay100TCYx(100);
						op_bp=U_isp1;tst_AN_X_h();//AN4
						U_C_isp1=ADRESH;

						if(U_C_isp1>20)
							{
							obr_C_isp1=1;zmk_C_isp1=0;
//							if((t_avr_C_isp1_o<3)&&(!obr_C_isp1)){t_avr_C_isp1_o=0;}
//							if((t_avr_C_isp1_o<3)&&obr_C_isp1)
//									{t_avr_C_isp1_o++;obr_C_isp1=0;}
//							if((t_avr_C_isp1_o>=3)&&obr_C_isp1)
//								{
//								obr_C_isp1=1;zmk_C_isp1=0;
////								if(uC_con&&uCOMP)uCOMP=0;
//								}
							}	
						else {obr_C_isp1=0;}

						trC_isp1=0;	kC_isp1=1;
						Delay100TCYx(100);
						trC_isp1=1;	
						}	

					if(!obr_C_isp1)I_C_isp1=25;
					else I_C_isp1=0;
					}
				else {zmk_C_isp1=1;I_C_isp1=0;}

			if((t_avr_C_isp1<3)&&(!zmk_C_isp1)){t_avr_C_isp1=0;}
			if((t_avr_C_isp1<3)&&zmk_C_isp1){t_avr_C_isp1++;zmk_C_isp1=0;}
			if((t_avr_C_isp1>=3)&&zmk_C_isp1)
				{
				obr_C_isp1=0;
				I_C_isp1=0;
				t_zad_isp1=100;
				kC_isp1=0;trC_isp1=0;	
				}
			}
		else 
			{//zmk_C_isp1=1	
			t_avr_isp1=0;
			t_vkl_isp1=0;

				kC_isp1=0;trC_isp1=0;	
				Delay10KTCYx(2);
				trC_isp1=1;	
		//���������� ������� ���������� 1
				Delay100TCYx(10);
				op_bp=U_isp1;tst_AN_X_h();//AN4
				U_C_isp1=ADRESH;
				trC_isp1=0;	
	
				if(U_C_isp1>20)
					{
					obr_C_isp1=1;
					zmk_C_isp1=0;
					t_avr_C_isp1=0;

					}	
				else obr_C_isp1=0;
			}
		}
	else 			//���������� ������� ���������� 1
		{
			t_avr_C_isp1=0;t_avr_C_isp1_o=0;
			t_vkl_isp1=0;
if(t_zad_isp1)t_zad_isp1--;

			trC_isp1=0; kC_isp1=0;
			Delay100TCYx(100);
			trC_isp1=1;	
			Delay100TCYx(100);
			//���������� �� ������� ����������
			op_bp=U_isp1;tst_AN_X_h();//AN4
			U_C_isp1=ADRESH;
			trC_isp1=0;	

			if(U_C_isp1>20){obr_C_isp1=1;zmk_C_isp1=0;}	
			else obr_C_isp1=0;

			if(zmk_C_isp1)obr_C_isp1=0;

			//��� ������� ����������

			I_C_isp1=0;

			if(zmk_C_isp1)
				{
				if(FCL1s)t_res_C_isp1++;
				if(t_res_C_isp1>5){t_res_C_isp1=0;zmk_C_isp1=0;}
				}
			}


		if(t_zad_isp2&&uC_isp2)
			{
			t_zad_isp2--;
			kC_isp2=0;trC_isp2=0;
			}

		if(uC_isp2&&(!t_zad_isp2)) //��������� ������� ���������� 2
			{
			if(t_avr_C_isp2==0){zmk_C_isp2=0;}
			if(!zmk_C_isp2)
				{
				if(t_vkl_isp2<4)
					{
					t_vkl_isp2++;
					trC_isp2=0;	kC_isp2=1;trC_isp2=0;	
					Delay100TCYx(60);
					trC_isp2=1;	
					Delay100TCYx(100);
					}
				else 
					{
					trC_isp2=1;	
					}

		//���������� ������� ���������� 2
				op_bp=U_isp2;tst_AN_X_h();//AN4
				U_C_isp2=ADRESH;

				if(U_C_isp2>100)
					{
					zmk_C_isp2=0;

					if(FCL1s)
						{
						kC_isp2=0;trC_isp2=0;	
						Delay100TCYx(100);
						trC_isp2=1;	

				//���������� ������� ���������� 2
						Delay100TCYx(100);
						op_bp=U_isp2;tst_AN_X_h();//AN4
						U_C_isp2=ADRESH;

						if(U_C_isp2>20)
							{
							obr_C_isp2=1;zmk_C_isp2=0;
//							if((t_avr_C_isp2_o<3)&&(!obr_C_isp2)){t_avr_C_isp2_o=0;}
//							if((t_avr_C_isp2_o<3)&&obr_C_isp2)
//									{t_avr_C_isp2_o++;obr_C_isp2=0;}
//							if((t_avr_C_isp2_o>=3)&&obr_C_isp2)
//								{
//								obr_C_isp2=1;zmk_C_isp2=0;
////								if(uC_con&&uCOMP)uCOMP=0;
//								}
							}	
						else {obr_C_isp2=0;}

						trC_isp2=0;	kC_isp2=1;
						Delay100TCYx(100);
						trC_isp2=1;	
						}	

					if(!obr_C_isp2)I_C_isp2=25;
					else I_C_isp2=0;
					}
				else {zmk_C_isp2=1;I_C_isp2=0;}

			if((t_avr_C_isp2<3)&&(!zmk_C_isp2)){t_avr_C_isp2=0;}
			if((t_avr_C_isp2<3)&&zmk_C_isp2){t_avr_C_isp2++;zmk_C_isp2=0;}
			if((t_avr_C_isp2>=3)&&zmk_C_isp2)
				{
				obr_C_isp2=0;I_C_isp2=0;
				t_zad_isp2=100;
				kC_isp2=0;trC_isp2=0;	
				}
			}
		else 
			{//zmk_C_isp2=1	
			t_avr_isp2=0;
			t_vkl_isp2=0;


				kC_isp2=0;trC_isp2=0;	
				Delay10KTCYx(2);
				trC_isp2=1;	
		//���������� ������� ���������� 2
				Delay100TCYx(10);
				op_bp=U_isp2;tst_AN_X_h();//AN4
				U_C_isp2=ADRESH;
				trC_isp2=0;	
	
				if(U_C_isp2>20)
					{
					obr_C_isp2=1;
					zmk_C_isp2=0;
					t_avr_C_isp2=0;

					}	
				else obr_C_isp2=0;
			}
		}
	else 			//���������� ������� ���������� 2
		{
			t_avr_C_isp2=0;t_avr_C_isp2_o=0;
			t_vkl_isp2=0;
if(t_zad_isp2)t_zad_isp2--;

			trC_isp2=0; kC_isp2=0;
			Delay100TCYx(100);
			trC_isp2=1;	
			Delay100TCYx(100);
			//���������� �� ������� ����������
			op_bp=U_isp2;tst_AN_X_h();//AN4
			U_C_isp2=ADRESH;
			trC_isp2=0;	

			if(U_C_isp2>20){obr_C_isp2=1;zmk_C_isp2=0;}	
			else obr_C_isp2=0;

			if(zmk_C_isp2)obr_C_isp2=0;

			//��� ������� ����������

			I_C_isp2=0;

			if(zmk_C_isp2)
				{
				if(FCL1s)t_res_C_isp2++;
				if(t_res_C_isp2>5){t_res_C_isp2=0;zmk_C_isp2=0;}
				}
			}

	TSTL=0;		 

	}//silov_kl_dop




void Config_T(void)
{
fConfig=0;
fConfig_t=0;

timer1 = 0;

//op=0;
//eepromReadByte(op);//��������� ���� �� EEPROM
//op_b_ee=EEDATA;

		TSTL=1;
//
			trV_isp1=1;
			anV_isp1=1;
			Delay10KTCYx(1);
			//U_CL_isp1  ����������
			op_bp=U_V_isp1;tst_AN_X_h();//
			U_CL_isp1=ADRESH;
			if(U_CL_isp1<10)fConfig|=0x1;
			anV_isp1=0;
			kV_isp1=0;trV_isp1=0;	

			trV_knd2=1; anV_knd2=1; 
			Delay10KTCYx(1);
			//U_CL_knd2  ����������
			op_bp=U_V_knd2;tst_AN_X_h();//
			U_CL_knd2=ADRESH;
 			if(U_CL_knd2<10)fConfig|=0x8;
			anV_knd2=0; 
			kV_knd2=0; trV_knd2=0; 

			trV_isp2=1;	anV_isp2=1;
			Delay10KTCYx(1);
			//U_CL_isp2  ����������
			op_bp=U_V_isp2;tst_AN_X_h();//
			U_CL_isp2=ADRESH;
			if(U_CL_isp2<10)fConfig|=0x2;
			anV_isp2=0;
			kV_isp2=0;trV_isp2=0;	

			trV_knd1=1; anV_knd1=1;
			Delay10KTCYx(1);
			//U_CL_knd1  ����������
			op_bp=U_V_knd1;tst_AN_X_h();//AN8
			U_CL_knd1=ADRESH;
 			if(U_CL_knd1<10)fConfig|=0x4;
			anV_knd1=0; 
			kV_knd1=0; trV_knd1=0;

		TSTL=0;

	if(fSTANBY)
		{
//��������� ������������
	
		tst_pr_stanby();

		kV_isp1=1;trV_isp1=0;	
		Delay100TCYx(60);
		trV_isp1=1;
		anV_isp1=1;
		Delay100TCYx(30);
		//U_CL_isp1  ����������
		op_bp=U_V_isp1;tst_AN_X_h();//AN3
		U_CL_isp1=ADRESH;
		if(U_CL_isp1>30)fConfig_t|=0x1;
		anV_isp1=0;
		kV_isp1=0;trV_isp1=0;	

		Delay10KTCYx(2);
		tst_pr_stanby();

		kV_knd2=1;trV_knd2=0; 
		Delay100TCYx(60);
		trV_knd2=1;
		anV_knd2=1;
		Delay100TCYx(50);
		//U_CL_knd2  ����������
		op_bp=U_V_knd2;tst_AN_X_h();//AN13
		U_CL_knd2=ADRESH;
			if(U_CL_knd2>30)fConfig_t|=0x8;
		anV_knd2=0;
		kV_knd2=0; trV_knd2=0; 

		Delay10KTCYx(2);
		tst_pr_stanby();


		kV_isp2=1;trV_isp2=0;	
		Delay100TCYx(60);
		trV_isp2=1;
		anV_isp2=1;
		Delay100TCYx(30);

		//U_CL_isp2  ����������
		op_bp=U_V_isp2;tst_AN_X_h();//AN17
		U_CL_isp2=ADRESH;
		if(U_CL_isp2>30)fConfig_t|=0x2;
		anV_isp2=0;
		kV_isp2=0;trV_isp2=0;	

		Delay10KTCYx(5);
		tst_pr_stanby();

		kV_knd1=1; trV_knd1=0; 
		Delay100TCYx(60);
		trV_knd1=1; 
		anV_knd1=1;
		Delay100TCYx(30);

		//U_CL_knd1  ����������
		op_bp=U_V_knd1;tst_AN_X_h();//AN8
		U_CL_knd1=ADRESH;
			if(U_CL_knd1>30)fConfig_t|=0x4;
		anV_knd1=0;
		kV_knd1=0; trV_knd1=0;
		}
	else  // no fSTANBY
		{
//��������� ������������
		if(U_pr2>60)	
			{
			kV_isp1=1;trV_isp1=0;	
			Delay10KTCYx(1);
			trV_isp1=1;
			anV_isp1=1;
			Delay10KTCYx(1);
			//U_CL_isp1  ����������
			op_bp=U_V_isp1;tst_AN_X_h();//
			U_CL_isp1=ADRESH;
			if(U_CL_isp1>30)fConfig_t|=0x1;
			anV_isp1=0;
			kV_isp1=0;trV_isp1=0;	
			Delay10KTCYx(1);
			kV_isp1=0;trV_isp1=0;	

			kV_knd2=1;trV_knd2=0; 
			Delay10KTCYx(1);
			trV_knd2=1; 
			anV_knd2=1;
			Delay10KTCYx(1);
			//U_CL_knd2  ����������
			op_bp=U_V_knd2;tst_AN_X_h();//
			U_CL_knd2=ADRESH;
 			if(U_CL_knd2>30)fConfig_t|=0x8;
			anV_knd2=0;
			kV_knd2=0; trV_knd2=0; 
			Delay10KTCYx(1);
			kV_knd2=0; trV_knd2=0; 
			}

		if(U_pr1>60)	
			{
			kV_isp2=1;trV_isp2=0;	
			Delay10KTCYx(1);
			trV_isp2=1;	
			anV_isp2=1;
			Delay10KTCYx(1);
			//U_CL_isp2  ����������
			op_bp=U_V_isp2;tst_AN_X_h();//
			U_CL_isp2=ADRESH;
			if(U_CL_isp2>30)fConfig_t|=0x2;
			anV_isp2=0;
			kV_isp2=0;trV_isp2=0;	
			Delay10KTCYx(1);
			kV_isp2=0;trV_isp2=0;	

			kV_knd1=1; trV_knd1=0; 
			Delay10KTCYx(1);
			trV_knd1=1; 
			anV_knd1=1;
			Delay10KTCYx(1);
			//U_CL_knd1  ����������
			op_bp=U_V_knd1;tst_AN_X_h();//AN8
			U_CL_knd1=ADRESH;
 			if(U_CL_knd1>30)fConfig_t|=0x4;
			anV_knd1=0;
			kV_knd1=0; trV_knd1=0;
			Delay10KTCYx(1);
			kV_knd1=0; trV_knd1=0;
			}
		}
 
fConfig_t = fConfig_t|fConfig;

if(cConfig_t4)fConfig_t = 0x0f;

		k_line_adr=0x28;
		cSOST_UPR1=0xff;
		cSOST_UPR2=0xff;
		cSOST_UPR3=0xff;
		cUPR_BT=0xff;

		if(fConfig_t==0x02)//2-� �������� 2-�� ���������� 1 �����
			{
			k_line_adr=0x29;
			cSOST_UPR1=0xf0;
			cSOST_UPR2=0xff;
			cSOST_UPR3=0x43;
			cUPR_BT=0xf2;
			}
		else if(fConfig_t==0x01)//2-� �������� 2-�� ���������� 1 �����
			{
			k_line_adr=0x29;
			cSOST_UPR1=0xf3;
			cSOST_UPR2=0xff;
			cSOST_UPR3=0x10;
			cUPR_BT=0xf1;
			}
		else if(fConfig_t==0x03)//2-� �������� 2-�� ���������� 2 �����a
			{
			k_line_adr=0x29;
			cSOST_UPR1=0xf3;
			cSOST_UPR2=0xff;
			cSOST_UPR3=0x53;
			cUPR_BT=0xf3;
			}
		else if(fConfig_t==0x06)//1-� ��������  2 ������
			{
			k_line_adr=0x28;
			cSOST_UPR1=0xfc;
			cSOST_UPR2=0xff;
			cSOST_UPR3=0xf3;
			cUPR_BT=0xf6;
			}
		else fConfig_t=0x0f;
//
	if(fH_def_12)
		{
		k_line_adr=0x29;
		cSOST_UPR1=0xff;
		cSOST_UPR2=0xff;
		cSOST_UPR3=0xff;
		cUPR_BT=0xf3;
		fConfig_t=0x03;
		}

	if(fConfig_t&0xd)f_standart=1;
	else f_standart=0;

	trON_AD=0;ON_AD=1;Nop();Nop();
	trON_AD=1;Nop();Nop();
	if(ON_ADp)
		{
		f_davl_an=0;//��� ������ ���������� (��������� ���)
		ANSELB &= 0xfd; //RB1
		}
	else 
		{
		f_davl_an=1;// ����������
		ANSELB |= 0x02; //RB1
		}

	trON_AD=0;ON_AD=0;



	if((fConfig_t&0x10)==0)
		{
		trON_CNDL=0;ON_CNDL=0;
		Nop();
		trON_CNDL=1;
		Delay100TCYx(30);
		if(ON_CNDLp){DOP_MODUL=0x1;on_cndl=1;}

		trON_CNDL=0;ON_CNDL=1;
		Delay100TCYx(30);
		trON_CNDL=1;
		Delay100TCYx(50);
		if(!ON_CNDLp){DOP_MODUL=0x1;trON_CNDL=1;}
	//	else {trON_CNDL=0;ON_CNDL=0;DOP_MODUL=0;}
		}
//
DOP_MODUL = 0;

	if(((fConfig_t&0x10)==0)&&(DOP_MODUL==0)) //������ ������������
		{
		trON_CNDL=1;
		Nop();Nop();Nop();Nop();Nop();
		if(!ON_CNDLp)
			{
			kC_isp2=1;Nop();Nop();Nop();
			if(ON_CNDLp){DOP_MODUL=0x0;on_cndl=0;fConfig_t|=0x10;f_klp_cmp=1;}
			kC_isp2=0;
			}
		}

//	if(((fConfig_t&0x10)==0))
//		{
		trRC2=0;kRC2=1;
		Nop();Nop();Nop();Nop();Nop();
		trRC2=1;fH_def=0;
		Nop();Nop();Nop();Nop();Nop();

		if(!kRC2p)
			{
			fH_def=1;
			}
		Nop();
//		}
	if(fH_def_12)fH_def=0;	

}


//#####################################################
//***********************************************
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void tst_pr_stanby_rot(void)
	{
	for(iu=0;iu<60;iu++)
		{
		buf_Upr_rt[iu]=0;
		ji=0;
		}

	for(iu=0;iu<30;iu++)
		{
		tst_U_pr1();
		sU_pr1_s=sU_pr1;
		buf_Upr_rt[ji++]=sU_pr1;
		Delay100TCYx(3);
		tst_U_pr1();
		buf_Upr_rt[ji++]=sU_pr1;

//		Delay100TCYx(3);
		if(fU_24)
			{			
			Nop();
			if((sU_pr1<sU_pr1_s)&&(sU_pr1<130)&&(sU_pr1_s<160))
//			if((sU_pr1<sU_pr1_s)&&(sU_pr1<170)&&(sU_pr1_s<200)&&(sU_pr1>100))
//			if((sU_pr1>(sU_pr1_s+6))&&(sU_pr1>90)&&(sU_pr1_s>70)&&(sU_pr1<140))
				{
				Nop();
				Nop();
				Nop();
				break;
				}
			}
		}
	}



//#####################################################
//***********************************************
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void tst_pr_stanby(void)
	{
	for(iu=0;iu<60;iu++)
		{
		buf_Upr[iu]=0;
		ji=0;
		}

	for(iu=0;iu<30;iu++)
		{
		tst_U_pr1();
		sU_pr1_s=sU_pr1;
		buf_Upr[ji++]=sU_pr1;
		Delay100TCYx(3);
		tst_U_pr1();
		buf_Upr[ji++]=sU_pr1;

//		Delay100TCYx(3);
		if(fU_24)
			{			
			Nop();
//			if((sU_pr1<sU_pr1_s)&&(sU_pr1<140)&&(sU_pr1_s<160)&&(sU_pr1>60))
//			if((sU_pr1<sU_pr1_s)&&(sU_pr1<170)&&(sU_pr1_s<200)&&(sU_pr1>100))
			if((sU_pr1>(sU_pr1_s+6))&&(sU_pr1>90)&&(sU_pr1_s>70)&&(sU_pr1<180))
				{
				Nop();
				Nop();
				Nop();
				break;
				}
			}
		else
			{
			Nop();
			if((sU_pr1>(sU_pr1_s+6))&&(sU_pr1>90)&&(sU_pr1_s>70)&&(sU_pr1<140))
				{
				Nop();
				Nop();
				Nop();
				break;
				}
			}

		}
	Nop();
	Nop();
	Nop();
	}
