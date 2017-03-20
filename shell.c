/*    Copyright 2013 Meredith Myers

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
void prnt(char buff);
void parseInput(char buffer);
int div(int a, int b);
void printChar(char ch);
void clear(char*,int);

char parent[7];
char dir[7];

main(){
	char buffer[180];
  dir[0] = 0x00;
  dir[1] = 0x00;
  dir[2] = 0x00;
  dir[3] = 0x00;
  dir[4] = 0x00;
  dir[5] = 0x00;
  dir[6] = 0x00;
  dir[7] = 0x00;
  dir[8] = 99;
  
  parent[0] = 0x00;
  parent[1] = 0x00;
  parent[2] = 0x00;
  parent[3] = 0x00;
  parent[4] = 0x00;
  parent[5] = 0x00;
  parent[6] = 0x00;
  parent[7] = 0x00;
  
	prnt("Hello, Modified Shell is Running!");
	prnt("\r\n");
	prnt("shell> ");

	while(1){
		
		interrupt(0x21,1,buffer,0,0);	
		prnt("\r\n");
		prnt("shell> ");
		parseInput(buffer);
		clear(buffer,180);

	}
}

void parseInput(char* buff){
	char grabBuff[180];
	char createBuff[512];
	int createIndex = 0;
	char fileName[13];
	char type[4];
	char run[3];
	char dirBuff[512];
	char fileBuff[13312];
	char fileName1[13];
	char fileName2[13];
  char parentName[13];
	char parentName2[13];
	int bools = 1;
	int bufferCt = 0;
	int indexIn, index;
	int end;
	int i = 0;
	int lock = 0;
	int fileLen = 0;
	int sectors;
  int yes;
	int input = 1;
	char b[512];
	int lnCt=0;
	while(bools){
		if (buff[bufferCt] == 0x0 || buff[bufferCt] == "\0"){
			
			bools = 0;
		}
		else{
			bufferCt++;
		}
	}
	for (indexIn = 0; indexIn <180; indexIn++){

		if(buff[indexIn] != 0x0 && buff[indexIn] != '\r' && buff[indexIn] != '\n' && buff[indexIn] != '-' && buff[indexIn] != '>'){
			break;
		}
	}
	for (end=indexIn;end<180;end++){

		if(buff[end] == '\r'){
			break;
		}
	}
	
	if (end - indexIn < 1){
		prnt("Too short!");
	}
	else if (buff[indexIn]=='t' && buff[indexIn+1]=='y' && buff[indexIn+2]=='p' && buff[indexIn+3]=='e'){
		indexIn = indexIn + 5;

		for(i=0;i<6;i++){
			fileName[i] = buff[indexIn+i];
		}
		fileName[6] = "\0";
		
		interrupt(0x21, 3, fileName, fileBuff, 0);

		prnt(fileBuff);
		prnt("shell> ");


		
	}
	else if (buff[indexIn]=='e' && buff[indexIn+1]=='x' && buff[indexIn+2]=='e' && buff[indexIn+3]=='c' && buff[indexIn+4]=='u' && buff[indexIn+5]=='t' && buff[indexIn+6]=='e'){
		
		indexIn = indexIn + 8;

		for(i=0;i<6;i++){
			fileName[i] = buff[indexIn+i];
		}
		fileName[6] = "\0";

		interrupt(0x21, 4, fileName, 0x2000, 0);
		
	}
	else if (buff[indexIn]=='d' && buff[indexIn+1]=='e' && buff[indexIn+2]=='l' && buff[indexIn+3]=='e'&& buff[indexIn+4]=='t' && buff[indexIn+5]=='e'){
		indexIn = indexIn + 7;

		for(i=0;i<6;i++){
			fileName[i] = buff[indexIn+i];
		}
		fileName[6] = "\0";

    interrupt(0x21,7,fileName,0,0);
	}
	else if (buff[indexIn]=='c' && buff[indexIn+1]=='o' && buff[indexIn+2]=='p' && buff[indexIn+3]=='y'){
		/* Get the file names Split at space char */

		index = indexIn+5;
		i = 0;
		while(buff[index] != 0x20 && buff[index] != 0x0){
			fileName1[i] = buff[index];
			index++;
			i++;
		}
		fileName1[6] = '\0';

		i = 0;
		index++;
		while(buff[index] != 0x20 && buff[index] != 0x0){
			fileName2[i] = buff[index];
			index++;
			i++;
		}
		fileName2[6] = '\0';
		/* Have the file names. Read in filename1 */
		interrupt(0x21,3,fileName1,fileBuff,0);
    
    /* Figure out how many sectors we need */
		while(fileBuff[fileLen] != 0x0){
			fileLen++;
		}		
		sectors = div(fileLen,512);
		/* Write fileBuff (with fileName1 inside of it) to fileName2 */
    
    interrupt(0x21,8,fileName2,fileBuff,sectors+1);
		
	}
	else if (buff[indexIn]=='d' && buff[indexIn+1]=='i' && buff[indexIn+2]=='r'){
		interrupt(0x21,11,dir,0,0);
		prnt("shell> ");

	}
	else if (buff[indexIn]=='c' && buff[indexIn+1]=='r' && buff[indexIn+2]=='e' && buff[indexIn+3]=='a'&& buff[indexIn+4]=='t' && buff[indexIn+5]=='e' && buff[indexIn+6]!='d'){
		indexIn = indexIn + 7;
		prnt("START FILE HERE: \r\n");
		prnt("\t-:");
		for(i=0;i<6;i++){
			fileName[i] = buff[indexIn+i];
		}
		fileName[6] = "\0";

		while(input){
			/* Get user input */
			clear(grabBuff,180);

			interrupt(0x21,1,grabBuff,0,0);
			prnt("\r\n");
			prnt("\t-:");

			if (grabBuff[2] == 0x0){
				prnt("END OF FILE");
				prnt("\r\n");
				prnt("shell> ");
				input = 0;
				break;
			}
			else{

				for(i=0;i<180;i++){
					if(grabBuff[i] == 0x0 || grabBuff[i] == '\0'||grabBuff[i]=='\r'||grabBuff[i]=='\n'||grabBuff[i]=='\t'){
						grabBuff[i] = 0x20;
					}
					createBuff[i+180*createIndex] = grabBuff[i];
				}
				lnCt++;
				createIndex++;
			}
		}	
		sectors = div(lnCt/512);
		/* Now create the file */
		interrupt(0x21,8,fileName,createBuff,lnCt);

	}
  else if (buff[indexIn]=='t' && buff[indexIn+1]=='e' && buff[indexIn+2]=='s'){
   
    prnt("cur dir : ");prnt(dir);
    prnt("\r\n");
   prnt("parent of cur dir : ");prnt(parent);
    prnt("\r\n");
  /*  prnt("testing searchParent : ");
   interrupt(0x21,10,dir,&yes,parentName);
   prnt(parentName);
   prnt("\r\n");*/
				prnt("shell> ");
   
		
	}
  else if (buff[indexIn]=='c' && buff[indexIn+1]=='r' && buff[indexIn+2]=='e' && buff[indexIn+3]=='a'&& buff[indexIn+4]=='t' && buff[indexIn+5]=='e' && buff[indexIn+6]=='d'&& buff[indexIn+7]=='i' && buff[indexIn+8]=='r'){
    
    indexIn = indexIn + 10;

		for(i=0;i<6;i++){
			fileName[i] = buff[indexIn+i];
      if ((fileName[i] == 0x0) || (fileName[i] == '\r') || (fileName[i] == '\n')){
        fileName[i] = 0x20;
      }
		}
    for(i=6;i<12;i++){
			fileName[i] = dir[i-6];
		}
    
    
		fileName[12] = "\0";
    prnt("\r\n");
    prnt("the name we got : ");prnt(fileName);
    prnt("\r\n");
    
    interrupt(0x21,8,fileName,0,0);
     prnt("\r\n");
		prnt("shell> ");
    
	} 
  else if (buff[indexIn]=='c' && buff[indexIn+1]=='d'){
    /*can go to any directory, not only the one in the current directries*/
    /* assuming that directory names ( and also filenames) are all unique*/
    yes = 0;
    indexIn = indexIn + 3;

    if (buff[indexIn] != '.') {
      prnt("this in\r\n");
      for(i=0;i<6;i++){
        fileName[i] = buff[indexIn+i];
      }
      interrupt(0x21,10,fileName,&yes,parentName);
      prnt("the parent we got : ");prnt(parentName);
      prnt("\r\n");
      if (yes > 0) {
        /*check if it's on curent directory
        for(i = 0; i < 6; i++){
          if (dir[j] == 0x0 || dir[j] == '\r' || dir[j] == '\n' && parentName[j] == 0x0 || parentName[j] == '\r' || parentName[j] == '\n') {
            break;
          }
          yes &= (parentName[i] == dir[i]);
        }
        if (yes > 0) {     */   
          for(i=0;i<6;i++){
            parent[i] = dir[i];
            dir[i] = fileName[i];
          }
          prnt("and we're in the dir : ");prnt(dir);
          prnt("\r\n");
        //}
      }
    } else {
      for(i=0;i<7;i++){
        dir[i] = parent[i];
      }
      interrupt(0x21,10,parent,&yes,parentName);
      for(i=0;i<7;i++){
        parent[i] = parentName[i];
      }
    }
    prnt("\r\n");
		prnt("shell> ");
  }
  else{
		prnt("Command not found!");
		prnt("\r\n");
		prnt("shell> ");
	}
}
int div(int a, int b){
    int q = 0;
    while(q*b <=a){
        q = q+1;
    }
    return q-1;

}
void prnt(char* buff){
	interrupt(0x21,0,buff,0,0);
}
void clear(char* buff, int len){
	int i;
	for(i=0;i<len;i++){
		buff[i] = 0x0;
	}
}
void printChar(char ch){
	char* chars[2];
	chars[0] = ch;
	chars[1] = '\0';
	prnt(chars);
}
