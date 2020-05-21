

import urequests
import ujson

# before using this module you may visit https://dweet.io/dweet/for/rollingjcjsheartantasdxsesp8266e?hello=world

def upload(HR,PO):
    data ='HR=' + str(HR) +'&PO=' + str(PO)
    response = urequests.get('https://dweet.io/dweet/for/rollingjcjsheartantasdxsesp8266e?'+data)
    trytime = 0
    while ujson.loads(response.text)['this'] != 'succeeded':
        response = urequests.get('https://dweet.io/dweet/for/rollingjcjsheartantasdxsesp8266e?'+data)
        trytime += 1
        if trytime > 4:
            return 0
    return 1
  
if __name__ == "__main__": # if just for test.Do not change it.
    from time import sleep
    list = [(i,i) for i in range(60,100,2)]
    for i,j in list:
        upload(i,j)
        sleep(30)
    print('over')
 



