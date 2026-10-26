;******************************************************
; ПРОГРАММА БЛОКА УПРАВЛЕНИЯ КЛИМАТОМ
;******************************************************
EXTERN SECOND,MINUTE,HOUR,nom_err
EXTERN TEM_SET,zOPER,CLOC1s,st_kl,Bright
EXTERN T_air,T_isp,tON_OFF,T_cmp
EXTERN T_air_dpl,T_air_dmn,U_nap
EXTERN T_air_dpl_a,T_air_dmn_a,T_air_dpl_o
EXTERN knop,t_kl,sZADT,tON_OFF_2h
EXTERN tONCOLD5,tONCOLD,tONDEF,tENDDEF
EXTERN tENDHOT,CLOC1m,t_X_DAVL
EXTERN sSTATUS,sSTATUS1,sSTATUS2,U_davl
EXTERN f_config_t,ver_sil,mUPR_BT,KNOPKA
;
;bits
EXTERN blok_fl,UPR_BT,DAT_BIT,tech_upr
EXTERN SOST_UPR1,SOST_UPR2,SOST_UPR3,fAVR_IND

;
;programs
EXTERN S1OZSPV,S1OZREJ,S1OZUPR,t_OTOP_AVR,OTOP_SLEEP   
;
;eeprom
EXTERN tPER_DEF,tDEF,T_FIN_DEF,tWAT_DEF
EXTERN T_START_HOT,t_FIN_HOT,t_START_HOT
EXTERN dT_GIST,s_blok_fl,tech_upr_dop,tUPR_BT_dop
EXTERN T_SET_COLD_MIN,T_SET_HOT_MAX,T_START_HOT2

EXTERN rbit ;rT_air,rT_isp,rT_kmp
EXTERN t_OFF,t_nom_upr,n_err_txt,n_err_bt
;EXTERN i_rtKMPh_l,i_rtKMPh_h,i_nom_zap
EXTERN t_nom,t_l,t_h,z_nom_err,oT_air
 
EXTERN rtKMPh_l_1,rtKMPh_l_2,rtKMPh_h_1,rtKMPh_h_2,rtKMPh_h_3
EXTERN s_rtKMPh_l,rtKMPh_l
EXTERN rtKMPh_h
EXTERN rtKMPm
EXTERN tMIN5,nSTEP
EXTERN tTIMER2,t_TDEF
EXTERN tSECCOM,tSECVKL
EXTERN sONOFF,BankEE
EXTERN tD_AVR,dTp,tWait_20m,tPaus_20m
EXTERN sI_CL1,UPR_BT,tOFF_A,ti_AD2
EXTERN sSOST_UPR1,sSOST_UPR2,S1OZOTOP,sSTATUS_OTOP
EXTERN POWER_OTOP,t_WAIT_OTOP,zOPER_PL,zOPER_MN
EXTERN t_WAIT_OTOP_A,t_def_Visp,s_tONDEF,tON_VKL



#define V_PO_Y  0x33
#define V_PO_N  0x38
;
;eblok_fl	0x00
#define fONLY_A		00H ;
#define fCOLD		01H	;
#define fHOT_COLD	02H	;реж. работы нагрев/охлаждение
#define fON_STANB	03H	;флаг записи параметров
#define fSYN_V_ISP	04H	;
#define fAUTO		05H	;
#define fONDEFR		06H	;реж. 
#define fHOTDO		07H	;флаг РАБОТЫ РЕЖ НАГРЕВА
;
;
;UPR_BT		0x01
#define uV_ISP	0x10	
#define uC_ISP  0x11	
#define uV_CON	0x12
;#define 	0x13
#define uH_DEF 0x14
#define uC_DEF	0x15
#define uC_CON	0x16
#define uCOMP 	0x17

;
;DAT_BIT	0x02
#define kP_MID	0x20
#define kP_AVR	0x21
;#define 	0x22
#define kCND	0x22
#define fZMKV_ISP3	0x23 ;fZMK_Tcmp
#define fOBRV_ISP3 0x24  ;fOBR_Tcmp
#define fBLK_ISP3 0x25
#define kDOOR	0x26
#define fSTANB	0x27
;
;SOST_UPR1	0x03
#define fZMKV_ISP1   0x30
#define	fOBRV_ISP1	0x31
#define fZMKV_CON1   0x32
#define	fOBRV_CON1	0x33
#define fZMKC_DEF   0x34
#define	fOBRC_DEF	0x35
#define fZMKC_CON   0x36
#define fOBRC_CON_T	0x37
;
;F1		0x04
#define fBLKLAV 	0x40
#define fONOFF 		0x41
#define fYES_TCMP 	0x42
#define fZMK_Tcmp	0x43
#define fOBR_Tcmp	0x44
#define uKL_CMP 	45H	; клап охл компр
#define fMIGAN		46H	; флаг мигания надписей
#define fAVR_TCMP	47H	;флаг защёлка для клап охл компр
;
;F2		0x05
#define fCHANG_TDEF	0x50
#define fSTART_HOT	0x51
#define fOTOP_WORK  0x52
#define fYES_OTOP   0x53
#define fEND_DEF    0x54
#define fAVAR_OTOP  0x55
#define INDIK_OTOP  0x56
#define YES_OTOP    0x57
;
;F3		0x06
#define fAD2		0x60
#define fT1_ERR		0x61
#define fT2_ERR		0x62
#define fCHANGE		0x63
#define fDOOR		0x64
#define fNO_U_nap	0x65
#define fSTART_HOT_t 0x66
#define fCONTR_D	0x67
;
;F4		0x07
#define fDO_SLEEP	0x70
#define f_davl_an	0x71
#define rfONOFF		0x72
#define fACC_LOW	0x73
#define fON_CND		0x74
#define fTECH_ERR	0x75
#define f_ver_sil	0x76
#define fOBRC_CON	0x77
;
;rbit	0x08
#define fINDIK_TXT	0x80
#define n_e_txt_m	0x81
#define n_e_txt_p	0x82
#define f_clr_err 	0x83
#define f_stop_zmk 	0x84
;#define 	0x85	; 
;#define 	0x86	;
;#define 	0x87
;
;u1	0x9
#define multi1	0x90
#define fAVR_LIN	0x91
#define fONDEFR_R 0x92
#define F1m			0x93
#define fTECH_DLT		0x94  ;cfPROG
#define fEQTIMES	0x95
#define fIND_tC		0x96	
#define FCL1s		0x97

;fAVR_IND	0xA
#define f_no_work	0xA0
#define f_stop		0xA1
#define f_no_stop	0xA2
#define f_no_klap	0xA3
#define f_no_temp	0xA4
#define f_no_comp	0xA5
#define f_blk_vnt 	0xA6
#define fNO_OFF		0xA7	;


;SOST_UPR3	0xB
#define fZMKV_ISP2	0xb0
#define fOBRV_ISP2	0xb1
#define fZMKV_CON2  0xb2
#define	fOBRV_CON2	0xb3
#define fBLK_ISP1   0xb4
#define	fBLK_CON1	0xb5
#define fBLK_ISP2	0xb6	
#define fBLK_CON2	0xb7
;
;u4 0xC
#define fOTKL		0xc0
#define fSLEEP		0xc1
#define faONOFF		0xc2
#define f_AVRSTR	0xc3
#define fBUZ		0xc4
#define multi2		0xc5
#define f_multi2_lin 0xc6
#define f_H_def	0xc7
;
;F5 0xD
#define bl_up_dvg 0xd0
#define fDO_CMP	  0xd1
#define fON_CNDL	0xd2
#define fI_DAVL	0xd3 ;
#define fI_TISP	0xd4 ;используются
#define fWAIT	0xd5 ;используются
#define fTECH_UPR  	0xd6
#define f_T_isp3	0xd7
;
;SOST_UPR_dop	0xE
#define fZMKH_DEF  0xe2
#define	fOBRH_DEF	0xe3
#define fZMKC1_ISP  0xe4
#define	fOBRC1_ISP	0xe5
#define fZMKC2_ISP 0xe6
#define fOBRC2_ISP	0xe7

;

;SOST_UPR2	0xF
#define fZMK_COMP	0xf0
#define fOBR_COMP	0xf1
#define fNO_PR1		0xf2
#define fNO_PR2		0xf3
#define fZMK_Tisp	0xf4
#define fOBR_Tisp	0xf5
#define fZMK_Tair	0xf6
#define fOBR_Tair	0xf7

;UPR_BT2 0xE
;#define uV_ISP3		0xe0
;#define uV_ISP4		0xe1
;#define uC_ISP1		0xe2
;#define uC_ISP2		0xe3
;#define fsNOCIKL	0xe4
;#define uC_DEF2		0xe5
;#define uC_CON2		0xe6
;#define uCOMP2		0xe7

;EEPROM BANK
#define eblok_fl	0	;
#define etPER_DEF   1	;период авт. вкл. оттайки
#define etDEF		2   ;длительность оттайки
#define eT_FIN_DEF  3	;темп. окончания оттайки
#define etWAT_DEF	4   ;время стекания воды при оттайки
#define eT_SET_COLD_MIN 5	;минимальн. знач. температуры
#define eT_SET_HOT_MAX  0x6 ;максимальн. знач. температуры
#define esZADT		0x7
#define es_blok_fl		0x8
;
#define eONOFF 	0x9
;
#define etONCOLD5	0xA
#define etONCOLD	0xB
;
#define EETCOM_M 0xC
#define EETCOM_H 0xD
#define EETCOM_W 0xE

#define eNOM_ERR 0xF
#define eBright 0x10
;
#define edTp 0x11

;*********************************************
;
;***************************************************
;***************************************************
;   ТЕКСТ САМОЙ УНИВЕРСАЛЬНОЙ ПРОГРАММЫ
;***************************************************
;***************************************************
#define 	kTEST(N)   DW   0100H+N	; контроль
;
#define 	kF(F)	DW   0H+F
#define 	kN(F)	DW   100H+F
#define 	kNA(F)	DW   200H+F
#define 	kORL	DW   300H
#define 	kE(C)	DW   400H+C
#define 	kEA(C)	DW   500H+C
#define 	kEF(C)	DW   600H+C ;провер.на маску C
;
;#define 	knE(C)	DW   600H+C
;#define 	knEA(C)	DW   700H+C
;#define 	kB(C)	DW   800H+C;больше 
;#define 	kBA(C)	DW   900H+C;больше по адресу			
;#define 	kM(C)	DW   0A00H+C;меньше
;#define 	kMA(C)	DW   0B00H+C;меньше по адресу	
;
#define 	JUMP	DW    0C00H
#define 	kJUMP	DW    0C01H
#define 	kGO		DW    0C02H
#define 	kNOP	DW    0C03H
;
#define 	kKLAV(C) DW    0D00H+C ;опрос клавиатуры

;
#define 	v	DW		;переменная
#define 	f	DW		;флаг
#define 	m	DW		;метка
#define 	cw	DW		;метка
#define 	c	DW		;метка
;
#define 	MS(K)	DW   0H+K	;код проверки с переход.
#define 	kMS(K)	DW   100H+K	;код проверки с переход.
#define 	MSO(K)	DW   200H+K	;код проверки с операц.
#define 	kMSO(K)	DW   300H+K	;код проверки с операц.
;
#define 	C_END	DW   0FFFFH	;конец пров. условия
;
#define 	pSAV(v)		DW   1100H+v
;#define 	pASM		DW   1200H+v
;#define 	pTAB(v)		DW   1300H+v
;#define 	pBUFC(v)	DW   1400H+v
;#define 	BUF(N,C)	DW   100H*N+C
;#define 	pCOPBUF(v)	DW   1500H+v
;#define 	pADD(v)		DW   1600H+v
#define 	pMOVB(v)	DW   1700H+v
#define 	pBCF(f)		DW   1800H+f
#define 	pBSF(f)		DW   1900H+f
#define 	OFF(f)		DW   1800H+f	
#define 	ON(f)		DW   1900H+f

;#define 	pDEL(v)		DW   1A00H+v
#define 	pMOVLF(v) 	DW   1B00H+v
#define 	pINC(v)		DW   1C00H+v
#define 	pDEC(v)		DW   1D00H+v
#define 	pADDC(v)	DW   1E00H+v
#define 	pSUBC(v)	DW   1F00H+v

#define 	pSTOP(v)	DW   2000H+v
#define 	pBUZON		DW   2100H
#define 	pBUZOFF		DW   2200H
#define 	pCLRF(v)	DW   2300H+v
#define 	pDEC10(v)	DW   2400H+v
#define 	pINC10(v)	DW   2500H+v
;#define 	pSUBZ(v)	DW   2700H+v
;#define 	pDEC1M(v)	DW   2800H+v
#define 	pINC1M(v)	DW   2900H+v
;#define 	pBIT(f)		DW   2A00H+f
;#define 	pSVUKRDRG	DW   2B00H  ;adrEEPROM_rd
;#define  	pLDUKRDRG	DW   2C00H  ;adrEEPROM_rd
;#define	pSTEPINC(v) DW   2D00H+v  ;adrEEPROM_rd		
;#define 	pSTEPDEC(v) DW   2E00H+v  ;adrEEPROM_rd
;#define 	pEQWBT(v)	DW   2F00H+v  ;	
;
#define		Ustkur(v)	DW 3000H+v
#define 	Prstr		DW 3100H
#define 	Prdes1(v)	DW 3200H+v
#define 	Prsim(v)	DW 3300H+v
#define		Prdtmp(v)	DW 3400H+v
#define		Prdes(v)	DW 3500H+v
#define		Prtemp(v)	DW 3600H+v
;
#define 	Prbd		DW 3700H
;#define	WrEE(v)		DW 3800H+v
;#define 	RdEE(v)		DW 3900H+v
;
#define		RdEEin(v)	DW 3A00H+v
#define		WrEEin(v)	DW 3B00H+v
;#define		Clr_disp	DW 3C00H
;#define		Clr_str(v)	DW 3D00H+v
;#define		Big_zifra(v) DW 3E00H+v
;#define		Spez(v)     DW 3F00H+v
;#define		Mid_zifra(v) DW 4000H+v
;#define		Prclock(v)  DW 4100H+v
;#define		Clr_big     DW 4200H
;#define		Prnapr(v)	DW 4300H+v
;
;#define		pMIN5		DW 4400H
;#define		pINC_EE(v) DW 4500H+v  ;adrEEPROM_wr		
;#define 		pDEC_EE(v) DW 4600H+v  ;adrEEPROM_wr
;
;#define		pEQ_RDWR_Q	DW 4700H ;fRDWR_Q
;#define		pINC5MIN	DW 4800H ;
;#define		pDEC5MIN	DW 4900H ;
#define		pREGTCOM	DW 4A00H ;ЗАПИСЬ НАРАБОТКИ УСТАНОВКИ.
#define		pRDTCOM		DW 4B00H ;ЧТЕНИЕ НАРАБОТКИ УСТАНОВКИ.
;
;#define		Prdes2(v)	DW 4C00H+v ;
;#define		pEQWTIME	DW 4D00H ;СРАВНЕНИЕ ВРЕМЕНИ ВКЛЮЧЕНИЯ
;#define		Prnum(v)	DW 4E00H+v ;1 hex znak
;#define		pBRIGHT		DW 4F00H
;#define		pWrEE128	DW 5000H


;//
sKODEE	EQU 0xE1
;*********************************************
;*********************************************
	ORG 4140H
;*********************************************
;*********************************************
;
END_TECH:


SUPERVIS:
	RdEEin(es_blok_fl),s_blok_fl
	RdEEin(eblok_fl),blok_fl	
	RdEEin(etPER_DEF),tPER_DEF	
	RdEEin(etDEF),tDEF	
	RdEEin(eT_FIN_DEF),T_FIN_DEF	
	RdEEin(etWAT_DEF),tWAT_DEF	
	RdEEin(eT_SET_COLD_MIN),T_SET_COLD_MIN
	RdEEin(eT_SET_HOT_MAX),T_SET_HOT_MAX
	RdEEin(esZADT),sZADT
;
	RdEEin(etONCOLD5),tONCOLD5
	RdEEin(etONCOLD),tONCOLD
;
	RdEEin(eNOM_ERR),nom_err
	RdEEin(eBright),Bright
	RdEEin(edTp),dTp
;<<
	kTEST(1)
	kE(sKODEE),s_blok_fl
;
	kMSO(0)		;0
;
	pMOVLF(blok_fl),0x20
	pMOVLF(s_blok_fl),sKODEE
	pMOVLF(tPER_DEF),D'24'	;*5 = 120
	pMOVLF(tDEF),D'20'
	pMOVLF(T_FIN_DEF),D'62'
	pMOVLF(tWAT_DEF),D'2'
	pMOVLF(T_SET_COLD_MIN),D'40' ;D'40' ;D'40'  ;D'35'
	pMOVLF(T_SET_HOT_MAX), D'72' ;D'72' ;D'80'	;D'90'
	pMOVLF(sZADT),D'65'	;0
	pMOVLF(dTp),D'3'	;0
;
	pCLRF(nom_err)
;
;//
	WrEEin(eblok_fl),blok_fl
	WrEEin(es_blok_fl),s_blok_fl	
	WrEEin(etPER_DEF),tPER_DEF	
	WrEEin(etDEF),tDEF	
	WrEEin(eT_FIN_DEF),T_FIN_DEF	
	WrEEin(etWAT_DEF),tWAT_DEF	
	WrEEin(eT_SET_COLD_MIN),T_SET_COLD_MIN
	WrEEin(eT_SET_HOT_MAX),T_SET_HOT_MAX
	WrEEin(esZADT),sZADT
	WrEEin(edTp),dTp
;
	pCLRF(zOPER)
	WrEEin(etONCOLD5),zOPER
	WrEEin(etONCOLD),zOPER
	WrEEin(eNOM_ERR),nom_err
	WrEEin(eBright),zOPER
;
	DW 0FEFEH
;
	C_END
;>>

	pMOVLF(t_START_HOT),D'15'
	pMOVLF(T_START_HOT2),D'62'
	pMOVLF(T_START_HOT),D'63'
	pMOVLF(t_FIN_HOT),D'12'
	pMOVLF(dT_GIST),D'1'

;
;

;	pEQWTIME	;СРАВНЕНИЕ ВРЕМЕНИ ВКЛЮЧЕНИЯ
;
;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;;<<
;	kTEST(1)
;	kF(fEQTIME)
;	kMSO(0x1)	;1
;	RdEEin(etONCOLD5),tONCOLD5
;	RdEEin(etONCOLD),tONCOLD
;	DW 0FEFEH
;	kMSO(0x0)	;0
;	pCLRF(tONCOLD5)
;	pCLRF(tONCOLD)
;	WrEEin(etONCOLD5),tONCOLD5
;	WrEEin(etONCOLD),tONCOLD
;	DW 0FEFEH
;	C_END
;;>>
;
	pRDTCOM	;ЧТЕНИЕ НАРАБОТКИ УСТАНОВКИ
	RdEEin(eONOFF),sONOFF
;
;	pMOVB(rtKMPh_l),s_rtKMPh_l


	pSAV(S1OZREJ),REJ_UPR
;
	pBSF(fEQTIMES)
;
	pSAV(S1OZOTOP),UPR_OTOP
;
	kGO
;


;**********************************************************
;<< ВЫБОР РЕЖИМА ТЕХНОЛОГИЧЕСКОГО
	kTEST(5)
	kF(fTECH_ERR)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'10'),t_kl
	kE(0xD),knop
;
	kMSO(b'00001')
	pBSF(fTECH_ERR)
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>

;<< ВЫБОР РЕЖИМА ТЕХНОЛОГИЧЕСКОГО
	kTEST(1)
	kF(fTECH_ERR)
;
	MSO(b'1')
	pSAV(S1OZREJ),0
	pSAV(S1OZOTOP),0
	DW 0FFFFH
	m TCH_ERR
	C_END
;>>

;<< ВЫБОР РЕЖИМА ТЕХНОЛОГИЧЕСКОГО УПРАВЛ
	kTEST(1)
	kF(fTECH_UPR)
;
	MSO(b'1')
	pSAV(S1OZREJ),0
	pSAV(S1OZOTOP),0
	pBCF(fTECH_ERR)
	DW 0FFFFH
	m TCH_UPR
	C_END
;>>

;************************************************************


;<<
	kTEST(2)
	kF(fYES_OTOP)
	kF(fOBRC_CON)
	kMSO(B'11')
	pBCF(f_no_klap)
	pBCF(fOBRC_CON)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(fAUTO)
	kF(fHOT_COLD)
	kF(fOBRC_CON)
	kMSO(B'001')
	pBCF(f_no_klap)
	DW 0FEFEH
	C_END
;>>

;<<ОТСЧЕТ ВРЕМЕНИ РАБОТЫ УСТАНОВКИ
	kTEST(3)
	kF(fYES_OTOP)
	kF(fONOFF)
	kF(FCL1s)
	MSO(b'011')
	pINC(tSECCOM)
	pREGTCOM
	DW 0FEFEH
	C_END
;>>

;<<ОТСЧЕТ ВРЕМЕНИ РАБОТЫ УСТАНОВКИ
	kTEST(4)
	kF(uCOMP)
	kF(fYES_OTOP)
	kF(fONOFF)
	kF(FCL1s)
	MSO(b'1111')
	pINC(tSECCOM)
	pREGTCOM
	DW 0FEFEH
	C_END
;>>


;<< ВЫВОД НАРАБОТКИ
	kTEST(3)
	kF(fSLEEP)
	kN(D'9'),rtKMPh_h
	kE(D'0'),rtKMPh_h
	kMSO(b'111')
	Ustkur(0x1)
	Prsim(' ')
	Ustkur(0x2)
	Prbd
	Prdes1(rtKMPh_l_2)
	Prdes1(rtKMPh_l_1)
	pBUZOFF
	DW 0FFFFH
	m REJ_OFF
	kMSO(b'110')
	Ustkur(0x1)
	Prbd
	Prdes1(rtKMPh_h_1)
	Prdes1(rtKMPh_l_2)
	Prdes1(rtKMPh_l_1)
	pBUZOFF
	DW 0FFFFH
	m REJ_OFF
	kMSO(b'100')
	Ustkur(0x1)
	Prbd
	Prdes1(rtKMPh_h_2)
	Prdes1(rtKMPh_h_1)
	Prdes1(rtKMPh_l_2)
	pBUZOFF
	DW 0FFFFH
	m REJ_OFF
	C_END
