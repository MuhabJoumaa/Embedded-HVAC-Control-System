#define b TBLPTR
//
#pragma udata sect001 = 0x60
unsigned char stPORTA,stPORTB;
unsigned char stPORTC,stPORTD,stPORTE;
unsigned char tOFF_A,inc_t,ti_AD2;
unsigned char tWait_20m,tPaus_20m;
//
#pragma udata sect0 = 0x70
unsigned char knop,t_kl,CLOC_04s;
//unsigned char T2_air,T2_isp,U_pr3;
unsigned char st_kl,Bright;
unsigned char uSOST_UPR4,uSOST_UPR5,sZADT2;
unsigned char stroka,simvol,KNOPKA,zOPER;
unsigned char T_air,T_isp,tON_OFF_2h,tON_OFF;
//
#pragma udata sect01 = 0x80
union	{ struct {
			        unsigned fONLY_A:1;
			        unsigned fCOLD:1;//
			        unsigned fHOT_COLD:1;//
			        unsigned tfON_STANB:1;
			        unsigned tfSYN_V_ISP:1;
			        unsigned fAUTO:1;
			        unsigned tfONDEFR:1;
			        unsigned fHOTDO:1;        
		         };
unsigned char bits19;} blok_fl;

unsigned char UPR_BT,DAT_BIT;

union	{ struct {
			        unsigned tfzmk_V_isp1:1;
			        unsigned tfobr_V_isp1:1;
			        unsigned tfzmk_V_knd1:1;
			        unsigned tfobr_V_knd1:1;
			        unsigned tfzmk_C_def:1;
			        unsigned tfobr_C_def:1;
			        unsigned tfzmk_C_con:1;
			        unsigned tfobr_C_con:1;
		         };
unsigned char bits3;} SOST_UPR1;//0x3


unsigned char F1,F2,F3,F4,rbit;//bits
union	{ struct {
			        unsigned tmulti1:1;
			        unsigned tfAVR_LIN:1;//
			        unsigned tfONDEFR_R:1;//
			        unsigned tF1m:1;
			        unsigned tfTECH_DLT:1; //tcfPROG
			        unsigned tfEQTIMES:1;
			        unsigned tfIND_tC:1;
			        unsigned tFCL1s:1;        
		         };
unsigned char bits1;} u1;   //0x9


union	{ struct {
			        unsigned tf_no_work:1;
			        unsigned tf_stop:1;//
			        unsigned tf_no_stop:1;//
			        unsigned tf_no_klap:1;
			        unsigned tf_no_temp:1;
			        unsigned tf_no_comp:1;
			        unsigned tf_blk_vnt:1;
			        unsigned tfNO_OFF:1;
		         };
unsigned char bits11;}	fAVR_IND;//A


union	{ struct {
			        unsigned tfzmk_V_isp2:1;
			        unsigned tfobr_V_isp2:1;
			        unsigned tfzmk_V_knd2:1;
			        unsigned tfobr_V_knd2:1;
			        unsigned tfblk_V_isp1:1;
			        unsigned tfblk_V_knd1:1;
			        unsigned tfblk_V_isp2:1;
			        unsigned tfblk_V_knd2:1;
		         };
unsigned char bits2;} SOST_UPR3;//0xB

union	{ struct {
			        unsigned tfOTKL:1;
			        unsigned tfSLEEP:1;
			        unsigned tfaONOFF:1;
			        unsigned tf_AVRSTR:1;
			        unsigned tfBUZ:1;
			        unsigned tmulti2:1;
			        unsigned tf_multi2_lin:1;
			        unsigned tf_H_def:1;        
		         };
unsigned char bits4;} u4;

unsigned char F5;//D

union	{ struct {
			        unsigned tuC1_isp:1;
			        unsigned tuC2_isp:1;
			        unsigned tTm_C1_isp:1;
			        unsigned tTm_C2_isp:1;
			        unsigned tzmk_C1_isp:1;
			        unsigned tobr_C1_isp:1;
			        unsigned tzmk_C2_isp:1;
			        unsigned tobr_C2_isp:1;
		         };
unsigned char bits5;} SOST_UPR_dop;//E

union	{ struct {
			        unsigned tfzmk_COMP:1;
			        unsigned tfobr_COMP:1;
			        unsigned tfno_U_pr1:1;
			        unsigned tfno_U_pr2:1;
			        unsigned tfzmk_T_isp:1;
			        unsigned tfobr_T_isp:1;
			        unsigned tfzmk_T_air:1;
			        unsigned tfobr_T_air:1;
		         };
unsigned char bits9;} SOST_UPR2;//0xF
//****************************************************

