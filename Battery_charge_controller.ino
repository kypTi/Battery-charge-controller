#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C _lcd1(0x27, 16, 2);
int _dispTempLength1=0;
boolean _isNeedClearDisp1;
bool _FreeLog2_IArr[2];
bool _FreeLog2_Q1_StArr[] = {1, 0};
bool _FreeLog2_Q2_StArr[] = {0, 0};
bool _FreeLog2_Q3_StArr[] = {0, 1};
bool _FreeLog2_Q1 = 0;
bool _FreeLog2_Q2 = 0;
bool _FreeLog2_Q3 = 0;
int _disp3oldLength = 0;
int _disp5oldLength = 0;
int _disp1oldLength = 0;
int _disp2oldLength = 0;
int _disp4oldLength = 0;
void setup()
{
    pinMode(2, OUTPUT);
    digitalWrite(2, 0);
    pinMode(3, OUTPUT);
    digitalWrite(3, 0);
    pinMode(4, OUTPUT);
    digitalWrite(4, 0);
    pinMode(9, OUTPUT);
    digitalWrite(9, 0);
    Wire.begin();
    delay(10);
    _lcd1.init();
    _lcd1.backlight();
}
void loop()
{
    if (_isNeedClearDisp1) 
    {
        _lcd1.clear();
        _isNeedClearDisp1= 0;
    }
    //Плата:1
    _FreeLog2_IArr[0] = ((analogRead (2))) > (767);
    _FreeLog2_IArr[1] = ((analogRead (2))) < (307);
    _FreeLog2_Q1 = _checkFreeLogicBlockOutput(_FreeLog2_IArr, 2, _FreeLog2_Q1_StArr, 2);
    _FreeLog2_Q2 = _checkFreeLogicBlockOutput(_FreeLog2_IArr, 2, _FreeLog2_Q2_StArr, 2);
    _FreeLog2_Q3 = _checkFreeLogicBlockOutput(_FreeLog2_IArr, 2, _FreeLog2_Q3_StArr, 2);
    digitalWrite(4, _FreeLog2_Q3);
    digitalWrite(3, _FreeLog2_Q2);
    digitalWrite(2, _FreeLog2_Q1);
    digitalWrite(9, ((analogRead (2))) < (102));
    if (((analogRead (2))) < (102)) 
    {
        _dispTempLength1 = (String("NEEDED CHARGING")).length();
        if (_disp1oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp1oldLength = _dispTempLength1;
        _lcd1.setCursor(int((16 - _dispTempLength1)/2), 0);
        _lcd1.print(String("NEEDED CHARGING"));
    }
     else 
    {
        if (_disp1oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp1oldLength = 0;
        }
    }
    if (!(((analogRead (2))) < (102))) 
    {
        _dispTempLength1 = ((((((String("Power: ")) + ((String((int(((analogRead (2)))*(0.09775))), DEC))))) + (String(" %"))))).length();
        if (_disp5oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp5oldLength = _dispTempLength1;
        _lcd1.setCursor(int((16 - _dispTempLength1)/2), 0);
        _lcd1.print((((((String("Power: ")) + ((String((int(((analogRead (2)))*(0.09775))), DEC))))) + (String(" %")))));
    }
     else 
    {
        if (_disp5oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp5oldLength = 0;
        }
    }
    digitalWrite(9, ((analogRead (0))) > (175));
    if (((analogRead (0))) > (175)) 
    {
        _dispTempLength1 = (String("WARNING")).length();
        if (_disp4oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp4oldLength = _dispTempLength1;
        _lcd1.setCursor(int((16 - _dispTempLength1)/2), 1);
        _lcd1.print(String("WARNING"));
    }
     else 
    {
        if (_disp4oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp4oldLength = 0;
        }
    }
    if (!(((analogRead (0))) > (175))) 
    {
        _dispTempLength1 = (String("Temp.=        C")).length();
        if (_disp3oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp3oldLength = _dispTempLength1;
        _lcd1.setCursor(0, 1);
        _lcd1.print(String("Temp.=        C"));
    }
     else 
    {
        if (_disp3oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp3oldLength = 0;
        }
    }
    if (!(((analogRead (0))) > (175))) 
    {
        _dispTempLength1 = (((_floatToStringWitRaz((((((analogRead (1)))-(20.00))*(3.04))*(0.161))-(40.00),2)))).length();
        if (_disp2oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp2oldLength = _dispTempLength1;
        _lcd1.setCursor(7, 1);
        _lcd1.print(((_floatToStringWitRaz((((((analogRead (1)))-(20.00))*(3.04))*(0.161))-(40.00),2))));
    }
     else 
    {
        if (_disp2oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp2oldLength = 0;
        }
    }
}
String  _floatToStringWitRaz(float value, int raz)
{
    return String(value,raz);
}
bool _checkFreeLogicBlockOutput(bool inArray[], int inArraySize, bool stArray[], int stArraySize)
{
    int inIndex = 0;
    bool result = 1;
    for (int i = 0; i < stArraySize; i = i + 1)
    {
        if (!(inArray[inIndex] == stArray[i])) 
        {
             result = 0;
        }
        inIndex ++;
        if (inIndex == inArraySize)
        {
            if (result) 
            {
                 return 1;
            }
             else 
            {
                result = 1;
            }
            inIndex = 0;
        }
    }
    return 0;
}