;>>
	Prbd

;<<
	kTEST(1)
	kF(fSLEEP)
	kMS(B'1')
	m REJ_OFF
	C_END
;>>


;ИСКЛЮЧЕНИЕ РЕЖИМОВ /НАГРЕВ/АВТО при обрыве CON


;<<
	kTEST(4)
	kF(fYES_OTOP)
	kF(fONOFF)
	kF(fHOT_COLD)
	kF(fOBRC_CON)
	kMSO(B'0011')
;	pBCF(fAUTO)
;	pBCF(fHOT_COLD)
	pBCF(fONLY_A)	
	WrEEin(eblok_fl),blok_fl
;	pBCF(f_no_klap)
;	pBCF(fOBRC_CON)
	DW 0FEFEH
;	m no_r_zad
;
	kMSO(B'0001')
	pBCF(fAUTO)
	pBCF(fONLY_A)	
	WrEEin(eblok_fl),blok_fl
;	pBCF(f_no_klap)
;	pBCF(fOBRC_CON)
	DW 0FEFEH
;
;	kMSO(B'0011')
;	pBCF(fAUTO)
;	pBCF(fHOT_COLD)
;	pBCF(fONLY_A)	
;	WrEEin(eblok_fl),blok_fl
;	DW 0FEFEH
	C_END
;>>

;ВЫБОР РЕЖИМА АВТО - КАК ЕДИНСТВЕННОГО
;<<
	kTEST(5)
	kF(fONLY_A)	
;	kF(fAUTO)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'10'),t_kl
	kE(0x5),knop
;
	kMSO(B'00001')
	pBSF(fAUTO)
	pBSF(fBLKLAV)
	pBSF(fONLY_A)	
	WrEEin(eblok_fl),blok_fl
	DW 0FEFEH
;
	kMSO(B'10001')
	pBCF(fAUTO)
	pBSF(fBLKLAV)
	pBCF(fONLY_A)	
	WrEEin(eblok_fl),blok_fl
	DW 0FEFEH
	C_END
;>>

;ВЫБОР РЕЖИМА АВТО - КАК ЕДИНСТВЕННОГО
;<<
	kTEST(5)
	kF(fSYN_V_ISP)	
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'10'),t_kl
	kE(0x5),knop
;;
;	kMSO(B'01001')
;	pBSF(fBLKLAV)
;	pBSF(fSYN_V_ISP)	
;	WrEEin(eblok_fl),blok_fl
;	DW 0FEFEH
;;
	kMSO(B'11001')
	pBSF(fBLKLAV)
	pBCF(fSYN_V_ISP)	
	WrEEin(eblok_fl),blok_fl
	DW 0FEFEH
	C_END
;>>

;???????????????????????????????????????????????????????
;;<<СБРОС ФЛАГА ИНДИКАЦИИ ТО
;	kTEST(4)
;	kF(fONOFF)
;	kF(fBLKLAV)
;	kN(D'100'),t_kl
;	kE(0xC),knop
;;
;	kMSO(B'0001')
;	pBSF(fBLKLAV)
;	pBCF(fWR_EEPROM)
;	pBSF(fSOS_YES)
;	WrEEin(eblok_fl),blok_fl
;	DW 0FEFEH
;	C_END
;;>>


;;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;;<<СБРОС ФЛАГА проведения ТО
;	kTEST(1)
;	kE(D'99'),rtKMPh_l
;	kMS(B'0')
;	m YES_SOS
;	C_END
;;>>

;;<<СБРОС ФЛАГА проведения ТО
;	kTEST(7)
;	kE(D'4'),rtKMPh_h
;	kORL
;	kE(D'9'),rtKMPh_h
;	kORL
;	kE(D'14'),rtKMPh_h
;	kORL
;	kE(D'19'),rtKMPh_h
;	kORL
;	kE(D'24'),rtKMPh_h
;	kORL
;	kE(D'29'),rtKMPh_h
;	kORL
;	kE(D'34'),rtKMPh_h
;;
;	kMSO(B'1111111')
;	pBCF(fSOS_YES)
;	WrEEin(eblok_fl),blok_fl
;	DW 0FEFEH
;	C_END
;;>>
;;<<СБРОС ФЛАГА проведения ТО
;	kTEST(7)
;	kE(D'39'),rtKMPh_h
;	kORL
;	kE(D'44'),rtKMPh_h
;	kORL
;	kE(D'49'),rtKMPh_h
;	kORL
;	kE(D'54'),rtKMPh_h
;	kORL
;	kE(D'59'),rtKMPh_h
;	kORL
;	kE(D'64'),rtKMPh_h
;	kORL
;	kE(D'69'),rtKMPh_h
;;
;	kMSO(B'1111111')
;	pBCF(fSOS_YES)
;	WrEEin(eblok_fl),blok_fl
;	DW 0FEFEH
;	C_END
;;>>

;;<<СБРОС ФЛАГА проведения ТО
;	kTEST(5)
;	kE(D'74'),rtKMPh_h
;	kORL
;	kE(D'79'),rtKMPh_h
;	kORL
;	kE(D'84'),rtKMPh_h
;	kORL
;	kE(D'89'),rtKMPh_h
;	kORL
;	kE(D'94'),rtKMPh_h
;;
;	kMSO(B'11111')
;	pBCF(fSOS_YES)
;	WrEEin(eblok_fl),blok_fl
;	DW 0FEFEH
;	C_END
;;>>


;YES_SOS:
;;<<УСТАНОВКА ФЛАГА ИНДИКАЦИИ ТО
;	kTEST(2)
;	kF(fSOS_YES)
;	kORL
;	kF(fWR_EEPROM)
;	kMS(B'11')
;	m NO_SOS
;	C_END
;;>>

;;<<УСТАНОВКА ФЛАГА ИНДИКАЦИИ ТО
;	kTEST(2)
;	kE(D'80'),rtKMPh_l
;	kE(D'0'),rtKMPh_h
;;
;	kMSO(B'11')
;	pBSF(fWR_EEPROM)
;;	pBCF(fSOS_YES)
;	WrEEin(eblok_fl),blok_fl
;	DW 0FEFEH
;	C_END
;;>>
;???????????????????????????????????????????????????????

;;<<УСТАНОВКА ФЛАГА ИНДИКАЦИИ ТО
;	kTEST(7)
;	kE(D'5'),rtKMPh_h
;	kORL
;	kE(D'10'),rtKMPh_h
;	kORL
;	kE(D'15'),rtKMPh_h
;	kORL
;	kE(D'20'),rtKMPh_h
;	kORL
;	kE(D'25'),rtKMPh_h
;	kORL
;	kE(D'30'),rtKMPh_h
;	kORL
;	kE(D'35'),rtKMPh_h
;;
;	kMSO(B'1111111')
;	pBSF(fWR_EEPROM)
;	WrEEin(eblok_fl),blok_fl
;	DW 0FEFEH
;	C_END
;;>>
;;<<УСТАНОВКА ФЛАГА ИНДИКАЦИИ ТО
;	kTEST(7)
;	kE(D'40'),rtKMPh_h
;	kORL
;	kE(D'45'),rtKMPh_h
;	kORL
;	kE(D'50'),rtKMPh_h
;	kORL
;	kE(D'55'),rtKMPh_h
;	kORL
;	kE(D'60'),rtKMPh_h
;	kORL
;	kE(D'65'),rtKMPh_h
;	kORL
;	kE(D'70'),rtKMPh_h
;;
;	kMSO(B'1111111')
;	pBSF(fWR_EEPROM)
;	WrEEin(eblok_fl),blok_fl
;	DW 0FEFEH
;	C_END
;;>>

;;<<УСТАНОВКА ФЛАГА ИНДИКАЦИИ ТО
;	kTEST(5)
;	kE(D'75'),rtKMPh_h
;	kORL
;	kE(D'80'),rtKMPh_h
;	kORL
;	kE(D'85'),rtKMPh_h
;	kORL
;	kE(D'90'),rtKMPh_h
;	kORL
;	kE(D'95'),rtKMPh_h
;;
;	kMSO(B'11111')
;	pBSF(fWR_EEPROM)
;	WrEEin(eblok_fl),blok_fl
;	DW 0FEFEH
;	C_END
;;>>


;NO_SOS:

;<<
	kTEST(1)
	kF(fONLY_A)
	kMS(B'1')
	m no_r_zad
	C_END
;>>

;<<ВЫБОР РЕЖИМА НАГРЕВ/ОХЛАЖДЕНИЕ/АВТО
	kTEST(7)
	kF(fOBRC_CON)
	kF(fAUTO)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'60'),t_kl
	kE(1),knop
	kF(fHOT_COLD)
;
	kMSO(B'1000011')
	pSAV(S1OZREJ),REJ_UPR
	pSAV(S1OZUPR),0x00	
	pBCF(fHOT_COLD)
	WrEEin(eblok_fl),blok_fl
	pBSF(fBLKLAV)
	pMOVLF(t_OFF),D'80'
	DW 0FEFEH
;
	kMSO(B'0100010')
	pSAV(S1OZREJ),REJ_UPR
	pSAV(S1OZUPR),0x00			
	pBCF(fAUTO)
	WrEEin(eblok_fl),blok_fl
	pBSF(fBLKLAV)
	pMOVLF(t_OFF),D'80'
	DW 0FEFEH
;
	kMSO(B'0100011')
	pSAV(S1OZREJ),REJ_UPR
	pSAV(S1OZUPR),0x00			
	pBCF(fAUTO)
	pBCF(fHOT_COLD)
	WrEEin(eblok_fl),blok_fl
	pBSF(fBLKLAV)
	pMOVLF(t_OFF),D'80'
	DW 0FEFEH
;
	kMSO(B'0000010')
	pSAV(S1OZREJ),REJ_UPR
	pSAV(S1OZUPR),0x00	
	pBSF(fHOT_COLD)
	WrEEin(eblok_fl),blok_fl
	pBSF(fBLKLAV)
	pMOVLF(t_OFF),D'80'
	DW 0FEFEH
;
	kMSO(B'1000010')
	pSAV(S1OZREJ),REJ_UPR
	pSAV(S1OZUPR),0x00	
	pBSF(fHOT_COLD)
	WrEEin(eblok_fl),blok_fl
	pBSF(fBLKLAV)
	pMOVLF(t_OFF),D'80'
	DW 0FEFEH
;
	kMSO(B'0000011')
	pSAV(S1OZREJ),REJ_UPR
	pSAV(S1OZUPR),0x00	
	pBCF(fHOT_COLD)
	pBSF(fAUTO)
	WrEEin(eblok_fl),blok_fl
	pBSF(fBLKLAV)
	pMOVLF(t_OFF),D'80'
	DW 0FEFEH
	C_END
;>>

no_r_zad:

;<< ЗАДАНИЕ ПОСТ ТЕМП КАМЕРЫ ДЛЯ ЗАПУСКА
;АВТ ОТОПИТЕЛЯ
	kTEST(5)
	kN(D'15'),t_kl
	kF(fBLKLAV)
	kE(D'90'),sZADT
	kF(fHOT_COLD)
	kF(YES_OTOP)
;
	kMSO(b'00111')
	pMOVLF(oT_air),D'85'
	pBSF(fBLKLAV)
	DW 0FEFEH
;
	C_END
;>>
;<< ВЫБОР РУЧНОЙ РАЗМОРОЗКИ
	kTEST(6)
	kF(fONDEFR)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'25'),t_kl
	kE(0xC),knop
	kF(fHOT_COLD)
;
	kMSO(b'010010')
	pBSF(fONDEFR)
	pBSF(fONDEFR_R)
	pBSF(fBLKLAV)
	DW 0FEFEH
;
	C_END
;>>

	pBCF(fIND_tC)

;<< ВЫБОР ИЗМЕНЕНИЯ Т РАЗМОРОЗКИ
	kTEST(5)
	kF(fONDEFR)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'80'),t_kl
	kE(0xC),knop
;
	kMSO(b'00001')
	pBSF(fIND_tC)
	pBSF(fCHANG_TDEF)
	pBSF(fBLKLAV)
	pMOVLF(t_TDEF),D'80'
	DW 0FEFEH
	C_END
;>>

;<< ВЫБОР ИЗМЕНЕНИЯ ВРЕМЕНИ РАЗМОРОЗКИ
	kTEST(5)
	kF(fONDEFR)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'30'),t_kl
	kE(0xC),knop
;
	kMSO(b'11001')
	pBSF(fIND_tC)
	pBSF(fCHANG_TDEF)
	pBSF(fBLKLAV)
	pMOVLF(t_TDEF),D'80'
	DW 0FEFEH
	C_END
;>>



;<< ВЫБОР ВЫВОДИМОЙ ТЕМПЕРАТУРЫ
	kTEST(4)
	kF(fI_TISP)
	kF(fBLKLAV)
	kN(D'20'),t_kl
	kE(0x9),knop
;
	kMSO(b'0001')
	pBSF(fI_TISP)
	pBSF(fBLKLAV)
	DW 0FEFEH
;
	kMSO(b'1001')
	pBCF(fI_TISP)
	pBSF(fBLKLAV)
	pBCF(fI_DAVL)
	DW 0FEFEH
	C_END
;>>

;<< ВЫБОР ВЫВОДИМОЙ ТЕМПЕРАТУРЫ И ДАВЛЕНИЯ
	kTEST(5)
	kF(f_davl_an)
	kF(fI_TISP)
	kF(fBLKLAV)
	kN(D'60'),t_kl
	kE(0x9),knop
;
	kMSO(b'11101')
	pBSF(fI_DAVL)
	pBCF(fBUZ)
	DW 0FEFEH
	C_END
;>>


;
;**********************************

;<<
	kTEST(2)
	kF(fBLKLAV)
	kE(0),knop
	kMSO(03)	;11
	pBCF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>

ON_OFF EQU 0x0001

;<<
	kTEST(1)
	kN(0x0),tTIMER2
	MSO(b'0')
	pDEC(tTIMER2)
	DW 0FEFEH
	C_END
;>>

;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;<< ВЫБОР РЕЖИМА ИЗМЕНЕНИЯ ПОГРЕШНОСТИ T
	kTEST(5)
	kF(fTECH_DLT)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'3'),t_kl
	kE(0xD),knop
;;
;	MSO(b'01001')
;	pBSF(fBLKLAV)
;	pBSF(fTECH_DLT)
;	pSTOP(1)
;	DW 0FEFEH
;;
	MSO(b'11001')
	pBSF(fBLKLAV)
	pBCF(fTECH_DLT)
	DW 0FEFEH
	C_END
;>>

;<< ЗАМЕНА ЗАДАННОЙ ТЕМПЕРАТУРЫ НА DEFR
	kTEST(3)
	kF(fONOFF)
	kF(fCHANG_TDEF)
	kE(0),t_TDEF
;
	kMSO(b'010')
	pDEC(t_TDEF)
	pMOVB(T_FIN_DEF),sZADT
	pBSF(fIND_tC)
	pMOVLF(tTIMER2),D'50'
	DW 0FEFEH
;ВРЕМЯ ОТТАЙКИ
	kMSO(b'110')
	pDEC(t_TDEF)
	pMOVB(tPER_DEF),sZADT
	pBSF(fIND_tC)
	pMOVLF(tTIMER2),D'50'
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(2)
	kF(fCHANG_TDEF)
	kE(0),t_TDEF
	kMSO(b'11')
	pBCF(fCHANG_TDEF)
	pCLRF(tTIMER2)
	RdEEin(esZADT),sZADT
	DW 0FEFEH
	C_END
;>>



;<<
	kTEST(4)
	kE(0x9),knop
	kF(fONOFF)	
	kE(0x0),tTIMER2
	kE(0x1),sONOFF

;	MSO(b'111')
;	Ustkur(0x1)
;	Prtemp(T_air)
;	pBSF(fIND_tC)
;	DW 0FEFEH
	MSO(b'0101')
	Ustkur(0x1)
	Prtemp(sZADT)
	pBSF(fIND_tC)
	DW 0FEFEH
	MSO(b'0001')
	Ustkur(0x1)
	Prtemp(sZADT)
	pBSF(fIND_tC)
	DW 0FEFEH

	MSO(b'0100')
	Ustkur(0x1)
	Prtemp(sZADT)
;	Ustkur(0x4)
;	Prsim(' ')
	pBSF(fIND_tC)
	DW 0FEFEH
	MSO(b'0000')
	Ustkur(0x1)
	Prtemp(sZADT)
;	Ustkur(0x4)
;	Prsim(' ')
	pBSF(fIND_tC)
	DW 0FEFEH
	MSO(b'0001')
	Ustkur(0x1)
	Prtemp(sZADT)
;	Ustkur(0x4)
;	Prsim(' ')
	pBSF(fIND_tC)
	DW 0FEFEH
	C_END
;>>


;Работа с надписью OFF
;<<
	kTEST(5)
	kF(fON_CNDL)	
	kE(0x0),tTIMER2
	kN(0x3),knop
	kF(fONOFF)	
	kE(0x0),t_OFF
	kMSO(B'01001')
	Prstr,0x1,STR_OFF
	pBCF(f_ver_sil)
	DW 0FFFFH
	m YES_OFF
	C_END
;>>

;<<
	kTEST(5)
	kF(fON_CNDL)	
	kE(0x0),tTIMER2
	kE(0x0),knop
	kF(fONOFF)	
	kE(0x0),t_OFF
	kMSO(B'01101')
	Prstr,0x1,STR_OFF
	pBCF(f_ver_sil)
	DW 0FFFFH
	m YES_OFF
	kMSO(B'11101')
	Prstr,0x1,STR_CND
	DW 0FFFFH
	m YES_OFF
	C_END
;>>
; включение вентил конденсора
;<<
	kTEST(5)
	kF(fON_CNDL)	
	kE(0x0),tTIMER2
	kE(0x0),knop
	kF(fONOFF)	
	kE(0x0),t_OFF
	kMSO(B'11101')
	Prstr,0x1,STR_CND
	DW 0FFFFH
	m YES_OFF
	C_END
;>>

;<<
	kTEST(2)
	kF(fONOFF)	
	kE(0x0),t_OFF
	kMSO(B'10')
	pCLRF(t_OFF)
	DW 0FEFEH
	kMSO(B'00')
	pDEC(t_OFF)
	DW 0FEFEH
	kMSO(B'10')
	pCLRF(t_OFF)
	DW 0FEFEH
	C_END
;>>

;
;Вывод режимов работы
;<<
	kTEST(6)
	kE(0x9),knop
	kE(0x0),tTIMER2
	kF(fONDEFR)
	kF(fONOFF)	
	kF(fAUTO)
	kF(fHOT_COLD)
	MSO(B'010001')
	Prstr,0x1,STR_HOT
	pBCF(fIND_tC)
	DW 0FEFEH
	MSO(B'010000')
	Prstr,0x1,STR_COLD
	pBCF(fIND_tC)
	DW 0FEFEH	
	MSO(B'011000')
	Prstr,0x1,STR_DEFR
	pBCF(fIND_tC)
	DW 0FEFEH	
;	MSO(B'010101')
;	Ustkur(0x4)
;	Prsim('h')
;	DW 0FEFEH
;	MSO(B'010100')
;	Ustkur(0x4)
;	Prsim('c')
;	DW 0FEFEH	
	C_END
;>>

;<<
	kTEST(4)
	kE(0x9),knop
	kE(0x0),tTIMER2
	kF(fONOFF)	
	kF(fAUTO)
	MSO(B'0101')
	Prstr,0x1,STR_AUTO
	pBCF(fIND_tC)
	DW 0FEFEH
;	MSO(B'0111')
;	Ustkur(0x4)
;	Prsim(' ')
;	DW 0FEFEH
	C_END
;>>

YES_OFF:

;Выбор вывода версии программы

;<< 
	kTEST(4)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'30'),t_kl
	kE(0xC),knop
;
	kMSO(b'0001')
	Ustkur(0x1)
	pMOVLF(rtKMPh_h_1),V_PO_Y
	Prdes1(rtKMPh_h_1)
	pMOVLF(rtKMPh_l_2),'o'
	Prdes1(rtKMPh_l_2)
	pMOVLF(rtKMPh_l_1),V_PO_N
	Prdes1(rtKMPh_l_1)
	pBSF(f_ver_sil)
	pCLRF(st_kl)
	DW 0FEFEH
	kMSO(b'00011')
	pMOVB(t_kl),st_kl
	DW 0FEFEH
	C_END
;>>
;<< 
	kTEST(5)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'0'),st_kl
	kN(D'20'),st_kl
	kE(0x0),knop
;
	kMSO(b'00011')
	pINC(Bright)
	WrEEin(eBright),Bright
	pCLRF(t_kl)
	pCLRF(st_kl)
	pCLRF(KNOPKA)
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;<< 
	kTEST(1)
	kN(D'4'),Bright
	kMSO(b'0')
	pCLRF(Bright)
	WrEEin(eBright),Bright
	DW 0FEFEH
	C_END
;>>



;;<<
;	kTEST(4)
;	kE(0x9),knop
;	kF(fONOFF)	
;	kF(fAUTO)	
;	kF(fONDEFR)
;	MSO(B'0101')
;	Ustkur(0x4)
;	Prsim('c')
;	DW 0FEFEH	
;	MSO(B'0111')
;	Ustkur(0x4)
;	Prsim(' ')
;	DW 0FEFEH	
;	C_END
;;>>




;<<
	kTEST(5)
	kF(fI_DAVL)
	kE(0x9),knop
	kF(fI_TISP)
	kF(fONOFF)	
	kE(0x0),tTIMER2
;
	MSO(b'01011')
	Ustkur(0x1)
	Prtemp(T_air)
	pBSF(fIND_tC)
	DW 0FEFEH
