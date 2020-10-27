import paho.mqtt.client as mqtt
from tempfile import NamedTemporaryFile
import shutil
import csv

def getFilePath():
    filename = r"C:\Users\ASUS\source\repos\TransferMedicalImages\TransferMedicalImages\Status.csv"
    return filename

def OpenAndUpdateCSVFile(DiagnosedImageName,filename):

    tempfile = NamedTemporaryFile(mode='w', delete=False)

    fields = ['IMAGE_NAME','DIAGNOSIS_STATUS']
    with open(filename, 'r') as csvfile, tempfile:
        reader = csv.DictReader(csvfile, fieldnames=fields)
        writer = csv.DictWriter(tempfile, fieldnames=fields)
        for row in reader:
            if row['IMAGE_NAME'] ==DiagnosedImageName:
                print('updating row', row['IMAGE_NAME'])
                row['IMAGE_NAME'], row['DIAGNOSIS_STATUS'] = "0.img","Completed"
            row = {'IMAGE_NAME': row['IMAGE_NAME'], 'DIAGNOSIS_STATUS': row['DIAGNOSIS_STATUS']}
            writer.writerow(row)
    shutil.move(tempfile.name, filename)

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("ImageName")
   
def on_message(client, userdata, msg):
    filename=getFilePath()
    ImageName=msg.payload.decode("utf-8")
    OpenAndUpdateCSVFile(ImageName,filename)
    print(msg.topic+" "+(msg.payload).decode("utf-8"))

if __name__=="main":
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("mqtt.eclipse.org", 1883, 60)
    client.loop_forever()

