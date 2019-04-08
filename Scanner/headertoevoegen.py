import csv

f = open("C:\myproject\\app\static\\bestandinfoblacklist.csv", "w")
writer = csv.DictWriter(
    f, fieldnames=["filename", "directory", "file_hash_hex", "Modification date"])
writer.writeheader()
f.close()