;
	MSO(b'01001')
	Ustkur(0x1)
	Prtemp(T_air)
	pBSF(fIND_tC)
	DW 0FEFEH
;
	MSO(b'00011')
	Ustkur(0x1)
	Prtemp(T_air)
	pBSF(fIND_tC)
	DW 0FEFEH
;
	C_END
;>>

;<<
	kTEST(2)
	kF(fMIGAN)
	kF(fTECH_DLT)
;
	MSO(b'11')
	Ustkur(0x1)
	Prdtmp(dTp)
	DW 0FEFEH
;
	C_END
;>>

;<<
	kTEST(6)
	kF(fMIGAN)
	kF(fI_DAVL)
	kE(0x9),knop
	kF(fI_TISP)
	kF(fONOFF)	
	kE(0x0),tTIMER2
;
	MSO(b'001111')
	Ustkur(0x1)
	Prtemp(T_isp)
	pBSF(fIND_tC)
	DW 0FEFEH
;
	MSO(b'000111')
	Ustkur(0x1)
	Prtemp(T_isp)
	pBSF(fIND_tC)
	DW 0FEFEH
;
	MSO(b'001101')
	Ustkur(0x1)
	Prtemp(T_isp)
	pBSF(fIND_tC)
	DW 0FEFEH
	C_END
;>>
;	pBSF(fYES_TCMP)
;<<
	kTEST(1)
	kF(fYES_TCMP)
;
	MSO(b'0')
	pMOVB(T_isp),T_cmp
	DW 0FEFEH
;
;	MSO(b'1')
;	pMOVLF(T_cmp),D'165'
;	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(6)
	kF(fMIGAN)
	kF(fI_DAVL)
	kE(0x9),knop
	kF(fI_TISP)
	kF(fONOFF)	
	kE(0x0),tTIMER2
;
	MSO(b'101111')
	Ustkur(0x1)
	Prtemp(T_cmp)
	pBSF(fIND_tC)
	DW 0FEFEH
;
	MSO(b'100111')
	Ustkur(0x1)
	Prtemp(T_cmp)
	pBSF(fIND_tC)
	DW 0FEFEH
;
	MSO(b'101101')
	Ustkur(0x1)
	Prtemp(T_cmp)
	pBSF(fIND_tC)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(3)
	kF(fI_DAVL)
	kE(0x9),knop
	kE(0x0),tTIMER2
;	kE(0x1),sONOFF
;
	MSO(b'111')
	Ustkur(0x1)
	Prdes(U_davl)
	pBSF(fIND_tC)
	DW 0FEFEH
;
	MSO(b'101')
	Ustkur(0x1)
	Prdes(U_davl)
	pBSF(fIND_tC)
	DW 0FEFEH
	C_END
;>>


;
	pMOVB(SOST_UPR1),sSOST_UPR1
	pMOVB(SOST_UPR2),sSOST_UPR2
;
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
; Д И А Г Н О С Т И К А
;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
;***********************************************************


;****************************************
;ПРИОРИТЕТ 4

;<< ВЫВОД СТРОКИ "ДВЕРЬ"
	kTEST(3)
	kF(fONOFF)
	kF(kDOOR)
	kF(fMIGAN)
	MSO(b'111')
	Prstr,0x01,STR_DOW
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;
;<< ВЫВОД СТРОКИ "ACC"
	kTEST(2)
;	kF(fONOFF)
	kF(fACC_LOW)
	kF(fMIGAN)
	MSO(b'11')
	Prstr,0x01,STR_ACC
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>


;;<< ПРИ НЕИСПРАВН. ВЕНТИЛЯТ. ИСПАРИТЕЛЯ
;	kTEST(3)
;	kF(fBLK_ISP1)
;	kF(f_blk_vnt)
;	kF(fMIGAN)
;	MSO(0x7)	;11
;	Prstr,0x01,STR_VI_BLK
;	pBSF(f_AVRSTR)
;	pBSF(fBUZ)
;	DW 0FEFEH
;	C_END
;;>>
;;<<
;	kTEST(3)
;	kF(fBLK_ISP2)
;	kF(f_blk_vnt)
;	kF(fMIGAN)
;	MSO(0x7)	;11
;	Prstr,0x01,STR_VI_BLK
;	pBSF(f_AVRSTR)
;	pBSF(fBUZ)
;	DW 0FEFEH
;	C_END
;;>>
;<<
	kTEST(3)
	kF(fBLK_ISP1)
	kF(fBLK_ISP2)
	kF(fMIGAN)
	MSO(0x05)	;101
	Prstr,0x01,STR_VI_BLK
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(0x03)	;011
	Prstr,0x01,STR_VI_BLK
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(0x07)	;011
	Prstr,0x01,STR_VI_BLK
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>


;;<< ПРИ НЕИСПРАВН. ВЕНТИЛЯТ. ИСПАРИТЕЛЯ
;<<
	kTEST(3)
	kF(fOBRV_ISP1)
	kF(fOBRV_ISP2)
	kF(fMIGAN)
	MSO(0x5)	;101
	Prstr,0x01,STR_VI_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(0x3)	;011
	Prstr,0x01,STR_VI_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(0x7)	;011
	Prstr,0x01,STR_VI_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>

;;<< ПРИ НЕИСПРАВН. ВЕНТИЛЯТ. ИСПАРИТЕЛЯ
;<<
	kTEST(3)
	kF(fZMKV_ISP1)
	kF(fZMKV_ISP2)
	kF(fMIGAN)
	MSO(0x3)	;011
	Prstr,0x01,STR_VI_ZMK
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(0x5)	;101
	Prstr,0x01,STR_VI_ZMK
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(0x7)	;101
	Prstr,0x01,STR_VI_ZMK
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>

;Пауза автономного отопителя
;<<
	kTEST(3)
	kN(D'15'),t_OTOP_AVR
	kF(INDIK_OTOP)
	kF(fMIGAN)
	MSO(b'001')
	Prstr,0x01,STR_OTP_PAU
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>
;Неисправность автономного отопителя
;<<
	kTEST(2)
	kF(fAVAR_OTOP)
	kF(INDIK_OTOP)
	MSO(0x3)	;11
	Prstr,0x01,STR_OTP_AVR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>
;Неисправность автономного отопителя
;<<
	kTEST(4)
	kF(fMIGAN)
	kN(0x3),t_OTOP_AVR
	kF(fAVAR_OTOP)
	kF(INDIK_OTOP)
	MSO(b'1010')	;110
	Prstr,0x01,STR_OTP_AVR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>


;<< ОБХОД ПРИ РАБОТЕ АВТОНОМНОГО ОТОПИТЕЛЯ
	kTEST(3)
	kF(fAUTO)
	kF(fHOT_COLD)
	kF(YES_OTOP)
	kMSO(b'011')
	pBCF(f_stop)
	pBCF(faONOFF)
	DW 0FFFFH
	m NO_AV_DD
	C_END
;>>

;****************************************
;ПРИОРИТЕТ 2
;ОБРЫВ
;;<< ПРИ НЕИСПРАВН. ВЕНТИЛЯТ. КОНДЕНСОРА

;<< 
	kTEST(3)
	kF(fOBRV_CON1)
	kF(fOBRV_CON2)
	kF(fMIGAN) 
	MSO(0x5)	;011
	Prstr,0x01,STR_VC_OBR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(0x3)	;011
	Prstr,0x01,STR_VC_OBR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(0x7)	;011
	Prstr,0x01,STR_VC_OBR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>


;КОРОТКОЕ ЗАМЫКАНИЕ
;<< 
	kTEST(3)
	kF(fZMKV_CON2)
	kF(fZMKV_CON1)
	kF(fMIGAN) 
	MSO(0x5)	;101
	Prstr,0x01,STR_VC_ZMK
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(0x3)	;311
	Prstr,0x01,STR_VC_ZMK
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(0x7)	;311
	Prstr,0x01,STR_VC_ZMK
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;***************************************
;ПРИОРИТЕТ 3
;БЛОКИРОВКА
;<< 
	kTEST(3)
	kF(fBLK_CON1)
	kF(fBLK_CON2)
	kF(fMIGAN) 
	MSO(0x5)	;101
	Prstr,0x01,STR_VC_BLK
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(0x3)	;011
	Prstr,0x01,STR_VC_BLK
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(0x7)	;011
	Prstr,0x01,STR_VC_BLK
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>

;<< ПРИ АВАРИИ ДАТЧ. ДАВЛ.
	kTEST(2)
	kF(kP_AVR)
	kF(fMIGAN) 
	MSO(b'11')
	Prstr,0x01,STR_AVR_DVL
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;
;<< ПРИ АВАРИИ ДАТЧ. ДАВЛ.
	kTEST(3)
	kE(0xfe),U_davl
	kE(0xfd),U_davl
	kF(fMIGAN) 
	MSO(b'101')
	Prstr,0x01,STR_AVR_DVL_K
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'011')
	Prstr,0x01,STR_AVR_DVL_O
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(1)
	kF(fAD2)
	MSO(b'1')
	pINC(ti_AD2)
	DW 0FEFEH
	MSO(b'0')
	pCLRF(ti_AD2)
	DW 0FEFEH
	C_END
;>>

;<< ПРИ АВАРИИ ДАТЧ. ДАВЛ.2
	kTEST(3)
	kN(D'20'),ti_AD2
	kF(fAD2)
	kF(fMIGAN) 
	MSO(b'011')
	Prstr,0x01,STR_AVR_DVL2
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	pMOVLF(ti_AD2),D'22'
	DW 0FEFEH
	C_END
;>>


NO_AV_DD:
;****************************************
;
;ПРИОРИТЕТ 1
;<< ПРИ ОТСУТСТВИИ ОБМЕНА С ИСП. БЛОКОМ
	kTEST(2)
	kF(fAVR_LIN)
	kF(fMIGAN)
	MSO(0x3)	;11
	Prstr,0x01,STR_LIN_AV
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>
;;<< ВЫВОД СТРОКИ "ПРЕДОХРАНИТ1"
;	kTEST(2)
;	kF(fNO_PR1)
;	kF(fMIGAN)
;	MSO(b'11')
;	Prstr,0x01,STR_Pr1
;	pBSF(fBUZ)
;	DW 0FEFEH
;	C_END
;;>>
;<< ВЫВОД СТРОКИ "ПРЕДОХРАНИТ2"
	kTEST(2)
	kF(fNO_PR2)
	kF(fMIGAN)
	MSO(b'11')
	Prstr,0x01,STR_Pr2
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>
;
;<< ПРИ НЕИСПРАВН. ДАТЧ. ТЕМПЕРАТУР
	kTEST(3)
	kF(fOBR_Tair)
	kF(fZMK_Tair)
	kF(fMIGAN) 
	MSO(b'101')	;11
	Prstr,0x01,STR_TA_OBR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'011')	;11
	Prstr,0x01,STR_TA_ERR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>

;
;<< ПРИ НЕИСПРАВН. ДАТЧ. ТЕМПЕРАТУР
	kTEST(3)
	kF(fOBR_Tcmp)
	kF(fZMK_Tcmp)
	kF(fMIGAN) 
	MSO(b'101')	;11
	Prstr,0x01,STR_TC_OBR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'011')	;11
	Prstr,0x01,STR_TC_ERR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>


;ОБХОД НЕИСПР ПРИ РАБОТЕ АО
;
;<< 
	kTEST(3)
	kF(fAUTO)
	kF(fHOT_COLD)
	kF(YES_OTOP)
	kMS(b'011')
	m NO_AV_DD1
	C_END
;>>

;<< ПРИ НЕИСПРАВН. ДАТЧ. ТЕМПЕРАТУР
	kTEST(3)
	kF(fOBR_Tisp)
	kF(fZMK_Tisp)
	kF(fMIGAN) 
	MSO(b'101')	;11
	Prstr,0x01,STR_TI_OBR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'011')	;11
	Prstr,0x01,STR_TI_ERR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>

;
;<< ПРИ НЕИСПРАВН. КЛАПАНОВ
	kTEST(3)
	kF(fOBRC_DEF)
	kF(fZMKC_DEF)
	kF(fMIGAN)
	MSO(0x5)	;101
	Prstr,0x01,STR_С_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(0x3)	;011
	Prstr,0x01,STR_С_ERR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>

;<< ПРИ НЕИСПРАВН. КЛАПАНОВ
	kTEST(4)
	kF(fHOT_COLD)
	kF(fOBRC_CON)
	kF(fZMKC_CON)
	kF(fMIGAN)
	MSO(0xD)	;1101
	Prstr,0x01,STR_СC_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
;	pBCF(fAUTO)
	DW 0FEFEH
	MSO(0xB)	;1011
	Prstr,0x01,STR_СC_ERR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
;	pBCF(fAUTO)
	DW 0FEFEH
	C_END
;>>

;<< ПРИ НЕИСПРАВН. КЛАПАНОВ
	kTEST(4)
	kF(fAUTO)
	kF(fOBRC_CON)
	kF(fZMKC_CON)
	kF(fMIGAN)
	MSO(0xD)	;1101
	Prstr,0x01,STR_СC_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
;	pBCF(fAUTO)
	DW 0FEFEH
	MSO(0xB)	;1011
	Prstr,0x01,STR_СC_ERR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
;	pBCF(fAUTO)
	DW 0FEFEH
	C_END
;>>

;***********************************************
;ДОП 
;
;<< ПРИ НЕИСПРАВН. КЛАПАНОВ
	kTEST(3)
	kF(fYES_TCMP)
	kF(fZMKC1_ISP)
	kF(fMIGAN)
	MSO(b'011')	;011
	Prstr,0x01,STR_С1I_ERR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(b'111')	;111
	Prstr,0x01,STR_СCP_ERR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>
;<< ПРИ НЕИСПРАВН. КЛАПАНОВ
	kTEST(3)
	kF(fYES_TCMP)
	kF(fOBRC1_ISP)
	kF(fMIGAN)
	MSO(b'011')	;011
	Prstr,0x01,STR_С1I_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(b'111')	;111
	Prstr,0x01,STR_СCP_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>
;<< ПРИ НЕИСПРАВН. КЛАПАНОВ
	kTEST(3)
	kF(fOBRC2_ISP)
	kF(fZMKC2_ISP)
	kF(fMIGAN)
	MSO(0x5)	;101
	Prstr,0x01,STR_С2I_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(0x3)	;011
	Prstr,0x01,STR_С2I_ERR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>

;<< ПРИ НЕИСПРАВН. кабеля поддона
	kTEST(4)
	kF(multi1)
	kF(fZMKH_DEF)
	kF(fOBRH_DEF)
	kF(fMIGAN)
	MSO(b'1101')	;101
	Prstr,0x01,STR_СDF_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(b'1011')	;011
	Prstr,0x01,STR_СDF_ERR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>

;ОБРЫВ
;<< ПРИ НЕИСПРАВН. кабеля поддона
	kTEST(4)
	kF(multi2)
	kF(fOBRV_CON1)
	kF(fOBRV_CON2)
	kF(fMIGAN) 
	MSO(b'1101')	;011
	Prstr,0x01,STR_СDF_OBR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'1011')	;011
	Prstr,0x01,STR_СDF_OBR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'1111')	;011
	Prstr,0x01,STR_СDF_OBR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>

;КОРОТКОЕ ЗАМЫКАНИЕ
;<< 
	kTEST(4)
	kF(multi2)
	kF(fZMKV_CON2)
	kF(fZMKV_CON1)
	kF(fMIGAN) 
	MSO(b'1101')	;101
	Prstr,0x01,STR_СDF_ERR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'1011')	;111
	Prstr,0x01,STR_СDF_ERR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'1111')	;111
	Prstr,0x01,STR_СDF_ERR
	pBSF(fBUZ)
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>


;<< ПРИ НЕИСПРАВН. КОМПРЕССОРА
	kTEST(3)
	kF(fOBR_COMP)
	kF(fZMK_COMP)
	kF(fMIGAN)
	MSO(b'101')
	Prstr,0x01,STR_СOMP_OBR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	MSO(b'011')
	Prstr,0x01,STR_СOMP_ERR
	pBSF(f_AVRSTR)
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>

NO_AV_DD1:

;	pBCF(fBUZ)

;<<
	kTEST(2)
	kF(fBUZ)
	kF(fONOFF)
	MSO(0x03)	;11
	pBUZON
	DW 0FEFEH
	MSO(0x01)	;01
	pBUZOFF
	DW 0FEFEH
	MSO(0x00)	;00
	pBUZOFF
	DW 0FEFEH
	MSO(0x02)	;10
	pBUZOFF
	pBCF(fBUZ)
	DW 0FEFEH
	C_END
;>>

;
;КОНТРОЛЬ НЕИСПРАВНОСТЕЙ ЭЛЕКТРОЦЕПЕЙ

;<<
	kTEST(1)
	kF(f_stop)
	kMSO(B'1')
	pBSF(faONOFF)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(2)
	kF(faONOFF)
	kF(fOTKL)
	kMSO(0x3)	;11
	pBSF(fBUZ)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(1)
	kE(0x0),fAVR_IND	
	kMSO(0x1)	;1
	pBCF(faONOFF)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(fMIGAN)
	kF(fBUZ)
	kF(fOTKL)
	MSO(0x07)	;111
	pBUZON
	DW 0FEFEH
	MSO(0x03)	;011
	pBUZOFF
	pBCF(fBUZ)
	DW 0FEFEH
	MSO(0x02)	;010
	pBUZOFF
	pBCF(fBUZ)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(1)
	kF(faONOFF)
	kMS(0x0)	;0
	m REJ_OFF
	C_END
;>>

REJ_OFF:
	C_END
;


;*********************************************
;*********************************************
;*********************************************
IND_N_ERR:
;<<
	kTEST(2)
	kE(0x0),nom_err
	kN(0x1),z_nom_err
	kMSO(b'00')	;
	pDEC(z_nom_err)
	pMOVLF(n_err_bt),D'1'
	pCLRF(n_err_txt)	
	DW 0FEFEH
	kMSO(b'01')	;
	pMOVB(nom_err),z_nom_err
	pMOVLF(n_err_bt),D'1'	
	pCLRF(n_err_txt)	
	DW 0FEFEH
	C_END
;>>

	C_END
;
;
MINUS_N_ERR:
;<<
	kTEST(1)
	kN(0x1),n_err_bt
	kMSO(b'0')	;
	pDEC(n_err_bt)
	pCLRF(n_err_txt)	
	DW 0FEFEH
	C_END
;>>

	C_END
;
;
PLUS_N_ERR:

;<<
	kTEST(2)
	kE(0x0),n_err_txt
	kE(0x4),n_err_bt
	kMSO(b'01')	;
	pBSF(n_e_txt_p)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kE(0x0),n_err_txt
	kN(0x3),n_err_bt
	kE(0x3),n_err_bt
	kMSO(b'110')	;
	pINC(n_err_bt)
	DW 0FEFEH
	kMSO(b'111')	;
	pINC(n_err_bt)
	pBSF(n_e_txt_p)
	pBSF(fINDIK_TXT)
	DW 0FEFEH
	C_END
;>>
TCH_CLR:
	C_END



;*********************************************
;*********************************************
;*********************************************
;	ОШИБКИ
;	В ТЕХНОЛОГИЧЕСКОМ РЕЖИМЕ
;*********************************************
;*********************************************
;*********************************************
TCH_ERR:
;<<
	kTEST(1)
	kE(0x0),nom_err
	kMSO(b'0')	;
	Prstr,0x01,STR_TE_ERR
	pMOVB(nom_err),z_nom_err
	pMOVB(nom_err),t_nom
	pMOVLF(n_err_bt),D'1'	
	DW 0FEFEH
	kMSO(b'1')	;
	Ustkur(0x1)
	Prsim('E')
	Prsim('-')
	Prsim('-')
	DW 0FEFEH
	C_END
;>>
	kGO
;
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
;<<
	kTEST(4)
	kF(fBLKLAV)
	kN(D'50'),t_kl
	kE(D'0'),nom_err
	kE(0xC),knop
;
	MSO(B'1001')
	pCLRF(nom_err)
	pCLRF(z_nom_err)
	WrEEin(eNOM_ERR),nom_err
	Ustkur(0x1)
	Prsim('E')
	Prsim('-')
	Prsim('-')
	pBSF(f_clr_err)
	pCLRF(t_kl)
	pBCF(fBLKLAV)
	DW 0FFFFH
	m TCH_ERR
;
	kMSO(B'0101')
	pBSF(fBLKLAV)
	DW 0FFFFH
	m TCH_CLR
;
	kMS(B'1101')
	m TCH_CLR
	C_END
;>>

;::::::::::::::::::::::::::::::::::::::::::::::::::
;:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;***************************************************
	kKLAV(0x0D)
	m IND_N_ERR
	m MINUS_N_ERR
	m PLUS_N_ERR
;
;<<ВЫХОД ПО ОТКЛ АСС
	kTEST(1)
	kN(D'60'),U_nap
	MSO(b'1') 
	Prstr,0x01,STR_OFF
	pBCF(fTECH_ERR)
	pBCF(fTECH_UPR)
	DW 0FFFFH
	m END_TECH
	C_END
;>>
;
;1 БАЙТ ОШИБОК
;<<
	kTEST(5)
	kE(0x1),n_err_txt
	kE(0x2),n_err_txt
	kE(0x3),n_err_txt
	kE(0x4),n_err_txt
	kF(fINDIK_TXT)
	kMSO(b'10001')	;11
	Prstr,0x01,STR_VI_BLK
	DW 0FEFEH
	kMSO(b'01001')	;11
	Prstr,0x01,STR_VI_OBR
	DW 0FEFEH
	kMSO(b'00101')	;11
	Prstr,0x01,STR_VC_BLK
	DW 0FEFEH
	kMSO(b'00011')	;11
	Prstr,0x01,STR_VC_OBR
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(5)
	kE(D'5'),n_err_txt
	kE(D'6'),n_err_txt
	kE(D'7'),n_err_txt
	kE(D'8'),n_err_txt
	kF(fINDIK_TXT)
	kMSO(b'10001')	;11
	Prstr,0x01,STR_С_ERR
	DW 0FEFEH
	kMSO(b'01001')	;11
	Prstr,0x01,STR_С_OBR
	DW 0FEFEH
	kMSO(b'00101')	;11
	Prstr,0x01,STR_СC_ERR
	DW 0FEFEH
	kMSO(b'00011')	;11
	Prstr,0x01,STR_СC_OBR
	DW 0FEFEH
	C_END
