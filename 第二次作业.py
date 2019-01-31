input_file = 'Request.txt'
output_file = 'output.txt'
i=0

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

def write_file(name):
    with open (output_file,'a') as file_object:
        name = ''.join(name)
        file_object.write(name+'\n')

def find_key (dict, value):
    return [k for k,v in dict.items() if v == value]

for value in lists.values():
    if value>1500:
        write_file(find_key(lists,value))
        i=i+1

with open(output_file, "r+") as file_object:
     old = file_object.read()
     file_object.seek(0)
     i=str(i)
     file_object.write(i+'\n')
     file_object.write(old)