union	{ struct {
			        unsigned tuC1_isp:1;
			        unsigned tuC2_isp:1;
			        unsigned tTm_C1_isp:1;
			        unsigned tTm_C2_isp:1;
			        unsigned tzmk_C1_isp:1;
			        unsigned tobr_C1_isp:1;
			        unsigned tzmk_C2_isp:1;
			        unsigned tobr_C2_isp:1;
		         };
unsigned char bits5;} tuSOST_UPR_dop;//2


union	{ struct {
			        unsigned tfzmk_C_isp1:1;
			        unsigned tfobr_C_isp1:1;
			        unsigned :1;
			        unsigned tfzmk_V_isp3:1;
			        unsigned tfobr_V_isp3:1;
			        unsigned tfblk_V_isp3:1;
			        unsigned tfzmk_C_isp2:1;
			        unsigned tfobr_C_isp2:1;
		         };
unsigned char bits3;} SOST_UPR4;//

unsigned char sSOST_UPR2,sSOST_UPR3;

unsigned char tUPR_BT,sUPR_BT,rs_mes_t;
//
union	{ struct {
			        unsigned tzmk_V_isp1:1;
			        unsigned tobr_V_isp1:1;
			        unsigned tzmk_V_knd1:1;
			        unsigned tobr_V_knd1:1;
			        unsigned tzmk_C_def:1;
			        unsigned tobr_C_def:1;
			        unsigned tzmk_C_con:1;
			        unsigned tobr_C_con:1;
		         };
unsigned char bits5;} tuSOST_UPR1;//2

union	{ struct {
			        unsigned tzmk_COMP:1;
			        unsigned tobr_COMP:1;
			        unsigned tno_U_pr1:1;
			        unsigned tno_U_pr2:1;
			        unsigned tzmk_T_isp:1;
			        unsigned tobr_T_isp:1;
			        unsigned tzmk_T_air:1;
			        unsigned tobr_T_air:1;
		         };
unsigned char bits6;} tuSOST_UPR2;//0x3

union	{ struct {
			        unsigned tzmk_V_isp2:1;
			        unsigned tobr_V_isp2:1;
			        unsigned tzmk_V_knd2:1;
			        unsigned tobr_V_knd2:1;
			        unsigned tblk_V_isp1:1;
			        unsigned tblk_V_knd1:1;
			        unsigned tblk_V_isp2:1;
			        unsigned tblk_V_knd2:1;
		         };
unsigned char bits7;} tuSOST_UPR3;//0x4



union	{ struct {
			        unsigned tuV_isp1:1;
			        unsigned tuV_isp2:1;
			        unsigned tuV_knd1:1;
			        unsigned tuV_knd2:1;
			        unsigned tuH_def:1;
			        unsigned tuC_def:1;
			        unsigned tuC_con:1;
			        unsigned tuCOMP:1;        
		         };
unsigned char bits8;} tuUPR_BT;//0x4
//


//
unsigned char U_nap;
unsigned char T_air_dpl,T_air_dmn;
unsigned char T_air_dpl_a,T_air_dmn_a;
unsigned char tONCOLD5,tONCOLD;
//
union	{ struct {
			        unsigned ftl:1;
			        unsigned tF_MEN:1;
			        unsigned tno_repit:1;
			        unsigned tNo_clock:1;
			        unsigned tOn_st:1;
			        unsigned tFCL1m:1;
			        unsigned tfknop48:1;
			        unsigned ftl_end:1;        
		         };
unsigned char bits2;} u2;

//
unsigned int S1OZSPV,S1OZREJ,S1OZUPR,S1OZOTOP;
unsigned char CLOC1m,CLOC1s;
//EEPROM
//unsigned char kontrast;//
unsigned char tPER_DEF;   //период авт. вкл. оттайки
unsigned char tDEF;		  //длительность оттайки
unsigned char T_FIN_DEF;  //темп. окончания оттайки
unsigned char tWAT_DEF;	  //время стекания воды при оттайки
unsigned char T_START_HOT; //темп. старта отопления
unsigned char t_FIN_HOT;  //защитн. интервал отопления
//unsigned char t_OFF_DOOR; //защитн. интервал отключ.при открытых дверях
unsigned char dT_GIST;	 //гистерезис по температуре
unsigned char T_SET_COLD_MIN; //минимальн. знач. температуры
unsigned char T_SET_HOT_MAX;  //максимальн. знач. температуры
//unsigned char T_MAX_COM;//макс.значение темп.компресора
//unsigned char dT_COMP;	 //гистерезис по температуре компрессора
unsigned char T_START_HOT2;	 //гистерезис по повторному старту отопления
//unsigned char U_nap12;//напряжение отключения нагрузок 12 В
//unsigned char U_nap24;//напряжение отключения нагрузок 24В
//
unsigned char sZADT;
unsigned char TEM_SET;
unsigned char t_START_HOT; //время старта отопления
unsigned char s_blok_fl;
//

