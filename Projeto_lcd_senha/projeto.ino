#include <LiquidCrystal_I2C.h>

#include <Wire.h>
//para usar o lcd i2c
// Endereço I2C do display LCD
#define LCD_ADDRESS 0x20

// Número de colunas e linhas do LCD
#define LCD_COLUMNS 16
#define LCD_ROWS 2
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

#define NUMERO_DE_LINHAS 4
#define NUMERO_DE_COLUNAS 4

#define PINOS_LINHA {3, 4, 5, 6}
#define PINOS_COLUNA {8, 9, 10, 11}

int pinos_linha[NUMERO_DE_LINHAS] = PINOS_LINHA;
int pinos_coluna[NUMERO_DE_COLUNAS] = PINOS_COLUNA;

String valoresnum[4][4] = {{"1", "2", "3", "A"}, {"4", "5", "6", "B"}, {"7", "8", "9", "0"}, {"0", "0", "0", "0"}};
String mensagem = "";

#define btnEsq 13
#define btnDir 12
//int btnEsq = 13, btnDir = 12;

void setup() {
    // Inicializa o display LCD
  lcd.init();
  // Ativa o backlight do LCD
  lcd.backlight();
  // Define a posição do cursor na coluna 0, linha 0
  lcd.setCursor(0, 0);
  // Imprime um número no LCD
  lcd.print("Ola Mundo!");
  delay(3000);
  lcd.clear();
  // Configura pinos de saída para as linhas
  for (int i = 0; i < NUMERO_DE_LINHAS; i++) {
    pinMode(pinos_linha[i], OUTPUT);
  }
  
  // Configura pinos de entrada para as colunas
  for (int i = 0; i < NUMERO_DE_COLUNAS; i++) {
    pinMode(pinos_coluna[i], INPUT);
  }
  
  pinMode(btnEsq, INPUT);
  pinMode(btnDir, INPUT);
  
  
  Serial.begin(9600);
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println();
  
  
  
  //digitalWrite(btnEsq, LOW);
  //digitalWrite(btnDir, LOW);

}

void loop() {
  if(digitalRead(btnEsq) == HIGH){
    btnSalvar(mensagem);
  }
  
  if(digitalRead(btnDir) == HIGH){
    btnValidar(mensagem);
  }
  
  
  for (int linha = 0; linha < NUMERO_DE_LINHAS; linha++) {
    // Alterna para a próxima linha
    for (int i = 0; i < NUMERO_DE_LINHAS; i++) {
      digitalWrite(pinos_linha[i], i == linha ? HIGH : LOW);
    }
    
    // Verifica as colunas para a linha atual
    for (int coluna = 0; coluna < NUMERO_DE_COLUNAS; coluna++) {
      if (digitalRead(pinos_coluna[coluna]) == HIGH) {
        imprime_linha_coluna(linha + 1, coluna + 1);        
          
        while (digitalRead(pinos_coluna[coluna]) == HIGH) {
          	delay(100);
          	//lcd.clear();
          	if(linha+1 == 1 && coluna+1 == 4){
        		mensagem = mensagem.substring(0, mensagem.length() - 1);
              	lcd.clear();
              	lcd.print(mensagem);
            }else if(linha+1 == 2 && coluna + 1 == 4){
            	lcd.clear();
              	mensagem = "";
            }else{
              lcd.print(valoresnum[linha][coluna]);
              mensagem += valoresnum[linha][coluna];
            }
          	//lcd.print(mensagem);
        
        } // Aguarda até que a tecla seja liberada
      }
    }
  }
  delay(10);
  
}
String senha = "";
void btnSalvar(String msg){
  //lcd.print("pqq");
  if(msg != "")
	senha = msg;
}
void btnValidar(String msg){
  //lcd.print("pqq222");
  if(msg != ""){
  	if(senha == msg){
  		lcd.clear();
    	lcd.print("Acesso autorizado!!");
  	}else{
  		lcd.clear();
    	lcd.print("Acesso negado!!");
  	}
  }else
    lcd.print("Digite um valor!");
  		
}

void imprime_linha_coluna(int linha, int coluna) {
  Serial.print("Tecla pressionada: Linha ");
  Serial.print(linha);
  Serial.print(", Coluna ");
  Serial.println(coluna);
}