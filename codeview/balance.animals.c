/*
Autor: Gustavo Nunes Teixeira
Data: 20/08/2020
Titulo: balance.animals
Rev.Atual:  V04
Assunto: Trabalho de Conclus�o de Curso(TCC)
V05 - Projeto realizado na disciplina de Projetos III, onde simula o funcionamento de 
      um projeto de automa��o para carga de bovinos, al�m de realizar a pesagem dos 
      mesmos, visando a melhoria de tarefas simples, mas importantes para as pessoas.
*/

//********************************* Bibliotecas Utilizadas ***************************************
#include<16f877A.h>                                            
#use delay(clock = 20000000)                                   
//************************************************************************************************


//************************** Fuses (Configura��o dos registradores) ******************************
#fuses HS,NOWDT,NOPROTECT,NOLVP
//************************************************************************************************


//************************** Define Valores Padr�es para o Programa ******************************
#define HX711_DO PIN_A0                                        
#define HX711_CLK PIN_A1                                       
#define LCD_ENABLE_PIN  PIN_C0                                
#define LCD_RS_PIN      PIN_E1                                                            
#define LCD_RW_PIN      PIN_E2                                                            
#define LCD_DATA4       PIN_C1                                                             
#define LCD_DATA5       PIN_C2                                                              
#define LCD_DATA6       PIN_D0                                                              
#define LCD_DATA7       PIN_D1                                 
#include "LCD.c"                                               
//************************************************************************************************


//************************************ Vari�veis globais *****************************************
char digito = ' ';                                            
int i = 0;                                                     
int vezes = 0;                                                 
int libera = 0;                                               
int16 peso_total = 0;                                          
int peso_total_parte1 = 0;                                     
int peso_total_parte2 = 0;                                     
int1 flag_ajuste = 0;                                          
int1 k = 0;                                                    
int1 flag_local = 0;                                           
int1 flag_zera = 0;                                            
int flag_peso = 0;                                            
int1 flag_cancela = 0;                                         
int1 flag_ok = 0;                                              
int1 flag_confirma = 0;                                       
int1 flag_grava = 0;                                           
int1 flag = 0;                                                 
int1 flag_1 = 0;                                               
int1 flag_2 = 0;                                               
int1 flag_3 = 0;                                               
int1 flag_4 = 0;                                              
int1 flag_5 = 0;                                               
int1 flag_6 = 0;                                               
int1 flag_home = 0;                                           
int1 flag_senha = 0;                                           
int1 flag_peso_maximo = 0;                                     
int1 flag_inicio = 0;                                          
int1 flag_libera_zera = 0;                                     
int estado_botao = 0;                                          
int flag_tranca_senha = 0;                                     
int ajuste = 0;                                                
int peso_maximo_1 = 0;                                        
int peso_maximo_2 = 0;                                        
int16 ajuste_peso_maximo = 0;                                  
int16 ajuste_animal = 0;                                       
int peso_animal_1 = 0;                                         
int peso_animal_2 = 0;                                        
int acelera_positivo = 0;                                      
int acelera_negativo = 0;                                      
char senha1[4] = {'0','0','0','0'};                            
int32 convert;                                                 
int16 diferenca;                                               
int16 calc_1 = 0;                                              
int16 calc_2 = 0;                                             
//************************************************************************************************


//********************************* Prot�tipos de fun��es ****************************************
void informativo();                                            
void menu();                                                   
void home();                                                   
void senha();                                                  
void peso_maximo();                                            
#int_EXT                                                       
void le_teclado_3x4();                                         
//************************************************************************************************