unsigned char tONDEF,tENDDEF,tENDHOT,t_X_DAVL;
//
union {
	struct	{unsigned char adr_ee_wr_l,adr_ee_wr_h;};
	unsigned int adrEEPROM_wr;
	}w8;
union {
	struct	{unsigned char adr_ee_rd_l,adr_ee_rd_h;};
	unsigned int adrEEPROM_rd;
	}w9;
//
unsigned char rtKMPh_l,rtKMPh_h,rtKMPm;

//
//unsigned char rMINUTE,rHOUR,rDATE,rMONTH;

unsigned char rT_air,rT_isp;
unsigned char rtKMP;

unsigned char tMIN5,nSTEP;
unsigned char tSECCOM;
unsigned char tSECVKL;
unsigned char sONOFF;
unsigned char tUPR_BT2,sUPR_BT2;
// для регистратора
unsigned char tOBR,tD_AVR;
unsigned char sI_CL1,OTOP_SLEEP;
unsigned char tTIMER2;
unsigned char T_air_dpl_o;
unsigned char t_OFF;
unsigned char rtKMPh_l_1,rtKMPh_l_2,rtKMPh_h_1,rtKMPh_h_2;
unsigned char rtKMPh_h_3;
unsigned char pult_m,tester_lin,sSTATUS,sSTATUS1,sSTATUS2;
unsigned char t_TDEF,U_davl;
//
unsigned char POWER_OTOP,t_WAIT_OTOP;
unsigned char zOPER_MN,zOPER_PL;
unsigned char sSTATUS_OTOP,t_WAIT_OTOP_A;
//
unsigned char s_rtKMPh_l,nom_err,tech_upr,tech_upr_dop;
unsigned char t_nom_upr,n_err_txt,n_err_bt;
unsigned char tUPR_BT_dop;

//unsigned char i_rtKMPh_l,i_rtKMPh_h,i_nom_zap;
unsigned char t_nom,t_l,t_h,z_nom_err,oT_air;
unsigned char t_OTOP_AVR;
unsigned char t_def_Visp,s_tONDEF;

unsigned char T_cmp,f_config_t,ver_sil,mUPR_BT;
unsigned char dTp,tON_VKL;


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma udata sect2 = 0x100

unsigned char U_pr1,U_pr2;

unsigned char znak,trazr1,trazr2,trazr3,trazr4;
unsigned char razr1,razr2,razr3,razr4;

unsigned char 	 p_res, L_res,p_res2, L_res2,L_out2,  
		p_out, p_out2,L_out,k_res,i_kl,L_in,L_in2,summa,cikl,ip,ir,f;

unsigned char buf,op_b2,p_in,p_in2,ip2,ir2,irr,ipp;

unsigned char com_trm,L_res;
unsigned char rs_mes_end,rs_mes_start;
unsigned char yes_tr_com,summa_tr,block_ans,rs_mes;

rom unsigned char *uk;

unsigned char buf_in[44];
unsigned char res[44];
unsigned char buf_out[18];

unsigned char I_CL_isp1,I_CL_isp2,I_CL_knd1,I_CL_knd2;
unsigned char U_CL_isp1,U_CL_isp2,U_CL_knd1,U_CL_knd2;

unsigned char sT_ISP,tT_ISP,ssT_ISP,T_ISP;
unsigned char sT_AIR,tT_AIR,iT_ISP,iT_ISP2;

unsigned char T_AIR,wT_AIR,iT_AIR,iT_AIR2;
unsigned char mT_ISP,mT_AIR,zT_ISP,zT_AIR;
unsigned char U_BS;
unsigned char tU_nap,sU_nap;
unsigned char iUPR_BT;
unsigned char KNOPKI;

