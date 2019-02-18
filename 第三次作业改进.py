input_file = 'packet_capture.txt'
output_file = 'out_put.txt'
i=0
from countminsketch import CountMinSketch
sketch = CountMinSketch(100,1)  # m=100, d=1

with open(input_file) as file_object:
    lines = file_object.readlines()

lists = {}
for line in lines:
    x = line.split(' ', )
    if len(x) > 9:
        IP =str(x[2])+str(x[3])+str(x[4])
        if x[-2] == 'length':
            x[-1]=int(x[-1])
            if IP in lists.keys():
                lists[IP] += x[-1]
            else:
                lists[IP] = x[-1]
        sketch.add(IP)

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
