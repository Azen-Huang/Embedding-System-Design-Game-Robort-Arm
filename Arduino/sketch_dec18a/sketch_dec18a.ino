#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <OV7670.h>
#include <SoftwareSerial.h>


// OV7670 配置
#define OV7670_ADDR 0x21
OV7670 ov7670(OV7670_ADDR);

// Bluetooth 配置
SoftwareSerial BTSerial(2, 3); // RX, TX

Servo spin, claw, right, left; //宣告一個Servo物件，命名為servoClaw (Servo是伺服馬達的封裝類別，定義了伺服馬達各種屬性與動作。)
int init_pos_right = 90, init_pos_left = 90, init_pos_spin = 115, init_pos_claw = 70;
int curr_move_right, curr_move_left, curr_move_spin;
int claw_close = 60, claw_open = 10;
int board[9], ex_board[9];

void setup(){ //初始化副程式/函式，此副程式只會在Arduino板子啟動時執行一次
  Serial.begin(9600);
  BTSerial.begin(9600);

  board[0] = 0;board[1] = 0;board[2] = 0;
  board[3] = 0;board[4] = 0;board[5] = 0;
  board[6] = 0;board[7] = 0;board[8] = 0;

  ex_board[0] = 0;ex_board[1] = 0;ex_board[2] = 0;
  ex_board[3] = 0;ex_board[4] = 0;ex_board[5] = 0;
  ex_board[6] = 0;ex_board[7] = 0;ex_board[8] = 0;

  spin.attach(7);//底座 0-最右邊 90-中間 180-最邊
  claw.attach(11); //爪子 70-合 0-開
  right.attach(12);// 70-上 115-下 
  left.attach(13);// 0-前 180-後

  ov7670.begin();
}

void back_init_pos(){
  while(curr_move_right != init_pos_right){
    curr_move_right = curr_move_right - 1;
    right.write(curr_move_right);
    claw.write(claw_open);
    delay(10);
  }
  delay(500);
  while(curr_move_left != init_pos_left){
    curr_move_left = curr_move_left - 1;
    left.write(curr_move_left);
    claw.write(claw_open);
    delay(10);
  }
  delay(500);
  int flag = curr_move_spin - init_pos_spin;
  if(flag < 0){
    while(curr_move_spin != init_pos_spin){
      curr_move_spin = curr_move_spin + 1;
      spin.write(curr_move_spin);
      claw.write(claw_close);
      right.write(curr_move_right);
      left.write(curr_move_left);
      delay(10);
    }
  }
  else{
    while(curr_move_spin != init_pos_spin){
      curr_move_spin = curr_move_spin - 1;
      spin.write(curr_move_spin);
      claw.write(claw_close);
      right.write(curr_move_right);
      left.write(curr_move_left);
      delay(10);
    }    
  }
  delay(2000);
}

void To_Pos_1(){
  int target_spin = init_pos_spin;
  int target_right_1 = init_pos_right + 7;
  int target_left_1 = init_pos_left + 25;
  
  while(curr_move_spin != target_spin){
    curr_move_spin = curr_move_spin + 1;
    right.write(curr_move_right);
    left.write(curr_move_left);
    spin.write(curr_move_spin);
    delay(10);
  }
  while(curr_move_left != target_left_1){
    curr_move_left = curr_move_left + 1;
    left.write(curr_move_left);
    delay(10);
  }
  while(curr_move_right != target_right_1){
    curr_move_right = curr_move_right + 1;
    right.write(curr_move_right);
    delay(10);
  }
}

void To_Pos_2(){
  int target_spin = init_pos_spin;
  int target_right_1 = init_pos_right + 15;
  int target_left_1 = init_pos_left + 50;

  while(curr_move_spin != target_spin){
    curr_move_spin = curr_move_spin + 1;
    right.write(curr_move_right);
    left.write(curr_move_left);
    spin.write(curr_move_spin);
    delay(10);
  }
  while(curr_move_left != target_left_1){
    curr_move_left = curr_move_left + 1;
    left.write(curr_move_left);
    delay(10);
  }
  while(curr_move_right != target_right_1){
    curr_move_right = curr_move_right + 1;
    right.write(curr_move_right);
    delay(10);
  }
}