//****************************** Fun��o Principal do Programa ************************************
void main()                                                    
{                                                              
   port_B_pullups(TRUE);                                       
   
   enable_interrupts(GLOBAL);                                  
   ext_int_edge(H_TO_L);                                       

   lcd_init();                                                 
   delay_ms(10);                                               
   
   output_low(PIN_D5);                                         
   output_low(PIN_D6);                                         
   output_low(PIN_D7);                                         
   
   output_low(PIN_D3);                                        
   output_low(PIN_D2);                                         
   output_low(PIN_E0);                                         
   output_low(PIN_A5);                                         

   peso_maximo_1 = read_eeprom(0);                            
   delay_ms(5);                                                
   
   peso_maximo_2 = read_eeprom(1);                             
   delay_ms(5);                                                
 
   senha1[0] = read_eeprom(3);                                 
   delay_ms(5);                                                
   senha1[1] = read_eeprom(4);                                 
   delay_ms(5);                                                
   senha1[2] = read_eeprom(5);                                 
   delay_ms(5);                                               
   senha1[3] = read_eeprom(6);                                 
   delay_ms(5);                                                
   
   flag_inicio = read_eeprom(11);                               
   delay_ms(5);                                                
 
   ajuste_animal = make16(read_eeprom(9),read_eeprom(8));     
   delay_ms(5);                                               
   peso_total = make16(read_eeprom(255),read_eeprom(254));     
   delay_ms(5);                                                
   ajuste_peso_maximo = make16(peso_maximo_2,peso_maximo_1);   
   
   informativo();                                              
   lcd_putc('\f');                                             
   
   if(peso_total >= ajuste_peso_maximo && flag_inicio == 0)    
   {                                                           
      flag_ajuste = 1;                                        
      home();                                                  
   }                                                           
   else                                                        
   {                                                           
      menu();                                                  
   }                                                           
   
   while(1)                                                    
   {                                                           
      if(input(PIN_C6) == 0 && flag == 0 && flag_ajuste == 0)  
      {                                                       
         ajuste++;                                             
         flag_local = 0;                                       
         flag_tranca_senha = 0;                                
         flag = 1;                                             
         lcd_putc('\f');                                       
         flag_home = 0;                                       
         flag_senha = 0;                                       
         flag_peso_maximo = 0;                                
         vezes = 0;                                            
         libera = 0;                                           
         flag_confirma = 0;                                    
         i = 0;                                                
         peso_animal_1 = read_eeprom(8);                      
         delay_ms(5);                                         
         peso_animal_2 = read_eeprom(9);                       
         delay_ms(5);
         peso_maximo_2 = read_eeprom(0);                       
         delay_ms(5);                                          
         peso_maximo_1 = read_eeprom(1);                       
         delay_ms(5);                                          
         
         if(input(PIN_C4) == 1)                                
         {                                                     
            output_low(PIN_D2);                                
            output_high(PIN_D3);                               
         }                                                    
         if(input(PIN_A4) == 1)                                
         {                                                     
            output_low(PIN_A5);                                
            output_high(PIN_E0);                               
         }                                                    
      }                                                        
      
      if(input(PIN_C6) == 1 && flag == 1)                     
      {                                                        
         flag = 0;                                             
      }                                                        
      
      if(ajuste == 0 && flag_home == 0)                        
      {                                                        
         menu();                                               
         lcd_gotoxy(20,2);                                     
         printf(lcd_putc,("<"));                               
      }                                                        
      
      if(ajuste == 0 && input(PIN_B5) == 0 && flag_1 == 0)    
      {                                                       
         lcd_putc('\f');                                       
         flag_1 = 1;                                           
         flag_home = 1;                                        
      }                                                        
      
      if(flag_home == 1)                                       
      {                                                        
         home();                                              
      }                                                        
      
      if(ajuste == 0 && input(PIN_B5) == 1 && flag_1 == 1)     
      {                                                        
         flag_1 = 0;                                          
      }                                                        
      
      if(ajuste == 1 && flag_senha == 0)                       
      {                                                        
         flag_local=0;
         menu();                                               
         lcd_gotoxy(40,1);                                     
         printf(lcd_putc,("<"));                               
      }                                                        
      
      if(ajuste == 1 && input(PIN_B5) == 0 && flag_1 == 0 && flag_tranca_senha == 0) 
      {                                                        
         lcd_putc('\f');                                       
         flag_1 = 1;                                           
         flag_senha = 1;                                       
      }                                                        
      
      if(flag_senha == 1)                                      
      {                                                        
         flag_tranca_senha = 1;
         if(vezes == 0)                                        
         {                                                     
            lcd_gotoxy(2,1);                                   
            printf(lcd_putc,("INFORME SUA SENHA:"));           
            lcd_gotoxy(21,1);                                  
            if(peso_total >= ajuste_peso_maximo && flag_peso == 1) 
            {                                                  
               lcd_gotoxy(2,1);                                
               printf(lcd_putc,("INFORME SUA SENHA:"));        
               lcd_gotoxy(22,1);                               
               printf(lcd_putc, ("SISTEMA BLOQUEADO!"));       
               lcd_gotoxy(21,2);                               
               printf(lcd_putc, ("PESO MAXIMO EXCEDIDO"));     
            }                                                  
            vezes = 1;                                         
         }                                                     
         senha();                                              
      }                                                        
      
      if(ajuste == 1 && input(PIN_B5) == 1 && flag_1 == 1)     
      {                                                        
         flag_1 = 0;                                           
      }                                                        
      
      if(ajuste == 2 && flag_peso_maximo == 0)                 
      {                                                        
         flag_local=0;
         menu();                                               
         lcd_gotoxy(40,2);                                     
         printf(lcd_putc,("<"));                               
      }                                                        
      
      if(ajuste == 2 && input(PIN_B5) == 0 && flag_1 == 0)     
      {                                                        
         lcd_putc('\f');                                       
         flag_1 = 1;                                           
         flag_peso_maximo = 1;                                
      }                                                        
      
      if(flag_peso_maximo == 1)                                
      {                                                        
         peso_maximo();                                        
      }                                                        
      
      if(ajuste == 2 && input(PIN_B5) == 1 && flag_1 == 1)     
      {                                                        
         flag_1 = 0;                                           
      }                                                        
      
      if(ajuste >= 3)                                          
      {                                                        
         ajuste = 0;                                           
      }                                                        
   }                                                           
}                                                              
//************************************************************************************************