;>>
;2 БАЙТ ОШИБОК
;<<
	kTEST(5)
	kE(D'9'),n_err_txt
	kE(D'10'),n_err_txt
	kE(D'11'),n_err_txt
	kE(D'12'),n_err_txt
	kF(fINDIK_TXT)
	kMSO(b'10001')	;11
	Prstr,0x01,STR_СOMP_ERR
	DW 0FEFEH
	kMSO(b'01001')	;11
	Prstr,0x01,STR_СOMP_OBR
	DW 0FEFEH
	kMSO(b'00101')	;11
	Prstr,0x01,STR_VI_ZMK
	DW 0FEFEH
	kMSO(b'00011')	;11
	Prstr,0x01,STR_VC_ZMK
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(5)
	kE(D'13'),n_err_txt
	kE(D'14'),n_err_txt
	kE(D'15'),n_err_txt
	kE(D'16'),n_err_txt
	kF(fINDIK_TXT)
	kMSO(b'10001')	;11
	Prstr,0x01,STR_TI_ERR
	DW 0FEFEH
	kMSO(b'01001')	;11
	Prstr,0x01,STR_TI_OBR
	DW 0FEFEH
	kMSO(b'00101')	;11
	Prstr,0x01,STR_TA_ERR
	DW 0FEFEH
	kMSO(b'00011')	;11
	Prstr,0x01,STR_TA_OBR
	DW 0FEFEH
	C_END
;>>
;3 БАЙТ ОШИБОК
;<<
	kTEST(5)
	kE(D'17'),n_err_txt
	kE(D'18'),n_err_txt
	kE(D'19'),n_err_txt
	kE(D'20'),n_err_txt
	kF(fINDIK_TXT)
	kMSO(b'10001')	;11
	Prstr,0x01,STR_AVR_DVL
	DW 0FEFEH
	kMSO(b'01001')	;11
	Prstr,0x01,STR_AVR_DVL2
	DW 0FEFEH
	kMSO(b'00101')	;11
	Prstr,0x01,STR_AVR_DVL_K
	DW 0FEFEH
	kMSO(b'00011')	;11
	Prstr,0x01,STR_AVR_DVL_O
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kE(D'21'),n_err_txt
	kE(D'22'),n_err_txt
	kF(fINDIK_TXT)
	kMSO(b'101')	;11
	Prstr,0x01,STR_PrNo
	DW 0FEFEH
	kMSO(b'011')	;11
	Prstr,0x01,STR_LIN_AV
	DW 0FEFEH
	C_END
;>>
;4 БАЙТ ОШИБОК
;<<
	kTEST(5)
	kE(D'23'),n_err_txt
	kE(D'24'),n_err_txt
	kE(D'25'),n_err_txt
	kE(D'26'),n_err_txt
	kF(fINDIK_TXT)
	kMSO(b'10001')	;11
	Prstr,0x01,STR_С1I_ERR
	DW 0FEFEH
	kMSO(b'01001')	;11
	Prstr,0x01,STR_С1I_OBR
	DW 0FEFEH
	kMSO(b'00101')	;11
	Prstr,0x01,STR_С2I_ERR
	DW 0FEFEH
	kMSO(b'00011')	;11
	Prstr,0x01,STR_С2I_OBR
	DW 0FEFEH
	C_END
;>>
;ВЫВОД НОМЕРА ЗАПИСИ И МОТОЧАСОВ
;<<
	kTEST(2)
	kN(D'9'),z_nom_err
	kE(D'1'),n_err_bt
	kMSO(b'11')	;11
	Ustkur(0x1)
	Prdes(z_nom_err)
	Ustkur(0x1)
	Prsim('E')
	Prsim('-')
	DW 0FEFEH
	kMSO(b'01')	;01
	Ustkur(0x1)
	Prdes(z_nom_err)
	Ustkur(0x1)
	Prsim('E')
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(2)
	kE(D'2'),n_err_bt
	kE(D'3'),n_err_bt
	kMSO(b'10')	;11
	Ustkur(0x1)
	Prbd
	Prdes1(rtKMPh_h_1)
	Prdes1(rtKMPh_l_2)
	Prdes1(rtKMPh_l_1)
	DW 0FEFEH
	kMSO(b'01')	;11
	Ustkur(0x1)
	Prbd
	Prsim(' ')
	Prdes1(rtKMPh_h_3)
	Prdes1(rtKMPh_h_2)
	DW 0FEFEH
	C_END
;>>

;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;<< ВЫБОР РЕЖИМА ТЕХНОЛОГИЧЕСКОГО УПРАВЛ
	kTEST(4)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'10'),t_kl
	kE(0xD),knop
;
	MSO(b'0001')
	pBSF(fTECH_UPR)
	pBSF(fBLKLAV)
	pBCF(fTECH_ERR)
	DW 0FFFFH
	m TCH_UPR
	C_END
;>>
;<< ВЫБОР РЕЖИМА ТЕХНОЛОГИЧЕСКОГО УПРАВЛ
	kTEST(1)
	kF(fTECH_UPR)
;
	MSO(b'1')
	pSAV(S1OZREJ),0
	pSAV(S1OZOTOP),0
	pBCF(fTECH_ERR)
	DW 0FFFFH
	m TCH_UPR
	C_END
;>>
;********************************************
;<<
	kTEST(2)
	kF(fBLKLAV)
	kE(0),knop
	kMSO(b'11')	;11
	pBCF(fBLKLAV)
	pBUZOFF
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(2)
	kF(fBLKLAV)
	kE(0),knop
	kMSO(b'01')	;11
	pBUZOFF
	DW 0FEFEH
	C_END
;>>
	C_END


;*********************************************
;*********************************************
;*********************************************
;	ВКЛЮЧЕНИЯ ВЫКЛЮЧЕНИЯ
;	В ТЕХНОЛОГИЧЕСКОМ РЕЖИМЕ
;*********************************************
;*********************************************
END_TECH1:
	kTEST(3)
	kF(fONOFF)
	kN(D'3'),zOPER
	kE(0x0),knop
;
	MSO(b'011')
	pINC(zOPER)
	pMOVLF(tech_upr),0
	pMOVLF(tech_upr_dop),0
	pBCF(fBUZ)
	pBUZOFF
	DW 0FEFEH
	MS(b'001')
	m SUPERVIS ;ПЕРЕХОД В НАЧАЛО
	C_END
;>>
END_TECH2:
	C_END

;*********************************************
TCH_UPR:
	pMOVLF(t_nom_upr),0x1
;
;<<ВЫХОД ПО ОТКЛ АСС
	kTEST(1)
	kN(D'60'),U_nap
	MSO(b'1') 
	Prstr,0x01,STR_OFF
	pBCF(fTECH_ERR)
	pBCF(fTECH_UPR)
	DW 0FFFFH
	m END_TECH
	C_END
;>>
;
;<< выкл всех потребителей
	kTEST(5)
	kE(0xf),t_nom_upr
	kE(0x0),tech_upr
	kN(D'8'),t_kl
	kE(0xc),knop
	kF(fBLKLAV)
	kMSO(b'00110')	;1
	pBSF(fBLKLAV)
	DW 0FFFFH
	m NO_VAC
	kMSO(b'00111')	;1
	pBSF(fBLKLAV)
	DW 0FFFFH
	m NO_VAC
	kMSO(b'00011')	;1
	pMOVLF(tech_upr),0
	pMOVLF(tech_upr_dop),0
	pBSF(fBLKLAV)
	DW 0FFFFH
	m NO_VAC
	kMSO(b'01011')	;1
	pBSF(fBLKLAV)
	DW 0FFFFH
	m NO_VAC
	C_END
;>>
;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;<< ВЫХОД ИЗ РЕЖИМА ТЕХНОЛОГИЧЕСКОГО УПРАВЛ
	kTEST(4)
	kF(fONOFF)
	kF(fBLKLAV)
	kN(D'6'),t_kl
	kE(0xD),knop
;
	MSO(b'0001')
	pBCF(fTECH_UPR)
	pMOVLF(tech_upr),0
	pMOVLF(tech_upr_dop),0
	pBSF(fBLKLAV)
	Prstr,0x1,STR_OFF
	DW 0FFFFH
	m END_TECH1
	C_END
;>>
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;<< вкл вакуумир доп клапанов
	kTEST(4)
	kF(kCND)
	kE(0xf),t_nom_upr
	kE(0xc),knop
	kF(fBLKLAV)
	kMSO(b'1010')	;1
	pMOVLF(t_nom_upr),0xf
	pMOVLF(sSTATUS),0xf
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;1
	pMOVLF(t_nom_upr),0xf
	pMOVLF(sSTATUS),0xf
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;<< вкл вакуумир 2 клапана
	kTEST(4)
	kF(multi1)
	kE(0xf),t_nom_upr
	kE(0xc),knop
	kF(fBLKLAV)
	kMSO(b'1010')	;1
	pMOVLF(t_nom_upr),0xf
	pMOVLF(sSTATUS),0xf
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;1
	pMOVLF(t_nom_upr),0xf
	pMOVLF(sSTATUS),0xf
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;<< вкл вакуумир 2 клапана
	kTEST(4)
	kF(multi2)
	kE(0xf),t_nom_upr
	kE(0xc),knop
	kF(fBLKLAV)
	kMSO(b'1010')	;1
	pMOVLF(t_nom_upr),0xf
	pMOVLF(sSTATUS),0xf
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;1
	pMOVLF(t_nom_upr),0xf
	pMOVLF(sSTATUS),0xf
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>

;выключ. вакуумирования
;<< 
	kTEST(3)
	kE(0xf),t_nom_upr
	kE(0x1),knop
	kF(fBLKLAV)
	kMSO(b'110')	;1
	pMOVLF(t_nom_upr),0x1
	pBSF(fBLKLAV)
	pMOVLF(sSTATUS),0x0
	pMOVLF(tech_upr),0
	pMOVLF(tech_upr_dop),0
	DW 0FFFFH
	m END_TECH2
	C_END
;>>
;;<< 
;	kTEST(3)
;	kF(multi2)
;	kN(0xe),t_nom_upr
;	kE(0xf),sSTATUS1
;	kMSO(b'111')	;1
;	pMOVLF(t_nom_upr),0xf
;	pMOVLF(sSTATUS),0xf
;	DW 0FEFEH
;	C_END
;;>>
;;<< 
;	kTEST(3)
;	kF(multi1)
;	kN(0xe),t_nom_upr
;	kE(0xf),sSTATUS2
;	kMSO(b'111')	;1
;	pMOVLF(t_nom_upr),0xf
;	pMOVLF(sSTATUS),0xf
;	DW 0FEFEH
;	C_END
;;>>

NO_VAC:

;<< 
	kTEST(1)
	kF(f_H_def)
	kMSO(b'1')	;1
	pBSF(f_T_isp3)
	DW 0FEFEH
	C_END
;>>

;<< если нет испар 3 +
	kTEST(6)
	kF(fYES_TCMP)
	kE(0x8),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(kCND)
	kE(0x7),t_nom_upr
	kMSO(b'010000')	;1
	pINC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'010010')	;1
	pINC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'010001')	;1
	pMOVLF(t_nom_upr),0x1
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'010011')	;1
	pMOVLF(t_nom_upr),0x9
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;
;<< если нет испар 3 +
	kTEST(7)
	kF(kCND)
	kE(0x8),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(fYES_TCMP)
	kN(0x6),t_nom_upr
	kE(0x7),t_nom_upr
	kMSO(b'0100110')	;1
	pINC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'0100101')	;1
	pMOVLF(t_nom_upr),0x9
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>


;<< если нет испар 3 +
	kTEST(2)
	kF(multi2)
	kE(0x6),t_nom_upr
	kMSO(b'11')	;1
	pMOVLF(t_nom_upr),0x1
	DW 0FEFEH
	C_END
;>>

;<< если нет испар 3 +
	kTEST(1)
	kE(0xB),t_nom_upr
	kMSO(b'1')	;1
	pMOVLF(t_nom_upr),0x1
	DW 0FEFEH
	C_END
;>>
;
;<< если нет испар 3 +
	kTEST(5)
	kE(0x8),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(fYES_TCMP)
	kE(0x9),t_nom_upr
	kMSO(b'10011')	;1
	pMOVLF(t_nom_upr),0x1
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;<< если нет испар 3 +
	kTEST(5)
	kE(0x8),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(kCND)
	kE(0x9),t_nom_upr
	kMSO(b'10011')	;1
	pMOVLF(t_nom_upr),0xA
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>


;<< если нет испар 3 +
	kTEST(5)
	kE(0x8),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(kCND)
	kE(0xA),t_nom_upr
	kMSO(b'10011')	;1
	pMOVLF(t_nom_upr),0x1
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
;<< если нет испар 3 -
	kTEST(7)
	kF(fYES_TCMP)
	kF(multi2)
	kE(0x4),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(kCND)
	kE(0x1),t_nom_upr
	kMSO(b'0010000')	;1
	pDEC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'0110000')	;1
	pDEC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'0010010')	;1
	pDEC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'0010001')	;1
	pMOVLF(t_nom_upr),0x7
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'0010011')	;1
	pMOVLF(t_nom_upr),0xA
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'0110001')	;1
	pMOVLF(t_nom_upr),0x5
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;<< если нет испар 3 +
	kTEST(2)
	kF(f_T_isp3)
	kE(0x8),t_nom_upr
	kMSO(b'01')	;1
	pMOVLF(t_nom_upr),0x7
	DW 0FEFEH
	C_END
;>>

;<< если нет испар 3 +
	kTEST(5)
	kE(0x4),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(kCND)
	kE(0x1),t_nom_upr
	kMSO(b'10011')	;1
	pMOVLF(t_nom_upr),0xA
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;
;<< если нет испар 3 +
	kTEST(5)
	kE(0x4),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(fYES_TCMP)
	kE(0x1),t_nom_upr
	kMSO(b'10011')	;1
	pMOVLF(t_nom_upr),0x9
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>

;<< если нет испар 3 +
	kTEST(5)
	kE(0x4),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(kCND)
	kE(0xA),t_nom_upr
	kMSO(b'10011')	;1
	pMOVLF(t_nom_upr),0x9
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;
;<< если нет испар 3 +
	kTEST(5)
	kE(0x4),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(fYES_TCMP)
	kE(0x9),t_nom_upr
	kMSO(b'10011')	;1
	pMOVLF(t_nom_upr),0x7
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;
;<< если нет испар 3 +
	kTEST(6)
	kE(0x4),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(fYES_TCMP)
	kN(0x1),t_nom_upr
	kN(0x7),t_nom_upr
	kMSO(b'100101')	;1
	pDEC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>


;<< если нет испар 3 +
	kTEST(5)
	kE(0x4),knop
	kF(fBLKLAV)
	kF(f_T_isp3)
	kF(kCND)
	kE(0x9),t_nom_upr
	kMSO(b'10011')	;1
	pMOVLF(t_nom_upr),0x7
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>

;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

; если есть испар 3
;<<
	kTEST(6)
	kF(multi2)
	kF(f_T_isp3)
	kE(0x8),knop
	kF(fBLKLAV)
	kE(0x5),t_nom_upr
	kE(0x8),t_nom_upr
	kMSO(b'111000')	;1
	pINC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'111010')	;1
	pMOVLF(t_nom_upr),0x8
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'111001')	;1
	pMOVLF(t_nom_upr),0x1
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(5)
	kF(multi2)
	kF(f_T_isp3)
	kE(0x4),knop
	kF(fBLKLAV)
	kE(0x8),t_nom_upr
	kMSO(b'11101')	;1
	pMOVLF(t_nom_upr),0x5
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(5)
	kF(multi2)
	kF(f_T_isp3)
	kE(0x4),knop
	kF(fBLKLAV)
	kE(0x1),t_nom_upr
	kMSO(b'11100')	;1
	pDEC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'11101')	;1
	pMOVLF(t_nom_upr),0x8
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>



; если есть испар 3
;<<
	kTEST(5)
	kF(multi1)
	kF(f_T_isp3)
	kE(0x8),knop
	kF(fBLKLAV)
	kE(0x8),t_nom_upr
	kMSO(b'11100')	;1
	pINC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'11101')	;1
	pMOVLF(t_nom_upr),0x1
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(5)
	kF(multi1)
	kF(f_T_isp3)
	kE(0x4),knop
	kF(fBLKLAV)
	kE(0x1),t_nom_upr
	kMSO(b'11100')	;1
	pDEC(t_nom_upr)
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'11101')	;1
	pMOVLF(t_nom_upr),0x8
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>



;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

;вакуумирование

;<<
	kTEST(2)
	kF(kCND)
	kE(0xf),t_nom_upr
	kMSO(b'11')	;11
	pMOVLF(tech_upr),0x20
	pMOVLF(tech_upr_dop),0x03
	Prstr,0x1,STR_С_VAC
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(2)
	kF(multi1)
	kE(0xf),t_nom_upr
	kMSO(b'11')	;11
	pMOVLF(tech_upr),0x60
	Prstr,0x1,STR_С_VAC
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(2)
	kF(multi2)
	kE(0xf),t_nom_upr
	kMSO(b'11')	;11
	pMOVLF(tech_upr),0xa0
	Prstr,0x1,STR_С_VAC
	DW 0FEFEH
	C_END
;>>

;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;разморозка
;<<
	kTEST(1)
	kE(0x1),t_nom_upr
	kMSO(b'1')	;1
	Prstr,0x1,STR_С_UP
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(4)
	kEF(0x20),tech_upr
	kF(fBLKLAV)
	kE(0x1),t_nom_upr
	kE(0x1),knop
	kMSO(b'0011')	;11
	pADDC(tech_upr),0x20
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;10
	pSUBC(tech_upr),0x20
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;отсечка
;OC1 multi1
;<<
	kTEST(2)
	kF(multi1)
	kE(0x2),t_nom_upr
	kMSO(b'01')	;1
	Prstr,0x1,STR_СC_UP
	DW 0FEFEH
	kMSO(b'11')	;1
	Prstr,0x1,STR_С1_UP
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(4)
	kEF(0x40),tech_upr
	kF(fBLKLAV)
	kE(0x2),t_nom_upr
	kE(0x1),knop
	kMSO(b'0011')	;11
	pADDC(tech_upr),0x40
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;10
	pSUBC(tech_upr),0x40
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;компрессор
;OC2 multi2
;<<
	kTEST(2)
	kF(multi2)
	kE(0x3),t_nom_upr
	kMSO(b'01')	;01
	Prstr,0x1,STR_СP_UP
	DW 0FEFEH
	kMSO(b'11')	;11
	Prstr,0x1,STR_С2_UP
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(4)
	kEF(0x80),tech_upr
	kF(fBLKLAV)
	kE(0x3),t_nom_upr
	kE(0x1),knop
	kMSO(b'0011')	;011
	pADDC(tech_upr),0x80
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;10
	pSUBC(tech_upr),0x80
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>


;вент испарителя 1 3
;;<<
;	kTEST(4)
;	kEF(0x10),f_config_t
;	kE(0x31),ver_sil
;	kF(multi2)
;	kE(0x4),t_nom_upr
;	kMSO(b'1111')	;1
;	Prstr,0x1,STR_VI3_UP
;	DW 0FEFEH
;	C_END
;;>>
;;;;;;;;;;;;;;;;;;;;;;;;;
;<<
	kTEST(6)
	kF(multi2)
	kEF(0x10),f_config_t
	kEF(0x10),tech_upr
	kF(fBLKLAV)
	kE(0x4),t_nom_upr
	kE(0x1),knop
	kMSO(b'110011')	;011
	pADDC(tech_upr),0x10
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'111011')	;10
	pSUBC(tech_upr),0x10
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;вент испарителя 1
;<<
	kTEST(2)
	kEF(0x01),f_config_t
	kE(0x4),t_nom_upr
	kMSO(b'11')	;11
	Prstr,0x1,STR_VI1_UP
	DW 0FEFEH
	C_END
;>>
;;;;;;;;;;;;;;;;;;;;;;;;;
;<<
	kTEST(5)
	kEF(0x01),f_config_t
	kEF(0x01),tech_upr
	kF(fBLKLAV)
	kE(0x4),t_nom_upr
	kE(0x1),knop
	kMSO(b'10011')	;011
	pADDC(tech_upr),0x01
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'11011')	;10
	pSUBC(tech_upr),0x01
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>

;вент испарителя 2
;<<
	kTEST(1)
	kE(0x5),t_nom_upr
	kMSO(b'1')	;1
	Prstr,0x1,STR_VI2_UP
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(4)
	kEF(0x02),tech_upr
	kF(fBLKLAV)
	kE(0x5),t_nom_upr
	kE(0x1),knop
	kMSO(b'0011')	;011
	pADDC(tech_upr),0x02
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;10
	pSUBC(tech_upr),0x02
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;вент конденсора 1
;<<
	kTEST(1)
	kE(0x6),t_nom_upr
	kMSO(b'1')	;1
	Prstr,0x1,STR_VC1_UP
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(4)
	kEF(0x04),tech_upr
	kF(fBLKLAV)
	kE(0x6),t_nom_upr
	kE(0x1),knop
	kMSO(b'0011')	;011
	pADDC(tech_upr),0x04
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;10
	pSUBC(tech_upr),0x04
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>
;вент конденсора 2
;<<
	kTEST(1)
	kE(0x7),t_nom_upr
	kMSO(b'1')	;1
	Prstr,0x1,STR_VC2_UP
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(4)
	kEF(0x08),tech_upr
	kF(fBLKLAV)
	kE(0x7),t_nom_upr
	kE(0x1),knop
	kMSO(b'0011')	;011
	pADDC(tech_upr),0x08
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;10
	pSUBC(tech_upr),0x08
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>