void To_Pos_3(){
  int target_spin = init_pos_spin;
  int target_right_1 = init_pos_right + 27;
  int target_left_1 = init_pos_left + 80;

  while(curr_move_spin != target_spin){
    curr_move_spin = curr_move_spin + 1;
    right.write(curr_move_right);
    left.write(curr_move_left);
    spin.write(curr_move_spin);
    delay(10);
  }
  while(curr_move_left != target_left_1){
    curr_move_left = curr_move_left + 1;
    left.write(curr_move_left);
    delay(10);
  }
  while(curr_move_right != target_right_1){
    curr_move_right = curr_move_right + 1;
    right.write(curr_move_right);
    delay(10);
  }
}

void To_Pos_4(){
  int target_spin = init_pos_spin + 16;
  int target_right_1 = init_pos_right + 11;
  int target_left_1 = init_pos_left + 25;

  while(curr_move_spin != target_spin){
    curr_move_spin = curr_move_spin + 1;
    right.write(curr_move_right);
    left.write(curr_move_left);
    spin.write(curr_move_spin);
    delay(10);
  }
  while(curr_move_left != target_left_1){
    curr_move_left = curr_move_left + 1;
    left.write(curr_move_left);
    delay(10);
  }
  while(curr_move_right != target_right_1){
    curr_move_right = curr_move_right + 1;
    right.write(curr_move_right);
    delay(10);
  }
}

void To_Pos_5(){
  int target_spin = init_pos_spin + 14;
  int target_right_1 = init_pos_right + 14;
  int target_left_1 = init_pos_left + 55;

  while(curr_move_spin != target_spin){
    curr_move_spin = curr_move_spin + 1;
    right.write(curr_move_right);
    left.write(curr_move_left);
    spin.write(curr_move_spin);
    delay(10);
  }
  while(curr_move_left != target_left_1){
    curr_move_left = curr_move_left + 1;
    left.write(curr_move_left);
    delay(10);
  }
  while(curr_move_right != target_right_1){
    curr_move_right = curr_move_right + 1;
    right.write(curr_move_right);
    delay(10);
  }
}

void To_Pos_6(){
  int target_spin = init_pos_spin + 10;
  int target_right_1 = init_pos_right + 27;
  int target_left_1 = init_pos_left + 75;

  while(curr_move_spin != target_spin){
    curr_move_spin = curr_move_spin + 1;
    right.write(curr_move_right);
    left.write(curr_move_left);
    spin.write(curr_move_spin);
    delay(10);
  }
  while(curr_move_left != target_left_1){
    curr_move_left = curr_move_left + 1;
    left.write(curr_move_left);
    delay(10);
  }
  while(curr_move_right != target_right_1){
    curr_move_right = curr_move_right + 1;
    right.write(curr_move_right);
    delay(10);
  }
}

void To_Pos_7(){
  int target_spin = init_pos_spin +32;
  int target_right_1 = init_pos_right + 5;
  int target_left_1 = init_pos_left + 37;

  while(curr_move_spin != target_spin){
    curr_move_spin = curr_move_spin + 1;
    right.write(curr_move_right);
    left.write(curr_move_left);
    spin.write(curr_move_spin);
    delay(10);
  }
  while(curr_move_left != target_left_1){
    curr_move_left = curr_move_left + 1;
    left.write(curr_move_left);
    delay(10);
  }
  while(curr_move_right != target_right_1){
    curr_move_right = curr_move_right + 1;
    right.write(curr_move_right);
    delay(10);
  }
}

void To_Pos_8(){
  int target_spin = init_pos_spin +25;
  int target_right_1 = init_pos_right + 11;
  int target_left_1 = init_pos_left + 65;

  while(curr_move_spin != target_spin){
    curr_move_spin = curr_move_spin + 1;
    right.write(curr_move_right);
    left.write(curr_move_left);
    spin.write(curr_move_spin);
    delay(10);
  }
  while(curr_move_left != target_left_1){
    curr_move_left = curr_move_left + 1;
    left.write(curr_move_left);
    delay(10);
  }
  while(curr_move_right != target_right_1){
    curr_move_right = curr_move_right + 1;
    right.write(curr_move_right);
    delay(10);
  }
}

