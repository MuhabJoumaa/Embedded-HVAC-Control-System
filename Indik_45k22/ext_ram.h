extern union {
	struct	{unsigned char adr_ee_wr_l,adr_ee_wr_h;};
	unsigned int adrEEPROM_wr;
	}w8;
extern union {
	struct	{unsigned char adr_ee_rd_l,adr_ee_rd_h;};
	unsigned int adrEEPROM_rd;
	}w9;

extern rom const far unsigned char Znakogenerator[];

extern union {
	struct	{unsigned char tadr,tkom;};
	unsigned int tetalon;
	}w1;

extern void fconw (void),rconw (void);
extern void OpenEE (void);
extern void Clr_disp (void);

extern unsigned int *blozu;
extern unsigned int adres,timer,k,etalon,ij;
extern unsigned char kom,adr,oper,kol,op_b,zOPER,op;
extern union	{ struct {
			        unsigned :1;
			        unsigned tfAVR_LIN:1;//
			        unsigned tfAVR_LIN_TAB:1;//
			        unsigned tF1m:1;
			        unsigned :1;
			        unsigned :1;
			        unsigned :1;
			        unsigned tFCL1s:1;        
		         };
 unsigned char bits1;} u1;	
extern union	{ struct {
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
extern union	{ struct {
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
extern union	{ struct {
			        unsigned tfRDWR_Q:1;
			        unsigned tfZMK_COMP:1;
			        unsigned tfOBRV_COMP:1;
			        unsigned tfLOAD:1;
			        unsigned tavrLOAD:1;
			        unsigned tfEQTIME:1;
			        unsigned tfLDREG:1;
			        unsigned tNomer_set:1;        
		         };
unsigned char bits3;} u3;
extern union	{ struct {
			        unsigned tfOTKL:1;
			        unsigned tfELAVR:1;
			        unsigned tfaONOFF:1;
			        unsigned tf_AVRSTR:1;
			        unsigned tfBUZ:1;
			        unsigned tfELOBR:1;
			        unsigned tfELZMK:1;
			        unsigned tfAVR_SUM:1;        
		         };
unsigned char bits4;} u4;



extern unsigned char znak,razr1,razr2,razr3,razr4;

extern unsigned int ptrindex,conwt,ptb,ptd,z;
extern unsigned char mask[8],i,j;
extern unsigned char popa,knop,TIMKN,t_kl,KNOPKA,out_men,CLOC1s;
extern unsigned char kom,adr,oper,kol,op_b,zOPER,op,kolpar,kodusl,kol_mask,fl_sovp;
extern unsigned char blok_fl;
extern union {unsigned int w; unsigned char by[2];}kod_sim;
extern unsigned char bufferSim[12];
extern unsigned char x,y,stroka,simvol,f,bank,eercode,KP,kn1,kn,l;
extern union{ unsigned int w; unsigned char by[2]; }ee;
extern unsigned int adrEEPROM;
extern unsigned int PAGE_EE,GR_CUR;
extern unsigned char INDEX_EE,popa1;
extern unsigned char lin_in[8],lin_out,buf,sZADT,tOPER1,tOPER2,tTIMER1,tTIMER2;
extern unsigned char tONDEF,tENDDEF;
extern unsigned char T_air,T_isp,T_kmp,T_set,DAT_BIT,SOST_UPR,UPR_BT;
extern unsigned char T_air_dpl,T_air_dmn,dT_GIST,F3,U_nap;
extern unsigned char *ptr,kn_schet,tREPIT,rrr,gist1;
extern rom far unsigned char *uk;
extern unsigned char sT_air,sT_isp,sT_kmp,sU_nap;
extern unsigned char tT_air,tT_isp,tT_kmp,tU_nap;
extern unsigned char nt,T_air_dpl_a,T_air_dmn_a;
extern unsigned char tMIN5,MINUTE;
extern unsigned char fRDWR_M,fRDWR_B;
extern unsigned char rMINUTE,rHOUR,rDATE,rMONTH,nSTEP;
extern unsigned char tSECCOM,rtKMPm,rtKMPh_l,rtKMPh_h;
extern unsigned char sMINUTE,sHOUR,sDATE;
extern unsigned char SECOND,MINUTE,HOUR,DAY,DATE,MONTH,YEAR;
extern unsigned char reg_LOAD;
extern unsigned char NCAR_S,NCAR_D,NCAR_E;
extern unsigned char BankEE,F4,F5;
extern unsigned char summa,control;
extern unsigned char bufLOAD[];
extern unsigned char ind_cln,tLIN,t_TDEF;
extern unsigned char kontrast;
extern unsigned char I_CL1,I_CL2,SUMMA;

extern unsigned char GDI1[15];
extern unsigned char GDI2[15];
extern unsigned char *tar;
extern union{ unsigned int w; unsigned char by[2]; }u;	
extern unsigned char GDU1[15],GDU2[15];
extern unsigned char avrIC,T_blk,sT_blk,tT_blk;
extern rom unsigned char  *tarrom;
extern unsigned char f_per_m2,t_per_m2,f_m2_n;
extern unsigned char f_per_m1,t_per_m1,f_m1_n,F1;
extern unsigned char f_zam_m1,f_zam_m2,f_start_m1,f_start_m2;
extern unsigned char f_rele,F6,f_on_t;
extern unsigned char i_lin,j_lin,f_st_lin,f_byte_lin;
extern unsigned char l_bits[80],l_paus[80];
extern unsigned char ir_lin,jr_lin,dlina;
extern union { unsigned int wd; struct { char l, h; };}adrs;

extern unsigned char sdvig,msk;
extern unsigned char sim_ozu;
extern unsigned int tmp;
extern unsigned char rtKMPh_l_1,rtKMPh_l_2,rtKMPh_h_1,rtKMPh_h_2;
extern unsigned char rtKMPh_h_3;
extern unsigned char t_l,t_h;

extern unsigned char se_rtKMPm,se_rtKMPh_l,se_rtKMPh_h;
extern unsigned char s_rtKMPm,f_new_mtch,op_b_ee;



