
#define b TBLPTR


#define read_tabw(e) _asm TBLRDPOSTINC _endasm\
					  *(char *)(&e)=TABLAT;\
					 _asm TBLRDPOSTINC _endasm\
					  *(char *)((char *)&e+1)=TABLAT;
#define read_tabwb(a,b) _asm TBLRDPOSTINC _endasm\
					  b=TABLAT;\
					 _asm TBLRDPOSTINC _endasm\
					  a=TABLAT;	
#define read_tab(q)	{_asm TBLRDPOSTINC _endasm\
					 q=TABLAT;}				  
#define read_tabn(w) {_asm TBLRD _endasm\
					  w=TABLAT;}

#define conb 	FSR0
#define conw 	FSR0
#define fconb()	INDF0=op_b
#define rconb()	op_b=INDF0

#define fl 		u2.ftl
#define fl_end  u2.ftl_end
#define f_H_def	u4.tf_H_def
#define FCL1s	u1.tFCL1s
//#define fl_01	u2.tfl_01
#define F_MEN	u2.tF_MEN
#define fSLEEP	u4.tfSLEEP
#define No_clock u2.tNo_clock
#define On_st 	u2.tOn_st
#define adr	w1.tadr
#define kom w1.tkom
#define etalon w1.tetalon
#define FCL1m	u2.tFCL1m
#define fknop48 u2.tfknop48
#define no_repit u2.tno_repit
#define F1m u1.tF1m
//#define fEQTIME u3.tfEQTIME
#define multi1 u1.tmulti1
#define multi2 u4.tmulti2
#define f_multi2_lin u4.tf_multi2_lin
#define fLOAD	u4.tfLOAD
//#define fl_256  u3.tfl_256
//#define fLDREG u1.tfLDREG

#define fl_1st	u5.tfl_1st
#define fl_2st	u5.tfl_2st
#define fl_3st	u5.tfl_3st
#define fl_4st	u5.tfl_4st

#define fAVR_LIN u1.tfAVR_LIN
#define fAVR_LIN_TAB u1.tfAVR_LIN_TAB
#define fIND_tC u1.tfIND_tC

#define fTECH_DLT u1.tfTECH_DLT


#define tblok_fl blok_fl.bits19
//#define fWR_EEPROM blok_fl.tfWR_EEPROM
#define fSOS_YES blok_fl.tfSOS_YES

#define fAVR_SUM u4.tfAVR_SUM

#define fONDEFR blok_fl.tfONDEFR
#define fSYN_V_ISP blok_fl.tfSYN_V_ISP

#define EETCOM_M 0xC
#define EETCOM_H 0xD
#define EETCOM_W 0xE


#define fAVRCOMP	u3.tfZMK_COMP
#define fAVRCOMPO	u3.tfOBRV_COMP

#define Int_TMR3_ON	PIE2bits.TMR3IE=1
#define Int_TMR3_OFF	PIE2bits.TMR3IE=0

#define TMR3_set		 TMR3H=0xfe; TMR3L=0x48   

#define	bl55	0



#define uUPR_BT tuUPR_BT.bits8

#define uV_isp1 tuUPR_BT.tuV_isp1
#define uV_isp2 tuUPR_BT.tuV_isp2
#define uV_knd1 tuUPR_BT.tuV_knd1
#define uV_knd2 tuUPR_BT.tuV_knd2

#define uH_def tuUPR_BT.tuH_def

#define uC_def tuUPR_BT.tuC_def
#define uC_con tuUPR_BT.tuC_con
#define uCOMP tuUPR_BT.tuCOMP       
#define uC_isp1 tuUPR_BT.tuC_con
#define uC_isp2 tuUPR_BT.tuCOMP




#define uSOST_UPR1 tuSOST_UPR1.bits5

#define zmk_V_isp1  tuSOST_UPR1.tzmk_V_isp1	//1 f_stop1
#define obr_V_isp1 tuSOST_UPR1.tobr_V_isp1	//1 f_stop1
#define zmk_V_knd1 tuSOST_UPR1.tzmk_V_knd1	//2 f_stop2
#define obr_V_knd1 tuSOST_UPR1.tobr_V_knd1	//2 f_stop2
#define zmk_C_def tuSOST_UPR1.tzmk_C_def //f_stop
#define obr_C_def tuSOST_UPR1.tobr_C_def //f_stop
#define zmk_C_con tuSOST_UPR1.tzmk_C_con //f_stop
#define obr_C_con tuSOST_UPR1.tobr_C_con	 //f_stop


