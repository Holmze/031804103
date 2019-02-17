input_file = 'Request.txt'
output_file = 'output.txt'
i=0
from countminsketch import CountMinSketch
sketch = CountMinSketch(100,1)  # m=100, d=1

with open(input_file) as file_object:
    lines = file_object.readlines()

lists = {}
for line in lines:
    x = line.split(' ',)
    x[0]=str(x[0])
    x[1]=int(x[1])
    if x[0] in lists.keys():
        lists[x[0]] += x[1]
    else:
        lists[x[0]] = x[1]
    sketch.add(str(x[0]))

def write_file(name):
    with open (output_file,'a') as file_object:
        name = ''.join(name)
        file_object.write(name+'\n')

def find_key (dict, value):
    return [k for k,v in dict.items() if v == value]

for value in lists.values():
    if value>50000:
        if sketch[str(find_key(lists,value))]>100:
            write_file(find_key(lists,value))
            i=i+1

with open(output_file, "r+") as file_object:
     old = file_object.read()
     file_object.seek(0)
     i=str(i)
     file_object.write(i+'\n')
     file_object.write(old)
