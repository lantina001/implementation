import os
import csv
import hashlib
import time
import zipfile
import threading

src_dir = 'C:/myproject/scanner/dummy_folder'
log_dir = 'C:/myproject/logger/'


# fucntie voor Hasht bestanden
def file_hash_hex(file_path, hash_func):
    with open(file_path, 'rb') as f:
        return hash_func(f.read()).hexdigest()


# make comment here
def recursive_file_listing(base_dir):
    for directory, subdirs, files in os.walk(base_dir):
        for filename in files:
            yield directory, filename, os.path.join(directory, filename)


def job():
    # Verwijzing naar het juiste pad
    os.chdir(src_dir)

    # Loopt door de dummy folder heen en laat alle bestanden in de dummy folder zien
    for root, dirs, files in os.walk(src_dir):
        for filename in files:
            print(filename)
    with open(log_dir + '/bestandinfo.csv', 'w') as f:
        writer = csv.writer(f, delimiter=';', quotechar='"', quoting=csv.QUOTE_MINIMAL)

        for directory, filename, path in recursive_file_listing(src_dir):
            fileToCheck = os.path.join(directory, filename)
            ts = time.ctime(os.path.getmtime(fileToCheck))
            writer.writerow([filename, directory, file_hash_hex(path, hashlib.md5), ts])
    # Laat de tijd zien waarop de bestanden veranderd zijn
    for directory, filename, path in recursive_file_listing(src_dir):
        fileToCheck = os.path.join(directory, filename)
        ts = time.ctime(os.path.getmtime(fileToCheck))
        print("last modified: " + ts)

    # Het zippen van bestanden
    os.chdir(log_dir)
    zip1 = zipfile.ZipFile(log_dir + '/geziptehash.zip', 'w')
    zip1.write(log_dir + '/bestandinfo.csv', compress_type=zipfile.ZIP_DEFLATED)
    zip1.close()
    print("Bestand gezipt")


# Laat de code runnen als een deamon
def printit():

    try:
        threading.Timer(0.5, printit).start()
        job()
    except (KeyboardInterrupt, SystemExit):
        print("interrupt!")

printit()



