#ifndef ADC_H
#define ADC_H

extern void ADC_Init( void );
extern void ADC_Start( void );
extern uint8_t ADC_Read( void );
extern void ADC_UpdateWindow( uint8_t upper, uint8_t lower );
extern void ADC_ClearInterrupt( void );
extern void ADC_DisableInterrupt( void );

#endif /* ADC_H */
