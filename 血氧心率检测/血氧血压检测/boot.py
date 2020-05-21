

# This file is executed on every boot (including wake-boot from deepsleep)
#import esp
#esp.osdebug(None)
import uos, machine
#uos.dupterm(None, 1) # disable REPL on UART(0)
import gc
#import webrepl
#webrepl.start()
gc.collect()
import time
from machine import Pin,I2C
from ssd1306 import SSD1306_I2C
from get_data import get
#import webrepl
import urandom
import binascii
import os
from net_connect import do_connect
from upload_data import upload
led = machine.Pin(2,machine.Pin.OUT)
def main_loop():
      
    gpio_scl=Pin(14)
    gpio_sda=Pin(12)
    i2c=I2C(scl=gpio_scl,sda=gpio_sda,freq=400000)
    print(i2c.scan())
    i2c.writeto_mem(87,1,b'\xf0')
    i2c.writeto_mem(87,3,b'\x02')
    i2c.writeto_mem(87,33,b'\x01')
    i2c.writeto_mem(87,10,b'\x43')
    i2c.writeto_mem(87,12,b'\xff')
    i2c.writeto_mem(87,13,b'\xff')
    i2c.writeto_mem(87,9,b'\x0b')
    i2c.writeto_mem(87,8,b'\x0f')  
    i2c2 = I2C(scl=Pin(5), sda=Pin(4))  
    oled = SSD1306_I2C(128, 64, i2c2)
    oled.fill(1)
    oled.show()
    oled.fill(0)
    oled.show() 
    while True:
      oo2=[]
      IRdata1=[]
      Rdata1=[]
      l=0
      while(l<1):
        if(i2c.readfrom_mem(87,4,1)==b'\x1f'):
          oo2=i2c.readfrom_mem(87,7,192)
          for i in range(1,33):        
            IRdata1.append(oo2[6*(i-1)+0]*65536+oo2[6*(i-1)+1]*256+oo2[6*(i-1)+2])
            Rdata1.append(oo2[6*(i-1)+3]*65536+oo2[6*(i-1)+4]*256+oo2[6*(i-1)+5])  
          l=l+1
          oled.text('SPO2&HR detector', 0, 0)
          oled.text('Place ur finger', 4, 20)
          oled.show()
      if Rdata1[10]>=3500: 
        oled.fill(0)
        oled.show()
        oled.text('Hold on for 8s', 4, 20)
        oled.show()
        time.sleep(1)
        oled.fill(0)
        oled.show()
        HR,PO=get(oled)
        if HR>20:
          oled.fill(0)
          oled.show()
          oled.text('Uploading data', 4, 20)
          oled.show()
          upload(HR,PO)
          oled.fill(0)
          oled.show()
          oled.text('successful!', 4, 20)
          oled.show()
          time.sleep(1)
          oled.fill(0)
          oled.show()
          
          
if __name__ == "__main__": 
      do_connect()
      for i in range(3):
          led.on()
          time.sleep(0.5)
          led.off()
          time.sleep(0.5)
      main_loop()
          







