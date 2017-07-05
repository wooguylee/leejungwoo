char first[10] = {'F', 'i', 'r', 's', 't',};
char second[10] = {'S', 'e', 'c', 'o', 'n', 'd',};

void setup() {
  Serial.begin(9600);
}

int passCnt = 0;
int itemCnt = 0;
void loop() {
  // check if data has been sent from the computer:
  if (Serial.available()) {
    passCnt = 0;
    char inChar = Serial.read();
    first[itemCnt] = inChar;
    second[itemCnt] = inChar;
    itemCnt++;
  }
  else if( passCnt < 300 )
  {
    passCnt++;
    if( passCnt == 300 )
    {
      first[itemCnt] = 0;
      second[itemCnt] = 0;
      Serial.println(first);
      Serial.println(second);
      itemCnt = 0;
      int addrFirst = (int)first;
      int addrSecond = (int)second;
      Serial.println(addrFirst, HEX);
      Serial.println(addrSecond, HEX);
    }
  }
}
