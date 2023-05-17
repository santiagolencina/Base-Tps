#include "chip.h"
#include "digital.h"
#include <stdbool.h>

typedef struct digital_output_s {
    uint8_t port;
    uint8_t pin;
    bool allocated;
} *digital_output_t;


typedef struct digital_input_s{
    uint8_t port;
    uint8_t pin;
    uint8_t invertir;
    bool last_state;
    bool allocated;
} *digital_input_t;






digital_output_t DigitalOutputAllocate(void);

digital_output_t DigitalOutputAllocate(void){
    digital_output_t output =NULL;

    static struct digital_output_s instances[NUMERO_GPIO_OUT]={0};

    for(int index=0;index<NUMERO_GPIO_OUT;index++){
        if(!instances[index].allocated){
            instances[index].allocated=true;
            output=&instances[index];
            break;
        }
    }

return output;
}

digital_input_t DigitalinputAllocate(void){
    digital_input_t input =NULL;

    static struct digital_input_s instances[NUMERO_GPIO_INPUT]={0};

    for(int index=0;index<NUMERO_GPIO_INPUT;index++){
        if(!instances[index].allocated){
            instances[index].allocated=true;
            input=&instances[index];
            break;
        }
    }

return input;
}


digital_input_t  DigitalInputCreate(uint8_t port,uint8_t invertir,uint8_t pin){

digital_input_t input=DigitalinputAllocate();

if(input){
input->port=port;
input->pin=pin;
input->invertir= invertir;
Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,input->port,input->pin, false);
  
}
return input;
}






digital_output_t Digital_OutputCreate(uint8_t port,uint8_t pin){

digital_output_t output=DigitalOutputAllocate();

if(output){
output->port=port;
output->pin=pin;

    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->port, output->pin, true);
}
return output;
}



void DigitalOutPutActivate(digital_output_t output){
    Chip_GPIO_SetPinState(LPC_GPIO_PORT,output->port,output->pin,true);
}

void DigitalOutPutDesactivate(digital_output_t output){
    Chip_GPIO_SetPinState(LPC_GPIO_PORT,output->port,output->pin,false);
}

void DigitalOutPutToggle(digital_output_t output){
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,output->port,output->pin);
}

bool DigitalInputState(digital_input_t input){
   return  input->invertir ^ Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, input->port, input->pin);
}

bool DigitalInputhasChanged(digital_input_t input){

    bool state = DigitalInputState(input);
    bool result = state != input->last_state;
    input->last_state=state;
    return result;

}

bool DigitalInputhasActivated(digital_input_t input){

    bool state = DigitalInputState(input);
    bool result = state && !input->last_state;
    input->last_state= state;
    return result;

}

bool DigitalInputhasDesactivated(digital_input_t input){

    bool state = DigitalInputState(input);
    bool result = !state && !input->last_state;
    input->last_state= state;
    return result;

}