//*********************************** Tratamento das Fun��es *************************************
int32 read_count()                                             
{                                                              
   int32 count;                                               
   int i;                                                      
   int position_1;                                             
   int position_2;                                             
   int position_3;                                             

   output_high(HX711_DO);                                      
   output_low(HX711_CLK);                                      
   count = 0;                                                  
   
   while(input(HX711_DO));                                     

   for (i=0; i<24; i++)                                        
   {                                                           
      output_high(HX711_CLK);                                  
      count = count<<1;                                        
      output_low(HX711_CLK);                                   
      
      if(input(HX711_DO))                                      
      {                                                        
         count++;                                              
      }                                                        
   }                                                           
    
   output_high(HX711_CLK);                                     
   count = count^0x800000;                                     
   output_low(HX711_CLK);                                      

   position_1 = make8(count, 0);                               
   position_2 = make8(count, 1);                               
   position_3 = make8(count, 2);                               
   position_1 = (position_1 & 0b11111000);                     
   count = make16(position_3, position_2);                     
   return(count);                                              
}                                                              

void informativo()                                             
{                                                              
   disable_interrupts(INT_EXT);                                
   lcd_gotoxy(1,1);                                            
   printf(lcd_putc, "********************");                   
   lcd_gotoxy(1,2);                                            
   printf(lcd_putc, "*");                                      
   lcd_gotoxy(20,2);                                           
   printf(lcd_putc, "*");                                      
   lcd_gotoxy(21,1);                                           
   printf(lcd_putc, "*");                                      
   lcd_gotoxy(40,1);                                          
   printf(lcd_putc, "*");                                      
   lcd_gotoxy(40,2);                                           
   printf(lcd_putc, "*");                                      
   lcd_gotoxy(21,2);                                           
   printf(lcd_putc, "********************");                   
   lcd_gotoxy(4,2);                                            
   printf(lcd_putc, "SEJA BEM VINDO");                         
   lcd_gotoxy(26,1);                                           
   printf(lcd_putc,"AO SISTEMA");                              
   delay_ms(3000);                                             
   lcd_putc('\f');                                             
}                                                             

void menu()                                                    
{                                                              
   disable_interrupts(INT_EXT);                                
   lcd_gotoxy(1,1);                                            
   printf(lcd_putc, "MENU");                                   
   lcd_gotoxy(1,2);                                            
   printf(lcd_putc, "1 - HOME");                               
   lcd_gotoxy(21,1);                                           
   printf(lcd_putc, "2 - SENHA");                              
   lcd_gotoxy(21,2);                                           
   printf(lcd_putc, "3 - PESOS");                              
   
   if(input(PIN_C3) == 0)                                      
   {                                                           
      output_low(PIN_D2);                                      
   }                                                           
   
   if(input(PIN_C4) == 0)                                      
   {                                                           
      output_low(PIN_D3);                                      
   }                                                           
   
   if(input(PIN_A3) == 0)                                      
   {                                                           
      output_low(PIN_A5);                                      
   }                                                           
   
   if(input(PIN_A4) == 0)                                      
   {                                                           
      output_low(PIN_E0);                                      
   }                                                          
}                                                              

