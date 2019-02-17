input_file = 'Request.txt'
output_file = 'output.txt'
i=0

def write_file(name):
    with open (output_file,'a') as file_object:
        name = ''.join(name)
        file_object.write(name+'\n')

def find_key (dict, value):
    for k, v in dict.items():
        if v == value:
            return k

def average(Dict):
    Len = len(Dict)
    Sum = sum(Dict.values())
    Average = Sum/Len
    return Average

def send_number(key):
    Send_number=1
    with open(input_file) as file_object:
        lines = file_object.readlines()
    for line in lines:
        x = line.split(' ',2)
        if x[0]==key:
            Send_number=Send_number+1
    return Send_number

with open(input_file) as file_object:
    lines = file_object.readlines()

lists = {}
for line in lines:
    x = line.split(' ',2)
    x[2]=int(x[2])
    if x[0] in lists.keys():
        lists[x[0]] += x[2]
    else:
        lists[x[0]] = x[2]

Med2 = 0
for value in lists.values():
    Med2 =Med2 + (value-average(lists))**2
Med = (Med2/len(lists))**0.5

for value in lists.values():
    S = average(lists)+2*Med
    if value>S:
        key0 = find_key(lists,value)
        if send_number(key0)>3:
            print(key0,value)
            write_file(key0)
            i=i+1

with open(output_file, "r+") as file_object:
     old = file_object.read()
     file_object.seek(0)
     i=str(i)
     file_object.write(i+'\n')
     file_object.write(old)
