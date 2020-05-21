
import serial
import time

# portx= input('choose a com (/dev/ttyUSB0 or dev/ttyUSB20)')
bps=19200
portx = "COM6" #'/dev/ttyUSB0'
timex = 1
#print('write' + str(ser.write('hello\n'.encode('ascii'))) + '\n')
#print('read :' + str(ser.readline()))
ser=serial.Serial(portx,bps,timeout=timex)
# ser.close()

def monit(ser,ltime):
    # ser.open()
    t1 = time.time()
    while 1:
        re = ser.readline()
        print(re)
        out = []
        for i in re:
            out.append(hex(i))
        print(out)
        if time.time() - t1 > ltime:
            break
    # ser.close()

def sendcmd(ser,cmd):
    ser.write(cmd)
    ser.write('\n'.encode())


def timeset(a):# in form yyyy/MM/dd/hh/mm/ss
    pcmd = []
    a = a.encode()
    for i in [2,3,5,6,8,9,11,12,14,15,17,18]:
        pcmd.append(a[i]&0x0f)
    cmd = []
    for i in range(6):
        cmd.append(pcmd[i*2]<<4 | pcmd[2*i+1])
    cmd.insert(1,0x01)
    cmd.reverse()
    cmd = b"TS" + bytes(cmd)
    sendcmd(ser,cmd)

def setFeedPlan(TL,WL): #HH time list and weight list
    addr = 0;
    for (t,w) in zip(TL,WL):
        cmd = b'FS'
        t = t.encode()
        cmd += bytes([addr,((t[1] & 0x0f)) | ((t[0] & 0x0f)<<4),w])
        addr += 1
        sendcmd(ser,cmd)
        time.sleep(0.15)
        print(cmd)
    sendcmd(ser,b'FS' + bytes([addr]) + b'\x25\x00')
        
def gettime():
    def bTos(byte):
        return (byte&0x0f) + 0x30, ((byte&0xf0)>>4) + 0x30
    re = []
    sendcmd(ser,b'TR')
    try:
        re.append(ser.readline())
    except:
        pass
    back = []
    for i in re:
        if len(i) == 8 and i != b'ACK CMD\n' and i!= b'Not Empty\n':
            for k in i:
                a, b = bTos(k)
                back.insert(0,a)
                back.insert(0,b)
            break
    del back[0:2]
    return bytes(back).decode()

def getweight():
    re = []
    sendcmd(ser,b'WR')
    re.append(ser.readline())
    re.append(ser.readline())
    # re.append(ser.readline())
    # re.append(ser.readline())
    for i in re:
        if i[-2] == 'g'.encode():
            we = i[0:-2].decode()
            return eval(we)
        if i[0:2] == "NO".encode():
            return False

def getFeedPlan():
    def bTos(byte):
        return  ((byte&0xf0)>>4) + 0x30 , (byte&0x0f) + 0x30
    re = []
    out = [[],[]]
    sendcmd(ser,b'FR')
    while out[0] == [] or out[1] == []:
        out = [[],[]]
        re = []
        sendcmd(ser,b'FR')
        re.append(ser.readline())
        re.append(ser.readline())
        # print(re)

        for i in re:
            if i[0:2] == b'FT':
                for _ in i[2:-1]:
                    out[0].append(bytes(bTos(_)))
                break
        for i in re:
            if i[0:2] == b'FW':
                for _ in i[2:-1]:
                    out[1].append(_)
                break
    return out 

            


    
if __name__ == "__main__":

    def testsend(cmd):
        sendcmd(ser,cmd)
        ser.flush()
        print(ser.readline())
        print(ser.readline())
        print(ser.readline())
        print(ser.readline())
        print(ser.readline())

    while(1):
        a = input("waiting...")
        monit(ser,eval(a))
        # getFeedPlan()

        #
        #  timeset(a)
        # if a == 'kkk':
        #     pass
        # elif a[0:3] =="mmm":
        #     monit(ser,eval(a[3:]))
        # else:
        #     testsend(a.encode())
        # print(gettime())
        # print(getFeedPlan())
        time.sleep(1)



        
    
    
    
   