unsigned char cikl_int,com_line,fl_Kline,s_com_line;
unsigned char sDAT_BIT,uUPR_BT2;
unsigned char tOPER1;

unsigned char iSOST_UPR1,iSOST_UPR2,iSOST_UPR3,iSOST_UPR_dop;
unsigned char tSOST_UPR1,tSOST_UPR2,tSOST_UPR3,tSOST_UPR_dop;

unsigned char iSOST_UPR4,iSOST_UPR5,mT_ISP2,sDAT_BIT2;
unsigned char tSOST_UPR4,tSOST_UPR5,mT_AIR2;

unsigned char t_up_isp2,t_up_knd2,t_up_isp3;

unsigned char t_st_up1,t_st_up2,t_st_up3,t_st_up_dop;

unsigned char t_blk_isp1,t_blk_isp2,t_blk_knd1,t_blk_knd2;
unsigned char t_tst_obr_i,t_tst_obr_c;

unsigned char t_zmk_Comp,t_rs_mes;
unsigned char t_zmk_def,t_zmk_con,ifAVR_IND2;
//unsigned char I_CL_DEF2,I_KL_ISP2;

unsigned char T_ISP1,T_AIR1,sDAT_BIT1,UPR_BT1;
unsigned char sZADT1,ifAVR_IND1,T_ISP2,T_AIR2;
unsigned char mSOST_UPR1,mSOST_UPR2,mSOST_UPR3;

unsigned char mDAT_BIT,mfAVR_IND1,mfAVR_IND2;
unsigned char iDAT_BIT,f_config_t2;

unsigned char tPORTA,tPORTB,tPORTC,tPORTD,tPORTE;

unsigned char t_st_up4,t_blk_isp3,fuC_con,ct_st_up;

unsigned char uUPR_STEND;

unsigned char schetcik5,f_stend_hand,utUPR_BT;
unsigned char ver_mod,rT_kmp,f_otop_lin;
unsigned char t_knd1_rot,t_knd2_rot,t_knd_rot;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
#pragma udata sect3 = 0x200

unsigned char buf_in2[50];
unsigned char res2[50];
unsigned char buf_out2[45];
unsigned char I_CL_DEF,I_CL_CON,I_CL_CMP,I_KL_ISP;
unsigned char yes_tr_com2,com_trm2,summa_tr2;
unsigned char rs_mes_end2,rs_mes_start2,summa2;
unsigned char com_line2,rs_mes2,rs_mes2_yes;
unsigned char BankEE;

unsigned int *blozu,tmr3,tmr4;
unsigned int timer,adres,k,conwt,z,tmr1,tmr2,tmr;

union {
	struct	{unsigned char tadr,tkom;};
	unsigned int tetalon;
	}w1;

unsigned char oper,kol,op_b,op,kolpar,kodusl,kol_mask,fl_sovp;
unsigned char mask[8],i,j,ij;

unsigned int *prer1[6];

unsigned int ptrindex,ptb,ptd;
unsigned char popa,TIMKN,out_men,bank,KP,kn1,kn,CLO30s;
unsigned char popa1,kn_schet,tREPIT,rrr,nt;
unsigned char tAVR_LIN,tLIN;

unsigned char SECOND,MINUTE,HOUR;
unsigned char I_CL_isp3,U_CL_isp3;
unsigned char sSOST_UPR1,stSOST_UPR1,stSOST_UPR2,nREGNES;

unsigned char se_rtKMPm,se_rtKMPh_l,se_rtKMPh_h;
unsigned char s_rtKMPm,f_new_mtch,op_b_ee,f_str_mtch;
unsigned char f_yes_mtch,sf_config_t;
unsigned char ssDAT_BIT;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
#pragma udata sect4 = 0x300
union	{ struct {
			        unsigned teblk_V_isp:1;
			        unsigned teobr_V_isp:1;
			        unsigned teblk_V_knd:1;
			        unsigned teobr_V_knd:1;
			        unsigned tezmk_C_def:1;
			        unsigned teobr_C_def:1;
			        unsigned tezmk_C_con:1;
			        unsigned teobr_C_con:1;
		         };
unsigned char bits3;} teSOST_UPR1;//0x3

union	{ struct {
			        unsigned tezmk_COMP:1;
			        unsigned teobr_COMP:1;
			        unsigned tezmk_V_isp:1;
			        unsigned tezmk_V_knd:1;
			        unsigned tezmk_T_isp:1;
			        unsigned teobr_T_isp:1;
			        unsigned tezmk_T_air:1;
			        unsigned teobr_T_air:1;
		         };
unsigned char bits3;} teSOST_UPR2;//0xF