;вент испарителя 3
;<<
	kTEST(2)
	kF(f_H_def)
	kE(0x8),t_nom_upr
	kMSO(b'01')	;1
	Prstr,0x1,STR_VI3_UP
	DW 0FEFEH
	kMSO(b'11')	;1
	Prstr,0x1,STR_HDF_UP
	DW 0FEFEH
	C_END
;>>
;нагрев поддона
;<<
	kTEST(4)
	kEF(0x10),tech_upr
	kF(fBLKLAV)
	kE(0x8),t_nom_upr
	kE(0x1),knop
	kMSO(b'0011')	;011
	pADDC(tech_upr),0x10
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;10
	pSUBC(tech_upr),0x10
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>



;доп клап 1
;
;<<клап COMP
;<<
	kTEST(2)
	kF(fYES_TCMP)
	kE(0x9),t_nom_upr
	kMSO(b'01')	;01
	Prstr,0x1,STR_С1_UP
	DW 0FEFEH
	kMSO(b'11')	;11
	Prstr,0x1,STR_СCP_UP
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(4)
	kEF(0x01),tech_upr_dop
	kF(fBLKLAV)
	kE(0x9),t_nom_upr
	kE(0x1),knop
	kMSO(b'0011')	;
	pADDC(tech_upr_dop),0x01
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;
	pSUBC(tech_upr_dop),0x01
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>

;доп клап 2
;<<
	kTEST(1)
	kE(0xA),t_nom_upr
	kMSO(b'1')	;1
	Prstr,0x1,STR_С2_UP
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(4)
	kEF(0x02),tech_upr_dop
	kF(fBLKLAV)
	kE(0xA),t_nom_upr
	kE(0x1),knop
	kMSO(b'0011')	;
	pADDC(tech_upr_dop),0x02
	pBSF(fBLKLAV)
	DW 0FEFEH
	kMSO(b'1011')	;
	pSUBC(tech_upr_dop),0x02
	pBSF(fBLKLAV)
	DW 0FEFEH
	C_END
;>>


;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;<< ПРИ НЕИСПРАВН. КЛАПАНОВ
	kTEST(4)
	kF(fZMKC_DEF)
	kF(fOBRC_DEF)
	kF(fMIGAN)
	kE(0x1),t_nom_upr
	MSO(b'1011')	;0
	Prstr,0x01,STR_С_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'0111')	;0
	Prstr,0x01,STR_С_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;
;<< ПРИ НЕИСПРАВН. КЛАПАНОВ
	kTEST(4)
	kF(fZMKC_CON)
	kF(fOBRC_CON)   ;(fOBRC_CON_T)
	kF(fMIGAN)
	kE(0x2),t_nom_upr
	MSO(b'1011')	;0
	Prstr,0x01,STR_СC_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'0111')	;0
	Prstr,0x01,STR_СC_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;<< ПРИ НЕИСПРАВН. OC1
	kTEST(5)
	kF(multi1)
	kF(fZMKC1_ISP)
	kF(fOBRC1_ISP)
	kF(fMIGAN)
	kE(0x2),t_nom_upr
	MSO(b'11011')	;0
	Prstr,0x01,STR_С1I_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'10111')	;0
	Prstr,0x01,STR_С1I_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;
;<< ПРИ НЕИСПРАВН. ДОП КЛАПАНОВ
	kTEST(5)
	kF(fYES_TCMP)
	kF(fZMKC1_ISP)
	kF(fOBRC1_ISP)
	kF(fMIGAN)
	kE(0x9),t_nom_upr
	MSO(b'01011')	;0
	Prstr,0x01,STR_С1I_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'00111')	;0
	Prstr,0x01,STR_С1I_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'11011')	;0
	Prstr,0x01,STR_СCP_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'10111')	;0
	Prstr,0x01,STR_СCP_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;
;<< ПРИ НЕИСПРАВН. ДОП КЛАПАНОВ
	kTEST(4)
	kF(fZMKC2_ISP)
	kF(fOBRC2_ISP)
	kF(fMIGAN)
	kE(0xA),t_nom_upr
	MSO(b'1011')	;0
	Prstr,0x01,STR_С2I_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'0111')	;0
	Prstr,0x01,STR_С2I_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;
;<< ПРИ НЕИСПРАВН. НАГРЕВА ПОДДОНА
	kTEST(5)
	kF(f_H_def)
	kF(fZMKH_DEF)
	kF(fOBRH_DEF)
	kF(fMIGAN)
	kE(0x8),t_nom_upr
	MSO(b'11011')	;0
	Prstr,0x01,STR_СDF_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'10111')	;0
	Prstr,0x01,STR_СDF_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;<< ПРИ НЕИСПРАВН. КОМПРЕССОРА
	kTEST(5)
	kF(multi2)
	kF(fZMK_COMP)
	kF(fOBR_COMP)
	kF(fMIGAN)
	kE(0x3),t_nom_upr
	MSO(b'01011')	;0
	Prstr,0x01,STR_СOMP_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'00111')	;0
	Prstr,0x01,STR_СOMP_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;<< ПРИ НЕИСПРАВН. OC2
	kTEST(5)
	kF(multi2)
	kF(fZMKC2_ISP)
	kF(fOBRC2_ISP)
	kF(fMIGAN)
	kE(0x3),t_nom_upr
	MSO(b'11011')	;0
	Prstr,0x01,STR_С2I_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'10111')	;0
	Prstr,0x01,STR_С2I_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;<< ПРИ НЕИСПРАВН. ВЕНТИЛЯТ. ИСПАРИТЕЛЯ 1
	kTEST(5)
	kF(fBLK_ISP1)
	kF(fOBRV_ISP1)
	kF(fZMKV_ISP1)
	kF(fMIGAN)
	kE(0x4),t_nom_upr
	MSO(b'10011')	;
	Prstr,0x01,STR_VI_BLK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'01011')	;
	Prstr,0x01,STR_VI_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'00111')	;
	Prstr,0x01,STR_VI_ZMK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>

;<< ПРИ НЕИСПРАВН. ВЕНТИЛЯТ. ИСПАРИТЕЛЯ 1 3
	kTEST(7)
	kEF(0x01),f_config_t
	kF(multi2)
	kF(fBLK_ISP3)
	kF(fOBRV_ISP3)
	kF(fZMKV_ISP3)
	kF(fMIGAN)
	kE(0x4),t_nom_upr
	MSO(b'0110011')	;
	Prstr,0x01,STR_VI_BLK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'0101011')	;
	Prstr,0x01,STR_VI_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'0100111')	;
	Prstr,0x01,STR_VI_ZMK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>



;<< ПРИ НЕИСПРАВН. ВЕНТИЛЯТ. ИСПАРИТЕЛЯ 2
	kTEST(5)
	kF(fBLK_ISP2)
	kF(fOBRV_ISP2)
	kF(fZMKV_ISP2)
	kF(fMIGAN)
	kE(0x5),t_nom_upr
	MSO(b'10011')	;
	Prstr,0x01,STR_VI_BLK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'01011')	;
	Prstr,0x01,STR_VI_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'00111')	;
	Prstr,0x01,STR_VI_ZMK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;<< ПРИ НЕИСПРАВН. ВЕНТИЛЯТ. ИСПАРИТЕЛЯ 3
	kTEST(6)
	kF(f_H_def)
	kF(fBLK_ISP3)
	kF(fOBRV_ISP3)
	kF(fZMKV_ISP3)
	kF(fMIGAN)
	kE(0x8),t_nom_upr
	MSO(b'010011')	;
	Prstr,0x01,STR_VI_BLK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'001011')	;
	Prstr,0x01,STR_VI_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'000111')	;
	Prstr,0x01,STR_VI_ZMK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;<< ПРИ НЕИСПРАВН. ВЕНТИЛЯТ. Конденсора 1
	kTEST(5)
	kF(fBLK_CON1)
	kF(fOBRV_CON1)
	kF(fZMKV_CON1)
	kF(fMIGAN)
	kE(0x6),t_nom_upr
	MSO(b'10011')	;
	Prstr,0x01,STR_VC_BLK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'01011')	;
	Prstr,0x01,STR_VC_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'00111')	;
	Prstr,0x01,STR_VC_ZMK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>

;<< ПРИ НЕИСПРАВН. ВЕНТИЛЯТ. Конденсора 2
	kTEST(5)
	kF(fBLK_CON2)
	kF(fOBRV_CON2)
	kF(fZMKV_CON2)
	kF(fMIGAN)
	kE(0x7),t_nom_upr
	MSO(b'10011')	;
	Prstr,0x01,STR_VC_BLK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'01011')	;
	Prstr,0x01,STR_VC_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'00111')	;
	Prstr,0x01,STR_VC_ZMK
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>

;<< ПРИ НЕИСПРАВН. КАБЕЛЯ ПОДДОНА
	kTEST(4)
	kF(fOBRV_CON1)
	kF(fOBRV_CON2)
	kF(fMIGAN)
	kE(0x8),t_nom_upr
	MSO(b'1011')	;
	Prstr,0x01,STR_СDF_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'0111')	;
	Prstr,0x01,STR_СDF_OBR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>
;<< ПРИ НЕИСПРАВН. КАБЕЛЯ ПОДДОНА
	kTEST(4)
	kF(fZMKV_CON1)
	kF(fZMKV_CON2)
	kF(fMIGAN)
	kE(0x8),t_nom_upr
	MSO(b'1011')	;
	Prstr,0x01,STR_СDF_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	MSO(b'0111')	;
	Prstr,0x01,STR_СDF_ERR
	pBSF(f_AVRSTR)
	DW 0FEFEH
	C_END
;>>

;;<<
;	kTEST(2)
;	kN(0xe),t_nom_upr
;	kE(0x0),knop
;	kMSO(b'11')	;1
;	pMOVLF(tech_upr),0
;	pMOVLF(tech_upr_dop),0
;	DW 0FEFEH
;	C_END
;;>>

;<<
	kTEST(2)
	kF(fBLKLAV)
	kE(0),knop
	kMSO(03)	;11
	pBCF(fBLKLAV)
	pBUZOFF
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(2)
	kF(fBLKLAV)
	kE(0),knop
	kMSO(b'01')	;11
	pBUZOFF
	DW 0FEFEH
	C_END
;>>
	C_END




;*********************************************
;	РЕЖИМ ВКЛЮЧЕНИЯ ВЫКЛЮЧЕНИЯ
;	И ИЗМЕНЕНИЯ ЗАДАННОЙ ТЕМПЕРАТУРЫ
;*********************************************
REJ_UPR:
	pBCF(fONOFF)
;
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
;	OFF(uC_ISP)
;
	kGO
;
;<<
	kTEST(2)
	kF(fONOFF)
	kF(faONOFF)
	kMSO(0x3)	;11
	pBSF(fOTKL)
	DW 0FFFFH
	m ONOFF_A
	C_END
;>>

	OFF(uV_CON)

; включение вентил конденсора по среднему давл.
;<<
	kTEST(3)
	kF(fON_CNDL)	
	kF(fONOFF)
	kF(kP_MID)	
	kMSO(B'101')
	ON(uV_CON)
	DW 0FEFEH
	C_END
;>>

;;<<УПРАВЛ. ОТКЛ. ВЕНТ. КОНДЕНСОРА f_davl_an=1
;	kTEST(5)
;	kE(0x0),sSTATUS
;	kF(f_davl_an)
;	kF(kP_AVR)
;	kF(uCOMP)
;	kF(kP_MID)
;	MSO(b'01111')
;	ON(uV_CON)
;	DW 0FEFEH
;	MSO(b'01011')
;	ON(uV_CON)
;	DW 0FEFEH
;	MSO(b'01101')
;	ON(uV_CON)
;	DW 0FEFEH
;	C_END
;;>>
;;<< УПРАВЛ. ВЕНТИЛЯТ. ПО P_MID COOL f_davl_an=0
;	kTEST(6)
;	kE(0x0),sSTATUS
;	kN(0x4),sSTATUS
;	kF(f_davl_an)
;	kF(uCOMP)
;	kF(kP_AVR)
;	kF(kP_MID)
;	MSO(b'010111')
;	ON(uV_CON)
;	DW 0FEFEH
;	MSO(b'010101')
;	ON(uV_CON)
;	DW 0FEFEH
;	MSO(b'010011')
;	ON(uV_CON)
;	DW 0FEFEH
;	C_END
;;>>
;;<< УПРАВЛ. ВЕНТИЛЯТ. ПО P_MID HEAT f_davl_an=0
;	kTEST(5)
;	kN(0x4),sSTATUS
;	kF(f_davl_an)
;	kF(uCOMP)
;	kF(kP_AVR)
;	kF(kP_MID)
;	MSO(b'00111')
;	ON(uV_CON)
;	DW 0FEFEH
;	MSO(b'00011')
;	ON(uV_CON)
;	DW 0FEFEH
;	C_END
;;>>

;::::::::::::::::::::::::::::::::::::::::::::::::::
;:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;***************************************************
	kKLAV(0x0D)
	m ONOFF
	m MINUS_T_HOT
	m PLUS_T_HOT
;
;ОТСЧЕТ 15 СЕКУНД ДЛЯ АВТОМАТИЧЕСКОГО ВКЛЮЧЕНИЯ 
;<<f_wr_err
	kTEST(4)
	kE(0x1),sONOFF
	kF(fEQTIMES)	
	kF(fONOFF)
	kN(D'15'),tSECVKL
	MSO(b'1101')	
	pINC10(tSECVKL)
	DW 0FEFEH
	kMSO(b'1100')
	pBCF(fEQTIMES)
	pBSF(fONOFF)
	DW 0FEFEH	
	C_END
;>>	

;new_stb  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;<< 
	kTEST(3)
	kF(fON_STANB)
	kF(fSTANB)
	kF(fONOFF)
	MSO(b'011')
	pBSF(fON_STANB)
	WrEEin(eblok_fl),blok_fl
	DW 0FEFEH	
	C_END
;>>	
;<< 
	kTEST(5)
	kN(D'5'),tOFF_A
	kF(fON_STANB)
	kF(fSTANB)
	kF(fONOFF)
	kN(D'15'),tON_VKL
	MSO(b'11101')
	pINC10(tON_VKL)
	DW 0FEFEH
	MSO(b'11100')
;	pCLRF(tON_VKL)
	pINC10(tON_VKL)
	pBSF(fONOFF)
	pBSF(fCOLD)
	pCLRF(tON_VKL)
	pMOVLF(tSECVKL),D'16'
	pMOVLF(sONOFF),D'1'
	DW 0FEFEH
	C_END
;>>	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;<<
	kTEST(5)
	kF(YES_OTOP)
	kE(0x1),sONOFF
	kF(fONOFF)
	kF(fHOTDO)
	kE(D'16'),tSECVKL
	MSO(b'01111')	
   	pSAV(S1OZUPR),UPR_HOT
	pINC10(tSECVKL)
	DW 0FEFEH	
	C_END
;>>	

;<<
	kTEST(5)
	kF(fHOTDO)
	kE(0x1),sONOFF
	kF(fONOFF)
	kF(fCOLD)
	kE(D'16'),tSECVKL
	MSO(b'01111')	
   	pSAV(S1OZUPR),UPR_COLD
	pINC10(tSECVKL)
	DW 0FEFEH	
	C_END
;>>	
;**************************************
;<<
	kTEST(5)
	kF(fHOTDO)
	kE(0x1),sONOFF
	kF(fONOFF)
	kF(fONDEFR)
	kE(D'16'),tSECVKL
	MSO(b'01111')	
   	pSAV(S1OZUPR),UPR_DEFR
	pINC10(tSECVKL)
	DW 0FEFEH	
	C_END
;>>	



;******************************************************
;******************************************************
;ОПРОС ВЫКЛЮЧЕНИЯ ЗАЖИГАНИЯ
;******************************************************
;<<
	kTEST(5)
	kF(fSLEEP)
	kF(fDO_SLEEP)
;	kF(fONOFF)
	kE(D'0'),tENDHOT
	kF(fNO_OFF)
	kN(D'60'),U_nap
	kMSO(b'00101')  ; (b'001101')
	pBSF(fSLEEP) 
	pBCF(fONOFF)
	pCLRF(tSECVKL)
	pBSF(fNO_U_nap) 
	pMOVLF(CLOC1m),D'60'
	pBCF(fBUZ)
	DW 0FEFEH
;	kMSO(b'000101') 
;	pBSF(fSLEEP) 
;	pBCF(fONOFF)
;	pCLRF(tSECVKL)
;	pBSF(fNO_U_nap) 
;	pMOVLF(CLOC1m),D'60'
;	pBCF(fBUZ)
;	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(1)
	kN(D'60'),U_nap
	kMSO(b'0') 
	pBCF(fNO_U_nap) 
	pBCF(fDO_SLEEP)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(5)
	kF(fDO_SLEEP)
	kF(fEQTIMES)	
	kF(fONOFF)
	kF(fNO_OFF)
	kN(D'40'),U_nap
	kMSO(b'00001')  
	pBSF(fSLEEP)
;	pBSF(fNO_OFF)
	pCLRF(tSECVKL)
	pBCF(fBUZ)
	DW 0FEFEH
	kMSO(b'00000')  
	pBCF(fSLEEP)
	pBSF(fEQTIMES)
	pCLRF(tSECVKL)
	DW 0FEFEH
	C_END
;>>
;
;ВЫХОД ИЗ ДЕЖУРНОГО РЕЖИМА ПО ВРЕМЕНИ
;
;<<
	kTEST(2)
	kF(fSLEEP)
	kN(D'120'),tON_OFF_2h
	kMSO(b'11')  
	pINC1M(tON_OFF_2h)
	DW 0FEFEH
	kMSO(b'01')  
	pCLRF(tON_OFF_2h)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(2)
	kF(fSLEEP)
	kN(D'50'),tON_OFF
	kMSO(b'11')  
	pINC(tON_OFF)	
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(3)
	kN(D'50'),tON_OFF
	kF(fSLEEP)
	kE(0x1),sONOFF
	kMSO(b'010')  
	pBSF(fNO_OFF)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(4)
	kF(fONDEFR)
	kN(D'30'),tON_OFF_2h	;D'10'
	kF(fSLEEP)
	kE(0x1),sONOFF
	kMSO(b'0011') 
	pCLRF(tONCOLD5)
	pCLRF(tONCOLD)
	WrEEin(etONCOLD5),tONCOLD5
	WrEEin(etONCOLD),tONCOLD
	pBSF(fNO_OFF)
	DW 0FEFEH
	kMSO(b'1011') 
	pCLRF(tONCOLD5)
	pCLRF(tONCOLD)
	WrEEin(etONCOLD5),tONCOLD5
	WrEEin(etONCOLD),tONCOLD
	pBSF(fNO_OFF)
	pBCF(fONDEFR)
	pBSF(fCOLD)
	WrEEin(eblok_fl),blok_fl
	DW 0FEFEH
	C_END
;>>


;<<
	kTEST(2)
	kF(multi2)
	kORL
	kF(multi1)
	kMS(b'11') 
	m SIN_MULTI
	C_END
;>>
;
	C_END
;
;********************************************
SIN_MULTI:
;<<
	kTEST(1)
	kF(multi2)
	kMS(b'0') 
	m NO_MULT2 
	C_END
;>>
;2222222222222222222222222222222222222222222222222222222222222
;2-я обнуление fWAIT если 1-я выключена
;<<
	kTEST(1)
	kE(0x0),sSTATUS1
	kMSO(b'1')  
	pBCF(fWAIT)
	DW 0FFFFH
	m NO_MULT2 
	C_END
;>>


;2-я охлаждение 1-я разморозка
;<<
	kTEST(2)
	kE(0x4),sSTATUS1
	kE(0x1),sSTATUS
	kMSO(b'11')  
	pBSF(fWAIT)
	DW 0FFFFH
	m NO_MULT2 
	C_END
;>>
;2-я разморозка 1-я разморозка
;<<
	kTEST(2)
	kE(0x3),sSTATUS1
	kE(0x3),sSTATUS
	kMSO(b'11')  
	pBCF(fWAIT)
	DW 0FFFFH
	m NO_MULT2 
	C_END
;>>
;<<
	kTEST(2)
	kE(0x3),sSTATUS1
	kE(0x4),sSTATUS
	kMSO(b'11')  
	pBSF(fWAIT)
	DW 0FFFFH
	m NO_MULT2 
	C_END
;>>
;<<
	kTEST(2)
	kE(0x4),sSTATUS1
	kE(0x4),sSTATUS
	kMSO(b'11')  
	pBCF(fWAIT)
	DW 0FFFFH
	m NO_MULT2 
	C_END
;>>
NO_MULT2:

;11111111111111111111111111111111111111111111111111111111111111111
;&&&&&&&&&&&&&&&&&&&
;<<
	kTEST(1)
	kF(multi1)
	kMS(b'0') 
	m NO_MULT1 
	C_END
;>>
;1-я обнуление fWAIT если 2-я выключена
;<<
	kTEST(1)
	kE(0x0),sSTATUS2
	kMSO(b'1')  
	pBCF(fWAIT)
	DW 0FFFFH
	m NO_MULT1 
	C_END
;>>



;******************************************************

;1-я охлаждение 2-я разморозка
;<<
	kTEST(2)
	kE(0x4),sSTATUS2
	kE(0x1),sSTATUS
	kMSO(b'11')  
	pBSF(fWAIT)
	DW 0FFFFH
	m NO_MULT1 
	C_END
;>>
;1-я разморозка 2-я разморозка
;<<
	kTEST(2)
	kE(0x3),sSTATUS2
	kE(0x3),sSTATUS
	kMSO(b'11')  
	pBCF(fWAIT)
	DW 0FFFFH
	m NO_MULT1 
	C_END
;>>
;<<
	kTEST(2)
	kE(0x3),sSTATUS2
	kE(0x4),sSTATUS
	kMSO(b'11')  
	pBSF(fWAIT)
	DW 0FFFFH
	m NO_MULT1 
	C_END
