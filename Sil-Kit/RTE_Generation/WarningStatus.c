/*
 * WarningStatus.c
 *
 *  Created on: Mar 28, 2026
 *      Author: MohamedMooo
 */


/*****************************************************
 * Runnable: 	ALG_Warning
 * DataElement: EgoSpeed_IOSWC
 *****************************************************/
extern void ALG_Warning(void){
	double speed;
	speed = Rte_IRead_WarningStatus_ALG_Warning_RP_EgoSpeed_COM_EgoSpeed_IOSWC();
	if(speed > 60){
		// turn on led
	}else{
		// turn off led
	}
}