union	{ struct {
			        unsigned teAVR_AD:1;
			        unsigned teAVR_AD2:1;
			        unsigned tezmk_AD:1;
			        unsigned teobr_AD:1;
			        unsigned teno_U_pr:1;
			        unsigned teAVR_LIN:1;//
			        unsigned tef_stop:1;//
			        unsigned tef_STANB:1;//
		         };
unsigned char bits3;} teSOST_UPR3;//0xF

union	{ struct {
			        unsigned tezmk_C_isp1:1;
			        unsigned teobr_C_isp1:1;
			        unsigned tezmk_C_isp2:1;
			        unsigned teobr_C_isp2:1;
			        unsigned tezmk_C1_isp:1;
			        unsigned teobr_C1_isp:1;
			        unsigned tezmk_C2_isp:1;
			        unsigned teobr_C2_isp:1;
		         };
unsigned char bits3;} teSOST_UPR_dop;//2

unsigned char f_wr_err,f_chng_n_err;

unsigned char s_eSOST_UPR1,s_eSOST_UPR2;
unsigned char s_eSOST_UPR3,s_eSOST_UPR_dop;

unsigned char state_reg,ee_reg,t_nom_err;

//unsigned char t_nom,t_l,t_h;
unsigned char t_sost1,t_sost2,t_sost3,t_sost_dop;
unsigned char f_config_dop,z_rtKMPh_l;
unsigned char yes_err,t_U_napr,t_U_91,t_U_92;

unsigned char t_blk_isp1_c,t_blk_isp2_c,t_blk_isp3_c;
unsigned char t_blk_knd1_c,t_blk_knd2_c;

unsigned char t_zmk_isp1_c,t_zmk_isp2_c,t_zmk_isp3_c;
unsigned char t_zmk_knd1_c,t_zmk_knd2_c;

unsigned char t_zmk_knd2,t_zmk_knd1;
unsigned char t_zmk_isp2,t_zmk_isp1,t_zmk_isp3;

unsigned char t_AD2,n_AD2;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
#pragma udata sect7 = 0x380
unsigned char buf_err[128];



#pragma udata sect5 = 0x500
unsigned char *tar;
union{ unsigned int w; unsigned char by[2]; }u;	

unsigned char avrIC,sT_blk,tT_blk,f_heat,f_heat_on;

unsigned char fAVRCOMPS,f_comp_up,U_stn;

rom unsigned char  *tarrom;

unsigned char f_per_m2,t_per_m2,f_m2_n;
unsigned char f_per_m1,t_per_m1,f_m1_n;

unsigned char f_zam_m1,f_zam_m2,f_start_m1,f_start_m2;
unsigned char f_rele,f_on_t;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
unsigned char i_lin,j_lin,ir_lin,jr_lin;
unsigned char f_st_lin,f_byte_lin,dlina;

unsigned char t_avr_comp;

union	{ struct {
			        unsigned tfl_1st:1;
			        unsigned tfl_2st:1;
			        unsigned tfl_3st:1;
			        unsigned tfl_4st:1;
			        unsigned :1;
			        unsigned :1;//
			        unsigned :1;//
			        unsigned :1;        
		         };
unsigned char bits5;} u5;

union { unsigned int wd; struct { char l, h; };}adrs;

unsigned char sdvig,msk;
unsigned char sim_ozu;
unsigned int tmp,schetcik1,schetcik2,schetcik3;

//union {unsigned int w; unsigned char by[2];}kod_sim;
//unsigned char bufferSim[12];
//unsigned char x,y,l,eercode;
//unsigned char ClockBuffer[8];
//unsigned char *ptrClockBuffer;
//union{ unsigned int w; unsigned char by[2]; }ee;
//unsigned char lin_in[10],SUMMA,lin_out;
//unsigned char *ptr,*p;
//unsigned char ind_cl,zifra,ind_clp,gist,gist1,kol_bayt;
//unsigned char sT_air,sT_isp,sT_kmp;
//unsigned char tT_air,tT_isp,tT_kmp;
//unsigned char sSECOND,MARK;
//unsigned char ssMINUTE;
//unsigned char reg_LOAD;
//unsigned char control;
//unsigned char bufLOAD[64];
//unsigned char ind_cln;
//unsigned char INDEX_EE,SEK01;
//unsigned char GDU1[15],GDU2[15];
//

