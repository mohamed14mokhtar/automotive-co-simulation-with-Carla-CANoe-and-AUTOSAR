/*
 * SA_Speed_SWC.c
 *
 *  Created on: Mar 28, 2026
 *      Author: MohamedMooo
 */


/*****************************************************
 * Runnable: 	SpeedTakeAction
 * DataElement: EgoSpeed_SASWC
 *****************************************************/
extern void SpeedTakeAction(void){
	double speed;
	speed = Rte_IRead_SA_Speed_SWC_SpeedTakeAction_RP_EgoSpeed_IO_EgoSpeed_SASWC();
	if(speed > 60){
		// call complex driver to take an action
		Rte_IWrite_SA_Speed_SWC_SpeedTakeAction_PP_EgoSpeed_SA_EgoSpeed_IOSWC(speed);
	}else{

	}
}