;>>
;<<
	kTEST(2)
	kE(0x4),sSTATUS2
	kE(0x4),sSTATUS
	kMSO(b'11')  
	pBCF(fWAIT)
	DW 0FFFFH
	m NO_MULT1 
	C_END
;>>
NO_MULT1:
;
	C_END
;
;
;
;
;*****************************************
MINUS_T_HOT:
;<<
	kTEST(3)
	kF(fYES_OTOP)
	kF(fSLEEP)
	kF(fNO_U_nap)
	kMSO(b'011')	;
	pBUZOFF
	DW 0FFFFH
	m UPR_END
	C_END
;>>	


;fCHANG_TDEF
;<< ЗАМЕНА ЗАДАННОЙ ТЕМПЕРАТУРЫ НА DEFR
	kTEST(1)
	kE(0),t_TDEF
	kMS(b'1')  
	m MINUS_T_HOT1 
	C_END
;>>

;<<
	kTEST(3)
	kF(fONDEFR)
	kE(D'0'),tTIMER2
	kN(D'62'),T_FIN_DEF
	kMSO(b'000')	;0
	pMOVLF(tTIMER2),D'30'
	pDEC(T_FIN_DEF)
	WrEEin(eT_FIN_DEF),T_FIN_DEF	
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(3)
	kF(fONDEFR)
	kE(D'0'),tTIMER2
	kN(D'12'),tPER_DEF
	kMSO(b'100')	;0
	pMOVLF(t_TDEF),D'50'
	pMOVLF(tTIMER2),D'30'
	pDEC(tPER_DEF)
	WrEEin(etPER_DEF),tPER_DEF	
	DW 0FEFEH
	C_END
;>>
	C_END
;




MINUS_T_HOT1:

;<<
	kTEST(1)
	kF(fONDEFR)
	kMS(b'1')
	m NO_T_HOT1
	C_END
;>>

;<<
	kTEST(1)
	kF(fTECH_DLT)
	kMS(b'1')
	m T_TECH_DLT_M
	C_END
;>>

;<<
	kTEST(3)
	kF(multi2)
	kE(D'0'),tTIMER2
	kNA(T_SET_COLD_MIN),sZADT
	kMSO(b'000')	;0
	pMOVLF(tTIMER2),D'30'
	pDEC(sZADT)
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi2)
	kE(D'0'),tTIMER2
	kN(D'55'),sZADT
	kMSO(b'100')	;0
	pMOVLF(tTIMER2),D'30'
	pDEC(sZADT)
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	kMSO(b'101')	;0
	pMOVLF(tTIMER2),D'30'
	pMOVLF(sZADT),D'55'
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(5)
	kF(fYES_OTOP)
	kF(fAUTO)
	kF(fHOT_COLD)
	kE(D'0'),tTIMER2
	kNA(sZADT),T_SET_HOT_MAX
	kMSO(b'00101')	;0
	pMOVLF(tTIMER2),D'30'
	pMOVB(T_SET_HOT_MAX),sZADT
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(4)
	kF(fYES_OTOP)
	kF(fAUTO)
	kE(D'0'),tTIMER2
	kNA(sZADT),T_SET_HOT_MAX
	kMSO(b'0101')	;0
	pMOVLF(tTIMER2),D'30'
	pMOVB(T_SET_HOT_MAX),sZADT
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(1)
	kE(D'0'),tTIMER2
	kMSO(b'1')	;
	pMOVLF(tTIMER2),D'30'
	DW 0FEFEH
	C_END
;>>
NO_T_HOT1:
	C_END
;

T_TECH_DLT_M:
;<<
	kTEST(2)
	kN(0x5),dTp
	kORL
	kN(0xfa),dTp
	kMSO(b'10')	;0
	pDEC(dTp)
	WrEEin(edTp),dTp
	DW 0FEFEH
	C_END
;>>
	C_END
;

T_TECH_DLT_P:
;<<
	kTEST(2)
	kN(0x3),dTp
	kORL
	kN(0xf9),dTp
	kMSO(b'10')	;0
	pINC(dTp)
	WrEEin(edTp),dTp
	DW 0FEFEH
	C_END
;>>
	C_END
;

;*******
PLUS_T_HOT:
;<<
	kTEST(3)
	kF(fYES_OTOP)
	kF(fSLEEP)
	kF(fNO_U_nap)
	kMSO(b'011')	;
	pBUZOFF
	DW 0FFFFH
	m UPR_END
	C_END
;>

;fCHANG_TDEF
;<< ЗАМЕНА ЗАДАННОЙ ТЕМПЕРАТУРЫ НА DEFR
	kTEST(1)
	kE(0),t_TDEF
	kMS(b'1')  
	m PLUS_T_HOT1 
	C_END
;>>

;<<
	kTEST(3)
	kF(fONDEFR)
	kE(D'0'),tTIMER2
	kN(D'66'),T_FIN_DEF
	kMSO(b'001')	;
	pMOVLF(tTIMER2),D'30'
	pINC(T_FIN_DEF)
	WrEEin(eT_FIN_DEF),T_FIN_DEF	
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(fONDEFR)
	kE(D'0'),tTIMER2
	kN(D'51'),tPER_DEF    ;35
	kMSO(b'101')	;
	pMOVLF(t_TDEF),D'50'
	pMOVLF(tTIMER2),D'30'
	pINC(tPER_DEF)
	WrEEin(etPER_DEF),tPER_DEF	
	DW 0FEFEH
	C_END
;>>
	C_END
;


PLUS_T_HOT1:
;<<
	kTEST(1)
	kF(fONDEFR)
	kMS(b'1')
	m NO_T_HOT1
	C_END
;>>

;<<
	kTEST(1)
	kF(fTECH_DLT)
	kMS(b'1')
	m T_TECH_DLT_P
	C_END
;>>

;<<
	kTEST(3)
	kF(fYES_OTOP)
	kE(D'0'),tTIMER2
	kN(D'89'),sZADT
	kMSO(b'101')	;0
	pMOVLF(tTIMER2),D'30'
	pINC(sZADT)
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(5)
	kF(fYES_OTOP)
	kF(fAUTO)
	kF(fHOT_COLD)
	kE(D'0'),tTIMER2
	kN(D'91'),sZADT
	kMSO(b'00001')	;0
	pMOVLF(tTIMER2),D'30'
	pINC(sZADT)
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(5)
	kF(fYES_OTOP)
	kF(fAUTO)
	kF(fHOT_COLD)
	kE(D'0'),tTIMER2
	kNA(sZADT),T_SET_HOT_MAX
	kMSO(b'00100')	;0
	pMOVLF(tTIMER2),D'30'
	pINC(sZADT)
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	kMSO(b'00101')	;0
	pMOVLF(tTIMER2),D'30'
	pMOVB(T_SET_HOT_MAX),sZADT
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(4)
	kF(fYES_OTOP)
	kF(fAUTO)
	kE(D'0'),tTIMER2
	kNA(sZADT),T_SET_HOT_MAX
	kMSO(b'0100')	;0
	pMOVLF(tTIMER2),D'30'
	pINC(sZADT)
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	kMSO(b'0101')	;0
	pMOVLF(tTIMER2),D'30'
	pMOVB(T_SET_HOT_MAX),sZADT
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(1)
	kE(D'0'),tTIMER2
	kMSO(b'1')	;
	pMOVLF(tTIMER2),D'30'
	DW 0FEFEH
	C_END
;>>	
	C_END
;
; ПРОЦЕДУРА ВКЛЮЧЕНИЯ И ВЫКЛЮЧЕНИЯ
;

ONOFF_A:
;<< 
	kTEST(5)
	kF(fON_STANB)
	kF(fSTANB)
	kF(fONOFF)
	kF(f_stop_zmk)
	kN(D'6'),tOFF_A
	kMSO(b'11111')
	pINC(tOFF_A)
	DW 0FFFFH
	m ONOFF_1	
	C_END
;>>	
	kJUMP
	m ONOFF_1
;>>	


ONOFF:
;<< 
	kTEST(3)
	kF(fON_STANB)
	kF(fSTANB)
	kF(fONOFF)
	MSO(b'111')
	pBCF(fON_STANB)
	WrEEin(eblok_fl),blok_fl
	pCLRF(tOFF_A)
	DW 0FEFEH	
	C_END
;>>	

;
ONOFF_1:
;<<
	kTEST(4)
	kE(D'0'),OTOP_SLEEP
	kF(fYES_OTOP)
	kF(fSLEEP)
	kF(fNO_U_nap)
	kMSO(b'1111')	;
	pBSF(fONOFF)
	pBCF(fSLEEP)
	pBSF(fDO_SLEEP)
	DW 0FFFFH
	m UPR_END
	C_END
;>>	

;<<
	kTEST(3)
	kF(fYES_OTOP)
	kF(fSLEEP)
	kF(fNO_U_nap)
	kMSO(b'011')	;
	pBCF(fONOFF)
	pBUZOFF

;	pBCF(fON_STANB)
;	WrEEin(eblok_fl),blok_fl

;	pBCF(fSLEEP)
;	pBSF(fDO_SLEEP)
	DW 0FFFFH
	m UPR_END
	C_END
;>>	

;<<
	kTEST(1)
	kF(f_no_work)
	kMSO(b'1')	;
	pBCF(fONOFF)
	pBCF(fOTKL)
;
	pCLRF(UPR_BT)
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
;	OFF(uC_ISP)
	pBCF(uKL_CMP) ;включ клап охл компр
	pSAV(S1OZUPR),0x0
	pMOVLF(sONOFF),0
	WrEEin(eONOFF),sONOFF
	pCLRF(sSTATUS)
	pBCF(fWAIT)
	pBCF(fCHANGE)
	pCLRF(tENDHOT)
	DW 0FFFFH
	m UPR_END
	C_END
;>>	

;<<
	kTEST(2)
	kE(0x1),sONOFF	
	kF(fEQTIMES)
	kMSO(0x3)	;11
	pBCF(fEQTIMES)
	pMOVLF(sONOFF),0
	WrEEin(eONOFF),sONOFF
	pBSF(fONOFF)
	pCLRF(tENDHOT)
	DW 0FEFEH
;	m REJ_OFF
	C_END
;>>

;<<
	kTEST(3)
	kF(fSLEEP)
	kF(fHOT_COLD)
	kF(fONOFF)
	kMSO(b'011')
	pBCF(fONOFF)
    pCLRF(tENDHOT)
	pMOVLF(sONOFF),0
	WrEEin(eONOFF),sONOFF
	pBCF(fHOTDO)

;	pBCF(fON_STANB)
	WrEEin(eblok_fl),blok_fl

	pCLRF(t_OTOP_AVR)
	DW 0FFFFH
	m UPR_END
;
	kMSO(b'001')
	pBCF(uKL_CMP) ;включ клап охл компр
	pBCF(fONOFF)
;
	pCLRF(UPR_BT)
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
;	OFF(uC_ISP)
	pCLRF(sSTATUS)
	pBCF(fWAIT)
	pBCF(fCHANGE)
	pSAV(S1OZUPR),0x0
	pMOVLF(sONOFF),0
	WrEEin(eONOFF),sONOFF
	pBCF(fONDEFR)
	pBCF(fONDEFR_R)
	pBCF(fHOTDO)
	pBCF(fCOLD)

;	pBCF(fON_STANB)
   	WrEEin(eblok_fl),blok_fl

	pCLRF(tENDHOT)
	pCLRF(t_OTOP_AVR)
	DW 0FFFFH
	m UPR_END
	C_END
;>>

;<<
	kTEST(2)
	kF(fSLEEP)
	kF(fONOFF)
	MSO(b'00')		;0
	pBCF(fOTKL)
	pMOVLF(sONOFF),1
	WrEEin(eONOFF),sONOFF
;
	pBSF(fONOFF)
	pBCF(fEQTIMES)	
;	Prstr,ON_OFF,STR_ON
	pCLRF(zOPER)
	pCLRF(tENDHOT)
;
;	pBSF(uRS_ERR)
;
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(5)
	kF(fSLEEP)
	kF(fAUTO)
	kF(fONOFF)
	kF(fHOT_COLD)
	kF(fONDEFR)
	MSO(B'00110')
	pSAV(S1OZUPR),UPR_HOT
    pCLRF(tENDHOT)
	DW 0FEFEH
	MSO(B'00100')
	pSAV(S1OZUPR),UPR_COLD
    pCLRF(tENDHOT)
	DW 0FEFEH
	MSO(B'00101')
	pSAV(S1OZUPR),UPR_DEFR
    pCLRF(tENDHOT)
	DW 0FEFEH
	C_END
;>>


;<<
	kTEST(5)
	kF(fSLEEP)
	kF(fAUTO)
	kF(fONOFF)
;	kNA(T_air_dpl_a),sZADT
	kNA(T_air),sZADT
	kF(fONDEFR)
	MSO(B'01100')
	pSAV(S1OZUPR),UPR_HOT
    pCLRF(tENDHOT)
	DW 0FEFEH
	MSO(B'01110')
	pSAV(S1OZUPR),UPR_COLD
    pCLRF(tENDHOT)
	DW 0FEFEH
	MSO(B'01111')
	pSAV(S1OZUPR),UPR_DEFR
    pCLRF(tENDHOT)
	DW 0FEFEH
	C_END
;>>

UPR_END:
	C_END

;
tPERD	EQU 5

;*********************************************
;*********************************************
;	ПРОГРАММА УПРАВЛЕНИЯ ОХЛАЖДЕНИЕМ
;*********************************************
;*********************************************
UPR_COLD:
;	pCLRF(tTIMER1)
;	pBCF(fT_CMP_AVR)
;	pCLRF(tONCOLD5)
;	pCLRF(tONCOLD)
	pBCF(fSTART_HOT)
	pBCF(fCONTR_D)
;
	pBCF(fHOTDO)
	pBCF(fHOT_COLD)
	pBCF(fONDEFR)
	pBCF(fONDEFR_R)
	pBSF(fCOLD)
	WrEEin(eblok_fl),blok_fl
;
	pBCF(fEND_DEF)
	pCLRF(tENDDEF)
	pCLRF(tONDEF)
	pCLRF(tENDHOT)
;
	pMOVLF(sSTATUS),0x1
	pMOVLF(sSTATUS2),0x6
	pBCF(fWAIT)
;
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uC_ISP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;

;<< ПРОВЕРКА ТЕМПЕР. ИСПАРИТЕЛЯ
	kTEST(1)
	kN(D'61'),T_isp
	MSO(b'0')
	pCLRF(tONCOLD5)
	pCLRF(tONCOLD)
	WrEEin(etONCOLD5),tONCOLD5
	WrEEin(etONCOLD),tONCOLD
	DW 0FEFEH
	C_END
;>>

	kGO
;

;<<
	kTEST(1)
	kF(fDO_SLEEP)
	MS(b'1')  
	m UPR_COLD
	C_END
;>>

	ON(uV_ISP)
	OFF(uC_DEF)
	OFF(uC_CON)
;
;;<< 3o4
;	kTEST(3)
;	kF(multi1)
;	kE(0x5),sSTATUS2
;	kNA(sZADT),T_air_dmn_a
;	MSO(b'110')	;
;	ON(uCOMP)
;	ON(uV_ISP)
;	ON(uC_ISP)
;	pMOVLF(sSTATUS),0x1
;	pMOVLF(sSTATUS2),0x6
;	pBCF(fWAIT)
;	DW 0FEFEH
;	C_END
;;>>

;<<
	kTEST(3)
	kF(multi1)
	kE(0x5),sSTATUS2
	kE(0x6),sSTATUS2
	kMSO(b'101')  
	pBCF(fWAIT)
	DW 0FEFEH
	kMSO(b'110')  
	pBSF(fWAIT)
	OFF(uCOMP)
	OFF(uC_ISP)
	pMOVLF(sSTATUS),0x2
	DW 0FFFFH
	m no_Tair_c
	C_END
;>>

;<<УПРАВЛ. КОМПР. И ВЕНТИЛЯТОРАМИ
	kTEST(2)
	kF(fYES_OTOP)
	kNA(T_air_dpl),sZADT
	MSO(b'00')	;0
	OFF(uCOMP)
	OFF(uC_ISP)
	pMOVLF(sSTATUS),0x2
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(2)
	kF(fYES_OTOP)
	kNA(sZADT),T_air_dmn
	MSO(b'00')	;
	ON(uCOMP)
	ON(uV_ISP)
	ON(uC_ISP)
	pMOVLF(sSTATUS),0x1
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>

no_Tair_c:


;<<
	kTEST(3)
	kN(D'0'),POWER_OTOP
	kF(fYES_OTOP)
	kN(D'1'),zOPER_PL
	MSO(b'010')	;
	ON(uCOMP)
	ON(uV_ISP)
	ON(uC_ISP)
	pMOVLF(sSTATUS),0x1
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kE(D'0'),POWER_OTOP
	kF(fYES_OTOP)
	kN(D'1'),zOPER_PL
	MSO(b'110')	;
	ON(uCOMP)
	ON(uV_ISP)
	ON(uC_ISP)
	pMOVLF(sSTATUS),0x1
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;<<
	kTEST(1)
	kF(uKL_CMP)
	MSO(b'0')
	pBCF(fAVR_TCMP)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(6)
	kF(fOBR_Tcmp)
	kF(fZMK_Tcmp)
	kF(fYES_TCMP)
	kF(fAVR_TCMP)
	kN(D'174'),T_cmp
	kN(D'154'),T_cmp
;
	MSO(b'001100')
	pBSF(uKL_CMP) ;включ клап охл компр
	DW 0FEFEH
;
	MSO(b'001000')
	pBSF(uKL_CMP) ;включ клап охл компр
	pBSF(fAVR_TCMP)
	DW 0FEFEH
;
	MSO(b'001110')
	pBSF(uKL_CMP) ;включ клап охл компр
	pBSF(fAVR_TCMP)
	DW 0FEFEH
;
	MSO(b'001111')
	pBCF(uKL_CMP) ;включ клап охл компр
	pBCF(fAVR_TCMP)
	DW 0FEFEH
	C_END
;>>


;<<
	kTEST(2)
	kF(fYES_OTOP)
	kE(D'0'),zOPER_PL
	MSO(b'11')	;
	OFF(uCOMP)
	OFF(uC_ISP)
	pMOVLF(sSTATUS),0x1
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>


;<<
	kTEST(3)
	kF(fYES_OTOP)
	kF(fAUTO)
	kF(fHOT_COLD)
	MSO(b'101')	;
	OFF(uCOMP)
	DW 0FEFEH
	C_END
;>>	

;<<
	kTEST(1)
	kF(uCOMP)
	MSO(1)	;1
	ON(uC_ISP)
	DW 0FEFEH
	C_END
;>>
;	kF(fSYN_V_ISP)  cool	
;<< 
	kTEST(2)
	kF(fSYN_V_ISP)	
	kF(uCOMP)
	MSO(b'10')	;
	OFF(uV_ISP)
	DW 0FEFEH
	C_END
;>>


;<<УПРАВЛ. ОТКЛ. ВЕНТ. КОНДЕНСОРА 
	kTEST(3)
	kF(kP_AVR)
	kF(uCOMP)
	kF(kP_MID)
;	MSO(b'010')
;	OFF(uV_CON)
;	DW 0FEFEH
	MSO(b'111')
	OFF(uCOMP)
;	ON(uV_CON)
	DW 0FEFEH
;	MSO(b'011')
;	ON(uV_CON)
;	DW 0FEFEH
;	MSO(b'000')
;	OFF(uV_CON)
;	DW 0FEFEH
	C_END
;>>


;<<ОТКЛЮЧ. ВСЕГО ПРИ ОТКР.ДВЕРИ
;ИЛИ АВАРИИ ДАТЧ. ДАВЛ.
	kTEST(2)
	kF(kDOOR)
	kORL
	kF(fSLEEP)
	MSO(b'11')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
;	OFF(uC_ISP)
;
	pBCF(uKL_CMP) ;включ клап охл компр
	DW 0FEFEH
	C_END
;>>

;<<ОТКЛЮЧ. ВСЕГО 
;ИЛИ АВАРИИ ДАТЧ. ДАВЛ.
	kTEST(3)
	kF(fYES_OTOP)
	kF(kP_AVR)
	kF(kP_MID)
	MSO(b'010')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
;	OFF(uC_ISP)
	pBCF(uKL_CMP) ;включ клап охл компр
	DW 0FEFEH
	MSO(b'110')
	OFF(uCOMP)
;	OFF(uV_ISP)
	OFF(uV_CON)
	OFF(uC_ISP)
	pBCF(uKL_CMP) ;включ клап охл компр
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(2)
	kF(fONOFF)
	kN(D'14'),tSECVKL
	MSO(b'01')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
;	OFF(uC_ISP)
	pBCF(uKL_CMP) ;включ клап охл компр
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(1)
	kF(fWAIT)
	MSO(b'1')
	OFF(uCOMP)
	OFF(uC_DEF)
	OFF(uC_ISP)
	pBCF(uKL_CMP) ;включ клап охл компр
	DW 0FEFEH
	C_END
;>>

;3o5
;<<
	kTEST(3)
	kF(multi1)
	kE(0x5),sSTATUS2
	kE(0x2),sSTATUS
	MSO(b'111')
	OFF(uC_ISP)
	OFF(uV_ISP)
	DW 0FEFEH
	C_END
;>>


;ПЕРЕХОД НА НАГРЕВ В АВТОМАТЕ
;<<
	kTEST(5)
	kF(fOBRC_CON)
	kF(fYES_OTOP)
	kF(fAUTO)
	kF(fONOFF)
	kNA(T_air_dpl_a),sZADT
	MSO(B'00110')
	pSAV(S1OZUPR),UPR_HOT
	DW 0FEFEH
	C_END
;>>

;?? технологические
;tPERD	EQU 1
;	pMOVLF(tPER_DEF),2

;<< ПЕРЕХОД НА РАЗМОРОЗКУ СИНХРОННО
	kTEST(4)
	kE(0x0),mUPR_BT
	kF(multi1)
	kN(0x2),sSTATUS2
	kN(0x4),sSTATUS2
	MSO(b'0101')  
