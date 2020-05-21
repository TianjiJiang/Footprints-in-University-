
import network
import time
def do_connect():
    wifi_list = [('HUAWEI P10', 'lxqwoaini625'),('123456','qwertyui')]
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.scan()#扫描当前环境下的ap
    if wlan.isconnected():#如果已连接则断开
        wlan.disconnect()
    print(wifi_list[1])
    wlan.connect(*wifi_list[1])
    print("连接中...")
      #等待wifi连接间隔1秒
    while not wlan.isconnected():
        time.sleep(1)
    print("\n连接成功...")
    #print('network config:', wlan.ifconfig()) # IF message printed don't include (0,0,0,0), the connection is successful
if __name__ == '__main__':
    do_connect()







