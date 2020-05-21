

import time
from machine import Pin,I2C
from ssd1306 import SSD1306_I2C
#import webrepl
import urandom
import binascii
import os
#webrepl.start()

def get_ordata():
    IRdata = []
    Rdata = []
    p=0
    f=open("hw.txt","w")
    while p<12:
        if(i2c.readfrom_mem(87,4,1)==b'\x1f'):
            oo=i2c.readfrom_mem(87,7,192)
            for i in range(1,33):        
                IRdata.append(oo[6*(i-1)+0]*65536+oo[6*(i-1)+1]*256+oo[6*(i-1)+2])
                Rdata.append(oo[6*(i-1)+3]*65536+oo[6*(i-1)+4]*256+oo[6*(i-1)+5]) 
                f.write(str(oo[6*(i-1)+3]*65536+oo[6*(i-1)+4]*256+oo[6*(i-1)+5])+'\n') 
                i2c.readfrom_mem(87,4,1)
            p=p+1
    f.close()
    Rdata[0]=Rdata[1]
    return Rdata,IRdata
  
def get():
    SP=[]
    sum1=0
    SPO2=0
    SPO=0
    hr=0
    str1=0
    str2=0
    Rdata5=[]
    IRdata5=[]
    Rdata,IRdata = get_ordata()

    for i in range(11):
        Rdata[32*(i+1)-1] = (Rdata[32*(i+1)-2] + Rdata[32*(i+1) ]) / 2
    for i in range(384):
        SP.append(IRdata[i]/Rdata[i])
    for i in range(384):
        sum1=sum1+SP[i]
    SPO=sum1/384
    SPO2=-45.060*SPO*SPO+30.354*SPO+94.845
    SPO3=round(SPO2,1)
    str2=str(SPO3)
    print(SPO3)
    maxsample = 0
    for i in range(375):
        maxd=Rdata[i:i+9]
        max1=max(maxd);
        min1=min(maxd);
        if (max1-min1) >= maxsample:
            maxsample=max1-min1
    maxsample *= 0.6
    print(maxsample)
    n2 = 1  
    i = 1
    d = []
    while(i<=375):
        maxd=Rdata[i:i+9]
        max1=max(maxd)
        min1=min(maxd)  
        if (max1-min1) >= maxsample:
            index1 = maxd.index(max1)+i-2
            index2=maxd.index(min1)+i-2
            d.append((index1+index2)/2)# 数组d存放的是可能需要的点
            i=i+25
        i=i+1
        u=1;
    #将数组d内的数据前后求差，满足25-50内的点保存到数组r里（心率60-120）
    r = []
    for o in range(len(d)-1):
        p=d[o+1]-d[o];
        if p > 30 and p < 50:
            r.append(p)
    print(r)
    if (len(r)<=1 or Rdata[4]<2500):
      #oled.fill(0)
      #oled.show()
     # for i in range(3):
       # oled.text('No figure!', 4, 20)
       # oled.show()
      #  time.sleep(1)
       # oled.fill(0)
       # oled.show()
     # oled.text('Waiting', 4, 20)
     # oled.show()
     # time.sleep(2)
    #  oled.fill(0)
    #  oled.show()
     # oo1=i2c.readfrom_mem(87,7,192)
      pass
      #return 0,0
    else:
        maxx=max(r)
        minn=min(r)
        if (maxx-minn)>=10:
            r[r.index(maxx)]=(maxx+minn)/2
            r[r.index(minn)]=(maxx+minn)/2
    #因为传感器写数据的频率是50HZ，所以用下式计算
        hr=3000/(sum(r)/len(r))
        hr1=int(hr)
        str1=str(hr1)
        #oled.fill(0)
        #oled.show()
        #oled.text('SPO2:'+str2+'%', 10, 20)
        #oled.text('  HR:'+str1, 10, 35)
        #oled.show()
        time.sleep(4)
        print(hr1)   
    return hr1,SPO3
gpio_scl=Pin(14)
gpio_sda=Pin(12)
i2c=I2C(scl=gpio_scl,sda=gpio_sda,freq=400000)
i2c.writeto_mem(87,1,b'\xf0')
i2c.writeto_mem(87,3,b'\x02')
i2c.writeto_mem(87,33,b'\x01')
i2c.writeto_mem(87,10,b'\x43')
i2c.writeto_mem(87,12,b'\xff')
i2c.writeto_mem(87,13,b'\xff')
i2c.writeto_mem(87,9,b'\x0b')
i2c.writeto_mem(87,8,b'\x0f')  



















