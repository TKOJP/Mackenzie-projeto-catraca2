#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h> 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  
 
LiquidCrystal lcd(6, 7, 5, 4, 3, 2); 
char st[20]; 
void setup() 
{
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();
  Serial.println("Aproxime o seu cartao do leitor");
  Serial.println();  
  lcd.begin(16, 2);  
  mensageminicial();
}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("ID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "F3 A3 0E 27") 
  {
    Serial.println("Ola Thiago!");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ola Thiago!");
    lcd.setCursor(0,1);
    lcd.print("Acesso liberado!");
    delay(3000);
    mensageminicial();
  }
  if (conteudo.substring(1) == "83 62 56 73") 
  {
    Serial.println("ID Invalido!");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ID Invalido!");
    lcd.setCursor(0,1);
    lcd.print("Acesso Negado !");
    delay(3000);
    mensageminicial();
  }
}  
void mensageminicial()
{
  lcd.clear();
  lcd.print("Aproxime o seu");  
  lcd.setCursor(0,1);
  lcd.print("cartao do leitor");  
}
