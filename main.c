#include <msp430.h> 
#include <stdbool.h>
#include <stdint.h>

/*
 * voorbeeld programma voor guessing game
 * 2017 Harry Broeders
 * 
 * Dit voorbeeld programma maakt gebruik van de functies:
 * digitalRead en digitalWrite waarmee je een digitale pin van 
 * de MSP-EXP430G2 Launchpad kunt aansturen of inlezen.
 
 * In dit voorbeeld wordt de digitale output pin 1.0 (rode led) 
 * gelijk gemaakt aan de logische AND functie van twee input
 * pins 2.0 en 2.1. Bovendien wordt de digitale output pin 1.6
 * (groene led) gelijk gemaakt aan de logische OR functie van
 * dezelfde twee input pins (2.0 en 2.1). 
 */

/*
 * Functie digitalWrite(port, pin, value)
 * Je kunt pin 6 van port 1 (pin 1.6, de groene led) true
 * maken met de code:
 * digitalWrite(1, 6, true);
 */
 
 void digitalWrite(uint8_t, port, uint8_t pin, bool value)
 {
    if (port == 1 && pin < 8)
    {
        P1DIR |= 1<<pin;
        if (value)
        {
            P1OUT |= 1<<pin;
        }
        else
        {
            P1OUT &= ~(1<<pin);
        }
    }
    else if (port == 2 && pin < 6)
    {
        P2DIR |= 1<<pin;
        if (value)
        {
            P2OUT |= 1<<pin;
        }
        else
        {
            P2OUT &= ~(1<<pin);
        }
    }
 }

/*
 * Functie digitalRead(port, pin)
 * Je kunt pin 1 van port 2 (pin 2.1) lezen en in de booleanse
 * variabele b opslaan met de code:
 * b = digitalRead(2, 1);
 */
 
 bool digitalRead(uint8_t, port, uint8_t pin)
 {
    bool result;
    if (port == 1 && pin < 8)
    {
        P1DIR &= ~(1<<pin);
        result = (P1IN & 1<<pin) == 1<<pin;
    }
    else if (port == 2 && pin < 6)
    {
        P2DIR &= ~(1<<pin);
        result = (P2IN & 1<<pin) == 1<<pin;
    }
    return result;
 }

 * In dit voorbeeld wordt de digitale output pin 1.0 (rode led) 
 * gelijk gemaakt aan de logische AND functie van twee input
 * pins 2.0 en 2.1. Bovendien wordt de digitale output pin 1.6
 * (groene led) gelijk gemaakt aan de logische OR functie van
 * dezelfde twee input pins (2.0 en 2.1). 
 */

int main(void) 
{
    // stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;
    
    while (1) // herhaal voor "altijd" 
    {
        bool p20 = digitalRead(2, 0);
        bool p21 = digitalRead(2, 1);
        
        bool redLed = p20 && p21; // && betekent logische AND
        bool greenLed = p20 || p21; // || betekent logische OR
        
        digitalWrite(1, 0, redLed);
        digitalWrite(1, 6, greenLed);
    }
    
	return 0;
}
