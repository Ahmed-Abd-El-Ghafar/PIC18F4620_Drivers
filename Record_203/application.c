/* 
 * File:   application.c
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 */

#include "application.h"
#include "MCAL_Layer/SPI/hal_spi.h"

SPI_Config SPI_Obj;
pin_config_t SPI_SS1;

uint8 SPI_Msater_Side_Slave1_RetVal = 0;

int main() { 
    Std_ReturnType ret = E_NOT_OK;
    
    application_intialize();
    
    SPI_Obj.spi_mode = SPI_MASTER_FOSC_DIV4;
    SPI_Obj.spi_config.SampleSelect = SPI_DATA_SAMPLE_MIDDLE;
    SPI_Obj.spi_config.ClockPolarity = SPI_IDLE_STATE_LOW_LEVEL;
    SPI_Obj.spi_config.ClockSelect = SPI_TRANSMIT_IDLE_TO_ACTIVE;
    ret = SPI_Init(&SPI_Obj);
    
    SPI_SS1.port = PORTD_INDEX;
    SPI_SS1.pin = GPIO_PIN0;
    SPI_SS1.direction = GPIO_DIRECTION_OUTPUT;
    SPI_SS1.logic = GPIO_HIGH;
    ret = gpio_pin_intialize(&SPI_SS1);
    
    while(1){  
        ret = gpio_pin_write_logic(&SPI_SS1, GPIO_LOW);
        ret = SPI_Send_Byte(&SPI_Obj, 'a');
        ret = SPI_Read_Byte(&SPI_Obj, &SPI_Msater_Side_Slave1_RetVal);
        __delay_ms(250);
        ret = SPI_Send_Byte(&SPI_Obj, 'b');
        ret = SPI_Read_Byte(&SPI_Obj, &SPI_Msater_Side_Slave1_RetVal);
        __delay_ms(250);
        ret = gpio_pin_write_logic(&SPI_SS1, GPIO_HIGH);
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();
}
