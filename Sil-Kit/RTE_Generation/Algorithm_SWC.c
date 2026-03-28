/*
 * Algorithm_SWC.c
 *
 *  Created on: Mar 28, 2026
 *      Author: MohamedMooo
 */


/*****************************************************
 * Runnable: 	Runnable_ReceiveCanFram
 * Period:		0.01
 *****************************************************/
double speed_ = 60.0;
extern void Runnable_ReceiveCanFram(void){


	Rte_IWrite_Algorithm_SWC_Runnable_ReceiveCanFram_PP_EgoSpeed_APP_EgoSpeed_AppSWC(speed_);
}

/*****************************************************
 * Runnable: 	Runnable_ApplySpeed
 * DataElement: EgoSpeed_AppSWC
 *****************************************************/
extern void Runnable_ApplySpeed(void){
	double speed;
	speed = Rte_IRead_Algorithm_SWC_Runnable_ApplySpeed_RP_EgoSpeed_APP_EgoSpeed_AppSWC();


	// algorithm for speed display
	Rte_IWrite_Algorithm_SWC_Runnable_ApplySpeed_PP_EgoSpeed_SA_EgoSpeed_SASWC(speed);
}