#define uSOST_UPR2 tuSOST_UPR2.bits6


#define zmk_COMP  tuSOST_UPR2.tzmk_COMP	//!f_no_work,f_stop
#define obr_COMP tuSOST_UPR2.tobr_COMP	//!f_no_work,f_stop
#define no_U_pr1 tuSOST_UPR2.tno_U_pr1	//!f_no_work,f_stop
#define no_U_pr2 tuSOST_UPR2.tno_U_pr2	//!f_no_work,f_stop
#define zmk_T_isp tuSOST_UPR2.tzmk_T_isp
#define obr_T_isp tuSOST_UPR2.tobr_T_isp
#define zmk_T_air tuSOST_UPR2.tzmk_T_air
#define obr_T_air tuSOST_UPR2.tobr_T_air


#define uSOST_UPR_dop tuSOST_UPR_dop.bits5

#define uC1_isp tuSOST_UPR_dop.tuC1_isp
#define uC2_isp tuSOST_UPR_dop.tuC2_isp
#define Tm_C1_isp tuSOST_UPR_dop.tTm_C1_isp
#define Tm_C2_isp tuSOST_UPR_dop.tTm_C2_isp

#define zmk_C1_isp tuSOST_UPR_dop.tzmk_C1_isp
#define obr_C1_isp tuSOST_UPR_dop.tobr_C1_isp
#define zmk_C2_isp tuSOST_UPR_dop.tzmk_C2_isp
#define obr_C2_isp tuSOST_UPR_dop.tobr_C2_isp

#define fSOST_UPR_dop SOST_UPR_dop.bits5

#define fuC1_isp SOST_UPR_dop.tuC1_isp
#define fuC2_isp SOST_UPR_dop.tuC2_isp
#define fTm_C1_isp SOST_UPR_dop.tTm_C1_isp
#define fTm_C2_isp SOST_UPR_dop.tTm_C2_isp
#define fzmk_C1_isp SOST_UPR_dop.tzmk_C1_isp
#define fobr_C1_isp SOST_UPR_dop.tobr_C1_isp
#define fzmk_C2_isp SOST_UPR_dop.tzmk_C2_isp
#define fobr_C2_isp SOST_UPR_dop.tobr_C2_isp


#define uSOST_UPR3 tuSOST_UPR3.bits7

#define zmk_V_isp2 tuSOST_UPR3.tzmk_V_isp2	//1 f_stop1
#define obr_V_isp2 tuSOST_UPR3.tobr_V_isp2	//1 f_stop1
#define zmk_V_knd2 tuSOST_UPR3.tzmk_V_knd2	//2 f_stop2
#define obr_V_knd2 tuSOST_UPR3.tobr_V_knd2	//2 f_stop2
#define blk_V_isp1 tuSOST_UPR3.tblk_V_isp1
#define blk_V_knd1 tuSOST_UPR3.tblk_V_knd1
#define blk_V_isp2 tuSOST_UPR3.tblk_V_isp2
#define blk_V_knd2 tuSOST_UPR3.tblk_V_knd2

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define fSOST_UPR1 SOST_UPR1.bits3

#define fzmk_V_isp1 SOST_UPR1.tfzmk_V_isp1
#define fobr_V_isp1 SOST_UPR1.tfobr_V_isp1
#define fzmk_V_knd1 SOST_UPR1.tfzmk_V_knd1
#define fobr_V_knd1 SOST_UPR1.tfobr_V_knd1
#define fzmk_C_def SOST_UPR1.tfzmk_C_def
#define fobr_C_def SOST_UPR1.tfobr_C_def
#define fzmk_C_con SOST_UPR1.tfzmk_C_con
#define fobr_C_con SOST_UPR1.tfobr_C_con


#define fSOST_UPR2 SOST_UPR2.bits9

#define fzmk_COMP  SOST_UPR2.tfzmk_COMP
#define fobr_COMP SOST_UPR2.tfobr_COMP
#define fno_U_pr1 SOST_UPR2.tfno_U_pr1
#define fno_U_pr2 SOST_UPR2.tfno_U_pr2
#define fzmk_T_isp SOST_UPR2.tfzmk_T_isp
#define fobr_T_isp SOST_UPR2.tfobr_T_isp
#define fzmk_T_air SOST_UPR2.tfzmk_T_air
#define fobr_T_air SOST_UPR2.tfobr_T_air


#define fSOST_UPR3 SOST_UPR3.bits2

