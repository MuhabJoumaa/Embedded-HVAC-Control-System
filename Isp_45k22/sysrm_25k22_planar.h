#define b TBLPTR
//
#pragma udata sect0 = 0x60
   
unsigned char sT_ISP,tT_ISP,ssT_ISP,T_ISP;
unsigned char sT_AIR,tT_AIR,iT_ISP;

unsigned char T_AIR,wT_AIR,iT_AIR,sZADT;
unsigned char mT_ISP,mT_AIR,zT_ISP,zT_AIR;

unsigned char T_CMP,mT_CMP,iT_CMP,sT_CMP,tT_CMP;

unsigned char U_nap,U_BS;
unsigned char tU_nap,sU_nap;
unsigned char iUPR_BT;

unsigned char op_bp;
unsigned char MARK,tOPER1;

unsigned char TIMKN,CLOC1s,CLOC01;


#pragma udata sect1 = 0x80

unsigned char blok_fl[1];//0  0x80
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
unsigned char bits5;} tSOST_UPR1;//2

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
unsigned char bits6;} tSOST_UPR2;//0x3

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
unsigned char bits7;} tSOST_UPR3;//0x4


union	{ struct {
			        unsigned tuV_isp1:1;
			        unsigned tuV_isp2:1;
			        unsigned tuV_knd1:1;
			        unsigned tuV_knd2:1;
			        unsigned tuV_isp3:1;
			        unsigned tuC_def:1;
			        unsigned tuC_con:1;
			        unsigned tuCOMP:1;        
		         };
unsigned char bits8;} tuUPR_BT;//0x4

union	{ struct {
			        unsigned tsuV_isp1:1;
			        unsigned tsuV_isp2:1;
			        unsigned tsuV_knd1:1;
			        unsigned tsuV_knd2:1;
			        unsigned tsuV_isp3:1;
			        unsigned tsuC_def:1;
			        unsigned tsuC_con:1;
			        unsigned tsuCOMP:1;        
		         };
unsigned char bits8;} tsuUPR_BT;//0x4

union	{ struct {
			        unsigned :1;
			        unsigned :1;
			        unsigned :1;
			        unsigned tuH_def1:1;
			        unsigned tuH_def:1;
			        unsigned tuC_isp1:1;
			        unsigned tuC_isp2:1;
			        unsigned tuH_def2:1;        
		         };
unsigned char bits8;} tuUPR_BT_dop;//0x4

union	{ struct {
			        unsigned :1;
			        unsigned :1;
			        unsigned tzmk_H_def:1;
			        unsigned tobr_H_def:1;
			        unsigned tzmk_C_isp1:1;
			        unsigned tobr_C_isp1:1;
			        unsigned tzmk_C_isp2:1;
			        unsigned tobr_C_isp2:1;
		         };
unsigned char bits5;} tSOST_UPR_dop;//2

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//


union	{ struct {
			        unsigned ftl:1;
			        unsigned ftl_end:1;
			        unsigned tFCL01:1;
			        unsigned tfl_Kline:1;
			        unsigned tfCALC:1;
			        unsigned tf_clr_err:1;
			        unsigned tFCL05s:1;
			        unsigned tFCL1s:1;        
		         };
unsigned char bits1;} u1;

union	{ struct {
			        unsigned tfl_01:1;
			        unsigned tF_MEN:1;
			        unsigned tfl_30s:1;
			        unsigned tfENSTOP1s:1;
			        unsigned tfENSTOP2s:1;
			        unsigned tFCL1m:1;
			        unsigned tfENSTOP1:1;
			        unsigned tfENSTOP2:1;        
		         };
unsigned char bits2;} u2;
//
union	{ struct {
			        unsigned tmid:1;
			        unsigned tmax:1;
			        unsigned tdoor:1;
			        unsigned tzmk_T_cmp:1;
			        unsigned tobr_T_cmp:1;
			        unsigned :1;           //f_new_mtch
			        unsigned tfU_24:1;
			        unsigned tfSTANBY:1;        
		         };
unsigned char bits9;} tsDAT_BIT;//0x4
//
//
unsigned char sSTATUS,op,op_b,op_b_ee,fAVR_LIN_TAB;
unsigned char I_CL_isp1,I_CL_isp2,I_CL_knd1,I_CL_knd2;
unsigned char U_CL_isp1,U_CL_isp2,U_CL_knd1,U_CL_knd2;

