file = open('C:\myproject\\app\static\\bestandinfoblacklist.csv','r')

newfile = []

name = input ("Geef de naam op van het bestand : ")

for line in file:
    data = line.split(",")
    if data[0] == name:
        verandering = "bestand is gewhitelist"
        newLine = "%s,%s,%s,%s \n" %(data[0],data[1],data[2],verandering)
        newfile.append(newfile)

    else:
        newfile.append(line)

    file.close()

    file = open('C:\myproject\\app\static\\bestandinfoblacklist1.csv',"w")

    for line in newfile:
        file.write(line)

    file.close()