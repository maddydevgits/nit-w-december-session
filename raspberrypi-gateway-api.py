import serial
import time
import urllib3

ser=serial.Serial("/dev/ttyUSB0",9600,timeout=0.5)
apiGateway="https://mlew-api-iot.onrender.com/"
isSent=False

def sendtoAPIGateway(api):
        http=urllib3.PoolManager()
        response=http.request('get',api)
        print(response.data)

def sendAlert(api,alertType,alertMsg):
        http=urllib3.PoolManager()
        response=http.request('get',api+"/alert?type="+alertType+"&message="+alertMsg)
        print(response.data)

while True:
        if (ser.inWaiting()>0):
                data=ser.readline().decode('utf-8')
                data=data.split(',')
                h=data[1]
                t=data[2]
                print(h,t)
                sendtoAPIGateway(apiGateway+"/store"+"?label=Humidity&value="+h)
                sendtoAPIGateway(apiGateway+"/store"+"?label=Temperature&value="+t)
                if(float(h)>90 and isSent==False):
                        sendAlert("https://mlew-api-iot.onrender.com","danger","Humidity Alert")
                        isSent=True
                if(float(h)<60):
                        isSent=False
        #time.sleep(2)