unsigned char U_pr1,U_pr2,ssU_nap,t_s_U_nap;

unsigned char t_avr_comp,fAVRCOMPS;
unsigned char t_avr_con,fAVRCONS;
unsigned char t_avr_def,fAVRDEFS;
//
unsigned char t_avr_isp1,fAVRISP1S;
unsigned char t_avr_isp2,fAVRISP2S;
//
unsigned char t_avr_knd1,fAVRKND1S;
unsigned char t_avr_knd2,fAVRKND2S;
unsigned char pult_yes,t_F_MEN,t_cl_1s,t_cl_1m;
//
unsigned char sU_pr1,sU_pr2,iu,iu1,ssU_pr1;
unsigned char sU_pr1_min,sU_pr1_max;
unsigned char sU_pr2_min,sU_pr2_max;
//
unsigned char f_tst_vnt,tON_OFF,t_stanby;

unsigned char U_davl,f_davl_an,fuC_con,f_d_max,f_d_mid,sU_davl;


//
union {
	struct	{unsigned char tadr,tkom;};
	unsigned int tetalon;
	}w1;

unsigned char i,l,lin_in[4],buf;
unsigned char POWER_OTOP,WORK_OTOP,YES_OTOP,YES_OTOP_TST;

unsigned char f_ACC;
unsigned char ssU_CL_knd1,ssU_CL_knd2,sU_pr1_s;

unsigned char tester_rej,bl_up_dvg,f_standart;
unsigned char svPOWER_OTOP,sPOWER_OTOP;

unsigned char DOP_MODUL,T3,DOP_KLAPS;
unsigned char fDO_CMP,fAD2,fAD2_kz,fAD2_obr;

unsigned char tech_up_dop,f_klp_cmp,sU_C_def;
unsigned char uUPR_STEND,f_stend_hand,sU_C_con;

unsigned char ssDAT_BIT,f_yes_Tcmp,t_tcmp;
unsigned char fAVR_TCMP,t_bl_dvg;

unsigned char U_C_def,I_C_def;
unsigned char U_C_con,I_C_con;
unsigned char U_Comp,I_Comp,t_mot_l_14;
unsigned char fH_def,t_zad_h_def;  //uH_def;
unsigned char t_zad_h_def1,t_zad_h_def2;
unsigned char t_res_h_def1,t_res_h_def2;
unsigned char t_avr_h_def1,t_vkl_h_def1;
unsigned char t_avr_h_def2,t_vkl_h_def2;

unsigned char t_avr_h_def,t_vkl_h_def;
unsigned char U_H_def,t_res_h_def;
unsigned char U_H_def1,U_H_def2;
unsigned char fH_def_12;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma udata sect2 = 0x100

unsigned int timer1,timer2,timer3,Sum_U_rot,Oper_int;
unsigned char rs_mes2_diag,rs_mes2_data;
unsigned char YES_OTOP2,op_d,op_d1;
unsigned char com_planar,s_POWER_OTOP;
unsigned char cikl_plan,err_plan;
unsigned char svd_mig_1s,err_mig;

unsigned char adc_ch_1_4,adc_ch_5_8,drivers;
unsigned char ctrl,ctrl2,warning;
unsigned char fl_comnd,ErrorCode;
unsigned char Phase,Script,Power_Level;
unsigned char rs_mes2_sost,st_stanby,t_max_power;
unsigned char NO_YES_OTOP2;

unsigned char t_stb,U_acp,max_U_acp,U_stnb;
unsigned char mU_stnb[32],iit,iis,ii;

unsigned int Sum_acp,Sredn_U_stnb; 
unsigned char minU_CL_isp1,maxU_CL_isp1;
unsigned char minU_CL_isp2,maxU_CL_isp2;
unsigned char minU_CL_knd1,maxU_CL_knd1;
unsigned char minU_CL_knd2,maxU_CL_knd2;

unsigned char buf_Upr_start_i1[40];
unsigned char buf_Upr_start_i2[40];
unsigned char buf_Upr_start_k1[40];
unsigned char buf_Upr_start_k2[40];


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma udata sect3 = 0x200

//
unsigned char sU_CL_isp1,sU_CL_isp2;
unsigned char sI_CL_isp1,sI_CL_isp2;

unsigned char mU_CL_isp1,mU_CL_isp2;
unsigned char mI_CL_isp1,mI_CL_isp2;