;	pBSF(fONDEFR_R)
	pBCF(fEND_DEF)
	pCLRF(tONCOLD5)
	pCLRF(tONCOLD)
;
	WrEEin(etONCOLD5),tONCOLD5
	WrEEin(etONCOLD),tONCOLD
	DW 0FFFFH
	m UPR_DEFR
	C_END
;>>
;<< ПЕРЕХОД НА РАЗМОРОЗКУ СИНХРОННО
	kTEST(4)
	kE(0x0),mUPR_BT
	kF(multi2)
	kN(0x2),sSTATUS1
	kN(0x4),sSTATUS1
	MSO(b'0101')  
;	pBSF(fONDEFR_R)
	pBCF(fEND_DEF)
	pCLRF(tONCOLD5)
	pCLRF(tONCOLD)
;
	WrEEin(etONCOLD5),tONCOLD5
	WrEEin(etONCOLD),tONCOLD
	DW 0FFFFH
	m UPR_DEFR
	C_END
;>>

;<< НЕТ ПЕРЕХОДА НА РАЗМОРОЗКУ
	kTEST(1)
	kE(D'52'),tPER_DEF
	MSO(b'1')	;
	pCLRF(tONCOLD5)
	pCLRF(tONCOLD)
	DW 0FEFEH
	C_END
;>>


;<< ОТСЧЕТ ВРЕМЕНИ ДО РАЗМОРОЗКИ
	kTEST(3)
	kF(fWAIT)
	kF(fSLEEP)
	kE(tPERD),tONCOLD5
	MSO(b'000')
	pINC1M(tONCOLD5)
	WrEEin(etONCOLD5),tONCOLD5
	DW 0FEFEH
	MSO(b'001')
	pCLRF(tONCOLD5)
	pINC(tONCOLD)
	WrEEin(etONCOLD5),tONCOLD5
	WrEEin(etONCOLD),tONCOLD
	DW 0FEFEH
	C_END
;>>

;<< ПЕРЕХОД НА РАЗМОРОЗКУ
	kTEST(2)
	kF(fONDEFR)	
	kORL
	kEA(tPER_DEF),tONCOLD
	MSO(3)	;11
	pCLRF(tONCOLD5)
	pCLRF(tONCOLD)
;
	WrEEin(etONCOLD5),tONCOLD5
	WrEEin(etONCOLD),tONCOLD
;
;
	pBSF(fONDEFR) 	;!!!!!!!
	pBCF(fEND_DEF)
	pBCF(fCOLD)
	DW 0FFFFH
	m UPR_DEFR
	C_END
;>>
NO_DEFR:
	C_END
;

;
;*********************************************
;*********************************************
;	ПРОГРАММА УПРАВЛЕНИЯ РАЗМОРОЗКОЙ
;*********************************************
;*********************************************
UPR_DEFR:

;<< ВЫБОР РУЧНОЙ РАЗМОРОЗКИ
	kTEST(5)
	kF(fONDEFR)
	kF(fONOFF)
	kE(D'90'),sZADT
	kF(fHOT_COLD)
	kF(YES_OTOP)
	kMS(b'11111')
	m NO_DEFR
	C_END
;>>

;<< 
	kTEST(1)
	kF(fONDEFR_R)
	MSO(0)	;0
	RdEEin(etDEF),tDEF	
	DW 0FEFEH
	MSO(1)	;1
	pMOVLF(tDEF),D'20'
	DW 0FEFEH
	C_END
;>>
;

	pCLRF(tONCOLD5)
	pCLRF(tONCOLD)
	WrEEin(etONCOLD5),tONCOLD5
	WrEEin(etONCOLD),tONCOLD
;
	pBCF(fHOT_COLD)
	pBCF(fHOTDO)
	pBCF(fCOLD)
	pCLRF(tONDEF)
	pMOVB(tONDEF),s_tONDEF
	pBCF(fWAIT)
	pBCF(fAVR_TCMP)
	pBCF(fEND_DEF)
;
;<< ПРОВЕРКА ТЕМПЕР. ИСПАРИТЕЛЯ
	kTEST(3)
	kF(fONDEFR_R)
	kF(fT2_ERR)
	kNA(T_FIN_DEF),T_isp
	MSO(0)	;000 
	pMOVLF(tENDDEF),D'110'
	pBSF(fEND_DEF)
	DW 0FEFEH
	C_END
;>>
;<< 
	kTEST(1)
	kF(fEND_DEF)
	MSO(0)	;0
	pCLRF(tENDDEF)
	pBSF(fONDEFR)
	WrEEin(eblok_fl),blok_fl
	DW 0FEFEH
	C_END
;>>
;	OFF(uC_DEF)
;	OFF(uC_CON)
;
	kGO

;
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;<< УПРАВЛ. ВЕНТИЛЯТ. И С_CON ПО P_MID
	kTEST(2)
	kF(fOBRC_CON)
	kF(kP_MID)
	MSO(b'01')	;01
	OFF(uC_CON)
	DW 0FEFEH
	MSO(b'11')	;11
	OFF(uC_CON)
	DW 0FEFEH
	MSO(b'00')	;00
	ON(uC_CON)
	DW 0FEFEH
	C_END
;>>
	OFF(uV_ISP)
	OFF(uV_CON)
	ON(uCOMP)
	ON(uC_DEF)
	pBSF(fONDEFR)
	pBCF(fCOLD)
	OFF(uC_ISP)
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;<<
	kTEST(6)
	kF(fOBR_Tcmp)
	kF(fZMK_Tcmp)
	kF(fYES_TCMP)
	kF(fAVR_TCMP)
	kN(D'174'),T_cmp
	kN(D'165'),T_cmp
;
	MSO(b'001100')
	OFF(uCOMP)
	pBSF(fAVR_TCMP)
	DW 0FEFEH
;
	MSO(b'001000')
	OFF(uCOMP)
	pBSF(fAVR_TCMP)
	DW 0FEFEH
;
	MSO(b'001110')
	OFF(uCOMP)
	DW 0FEFEH
;
	MSO(b'001111')
	pBCF(fAVR_TCMP)
	DW 0FEFEH
	C_END
;>>



;;<< 
;	kTEST(2)
;	kF(fONDEFR_R)
;	kNA(T_FIN_DEF),T_air
;	MSO(b'10')	;10
;	ON(uV_ISP)
;	DW 0FEFEH
;	MSO(b'11')	;11
;	OFF(uV_ISP)
;	DW 0FEFEH
;	C_END
;;>>

;<< 
	kTEST(2)
	kF(fEND_DEF)
	kE(0x0),t_def_Visp
	MSO(b'00')	;0
	ON(uV_ISP)
	pDEC(t_def_Visp)
	DW 0FEFEH
	C_END
;>>

;<<ОТКЛЮЧ. ВСЕГО ПРИ ОТКР.ДВЕРИ
;ИЛИ АВАРИИ ДАТЧ. ДАВЛ.
	kTEST(3)
	kF(kDOOR)
	kORL
	kF(kP_AVR)
	kORL
	kF(fSLEEP)
	MSO(b'111')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
	DW 0FEFEH
	C_END
;>>

;>>
	kTEST(2)
	kF(fONOFF)
	kN(D'14'),tSECVKL
	MSO(b'01')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
	DW 0FEFEH
	C_END
;>>


;<< ОТСЧЕТ ВРЕМЕНИ РАЗМОРОЗКИ
	kTEST(3)
	kF(fSLEEP)
	kF(fEND_DEF)
	kEA(tDEF),tONDEF
	MSO(b'000') 
	pINC1M(tONDEF)
	pMOVLF(sSTATUS),0x3
	DW 0FEFEH
	MSO(b'001')
	pBSF(fEND_DEF)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(1)
	kEA(s_tONDEF),tONDEF
	MSO(b'0') 
	pMOVB(tONDEF),s_tONDEF
	pMOVLF(t_def_Visp),D'30'
	DW 0FEFEH
	C_END
;>>


;<< ПРОВЕРКА ТЕМПЕР. ИСПАРИТЕЛЯ
	kTEST(4)
	kF(fONDEFR_R)
	kF(fEND_DEF)
	kF(fT2_ERR)
	kNA(T_FIN_DEF),T_isp
	MSO(0)	;0000 
	pBSF(fEND_DEF)
	DW 0FEFEH
	C_END
;>>
;<< 
	kTEST(1)
	kF(fONDEFR_R)
	MSO(1)	;1
	pMOVB(T_FIN_DEF),sI_CL1
	pINC(sI_CL1)
;	pINC(sI_CL1)
;	pINC(sI_CL1)
;	pINC(sI_CL1)
;	pINC(sI_CL1)
	DW 0FEFEH
	C_END
;>>

;<< ПРОВЕРКА ТЕМПЕР. ИСПАРИТЕЛЯ
	kTEST(4)
	kF(fONDEFR_R)
	kF(fEND_DEF)
	kF(fT2_ERR)
	kNA(sI_CL1),T_isp
	MSO(b'1000')	;1000 
	pBSF(fEND_DEF)
	DW 0FEFEH
	C_END
;>>

;<<ОКОНЧАНИЕ РАЗМОРОЗКИ
;ОТСЧЕТ ЗАЩИТНОГО ИНТЕРВАЛА
	kTEST(3)
	kF(fONDEFR_R)
	kN(D'120'),tENDDEF
	kF(fEND_DEF)
	MSO(b'011')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uC_DEF)
;	OFF(uC_CON)
;	OFF(uV_ISP)
	pINC10(tENDDEF)	
	pMOVLF(sSTATUS),0x4
	DW 0FEFEH
	MSO(b'001')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uC_DEF)
;	OFF(uC_CON)
;	OFF(uV_ISP)
	pMOVLF(sSTATUS),0x4
	DW 0FEFEH
	C_END
;>>
;<<ОКОНЧАНИЕ РАЗМОРОЗКИ
;ОТСЧЕТ ЗАЩИТНОГО ИНТЕРВАЛА
	kTEST(4)
	kF(fONDEFR_R)
	kN(D'240'),tENDDEF
	kN(D'120'),tENDDEF
	kF(fEND_DEF)
	MSO(b'1101')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uC_DEF)
;	OFF(uC_CON)
;	OFF(uV_ISP)
	pINC10(tENDDEF)	
	pMOVLF(sSTATUS),0x4
	DW 0FEFEH
	MSO(b'1111')
	pINC10(tENDDEF)	
	pMOVLF(sSTATUS),0x4
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(2)
	kE(D'0'),tTIMER2
	kF(fEND_DEF)
	MSO(b'01')
	pMOVLF(tENDDEF),D'115'
	DW 0FEFEH
	C_END
;>>

;<< 
	kTEST(2)
	kF(multi1)
	kF(f_H_def)
	kMSO(b'11')	;111
	ON(uH_DEF)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(3)
	kF(multi1)
	kE(0x4),sSTATUS
	kE(0x3),sSTATUS2
	kMSO(b'111')  
	pCLRF(tENDDEF)	
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi2)
	kE(0x4),sSTATUS
	kE(0x3),sSTATUS1
	kMSO(b'111')  
	pCLRF(tENDDEF)	
	DW 0FEFEH
	C_END
;>>

;<<ВЫХОД ИЗ РАЗМОРОЗКИ
	kTEST(3)
	kF(multi2)
	kN(0x2),sSTATUS1
	kE(0x0),mUPR_BT
	MSO(b'100')
	pBSF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<ВЫХОД ИЗ РАЗМОРОЗКИ
	kTEST(3)
	kF(multi1)
	kN(0x2),sSTATUS2
	kE(0x0),mUPR_BT
	MSO(b'100')
	pBSF(fWAIT)
	DW 0FEFEH
	C_END
;>>

;<<ВЫХОД ИЗ РАЗМОРОЗКИ
	kTEST(2)
	kF(multi1)
	kN(0x4),sSTATUS2
	MSO(b'10')
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>

;<<ВЫХОД ИЗ РАЗМОРОЗКИ
	kTEST(4)
	kF(fONDEFR_R)
	kE(0x0),tTIMER2
	kF(fWAIT)
	kN(D'120'),tENDDEF
	MSO(b'0100')
	pBCF(fEND_DEF)
	pBCF(fONDEFR)
	pBCF(fONDEFR_R)
	pCLRF(tONDEF)
	pCLRF(tENDDEF)
	WrEEin(eblok_fl),blok_fl
	OFF(uC_DEF)
	OFF(uH_DEF)
	pCLRF(sSTATUS)
	DW 0FFFFH
	m UPR_COLD
	C_END
;>>
;<<ВЫХОД ИЗ РАЗМОРОЗКИ
	kTEST(4)
	kF(fONDEFR_R)
	kE(0x0),tTIMER2
	kF(fWAIT)
	kN(D'240'),tENDDEF
	MSO(b'1100')
	pBCF(fEND_DEF)
	pBCF(fONDEFR)
	pBCF(fONDEFR_R)
	pCLRF(tONDEF)
	pCLRF(tENDDEF)
	WrEEin(eblok_fl),blok_fl
	OFF(uC_DEF)
	OFF(uH_DEF)
	pCLRF(sSTATUS)
	DW 0FFFFH
	m UPR_COLD
	C_END
;>>
;<<ВЫХОД ИЗ РАЗМОРОЗКИ
	kTEST(1)
	kN(D'230'),tENDDEF
	MSO(b'0')
	pCLRF(sSTATUS)
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>

;
NO_HOT:
	C_END
;
	

;*********************************************
;*********************************************
;	ПРОГРАММА УПРАВЛЕНИЯ НАГРЕВОМ
;*********************************************
;*********************************************
UPR_HOT:
;<<&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	kTEST(2)
	kF(fYES_OTOP)
	kF(fAUTO)
	MS(b'11')  
	m UPR_COLD
	C_END
;>>
;<<&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	kTEST(2)
	kF(fYES_OTOP)
	kF(fHOT_COLD)
	MS(b'11')  
	m NO_HOT
	C_END
;>>

	pBSF(fHOTDO)
	pBCF(fCOLD)
	pBSF(fHOT_COLD)
	WrEEin(eblok_fl),blok_fl
;
	pBCF(fSTART_HOT)
	pCLRF(t_X_DAVL)
	pBCF(fSTART_HOT_t)
	pBCF(fCONTR_D)
	pCLRF(tENDHOT)
;
	pCLRF(tONCOLD5)
	pCLRF(tONCOLD)
;
	pBCF(fAVR_TCMP)
;
	kGO
;<<
	kTEST(3)
	kF(fOBRC_CON)
	kF(fYES_OTOP)
	kF(fAUTO)
	MSO(b'101')  
	pBCF(fHOT_COLD)
	WrEEin(eblok_fl),blok_fl
	DW 0FFFFH
	m UPR_COLD
	C_END
;>>
;<<
	kTEST(4)
	kF(fOBRC_CON)
	kF(fYES_OTOP)
	kF(fHOT_COLD)
	kF(fAUTO)
	MSO(b'1011')  
	pBCF(fHOT_COLD)
	WrEEin(eblok_fl),blok_fl
	DW 0FFFFH
	m UPR_COLD
	C_END
;>>

;
	WrEEin(etONCOLD5),tONCOLD5
	WrEEin(etONCOLD),tONCOLD
;
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_CON)
;	OFF(uC_CON)
;	OFF(uC_DEF)
;	OFF(uC_ISP)
;

;<<
	kTEST(1)
	kNA(sZADT),T_SET_HOT_MAX
	kMSO(b'1')	;
	pMOVB(T_SET_HOT_MAX),sZADT
	WrEEin(esZADT),sZADT
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(2)
	kF(multi1)
	kE(0x1),sSTATUS2
	kMSO(b'11')  
	pBSF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(2)
	kF(multi2)
	kE(0x1),sSTATUS1
	kMSO(b'11')  
	pBSF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(1)
	kEA(sZADT),T_air
	MSO(b'1')
	pMOVLF(sSTATUS),0x6
	DW 0FEFEH
	C_END
;>>
;
	kGO

;;<< УПРАВЛ. ВЕНТИЛЯТ. ПО P_MID
;	kTEST(2)
;	kF(kP_AVR)
;	kF(kP_MID)
;	MSO(b'11')
;	ON(uV_CON)
;	DW 0FEFEH
;	MSO(b'01')
;	OFF(uV_CON)
;	DW 0FEFEH
;	C_END
;;>>

;<< 
	kTEST(1)
	kF(fONOFF)
	MSO(b'0')
	DW 0FFFFH
	m UPR_END_HOT
	C_END
;>>


;	ON(uCOMP)
;	ON(uC_CON)
;	ON(uC_DEF)
;	ON(uV_ISP)
;
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
;<<
	kTEST(4)
	kF(multi2)
	kE(0x2),sSTATUS1
	kE(0x5),sSTATUS
	kN(D'19'),tWait_20m
	kMSO(b'1111')  
	pINC1M(tWait_20m)
	DW 0FEFEH
	kMSO(b'1110')  
	pBSF(fWAIT)
	pMOVLF(sSTATUS),0x6
	OFF(uCOMP)
	OFF(uC_DEF)
	OFF(uC_CON)
	DW 0FEFEH
	C_END
;>>


;<<
	kTEST(4)
	kF(multi2)
	kE(0x2),sSTATUS1
	kE(0x6),sSTATUS
	kN(D'2'),tPaus_20m
	kMSO(b'1110')  
	pCLRF(tWait_20m)
	pCLRF(tPaus_20m)
	pMOVLF(sSTATUS),0x5
	DW 0FEFEH
	kMSO(b'1111')  
	pINC10(tPaus_20m)
	pBSF(fWAIT)
	OFF(uCOMP)
	OFF(uC_DEF)
	OFF(uC_CON)
	DW 0FFFFH
	m no_Tair_h
	C_END
;>>


;<<
	kTEST(2)
	kF(multi2)
	kE(0x1),sSTATUS1
	kMSO(b'11')  
	pCLRF(tWait_20m)
	pCLRF(tPaus_20m)
	DW 0FEFEH
	C_END
;>>



;<<
	kTEST(2)
	kF(multi2)
	kE(0x1),sSTATUS1
;	kE(0x5),sSTATUS
	kMSO(b'11')  
	pBSF(fWAIT)
	pMOVLF(sSTATUS),0x6
	OFF(uCOMP)
	OFF(uC_DEF)
	OFF(uC_CON)
	DW 0FFFFH
	m no_Tair_h
	C_END
;>>



;<<УПРАВЛ. КОМПР.
	kTEST(2)
	kF(fSTART_HOT)
	kNA(sZADT),T_air_dmn
	MSO(b'10')	;10
	OFF(uCOMP)
	OFF(uC_DEF)
	OFF(uC_CON)
	OFF(uH_DEF)
	pMOVLF(sSTATUS),0x6
	DW 0FEFEH
	MSO(b'00')	;00
	OFF(uCOMP)
	OFF(uC_DEF)
	OFF(uC_CON)
	OFF(uH_DEF)
	pMOVLF(sSTATUS),0x6
	pBSF(fSTART_HOT)  ;
	DW 0FEFEH
	C_END
;>>
;<< NEW_B
	kTEST(1)
	kNA(sZADT),T_air_dpl_o
	MSO(b'1')
	ON(uCOMP)
	ON(uC_DEF)
	ON(uC_CON)
	ON(uV_ISP)
	ON(uH_DEF)
	pMOVLF(sSTATUS),0x5
	DW 0FEFEH
	C_END
;>>

no_Tair_h:

;<< NEW_B
	kTEST(1)
	kNA(sZADT),T_air_dpl_o
	MSO(b'1')
	ON(uV_ISP)
	ON(uH_DEF)
	DW 0FEFEH
	MSO(b'0')
;	ON(uV_ISP)
	OFF(uH_DEF)
	DW 0FEFEH
	C_END
;>>


;;<< БЛОКИР. С_CON если обрыв
;	kTEST(1)
;	kF(fOBRC_CON)
;	MSO(b'1')
;	OFF(uC_CON)
;	DW 0FEFEH
;	C_END
;;>>


;<< УПРАВЛ. С_CON 
	kTEST(2)
	kF(kP_MID)
	kF(kP_AVR)
	MSO(b'10')
	ON(uC_CON)
;
	pBCF(fCONTR_D)
	pCLRF(t_X_DAVL)
	pCLRF(tD_AVR)
	DW 0FEFEH
	MSO(b'11')
	OFF(uC_CON)
	DW 0FEFEH
	C_END
;>>




;
;<<НАЧАЛО ОТОПЛЕНИЯ
	kTEST(2)
	kF(fSTART_HOT)
	kNA(T_START_HOT),T_isp
	MSO(1)	;01
	ON(uCOMP)
	OFF(uV_ISP)
	DW 0FEFEH
	MSO(0)	;00
	pBSF(fSTART_HOT)
;	ON(uCOMP)
	DW 0FEFEH
	C_END
;>>

;<<ПЕРЕХОД К ПОВТОРНОМУ СТАРТУ ОТОПЛЕНИЯ
	kTEST(2)
	kF(fSTART_HOT)
	kNA(T_START_HOT2),T_isp
	MSO(3)	;11
	OFF(uV_ISP)
	DW 0FEFEH
	MSO(0x2)	;10
	ON(uV_ISP)
	DW 0FEFEH
	C_END
;>>
;<< 
	kTEST(4)
	kF(fCONTR_D)
	kF(kP_MID)
	kF(kP_AVR)
	kN(D'6'),tD_AVR
	kMSO(b'1111')
	pINC(tD_AVR)
	DW 0FEFEH
	MSO(b'1110')
	OFF(uCOMP)
	DW 0FEFEH
	C_END
;>>	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;<<
	kTEST(6)
	kF(fOBR_Tcmp)
	kF(fZMK_Tcmp)
	kF(fYES_TCMP)
	kF(fAVR_TCMP)
	kN(D'174'),T_cmp
	kN(D'165'),T_cmp
;
	MSO(b'001100')
	OFF(uCOMP)
	DW 0FEFEH
;
	MSO(b'001000')
	OFF(uCOMP)
	pBSF(fAVR_TCMP)
	DW 0FEFEH
