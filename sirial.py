import serial   #���W���[������pyserial����, import����ۂ�serial�ł���

def main():
    with serial.Serial('COM3',9600,timeout=1) as ser:
        while True:
            flag=bytes(input(),'utf-8')

            #�V���A���ʐM�ŕ����𑗐M����ۂ�, byte������ɕϊ�����
            #input()����ۂ̕������utf-8

            ser.write(flag)

            #�V���A���ʐM:���M

            if(flag==bytes('a','utf-8')):
                break;
        ser.close()

if __name__ == "__main__":
    main()