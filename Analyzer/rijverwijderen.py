import pandas as pd
import csv


def header(msg):
    header("read text")
    filename= 'C:\myproject\\app\static\\bestandinfoblacklist.csv'
    df = pd.read_csv(filename)
    print(df)
    df.columns

with open('C:\myproject\\app\static\\bestandinfoblacklist.csv') as data_csv:
    data = csv.reader(data_csv, delimiter=';')

    for row in data:
        hash = {'filename':row[0],'directory':row[1],'file_hash':row[2],'timestamp':row[3]}
        print (hash)












