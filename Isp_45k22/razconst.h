/*
//синий средний временный
#define P_mid_c_17 133
#define P_mid_c_14 112 
#define P_mid_h_26 196
#define P_mid_h_23 178
#define P_max_32   238
#define P_max_28   214
#define P_min_01    10
*/
//красный первый и будущий
#define P_mid_c_17 120
#define P_mid_c_14 102 
#define P_mid_h_26 178
#define P_mid_h_23 158
#define P_max_32   214
#define P_max_28   194
#define P_min_01    19

//

#define cU_vent_kz_24 160
#define cU_vent_kz 30 //100

#define cU_vent_kz_st_24 15
#define cU_vent_kz_st 30

#define cU_knd_kz_24 80
#define cU_knd_kz 30

#define cU_knd_kz_st_24 30
#define cU_knd_kz_st 30

#define cRAZG_isp  25
#define cRAZG_isp_24  30

#define cRAZG_knd  15
#define cRAZG_knd_24  18


#define SOST_UPR1 tSOST_UPR1.bits5

#define zmk_V_isp1  tSOST_UPR1.tzmk_V_isp1
#define obr_V_isp1 tSOST_UPR1.tobr_V_isp1
#define zmk_V_knd1 tSOST_UPR1.tzmk_V_knd1
#define obr_V_knd1 tSOST_UPR1.tobr_V_knd1
#define zmk_C_def tSOST_UPR1.tzmk_C_def
#define obr_C_def tSOST_UPR1.tobr_C_def
#define zmk_C_con tSOST_UPR1.tzmk_C_con
#define obr_C_con tSOST_UPR1.tobr_C_con

#define zmk_H_def1 tSOST_UPR1.tzmk_V_knd1
#define obr_H_def1 tSOST_UPR1.tobr_V_knd1
#define zmk_H_def2 tSOST_UPR3.tzmk_V_knd2
#define obr_H_def2 tSOST_UPR3.tobr_V_knd2


#define SOST_UPR_dop tSOST_UPR_dop.bits5

#define zmk_C_isp1 tSOST_UPR_dop.tzmk_C_isp1
#define obr_C_isp1 tSOST_UPR_dop.tobr_C_isp1
#define zmk_C_isp2 tSOST_UPR_dop.tzmk_C_isp2
#define obr_C_isp2 tSOST_UPR_dop.tobr_C_isp2
#define zmk_H_def tSOST_UPR_dop.tzmk_H_def
#define obr_H_def tSOST_UPR_dop.tobr_H_def



#define SOST_UPR2 tSOST_UPR2.bits6

#define zmk_COMP  tSOST_UPR2.tzmk_COMP
#define obr_COMP tSOST_UPR2.tobr_COMP
#define zmk_Comp  tSOST_UPR2.tzmk_COMP
#define obr_Comp tSOST_UPR2.tobr_COMP

#define no_U_pr1 tSOST_UPR2.tno_U_pr1
#define no_U_pr2 tSOST_UPR2.tno_U_pr2
#define zmk_T_isp tSOST_UPR2.tzmk_T_isp
#define obr_T_isp tSOST_UPR2.tobr_T_isp
#define zmk_T_air tSOST_UPR2.tzmk_T_air
#define obr_T_air tSOST_UPR2.tobr_T_air


#define SOST_UPR3 tSOST_UPR3.bits7

#define zmk_V_isp2  tSOST_UPR3.tzmk_V_isp2
#define obr_V_isp2 tSOST_UPR3.tobr_V_isp2
#define zmk_V_knd2 tSOST_UPR3.tzmk_V_knd2
#define obr_V_knd2 tSOST_UPR3.tobr_V_knd2
#define blk_V_isp1 tSOST_UPR3.tblk_V_isp1
#define blk_V_knd1 tSOST_UPR3.tblk_V_knd1
#define blk_V_isp2 tSOST_UPR3.tblk_V_isp2
#define blk_V_knd2 tSOST_UPR3.tblk_V_knd2


//#define zmk_V_isp3  tsDAT_BIT.tzmk_V_isp3
//#define obr_V_isp3 tsDAT_BIT.tobr_V_isp3
//#define blk_V_isp3 tsDAT_BIT.tblk_V_isp3



#define uUPR_BT tuUPR_BT.bits8

#define uV_isp1 tuUPR_BT.tuV_isp1
#define uV_isp2 tuUPR_BT.tuV_isp2
#define uV_knd1 tuUPR_BT.tuV_knd1
#define uV_knd2 tuUPR_BT.tuV_knd2
//
#define uH_def1 tuUPR_BT_dop.tuH_def1
#define uH_def2 tuUPR_BT_dop.tuH_def2


#define uV_isp3 tuUPR_BT.tuV_isp3	

#define uC_def tuUPR_BT.tuC_def
#define uC_con tuUPR_BT.tuC_con
#define uComp tuUPR_BT.tuCOMP       
#define uCOMP tuUPR_BT.tuCOMP      

#define uUPR_BT_dop tuUPR_BT_dop.bits8

#define uC_isp1 tuUPR_BT_dop.tuC_isp1
#define uC_isp2 tuUPR_BT_dop.tuC_isp2
#define uH_def tuUPR_BT_dop.tuH_def
 

#define suUPR_BT tsuUPR_BT.bits8

#define suV_isp1 tsuUPR_BT.tsuV_isp1
#define suV_isp2 tsuUPR_BT.tsuV_isp2
#define suV_knd1 tsuUPR_BT.tsuV_knd1
#define suV_knd2 tsuUPR_BT.tsuV_knd2

