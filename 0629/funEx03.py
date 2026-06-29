dict1 = {"name":"alice","age":30,"city":"new york"}
dict2 = {"name":"bob","age":30,"city":"los angeles"}

#for key in dict1:
#    print(f"{key}:{dict1[key]}")

#for key,value in dict1.items():
#    print(f"{key}:{value}")
 
#동일


def print_kwarge(**kwargs):
    for key,value in kwargs.items():
        print(f"{key}:{value}")

print_kwarge(name="charlie",age=35,city="chicago")