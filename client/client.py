import requests
import json
url='http://127.0.0.1:3000/add'

data = { "time":'12:34:56',
        "val1":'いいい',
        "val2":123 }

print(json.dumps(data))
response = requests.post(url,data=json.dumps(data))
print(response)