void home()                                                      
{                                                              
   flag_cancela = 0;                                           
   if(flag_local == 0)                                         
   {                                                           
      printf(lcd_putc,("\f"));                                 
      lcd_gotoxy(1,1);                                         
      printf(lcd_putc, ("*****CARREGANDO*****"));              
      lcd_gotoxy(2,2);                                         
      printf(lcd_putc, ("POR FAVOR AGUARDE!"));                
      lcd_gotoxy(22,1);                                        
      printf(lcd_putc, ("ESTAMOS PREPARANDO"));                
      lcd_gotoxy(23,2);                                        
      printf(lcd_putc, ("TUDO PARA VOCE!"));                  
      flag_local = 1;                                          
      if(input(PIN_C3) == 0)                                   
      {                                                       
         output_low(PIN_D2);                                   
      }                                                        
      
      if(input(PIN_C4) == 0)                                   
      {                                                       
         output_low(PIN_D3);                                   
      }                                                        
      
      if(input(PIN_A3) == 0)                                   
      {                                                        
         output_low(PIN_A5);                                   
      }                                                        
      
      if(input(PIN_A4) == 0)                                   
      {                                                        
         output_low(PIN_E0);                                   
      }                                                        
      delay_ms(1000);                                          
      printf(lcd_putc, ("\f"));                                
   }                                                           
   if(peso_total < ajuste_peso_maximo || flag_peso == 2 || flag_inicio == 1) 
   {                                                           
      disable_interrupts(INT_EXT);                             
      lcd_gotoxy(6,1);                                        
      printf(lcd_putc, "PESO ATUAL");                          
      lcd_gotoxy(9,2);                                         
      printf(lcd_putc,("%04lu"),calc_2);                       
      lcd_gotoxy(26,1);                                        
      printf(lcd_putc, "PESO TOTAL");                          
      lcd_gotoxy(29,2);                                        
      printf(lcd_putc,("%04lu"),peso_total);                   
      
      convert = read_count();                                  
      diferenca = convert - 33410;                             
       
      calc_1=(convert-33400)/8.80;                             
      calc_2=(calc_1*5)-985;                                       
      
      if(diferenca < 6)                                        
      {                                                        
         calc_2 = 0;                                          
      }                                                        
      
      if(calc_2 < 0 || calc_2 > 11000)                         
      {                                                        
         calc_2 = 0;                                           
      }                                                        
   
      if(input(PIN_B5) == 0 && flag_2 == 0)                    
      {                                                        
         k = 0;                                                
         if(calc_2 >= ajuste_animal)                            
         {                                                     
            printf(lcd_putc,("\f"));                           
            lcd_gotoxy(1,1);                                              
            printf(lcd_putc, "PESO ATUAL EXCEDIDO");           
            lcd_gotoxy(1,2);                                        
            printf(lcd_putc, "PRESSIONE");                     
            lcd_gotoxy(21,1);                                          
            printf(lcd_putc, "CONFIRMA - CONTINUAR");          
            lcd_gotoxy(21,2);                                            
            printf(lcd_putc, "FECHAR - SAIR");                 
            delay_ms(1000);                                    
            while(k<1)                                         
            {                                                  
               if(input(PIN_B5) == 0 && flag_2 == 0)           
               {                                               
                  k = 1;                                      
                  flag_2 = 1;                                  
                  printf(lcd_putc,("\f"));                     
                  lcd_gotoxy(6,1);                             
                  printf(lcd_putc, "PESO ATUAL");              
                  lcd_gotoxy(9,2);                             
                  printf(lcd_putc,("%04lu"),calc_2);           
                  lcd_gotoxy(26,1);                            
                  printf(lcd_putc, "PESO TOTAL");              
                  lcd_gotoxy(29,2);                            
                  printf(lcd_putc,("%04lu"),peso_total);      
               }                                               
               if(input(PIN_B5) == 1 && flag_2 == 1)           
               {                                               
                  flag_2 = 0;                                  
               }                                               
               if(input(PIN_C7) == 0 && flag_zera == 0)        
               {                                               
                  flag_cancela = 1;                            
                  flag_zera = 1;                               
                  k = 1;                                       
                  printf(lcd_putc,("\f"));                     
                  lcd_gotoxy(1,1);                             
                  printf(lcd_putc, ("*****CARREGANDO*****"));  
                  lcd_gotoxy(2,2);                             
                  printf(lcd_putc, ("POR FAVOR AGUARDE!"));    
                  lcd_gotoxy(22,1);                            
                  printf(lcd_putc, ("ESTAMOS PREPARANDO"));    
                  lcd_gotoxy(23,2);                           
                  printf(lcd_putc, ("TUDO PARA VOCE!"));       
                  flag_local = 1;                              
                  delay_ms(2000);                              
                  printf(lcd_putc, ("\f"));                    
               }                                               
               if(input(PIN_C7) == 1 && flag_zera == 1)        
               {                                               
                  flag_zera = 0;                               
               }                                               
            }                                                  
         }                                                     
         
         if(flag_cancela == 0)                                 
         {                                                     
            flag_2 = 1;                                        
            k = 0;                                            
            peso_total = peso_total + calc_2;                  
            peso_total_parte1 = make8(peso_total,0);           
            peso_total_parte2 = make8(peso_total,1);           
            write_eeprom(254,peso_total_parte1);               
            write_eeprom(255,peso_total_parte2);               
            lcd_gotoxy(27,2);                                  
            printf(lcd_putc,("+"));                            
            delay_ms(1000);                                    
            printf(lcd_putc,("\f"));                           
         }                                                     
      }                                                        
      if(input(PIN_B5) == 1 && flag_2 == 1)                    
      {                                                        
         flag_2 = 0;                                           
      }                                                        
   }                                                           
   else                                                        
   {                                                           
      if(flag_inicio == 0)                                     
      {                                                        
         if(flag_peso == 0)                                    
         {                                                     
            lcd_putc('\f');                                    
            flag_ok = 0;                                       
            flag_confirma = 0;                                 
            libera = 0;                                        
            i = 0;                                             
            vezes = 0;                                         
            flag_home = 1;                                     
         }                                                     
         enable_interrupts(INT_EXT);                           
         if(flag_ajuste == 0)                                  
         {                                                     
            lcd_gotoxy(6,1);                                   
            printf(lcd_putc, "PESO ATUAL");                    
            lcd_gotoxy(9,2);                                   
            printf(lcd_putc,("%04lu"),calc_2);                 
            lcd_gotoxy(26,1);                                  
            printf(lcd_putc, "PESO TOTAL");                    
            lcd_gotoxy(29,2);                                 
            printf(lcd_putc,("%04lu"),peso_total);             
            lcd_putc('\f');                                    
         }                                                     
         flag_ajuste = 1;                                      
         flag_peso = 1;                                        
         lcd_gotoxy(2,1);                                      
         printf(lcd_putc,("INFORME SUA SENHA:"));              
         lcd_gotoxy(22,1);                                     
         printf(lcd_putc, ("SISTEMA BLOQUEADO!"));             
         lcd_gotoxy(21,2);                                     
         printf(lcd_putc, ("PESO MAXIMO EXCEDIDO"));           
         senha();                                             
      }                                                           
   }                                                           
   
   if(input(PIN_C7) == 0 && flag_peso != 1 && flag_cancela == 0)            
   {                                                           
      peso_total = 0;                                          
      flag_peso = 0;                                           
      flag_libera_zera = 1;                                    
      flag_inicio = 0;                                         
      write_eeprom(11,flag_inicio);                            
      write_eeprom(254,0);                                     
      write_eeprom(255,0);                                     
      printf(lcd_putc,("\f"));                                 
   }                                                           
   
   if(input(PIN_C7) == 1 && flag_libera_zera == 1)             
   {                                                          
      flag_libera_zera = 0;                                    
   }                                                           
   
   if(input(PIN_B7) == 0 && flag_3 == 0)                       
   {                                                           
      flag_3 = 1;                                              
   }                                                           
   
   if(input(PIN_B7) == 1 && flag_3 == 1)                      
   {                                                           
      flag_3 = 0;                                              
   }                                                           
   
   if(input(PIN_B6) == 0 && flag_4 == 0)                       
   {                                                         
      flag_4 = 1;                                              
   }                                                           
   
   if(input(PIN_B6) == 1 && flag_4 == 1)                      
   {                                                           
      flag_4 = 0;                                              
   }                                                           
   
   if(input(PIN_B7) == 0 && input(PIN_C3) == 1 && flag_ajuste == 0) 
   {                                                           
      output_low(PIN_D3);                                      
      output_high(PIN_D2);                                     
   }                                                           
   
   if(input(PIN_B6) == 0 && input(PIN_C4) == 1 && flag_ajuste == 0) 
   {                                                           
      output_low(PIN_D2);                                     
      output_high(PIN_D3);                                     
   }                                                           
   
   if(input(PIN_C3) == 0)                                      
   {                                                           
      output_low(PIN_D2);                                      
   }                                                           
   
   if(input(PIN_C4) == 0)                                     
   {                                                           
      output_low(PIN_D3);                                      
   }                                                           
 
   if(input(PIN_C5) == 0 && flag_5 == 0)                       
   {                                                           
      flag_5 = 1;                                              
   }                                                           
   
   if(input(PIN_C5) == 1 && flag_5 == 1)                       
   {                                                           
      flag_5 = 0;                                              
   }                                                           
   
   if(input(PIN_A2) == 0 && flag_6 == 0)                       
   {                                                           
      flag_6 = 1;                                              
   }                                                          
   
   if(input(PIN_A2) == 1 && flag_6 == 1)                       
   {                                                           
      flag_6 = 0;                                             
   }                                                          
   
   if(input(PIN_C5) == 0 && input(PIN_A3) == 1 && flag_ajuste == 0) 
   {                                                           
      output_low(PIN_E0);                                      
      output_high(PIN_A5);                                     
   }                                                           
   
   if(input(PIN_A2) == 0 && input(PIN_A4) == 1 && flag_ajuste == 0) 
   {                                                           
      output_low(PIN_A5);                                      
      output_high(PIN_E0);                                     
   }                                                           
   
   if(input(PIN_A3) == 0)                                      
   {                                                           
      output_low(PIN_A5);                                      
   }                                                           
   
   if(input(PIN_A4) == 0)                                      
   {                                                           
      output_low(PIN_E0);                                      
   }                                                           
}                                                              

