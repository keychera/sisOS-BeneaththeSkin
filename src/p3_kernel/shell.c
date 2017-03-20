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

main(){
	char buffer[180];
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
	char fileName[7];
	char type[4];
	char run[3];
	char dirBuff[512];
	char fileBuff[13312];
	char fileName1[7];
	char fileName2[7];
	int bools = 1;
	int bufferCt = 0;
	int indexIn, index;
	int end;
	int i = 0;
	int lock = 0;
	int fileLen = 0;
	int sectors;
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