unsigned char sU_CL_knd1,sU_CL_knd2;
unsigned char sI_CL_knd1,sI_CL_knd2;

//
unsigned char tRAZG_isp1,tRAZG_isp2;
unsigned char tRAZG_knd1,tRAZG_knd2;
unsigned char tOST_isp1,tOST_isp2;
unsigned char tOST_knd1,tOST_knd2;

unsigned char fAVR_IND,f_U1_max;


unsigned char t_blk_res_isp1,t_blk_res_isp2,t_blk_res_knd1;
unsigned char t_blk_res_knd2;
//
unsigned int U_C_def_all,tU_C_def;
unsigned int U_C_con_all,tU_C_con;
unsigned int U_Comp_all,tU_Comp;
//
unsigned char t_avr_def_o,t_avr_con_o,t_avr_comp_o;
//
unsigned char t_avr_isp1_o,t_avr_isp2_o;
unsigned char t_avr_knd1_o,t_avr_knd2_o;

unsigned char t_avr_isp1_b,t_avr_isp2_b,t_avr_isp3_b;
unsigned char t_avr_knd1_b,t_avr_knd2_b;

unsigned char fConfig_t,fConfig,mod_config,k_line_adr;
unsigned char cSOST_UPR1,cSOST_UPR2,cSOST_UPR3,multi;
unsigned char cUPR_BT,mod_3_mot;

unsigned char iu_ss2;

unsigned char t_avr_C_isp1,t_avr_C_isp1_o,t_res_C_isp1;
unsigned char U_C_isp1,I_C_isp1;

unsigned char t_avr_C_isp2,t_avr_C_isp2_o,t_res_C_isp2;
unsigned char U_C_isp2,I_C_isp2;

unsigned char on_cndl,t_ACC,t_ST_VENT,vU_vent_kz;

unsigned char tAVR_knd1,tAVR_knd2,tAVR_isp1,tAVR_isp2;

unsigned char stSVD_OTOP,stREZIST,vREZIST,sDAT_DAT,tZAD_CND;

unsigned char v_isp_razg,v_knd_razg;
unsigned char vU_knd_kz,vU_knd_obr,vU_vent_obr;

unsigned char t_vkl_comp,t_vkl_def,t_vkl_con;
unsigned char t_zad_def,t_zad_con;

unsigned char t_pau_comp,f_pau_comp;

unsigned char t_zad_isp1,t_zad_isp2;
unsigned char t_vkl_isp1,t_vkl_isp2;

unsigned char se_rtKMPm,se_rtKMPh_l,se_rtKMPh_h;
unsigned char f_new_mtch;

unsigned char rtKMPm,rtKMPh_l,rtKMPh_h;


//unsigned int *blozu;
unsigned int timer;
rom unsigned char *uk;
rom unsigned char  *tarrom;


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

unsigned char 	 p_res, L_res_k,  
		p_out, L_out,k_res,i_kl,L_in,summa,cikl,ip,ir;

unsigned char op_b2,p_in,znak;

unsigned char com_trm,L_res,com_line;
unsigned char rs_mes_end,rs_mes_start;
unsigned char yes_tr_com,summa_tr,block_ans,rs_mes;


rom unsigned char *uk;

unsigned char buf_in[20];
unsigned char res[20];
unsigned char buf_out[40];

unsigned char t_res_def,t_res_con,t_res_comp;

unsigned char I_CL_DEF,I_CL_CON,I_CL_CMP,I_KL_ISP;
unsigned char yes_tr_com2,com_trm2,summa_tr2;
unsigned char rs_mes_end2,rs_mes_start2,summa2;
unsigned char com_line2,rs_mes2,rs_mes2_yes;

unsigned char p_in2,ip2,ir2,L_out2,p_out2,L_in2,utUPR_BT;
unsigned char ipp,p_res2,L_res2,schetcik5,tester_lin,ji;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma udata sect4 = 0x300

unsigned char buf_in2[70];
//unsigned char buf_Upr_kz_i2[50];
//unsigned char buf_Upr_rot_i2[35];

unsigned char buf_Upr_kz[50];
unsigned char buf_Upr_rot[35];



#pragma udata sect5 = 0x500

unsigned char buf_Upr[60];
unsigned char buf_Upr_rt[60];

unsigned char res2[40];

unsigned char buf_out2[20];



