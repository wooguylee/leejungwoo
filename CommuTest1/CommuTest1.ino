char inBuffer[100];
int inBufCnt = 0;
char inCommuBuffer[100];
int inCommuCnt = 0;

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
}

unsigned long passCnt = 0;
void loop() {
  // read from port 1, send to port 0:
  if (Serial1.available()) {
    char inByte = Serial1.read();
    if( inByte == '\n' )
    {
      inCommuBuffer[inCommuCnt] = 0;
      Serial.println(inCommuBuffer);
      if( (inCommuBuffer[0] == 'A') || (inCommuBuffer[0] == 'C') )
      {
        int dataSize = 0;
        int dataStrtIdx = 0;
        for(int i=1; i<inCommuCnt; i++)
        {
          if( ('0' <= inCommuBuffer[i]) && (inCommuBuffer[i] <= '9') )
          {
            dataSize *= 10;
            dataSize += (inCommuBuffer[i] - '0');
          }
          else if( inCommuBuffer[i] == ':' )
          {
            dataStrtIdx = i+1;
            break;
          }
        }

        if( (dataSize > 0) && (dataStrtIdx > 0) )
        {
          if( inCommuBuffer[0] == 'A' )
          {
            int dataValue = 0;
            for(int i=0; i<dataSize; i++)
            {
              if( ('0' <= inCommuBuffer[i + dataStrtIdx]) && (inCommuBuffer[i + dataStrtIdx] <= '9') )
              {
                dataValue *= 10;
                dataValue += (inCommuBuffer[i + dataStrtIdx] - '0');
              }
            }

            Serial.println("Type - Analog");
            Serial.print("Size - ");
            Serial.println(dataSize);
            Serial.print("Data - ");
            Serial.print(dataValue);
            Serial.print(" * 2 = ");
            Serial.println(dataValue * 2);
            Serial.println();
          }
          else
          {
            Serial.println("Type - Chat");
            Serial.print("Size - ");
            Serial.println(dataSize);
            Serial.print("Data - ");
            Serial.println(&inCommuBuffer[dataStrtIdx]);
            Serial.println();
          }
        }
      }
      inCommuCnt = 0;
    }
    else
    {
      inCommuBuffer[inCommuCnt] = inByte;
      inCommuCnt++;      
    }
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
    char inByte = Serial.read();
    if( inByte == '\n' )
    {
      inBuffer[inBufCnt] = 0;
      Serial1.print("C");
      Serial1.print(inBufCnt);
      Serial1.print(":");
      Serial1.println(inBuffer);      
      inBufCnt = 0;
    }
    else
    {
      inBuffer[inBufCnt] = inByte;
      inBufCnt++;      
    }
  }

  if( passCnt > 200000 )
  {
    int sensorValue = analogRead(A0);
    Serial1.print("A");
    int compareValue = 1;
    for(int i=0; i<5; i++)
    {
      compareValue *= 10;
      if( sensorValue < compareValue )
      {
        Serial1.print(i+1);
        break;
      }
    }
    Serial1.print(":");
    Serial1.println(sensorValue);
    passCnt = 0;
  }

  passCnt++;
}