;
	MSO(b'001110')
	OFF(uCOMP)
	pBSF(fAVR_TCMP)
	DW 0FEFEH
;
	MSO(b'001111')
	pBCF(fAVR_TCMP)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(1)
	kF(fWAIT)
	MSO(b'1')
	OFF(uCOMP)
	OFF(uC_DEF)
	OFF(uC_ISP)
	OFF(uC_CON)
	ON(uV_ISP)
	DW 0FEFEH
	C_END
;>>


;<< ОТСЧЕТ ВРЕМЕНИ КОНТРОЛЯ ДАТЧИКОВ ДАВЛЕНИЯ 
;В ПАРЕ
	kTEST(4)
	kF(fCONTR_D)
	kF(kP_MID)
	kF(kP_AVR)
	kN(D'25'),t_X_DAVL
;
	MSO(b'0111')
	pINC(t_X_DAVL)
	pBSF(fCONTR_D)
	DW 0FEFEH
	MSO(b'1111')
	pINC(t_X_DAVL)
	DW 0FEFEH
;авария
	MSO(b'1110')
	pBCF(fCONTR_D)
	DW 0FEFEH
;
	MSO(b'0100')
	pCLRF(t_X_DAVL)
	pBSF(fCONTR_D)
	DW 0FEFEH
	MSO(b'0101')
	pCLRF(t_X_DAVL)
	pBSF(fCONTR_D)
	DW 0FEFEH
	C_END
;>>

;<<ОТКЛЮЧ. ПРИ АВАРИИ ДАТЧ. ДАВЛ.
;ПРИ СРАБАТЫВАНИИ 2-х ДАТЧИКОВ
	kTEST(3)
	kF(fCONTR_D)
	kF(kP_MID)
	kF(kP_AVR)
	MSO(b'011')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
	DW 0FEFEH
	MSO(b'001')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
	DW 0FEFEH
	MSO(b'101')
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
	pBSF(fCONTR_D)
	DW 0FEFEH
	C_END
;>>

;;<<ОТКЛЮЧ. ВСЕГО 
;;ИЛИ АВАРИИ ДАТЧ. ДАВЛ. 2
;	kTEST(1)
;	kE(0xff),U_davl
;	MSO(b'1')
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
;	OFF(uC_ISP)
;	DW 0FEFEH
;	C_END
;;>>

;<<ОТКЛ. ВСЕГО ПРИ НЕИСПР. ДАТЧИКОВ ТЕМП.
;ИЛИ  ВСЕГО ПРИ ОТКР.ДВЕРИ
	kTEST(3)
	kF(kDOOR)
	kORL
	kF(fT1_ERR)
	kORL
	kF(fT2_ERR)
	MSO(b'111')	;
	pCLRF(UPR_BT)
;
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_DEF)
;	OFF(uC_CON)
	DW 0FEFEH
	C_END
;>>

;<<ОТКЛ. ВСЕГО ПРИ НЕИСПР. ДАТЧИКОВ ТЕМП.
;ИЛИ  ВСЕГО ПРИ ОТКР.ДВЕРИ
	kTEST(1)
	kE(0x0),POWER_OTOP
	MSO(b'0')	;
	OFF(uCOMP)
;	OFF(uV_ISP)
	OFF(uV_CON)
	OFF(uC_DEF)
	DW 0FEFEH
	C_END
;>>

;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;<<
	kTEST(3)
	kF(multi2)
	kE(0x1),sSTATUS1
	kE(0x5),sSTATUS
	kMSO(b'111')  
	pBSF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi2)
	kE(0x1),sSTATUS1
	kE(0x6),sSTATUS
	kMSO(b'111')  
	pBSF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi2)
	kE(0x2),sSTATUS1
	kE(0x6),sSTATUS
	kMSO(b'111')  
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi2)
	kE(0x2),sSTATUS1
	kE(0x5),sSTATUS
	kMSO(b'111')  
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi2)
	kE(0x3),sSTATUS1
	kE(0x5),sSTATUS
	kMSO(b'111')  
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi2)
	kE(0x4),sSTATUS1
	kE(0x5),sSTATUS
	kMSO(b'111')  
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi2)
	kE(0x5),sSTATUS1
	kE(0x5),sSTATUS
	kMSO(b'111')  
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>

;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;<<
	kTEST(3)
	kF(multi1)
	kE(0x1),sSTATUS2
	kE(0x5),sSTATUS
	kMSO(b'111')  
	pBSF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi1)
	kE(0x1),sSTATUS2
	kE(0x6),sSTATUS
	kMSO(b'111')  
	pBSF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi1)
	kE(0x2),sSTATUS2
	kE(0x6),sSTATUS
	kMSO(b'111')  
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi1)
	kE(0x2),sSTATUS2
	kE(0x5),sSTATUS
	kMSO(b'111')  
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi1)
	kE(0x3),sSTATUS2
	kE(0x5),sSTATUS
	kMSO(b'111')  
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi1)
	kE(0x4),sSTATUS2
	kE(0x5),sSTATUS
	kMSO(b'111')  
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(3)
	kF(multi1)
	kE(0x5),sSTATUS2
	kE(0x5),sSTATUS
	kMSO(b'111')  
	pBCF(fWAIT)
	DW 0FEFEH
	C_END
;>>
;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;;<<
;	kTEST(1)
;	kE(0x6),sSTATUS
;	kMSO(b'111')  
;	pBCF(fWAIT)
;	DW 0FEFEH
;	C_END
;;>>

;<<
	kTEST(1)
	kF(fWAIT)
	MSO(b'1')
	OFF(uCOMP)
	OFF(uC_DEF)
	OFF(uC_ISP)
	OFF(uC_CON)
	ON(uV_ISP)
;	ON(uH_DEF)
	DW 0FEFEH
	C_END
;>>
;<< 
	kTEST(4)
	kNA(T_START_HOT2),T_isp
	kF(multi2)
	kF(f_H_def)
	kF(uH_DEF)
	kMSO(b'0111')	;111
	ON(uV_ISP)
	DW 0FEFEH
	C_END
;>>

;<< 
	kTEST(3)
	kF(multi1)
	kF(f_H_def)
	kF(uV_ISP)
	kMSO(b'110')	;111
	OFF(uH_DEF)
	DW 0FEFEH
	C_END
;>>

;	kF(fSYN_V_ISP)	heat
;<< 
	kTEST(2)
	kF(fSYN_V_ISP)	
	kF(uCOMP)
	MSO(b'10')	;
	OFF(uV_ISP)
	DW 0FEFEH
	C_END
;>>
;
;ПЕРЕХОД НА ОХЛАЖДЕНИЕ
;<<
	kTEST(3)
	kF(fAUTO)
	kF(fONOFF)
	kNA(T_air_dmn_a),sZADT
	MSO(B'0111')
	pSAV(S1OZUPR),UPR_END_HOT
	pBCF(fHOT_COLD)
	DW 0FEFEH
	C_END
;>>
	C_END



;*********************************************
;*********************************************
;	ПРОГРАММА ОКОНЧАНИЯ ОТОПЛЕНИЯ
;*********************************************
;*********************************************
UPR_END_HOT:
;	OFF(uCOMP)
;	OFF(uV_ISP)
;	OFF(uV_CON)
;	OFF(uC_CON)
;	OFF(uH_DEF)
;	ON(uC_DEF)
	pMOVLF(UPR_BT),0x20
	pCLRF(tENDHOT)
;
;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

;<<
	kTEST(2)
	kF(multi2)
	kE(0x0),sSTATUS1
	kMSO(b'10')  
	pMOVLF(tENDHOT),D'12'
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(2)
	kF(multi1)
	kE(0x0),sSTATUS2
	kMSO(b'10')  
	pMOVLF(tENDHOT),D'12'
	DW 0FEFEH
	C_END
;>>


	kGO

;<< 
	kTEST(1)
	kN(D'40'),U_nap
	MSO(b'1')
	pCLRF(tENDHOT)
	OFF(uC_DEF)
	pSAV(S1OZUPR),0
	DW 0FFFFH
	m END_HOT1
	C_END
;>>

;<<пропуск окончан. отоп. если нет кл. отсечки
	kTEST(1)
	kF(fOBRC_CON)
	kMSO(b'1')  
	pMOVLF(tENDHOT),D'13'
	DW 0FEFEH
	C_END
;>>


;<<
	kTEST(4)
	kN(D'6'),tENDHOT
	kF(fAUTO)
	kF(fONOFF)
	kNA(T_air),sZADT
	MSO(B'0111')
	pCLRF(tENDHOT)
	OFF(uC_DEF)
	pSAV(S1OZUPR),UPR_COLD
	DW 0FEFEH
	MSO(B'0110')
	pCLRF(tENDHOT)
	OFF(uC_DEF)
	pSAV(S1OZUPR),UPR_HOT
	DW 0FEFEH
	C_END
;>>
;
;<< ВКЛЮЧ. КЛАПАНА РАЗМОР. ПОСЛЕ НАГРЕВА
	kTEST(1)
	kN(D'6'),tENDHOT
	MSO(b'1')
	pINC10(tENDHOT)
	ON(uC_DEF)
	pBCF(fSLEEP)
	DW 0FEFEH
	MSO(b'0')
;	pBCF(fSTART_HOT)
;	pBCF(fHOTDO)
;	WrEEin(eblok_fl),blok_fl
	pCLRF(tENDHOT)
	OFF(uC_DEF)
	pSAV(S1OZUPR),0x0
	pBSF(fSLEEP)
	pCLRF(sSTATUS)
	DW 0FEFEH
	C_END
;>>
END_HOT1:
	C_END
;

;*********************************************
;*********************************************
;*********************************************
; ПРОГРАММА УПРАВЛЕНИЯ АВТОНОМНЫМ ОТОПИТЕЛЕМ
;*********************************************
;*********************************************
;*********************************************
;U_nap

UPR_OTOP:

;<<
	kTEST(1)
	kF(YES_OTOP)
	MSO(b'1')  
	pBSF(fYES_OTOP)
	DW 0FEFEH
	C_END
;>>
	pMOVLF(sSTATUS_OTOP),D'0'
	pCLRF(POWER_OTOP)
	pBCF(fAVAR_OTOP)

;<<
	kTEST(1)
	kN(D'70'),U_nap
	MSO(b'0')  
	pCLRF(OTOP_SLEEP)
	DW 0FEFEH
	C_END
;>>

;<<
	kTEST(2)
	kF(fYES_OTOP)
	kORL
	kN(D'0'),OTOP_SLEEP
	MS(b'00')  
	m UPR_OTOP
	C_END
;>>
;>>>>>>>>>>>>>>>
;<<
	kTEST(2)
	kF(fDO_SLEEP)
	kF(fONOFF)
	MSO(b'10')  
	pBSF(fNO_OFF)
	DW 0FEFEH
	C_END
;>>


;<<
	kTEST(3)
	kF(fYES_OTOP)
	kF(fAUTO)
	kF(fHOT_COLD)
	MS(b'100')  
	m UPR_OTOP
	C_END
;>>	

;<<
	kTEST(4)
	kF(fYES_OTOP)
	kF(fONOFF)
	kF(fAUTO)
	kF(fHOT_COLD)
	MSO(b'1001')  
	OFF(uV_ISP)
	DW 0FEFEH
	C_END
;>>


;<<<<<<<<<<<<<<<<<<<<<<<<<<<<

;<<
	kTEST(1)
	kF(INDIK_OTOP)
	MSO(b'1')  
	pBSF(fOTOP_WORK)
	DW 0FFFFH
	m VENTIL_OTOP
	MSO(b'0')  
	pBCF(fOTOP_WORK)
	DW 0FEFEH
	C_END
;>>

;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
;<<
	kTEST(3)
	kF(fOTOP_WORK)
	kF(fONOFF)
	kN(D'3'),zOPER_MN
	MSO(b'010')  
	pMOVLF(POWER_OTOP),D'1'
	pCLRF(t_WAIT_OTOP_A)
	DW 0FFFFH
	m UPR_OTOP_WORK
	C_END
;>>

;<<
	kTEST(3)
	kF(fONOFF)
	kF(fAUTO)
	kF(fHOT_COLD)
	MSO(b'101')  
	ON(uV_ISP)
	DW 0FEFEH
	C_END
;>>


;ОТСЧЕТ ВРЕМЕНИ ДО ВКЛЮЧ. ОТОП.
;<<
	kTEST(5)
	kF(fOTOP_WORK)
	kF(fONOFF)
	kN(D'2'),zOPER_MN
	kN(D'3'),zOPER_MN
	kN(D'10'),t_WAIT_OTOP
	MSO(b'01011')	; 
	pINC1M(t_WAIT_OTOP)
	DW 0FEFEH
	MSO(b'01010')	; 
	pMOVLF(POWER_OTOP),D'1'
	pCLRF(t_WAIT_OTOP_A)
	DW 0FFFFH
	m UPR_OTOP_WORK
	C_END
;>>

;<<
	kTEST(2)
	kN(D'2'),zOPER_MN
	kORL
	kF(fONOFF)
	MSO(b'10')	; 
	pCLRF(t_WAIT_OTOP)
	DW 0FEFEH
	C_END
;>>
	pMOVLF(sSTATUS_OTOP),D'1'
;
	C_END
;

VENTIL_OTOP:
;<<
	kTEST(1)
	kF(INDIK_OTOP)
	MSO(b'0')  
	pBCF(fOTOP_WORK)
	pCLRF(t_WAIT_OTOP)
	DW 0FFFFH
	m PAUSA_OTOP
	C_END
;>>
	pCLRF(POWER_OTOP)
	pMOVLF(sSTATUS_OTOP),D'6'
;;<<
;	kTEST(1)
;	kF(fONOFF)
;	MS(b'0')  
;	m UPR_OTOP
;	C_END
;;>>
;<<
	kTEST(3)
	kF(fONOFF)
	kF(fAUTO)
	kF(fHOT_COLD)
	MSO(b'101')  
	ON(uV_ISP)
	DW 0FEFEH
	C_END
;>>
;
	C_END
;
PAUSA_OTOP:
;<<
	kTEST(1)
	kN(D'12'),t_WAIT_OTOP
	MSO(b'1')	; 
	pINC10(t_WAIT_OTOP)
	DW 0FEFEH
	MSO(b'0')  
	pCLRF(t_WAIT_OTOP)
	pCLRF(sSTATUS_OTOP)
	DW 0FFFFH
	m UPR_OTOP
	C_END
;>>
	pMOVLF(sSTATUS_OTOP),D'7'
;<<
	kTEST(3)
	kF(fONOFF)
	kF(fAUTO)
	kF(fHOT_COLD)
	MSO(b'101')  
	ON(uV_ISP)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(1)
	kF(INDIK_OTOP)
	MSO(b'1')  
	pCLRF(t_OTOP_AVR)
	DW 0FEFEH
	C_END
;>>
;;<<
;	kTEST(1)
;	kF(fONOFF)
;	MS(b'0')  
;	m UPR_OTOP
;	C_END
;;>>
;
	C_END
;



UPR_OTOP_WORK:
	pCLRF(t_WAIT_OTOP)
	pCLRF(t_WAIT_OTOP_A)

;<<
	kTEST(1)
	kF(INDIK_OTOP)
	MSO(b'1')  
	pCLRF(t_OTOP_AVR)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(1)
	kN(D'1'),zOPER_MN
	MSO(b'0')	; 
	pMOVLF(POWER_OTOP),D'2'
	pMOVLF(sSTATUS_OTOP),D'4'
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(1)
	kN(D'3'),zOPER_PL
	MS(b'0')  
	m UPR_OTOP
	C_END
;>>
;<<
	kTEST(3)
	kF(fONOFF)
	kF(fAUTO)
	kF(fHOT_COLD)
	MSO(b'101')  
	ON(uV_ISP)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(1)
	kN(D'1'),zOPER_MN
	MSO(b'1')	; 
	pMOVLF(POWER_OTOP),D'1'
	pMOVLF(sSTATUS_OTOP),D'3'
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(2)
	kN(D'8'),t_WAIT_OTOP
	kN(D'1'),zOPER_MN
	MSO(b'11')	; 
	pCLRF(t_WAIT_OTOP)
	pCLRF(sSTATUS_OTOP)
	DW 0FFFFH
	m UPR_OTOP
	C_END
;>>

	pCLRF(tONCOLD)

;<<
	kTEST(1)
	kN(D'12'),t_WAIT_OTOP
	MSO(b'1')	; 
	pINC1M(t_WAIT_OTOP)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(2)
	kE(0x1),sONOFF	
	kF(fONOFF)
	MS(b'00')  
	m UPR_OTOP
	C_END
;>>

;<<
	kTEST(3)
	kE(0x1),sONOFF	
	kF(fSLEEP)
	kN(D'1'),tON_OFF_2h	
	MSO(b'110')  
	pMOVLF(OTOP_SLEEP),D'1'
	DW 0FFFFH
	m UPR_OTOP
	C_END
;>>
;Проверка исправности отопителя
;<<
	kTEST(2)
	kF(INDIK_OTOP)
	kN(D'40'),t_WAIT_OTOP_A
	MSO(b'01')  
	pINC10(t_OTOP_AVR)
	pINC(t_WAIT_OTOP_A)
	pMOVLF(sSTATUS_OTOP),D'5'
	DW 0FEFEH
	MSO(b'00')  
	pMOVLF(sSTATUS_OTOP),D'5'
	pBSF(fAVAR_OTOP)
	DW 0FFFFH
	m PAUSA_OTOP
	C_END
;>>
;<<
	kTEST(1)
	kF(INDIK_OTOP)
	MSO(b'1')  
	pCLRF(t_OTOP_AVR)
	DW 0FEFEH
	C_END
;>>
;<<
	kTEST(1)
	kN(D'18'),t_OTOP_AVR
	MSO(b'0')  
	pMOVLF(t_OTOP_AVR),D'17'
	DW 0FEFEH
	C_END
;>>
;
	C_END
;
STR_С_VAC:	DB 'U','A','C',0
STR_С_UP:	DB 'C','L','U',0
STR_СC_UP:	DB 'C','C','U',0
STR_СP_UP:	DB 'U','C','P',0
STR_VI1_UP:	DB 'B','I','1',0
STR_VI2_UP:	DB 'B','I','2',0
STR_VI3_UP:	DB 'B','I','3',0
STR_VC1_UP:	DB 'B','C','1',0
STR_VC2_UP:	DB 'B','C','2',0
STR_С1_UP:	DB 'C','1','U',0
STR_С2_UP:	DB 'C','2','U',0
STR_СCP_UP:	DB 'H','C','U',0
STR_HDF_UP: DB 'H','D','F',0

STR_TE_ERR:	DB 'E','r','r',0


;
STR_OTP_AVR:	DB 'A','0','E',0
;
STR_OTP_PAU:	DB 'A','0','P',0

;STR_SOS:	DB '5','0','B',0

STR_OFF:	DB '0','F','F',0
STR_CND:	DB ' ','A','C',0

STR_COLD:	DB 'C','0','L',0
STR_HOT:	DB 'H','E','A',0
STR_DEFR:	DB 'D','E','F',0
STR_AUTO:	DB 'A','C','H',0

;ДВЕРЬ
STR_DOW:	DB 'D','o','o',0

STR_Pr1:	DB 'P','r','1',0
STR_Pr2:	DB 'P','r','2',0
STR_ACC:	DB 'U','L','9',0
STR_PrNo:	DB 'P','r','-',0

;НЕИСПРАВНОСТЬ ДАТЧИКОВ ТЕМПЕРАТУРЫ
STR_TI_ERR:	DB 't','I','E',0
STR_TI_OBR:	DB 't','I','0',0
STR_TA_ERR:	DB 't','A','E',0
STR_TA_OBR:	DB 't','A','0',0

STR_TC_ERR:	DB 't','C','E',0
STR_TC_OBR:	DB 't','C','0',0

;НЕИСПРАВНОСТЬ КЛАПАНОВ
STR_С_ERR:	DB 'E','C','L',0
STR_С_OBR:	DB '0','C','L',0
STR_СC_ERR:	DB 'E','C','C',0
STR_СC_OBR:	DB '0','C','C',0

;НЕИСПРАВНОСТЬ ДОП КЛАПАНОВ
STR_С1I_ERR:	DB 'E','C','1',0
STR_С1I_OBR:	DB '0','C','1',0
STR_С2I_ERR:	DB 'E','C','2',0
STR_С2I_OBR:	DB '0','C','2',0

;<< ПРИ НЕИСПРАВН. кабеля поддона
STR_СDF_ERR:	DB 'E','D','F',0
STR_СDF_OBR:	DB '0','D','F',0

;НЕИСПРАВНОСТЬ КОМПРЕССОРА
STR_СOMP_ERR:	DB 'C','P','E',0
STR_СOMP_OBR:	DB 'C','P','0',0

;НЕИСПРАВНОСТЬ КЛАПАНА КОМПРЕССОРА
STR_СCP_ERR:	DB 'E','C','H',0
STR_СCP_OBR:	DB '0','C','H',0




;БЛОКИРОВКА ВЕНТИЛЯТОРОВ
STR_VC_BLK:	DB 'B','L','C',0
STR_VI_BLK:	DB 'B','L','I',0

;ОБРЫВ ВЕНТИЛЯТОРОВ
STR_VC_OBR:	DB '0','B','C',0
STR_VI_OBR:	DB '0','B','I',0

;ЗАМЫК. ВЕНТИЛЯТОРОВ
STR_VC_ZMK:	DB 'E','r','C',0
STR_VI_ZMK:	DB 'E','r','I',0

;АВАРИЙНОЕ ДАВЛЕНИЕ
STR_AVR_DVL:  DB 'A','D','E',0
STR_AVR_DVL2:  DB 'A','D','2',0

;НЕИСПРАВНОСТЬ ДАТЧИКА ДАВЛЕНИЯ
STR_AVR_DVL_K:  DB 'A','D','r',0
STR_AVR_DVL_O:  DB 'A','D','o',0

;АВАРИЯ НА ЛИНИИ
STR_LIN_AV:	  DB 'A','L','B',0

;
        END