void senha()                                                  
{                                                              
   enable_interrupts(INT_EXT);                                 
   if(digito != ' ')                                           
   {                                                          
      libera++;                                                
      lcd_gotoxy(i+9,2);                                       
      lcd_putc(digito);                                        
      senha1[i] = digito;                                      
      i++;                                                     
      digito = ' ';                                           
      if(i > 3)                                                
      {                                                       
         i = 0;                                                
      }                                                        
   }                                                           
      
   if(libera > 3)                                                                                         
   {                                                          
      flag_ok = 1;                                             
      flag_grava = 1;                                          
   }                                                           
      
   if(input(PIN_C3) == 0)                                      
   {                                                           
      output_low(PIN_D2);                                      
   }                                                           
   
   if(input(PIN_C4) == 0)                                      
   {                                                           
      output_low(PIN_D3);                                      
   }                                                           
   
   if(input(PIN_A3) == 0)                                      
   {                                                           
      output_low(PIN_A5);                                      
   }                                                           
   
   if(input(PIN_A4) == 0)                                      
   {                                                           
      output_low(PIN_E0);                                      
   }                                                          
}                                                              

void peso_maximo()            
{                                                             
   disable_interrupts(INT_EXT);                                
   if(input(PIN_C7) == 0 && flag_2 == 0)                       
   {                                                           
      lcd_putc('\f');                                          
      estado_botao++;                                          
      flag_2 = 1;                                              
   }                                                          
      
   if(input(PIN_C7) == 1 && flag_2 == 1)                       
   {                                                           
      flag_2 = 0;                                              
   }                                                           
   
   if(estado_botao == 2)                                       
   {                                                           
      estado_botao = 0;                                        
   }                                                           

   if(estado_botao == 0)                                       
   {                                                           
      lcd_gotoxy(20,2);                                        
      printf(lcd_putc,("<"));                                  
      
      if(input(PIN_B6) == 0)                                   
      {                                                      
         acelera_positivo++;                                   
      
         if(input(PIN_B6) == 0 && acelera_positivo < 10)       
         {                                                     
            ajuste_animal++;                                   
            delay_ms(230);                                     
         }                                                     
         else                                                  
         {                                                     
            if(input(PIN_B6) == 0 && acelera_positivo < 30)    
            {                                                  
               ajuste_animal++;                                
               delay_ms(100);                                  
            }                                                  
            else                                               
            {                                                  
               ajuste_animal++;                                
               delay_ms(50);                                   
            }                                                  
         }                                                     
            
         if(ajuste_animal >= 50001)                           
         {                                                     
            ajuste_animal = 0;                                 
         }                                                     
      }                                                        
   
      if(input(PIN_B6) == 1)                                   
      {                                                        
         acelera_positivo = 0;                                 
      }                                                        
   
      if(input(PIN_B7) == 0)                                   
      {                                                       
         acelera_negativo++;                                   
      
         if(input(PIN_B7) == 0 && acelera_negativo < 10)      
         {                                                     
            ajuste_animal--;                                   
            delay_ms(230);                                    
         }                                                     
         else                                                  
         {                                                     
            if(input(PIN_B7) == 0 && acelera_negativo < 30)    
            {                                                  
               ajuste_animal--;                                
               delay_ms(100);                                  
            }                                                  
            else                                              
            {                                                  
               ajuste_animal--;                                
               delay_ms(50);                                   
            }                                                  
         }                                                     
         
         if(ajuste_animal == -1)                               
         {                                                     
            ajuste_animal = 50000;                             
         }                                                     
      }                                                        
   
      if(input(PIN_B7) == 1)                                   
      {                                                        
         acelera_negativo = 0;                                 
      }                                                       
   }                                                          
  
   if(estado_botao == 1)                                       
   {                                                          
      lcd_gotoxy(40,2);                                        
      printf(lcd_putc,("<"));                                  
      
      if(input(PIN_B6) == 0)                                   
      {                                                        
         acelera_positivo++;                                   
      
         if(input(PIN_B6) == 0 && acelera_positivo < 10)       
         {                                                     
            ajuste_peso_maximo++;                              
            delay_ms(230);                                     
         }                                                    
         else                                                  
         {                                                     
            if(input(PIN_B6) == 0 && acelera_positivo < 30)    
            {                                                  
               ajuste_peso_maximo++;                           
               delay_ms(100);                                  
            }                                                  
            else                                               
            {                                                  
               ajuste_peso_maximo++;                           
               delay_ms(50);                                   
            }                                                  
         }                                                     
            
         if(ajuste_peso_maximo >=50001)                        
         {                                                     
            ajuste_peso_maximo = 0;                            
         }                                                     
      }                                                        
   
      if(input(PIN_B6) == 1)                                   
      {                                                        
         acelera_positivo = 0;                                 
      }                                                        
   
      if(input(PIN_B7) == 0)                                   
      {                                                        
         acelera_negativo++;                                   
      
         if(input(PIN_B7) == 0 && acelera_negativo < 10)       
         {                                                     
            ajuste_peso_maximo--;                              
            delay_ms(230);                                     
         }                                                     
         else                                                  
         {                                                     
            if(input(PIN_B7) == 0 && acelera_negativo < 30)    
            {                                                  
               ajuste_peso_maximo--;                           
               delay_ms(50);                                   
            }                                                  
            else                                               
            {                                                  
               ajuste_peso_maximo--;                           
               delay_ms(5);                                    
            }                                                 
         }                                                     
            
         if(ajuste_peso_maximo == -1)                          
         {                                                     
            ajuste_peso_maximo = 50000;                        
         }                                                     
      }                                                        
   
      if(input(PIN_B7) == 1)                                   
      {                                                        
         acelera_negativo = 0;                                 
      }                                                        
   }                                                           
   
   lcd_gotoxy(1,1);                                            
   printf(lcd_putc,("AJUSTE O PESO MAXIMO"));                  
   lcd_gotoxy(1,2);                                            
   printf(lcd_putc,("DO ANIMAL = %05lu"),ajuste_animal);       
   lcd_gotoxy(21,1);                                           
   printf(lcd_putc,("AJUSTE O PESO MAXIMO"));                  
   lcd_gotoxy(21,2);                                           
   printf(lcd_putc,("DO CAMINHAO = %05lu"),ajuste_peso_maximo);
   
   peso_maximo_1 = make8(ajuste_peso_maximo,0);                
   peso_maximo_2 = make8(ajuste_peso_maximo,1);                
   
   ajuste_peso_maximo = make16(peso_maximo_2,peso_maximo_1);   
    
   write_eeprom(0,peso_maximo_1);                              
   delay_ms(10);                                               
   
   write_eeprom(1,peso_maximo_2);                              
   delay_ms(10);                                               
   
   peso_animal_1 = make8(ajuste_animal,0);                     
   peso_animal_2 = make8(ajuste_animal,1);                    
   
   write_eeprom(8,peso_animal_1);                              
   delay_ms(10);                                               
   
   write_eeprom(9,peso_animal_2);                              
   delay_ms(10);                                               
   
   if(input(PIN_C3) == 0)                                      
   {                                                           
      output_low(PIN_D2);                                      
   }                                                           
   
   if(input(PIN_C4) == 0)                                      
   {                                                           
      output_low(PIN_D3);                                      
   }                                                           
   
   if(input(PIN_A3) == 0)                                      
   {                                                          
      output_low(PIN_A5);                                      
   }                                                           
   
   if(input(PIN_A4) == 0)                                      
   {                                                           
      output_low(PIN_E0);                                     
   }                                                           
}                                                              
//************************************************************************************************

