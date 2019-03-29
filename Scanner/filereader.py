import os
import csv
import hashlib
import schedule
import time
import zipfile


#Laat de code runnen als een deamon
def job():

    #Verwijzing naar het juiste pad
    os.chdir("C:/myproject/scanner/dummy_folder/")

#Loopt door de dummy folder heen en laat alle bestanden in de dummy folder zien
for root, dirs, files in os.walk("C:\myproject\scanner\dummy_folder"):
        for filename in files:
         print(filename)

#Hasht bestanden
def file_hash_hex(file_path, hash_func):
    with open(file_path, 'rb') as f:
        return hash_func(f.read()).hexdigest()

def recursive_file_listing(base_dir):
    for directory, subdirs, files in os.walk(base_dir):
        for filename in files:
            yield directory, filename, os.path.join(directory, filename)

src_dir = 'C:/myproject/scanner/dummy_folder'

with open('C:/myproject/logger/checksums_archive.csv', 'w') as f:
    writer = csv.writer(f, delimiter='\t', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    for directory, filename, path in recursive_file_listing(src_dir):
        fileToCheck = os.path.join(directory,filename)
        ts = time.ctime(os.path.getmtime(fileToCheck))
        writer.writerow((directory, filename, file_hash_hex(path, hashlib.md5),ts))
#Laat de tijd zien waarop de bestanden veranderd zijn
changedtime = time.ctime(os.path.getmtime('C:/myproject/scanner/dummy_folder/Implementation1.txt'))
print("last modified: " +changedtime)
dirToCheck = 'C:/myproject/scanner/dummy_folder'
for directory, filename, path in recursive_file_listing(src_dir):
    fileToCheck = os.path.join(directory,filename)
    ts = time.ctime(os.path.getmtime(fileToCheck))
    print ("last modified: " +ts)

#Het zippen van bestanden
os.chdir("C:/myproject/logger/")
zip1 = zipfile.ZipFile('C:/myproject/scanner/received/geziptehash.zip', 'w')
zip1.write('C:/myproject/logger/hashenpad.txt',compress_type=zipfile.ZIP_DEFLATED)
zip1.close()
print("Bestand gezipt")

schedule.every(5).seconds.do(job)
schedule.every().hour.do(job)
schedule.every().day.at("12:42").do(job)
time.sleep(0)

while 1:
    schedule.run_pending()
    time.sleep(0)