void To_Pos_9(){
  int target_spin = init_pos_spin +19;
  int target_right_1 = init_pos_right + 34;
  int target_left_1 = init_pos_left + 78;

  while(curr_move_spin != target_spin){
    curr_move_spin = curr_move_spin + 1;
    right.write(curr_move_right);
    left.write(curr_move_left);
    spin.write(curr_move_spin);
    delay(10);
  }
  while(curr_move_left != target_left_1){
    curr_move_left = curr_move_left + 1;
    left.write(curr_move_left);
    delay(10);
  }
  while(curr_move_right != target_right_1){
    curr_move_right = curr_move_right + 1;
    right.write(curr_move_right);
    delay(10);
  }
}

void put_stone(){
  delay(2000); //等待1秒(1000毫秒秒
  claw.write(0);
  delay(2000); //等待1秒(1000毫秒秒
}


void catch_stone(){
  claw.write(claw_open);

  int target_spin = init_pos_spin + 50;
  int target_right_1 = init_pos_right + 29;
  int target_left_1 = init_pos_left + 23;

  while(curr_move_spin != target_spin){
    curr_move_spin = curr_move_spin + 1;
    right.write(curr_move_right);
    left.write(curr_move_left);
    spin.write(curr_move_spin);
    delay(10);
  }
  delay(500);
  while(curr_move_left != target_left_1){
    curr_move_left = curr_move_left + 1;
    left.write(curr_move_left);
    delay(10);
  }
  delay(500);
  while(curr_move_right != target_right_1){
    curr_move_right = curr_move_right + 1;
    right.write(curr_move_right);
    delay(10);
  }

  delay(500);
  claw.write(claw_close);
  delay(500);
  
  while(curr_move_left != init_pos_left + 20){
    curr_move_left = curr_move_left - 1;
    left.write(curr_move_left);
    delay(10);
  }
  delay(500);
  while(curr_move_right != init_pos_right - 20){
    curr_move_right = curr_move_right - 1;
    right.write(curr_move_right);
    delay(10);
  }
  delay(500);
  int flag = curr_move_spin - init_pos_spin;
  if(flag < 0){
    while(curr_move_spin != init_pos_spin){
      curr_move_spin = curr_move_spin + 1;
      spin.write(curr_move_spin);
      right.write(curr_move_right);
      left.write(curr_move_left);
      delay(10);
    }
  }
  else{
    while(curr_move_spin != init_pos_spin){
      curr_move_spin = curr_move_spin - 1;
      spin.write(curr_move_spin);
      right.write(curr_move_right);
      left.write(curr_move_left);
      delay(10);
    }    
  }
  delay(2000);
  
}

void loop(){ //Arduino板子的無限執行迴圈 (初始化完後，會反複執行此一副程式)
  unsigned char *image = ov7670.capture();
  if (!image) {
    Serial.println("Failed to capture image");
    return;
  }

  for (int i = 0; i < ov7670.getImageSize(); i++) {
    BTSerial.write(image[i]);
  }

  while(mySerial.available() <= 0);

  Serial.write(mySerial.read());
  
  int pos = Serial[0];
  
  right.write(init_pos_right);
  left.write(init_pos_left);
  spin.write(init_pos_spin);
  claw.write(init_pos_claw);
  
  curr_move_right = init_pos_right;
  curr_move_left = init_pos_left;
  curr_move_spin = init_pos_spin;

  //catch_stone();
  //To_Pos_5();
  //put_stone();
  //back_init_pos(); 
  if(pos == 5){
    catch_stone();
    To_Pos_5();
    put_stone();
    back_init_pos();    
  }
  else if(pos == 4){
    catch_stone();
    To_Pos_4();
    put_stone();
    back_init_pos();  
  }
  else if(pos == 3){
    catch_stone();
    To_Pos_3();
    put_stone();
    back_init_pos();  
  }
  else if(pos == 7){
    catch_stone();
    To_Pos_7();
    put_stone();
    back_init_pos();  
  }
  else if(pos == 1){
    catch_stone();
    To_Pos_1();
    put_stone();
    back_init_pos();  
  }
  else if(pos == 2){
    catch_stone();
    To_Pos_2();
    put_stone();
    back_init_pos();  
  }
  else if(pos == 9){
    catch_stone();
    To_Pos_9();
    put_stone();
    back_init_pos();  
  }
  else if(pos == 6){
    catch_stone();
    To_Pos_6();
    put_stone();
    back_init_pos();  
  }
  else{
    catch_stone();
    To_Pos_8();
    put_stone();
    back_init_pos();  
  }
  delay(1000);

}