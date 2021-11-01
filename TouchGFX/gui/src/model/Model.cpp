#include <coinemu_rng.h>
#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

//Needed to use Semaphores
#include "cmsis_os.h"
#include "freeRTOS.h"
#include "queue.h"
#include "task.h"
#include "coinemu.h"
#include <stdlib.h>

extern osSemaphoreId_t pinPadSemaphoreHandle;
extern BlockEmuRNG bemurng;
extern xQueueHandle rngMsq;

Model::Model() : modelListener(0){
	guiRngActive = false; //The RNG is always in a failed state on boot.
	pinPadReady = false;  //The PinPad is always in a faileds state on boot.
}

void Model::tick(){
	/* First Check the PinPad Semaphore Handle to make sure the PinPad is ready for use */
	if(pinPadSemaphoreHandle != NULL){
		if(osSemaphoreAcquire(pinPadSemaphoreHandle, 0) == osOK){
			#ifdef _EMU_TOUGHGFX_DEBUG
				printf("%s","OS SEMAPHORE ACQUIRED - PIN-PAD IS READY\n\r");
			#endif
			pinPadReady = true;      //Update to the whole model that the pin pad is ready to be used.
			updateModelPinPad();     //Update the actual pin variable
		}
	}
	/* Check for new RNG Queue Data */
	if(xQueueReceive(rngMsq, &guiRngActive, 0) == pdTRUE){
		modelListener->updateRngStatusModel(guiRngActive);
		//Do something with the new message ..... This will be toggling the icon on our screen.
	}
}

/**
 * @desc: Update the PinPad with the correct digits in the correct order within the TouchGFX model
 * @ret: Return a pointer to the array of chars
 **/
void Model::updateModelPinPad(void){
	for(int pinbutton = 0; pinbutton < 10; pinbutton++ ){          //For each of the button on the Pin Pad - Give it a digit
		itoa(bemurng.pinPad[pinbutton],pinNumbers[pinbutton], 10); //Write to the global pin pad object with.
	}
	/* DO NOT RETURN ANYTHING - INSTEAD CALL A LINSTER FUNCTION TO HANDLE THE DATA CHANGE */
	modelListener->updatePinPad(&pinNumbers);

}
