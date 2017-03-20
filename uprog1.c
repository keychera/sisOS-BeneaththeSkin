main(){
	interrupt(0x21,0x00,"THIS IS A USER PROGRAM BY GROUP 9\r\n\0",0,0);
  interrupt(0x21, 5, 0, 0, 0);
  while(1);
}