//************************** Tratamento das Fun��es de Interrup��o *******************************
#int_EXT                                                       
void le_teclado_3x4()                                          
{                                                              
   output_low(PIN_D5);                                         
   output_high(PIN_D6);                                        
   output_high(PIN_D7);                                        
   
   if(input(PIN_B1) == 0)                                      
   {                                                          
      digito = '1';                                                      
   }                                                           
      
   if(input(PIN_B2) == 0)                                      
   {                                                           
      digito = '4';                                                      
   }                                                           
   
   if(input(PIN_B3) == 0)                                      
   {                                                           
      digito = '7';                                                      
   }                                                           
   
   if(input(PIN_B4) == 0 && libera >= 4 && flag_ok == 1 && flag_confirma < 1)
   {                                                         
      flag_confirma++;                                         
      if(read_eeprom(3) == senha1[0] && read_eeprom(4) == senha1[1] && read_eeprom(5) == senha1[2] && read_eeprom(6) == senha1[3]) 
      {                                                        
         if(flag_peso == 1)                                    
         {                                                     
            lcd_putc('\f');                                    
         }                                                     
         i = 0;                                                
         lcd_gotoxy(24,1);                                     
         printf(lcd_putc,("SENHA CORRETA!"));                  
         delay_ms(1000);                                       
         lcd_putc('\f');                                       
         libera = 0;                                           
         if(flag_peso == 0)                                    
         {                                                     
            lcd_gotoxy(1,1);                                   
            printf(lcd_putc,("INFORME A NOVA SENHA"));         
            senha();                                           
         }                                                     
         if(flag_peso == 1)                                    
         {                                                     
            flag_peso = 2;                                     
            flag_ajuste = 0;                                   
            flag_local = 0;                                    
            flag_inicio = 1;                                   
            write_eeprom(11,flag_inicio);                      
         }                                                     
      }                                                        
      else                                                     
      {                                                        
         i = 0;                                                
         libera = 0;                                           
         flag_ok = 0;                                          
         if(flag_peso == 1)                                    
         {                                                     
            lcd_putc('\f');                                    
         }                                                     
         flag_confirma = 0;                                    
         lcd_gotoxy(25,1);                                     
         printf(lcd_putc, ("SENHA ERRADA"));                   
         lcd_gotoxy(21,2);                                      
         printf(lcd_putc, ("TENTE DE NOVO EM 3s!"));           
         delay_ms(3000);                                       
         lcd_putc('\f');                                       
         lcd_gotoxy(2,1);                                      
         printf(lcd_putc,("INFORME SUA SENHA:"));              
         if(peso_total >= ajuste_peso_maximo && flag_peso == 1)
         {                                                     
            lcd_gotoxy(22,1);                                  
            printf(lcd_putc, ("SISTEMA BLOQUEADO!"));          
            lcd_gotoxy(21,2);                                  
            printf(lcd_putc, ("PESO MAXIMO EXCEDIDO"));        
         }                                                     
         senha();                                              
      }                                                        
   }                                                           
   
   output_high(PIN_D5);                                        
   output_low(PIN_D6);                                         
   output_high(PIN_D7);                                        
   
   if(input(PIN_B1) == 0)                                      
   {                                                            
      digito = '2';                                                       
   }                                                           
      
   if(input(PIN_B2) == 0)                                      
   {                                                           
      digito = '5';                                                       
   }                                                           
   
   if(input(PIN_B3) == 0)                                      
   {                                                           
      digito = '8';                                                    
   }                                                           
   
   if(input(PIN_B4) == 0)                                      
   {                                                           
      digito = '0';                                                   
   }                                                           
   
   output_high(PIN_D5);                                        
   output_high(PIN_D6);                                        
   output_low(PIN_D7);                                         
   
   if(input(PIN_B1) == 0)                                      
   {                                                           
      digito = '3';                                                
   }                                                          
      
   if(input(PIN_B2) == 0)                                      
   {                                                           
      digito = '6';                                               
   }                                                           
   
   if(input(PIN_B3) == 0)                                     
   {                                                           
      digito = '9';                                            
   }                                                           
   
   if(input(PIN_B4) == 0 && libera > 3 && flag_confirma >= 1 && flag_ajuste==0)  
   {                                                           
      flag_ok = 0;                                             
      flag_confirma = 0;                                       
      libera = 0;                                              
      flag_grava = 0;                                          
      i = 0;                                                   
      
      write_eeprom(3,senha1[0]);                               
      write_eeprom(4,senha1[1]);                               
      write_eeprom(5,senha1[2]);                               
      write_eeprom(6,senha1[3]);                               
      
      lcd_putc('\f');                                          
      lcd_gotoxy(4,1);                                         
      printf(lcd_putc,("SENHA ALTERADA"));                     
      lcd_gotoxy(4,2);                                         
      printf(lcd_putc,("AGUARDE ALGUNS"));                     
      lcd_gotoxy(24,1);                                        
      printf(lcd_putc,("SEGUNDOS PARA"));                      
      lcd_gotoxy(23,2);                                        
      printf(lcd_putc,("RETORNAR A SENHA!"));                    
      delay_ms(3000);                                          
      lcd_putc('\f');                                          
      lcd_gotoxy(2,1);                                         
      printf(lcd_putc,("INFORME SUA SENHA:"));                 
      if(peso_total >= ajuste_peso_maximo && flag_peso == 1)   
      {                                                        
         lcd_gotoxy(22,1);                                     
         printf(lcd_putc, ("SISTEMA BLOQUEADO!"));             
         lcd_gotoxy(21,2);                                     
         printf(lcd_putc, ("PESO MAXIMO EXCEDIDO"));           
         senha();                                              
      }                                                        
      senha();                                                 
   }                                                           
   
   output_low(PIN_D5);                                         
   output_low(PIN_D6);                                         
   output_low(PIN_D7);                                         
   
   delay_ms(50);                                               
}                                                              
//************************************************************************************************