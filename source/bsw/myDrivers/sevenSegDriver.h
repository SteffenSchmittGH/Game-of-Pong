/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

typedef enum {A,B,C,D,E,F,ZERO,EINS,ZWEI,DREI,VIER,FUENF,SECHS,SIEBEN,ACHT,NEUN,} sign_t;
enum {V,J,M,N,X} funny;
typedef enum {SEG1,SEG2,}segment_t;
void init_sev( segment_t seg);
sign_t getSegSign();
void setSegSign(sign_t sign);