#define fzmk_V_isp2 SOST_UPR3.tfzmk_V_isp2
#define fobr_V_isp2 SOST_UPR3.tfobr_V_isp2
#define fzmk_V_knd2 SOST_UPR3.tfzmk_V_knd2
#define fobr_V_knd2 SOST_UPR3.tfobr_V_knd2
#define fblk_V_isp1 SOST_UPR3.tfblk_V_isp1
#define fblk_V_knd1 SOST_UPR3.tfblk_V_knd1
#define fblk_V_isp2 SOST_UPR3.tfblk_V_isp2
#define fblk_V_knd2 SOST_UPR3.tfblk_V_knd2

#define fSOST_UPR4 SOST_UPR4.bits3

#define fzmk_C_isp1 SOST_UPR4.tfzmk_C_isp1 //f_stop
#define fobr_C_isp1 SOST_UPR4.tfobr_C_isp1	 //f_stop

#define fzmk_V_isp3 SOST_UPR4.tfzmk_V_isp3
#define fobr_V_isp3 SOST_UPR4.tfobr_V_isp3
#define fblk_V_isp3 SOST_UPR4.tfblk_V_isp3

#define fzmk_C_isp2 SOST_UPR4.tfzmk_C_isp2	//!f_no_work,f_stop
#define fobr_C_isp2 SOST_UPR4.tfobr_C_isp2	//!f_no_work,f_stop



#define ifAVR_IND	fAVR_IND.bits11

#define f_no_work fAVR_IND.tf_no_work
#define f_stop 	  fAVR_IND.tf_stop
#define f_no_stop fAVR_IND.tf_no_stop
#define f_no_klap fAVR_IND.tf_no_klap
#define f_no_temp fAVR_IND.tf_no_temp
#define f_no_comp fAVR_IND.tf_no_comp
#define f_blk_vnt fAVR_IND.tf_blk_vnt
#define fNO_OFF   fAVR_IND.tfNO_OFF      


//Запись ошибок

#define eSOST_UPR1 teSOST_UPR1.bits3

#define eblk_V_isp teSOST_UPR1.teblk_V_isp
#define eobr_V_isp teSOST_UPR1.teobr_V_isp
#define eblk_V_knd teSOST_UPR1.teblk_V_knd
#define eobr_V_knd teSOST_UPR1.teobr_V_knd
#define ezmk_C_def teSOST_UPR1.tezmk_C_def
#define eobr_C_def teSOST_UPR1.teobr_C_def
#define ezmk_C_con teSOST_UPR1.tezmk_C_con
#define eobr_C_con teSOST_UPR1.teobr_C_con

#define eSOST_UPR2 teSOST_UPR2.bits3

#define ezmk_COMP  teSOST_UPR2.tezmk_COMP
#define eobr_COMP teSOST_UPR2.teobr_COMP
#define ezmk_V_isp teSOST_UPR2.tezmk_V_isp
#define ezmk_V_knd teSOST_UPR2.tezmk_V_knd
#define ezmk_T_isp teSOST_UPR2.tezmk_T_isp
#define eobr_T_isp teSOST_UPR2.teobr_T_isp
#define ezmk_T_air teSOST_UPR2.tezmk_T_air
#define eobr_T_air teSOST_UPR2.teobr_T_air

#define eSOST_UPR3 teSOST_UPR3.bits3

#define eAVR_AD teSOST_UPR3.teAVR_AD
#define eAVR_AD2 teSOST_UPR3.teAVR_AD2
#define ezmk_AD teSOST_UPR3.tezmk_AD
#define eobr_AD teSOST_UPR3.teobr_AD
#define eno_U_pr teSOST_UPR3.teno_U_pr
#define eAVR_LIN teSOST_UPR3.teAVR_LIN
#define ef_stop  teSOST_UPR3.tef_stop
#define ef_STANB teSOST_UPR3.tef_STANB

#define eSOST_UPR_dop teSOST_UPR_dop.bits3
//
#define ezmk_C_isp1 teSOST_UPR_dop.tezmk_C_isp1 
#define eobr_C_isp1 teSOST_UPR_dop.teobr_C_isp1
#define ezmk_C_isp2 teSOST_UPR_dop.tezmk_C_isp2
#define eobr_C_isp2 teSOST_UPR_dop.teobr_C_isp2
#define ezmk_C1_isp teSOST_UPR_dop.tezmk_C1_isp
#define eobr_C1_isp teSOST_UPR_dop.teobr_C1_isp
#define ezmk_C2_isp teSOST_UPR_dop.tezmk_C2_isp
#define eobr_C2_isp teSOST_UPR_dop.teobr_C2_isp