#define suV_isp3 tsuUPR_BT.tsuV_isp3	

#define suC_def tsuUPR_BT.tsuC_def
#define suC_con tsuUPR_BT.tsuC_con
#define suComp tsuUPR_BT.tsuCOMP       
#define suCOMP tsuUPR_BT.tsuCOMP       

#define sDAT_BIT tsDAT_BIT.bits9

#define fSTANBY tsDAT_BIT.tfSTANBY
#define fU_24   tsDAT_BIT.tfU_24

#define obr_T_cmp  tsDAT_BIT.tobr_T_cmp
#define zmk_T_cmp  tsDAT_BIT.tzmk_T_cmp




#define kV_isp1 LATBbits.LATB3
#define trV_isp1 TRISBbits.TRISB3
#define anV_isp1 ANSELBbits.ANSB3

#define kV_isp2 LATAbits.LATA0
#define trV_isp2 TRISAbits.TRISA0
#define anV_isp2 ANSELAbits.ANSA0

#define kV_knd1 LATAbits.LATA1
#define trV_knd1 TRISAbits.TRISA1
#define anV_knd1 ANSELAbits.ANSA1

#define kV_knd2 LATBbits.LATB2
#define trV_knd2 TRISBbits.TRISB2
#define anV_knd2 ANSELBbits.ANSB2

//
#define kH_def1 LATAbits.LATA1
#define trH_def1 TRISAbits.TRISA1
#define anH_def1 ANSELAbits.ANSA1

#define kH_def2 LATBbits.LATB2
#define trH_def2 TRISBbits.TRISB2
#define anH_def2 ANSELBbits.ANSB2




#define kC_def LATDbits.LATD3
#define trC_def TRISDbits.TRISD3
#define anC_def ANSELDbits.ANSD3

#define kC_con LATCbits.LATC4
#define trC_con TRISCbits.TRISC4
#define anC_con ANSELCbits.ANSC4

#define kComp LATDbits.LATD2     
#define kCOMP LATDbits.LATD2      

#define trComp TRISDbits.TRISD2      
#define trCOMP TRISDbits.TRISD2    
#define anComp ANSELDbits.ANSD2
  

#define kC_isp1 LATCbits.LATC3
#define trC_isp1 TRISCbits.TRISC3

#define kC_isp2 LATDbits.LATD0
#define trC_isp2 TRISDbits.TRISD0

#define	U_isp1  15
#define	U_isp2  20

#define	U_V_isp1  9 //RB3 K1

#define	U_V_isp2  0  //RA0 K2

#define	U_V_knd1  1  //RA1 K3

#define	U_V_knd2  8  //RB2 K4

#define	U_def  23
#define	U_con  16
#define	U_comp  22

#define	U_h_def  3
#define	U_h_def1  1
#define	U_h_def2  8



#define fl 		u1.ftl
#define fl_end  u1.ftl_end
#define FCL01	u1.tFCL01
#define fl_Kline	u1.tfl_Kline
#define f_clr_err u1.tf_clr_err
#define FCL05s u1.tFCL05s
#define FCL1s	u1.tFCL1s
#define fl_01	u2.tfl_01
#define F_MEN	u2.tF_MEN
#define fl_30s	u2.tfl_30s
#define No_clock u2.tNo_clock
#define On_st 	u2.tOn_st
#define adr	w1.tadr
#define kom w1.tkom
#define etalon w1.tetalon
#define FCL1m	u2.tFCL1m

#define k_door tsDAT_BIT.tdoor

#define	F_MIG   F2.tF_MIG




#define	K1 LATBbits.LATB1
#define	K1p PORTBbits.RB1
#define	trK1 TRISBbits.TRISB1

#define	K2 LATBbits.LATB0
#define	K2p PORTBbits.RB0
#define	trK2 TRISBbits.TRISB0

#define	K3 LATDbits.LATD5
#define	K3p PORTDbits.RD5
#define	trK3 TRISDbits.TRISD5

//new
#define TSTL LATAbits.LATA4  
#define trTSTL TRISAbits.TRISA4

//AIR OTOP

#define	REZIST LATEbits.LATE2
#define	trREZIST TRISEbits.TRISE2
#define	ON_OTOP_TST  LATEbits.LATE2
#define	ON_OTOP_TSTp  PORTEbits.RE2

#define	ON_OTOP LATCbits.LATC0
#define	trON_OTOP TRISCbits.TRISC0

#define	SVD_OTOP LATAbits.LATA6
#define	SVD_OTOPp PORTAbits.RA6
#define	trSVD_OTOP TRISAbits.RA6


///
#define	ON_AD LATAbits.LATA5
#define	ON_ADp PORTAbits.RA5
#define	trON_AD TRISAbits.TRISA5

//
#define	OUT_BUD LATEbits.LATE1
#define	trOUT_BUD TRISEbits.TRISE1

#define	DO_CMP LATEbits.LATE0
#define	DO_CMPp PORTEbits.RE0
#define	trDO_CMP TRISEbits.TRISE0

//
#define	ON_CNDL LATCbits.LATC1
#define	trON_CNDL TRISCbits.TRISC1
#define	ON_CNDLp PORTCbits.RC1


#define	tst_ON LATBbits.LATB4
#define	tr_tst_ON TRISBbits.TRISB4


// Нагрев поддона
#define kH_def LATAbits.LATA3
#define trH_def TRISAbits.TRISA3
#define anH_def ANSELAbits.ANSA3

#define kRC2 LATCbits.LATC2
#define trRC2 TRISCbits.TRISC2
#define kRC2p PORTCbits.RC2








