#include "Delay.h"

#if (SYS_CLK == 24000000)

/****
	* @brief	—”≥Ÿ1Œ¢√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:Delay1us(); —”≥Ÿ1us
	*/
void Delay1us()		
{
    uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 4UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ5Œ¢√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:Delay5us(); —”≥Ÿ5us
	*/
void Delay5us()	
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 28UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ10Œ¢√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:  Delay10us(); —”≥Ÿ10us
	*/
void Delay10us()	
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 58UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ15Œ¢√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:  Delay15us(); —”≥Ÿ15us
	*/
void Delay15us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 88UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ20Œ¢√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:Delay20us(); —”≥Ÿ20us
	*/
void Delay20us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 118UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ50Œ¢√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:Delay50us(); —”≥Ÿ50us
	*/
void Delay50us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 298UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ100Œ¢√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:Delay100us();
	*/
void Delay100us()	
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 598UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ1∫¡√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:  Delay1ms(); —”≥Ÿ1ms
	*/
void Delay1ms()
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 5998UL;
	while (i) i--;
}

#elif (SYS_CLK == 12000000)		//12MHz

/****
	* @brief	—”≥Ÿ1Œ¢√Î
	* @param	Œﬁ	
	* @return 	Œﬁ        	
	* Sample usage:Delay1us(); —”≥Ÿ1us
	*/
void Delay1us()		//@12.000
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 1UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ5Œ¢√Î
	* @param	Œﬁ	
	* @return 	Œﬁ        	
	* Sample usage:Delay5us(); —”≥Ÿ5us
	*/
void Delay5us()		//@12.000
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 13UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ10Œ¢√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:Delay10us(); —”≥Ÿ10us
	*/
void Delay10us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 28UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ20Œ¢√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:Delay20us(); —”≥Ÿ20us
	*/
void Delay20us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 58UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ15Œ¢√Î
	* @param	Œﬁ	
	* @return   Œﬁ        	
	* Sample usage:Delay15us(); —”≥Ÿ15us
	*/
void Delay15us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 43UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ50Œ¢√Î
	* @param	Œﬁ	
	* @return   Œﬁ        	
	* Sample usage:Delay100us(); —”≥Ÿ50us
	*/
void Delay50us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 148UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ100Œ¢√Î
	* @param	Œﬁ	
	* @return   Œﬁ        	
	* Sample usage:Delay100us(); —”≥Ÿ100us
	*/
void Delay100us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 298UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ1∫¡√Î
	* @param	Œﬁ	
	* @return   Œﬁ        	
	* Sample usage:Delay1ms(); —”≥Ÿ1ms
	*/
void Delay1ms()	
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 2998UL;
	while (i) i--;
}

#else //11059200MHz

/****
	* @brief	—”≥Ÿ1Œ¢√Î
	* @param	Œﬁ	
	* @return   Œﬁ        	
	* Sample usage:Delay1us(); —”≥Ÿ1us
	*/
void Delay1us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	i = 1UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ5Œ¢√Î
	* @param	Œﬁ	
	* @return   Œﬁ        	
	* Sample usage:Delay5us(); —”≥Ÿ5us
	*/
void Delay5us()	
{
	uint32_t i;
	_nop_();
	_nop_();
	i = 12UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ10Œ¢√Î
	* @param	Œﬁ	
	* @return   Œﬁ        	
	* Sample usage:Delay10us(); —”≥Ÿ10us
	*/
void Delay10us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	i = 26UL;
	while (i) i--;
}

/****
	* @brief    —”≥Ÿ15Œ¢√Î
	* @param	Œﬁ	
	* @return   Œﬁ        	
	* Sample usage:Delay15us(); —”≥Ÿ15us
	*/
void Delay15us()		
{
	uint32_t i;
	_nop_();
	i = 40UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ20Œ¢√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:Delay20us(); —”≥Ÿ20us
	*/
void Delay20us()		
{
	uint32_t i;
	i = 54UL;
	while (i) i--;
}

/****
	* @brief    —”≥Ÿ50Œ¢√Î
	* @param	Œﬁ	
	* @return   Œﬁ        	
	* Sample usage:Delay100us(); —”≥Ÿ50us
	*/
void Delay50us()	
{
	uint32_t i;
	i = 137UL;
	while (i) i--;
}

/****
	* @brief    —”≥Ÿ100Œ¢√Î
	* @param	Œﬁ	
	* @return   Œﬁ        	
	* Sample usage:Delay100us(); —”≥Ÿ100us
	*/
void Delay100us()		
{
	uint32_t i;
	_nop_();
	i = 275UL;
	while (i) i--;
}

/****
	* @brief	—”≥Ÿ1∫¡√Î
	* @param	Œﬁ	
	* @return	Œﬁ        	
	* Sample usage:  Delay1ms(); —”≥Ÿ1ms
	*/
void Delay1ms()
{
	uint32_t i;
	_nop_();
	_nop_();
	i = 2763UL;
	while (i) i--;
}

#endif


/****
	* @brief	Œ¢√Îº∂—” ±
	* @param	xus	—” ± ±º‰		
	* @return	Œﬁ        	
	* Sample usage:Delay_us(1); 
	*/
void Delay_us(uint16_t xus)
{
	while(xus--)
	{
		Delay1us();
	}
}

/****
	* @brief	—”≥Ÿtime∫¡√Î
	* @param	xms	—”≥Ÿ ±º‰(1-65535)	
	* @return	Œﬁ        	
	* Sample usage:Delay(1000); —”≥Ÿ1s
	*/
void Delay_ms(uint16_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}

/****
	* @brief	√Îº∂—” ±
	* @param	xs	—” ± ±º‰		
	* @return	Œﬁ        	
	* Sample usage:Delay_s(1); 
	*/
void Delay_s(uint16_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
}